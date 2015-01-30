#include "CxAODTools/VBFbbAEvtSelection.h"

#include "xAODEgamma/Electron.h"
#include "xAODEgamma/Photon.h"
#include "xAODMuon/Muon.h"
#include "xAODJet/Jet.h"
#include "xAODEventInfo/EventInfo.h"


void VBFbbAEvtSelection::clearResult() {
  m_result.pass = false;
  m_result.jets.clear();
  m_result.ph  = nullptr;
  //  m_result.met = nullptr;
}

bool VBFbbAEvtSelection::passSelection(const xAOD::EventInfo* evtinfo,
                                         const xAOD::MissingET* met,
                                         const xAOD::ElectronContainer* electrons,
					 const xAOD::PhotonContainer* photons,
                                         const xAOD::MuonContainer* muons,
                                         const xAOD::JetContainer* jets) {

  // here just as an example:
  // if a new passKinematics() function is defined with some variables in the prototype,
  // one needs to reimplement passSelection here
  // otherwise, don't need to put any code
  return VHbbEvtSelection<ResultVBFbbA>::passSelection(evtinfo, met, electrons, muons, jets);
}

bool VBFbbAEvtSelection::passLeptonSelection(const xAOD::ElectronContainer* electrons,
                                               const xAOD::MuonContainer* muons,
                                               const xAOD::MissingET* met) {
  const xAOD::Electron *el1=nullptr, *el2=nullptr;
  const xAOD::Muon *mu1=nullptr, *mu2=nullptr;
  int res = doVHLeptonSelection(electrons, muons, el1, el2, mu1, mu2);
  if(res != 0) {
    return false;
  }
  //what does this do for met? todo : figure this out
  //m_result.met = met;
  // todo : is something similar needed for ph?
  //m_result.ph = ph
  return true;

}

// preselection versions
bool VBFbbAEvtSelection::passPreSelection(const xAOD::EventInfo* evtinfo,
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
  return VHbbEvtSelection<ResultVBFbbA>::passPreSelection(evtinfo, met, electrons,
                                                            muons, jets, fatjets);
}

bool VBFbbAEvtSelection::passLeptonPreSelection(const xAOD::ElectronContainer* electrons,
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



bool VBFbbAEvtSelection::passKinematics() {
  // MJ cuts, like MET / MPT etc...
  // my advice is to add in passKinematics() prototype all the stuff that
  // doesn't need to be put in the Result struct, like MPT

  return true;
}
