#include "CxAODTools/VHbb0lepEvtSelection.h"

#include "xAODEgamma/Electron.h"
#include "xAODEgamma/Photon.h"
#include "xAODMuon/Muon.h"
#include "xAODJet/Jet.h"
#include "xAODEventInfo/EventInfo.h"


void VHbb0lepEvtSelection::clearResult() {
  m_result.pass = false;
  m_result.jets.clear();
  m_result.met = nullptr;
}

bool VHbb0lepEvtSelection::passSelection(const xAOD::EventInfo* evtinfo,
                                         const xAOD::MissingET* met,
                                         const xAOD::ElectronContainer* electrons,
					 const xAOD::PhotonContainer* photons,
                                         const xAOD::MuonContainer* muons,
                                         const xAOD::JetContainer* jets) {

  // here just as an example:
  // if a new passKinematics() function is defined with some variables in the prototype,
  // one needs to reimplement passSelection here
  // otherwise, don't need to put any code
  return VHbbEvtSelection<ResultVHbb0lep>::passSelection(evtinfo, met, electrons, muons, jets);
}

bool VHbb0lepEvtSelection::passLeptonSelection(const xAOD::ElectronContainer* electrons,
                                               const xAOD::MuonContainer* muons,
                                               const xAOD::MissingET* met) {
  const xAOD::Electron *el1=nullptr, *el2=nullptr;
  const xAOD::Muon *mu1=nullptr, *mu2=nullptr;
  int res = doVHLeptonSelection(electrons, muons, el1, el2, mu1, mu2);
  if(res != 0) {
    return false;
  }
  m_result.met = met;
  return true;

}

// preselection versions
bool VHbb0lepEvtSelection::passPreSelection(const xAOD::EventInfo* evtinfo,
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
  return VHbbEvtSelection<ResultVHbb0lep>::passPreSelection(evtinfo, met, electrons,
                                                            muons, jets, fatjets);
}

bool VHbb0lepEvtSelection::passLeptonPreSelection(const xAOD::ElectronContainer* electrons,
                                                  const xAOD::MuonContainer* muons,
                                                  const xAOD::MissingET* met) {
  const xAOD::Electron *el1=nullptr, *el2=nullptr;
  const xAOD::Muon *mu1=nullptr, *mu2=nullptr;
  int res = doVHLeptonPreSelection(electrons, muons, el1, el2, mu1, mu2);
  if(res != 0) {
    return false;
  }
  return true;

}



bool VHbb0lepEvtSelection::passKinematics() {
  // MJ cuts, like MET / MPT etc...
  // my advice is to add in passKinematics() prototype all the stuff that
  // doesn't need to be put in the Result struct, like MPT

  return true;
}
