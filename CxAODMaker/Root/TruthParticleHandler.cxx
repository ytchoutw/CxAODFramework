#include <iostream>

// truth specific includes
#include "CxAODMaker/TruthParticleHandler.h"

bool TruthParticleHandler::m_isTop = false;

TruthParticleHandler::TruthParticleHandler(const std::string& name, ConfigStore & config,
                                           xAOD::TEvent * event, EventInfoHandler & eventInfoHandler) : 
  ObjectHandler(name, config, event, eventInfoHandler)
{

  // don't need element links for truth (and it's very slow)
  m_createElementLinks = false;

}


TruthParticleHandler::~TruthParticleHandler()
{

}


EL::StatusCode TruthParticleHandler::initializeTools() 
{ 

  return EL::StatusCode::SUCCESS; 
}


EL::StatusCode TruthParticleHandler::setObjects() 
{
  
  if (!m_eventInfoHandler.get_isMC()) {
    return EL::StatusCode::SUCCESS;
  }
  return ObjectHandler::setObjects();

}


/**
 * nothing to do in select()
 */
EL::StatusCode TruthParticleHandler::select() 
{

  return EL::StatusCode::SUCCESS;

}


/**
 * This function decides if a particle should be saved or not
 */
bool TruthParticleHandler::checkPassSel(xAOD::TruthParticle * part) 
{

  // if(part->isChLepton()) return true;
  // if(part->isNeutrino()) return true;
  // if(part->isQuark()) return true;
  
  // int mcChannelNumber = m_eventInfo->mcChannelNumber();
  
  // deal with top quarks
  if(part->isTop()) {

    m_isTop = true;

    if(part->status() != 3) return false;

    return true;
  }

  // deal with W/Z bosons
  if( part->isW() || part->isZ() ) {
    
    if(m_isTop) return false;
    
    return true;
  }

  // W/Z from Sherpa
  if(part->isLepton()) {
    if(m_isTop) return false;
    if(part->status() != 3) return false;
    return true;
  }

  // deal with the Higgs boson
  if(part->isHiggs()) {
    
    return true;
  }
  
  return false;  
}


EL::StatusCode TruthParticleHandler::fillOutputContainer() 
{
  m_isTop = false;

  if (!m_eventInfoHandler.get_isMC()) {
    return EL::StatusCode::SUCCESS;
  }
  return fillOutputContainerCheck(&checkPassSel);
}


/**
 * Perform cleaning if needed
 */
EL::StatusCode TruthParticleHandler::clearEvent() 
{

  if (ObjectHandler::clearEvent() != EL::StatusCode::SUCCESS) {
    Error("EL::StatusCode TruthParticleHandler::clearEvent()", "Failed to clear event in object handler!");
    return EL::StatusCode::FAILURE;
  }
  return EL::StatusCode::SUCCESS;
}


/**
 * No decoration is needed here
 */
EL::StatusCode TruthParticleHandler::decorate(xAOD::TruthParticle * particle) 
{

  return EL::StatusCode::SUCCESS;
}


/**
 * No calib is needed here
 */
EL::StatusCode TruthParticleHandler::calibrateCopies(xAOD::TruthParticleContainer * particles, const CP::SystematicSet & sysSet) 
{

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TruthParticleHandler::setVariables(xAOD::TruthParticle * inPart, xAOD::TruthParticle * outPart, bool isSysVar) 
{

  // set kinematics
  setP4( inPart , outPart );

  outPart->setPdgId(inPart->pdgId());

  // the next two are temp for testing
  outPart->setBarcode(inPart->barcode());
  outPart->setStatus(inPart->status());

  outPart->toPersistent();

  return EL::StatusCode::SUCCESS;

}
