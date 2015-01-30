#include <iostream>

//muon specific includes
#include "xAODTruth/TruthEventContainer.h"
#include "CxAODMaker/TruthEventHandler.h"

// framework includes
#include "CxAODTools/ConfigStore.h"
#include "CxAODMaker/EventInfoHandler.h"


TruthEventHandler::TruthEventHandler(ConfigStore & config, xAOD::TEvent * event, EventInfoHandler & eventInfoHandler) : 
  m_config(config), 
  m_eventInfoHandler(eventInfoHandler),
  m_event(event)
{
  
  // set container name
  m_config.getif<std::string>("truthEventContainer", m_containerName);
  
}


TruthEventHandler::~TruthEventHandler()
{

}


EL::StatusCode TruthEventHandler::setObjects() 
{
  
  if (!m_eventInfoHandler.get_isMC()) {
    return EL::StatusCode::SUCCESS;
  }

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode TruthEventHandler::select() 
{

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode TruthEventHandler::fillOutputContainer() 
{

  if (!m_eventInfoHandler.get_isMC()) {
    return EL::StatusCode::SUCCESS;
  }

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode TruthEventHandler::clearEvent() 
{

  return EL::StatusCode::SUCCESS;

}

