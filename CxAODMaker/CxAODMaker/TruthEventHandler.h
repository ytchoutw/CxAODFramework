// Dear emacs, this is -*-c++-*-

#ifndef CxAODMaker_TruthEventHandler_H
#define CxAODMaker_TruthEventHandler_H

// STL includes
#include <string>

// Infra structure includes
#include "xAODRootAccess/TEvent.h"
#include "EventLoop/StatusCode.h"

// Forward declarations
class ConfigStore;
class EventInfoHandler;
namespace xAOD {
#ifndef XAODTRUTH_TRUTHPARTICLECONTAINER_H 
  class TruthEventContainer;
#endif
#ifndef XAODTRUTH_TRUTHPARTICLE_H 
  class TruthEvent;
#endif
}

class TruthEventHandler {
  
public:

  TruthEventHandler(ConfigStore & config, xAOD::TEvent * event, EventInfoHandler & eventInfoHandler);
  
  ~TruthEventHandler();
  
  EL::StatusCode setObjects();
  EL::StatusCode select();
  EL::StatusCode fillOutputContainer();
  EL::StatusCode clearEvent();
  

private:

  ConfigStore      & m_config;
  EventInfoHandler & m_eventInfoHandler;
  xAOD::TEvent     * m_event;
  std::string        m_containerName;

};

#endif
