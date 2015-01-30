#ifndef CxAOD__VHbb2lepEvtSelection_H
#define CxAOD__VHbb2lepEvtSelection_H

#include <vector>

#include "VHbbEvtSelection.h"

// structure holding kinematics of the result
struct ResultVHbb2lep
{
  bool pass;
  const xAOD::Electron* el1;
  const xAOD::Electron* el2;
  const xAOD::Muon* mu1;
  const xAOD::Muon* mu2;
  std::vector<const xAOD::Jet*> jets;

  enum class Type { undefined, ee, mm, em };
  Type type() {
    if(el1!=nullptr && el2!=nullptr) return Type::ee;
    if(mu1!=nullptr && mu2!=nullptr) return Type::mm;
    if(mu1!=nullptr && el1!=nullptr) return Type::em;
    return Type::undefined;
  }
};

class VHbb2lepEvtSelection : public VHbbEvtSelection<ResultVHbb2lep>
{
  public:
    VHbb2lepEvtSelection() = default;
    virtual ~VHbb2lepEvtSelection() noexcept {}

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
