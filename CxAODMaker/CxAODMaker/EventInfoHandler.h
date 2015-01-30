// Dear emacs, this is -*-c++-*-
#ifndef CxAODMaker_EventInfoHandler_H
#define CxAODMaker_EventInfoHandler_H

// Framework includes
#ifndef __MAKECINT__

#include "CxAODTools/EventInfoDecorator.h"
#include "xAODCore/AuxContainerBase.h"
#include "xAODCore/AuxInfoBase.h"
#include "xAODCore/ShallowCopy.h"
#include "GoodRunsLists/GoodRunsListSelectionTool.h"
#endif // not __MAKECINT__


#include "xAODEventInfo/EventInfo.h"


// Forward declarations
class ConfigStore;

class EventInfoHandler {

public:

  EventInfoHandler(ConfigStore & config);

  ~EventInfoHandler();

  EL::StatusCode initialize();
  EL::StatusCode executeEvent(xAOD::TEvent * event);
  EL::StatusCode fillOutputContainer(xAOD::TEvent * event);
  
  // get info
  int   get_runNumber()       { return m_eventInfoIn->runNumber()                                                           ; }
  int   get_eventNumber()     { return m_eventInfoIn->eventNumber()                                                         ; }
  int   get_mcEventNumber()   { return m_isMC ? m_eventInfoIn->mcEventNumber()                                      : -1    ; }
  int   get_mcChannelNumber() { return m_isMC ? m_eventInfoIn->mcChannelNumber()                                    : -1    ; }
  float get_MCEventWeight()   { return m_isMC ? m_decorator.get(m_eventInfoIn, EventInfoFloatProps::MCEventWeight)  : -999. ; }
  float get_ZPV()             { return m_decorator.get(m_eventInfoIn, EventInfoFloatProps::ZPV)                             ; }
  int   get_NVtx3Trks()       { return m_decorator.get(m_eventInfoIn, EventInfoIntProps::NVtx3Trks)                         ; }
  int   get_isMC()            { return m_isMC                                                                               ; }

  // get decorator
  const xAOD::EventInfo * getEventInfo() const { return m_eventInfoIn; }

  // clean shallow copy
  EL::StatusCode clearEvent();


private:

  ConfigStore & m_config;
  
  void setVariables(xAOD::EventInfo* eventInfoIn, xAOD::EventInfo* eventInfoOut);

#ifndef __MAKECINT__
  xAOD::EventInfo      * m_eventInfoOut; //!
  xAOD::EventInfo      * m_eventInfoIn; //!
  EventInfoDecorator   m_decorator; //!
  GoodRunsListSelectionTool *m_grlSelectionTool; //!
  #endif // not __MAKECINT__

  std::string m_grl;
  int m_isMC;

};

#endif
