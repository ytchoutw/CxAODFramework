#include "iostream"


#include "CxAODMaker/METHandler.h"
#include "METUtilities/METRebuilder.h"
// declare static members
//MuonDecorator MuonHandler::m_decorator;



METHandler::METHandler(ConfigStore *config, xAOD::TEvent *event) :
  m_event(event)
{

  debug=false;

  // set container name
  m_config = config; //This is usually defined in ObjectHandler so I add here by hand
  m_containerName = m_config->get<std::string>("METContainer"); //This is usually defined in ObjectHandler so I add here by hand


  //// initialize the MET utilities tool
  m_metutil = new met::METRebuilder("METRebuilderTool");

  if( m_metutil->initialize()  != StatusCode::SUCCESS){
    std::cerr << "Cannot intialize METRebuilder" << std::endl; // or substitute your favourite messaging macro
    std::cerr << "Exiting... " << std::endl;
    exit(-1);
  }



//  // TODO: move to AnalysisBase
//  // get recommended systematic uncertainties from registry and add them to list
//  //----------------------------------------------------------------------------
//  const CP::SystematicRegistry& registry = CP::SystematicRegistry::getInstance();
//  // SystematicSet = set storing SystematicVariation(s)
//  const CP::SystematicSet& recommendedSystematics = registry.recommendedSystematics();
//
//  // this is the nominal set, no systematic -> empty!
//  m_sysList.push_back(CP::SystematicSet());
//  // loop on recommended systematic and add them to list if tool is affected
//  for (const CP::SystematicVariation sysVar : recommendedSystematics) {
//    std::cout << "sysVar.name() " << sysVar.name() << std::endl;
//    std::cout << "MonCalibrationAndSmearingTool is affected? "
//            << m_muonCalibrationAndSmearingTool->isAffectedBySystematic(sysVar)
//            << std::endl;
//    // check if tool is affected by systematic, if yes add it to list
//    if (m_muonCalibrationAndSmearingTool->isAffectedBySystematic(sysVar)) {
//      // CP tools take sets in order to be able to apply several systematic variations at once,
//      // but most of the times they just store one systematic variation
//      m_sysList.push_back(CP::SystematicSet());
//      m_sysList.back().insert(sysVar);
//    }
//  }

}

METHandler::~METHandler() {
  ////delete tool:
  //if (m_metutil) {
  //  delete m_metutil;
  //  m_metutil = 0;
  //}
}


EL::StatusCode METHandler::setMET(std::map<TString, xAOD::ElectronContainer*>* elec,
				  //std::map<TString, xAOD::PhotonContainer*>* gamma,
				  //std::map<TString, xAOD::TauJetContainer*>* taujet,
				  std::map<TString, xAOD::MuonContainer*>* muon,
				  std::map<TString, xAOD::JetContainer*>* jet){



  if(debug)std::cout << "SETTING MET" << std::endl;

  std::string m_eleTerm      = "RefEle"         ;
  std::string m_gammaTerm    = "RefGamma"       ;
  std::string m_tauTerm      = "RefTau"         ;
  std::string m_jetTerm      = "RefJet"         ;
  std::string m_muonTerm     = "Muons"          ;
  std::string m_softTerm     = "SoftClus"       ;
  std::string m_inputMap     = "METMap_RefFinal";
  std::string m_inputMETCont = "MET_RefFinal"   ;
  std::string m_outMETTerm   = "Final"          ;


  const xAOD::MissingETContainer* inputMETContainer = 0;
  if( m_event->retrieve( inputMETContainer, m_inputMETCont ).isFailure() ) {
    std::cout << "MET container could not be retrieved" << std::endl;
  }

  if (!inputMETContainer) {
    std::cerr << "Failed to retrieve MET_RefFinal container" << std::endl;
    return StatusCode::FAILURE;
  }



  xAOD::MissingETContainer::const_iterator met_it = inputMETContainer->find("Final");

  if (met_it == inputMETContainer->end()) {
    std::cerr << "No RefFinal inside MET container" << std::endl;
  }

  double mpx = (*met_it)->mpx();
  double mpy = (*met_it)->mpy();

  if(debug)std::cout << "Un-rebuilt MET: Missing Et (x,y): (" << mpx << "," <<  mpy << ")" << std::endl;

  bool doRebuild = false;

  if(!doRebuild){

    m_METContainer=(xAOD::MissingETContainer*)inputMETContainer;

  }else{
    //--------------------
    // Rebuilding MET
    // Create the new container and its auxiliary store.
    m_METContainer = new xAOD::MissingETContainer();
    xAOD::MissingETAuxContainer* METContainerAux = new xAOD::MissingETAuxContainer();
    m_METContainer->setStore( METContainerAux ); //< Connect the two


    const xAOD::MissingETComponentMap* metMap = 0;
    if( m_event->retrieve(metMap, m_inputMap).isFailure() ) {
      std::cout << "Unable to retrieve MissingETComponentMap: " << m_inputMap << std::endl;
      return StatusCode::SUCCESS;
    }

    const xAOD::MissingET* oldSoft = xAOD::MissingETComposition::getMissingET(metMap,m_softTerm);
    bool doTracks = MissingETBase::Source::isTrackTerm(oldSoft->source());

    bool m_doEle = false;
    //bool m_doGamma = false;
    //bool m_doTau = false;
    bool m_doMuon = false;


    if(m_doEle) {
      m_metutil->rebuildMET(m_eleTerm, &(*m_METContainer), (*elec)["Nominal"], metMap, doTracks);
    }

    //if(m_doGamma) {
    //  m_metutil->rebuildMET(m_gammaTerm, &(*m_METContainer),  (*gamma)["Nominal"], metMap, doTracks);
    //}
    //
    //if(m_doTau) {
    //  m_metutil->rebuildMET(m_tauTerm, &(*m_METContainer),  (*taujet)["Nominal"], metMap, doTracks);
    //}

    if(m_doMuon) {
      m_metutil->rebuildMET(m_muonTerm, &(*m_METContainer),  (*muon)["Nominal"], metMap, doTracks);
    }

    //m_metutil->rebuildJetMET(m_jetTerm, m_softTerm, &(*m_METContainer), (*jet)["Nominal"], metMap, doTracks);

    m_metutil->buildMETSum(m_outMETTerm, &(*m_METContainer));
    if(debug)std::cout << "Done rebuilding MET." << std::endl;

    double rebuilt_mpx = (*m_METContainer)["Final"]->mpx();
    double rebuilt_mpy = (*m_METContainer)["Final"]->mpy();

    if(debug)std::cout << "Rebuilt MET: Missing Et (x,y): (" << rebuilt_mpx << "," <<  rebuilt_mpy << ")" << std::endl;
  }

  return EL::StatusCode::SUCCESS;
}


xAOD::MissingET* METHandler::getMET() {
  xAOD::MissingETContainer::const_iterator met_it = m_METContainer->find("Final");
  if(met_it == m_METContainer->end()) {
    return nullptr;
  }
  return *met_it;
}


EL::StatusCode METHandler::fillOutputContainer() {
  //return fillOutputContainerCheck(&checkPassSel);
  //TODO ADD MORE SOPHISTICATED OUTPUT FILLING HERE

  xAOD::MissingETContainer* METNominal = new xAOD::MissingETContainer();
  xAOD::MissingETAuxContainer* METNominalAux = new xAOD::MissingETAuxContainer();
  METNominal->setStore( METNominalAux ); //< Connect the two

  xAOD::MissingETContainer::const_iterator met_it = m_METContainer->find("Final");

  xAOD::MissingET * met = new xAOD::MissingET();
  met->makePrivateStore( **met_it );
  METNominal->push_back( met );


  if (!m_event->record(METNominal, m_containerName + "___Nominal")) {
    return EL::StatusCode::FAILURE;
  }
  if (!m_event->record(METNominalAux, m_containerName + "___NominalAux.")) {
    return EL::StatusCode::FAILURE;
  }

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode METHandler::clearEvent() {
  return EL::StatusCode::SUCCESS;
}
