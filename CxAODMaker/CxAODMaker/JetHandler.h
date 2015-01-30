// Dear emacs, this is -*-c++-*-
#ifndef CxAODMaker_JetHandler_H
#define CxAODMaker_JetHandler_H

#include "CxAODMaker/ObjectHandler.h"
#include "CxAODTools/JetDecorator.h"

namespace xAOD {
#ifndef XAODJET_JETCONTAINER_H 
  class JetContainer;
#endif
#ifndef XAODJET_JET_H 
  class Jet;
#endif
}

class JetCalibrationTool;
class JetCleaningTool;


class JetHandler : public ObjectHandler<xAOD::Jet,xAOD::JetContainer> {

public:

  JetHandler(const std::string& name, ConfigStore & config, xAOD::TEvent * event,
             EventInfoHandler & eventInfoHandler);

  ~JetHandler();
  
  EL::StatusCode initializeTools();
  EL::StatusCode select();
  EL::StatusCode fillOutputContainer();
  EL::StatusCode clearEvent();  

  void setP4(const xAOD::Jet * in, xAOD::Jet * out) { out->setJetP4( in->jetP4() ); }
  
private:

  // decorator defining non-standard object variables
  static JetDecorator m_decorator;

  // tools
  JetCalibrationTool * m_jetCalibration;
  JetCleaningTool    * m_jetCleaning; 

  std::string m_jetAlgoName;
  bool m_isMC;

  // selection functions for single objects
  static bool checkPassSelOR(xAOD::Jet * part);
  static bool checkPassSelNoOR(xAOD::Jet * part);
  static bool passVetoJet(xAOD::Jet* jet);
  static bool passSignalJet(xAOD::Jet* jet);

  static void retrieveBTaggingDiscriminants(xAOD::Jet * jet);

  EL::StatusCode decorate(xAOD::Jet * jet);

  EL::StatusCode calibrateCopies(xAOD::JetContainer * particles, const CP::SystematicSet & sysSet);
  
  virtual EL::StatusCode setVariables(xAOD::Jet * inPart, xAOD::Jet * outPart, bool isSys);

  std::vector<std::string> m_btaggerNames;
};

#endif
