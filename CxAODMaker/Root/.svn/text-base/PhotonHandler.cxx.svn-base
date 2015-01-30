#include <iostream>

// photon specific includes
#include "xAODEgamma/PhotonContainer.h"
#include "xAODEgamma/PhotonAuxContainer.h"
#include "CxAODMaker/PhotonHandler.h"

#include "ElectronPhotonFourMomentumCorrection/EgammaCalibrationAndSmearingTool.h"
#include "ElectronPhotonSelectorTools/AsgPhotonIsEMSelector.h"
#include "PathResolver/PathResolver.h"

PhotonDecorator PhotonHandler::m_decorator;

PhotonHandler::PhotonHandler(const std::string& name, ConfigStore & config, xAOD::TEvent * event,
                             EventInfoHandler & eventInfoHandler) :
  ObjectHandler(name, config, event, eventInfoHandler),
  m_EgammaCalibrationAndSmearingTool(0),
  m_PhotonIsEMSelector(0)
{
}


PhotonHandler::~PhotonHandler()
{

  //delete tools
  delete m_EgammaCalibrationAndSmearingTool;
  delete m_PhotonIsEMSelector;

}


EL::StatusCode PhotonHandler::initializeTools()
{

  //calibration tool
  //----------------
  // todo : check if initialization is the same as for electrons
  m_EgammaCalibrationAndSmearingTool = new CP::EgammaCalibrationAndSmearingTool("EgammaCalibrationAndSmearingTool");
  m_EgammaCalibrationAndSmearingTool->setProperty("ESModel", "es2012c");
  m_EgammaCalibrationAndSmearingTool->setProperty("ResolutionType", "SigmaEff90");

  if (!m_EgammaCalibrationAndSmearingTool->initialize().isSuccess()) {
    Error("PhotonHandler::PhotonHandler()", "Failed to initialize EgammaCalibrationAndSmearingTool!");
    return EL::StatusCode::FAILURE;
  } else {
    if (m_config.get<bool>("debug")) {
      m_EgammaCalibrationAndSmearingTool->msg().setLevel(MSG::DEBUG);
    }
  }


  //isEM selector tool
  //------------------
  // todo : double check this
  m_PhotonIsEMSelector = new AsgPhotonIsEMSelector("PhotonIsEMSelector");

  //PhotonIsEMSelector has no "SetProperty" :(((
  //m_PhotonIsEMSelector->setProperty("ConfigFile", "ElectronPhotonSelectorTools/v1/ElectronIsEMLooseSelectorCutDefs.conf");
  //No config file for version of tool in current release
  //m_PhotonIsEMSelector->setProperty("ConfigFile", "/afs/cern.ch/work/p/prose/public/CxAODFramework/devBranchProse/PhotonIsEMSelectorCutDefs.conf");
  m_PhotonIsEMSelector->setProperty("isEMMask", static_cast<unsigned int> (egammaPID::PhotonTightIso)); // needs verification; maybe just PhotonTight
  m_PhotonIsEMSelector->setProperty("PIDName", static_cast<int> (egammaPID::IsEMTight));
  if (!m_PhotonIsEMSelector->initialize().isSuccess()) {
    Error("PhotonHandler::PhotonHandler()", "Failed to initialize PhotonIsEMSelector!");
    return EL::StatusCode::FAILURE;
  } else {
    if (m_config.get<bool>("debug")) {
      m_PhotonIsEMSelector->msg().setLevel(MSG::DEBUG);
    }
  }



  //register ISystematicsTools
  //--------------------------
  m_sysToolList.clear();
  m_sysToolList.push_back(m_EgammaCalibrationAndSmearingTool);

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode PhotonHandler::decorate(xAOD::Photon * photon)
{
  //selection tools
  //---------------
  //retrieve decision from tools and decorate photon with it
  //perform actual selection later
  
  
  // todo : implement the photon tools here
  //int isTightIso = static_cast<int>(m_PhotonIsEMSelector->accept(photon));
  int isTightIso = 0.; //dummy value. tool broken in current release
  m_decorator.set(photon, PhotIntProps::isTightIso, isTightIso);

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode PhotonHandler::calibrateCopies(xAOD::PhotonContainer * particles, const CP::SystematicSet & sysSet)
{
  
  //calibration tool
  //----------------
  //tell tool to apply systematic variation
  if (m_EgammaCalibrationAndSmearingTool->applySystematicVariation(sysSet) != CP::SystematicCode::Ok) {
    Error("PhotonHandler::calibrateCopies()", "Cannot configure photon calibration tool for systematic %s", sysSet.name().c_str());
  }

  //get EventInfo
  const xAOD::EventInfo * eventInfo = m_eventInfoHandler.getEventInfo();

  //configure tool for the standard DATA/MC use
  m_EgammaCalibrationAndSmearingTool->setDefaultConfiguration(eventInfo);

  for(xAOD::Photon * photon : *particles) {

    //calibration tool
    //----------------
    //set seed for smearing
    m_EgammaCalibrationAndSmearingTool->setRandomSeed(m_eventInfoHandler.get_eventNumber() + 100 * photon->index());
    //this ensures that the DynAux container has the same number of entries as the original one
    //not necessary in the case of photons - keep it for consistency?
    //setP4( electron, electron );
    if (m_EgammaCalibrationAndSmearingTool->applyCorrection(*photon, eventInfo) == CP::CorrectionCode::Error) {
      Error("PhotonHandler::calibrateCopies()", "EgammaCalibrationAndSmearingTool reported CP::CorrectionCode::Error");
    }

    // decorate photon
    if ( decorate( photon ) != EL::StatusCode::SUCCESS ) return EL::StatusCode::FAILURE;

  }
  
  return EL::StatusCode::SUCCESS;

}


EL::StatusCode PhotonHandler::select()
{

  //get number of photons (the same for nominal and syst variations)
  // TODO check for availability?
  unsigned int nPhotons = (*m_inContainer.begin()).second->size();

  //loop on photons in container
  for (unsigned int iPh = 0; iPh < nPhotons; ++iPh) {
    //loop of all containers /systematic variations
    //return value is ignored
    passAny(m_inContainer, iPh, &passVBFALoosePhoton);
    passAny(m_inContainer, iPh, &passVBFASignalPhoton);
  }

  return EL::StatusCode::SUCCESS;

}


bool PhotonHandler::checkPassSelOR(xAOD::Photon * photon)
{

  int res = 0;
  m_decorator.get(photon, PhotIntProps::passORGlob, res);
  return res;

}


bool PhotonHandler::checkPassSelNoOR(xAOD::Photon * photon)
{

  int res = 0;
  m_decorator.get(photon, PhotIntProps::isVBFALoosePhoton, res);
  return res;

}


bool PhotonHandler::passVBFALoosePhoton(xAOD::Photon * photon)
{

  bool passSel = true;

  if(!(fabs(photon->eta()) < 2.47 )) passSel = false;
  //if(!(photon->pt() > 15000.)) passSel = false;
  if(!(photon->pt() > 5000.)) passSel = false; //dummy value for testing
  //ToDo
  //steer certain cuts by config settings
  //cutflow


  // todo : implement better photon selection
  /*

  DO SELECTION HERE
  if (! (cuts) ) passSel = false;

  */

  m_decorator.set(photon, PhotIntProps::isVBFALoosePhoton, passSel);

  return passSel;

}


bool PhotonHandler::passVBFASignalPhoton(xAOD::Photon * photon)
{

  bool passSel = true;
  //ToDo
  //stree certain cuts by config settings
  //cutflow

  if (!m_decorator.get(photon, PhotIntProps::isVBFALoosePhoton)) passSel = false;
  
  if(!(photon->pt() > 10000.)) passSel = false; // dummy value for testing
  // todo : implement photon selection here
  /*

    SIGNAL CUTS HERE

  */

  m_decorator.set(photon, PhotIntProps::isVBFASignalPhoton, passSel);

  return passSel;

}


EL::StatusCode PhotonHandler::setVariables(xAOD::Photon * inPhoton, xAOD::Photon * outPhoton, bool isSysVar)
{

  //TODO clean up
  //TODO add check if variables changed due to calibrations?

  //set four momentum
  setP4( inPhoton, outPhoton );

  //set isolation
  // todo : check if these are the same for electrons/photons
  //outPhoton->SetIsolationValue(inPhoton->isolationValue(xAOD::Iso::ptcone20),xAOD::Iso::ptcone20);
  // todo : check if these are the same for electrons/photons
  //outPhoton->SetIsolationValue(inPhoton->isolationValue(xAOD::Iso::topoetcone30_corrected),xAOD::Iso::topoetcone30_corrected);
  //outPhoton->setIsolationValue(inPhoton->isolationValue(xAOD::Iso::topoetcone30),xAOD::Iso<topoetcone30);

  // set something without having a pre-defined method
  m_decorator.copy(inPhoton, outPhoton, PhotIntProps::isTightIso);
  m_decorator.copy(inPhoton, outPhoton, PhotIntProps::isVBFALoosePhoton);
  m_decorator.copy(inPhoton, outPhoton, PhotIntProps::isVBFASignalPhoton);


  // todo : figure out what this stuff was for!!!!!!!!!
  //
  //if (!isSysVar) {
  //m_decorator.copy(inElectron, outElectron, ElecIntProps::passSel);
  //} else {
  ////just proof of principle: it is possible to overwrite a quantity only if it changes wrt "Nominal"
  ////BUT: of course it got to exist in every event (otherwise it won't be written)
  //if (m_decorator.get(outElectron, ElecIntProps::passSel) != m_decorator.get(inElectron, ElecIntProps::passSel)) {
  //m_decorator.copy(inElectron, outElectron, ElecIntProps::passSel);
  //}
  //}

  //if (!isSysVar) {
  // temporarily attach passOR flag
  // TODO this should be used e.g. in checkPassSel instead
  // m_decorator.copy(inElectron, outElectron, ElecIntProps::passOR);
  // }

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode PhotonHandler::fillOutputContainer() 
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


EL::StatusCode PhotonHandler::clearEvent()
{
  
  if(ObjectHandler::clearEvent() != EL::StatusCode::SUCCESS) {
    Error("EL::StatusCode PhotonHandler::clearEvent()", "Failed to clear event in object handler!");
    return EL::StatusCode::FAILURE;
  }
  return EL::StatusCode::SUCCESS;

}
