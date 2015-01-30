#include "CxAODTools/VHbb1lepEvtSelection.h"

#include "xAODEgamma/Electron.h"
#include "xAODEgamma/Photon.h"
#include "xAODMuon/Muon.h"
#include "xAODJet/Jet.h"
#include "xAODEventInfo/EventInfo.h"


void VHbb1lepEvtSelection::clearResult() {
  m_result.pass = false;
  m_result.jets.clear();
  m_result.el = nullptr;
  m_result.mu = nullptr;
  m_result.met = nullptr;
}

bool VHbb1lepEvtSelection::passSelection(const xAOD::EventInfo* evtinfo,
                                         const xAOD::MissingET* met,
                                         const xAOD::ElectronContainer* electrons,
					 const xAOD::PhotonContainer* photons,
					 const xAOD::MuonContainer* muons,
                                         const xAOD::JetContainer* jets) {

  // here just as an example:
  // if a new passKinematics() function is defined with some variables in the prototype,
  // one needs to reimplement passSelection here
  // otherwise, don't need to put any code
  return VHbbEvtSelection<ResultVHbb1lep>::passSelection(evtinfo, met, electrons,
                                                         muons, jets);
}

bool VHbb1lepEvtSelection::passLeptonSelection(const xAOD::ElectronContainer* electrons,
                                               const xAOD::MuonContainer* muons,
                                               const xAOD::MissingET* met) {
  const xAOD::Electron* el_junk=nullptr;
  const xAOD::Muon* mu_junk=nullptr;
  int res = doVHLeptonSelection(electrons, muons, m_result.el, el_junk, m_result.mu, mu_junk);
  if(res != 1) {
    return false;
  }
  m_result.met = met;
  return true;

}

//
bool VHbb1lepEvtSelection::passPreSelection(const xAOD::EventInfo* evtinfo,
					    const xAOD::MissingET* met,
					    const xAOD::ElectronContainer* electrons,
					    const xAOD::PhotonContainer* photons,
					    const xAOD::MuonContainer* muons,
					    const xAOD::JetContainer* jets,
                                            const xAOD::JetContainer* fatjets) {

  // here just as an example:
  // if a new passKinematics() function is defined with some variables in the prototype,
  // one needs to reimplement passSelection here
  // otherwise, don't need to put any code
  return VHbbEvtSelection<ResultVHbb1lep>::passPreSelection(evtinfo, met, electrons,
                                                            muons, jets, fatjets);
}

bool VHbb1lepEvtSelection::passLeptonPreSelection(const xAOD::ElectronContainer* electrons,
                                               const xAOD::MuonContainer* muons,
                                               const xAOD::MissingET* met) {
  const xAOD::Electron* el_junk=nullptr;
  const xAOD::Muon* mu_junk=nullptr;
  int res = doVHLeptonPreSelection(electrons, muons, m_result.el, el_junk, m_result.mu, mu_junk);
  if(res != 1) {
    return false;
  }
  return true;

}

bool VHbb1lepEvtSelection::passKinematics() {
  // MJ cuts, like MET / MPT etc...
  // my advice is to add in passKinematics() prototype all the stuff that
  // doesn't need to be put in the Result struct, like MPT

  return true;
}
