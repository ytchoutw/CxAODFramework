// Dear emacs, this is -*-c++-*-

#ifndef CxAODMaker_METHandler_H
#define CxAODMaker_METHandler_H

#include "AsgTools/AsgTool.h"
#include "AsgTools/ToolHandle.h"


#ifndef __MAKECINT__
#include "METInterface/IMETRebuilder.h"
#include "xAODMissingET/MissingETContainer.h"	
#include "xAODMissingET/MissingETAuxContainer.h"
#include "xAODMissingET/MissingETComposition.h"
#endif


#include "CxAODMaker/ObjectHandler.h"

class IMETRebuilder;


namespace xAOD {
#ifndef XAODMUON_MUON_H 
  class Muon;
#endif
}

class METHandler {
public:

  METHandler(ConfigStore *config, xAOD::TEvent *event = 0);
  
  ~METHandler();

//  EL::StatusCode select();
  EL::StatusCode fillOutputContainer();
  EL::StatusCode clearEvent();
  //  EL::StatusCode setMET();
  //EL::StatusCode setMET(const xAOD::ElectronContainer* elec,
  ////		        const xAOD::PhotonContainer* gamma,
  ////		        const xAOD::TauJetContainer* taujet,
  //			const xAOD::MuonContainer* muon,
  //			const xAOD::JetContainer* jet);

  EL::StatusCode setMET(std::map<TString, xAOD::ElectronContainer*>* elec,
			//std::map<TString, xAOD::PhotonContainer*>* gamma,
			//std::map<TString, xAOD::TauJetContainer*>* taujet,
			std::map<TString, xAOD::MuonContainer*>* muon,
			std::map<TString, xAOD::JetContainer*>* jet);
  

  //adding these by hand because it's usually in ObjectHandler.h
  xAOD::TEvent* m_event;
  ConfigStore* m_config;
  std::string m_containerName;

  // FIXME we need to have a way to access MET frmo elsewhere in CxAODMaker
  // This function may be temporary though, as the final API of this class may change when
  // MET rebuilding and systematics work
  xAOD::MissingET* getMET();

private:

  bool debug = true;

  //  // decorator defining non-standard object variables
  //  static METDecorator m_decorator;

  // MET utilities tool
  ToolHandle<IMETRebuilder> m_metutil;//!
  //met::METRebuilder* m_metutil;
  
  xAOD::MissingETContainer* m_METContainer;
  xAOD::MissingETAuxContainer* m_METContainerAux;

  // selection functions for single objects

  //EL::StatusCode calibrateCopies(
  //        xAOD::METContainer* particles,
  //        const CP::SystematicSet &sysSet);



  /** @brief Sets certain variables for the outMET.
    * @param inMET MET from m_inContainer, from which values are read.
    * @param outMET MET from m_outContainer for which values are set.
    * @param isSysVar Bool deciding if container holding outMET is a shallow copy.
    *
    *Called in function copyContainer that is implemented in the ObjectHandler.
    *In case isSysVar is true, variation dependent object variables are overwritten.
   */
  //virtual EL::StatusCode setVariables(xAOD::MET* inMET, xAOD::MET* outMET, bool isSysVar);
};
#endif

