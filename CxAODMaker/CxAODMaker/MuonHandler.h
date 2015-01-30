// Dear emacs, this is -*-c++-*-

#ifndef CxAODMaker_MuonHandler_H
#define CxAODMaker_MuonHandler_H

#include "CxAODMaker/ObjectHandler.h"
#include "CxAODTools/MuonDecorator.h"

namespace xAOD {
#ifndef XAODMUON_MUONCONTAINER_H 
  class MuonContainer;
#endif
#ifndef XAODMUON_MUON_H 
  class Muon;
#endif
}

namespace CP {
  class MuonCalibrationAndSmearingTool;
  class MuonSelectionTool;
  class MuonEfficiencyScaleFactors;
}

class MuonHandler : public ObjectHandler<xAOD::Muon,xAOD::MuonContainer> {

public:

  MuonHandler(const std::string& name, ConfigStore & config, xAOD::TEvent * event,
              EventInfoHandler & eventInfoHandler);
  
  ~MuonHandler();
  
  EL::StatusCode initializeTools();
  EL::StatusCode select();
  EL::StatusCode fillOutputContainer();
  EL::StatusCode clearEvent();

  void setP4(const xAOD::Muon * in, xAOD::Muon * out) { out->setP4(in->pt(), in->eta(), in->phi()); }


private:

  // decorator defining non-standard object variables
  static MuonDecorator m_decorator;
  
  // calibration tools
  CP::MuonCalibrationAndSmearingTool * m_muonCalibrationAndSmearingTool;
  CP::MuonSelectionTool  *m_muonSelectionTool;
  CP::MuonEfficiencyScaleFactors * m_muonEfficiencyScaleFactors;

  // selection functions for single objects
  static bool passVHLooseMuon(xAOD::Muon * part);
  static bool passVHSignalMuon(xAOD::Muon * part);//common cuts for ZH and WH
  static bool passZHSignalMuon(xAOD::Muon * part);
  static bool passWHSignalMuon(xAOD::Muon * part);
  static bool checkPassSelOR(xAOD::Muon * part);
  static bool checkPassSelNoOR(xAOD::Muon * part);

  EL::StatusCode decorate(xAOD::Muon * muon); 
  
  EL::StatusCode calibrateCopies(xAOD::MuonContainer * particles, const CP::SystematicSet & sysSet);

  /** @brief Sets certain variables for the outMuon.
    * @param inMuon Muon from m_inContainer, from which values are read.
    * @param outMuon Muon from m_outContainer for which values are set.
    * @param isSysVar Bool deciding if container holding outMuon is a shallow copy.
    *
    *Called in function copyContainer that is implemented in the ObjectHandler.
    *In case isSysVar is true, variation dependent object variables are overwritten.
   */
  virtual EL::StatusCode setVariables(xAOD::Muon * inMuon, xAOD::Muon * outMuon, bool isSysVar);

};

#endif

