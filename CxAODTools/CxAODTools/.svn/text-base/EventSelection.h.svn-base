// Dear emacs, this is -*-c++-*-
#ifndef CxAODTools__EventSelection_H
#define CxAODTools__EventSelection_H

#ifndef __MAKECINT__
#include "CxAODTools/SuperDecorator.h"
#endif // not __MAKECINT__

#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODMissingET/MissingETContainer.h"	

class EventSelection
{
  protected:
#ifndef __MAKECINT__
    SuperDecorator m_decorator;
#endif // not __MAKECINT__

  public:
    EventSelection() = default;
    virtual ~EventSelection() = default;

    // TODO add MET somewhere when we know how to acecss it
    virtual bool passPreSelection(const xAOD::EventInfo* evtinfo,
                                  const xAOD::MissingET* met,
                                  const xAOD::ElectronContainer* electrons,
				  const xAOD::PhotonContainer* photons,
                                  const xAOD::MuonContainer* muons,
                                  const xAOD::JetContainer* jets,
                                  const xAOD::JetContainer* fatjets) = 0;

    virtual bool passSelection(const xAOD::EventInfo* evtinfo,
                               const xAOD::MissingET* met,
                               const xAOD::ElectronContainer* electrons,
			       const xAOD::PhotonContainer* photons,
                               const xAOD::MuonContainer* muons,
                               const xAOD::JetContainer* jets) = 0;
};


#endif
