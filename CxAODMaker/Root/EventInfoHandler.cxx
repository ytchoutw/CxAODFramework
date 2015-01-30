#include <iostream>

#include "EventLoop/StatusCode.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODCore/AuxInfoBase.h"
#include "xAODCore/ShallowAuxInfo.h"
#include "xAODTracking/Vertex.h"
#include "xAODRootAccess/tools/ReturnCheck.h"
#include "CxAODMaker/EventInfoHandler.h"
#include "GoodRunsLists/GoodRunsListSelectionTool.h"
#include "CxAODTools/ConfigStore.h"

EventInfoHandler::EventInfoHandler(ConfigStore & config) :
  m_config(config),
  m_eventInfoOut(0),
  m_eventInfoIn(0),
  m_decorator(),
  m_grlSelectionTool(0),
  m_grl(""),
  m_isMC(-1)
{

}
EventInfoHandler::~EventInfoHandler(){
  delete m_grlSelectionTool;
}


EL::StatusCode EventInfoHandler::initialize() {

  m_config.getif<std::string>("grl",m_grl);

  // GRL selection tool
  //--------------------
  m_grlSelectionTool = new GoodRunsListSelectionTool("GoodRunsListSelectionTool");
  std::vector<std::string> vecStringGRL;
  vecStringGRL.push_back(m_grl);
  m_grlSelectionTool->setProperty("GoodRunsListVec", vecStringGRL);
  // if true (default) will ignore result of GRL and will just pass all events
  m_grlSelectionTool->setProperty("PassThrough", false);
  if (!m_grlSelectionTool->initialize().isSuccess()) {
    Error("EventInfoHandler::initialize()", "Failed to properly initialize the GRL tool. Exiting.");
    return EL::StatusCode::FAILURE;
  } else {
    if (m_config.get<bool>("debug")) {
      m_grlSelectionTool->msg().setLevel(MSG::DEBUG);
    }
  }

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode EventInfoHandler::executeEvent(xAOD::TEvent * event) 
{

  //----------------------------
  // Event information
  //--------------------------- 

  // retrieve event info from TEvent
  const xAOD::EventInfo * eventInfoIn = 0;
  if ( ! event->retrieve(eventInfoIn, "EventInfo").isSuccess() ) {
    Error("EventInfoHandler::executeEvent()", "Failed to retrieve event info collection. Exiting.");
    return EL::StatusCode::FAILURE;
  }
  // make shallow copy
  std::pair< xAOD::EventInfo *, xAOD::ShallowAuxInfo *> sc_eventInfo = shallowCopyObject(*eventInfoIn);
  m_eventInfoIn = sc_eventInfo.first; 
  
  // check MC/data
  m_isMC = static_cast<int>(m_eventInfoIn->eventType(xAOD::EventInfo::IS_SIMULATION));
  if ( ! (m_isMC==0 || m_isMC==1) ) {
    Error("EventInfoHandler::executeEvent()", "Couldn't determine if the sample is MC!");
    return EL::StatusCode::FAILURE;
  }
  
  // use a custom decorator for isMC to avoid bit map
  m_decorator.set(m_eventInfoIn, EventInfoIntProps::isMC, m_isMC);
  if ( m_isMC ) {
    // use a custom decorator for mcEventWeight, since the original info is a vector
    if (eventInfoIn->mcEventWeights().size() != 1) {
      Error("EventInfoHandler::executeEvent()", "Number of MC weights is not 1!");
      return EL::StatusCode::FAILURE;
    }
    m_decorator.set(m_eventInfoIn, EventInfoFloatProps::MCEventWeight, eventInfoIn->mcEventWeight(0));
  } else {
    //check GRL - and decorate result
    int passGRL = true;
    if (!m_grlSelectionTool->passRunLB(*eventInfoIn)) passGRL = false;
    m_decorator.set(m_eventInfoIn, EventInfoIntProps::passGRL, passGRL);
    //check if event is clean - and decorate result
    int isCleanEvent = true;
    if ((eventInfoIn->errorState(xAOD::EventInfo::EventFlagSubDet::Tile) == xAOD::EventInfo::Error)
            || (eventInfoIn->errorState(xAOD::EventInfo::EventFlagSubDet::LAr) == xAOD::EventInfo::Error)
            || (eventInfoIn->isEventFlagBitSet(xAOD::EventInfo::Core, 18))) {
      isCleanEvent = false;
    }
    m_decorator.set(m_eventInfoIn, EventInfoIntProps::isCleanEvent, isCleanEvent);
  }

  //--------------------------
  //Vertex info
  //--------------------------

  // primary vertex
  const xAOD::Vertex * primVtx = 0;
  int nVtx3Trks = 0;

  // get the vertex container
  const xAOD::VertexContainer * primVtxCont = 0;
  if ( ! event->retrieve(primVtxCont, "PrimaryVertices").isSuccess() ) {
    Error("EventInfoHandler::executeEvent()", "Failed to retrieve primary vertices collection. Exiting.");
    return EL::StatusCode::FAILURE;
  } 

  // find the primary vertex and count the number of vertices with at least 2 tracks
  bool found = false;
  for (const xAOD::Vertex * vtx : *primVtxCont) {
    //primary vertex seems to be always at 0th position, but just to be sure
    //ask for type and at least two associated tracks
    if ( (vtx->vertexType() == xAOD::VxType::PriVtx) && (vtx->nTrackParticles() > 2) ) {
      // store the first one that has more than 2-tracks
      if(!found) {
	primVtx = vtx;
	found = true;
      }	
    }
    if ( vtx->nTrackParticles() > 2 ) ++nVtx3Trks;
  }
  m_decorator.set(m_eventInfoIn, EventInfoIntProps::NVtx3Trks, nVtx3Trks);
  
  // check if primary vertex is found
  float ZPV = -9999;
  if ( ! primVtx ) {
    Warning("EventInfoHandler::executeEvent()", "Couldn't find a primary vertex in this event!");
  } 
  else {
    ZPV = primVtx->z();
  }
  m_decorator.set(m_eventInfoIn, EventInfoIntProps::hasPV, primVtx != 0);
  m_decorator.set(m_eventInfoIn, EventInfoFloatProps::ZPV, ZPV);

  return EL::StatusCode::SUCCESS;
  
}

void EventInfoHandler::setVariables(xAOD::EventInfo* eventInfoIn, xAOD::EventInfo* eventInfoOut) {

  eventInfoOut->setRunNumber(eventInfoIn->runNumber());
  eventInfoOut->setEventNumber(eventInfoIn->eventNumber());
  eventInfoOut->setAverageInteractionsPerCrossing(eventInfoIn->averageInteractionsPerCrossing());  // TODO remove?
  m_decorator.copy(eventInfoIn, eventInfoOut, EventInfoIntProps::isMC);
  if ( m_isMC ) {
    eventInfoOut->setMCEventNumber(eventInfoIn->mcEventNumber());
    eventInfoOut->setMCChannelNumber(eventInfoIn->mcChannelNumber());
    m_decorator.copy(eventInfoIn, eventInfoOut, EventInfoFloatProps::MCEventWeight);
  } else {
    m_decorator.copy(eventInfoIn, eventInfoOut, EventInfoIntProps::passGRL); // TODO remove?
    m_decorator.copy(eventInfoIn, eventInfoOut, EventInfoIntProps::isCleanEvent); // TODO remove?
  }
  m_decorator.copy(eventInfoIn, eventInfoOut, EventInfoFloatProps::ZPV);
  m_decorator.copy(eventInfoIn, eventInfoOut, EventInfoIntProps::NVtx3Trks);

}


EL::StatusCode EventInfoHandler::fillOutputContainer(xAOD::TEvent * event) 
{

  // create containers
  m_eventInfoOut = new xAOD::EventInfo();
  xAOD::AuxInfoBase * eventInfoOutAux = new xAOD::AuxInfoBase();
  m_eventInfoOut->setStore(eventInfoOutAux);
  
  setVariables(m_eventInfoIn, m_eventInfoOut);

  // record event info 
  if ( ! event->record(m_eventInfoOut, "EventInfo___Nominal") ) {
    return EL::StatusCode::FAILURE;
  }
  if ( ! event->record(eventInfoOutAux, "EventInfo___NominalAux.") ) {
    return EL::StatusCode::FAILURE;
  }
  
  // //create a shallow copy e.g. for systematic variations of the event weights
  // if ( m_isMC ) {
  //   std::pair< xAOD::EventInfo *, xAOD::ShallowAuxInfo *> sc_eventInfoOut = shallowCopyObject(*m_eventInfoOut);
  //   //just an example: overwrite mcEventWeight...
  //   m_EventInfoDecorator.set(sc_eventInfoOut.first, EventInfoFloatProps::MCEventWeight,
  // 			     1.2*m_EventInfoDecorator.get(m_eventInfoOut, EventInfoFloatProps::MCEventWeight));
  //   if ( event->record(sc_eventInfoOut.first, "EventInfo___SC") ) {
  //     return EL::StatusCode::FAILURE;
  //   }
  //   if ( ! event->record(sc_eventInfoOut.second, "EventInfo___SCAux") ) {
  //     return EL::StatusCode::FAILURE;
  //   }
  // }
  

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode EventInfoHandler::clearEvent()
{
  
  delete m_eventInfoIn->getConstStore();
  delete m_eventInfoIn;
  m_eventInfoIn = 0;
  
  return EL::StatusCode::SUCCESS;

}
