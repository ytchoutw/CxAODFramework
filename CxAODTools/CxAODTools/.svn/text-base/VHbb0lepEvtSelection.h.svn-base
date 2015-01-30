#ifndef CxAOD__VHbb0lepEvtSelection_H
#define CxAOD__VHbb0lepEvtSelection_H

#include <vector>

#include "VHbbEvtSelection.h"

// structure holding kinematics of the result
struct ResultVHbb0lep
{
  bool pass;
  const xAOD::MissingET* met;
  std::vector<const xAOD::Jet*> jets;
};

class VHbb0lepEvtSelection : public VHbbEvtSelection<ResultVHbb0lep>
{
  public:
    VHbb0lepEvtSelection() = default;
    virtual ~VHbb0lepEvtSelection() noexcept {}


    virtual bool passSelection(const xAOD::EventInfo* evtinfo,
                               const xAOD::MissingET* met,
                               const xAOD::ElectronContainer* electrons,
			       const xAOD::PhotonContainer* photons,
                               const xAOD::MuonContainer* muons,
                               const xAOD::JetContainer* jets);

    virtual bool passPreSelection(const xAOD::EventInfo* evtinfo,
                                  const xAOD::MissingET* met,
                                  const xAOD::ElectronContainer* electrons,
				  const xAOD::PhotonContainer* photons,
                                  const xAOD::MuonContainer* muons,
                                  const xAOD::JetContainer* jets,
                                  const xAOD::JetContainer* fatjets);

  protected:
    virtual bool passLeptonSelection(const xAOD::ElectronContainer* electrons,
                                     const xAOD::MuonContainer* muons,
                                     const xAOD::MissingET* met);

    virtual bool passLeptonPreSelection(const xAOD::ElectronContainer* electrons,
                                        const xAOD::MuonContainer* muons,
                                        const xAOD::MissingET* met);

    virtual bool passKinematics();

    virtual void clearResult();

};

#endif
