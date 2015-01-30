#ifndef CxAOD__VHbb1lepEvtSelection_H
#define CxAOD__VHbb1lepEvtSelection_H

#include <vector>

#include "VHbbEvtSelection.h"

// structure holding kinematics of the result
struct ResultVHbb1lep
{
  bool pass;
  const xAOD::Electron* el;
  const xAOD::Muon* mu;
  const xAOD::MissingET* met;
  std::vector<const xAOD::Jet*> jets;

  bool isEl() { return el!=nullptr; }
};

class VHbb1lepEvtSelection : public VHbbEvtSelection<ResultVHbb1lep>
{
  public:
    VHbb1lepEvtSelection() = default;
    virtual ~VHbb1lepEvtSelection() noexcept {}


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
