// Dear emacs, this is -*-c++-*-
#ifndef CxAODTools__OverlapRemoval_H
#define CxAODTools__OverlapRemoval_H

#include "CxAODTools/SuperDecorator.h"

#include "EventLoop/StatusCode.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODJet/JetContainer.h"

class OverlapRemoval
{
  protected:
    SuperDecorator m_decorator;

  public:
    OverlapRemoval() = default;
    virtual ~OverlapRemoval() = default;

    virtual EL::StatusCode removeOverlap(const xAOD::ElectronContainer* electrons,
                                         const xAOD::PhotonContainer* photons,
					 const xAOD::MuonContainer* muons,
                                         const xAOD::JetContainer* jets);
};


#endif
