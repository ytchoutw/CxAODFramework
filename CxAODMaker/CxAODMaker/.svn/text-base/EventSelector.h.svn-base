#ifndef CxAODMaker_EventSelector_H
#define CxAODMaker_EventSelector_H

// infrastructure includes
#include "PATInterfaces/SystematicRegistry.h"
#include "PATInterfaces/ISystematicsTool.h"
#include "EventLoop/StatusCode.h"

#include "xAODRootAccess/TEvent.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODMissingET/MissingETContainer.h"	

#include "CxAODMaker/OverlapRemover.h"

#include "CxAODTools/ConfigStore.h"
#include "CxAODTools/SuperDecorator.h"
#include "CxAODTools/EventSelection.h"

#include "CxAODMaker/ElectronHandler.h"
#include "CxAODMaker/PhotonHandler.h"
#include "CxAODMaker/MuonHandler.h"
#include "CxAODMaker/JetHandler.h"
#include "CxAODMaker/FatJetHandler.h"
#include "CxAODMaker/EventInfoHandler.h"
#include "CxAODMaker/METHandler.h"

#include <set>

class ObjectHandlerBase;

class EventSelector {

private:

  ConfigStore & m_config;

  JetHandler* m_jets;
  FatJetHandler* m_fatjets;
  MuonHandler* m_muons;
  ElectronHandler* m_electrons;
  PhotonHandler* m_photons;
  METHandler* m_met;
  EventInfoHandler* m_info;

  bool m_doOR;
  OverlapRemover m_OR;
  EventSelection* m_selection;

  std::set<CP::SystematicSet> m_systematics;

  bool m_isFirstCall;

  EL::StatusCode fillSystematics();

  EL::StatusCode fillSystematics(ObjectHandlerBase* obj);

  bool performSelection(const TString& sysName);

  bool passORandPreSel(const CP::SystematicSet& syst);

public:

  EventSelector() = delete;

  EventSelector(ConfigStore & config);

  ~EventSelector();

  void setJets(JetHandler* jets);

  void setFatJets(FatJetHandler* jets);

  void setMuons(MuonHandler* muons);

  void setElectrons(ElectronHandler* electrons);

  void setPhotons(PhotonHandler* photons);

  void setMET(METHandler* met) { m_met = met; }

  void setEventInfo(EventInfoHandler* info) { m_info = info; }

  /**
   * @brief Set the event selection to apply
   *
   * @c this becomes the owner of the EventSelection object !
   *
   * @param[in] selection	The event selection to apply
   */
  void setSelection(EventSelection* selection) { m_selection = selection; }

  EL::StatusCode performSelection(bool& pass);

};

#endif
