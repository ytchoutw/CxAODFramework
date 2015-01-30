// Dear emacs, this is -*-c++-*-
#ifndef CxAODMaker_PhotonHandler_H
#define CxAODMaker_PhotonHandler_H

#include "CxAODMaker/ObjectHandler.h"
#include "CxAODTools/PhotonDecorator.h"

namespace xAOD {
#ifndef XAODEGAMMA_PHOTONCONTAINER_H
  class PhotonContainer;
#endif
#ifndef XAODEGAMMA_PHOTON_H
  class Photon;
#endif
}

namespace CP {
  class EgammaCalibrationAndSmearingTool;
}

// todo : real name for tools
class AsgPhotonIsEMSelector;

class PhotonHandler : public ObjectHandler<xAOD::Photon, xAOD::PhotonContainer> {

public:
  
  PhotonHandler(const std::string& name, ConfigStore & config, xAOD::TEvent * event,
                EventInfoHandler & eventInfoHandler);
  
  ~PhotonHandler();
  
  EL::StatusCode initializeTools();
  EL::StatusCode select();
  EL::StatusCode fillOutputContainer();
  EL::StatusCode clearEvent();
  
  void setP4(const xAOD::Photon * in, xAOD::Photon * out) {out->setP4(in->pt(), in->eta(), in->phi(), in->m()); }
  
  
private:
  
  //decorator defining non-standard object variables
  static PhotonDecorator m_decorator;

  // calibration tools
  CP::EgammaCalibrationAndSmearingTool * m_EgammaCalibrationAndSmearingTool;
  // todo : implement real tools
  AsgPhotonIsEMSelector                * m_PhotonIsEMSelector;

  //select functions for single objects
  static bool passVBFALoosePhoton(xAOD::Photon * photon);
  static bool passVBFASignalPhoton(xAOD::Photon * photon);
  static bool checkPassSelOR(xAOD::Photon * part);
  static bool checkPassSelNoOR(xAOD::Photon * part);

  EL::StatusCode decorate(xAOD::Photon * photon);
  
  EL::StatusCode calibrateCopies(xAOD::PhotonContainer * particles, const CP::SystematicSet & sysSet);

  virtual EL::StatusCode setVariables(xAOD::Photon * inPart, xAOD::Photon * outPart, bool isSys);


};//class PhotonHandler

#endif
