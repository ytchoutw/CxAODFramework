#include "CxAODTools/VHbb2lepEvtSelection.h"

#include "xAODEgamma/Electron.h"
#include "xAODEgamma/Photon.h"
#include "xAODMuon/Muon.h"
#include "xAODJet/Jet.h"
#include "xAODEventInfo/EventInfo.h"

void VHbb2lepEvtSelection::clearResult() {
  m_result.pass = false;
  m_result.jets.clear();
  m_result.el1 = nullptr;
  m_result.el2 = nullptr;
  m_result.mu1 = nullptr;
  m_result.mu2 = nullptr;
}

bool VHbb2lepEvtSelection::passSelection(const xAOD::EventInfo* evtinfo,
                                         const xAOD::MissingET* met,
					 const xAOD::ElectronContainer* electrons,
					 const xAOD::PhotonContainer* photons,
                                         const xAOD::MuonContainer* muons,
                                         const xAOD::JetContainer* jets) {

  // here just as an example:
  // if a new passKinematics() function is defined with some variables in the prototype,
  // one needs to reimplement passSelection here
  // otherwise, don't need to put any code
  return VHbbEvtSelection<ResultVHbb2lep>::passSelection(evtinfo, met, electrons,
                                                         muons, jets);
}

bool VHbb2lepEvtSelection::passLeptonSelection(const xAOD::ElectronContainer* electrons,
                                               const xAOD::MuonContainer* muons,
                                               const xAOD::MissingET* met) {
  int res = doVHLeptonSelection(electrons, muons, m_result.el1, m_result.el2,
                                m_result.mu1, m_result.mu2);
  if(res != 2) {
    return false;
  }
  return true;

}

bool VHbb2lepEvtSelection::passKinematics() {
  // MJ cuts, like MET / MPT etc...
  // my advice is to add in passKinematics() prototype all the stuff that
  // doesn't need to be put in the Result struct, like MPT

  return true;
}

//
// Pre-selection versions
bool VHbb2lepEvtSelection::passPreSelection(const xAOD::EventInfo* evtinfo,
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
  return VHbbEvtSelection<ResultVHbb2lep>::passPreSelection(evtinfo, met, electrons,
                                                            muons, jets, fatjets);
}

bool VHbb2lepEvtSelection::passLeptonPreSelection(const xAOD::ElectronContainer* electrons,
                                                  const xAOD::MuonContainer* muons,
                                                  const xAOD::MissingET* met) {
  int res = doVHLeptonPreSelection(electrons, muons, m_result.el1, m_result.el2,
                                   m_result.mu1, m_result.mu2);
  if(res != 2) {
    return false;
  }
  return true;

}

