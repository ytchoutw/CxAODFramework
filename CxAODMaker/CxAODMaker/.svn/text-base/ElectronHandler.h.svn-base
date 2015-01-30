// Dear emacs, this is -*-c++-*-
#ifndef CxAODMaker_ElectronHandler_H
#define CxAODMaker_ElectronHandler_H

#include "CxAODMaker/ObjectHandler.h"
#include "CxAODTools/ElectronDecorator.h"

namespace xAOD {
#ifndef XAODEGAMMA_ELECTRONCONTAINER_H 
  class ElectronContainer;
#endif
#ifndef XAODEGAMMA_ELECTRON_H 
  class Electron;
#endif
}

namespace CP {
  class EgammaCalibrationAndSmearingTool;
}
class AsgElectronLikelihoodTool;
class AsgElectronIsEMSelector;


class ElectronHandler : public ObjectHandler<xAOD::Electron, xAOD::ElectronContainer> {

public:

  ElectronHandler(const std::string& name, ConfigStore & config, xAOD::TEvent * event,
                  EventInfoHandler & eventInfoHandler);

  ~ElectronHandler();

  EL::StatusCode initializeTools();
  EL::StatusCode select();
  EL::StatusCode fillOutputContainer();
  EL::StatusCode clearEvent();

  void setP4(const xAOD::Electron * in, xAOD::Electron * out) { out->setP4(in->pt(), in->eta(), in->phi(), in->m()); }


private:

  // decorator defining non-standard object variables
  static ElectronDecorator m_decorator;

  // calibration tools
  CP::EgammaCalibrationAndSmearingTool * m_EgammaCalibrationAndSmearingTool;
  AsgElectronLikelihoodTool            * m_checkVeryLooseLH;
  AsgElectronLikelihoodTool            * m_checkVeryTightLH;
  AsgElectronIsEMSelector              * m_ElectronIsEMSelector;

  // selection functions for single objects
  static bool passVHLooseElectron(xAOD::Electron * electron);
  static bool passVHSignalElectron(xAOD::Electron * electron);//common cuts for ZH and WH
  static bool passZHSignalElectron(xAOD::Electron * electron);
  static bool passWHSignalElectron(xAOD::Electron * electron);
  static bool checkPassSelOR(xAOD::Electron * part);
  static bool checkPassSelNoOR(xAOD::Electron * part);

  EL::StatusCode decorate(xAOD::Electron * electron);

  EL::StatusCode calibrateCopies(xAOD::ElectronContainer * particles, const CP::SystematicSet & sysSet);

  virtual EL::StatusCode setVariables(xAOD::Electron * inPart, xAOD::Electron * outPart, bool isSys);

};

#endif
