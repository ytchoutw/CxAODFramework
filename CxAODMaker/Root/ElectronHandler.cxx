#include <iostream>

// electron specific includes
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/ElectronAuxContainer.h"
#include "CxAODMaker/ElectronHandler.h"
#include "ElectronPhotonFourMomentumCorrection/EgammaCalibrationAndSmearingTool.h"
#include "ElectronPhotonSelectorTools/AsgElectronLikelihoodTool.h"
#include "ElectronPhotonSelectorTools/AsgElectronIsEMSelector.h"
#include "PathResolver/PathResolver.h"

ElectronDecorator ElectronHandler::m_decorator;


ElectronHandler::ElectronHandler(const std::string& name, ConfigStore & config, xAOD::TEvent * event,
                                 EventInfoHandler & eventInfoHandler) : 
  ObjectHandler(name, config, event, eventInfoHandler),
  m_EgammaCalibrationAndSmearingTool(0),
  m_checkVeryLooseLH(0),
  m_checkVeryTightLH(0),
  m_ElectronIsEMSelector(0)
{
}


ElectronHandler::~ElectronHandler() 
{

  //delete tools
  delete m_EgammaCalibrationAndSmearingTool;
  delete m_checkVeryLooseLH;
  delete m_checkVeryTightLH;
  delete m_ElectronIsEMSelector;

}


EL::StatusCode ElectronHandler::initializeTools() 
{

  //calibration tool
  //-----------------
  m_EgammaCalibrationAndSmearingTool = new CP::EgammaCalibrationAndSmearingTool("EgammaCalibrationAndSmearingTool");
  m_EgammaCalibrationAndSmearingTool->setProperty("ESModel", "es2012c");
  m_EgammaCalibrationAndSmearingTool->setProperty("ResolutionType", "SigmaEff90");

  if (!m_EgammaCalibrationAndSmearingTool->initialize().isSuccess()) {
    Error("ElectronHandler::ElectronHandler()", "Failed to initialize EgammaCalibrationAndSmearingTool!");
    return EL::StatusCode::FAILURE;
  } else {
    if (m_config.get<bool>("debug")) {
      m_EgammaCalibrationAndSmearingTool->msg().setLevel(MSG::DEBUG);
    }
  }

  //LH selector tools
  //-----------------
  m_checkVeryLooseLH = new AsgElectronLikelihoodTool("checkVeryLooseLH");
  m_checkVeryLooseLH->setProperty("primaryVertexContainer", "PrimaryVertices");
  m_checkVeryLooseLH->setProperty("OperatingPoint", static_cast<unsigned int> (LikeEnum::VeryLoose));
  m_checkVeryLooseLH->setProperty("inputPDFFileName", "ElectronPhotonSelectorTools/v1/ElectronLikelihoodPdfs.root");
  if (!m_checkVeryLooseLH->initialize().isSuccess()) {
    Error("ElectronHandler::ElectronHandler()", "Failed to initialize checkVeryLooseLH tool!");
    return EL::StatusCode::FAILURE;
  } else {
    if (m_config.get<bool>("debug")) {
      m_checkVeryLooseLH->msg().setLevel(MSG::DEBUG);
    }
  }
  m_checkVeryTightLH = new AsgElectronLikelihoodTool("checkVeryTightLH");
  m_checkVeryTightLH->setProperty("primaryVertexContainer", "PrimaryVertices");
  m_checkVeryTightLH->setProperty("OperatingPoint", static_cast<unsigned int> (LikeEnum::VeryTight));
  m_checkVeryTightLH->setProperty("inputPDFFileName", "ElectronPhotonSelectorTools/v1/ElectronLikelihoodPdfs.root");
  if (!m_checkVeryTightLH->initialize().isSuccess()) {
    Error("ElectronHandler::ElectronHandler()", "Failed to initialize checkVeryTightLH tool!");
    return EL::StatusCode::FAILURE;
  } else {
    if (m_config.get<bool>("debug")) {
      m_checkVeryTightLH->msg().setLevel(MSG::DEBUG);
    }
  }

  //isEM selector tool
  //-----------------
  m_ElectronIsEMSelector = new AsgElectronIsEMSelector("ElectronIsEMSelector");
  m_ElectronIsEMSelector->setProperty("ConfigFile", "ElectronPhotonSelectorTools/v1/ElectronIsEMLooseSelectorCutDefs.conf");
  m_ElectronIsEMSelector->setProperty("isEMMask", static_cast<unsigned int> (egammaPID::ElectronTightPP));
  m_ElectronIsEMSelector->setProperty("PIDName", static_cast<int> (egammaPID::IsEMTight));
  if (!m_ElectronIsEMSelector->initialize().isSuccess()) {
    Error("ElectronHandler::ElectronHandler()", "Failed to initialize ElectronIsEMSelector!");
    return EL::StatusCode::FAILURE;
  } else {
    if (m_config.get<bool>("debug")) {
      m_ElectronIsEMSelector->msg().setLevel(MSG::DEBUG);
    }
  }
  
  // register ISystematicsTools
  //---------------------------
  m_sysToolList.clear();
  m_sysToolList.push_back(m_EgammaCalibrationAndSmearingTool);

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode ElectronHandler::decorate(xAOD::Electron * electron) 
{

  //selection tools
  //---------------
  //retrieve decision from tools and decorate electron with it
  //perform actual selection later
  int isVeryLooseLH = static_cast<int>(m_checkVeryLooseLH->accept(electron));
  int isVeryTightLH = static_cast<int>(m_checkVeryTightLH->accept(electron));
  int isTightPP     = static_cast<int>(m_ElectronIsEMSelector->accept(electron));
  m_decorator.set(electron, ElecIntProps::isVeryLooseLH, isVeryLooseLH);
  m_decorator.set(electron, ElecIntProps::isVeryTightLH, isVeryTightLH);
  m_decorator.set(electron, ElecIntProps::isTightPP, isTightPP);
  
  return EL::StatusCode::SUCCESS;  

}


EL::StatusCode ElectronHandler::calibrateCopies(xAOD::ElectronContainer * particles, const CP::SystematicSet & sysSet) 
{

  //calibration tool
  //-----------------
  // tell tool to apply systematic variation
  if (m_EgammaCalibrationAndSmearingTool->applySystematicVariation(sysSet) != CP::SystematicCode::Ok) {
    Error("ElectronHandler::calibrateCopies()", "Cannot configure electron calibration tool for systematic %s", sysSet.name().c_str());
  }

  // get EventInfo
  const xAOD::EventInfo * eventInfo = m_eventInfoHandler.getEventInfo();

  //configure the tool for the standard DATA/MC use
  m_EgammaCalibrationAndSmearingTool->setDefaultConfiguration(eventInfo);

  for (xAOD::Electron * electron : *particles) {

    //calibration tool
    //-----------------
    //set seed for smearing
    m_EgammaCalibrationAndSmearingTool->setRandomSeed(m_eventInfoHandler.get_eventNumber() + 100 * electron->index());
    //this ensures that the DynAux container has the same number of entries as the original one
    //not necessary in case of electrons - keep it for consistency?
    //setP4( electron , electron );
    if (m_EgammaCalibrationAndSmearingTool->applyCorrection(*electron, eventInfo) == CP::CorrectionCode::Error) {
      Error("ElectronHandler::calibrateCopies()", "EgammaCalibrationAndSmearingTool reported CP::CorrectionCode::Error");
    }

    // decorate electron
    if ( decorate( electron ) != EL::StatusCode::SUCCESS ) return EL::StatusCode::FAILURE;
    
  }

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode ElectronHandler::select() 
{

  //get number of electrons (the same for nominal and syst variations)
  // TODO check for availability?
  unsigned int nElectrons = (*m_inContainer.begin()).second->size();

  // loop on electrons in container
  for (unsigned int eleIndex = 0; eleIndex < nElectrons; ++eleIndex) {
    // loop over all containers / systematic variations
    //return value is ignored
    passAny(m_inContainer, eleIndex, &passVHLooseElectron);
    passAny(m_inContainer, eleIndex, &passVHSignalElectron);
    passAny(m_inContainer, eleIndex, &passZHSignalElectron);
    passAny(m_inContainer, eleIndex, &passWHSignalElectron);
  }

  return EL::StatusCode::SUCCESS;

}


bool ElectronHandler::checkPassSelOR(xAOD::Electron * electron) 
{

  int res = 0;
  m_decorator.get(electron, ElecIntProps::passORGlob, res);
  return res;

}


bool ElectronHandler::checkPassSelNoOR(xAOD::Electron * electron) 
{

  int res = 0;
  m_decorator.get(electron, ElecIntProps::isVHLooseElectron, res);
  return res;

}


bool ElectronHandler::passVHLooseElectron(xAOD::Electron * electron) 
{

  bool passSel = true;

  //ToDo
  //steer certain cuts by config settings
  //cutflow
  //if (!(electron->author() == xAOD::EgammaParameters::AuthorElectron)) passSel = false; //not needed anymore since forward electrons are stored in a different container
  if (!(m_decorator.get(electron, ElecIntProps::isVeryLooseLH))) passSel = false;
  if (!(fabs(electron->eta()) < 2.47)) passSel = false;
  if (!(electron->pt() > 7000.)) passSel = false;
  if (!(electron->isolationValue(xAOD::Iso::ptcone20) / electron->pt() < 0.1)) passSel = false;
  if (!(electron->isGoodOQ(xAOD::EgammaParameters::BADCLUSELECTRON))) passSel = false;

  m_decorator.set(electron, ElecIntProps::isVHLooseElectron, passSel);

  return passSel;

}

bool ElectronHandler::passVHSignalElectron(xAOD::Electron * electron) 
{

  bool passSel = true;
  //ToDo
  //steer certain cuts by config settings
  //cutflow

  if (!m_decorator.get(electron, ElecIntProps::isVHLooseElectron)) passSel = false;
  if (!(electron->pt() > 25000.)) passSel = false;
 
  m_decorator.set(electron, ElecIntProps::isVHSignalElectron, passSel);

  return passSel;

}

bool ElectronHandler::passZHSignalElectron(xAOD::Electron * electron) 
{

  bool passSel = true;
  //ToDo
  //steer certain cuts by config settings
  //cutflow

  if (!m_decorator.get(electron, ElecIntProps::isVHSignalElectron)) passSel = false;
 
  m_decorator.set(electron, ElecIntProps::isZHSignalElectron, passSel);

  return passSel;

}

bool ElectronHandler::passWHSignalElectron(xAOD::Electron * electron) 
{
  bool passSel = true;
  //ToDo
  //steer certain cuts by config settings
  //cutflow

  //require loose electron cuts to be passed - does this make sense?
  //isn't it possible that the VeryLooseLH isn't passed but VeryTight is?
  if (!m_decorator.get(electron, ElecIntProps::isVHSignalElectron)) passSel = false;

  if (!(m_decorator.get(electron, ElecIntProps::isVeryTightLH))) passSel = false;
  if (!(electron->isolationValue(xAOD::Iso::ptcone20) / electron->pt() < 0.04)) passSel = false;
  //if (!(electron->isolationValue(xAOD::Iso::topoetcone30_corrected) / electron->pt() < 0.04)) passWHSel = false;
  if (!(electron->isolationValue(xAOD::Iso::topoetcone30) / electron->pt() < 0.04)) passSel = false;

  m_decorator.set(electron, ElecIntProps::isWHSignalElectron, passSel);

  return passSel;

}


EL::StatusCode ElectronHandler::setVariables(xAOD::Electron * inElectron, xAOD::Electron * outElectron, bool isSysVar) 
{
  
  //TODO clean up
  //TODO add check if variables changed due to calibrations?

  // set four momentum
  setP4( inElectron , outElectron );

  //set isolation
  outElectron->setIsolationValue(inElectron->isolationValue(xAOD::Iso::ptcone20),xAOD::Iso::ptcone20);
  //outElectron->setIsolationValue(inElectron->isolationValue(xAOD::Iso::topoetcone30_corrected),xAOD::Iso::topoetcone30_corrected);
  outElectron->setIsolationValue(inElectron->isolationValue(xAOD::Iso::topoetcone30),xAOD::Iso::topoetcone30);

  // set something without having a pre-defined method
  m_decorator.copy(inElectron, outElectron, ElecIntProps::isVeryTightLH);
  m_decorator.copy(inElectron, outElectron, ElecIntProps::isVHLooseElectron);
  m_decorator.copy(inElectron, outElectron, ElecIntProps::isZHSignalElectron);
  m_decorator.copy(inElectron, outElectron, ElecIntProps::isWHSignalElectron);
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


EL::StatusCode ElectronHandler::fillOutputContainer() 
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


EL::StatusCode ElectronHandler::clearEvent() 
{
  
  if (ObjectHandler::clearEvent() != EL::StatusCode::SUCCESS) {
    Error("EL::StatusCode ElectronHandler::clearEvent()", "Failed to clear event in object handler!");
    return EL::StatusCode::FAILURE;
  }
  return EL::StatusCode::SUCCESS;

}
