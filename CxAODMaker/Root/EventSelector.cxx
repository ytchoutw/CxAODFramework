#include "CxAODMaker/EventSelector.h"

#include "CxAODMaker/ObjectHandlerBase.h"

#include <iterator>
#include <cstdlib>
#include <algorithm>

EventSelector::EventSelector(ConfigStore& config) :
  m_config(config),
  m_jets(nullptr),
  m_fatjets(nullptr),
  m_muons(nullptr),
  m_electrons(nullptr),
  m_photons(nullptr),
  m_met(nullptr),
  m_info(nullptr),
  m_doOR(true),
  m_OR(config),
  m_selection(nullptr),
  m_systematics(),
  m_isFirstCall(true)
{
  m_config.getif<bool>("removeOverlap", m_doOR);
}

EventSelector::~EventSelector() {
  // we are the owner of the EventSelection object
  delete m_selection;
}

void EventSelector::setJets(JetHandler* jets) {
  m_jets = jets;
  m_OR.setJets(jets);
  if(m_doOR) jets->useForOR(true);
}

void EventSelector::setFatJets(FatJetHandler* jets) {
  m_fatjets = jets;
  //m_OR.setJets(jets);
  //if(m_doOR) jets->useForOR(true);
}

void EventSelector::setMuons(MuonHandler* muons) {
  m_muons = muons;
  m_OR.setMuons(muons);
  if(m_doOR) muons->useForOR(true);
}

void EventSelector::setElectrons(ElectronHandler* electrons) {
  m_electrons = electrons;
  m_OR.setElectrons(electrons);
  if(m_doOR) electrons->useForOR(true);
}

void EventSelector::setPhotons(PhotonHandler* photons) {
  m_photons = photons;
  m_OR.setPhotons(photons);
  if(m_doOR) photons->useForOR(true);
}

EL::StatusCode EventSelector::fillSystematics(ObjectHandlerBase* obj) {
  if(obj) {
    const auto& systs = obj->getCPVariations();
    m_systematics.insert(std::begin(systs), std::end(systs));
  }

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode EventSelector::fillSystematics() {
  // as we use a set<>, the systematics should be there only once in the end
  // so no risk to double count the nominal, or e.g jet systematics between JetHandler
  // and METHandler
  fillSystematics(m_jets);
  fillSystematics(m_fatjets);
  fillSystematics(m_muons);
  fillSystematics(m_electrons);
  fillSystematics(m_photons);
  // TODO add MET systematics when MET depends on ObjectHandler

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode EventSelector::performSelection(bool& pass) {

  if(m_isFirstCall) {
    fillSystematics();
  }

  if(!m_selection) {
    if(m_isFirstCall) {
      Warning("EventSelector::performSelection()", "No event preselection has been set ! All events will pass");
    }
  }

  m_isFirstCall = false;

  // run on all systematics
  pass = false;
  for(const auto& syst : m_systematics) {
    pass |= passORandPreSel(syst);
  }

  return EL::StatusCode::SUCCESS;

}

bool EventSelector::passORandPreSel(const CP::SystematicSet& syst) {
  // if no OR, then no selection at all
  if(!m_doOR) { return true; }

  TString sysName = syst.name();
  EL::StatusCode res = m_OR.removeOverlap(sysName);
  if(res != EL::StatusCode::SUCCESS) {
    Error("EventSelector::passORandPreSel", "There has been an issue with the OR. Please investigate !");
    exit(EXIT_FAILURE);
  }
  if(!m_selection) {
    return true;
  }
  return performSelection(sysName);
}

bool EventSelector::performSelection(const TString& sysName) {
  // first, retrieve the containers. Always check for nullptr, in case some analyses don't use some containers
  xAOD::JetContainer* jets = nullptr;
  if(m_jets) { jets = m_jets->getInParticleVariation(sysName); }
  xAOD::JetContainer* fatjets = nullptr;
  if(m_fatjets) { fatjets = m_fatjets->getInParticleVariation(sysName); }
  xAOD::ElectronContainer* electrons = nullptr;
  if(m_electrons) { electrons = m_electrons->getInParticleVariation(sysName); }
  xAOD::PhotonContainer* photons = nullptr;
  if(m_photons) { photons = m_photons->getInParticleVariation(sysName); }
  xAOD::MuonContainer* muons = nullptr;
  if(m_muons) { muons = m_muons->getInParticleVariation(sysName); }

  // at the moment no systematics for MET. Will hopefully change.
  xAOD::MissingET* met = nullptr;
  if(m_met) { met = m_met->getMET(); }

  // event info is required !
  if(! m_info) {
    Error("EventSelector::performSelection",
          "We need to know about EventInfo ! Please call setEventInfo before any attempt to apply selections");
    exit(EXIT_FAILURE);
  }
  const xAOD::EventInfo* evtinfo = m_info->getEventInfo();

  // presence of m_selection has been checked in performSelection(bool)
  return m_selection->passPreSelection(evtinfo, met, electrons, photons, muons, jets, fatjets);
}

