#include <iostream>

//muon specific includes
#include "xAODMuon/MuonContainer.h"
#include "xAODMuon/MuonAuxContainer.h"
#include "CxAODMaker/MuonHandler.h"
#include "MuonMomentumCorrections/MuonCalibrationAndSmearingTool.h"
#include "MuonSelectorTools/MuonSelectionTool.h"
#include "MuonEfficiencyCorrections/MuonEfficiencyScaleFactors.h"

// declare static members
MuonDecorator MuonHandler::m_decorator;

MuonHandler::MuonHandler(const std::string& name, ConfigStore & config, xAOD::TEvent *event,
                         EventInfoHandler & eventInfoHandler) :
  ObjectHandler(name, config, event, eventInfoHandler),
  m_muonCalibrationAndSmearingTool(0),
  m_muonSelectionTool(0)
{
}

MuonHandler::~MuonHandler() {

  //delete tool:
  delete m_muonCalibrationAndSmearingTool;
  delete m_muonSelectionTool;
  
}


EL::StatusCode MuonHandler::initializeTools() 
{

  // initialize the muon calibration and smearing tool
  //---------------------------------------------------
  m_muonCalibrationAndSmearingTool = new CP::MuonCalibrationAndSmearingTool("MuonCalibrationTool");
  if (!m_muonCalibrationAndSmearingTool->initialize().isSuccess()) {
    Error("MuonHandler::MuonHandler()", "Failed to initialize MonCalibrationAndSmearingTool. Exiting.");
    return EL::StatusCode::FAILURE;
  } else {
    if (m_config.get<bool>("debug")) {
      m_muonCalibrationAndSmearingTool->msg().setLevel(MSG::DEBUG);
    }
  }

  // initialize the muon selector tool
  //---------------------------------------------------
  m_muonSelectionTool = new CP::MuonSelectionTool("MuonSelectionTool");
  m_muonSelectionTool->setProperty("MaxEta", 2.4);
  m_muonSelectionTool->setProperty("MuQuality", 1); // 0 tight, 1 medium, 2 loose, 3 very loose
  if (!m_muonSelectionTool->initialize().isSuccess()) {
    Error("MuonHandler::MuonHandler()", "Failed to initialize MuonSelectionTool. Exiting.");
    return EL::StatusCode::FAILURE;
  } else {
    if (m_config.get<bool>("debug")) {
      m_muonSelectionTool->msg().setLevel(MSG::DEBUG);
    }
  }
  
  // initialize the muon efficiency tool
  //---------------------------------------------------
  m_muonEfficiencyScaleFactors = new CP::MuonEfficiencyScaleFactors("MuonEfficiencyTool");
  m_muonEfficiencyScaleFactors->setProperty("WorkingPoint", "CBandST");
  m_muonEfficiencyScaleFactors->setProperty("DataPeriod", "2012");
  if (!m_muonEfficiencyScaleFactors->initialize().isSuccess()) {
    Error("MuonHandler::MuonHandler()", "Failed to initialize MuonEfficiencyTool. Exiting.");
    return EL::StatusCode::FAILURE;
  }
  
  // register ISystematicsTools
  //---------------------------
  m_sysToolList.clear();
  m_sysToolList.push_back(m_muonCalibrationAndSmearingTool);
  m_sysToolList.push_back(m_muonEfficiencyScaleFactors);

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode MuonHandler::decorate(xAOD::Muon * muon) 
{

  //compute some stuff, e.g. d0,z0, decorate muon object, but apply cuts later (in passVHLooseMuon,...)!
  const xAOD::TrackParticle * trackPart = muon->trackParticle(xAOD::Muon::TrackParticleType::InnerDetectorTrackParticle);
  if (!trackPart) {
    if (muon->muonType() != xAOD::Muon::MuonStandAlone) {
      Warning("MuonHandler::calibrateCopies","Couldn't get inner detector track particle... trying to get primary one");
    }
    trackPart = muon->trackParticle(xAOD::Muon::TrackParticleType::Primary);
  }
  if (!trackPart) {
    Error("MuonHandler::calibrateCopies","Failed to get the TrackParticle to retrieve d0/z0...");
    return EL::StatusCode::FAILURE; //do we want a failure here?
  }

  float d0 = trackPart->d0(); 
  
  float pvZ = m_eventInfoHandler.get_ZPV();
  float z0 = trackPart->z0()+ trackPart->vz() - pvZ;

  if (!m_decorator.exists(muon, MuonIntProps::passedIDCuts)) {
    bool passedIDCuts = m_muonSelectionTool->passedIDCuts(*muon);
    bool accepted = m_muonSelectionTool->accept(*muon);
    m_decorator.set(muon, MuonIntProps::passedIDCuts, passedIDCuts && accepted);
  }
  
  //decorate muon 
  m_decorator.set(muon, MuonFloatProps::d0,d0);
  m_decorator.set(muon, MuonFloatProps::z0,z0);
  
  int isMC = m_eventInfoHandler.get_isMC();
  if (isMC) {
    // TODO we would like to have this for Nominal only
    float effSF = -1;
    if (m_muonEfficiencyScaleFactors->getEfficiencyScaleFactor(*muon, effSF) == CP::CorrectionCode::Error) {
      Error("MuonHandler::decorate()", "MuonEfficiencyScaleFactors returned CP::CorrectionCode::Error");
      return EL::StatusCode::FAILURE;
    }
    m_decorator.set(muon, MuonFloatProps::effSF, effSF);
  }

  return EL::StatusCode::SUCCESS;
  
}


EL::StatusCode MuonHandler::calibrateCopies(xAOD::MuonContainer * particles, const CP::SystematicSet & sysSet) 
{

  // get isMC
  int isMC = m_eventInfoHandler.get_isMC();

  // tell tool to apply systematic variation
  if ( m_muonCalibrationAndSmearingTool->applySystematicVariation(sysSet) != CP::SystematicCode::Ok ) {
    Error("MuonHandler::calibrateCopies()", "Cannot configure muon calibration tool for systematic %s", sysSet.name().c_str());
  }

  // loop over the particles in the container
  for (xAOD::Muon * muon : *particles) {
    
    //calibration
    //------------
    //this ensures that the DynAux container has the same number of entries as the original one
    //since the calibration is not valid for all inMuons...
    setP4( muon , muon );
    
    bool passedIDCuts = m_muonSelectionTool->passedIDCuts(*muon);
    bool accepted = m_muonSelectionTool->accept( *muon );
    m_decorator.set(muon, MuonIntProps::passedIDCuts, passedIDCuts && accepted);

    if ( isMC && accepted ) {
      CP::CorrectionCode status = m_muonCalibrationAndSmearingTool->applyCorrection(*muon);
      if ( status == CP::CorrectionCode::Error ) {
        Warning("MuonHandler::calibrateCopies()", "MuonCalibrationAndSmearingTool returned CP::CorrectionCode::Error");
      }
      else if ( status == CP::CorrectionCode::OutOfValidityRange ) {
        // This warning doesn't appear (i.e. is fixed) in MuonMomentumCorrections-01-00-13 
	Warning("MuonHandler::calibrateCopies()", "MuonCalibrationAndSmearingTool returned CP::CorrectionCode::OutOfValidityRange");
      }
    }

    // decorate muon
    if ( decorate( muon ) != EL::StatusCode::SUCCESS ) return EL::StatusCode::FAILURE;
    
  }

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode MuonHandler::select() 
{
  
  //get number of muons (the same for nominal and syst variations)
  // TODO check for availability?
  unsigned int nMuons = (*m_inContainer.begin()).second->size();

  // loop on muons in container
  for (unsigned int muIndex = 0; muIndex < nMuons; ++muIndex) {
    // use passAny function to loop over all containers
    // return value is ignored
    passAny(m_inContainer, muIndex, &passVHLooseMuon);
    passAny(m_inContainer, muIndex, &passVHSignalMuon);
    passAny(m_inContainer, muIndex, &passZHSignalMuon);
    passAny(m_inContainer, muIndex, &passWHSignalMuon);

  }

  return EL::StatusCode::SUCCESS;

}


bool MuonHandler::checkPassSelOR(xAOD::Muon * part) 
{

  int res = 0;
  m_decorator.get(part, MuonIntProps::passORGlob, res);
  return res;

}


bool MuonHandler::checkPassSelNoOR(xAOD::Muon * part) 
{

  int res = 0;
  m_decorator.get(part, MuonIntProps::isVHLooseMuon, res);
  return res;

}


bool MuonHandler::passVHLooseMuon(xAOD::Muon * muon) 
{

  bool passSel = true;

  //apply selection for combined or segment tagged muons for now
  if (!((muon->muonType() == xAOD::Muon::Combined) || (muon->muonType() == xAOD::Muon::SegmentTagged))) passSel = false;
  if (!(m_decorator.get(muon, MuonIntProps::passedIDCuts))) passSel = false;
  if (!(fabs(m_decorator.get(muon, MuonFloatProps::d0)) < 0.1)) passSel = false;
  if (!(fabs(m_decorator.get(muon, MuonFloatProps::z0)) < 10)) passSel = false;
  if (!(fabs(muon->eta()) < 2.7)) passSel = false;
  if (!(muon->pt() > 7000.)) passSel = false;
  // Do not use quality directly. It always returns Loose==2(Tight==0) in 13(8)TeV. Quality selection(medium) has already been made using the muon selection tool
  //if (!(muon->quality() == xAOD::Muon::Tight)) passSel = false;
  // Do not use author directly.  For 13TeV it will kill MuGirl(Combined) and MuTagIMO(SegmentTagged).
  // For 8TeV it makes no difference as only combined available is MuidCo and all MuTagIMO(SegmentTagged)muons fail passedIDCuts
  //if (!(muon->author() == xAOD::Muon::MuidCo)) passSel = false;
  m_decorator.set(muon, MuonIntProps::isVHLooseMuon, passSel);

  return passSel;

}

bool MuonHandler::passVHSignalMuon(xAOD::Muon* muon){
  
  bool passSel = true;
 
  //check loose selection is passed
  if(!(m_decorator.get(muon, MuonIntProps::isVHLooseMuon))) passSel = false;
  //common cuts
  if (!((muon->muonType() == xAOD::Muon::Combined) || (muon->muonType() == xAOD::Muon::SegmentTagged))) passSel = false;
  if (!(fabs(muon->eta()) < 2.5)) passSel = false;
  if (!(muon->pt() > 25000.)) passSel = false;

  m_decorator.set(muon, MuonIntProps::isVHSignalMuon, passSel);
  
  return passSel;
}

bool MuonHandler::passZHSignalMuon(xAOD::Muon* muon){
  
  bool passSel = true;
 
  //check VH selection is passed
  if(!(m_decorator.get(muon, MuonIntProps::isVHSignalMuon))) passSel = false;

  m_decorator.set(muon, MuonIntProps::isZHSignalMuon, passSel);
  
  return passSel;
}

bool MuonHandler::passWHSignalMuon(xAOD::Muon* muon){
  
  bool passSel = true;
 
  //check VH selection is passed
  if(!(m_decorator.get(muon, MuonIntProps::isVHSignalMuon))) passSel = false;

  float trackIso = -999.;
  float caloIso = -999.;
  muon->isolation(trackIso,xAOD::Iso::ptcone20);
  muon->isolation(caloIso,xAOD::Iso::etcone30);
  if (!((trackIso / muon->pt()) < 0.04)) passSel = false;
  if (!((caloIso / muon->pt()) < 0.04)) passSel = false;

  m_decorator.set(muon, MuonIntProps::isWHSignalMuon, passSel);
  
  return passSel;
}

EL::StatusCode MuonHandler::setVariables(xAOD::Muon * inMuon, xAOD::Muon * outMuon, bool isSysVar) 
{

  //TODO clean up
  //TODO add check if variables changed due to calibrations?

  // set four momentum
  setP4( inMuon , outMuon );

  float trackIso = -999.;
  float caloIso = -999.;
  inMuon->isolation(trackIso, xAOD::Iso::ptcone20);
  inMuon->isolation(caloIso, xAOD::Iso::etcone30);
  outMuon->setIsolation(trackIso, xAOD::Iso::ptcone20);
  outMuon->setIsolation(caloIso, xAOD::Iso::etcone30); //corrected? not available (yet)!

  // set something without having a pre-defined method
  m_decorator.copy(inMuon, outMuon, MuonIntProps::isVHLooseMuon);
  m_decorator.copy(inMuon, outMuon, MuonIntProps::isZHSignalMuon);
  m_decorator.copy(inMuon, outMuon, MuonIntProps::isWHSignalMuon);

  // not dependent on systematic variations
  if (!isSysVar) {
    //set muon type
    xAOD::Muon::MuonType muonType = inMuon->muonType();
    outMuon->setMuonType(muonType);
    // set something without having a pre-defined method
//    m_decorator.copy(inMuon, outMuon, MuonFloatProps::z0);
//    m_decorator.copy(inMuon, outMuon, MuonFloatProps::d0);
  }

  //  if (!isSysVar) {
  //    m_decorator.copy(inMuon, outMuon, MuonIntProps::passSel);
  //  } else {
  //    //just proof of principle: it is possible to overwrite a quantity only if it changes wrt "Nominal"
  //    //BUT: of course it got to exist in every event (otherwise it won't be written)
  //    if (m_decorator.get(outMuon, MuonIntProps::passSel) != m_decorator.get(inMuon, MuonIntProps::passSel)) {
  //      m_decorator.copy(inMuon, outMuon, MuonIntProps::passSel);
  //    }
  //  }
  
  if (!isSysVar) {
    // temporarily attach passOR flag
    // TODO this should be used e.g. in checkPassSel instead
    //    m_decorator.copy(inMuon, outMuon, MuonIntProps::passOR);
    
    int isMC = m_eventInfoHandler.get_isMC();
    if (isMC) {
      // TODO is should be written event-wise
      m_decorator.copy(inMuon, outMuon, MuonFloatProps::effSF);
    }

  }

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode MuonHandler::fillOutputContainer() 
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


EL::StatusCode MuonHandler::clearEvent() 
{
  if (ObjectHandler::clearEvent() != EL::StatusCode::SUCCESS) {
    Error("EL::StatusCode MuonHandler::clearEvent()", "Failed to clear event in object handler!");
    return EL::StatusCode::FAILURE;
  }
  return EL::StatusCode::SUCCESS;

}
