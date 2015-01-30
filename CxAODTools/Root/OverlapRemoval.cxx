#include "CxAODTools/OverlapRemoval.h"

EL::StatusCode OverlapRemoval::removeOverlap(const xAOD::ElectronContainer* electrons,
                                             const xAOD::PhotonContainer* photons,
					     const xAOD::MuonContainer* muons,
                                             const xAOD::JetContainer* jets)
{

  // jet removal
  //-----------------
  if(jets) {
  for (const xAOD::Jet * jet : *jets) {
    // ensure flag is present for all jets
    m_decorator.set(jet, JetIntProps::passOR, false);
    // ignore particles that didn't pass pre-selection
    if (!m_decorator.get(jet, JetIntProps::isVetoJet)) {
      continue;
    }
    bool jetPassOR = true;

    // remove jet if within dR<0.4 of any electron
      if(electrons) {
    for (const xAOD::Electron* elec : *electrons) {
      // ignore particles that didn't pass pre-selection
      if (!m_decorator.get(elec, ElecIntProps::isVHLooseElectron)) {
        continue;
      }
      if (elec->p4().DeltaR(jet->p4()) < 0.4) {
        jetPassOR &= false;
      }
    }
      }

    // remove jets if Ntrk<=3 and within dR<0.4 of any muon
    int nJetTracks = 99;
    // TODO this returns a vector??
    //jet->getAttribute(xAOD::JetAttribute::AttributeID::NumTrkPt500, nJetTracks);
    if (nJetTracks <= 3) {
        if(muons) {
      for (const xAOD::Muon* muon : *muons) {
        // ignore particles that didn't pass pre-selection
        if (!m_decorator.get(muon, MuonIntProps::isVHLooseMuon)) {
          continue;
        }
        if (muon->p4().DeltaR(jet->p4()) < 0.4) {
          jetPassOR &= false;
        }
      }
    }
      }

    // set jet flag
    m_decorator.set(jet, JetIntProps::passOR, jetPassOR);
  }
  }

  // muon removal
  //-----------------
  if(muons) {
    for (const xAOD::Muon* muon : *muons) {
      // ensure flag is present for all muons
      m_decorator.set(muon, MuonIntProps::passOR, false);
      // ignore particles that didn't pass pre-selection
      if (!m_decorator.get(muon, MuonIntProps::isVHLooseMuon)) {
        continue;
      }
      bool muonPassOR = true;

      // remove muons within dR<0.4 of any jet with Ntrk>3
      if(jets) {
        for (const xAOD::Jet * jet : *jets) {
          // ignore particles that didn't pass pre-selection
          if (!m_decorator.get(jet, JetIntProps::isVetoJet)) {
            continue;
          }
          // ignore particles that didn't pass previous OR
          if (!m_decorator.get(jet, JetIntProps::passOR)) {
            continue;
          }
          int nJetTracks = 99;
          // TODO this returns a vector??
          //jet->getAttribute(xAOD::JetAttribute::AttributeID::NumTrkPt500, nJetTracks);
          if (muon->p4().DeltaR(jet->p4()) < 0.4 && nJetTracks > 3) {
            muonPassOR &= false;
          }
        }
      }

      // set muon flag
      m_decorator.set(muon, MuonIntProps::passOR, muonPassOR);
    }
  }

  // electron removal
  //-----------------
  if(electrons) {
    for (const xAOD::Electron* elec : *electrons) {
      // all electrons pass
      if (m_decorator.get(elec, ElecIntProps::isVHLooseElectron)) {
        m_decorator.set(elec, ElecIntProps::passOR, true);
      }
      else {
        m_decorator.set(elec, ElecIntProps::passOR, false);
      }
    }
  }


  // todo
  // photon removal
  if(photons) {
    for(const xAOD::Photon* phot : *photons) {
      m_decorator.set(phot,PhotIntProps::passOR, true);
    }
  }


  return EL::StatusCode::SUCCESS;
}

