#include <iostream>

// jet specific includes
#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"
#include "CxAODMaker/JetHandler.h"
#include "JetCalibTools/JetCalibrationTool.h"
#include "JetSelectorTools/JetCleaningTool.h"
#include "xAODBTagging/BTagging.h"

// declare static members
JetDecorator JetHandler::m_decorator;

JetHandler::JetHandler(const std::string& name, ConfigStore & config, xAOD::TEvent * event,
                       EventInfoHandler & eventInfoHandler) :
  ObjectHandler(name, config, event, eventInfoHandler),
  m_jetCalibration(0),
  m_jetCleaning(0),
  m_jetAlgoName("none"),
  m_isMC(0)
{

  // set jet algorithm name
  m_config.getif<std::string>(name+"AlgoName",m_jetAlgoName);

}

JetHandler::~JetHandler() {

  //delete tools
  delete m_jetCalibration;
  delete m_jetCleaning;

}

EL::StatusCode JetHandler::initializeTools()
{
  m_isMC = m_eventInfoHandler.get_isMC();
  
  //initialize jet calibration tool - this hopefully will become less messy...
  //-----------------------------------------------------------------------------
  //std::string configFile = Form("%s/%s/%s",gSystem->Getenv("ROOTCOREBIN"),"data/JetCalibTools","CalibrationConfigs/JES_Full2012dataset_Preliminary_MC14.config");
  //std::string configFileDir = Form("%s/%s",gSystem->Getenv("ROOTCOREBIN"),"data/JetCalibTools");
  std::string configFile = "JES_Full2012dataset_Preliminary_MC14.config";
  std::string configFileDir = "JetCalibTools/CalibrationConfigs/";
  std::string calibSec = "EtaJES";
  if( ! m_isMC ) calibSec += "_Insitu";

  std::cout << "m_containerName " << m_containerName << " m_jetAlgoName " << m_jetAlgoName << " m_isMC " << m_isMC << std::endl;

  m_jetCalibration = new JetCalibrationTool("JetCorrectionTool", 
					    m_jetAlgoName.c_str(),
					    configFile.c_str(),
					    calibSec.c_str(),
					    !m_isMC,
					    configFileDir.c_str());
  if( ! m_jetCalibration->initializeTool("JetCorrectionTool").isSuccess() ) {
    Error("JetHandler()", "Failed to properly initialize the JetCalibration Tool. Exiting." );
    return EL::StatusCode::FAILURE;
  }

  // initialize and configure the jet cleaning tool
  //------------------------------------------------
  m_jetCleaning = new JetCleaningTool("JetCleaning");
  if ( m_config.get<bool>("debug") ) {
    m_jetCleaning->msg().setLevel( MSG::DEBUG );
  }
  m_jetCleaning->setProperty( "CutLevel", "MediumBad");
  if( ! m_jetCleaning->initialize().isSuccess() ) {
    Error("JetHandler()", "Failed to properly initialize the JetCleaning Tool. Exiting." );
    return EL::StatusCode::FAILURE;
  }
  
    
  // register ISystematicsTools
  //---------------------------
  m_sysToolList.clear();
  // TODO jet calib is no ISystematicsTool?
  //m_sysToolList.push_back(m_jetCalibration);
  
  
  return EL::StatusCode::SUCCESS;

}


EL::StatusCode JetHandler::decorate(xAOD::Jet * jet) 
{

  // add decoration to jet
  // TODO: do we really need the decorate method?
  if (!m_decorator.exists(jet, JetIntProps::goodJet)) {
    bool goodJet = m_jetCleaning->accept( *jet );
    m_decorator.set(jet, JetIntProps::goodJet, goodJet);
  }

  // set btagging discriminants in the output
  retrieveBTaggingDiscriminants(jet);
  //
  return EL::StatusCode::SUCCESS;
  
}



EL::StatusCode JetHandler::calibrateCopies(xAOD::JetContainer * particles, const CP::SystematicSet & sysSet) 
{
  
  // TODO apply syst variation

  // loop over the particles in the container
  for (xAOD::Jet * jet : *particles) {
    //this ensures that the DynAux container has the same number of entries as the original one
    setP4( jet , jet );

    //only calibrate and write good clean jets
    bool goodJet = m_jetCleaning->accept( *jet );
    m_decorator.set(jet, JetIntProps::goodJet, goodJet);

	
    // MC: calibrate pT - use shallow copy
    if ( goodJet ) {
      if ( m_jetCalibration->applyCorrection(*jet) == CP::CorrectionCode::Error ) {
        Error("JetHandler::calibrateCopies()", "JetCalibration tool reported a CP::CorrectionCode::Error");
        return StatusCode::FAILURE;
      }    
    }

    // decorate jet
    if ( decorate( jet ) != EL::StatusCode::SUCCESS ) return EL::StatusCode::FAILURE;
    
  }
  
  return EL::StatusCode::SUCCESS;

}

void JetHandler::retrieveBTaggingDiscriminants(xAOD::Jet * part) 
{
  const xAOD::BTagging * tagInfo = part->btagging();
  
  double discriminant_mv1 = 0;
  double discriminant_sv1_ip3d = 0;
  double discriminant_mv2c00=0;
  double discriminant_mv2c10=0;
  double discriminant_mv2c20=0;
  double discriminant_mvb=0;
  
  if(tagInfo) {
    // for the moment - ignore the retval since we've set a default value
    bool retval = tagInfo->MVx_discriminant("MV1",discriminant_mv1);
    discriminant_sv1_ip3d = tagInfo->SV1plusIP3D_discriminant();
    retval = tagInfo->MVx_discriminant("MV2c00",discriminant_mv2c00);
    retval = tagInfo->MVx_discriminant("MV2c10",discriminant_mv2c10);
    retval = tagInfo->MVx_discriminant("MV2c20",discriminant_mv2c20);
    retval = tagInfo->MVx_discriminant("MVb",discriminant_mvb);
  }
  m_decorator.set(part,JetFloatProps::MV1, discriminant_mv1);
  m_decorator.set(part,JetFloatProps::SV1_IP3D,discriminant_sv1_ip3d);
  m_decorator.set(part,JetFloatProps::MV2c00,discriminant_mv2c00);
  m_decorator.set(part,JetFloatProps::MV2c10,discriminant_mv2c10);
  m_decorator.set(part,JetFloatProps::MV2c20,discriminant_mv2c20);
  m_decorator.set(part,JetFloatProps::MVb,discriminant_mvb);
}

bool JetHandler::checkPassSelOR(xAOD::Jet * part)
{

  int res = 0;
  m_decorator.get(part, JetIntProps::passORGlob, res);
  return res;

}


bool JetHandler::checkPassSelNoOR(xAOD::Jet * part)
{

  int res = 0;
  m_decorator.get(part, JetIntProps::isVetoJet, res);
  return res;

}


bool JetHandler::passVetoJet(xAOD::Jet* jet)
{
  
  bool passCentral = true;
  if (!(jet->pt() > 20000.)) passCentral = false;
  if (!(fabs(jet->eta()) < 2.5)) passCentral = false;
  
  bool passForward = true;
  if (!(jet->pt() > 30000.)) passForward = false;
  if (!(fabs(jet->eta()) >= 2.5)) passForward = false;
  if (!(fabs(jet->eta()) < 4.5)) passForward = false;
  
  bool passSel = true;
  if (!(m_decorator.get(jet, JetIntProps::goodJet))) passSel = false;
  if (!(passCentral || passForward)) passSel = false;
  
  m_decorator.set(jet, JetIntProps::isVetoJet, passSel);
  return passSel;
}


bool JetHandler::passSignalJet(xAOD::Jet* jet)
{
  
  bool passSel = true;
  if (!(m_decorator.get(jet, JetIntProps::isVetoJet))) passSel = false;
  if (!(jet->pt() > 20000.)) passSel = false;
  if (!(fabs(jet->eta()) < 2.5)) passSel = false;
  
  m_decorator.set(jet, JetIntProps::isSignalJet, passSel);
  return passSel;
}


EL::StatusCode JetHandler::setVariables(xAOD::Jet * inJet, xAOD::Jet * outJet, bool isSysVar)
{

   // set four momentum
   setP4( inJet , outJet );
   std::vector<float> jvf;
   inJet->getAttribute("JVF",jvf);
   //outJet->setAttribute("JVF",jvf);
   // for now just decorate the output jets
   if( jvf.size() > 0) {
     m_decorator.set(outJet,JetFloatProps::JVF,jvf[0]);
   } else  {
     m_decorator.set(outJet,JetFloatProps::JVF,0);
   }

   if(m_isMC) m_decorator.copy(inJet, outJet, JetIntProps::truthLabel); // in input xAOD
   m_decorator.copy(inJet, outJet, JetIntProps::isVetoJet);
   m_decorator.copy(inJet, outJet, JetIntProps::isSignalJet);
   m_decorator.copy(inJet, outJet, JetFloatProps::MV1);
   m_decorator.copy(inJet, outJet, JetFloatProps::SV1_IP3D);
   m_decorator.copy(inJet, outJet, JetFloatProps::MV2c00);
   m_decorator.copy(inJet, outJet, JetFloatProps::MV2c10);
   m_decorator.copy(inJet, outJet, JetFloatProps::MV2c20);
   m_decorator.copy(inJet, outJet, JetFloatProps::MVb);
   //   if (!isSysVar) {
   // temporarily attach passOR flag
   // TODO this should be used e.g. in checkPassSel instead
   //   m_decorator.copy(inJet, outJet, JetIntProps::passOR);
   // }
  
  return EL::StatusCode::SUCCESS;

 }


EL::StatusCode JetHandler::select() 
{

  // get number of jets (the same for nominal and syst variations)
  // TODO check for availability?
  unsigned int nJets = (*m_inContainer.begin()).second->size();

  // loop on electrons in container
  for (unsigned int jetIndex = 0; jetIndex < nJets; jetIndex++) {
    // loop over all containers / systematic variations
    // return value is ignored
    passAny(m_inContainer, jetIndex, &passVetoJet);
    passAny(m_inContainer, jetIndex, &passSignalJet);
  }
  return EL::StatusCode::SUCCESS;

}


EL::StatusCode JetHandler::fillOutputContainer() 
{

  EL::StatusCode res = EL::StatusCode::FAILURE;
  if(m_usedInOR) {
    res = fillOutputContainerCheck(&checkPassSelOR);
  }
  else {
    res = fillOutputContainerCheck(&checkPassSelNoOR);
  }
  return res;

}


EL::StatusCode JetHandler::clearEvent() {
 
  if (ObjectHandler::clearEvent() != EL::StatusCode::SUCCESS) {
    Error("EL::StatusCode JetHandler::clearEvent()", "Failed to clear event in object handler!");
    return EL::StatusCode::FAILURE;
  }
  return EL::StatusCode::SUCCESS;

}
