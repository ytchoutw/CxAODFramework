#ifndef CxAODReader_AnalysisReader_H
#define CxAODReader_AnalysisReader_H

#include <EventLoop/Algorithm.h>

// Infrastructure include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"

#ifndef __MAKECINT__
#include "CxAODTools/SuperDecorator.h"
#include "CxAODTools/VHbb0lepEvtSelection.h"
#include "CxAODTools/VHbb1lepEvtSelection.h"
#include "CxAODTools/VHbb2lepEvtSelection.h"
#include "CxAODTools/VBFbbAEvtSelection.h"
#include "CxAODTools/OverlapRemoval.h"
#include "CxAODTools/XSectionProvider.h"
#include "CxAODTools/sumOfWeightsProvider.h"
#endif // not __MAKECINT__

#include <TH1F.h>



class AnalysisReader : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  // float cutValue;

  xAOD::TEvent *m_event;  //!

  enum Type {e0Lep, e1Lep, e2Lep, VBFa, monoWZH};

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
  // Tree *myTree; //!
  // TH1 *myHist; //!



  // this is a standard constructor
  AnalysisReader ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  void SetAnalysisType(int analysistype) {m_analysisType=analysistype;}
  int GetAnalysisType() {return m_analysisType;}

  void SetCOMEnergy(TString com) {m_comEnergy=com;}

 private:
  EL::StatusCode histInitialize_0Lep();
  EL::StatusCode histInitialize_1Lep();
  EL::StatusCode histInitialize_2Lep();
  EL::StatusCode histInitialize_VBFa();
  EL::StatusCode histInitialize_monoWZH();
  EL::StatusCode fill_0Lep();
  EL::StatusCode fill_1Lep();
  EL::StatusCode fill_2Lep();
  EL::StatusCode fill_VBFa();
  EL::StatusCode fill_monoWZH();

  EL::StatusCode bTaggerHists(int bookfill, const xAOD::Jet *jet=0);


  int m_analysisType;
  int m_eventCounter; //!
  bool m_isMC; //!
  float m_weight; //!
  float m_sumOfWeights; //!  correct for the luminosity of the MC file
  TString m_comEnergy; 
  bool m_isSherpaVJets; // is Sherpa file
  bool m_isSherpaPt0VJets; //! is present sample SherpaVJets Pt0
  float m_SherpaPt0VJetsCut; //! cut Pt0 events overlapping with other PtV slices

  
  //  TH1F* m_hist_0lep_; //!
  //monoWZH hists
  //pre-selection
  TH1F* m_hist_mono_pre_MET; //!
  TH1F* m_hist_mono_pre_METPhi; //!
  TH1F* m_hist_mono_pre_Nfatjet; //!
  TH1F* m_hist_mono_pre_fatjetm; //!
  TH1F* m_hist_mono_pre_fatjetpt; //! 
  TH1F* m_hist_mono_pre_fatjeteta; //! 
  TH1F* m_hist_mono_pre_jetm; //!
  TH1F* m_hist_mono_pre_jetpt; //!
  TH1F* m_hist_mono_pre_jeteta; //!
  //cutflow
  TH1F* m_hist_mono_cutflow; //!
  TH1F* m_hist_mono_cutflow_fjet_MET; //!
  TH1F* m_hist_mono_cutflow_jetveto_MET; //!
  TH1F* m_hist_mono_cutflow_met_MET; //!
  TH1F* m_hist_mono_cutflow_mj_MET; //!
  TH1F* m_hist_mono_cutflow_Nsigfjet; //!
  TH1F* m_hist_mono_cutflow_fjetaddjetDeltaR; //!
    //monoWZH n-1
  TH1F* m_hist_nminusone_fjet; //!
  TH1F* m_hist_nminusone_jetveto; //!
  TH1F* m_hist_nminusone_met; //!
  TH1F* m_hist_nminusone_mj; //!
  TH1F* m_hist_mono_eff_MET; //!
  // 0 lep hists
  TH1F* m_hist2j_0lep_dRBB; //!
  TH1F* m_hist2j_0lep_dEtaBB; //!
  TH1F* m_hist2j_0lep_dPhiVBB; //!
  TH1F* m_hist2j_0lep_mBB; //!
  TH1F* m_hist2j_0lep_MEff; //!
  TH1F* m_hist2j_0lep_pTB1; //!
  TH1F* m_hist2j_0lep_pTB2; //!
  TH1F* m_hist2j_0lep_MET; //!
  //
  TH1F* m_hist3j_0lep_dRBB; //!
  TH1F* m_hist3j_0lep_dEtaBB; //!
  TH1F* m_hist3j_0lep_dPhiVBB; //!
  TH1F* m_hist3j_0lep_mBB; //!
  TH1F* m_hist3j_0lep_MEff3; //!
  TH1F* m_hist3j_0lep_pTB1; //!
  TH1F* m_hist3j_0lep_pTB2; //!
  TH1F* m_hist3j_0lep_MET; //!
  TH1F* m_hist3j_0lep_MBBJ; //!
  TH1F* m_hist3j_0lep_pTJ3; //!

  // 1 lep hists
  //  TH1F* m_hist_1lep_; //!
  TH1F* m_hist_1lep_NJets; //!
  TH1F* m_hist_1lep_j1Pt; //!
  TH1F* m_hist_1lep_fatJetPt; //!
  TH1F* m_hist_1lep_fatJetm; //!
  
  // 2 lep hists
  TH1F* m_hist_2lep_ZPV; //!
  TH1F* m_hist_2lep_MET; //!
  TH1F* m_hist_2lep_NJets; //!
  TH1F* m_hist_2lep_Mmumu; //!
  TH1F* m_hist_2lep_Mee; //!
  TH1F* m_hist_2lep_PtJets; //!
  TH1F* m_hist_2lep_EtaJets; //!
  TH1F* m_hist_2lep_DPhiJets; //!
  TH1F* m_hist_2lep_PtZ; //!
  TH1F* m_hist_2lep_PtZee; //!
  TH1F* m_hist_2lep_PtZmumu; //!

  TH1F* m_hist_2lep_CutFlowMu; //!
  TH1F* m_hist_2lep_CutFlowMu_noWght; //!  unweighted version

  // general histograms
  TH1F* m_hist_VPtTruth; //!
  
  // b-tagging histograms. Maps and TStrings are flavour of the month
  std::map<TString, TH1F*> m_hist_taggers;

  // VBFa hists
  // TH1F* m_hist_VBFa_; //!
  
  
  
  
  //  DerivEffProvider* m_derivEffProvider; //!


#ifndef __MAKECINT__
  SuperDecorator m_superDecorator;//!
  VHbb0lepEvtSelection* m_zerolepSel;//!
  VHbb1lepEvtSelection* m_onelepSel;//!
  VHbb2lepEvtSelection* m_twolepSel;//!
  VBFbbAEvtSelection* m_VBFaSel;//!
  OverlapRemoval* m_overlapRemoval; //!
  XSectionProvider* m_xSection; //!
  sumOfWeightsProvider* m_sumOfWeights_fix; //!
#endif // not __MAKECINT_

  // this is needed to distribute the algorithm to the workers
  ClassDef(AnalysisReader, 1);
};

#endif
