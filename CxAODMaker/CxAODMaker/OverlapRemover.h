#ifndef CxAODMaker_OverlapRemover_H
#define CxAODMaker_OverlapRemover_H

#include "EventLoop/StatusCode.h"

#include "CxAODTools/ConfigStore.h"
#include "CxAODTools/SuperDecorator.h"
#include "CxAODTools/OverlapRemoval.h"

#include "CxAODMaker/ElectronHandler.h"
#include "CxAODMaker/PhotonHandler.h"
#include "CxAODMaker/MuonHandler.h"
#include "CxAODMaker/JetHandler.h"

#include <map>


class OverlapRemover {

private:

  ConfigStore & m_config;

  JetHandler      * m_jets;
  MuonHandler     * m_muons;
  ElectronHandler * m_electrons;
  PhotonHandler   * m_photons;
  SuperDecorator m_decorator;

  OverlapRemoval m_OR;

public:

  OverlapRemover(ConfigStore & config);

  ~OverlapRemover();

  void setJets(JetHandler* jets) { m_jets = jets; }

  void setMuons(MuonHandler* muons) { m_muons = muons; }

  void setElectrons(ElectronHandler* electrons) { m_electrons = electrons; }

  void setPhotons(PhotonHandler* photons) { m_photons = photons; }

  EL::StatusCode removeOverlap(const TString& sysName);

};

#endif
