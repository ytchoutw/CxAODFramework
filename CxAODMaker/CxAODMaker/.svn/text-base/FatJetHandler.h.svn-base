// Dear emacs, this is -*-c++-*-
#ifndef CxAODMaker_FatJetHandler_H
#define CxAODMaker_FatJetHandler_H

#include "CxAODMaker/ObjectHandler.h"
#include "CxAODTools/FatJetDecorator.h"

namespace xAOD {
#ifndef XAODJET_JETCONTAINER_H 
  class JetContainer;
#endif
#ifndef XAODJET_JET_H 
  class Jet;
#endif
}


class FatJetHandler : public ObjectHandler<xAOD::Jet,xAOD::JetContainer> {

public:

  FatJetHandler(const std::string& name, ConfigStore & config, xAOD::TEvent * event,
                EventInfoHandler & eventInfoHandler);

  ~FatJetHandler();

  EL::StatusCode initializeTools();
  EL::StatusCode select();
  EL::StatusCode fillOutputContainer();
  EL::StatusCode clearEvent();  

  void setP4(const xAOD::Jet * in, xAOD::Jet * out) { out->setJetP4( in->jetP4() ); }
  
private:

  // decorator defining non-standard object variables
  static FatJetDecorator m_decorator;

  bool m_isMC;

  xAOD::JetContainer* m_cam12jets, * m_cam12grmjets;
  xAOD::JetAuxContainer* m_cam12jetsAux, * m_cam12grmjetsAux;
  // selection functions for single objects
  static bool checkPassSel(xAOD::Jet * part);
  
  static bool passFatJet(xAOD::Jet* jet);

  EL::StatusCode decorate(xAOD::Jet * jet);

  EL::StatusCode calibrateCopies(xAOD::JetContainer * particles, const CP::SystematicSet & sysSet);
  
  virtual EL::StatusCode setVariables(xAOD::Jet * inPart, xAOD::Jet * outPart, bool isSys);

};

#endif
