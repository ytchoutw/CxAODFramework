#include "TupleReader/Tuple.h"

// ROOT includes
#include "TTree.h"
#include "TString.h"
Tuple::~Tuple() {;}

void Tuple::DefineBranches(TTree * tr) {

  // jets
  TString jetLabel="jet";
  if( block_label != "") jetLabel+="_"+block_label;
  TString jetIndex="n"+jetLabel;
  tr->Branch(jetIndex,  &njet, jetIndex+"/I");
  tr->Branch(jetLabel+"_E",  jet_E, jetLabel+ "_E["+jetIndex+"]/F");
  tr->Branch(jetLabel+"_pt", jet_pt,jetLabel+"_pt["+jetIndex+"]/F");
  tr->Branch(jetLabel+"_phi",jet_phi,jetLabel+"_phi["+jetIndex+"]/F");
  tr->Branch(jetLabel+"_eta",jet_eta,jetLabel+"_eta["+jetIndex+"]/F");
  tr->Branch(jetLabel+"_ind",jet_ind,jetLabel+"_ind["+jetIndex+"]/I");
  tr->Branch(jetLabel+"_truth",jet_truth,jetLabel+"_truth["+jetIndex+"]/I");
  //tr->Branch(jetLabel+"_passOR",jet_passOR,jetLabel+"_passOR["+jetIndex+"]/O");
  tr->Branch(jetLabel+"_isVetoJet",jet_isVetoJet,jetLabel+"_isVetoJet["+jetIndex+"]/O");
  tr->Branch(jetLabel+"_isSignal",jet_isSignal,jetLabel+"_isSignal["+jetIndex+"]/O");

  // fat jets
  TString fatJetLabel="fat";
  if( block_label != "") fatJetLabel+="_"+block_label;
  TString fatJetIndex="n"+fatJetLabel;
  tr->Branch(fatJetIndex, &nfat, fatJetIndex+"/I");
  tr->Branch(fatJetLabel+"_E",  fat_E, fatJetLabel+ "_E["+fatJetIndex+"]/F");
  tr->Branch(fatJetLabel+"_pt", fat_pt,fatJetLabel+"_pt["+fatJetIndex+"]/F");
  tr->Branch(fatJetLabel+"_phi",fat_phi,fatJetLabel+"_phi["+fatJetIndex+"]/F");
  tr->Branch(fatJetLabel+"_eta",fat_eta,fatJetLabel+"_eta["+fatJetIndex+"]/F");
  tr->Branch(fatJetLabel+"_ind",fat_ind,fatJetLabel+"_ind["+fatJetIndex+"]/I");
  // additional variables
  //tr->Branch(fatJetLabel+"_truth",fat_truth,jetLabel+"_truth["+fatJetIndex+"]/I");
  tr->Branch(fatJetLabel+"_jvf",fat_jvf,fatJetLabel+"_jvf["+fatJetIndex+"]/F");
  tr->Branch(fatJetLabel+"_tau21",fat_tau21,fatJetLabel+"_tau21["+fatJetIndex+"]/F");
  tr->Branch(fatJetLabel+"_tau32",fat_tau32,fatJetLabel+"_tau32["+fatJetIndex+"]/F");
  
  // muons
  TString muoLabel="muo";
  if( block_label != "") muoLabel+="_"+block_label;
  TString muoIndex="n"+muoLabel;
  tr->Branch(muoIndex,   &nmuo,  muoIndex+"/I");
  tr->Branch(muoLabel+"_E",  muo_E,  muoLabel+"_E["+muoIndex+"]/F");
  tr->Branch(muoLabel+"_pt" ,muo_pt, muoLabel+"_pt["+muoIndex+"]/F");
  tr->Branch(muoLabel+"_phi",muo_phi,muoLabel+"_phi["+muoIndex+"]/F");
  tr->Branch(muoLabel+"_eta",muo_eta,muoLabel+"_eta["+muoIndex+"]/F");
  tr->Branch(muoLabel+"_ind",muo_ind,muoLabel+"_ind["+muoIndex+"]/I");
  //tr->Branch(muoLabel+"_passSel",muo_passSel,muoLabel+"_passSel["+muoIndex+"]/O");
  //tr->Branch(muoLabel+"_passOR",muo_passOR,muoLabel+"_passOR["+muoIndex+"]/O");
  //tr->Branch(muoLabel+"_passedIDCuts",muo_passedIDCuts,muoLabel+"_passedIDCuts["+muoIndex+"]/O");
  // 
  tr->Branch(muoLabel+"_ptcone20",muo_ptcone20,muoLabel+"_ptcone20["+muoIndex+"]/F");
  tr->Branch(muoLabel+"_etcone30",muo_etcone30,muoLabel+"_etcone30["+muoIndex+"]/F");
  //tr->Branch(muoLabel+"_z0",muo_z0,muoLabel+"_z0["+muoIndex+"]/F");
  //tr->Branch(muoLabel+"_d0",muo_d0,muoLabel+"_d0["+muoIndex+"]/F");
  tr->Branch(muoLabel+"_type",muo_type,muoLabel+"_type["+muoIndex+"]/I");
  tr->Branch(muoLabel+"_isVHL",muo_isVHL,muoLabel+"_isVHL["+muoIndex+"]/O");
  tr->Branch(muoLabel+"_isZH",muo_isZH,muoLabel+"_isZH["+muoIndex+"]/O");
  tr->Branch(muoLabel+"_isWH",muo_isWH,muoLabel+"_isWH["+muoIndex+"]/O");
  
  TString tauLabel="tau";
  if( block_label != "") tauLabel+="_"+block_label;
  TString tauIndex="n"+tauLabel;
  tr->Branch(tauIndex,   &ntau,  tauIndex+"/I");
  tr->Branch(tauLabel+"_E",  tau_E,  tauLabel+"_E["+tauIndex+"]/F");
  tr->Branch(tauLabel+"_pt" ,tau_pt, tauLabel+"_pt["+tauIndex+"]/F");
  tr->Branch(tauLabel+"_phi",tau_phi,tauLabel+"_phi["+tauIndex+"]/F");
  tr->Branch(tauLabel+"_eta",tau_eta,tauLabel+"_eta["+tauIndex+"]/F");
  tr->Branch(tauLabel+"_ind",tau_ind,tauLabel+"_ind["+tauIndex+"]/I");

  TString eleLabel="ele";
  if( block_label != "") eleLabel+="_"+block_label;
  TString eleIndex="n"+eleLabel;
  tr->Branch(eleIndex,   &nele,  eleIndex+"/I");
  tr->Branch(eleLabel+"_E",  ele_E,  eleLabel+"_E["+eleIndex+"]/F");
  tr->Branch(eleLabel+"_pt" ,ele_pt, eleLabel+"_pt["+eleIndex+"]/F");
  tr->Branch(eleLabel+"_phi",ele_phi,eleLabel+"_phi["+eleIndex+"]/F");
  tr->Branch(eleLabel+"_eta",ele_eta,eleLabel+"_eta["+eleIndex+"]/F");
  tr->Branch(eleLabel+"_ind",ele_ind,eleLabel+"_ind["+eleIndex+"]/I");
  tr->Branch(eleLabel+"_passSel",ele_passSel,eleLabel+"_passSel["+eleIndex+"]/O");
  //tr->Branch(eleLabel+"_passOR",ele_passOR,eleLabel+"_passOR["+eleIndex+"]/O");
  
  // 
  tr->Branch(eleLabel+"_isVTLH"  ,ele_isVTLH,      eleLabel+"_isVTLH["  +eleIndex+"]/O");
  tr->Branch(eleLabel+"_isVHL"   ,ele_isVHL,       eleLabel+"_isVHL["   +eleIndex+"]/O");
  tr->Branch(eleLabel+"_isWH"    ,ele_isWH,        eleLabel+"_isWH["    +eleIndex+"]/O");  
  tr->Branch(eleLabel+"_isZH"    ,ele_isZH,        eleLabel+"_isZH["    +eleIndex+"]/O");
  tr->Branch(eleLabel+"_ptcone20",ele_ptcone20,    eleLabel+"_ptcone20["+eleIndex+"]/F");
  tr->Branch(eleLabel+"_etcone30",ele_topoetcone30,eleLabel+"_etcone30["+eleIndex+"]/F");

  // MC particles
  TString mcLabel="mc";
  if( block_label != "") mcLabel+="_"+block_label;
  TString mcIndex="n"+mcLabel;
  tr->Branch(mcIndex,   &nmc,  mcIndex+"/I");
  tr->Branch(mcLabel+"_E",  mc_e,  mcLabel+"_E["+mcIndex+"]/F");
  tr->Branch(mcLabel+"_px" ,mc_px, mcLabel+"_px["+mcIndex+"]/F");
  tr->Branch(mcLabel+"_py" ,mc_py, mcLabel+"_py["+mcIndex+"]/F");
  tr->Branch(mcLabel+"_pz" ,mc_pz, mcLabel+"_pz["+mcIndex+"]/F");
  tr->Branch(mcLabel+"_pvz" ,mc_pvz, mcLabel+"_pvz["+mcIndex+"]/F");
  tr->Branch(mcLabel+"_ind",mc_ind,mcLabel+"_ind["+mcIndex+"]/I");
  tr->Branch(mcLabel+"_pdg",mc_pdg,mcLabel+"_pdg["+mcIndex+"]/I");
  tr->Branch(mcLabel+"_status",mc_status,mcLabel+"_status["+mcIndex+"]/I");
  tr->Branch(mcLabel+"_barcode",mc_barcode,mcLabel+"_barcode["+mcIndex+"]/I");

  // event properties
  TString eveLabel="eve";
  if( block_label != "") eveLabel+="_"+block_label;
  tr->Branch(eveLabel+"_num",&eve_num,eveLabel+"_num/I");
  tr->Branch(eveLabel+"_run",&eve_run,eveLabel+"_run/I");
  tr->Branch(eveLabel+"_mc_num",&eve_mc_num,eveLabel+"_mc_num/I");
  tr->Branch(eveLabel+"_pvz",&eve_pvz,eveLabel+"_pvz/F");
  tr->Branch(eveLabel+"_nv3",&eve_nv3,eveLabel+"_nv3/I");
  tr->Branch(eveLabel+"_mc_chan",&eve_mc_chan,eveLabel+"_mc_chan/I");
  tr->Branch(eveLabel+"_mc_w",&eve_mc_w,eveLabel+"_mc_w/F");
  tr->Branch(eveLabel+"_isMC",&eve_isMC,eveLabel+"_isMC/O");
  // physics event properties
  TString metLabel="met";
  if( block_label != "") metLabel+="_"+block_label;
  tr->Branch(metLabel+"_px",&met_px,metLabel+"_px/F");
  tr->Branch(metLabel+"_py",&met_py,metLabel+"_py/F");
  tr->Branch(metLabel+"_pt",&met_pt,metLabel+"_pt/F");
  tr->Branch(metLabel+"_phi",&met_phi,metLabel+"_phi/F");
  tr->Branch(metLabel+"_sumET",&met_sumET,metLabel+"_sumET/F");
}

bool Tuple::ValidateBranches(TTree * tr) {

  // jets
  TString jetLabel="jet";
  if( block_label != "") jetLabel+="_"+block_label;
  TString jetIndex="n"+jetLabel;
  if(!tr->FindBranch(jetIndex)) { return false;}
  if(!tr->FindBranch(jetLabel+"_E")) { return false;}
  if(!tr->FindBranch(jetLabel+"_pt")) { return false;}
  if(!tr->FindBranch(jetLabel+"_phi")) { return false;}
  if(!tr->FindBranch(jetLabel+"_eta")) { return false;}
  if(!tr->FindBranch(jetLabel+"_ind")) { return false;}
  //if(!tr->FindBranch(jetLabel+"_good")) {return false;}
  //if(!tr->FindBranch(jetLabel+"_passOR")) {return false;}
  if(!tr->FindBranch(jetLabel+"_isVetoJet")) {return false;}
  if(!tr->FindBranch(jetLabel+"_isSignal")) { return false;}
  if(!tr->FindBranch(jetLabel+"_truth")) { return false;}
  
  // fat jets
  TString fatJetLabel="fat";
  if( block_label != "") fatJetLabel+="_"+block_label;
  TString fatJetIndex="n"+fatJetLabel;
  if(!tr->FindBranch(fatJetIndex)) { return false;}
  if(!tr->FindBranch(fatJetLabel+"_E")) { return false;}
  if(!tr->FindBranch(fatJetLabel+"_pt")) { return false;}
  if(!tr->FindBranch(fatJetLabel+"_phi")) { return false;}
  if(!tr->FindBranch(fatJetLabel+"_eta")) { return false;}
  if(!tr->FindBranch(fatJetLabel+"_ind")) { return false;}
  //if(!tr->FindBranch(fatJetLabel+"_truth")) { return false;}
  if(!tr->FindBranch(fatJetLabel+"_jvf")) { return false;}
  if(!tr->FindBranch(fatJetLabel+"_tau21")) { return false;}
  if(!tr->FindBranch(fatJetLabel+"_tau32")) { return false;}
  
  // muons
  TString muoLabel="muo";
  if( block_label != "") muoLabel+="_"+block_label;
  TString muoIndex="n"+muoLabel;
  if(!tr->FindBranch(muoIndex)) { return false;}
  if(!tr->FindBranch(muoLabel+"_E")) { return false;}
  if(!tr->FindBranch(muoLabel+"_pt")) { return false;}
  if(!tr->FindBranch(muoLabel+"_phi")) { return false;}
  if(!tr->FindBranch(muoLabel+"_eta")) { return false;}
  if(!tr->FindBranch(muoLabel+"_ind")) { return false;}
  if(!tr->FindBranch(muoLabel+"_passSel")) { return false;}
  //if(!tr->FindBranch(muoLabel+"_passOR")) { return false;}
  //if(!tr->FindBranch(muoLabel+"_passedIDCuts")) { return false;}
  if(!tr->FindBranch(muoLabel+"_type")) { return false;}
  //if(!tr->FindBranch(muoLabel+"_z0")) {return false;}
  //if(!tr->FindBranch(muoLabel+"_d0")) {return false;}
  if(!tr->FindBranch(muoLabel+"_ptcone20")) {return false;}
  if(!tr->FindBranch(muoLabel+"_etcone30"))  {return false;}
  if(!tr->FindBranch(muoLabel+"_type")) {return false;}
  if(!tr->FindBranch(muoLabel+"_isVHL")) {return false;}
  if(!tr->FindBranch(muoLabel+"_isZH")) {return false;}
  if(!tr->FindBranch(muoLabel+"_isWH")) {return false;}
  

  // electrons
  TString eleLabel="ele";
  if( block_label != "") eleLabel+="_"+block_label;
  TString eleIndex="n"+eleLabel;
  if(!tr->FindBranch(eleIndex)) { return false;}
  if(!tr->FindBranch(eleLabel+"_E")) { return false;}
  if(!tr->FindBranch(eleLabel+"_pt")) { return false;}
  if(!tr->FindBranch(eleLabel+"_phi")) { return false;}
  if(!tr->FindBranch(eleLabel+"_eta")) { return false;}
  if(!tr->FindBranch(eleLabel+"_ind")) { return false;}
  if(!tr->FindBranch(eleLabel+"_passSel")) { return false;}
  //if(!tr->FindBranch(eleLabel+"_passOR")) { return false;}

  if(!tr->FindBranch(eleLabel+"_ptcone20")) { return false;}
  if(!tr->FindBranch(eleLabel+"_etcone30")) { return false;}
  if(!tr->FindBranch(eleLabel+"_isVTLH"  )) { return false;}
  if(!tr->FindBranch(eleLabel+"_isVHL"   )) { return false;}
  if(!tr->FindBranch(eleLabel+"_isWH"    )) { return false;}
  if(!tr->FindBranch(eleLabel+"_isZH"    )) { return false;}

  // taus
  TString tauLabel="tau";
  if( block_label != "") tauLabel+="_"+block_label;
  TString tauIndex="n"+tauLabel;
  if(!tr->FindBranch(tauIndex)) { return false;}
  if(!tr->FindBranch(tauLabel+"_E")) { return false;}
  if(!tr->FindBranch(tauLabel+"_pt")) { return false;}
  if(!tr->FindBranch(tauLabel+"_phi")) { return false;}
  if(!tr->FindBranch(tauLabel+"_eta")) { return false;}
  if(!tr->FindBranch(tauLabel+"_ind")) { return false;}
  // MC particles
  TString mcLabel = "mc";
  if( block_label != "") mcLabel+="_"+block_label;
  TString mcIndex = "n"+mcLabel;
  if(!tr->FindBranch(mcIndex)) { return false;}
  if(!tr->FindBranch(mcLabel+"_E")){return false;}
  if(!tr->FindBranch(mcLabel+"_px")){return false;}
  if(!tr->FindBranch(mcLabel+"_py")){return false;}
  if(!tr->FindBranch(mcLabel+"_pz")){return false;}
  if(!tr->FindBranch(mcLabel+"_pvz")){return false;}
  if(!tr->FindBranch(mcLabel+"_ind")){return false;}
  if(!tr->FindBranch(mcLabel+"_pdg")){return false;}
  if(!tr->FindBranch(mcLabel+"_status")){return false;}
  if(!tr->FindBranch(mcLabel+"_barcode")){return false;}
  // event properties
  TString eveLabel="eve";
  if( block_label != "") eveLabel+="_"+block_label;
  if(!tr->FindBranch(eveLabel+"_num")) { return false;}
  if(!tr->FindBranch(eveLabel+"_run")) { return false;}
  if(!tr->FindBranch(eveLabel+"_mc_num")) {return false;}
  if(!tr->FindBranch(eveLabel+"_pvz")) {return false;}
  if(!tr->FindBranch(eveLabel+"_nv3")) {return false;}
  if(!tr->FindBranch(eveLabel+"_mc_chan")) {return false;}
  if(!tr->FindBranch(eveLabel+"_mc_w")) {return false;}
  if(!tr->FindBranch(eveLabel+"_isMC")) {return false;}
  // physics event properties
  TString metLabel="met";
  if( block_label != "") metLabel+="_"+block_label;
  if(!tr->FindBranch(metLabel+"_px")) {return false;}
  if(!tr->FindBranch(metLabel+"_py")) {return false;}
  if(!tr->FindBranch(metLabel+"_pt")) {return false;}
  if(!tr->FindBranch(metLabel+"_phi")) {return false;}
  if(!tr->FindBranch(metLabel+"_sumET")) {return false;}
  
  return true;
}

// this might not be a good idea...
// since all it does is hide the error message from TTree:SetBranchAddress
// 
template <class T> void Tuple::SetBranchAddressSafe(TTree * tr, const char * label, T * var) {
  if( tr->GetBranch(label) ) {
    tr->SetBranchAddress(label,var);
  }
}


void Tuple::SetBranchAddresses(TTree * tr) {
  TString jetLabel = "jet";
  if( block_label != "") 
    jetLabel += "_"+block_label;
  TString jetIndex = "n"+jetLabel;
  SetBranchAddressSafe(tr,jetIndex,&njet);
  SetBranchAddressSafe(tr,jetLabel+"_E",jet_E);
  SetBranchAddressSafe(tr,jetLabel+"_pt",jet_pt);
  SetBranchAddressSafe(tr,jetLabel+"_phi",jet_phi);
  SetBranchAddressSafe(tr,jetLabel+"_eta",jet_eta);
  SetBranchAddressSafe(tr,jetLabel+"_ind",jet_ind);
  SetBranchAddressSafe(tr,jetLabel+"_truth",jet_truth);
  //SetBranchAddressSafe(tr,jetLabel+"_good",jet_good);
  //SetBranchAddressSafe(tr,jetLabel+"_passOR",jet_passOR);
  SetBranchAddressSafe(tr,jetLabel+"_isVetoJet",jet_isVetoJet);
  SetBranchAddressSafe(tr,jetLabel+"_isSignal",jet_isSignal);

  TString fatJetLabel = "fat";
  if( block_label != "")
    fatJetLabel += "_"+block_label;
  TString fatJetIndex = "n"+fatJetLabel;
  SetBranchAddressSafe(tr,fatJetIndex,&nfat);
  SetBranchAddressSafe(tr,fatJetLabel+"_E",fat_E);
  SetBranchAddressSafe(tr,fatJetLabel+"_pt",fat_pt);
  SetBranchAddressSafe(tr,fatJetLabel+"_phi",fat_phi);
  SetBranchAddressSafe(tr,fatJetLabel+"_eta",fat_eta);
  SetBranchAddressSafe(tr,fatJetLabel+"_ind",fat_ind);
  //SetBranchAddressSafe(tr,fatJetLabel+"_truth",fat_truth);
  SetBranchAddressSafe(tr,fatJetLabel+"_jvf",fat_jvf);
  SetBranchAddressSafe(tr,fatJetLabel+"_tau21",fat_tau21);
  SetBranchAddressSafe(tr,fatJetLabel+"_tau32",fat_tau32);

  TString muoLabel ="muo";
  if( block_label != "") 
    muoLabel += "_"+block_label;
  TString muoIndex = "n"+muoLabel;
  SetBranchAddressSafe(tr,muoIndex,&nmuo);
  SetBranchAddressSafe(tr,muoLabel+"_E",muo_E);
  SetBranchAddressSafe(tr,muoLabel+"_pt",muo_pt);
  SetBranchAddressSafe(tr,muoLabel+"_phi",muo_phi);
  SetBranchAddressSafe(tr,muoLabel+"_eta",muo_eta);
  SetBranchAddressSafe(tr,muoLabel+"_ind",muo_ind);

  //SetBranchAddressSafe(tr,muoLabel+"_passSel",muo_passSel);
  //SetBranchAddressSafe(tr,muoLabel+"_passOR",muo_passOR);
  //SetBranchAddressSafe(tr,muoLabel+"_passedIDCuts",muo_passedIDCuts);
  SetBranchAddressSafe(tr,muoLabel+"_ptcone20",muo_ptcone20);
  SetBranchAddressSafe(tr,muoLabel+"_etcone30",muo_etcone30);
  //SetBranchAddressSafe(tr,muoLabel+"_z0",muo_z0);
  //SetBranchAddressSafe(tr,muoLabel+"_d0",muo_d0);
  SetBranchAddressSafe(tr,muoLabel+"_type",muo_type);
  SetBranchAddressSafe(tr,muoLabel+"_isVHL",muo_isVHL);
  SetBranchAddressSafe(tr,muoLabel+"_isZH",muo_isZH);
  SetBranchAddressSafe(tr,muoLabel+"_isWH",muo_isWH);

  TString eleLabel ="ele";
  if( block_label != "") 
    eleLabel += "_"+block_label;
  TString eleIndex = "n"+eleLabel;
  SetBranchAddressSafe(tr,eleIndex,&nele);
  SetBranchAddressSafe(tr,eleLabel+"_E",ele_E);
  SetBranchAddressSafe(tr,eleLabel+"_pt",ele_pt);
  SetBranchAddressSafe(tr,eleLabel+"_phi",ele_phi);
  SetBranchAddressSafe(tr,eleLabel+"_eta",ele_eta);
  // Decorations here
  SetBranchAddressSafe(tr,eleLabel+"_ind",ele_ind);
  SetBranchAddressSafe(tr,eleLabel+"_passSel",ele_passSel);
  //SetBranchAddressSafe(tr,eleLabel+"_passOR",ele_passOR);
  //
  SetBranchAddressSafe(tr,eleLabel+"_ptcone20",ele_ptcone20);
  SetBranchAddressSafe(tr,eleLabel+"_etcone30",ele_topoetcone30);
  SetBranchAddressSafe(tr,eleLabel+"_isVTLH",ele_isVTLH);
  SetBranchAddressSafe(tr,eleLabel+"_isVHL",ele_isVHL);
  SetBranchAddressSafe(tr,eleLabel+"_isWH",ele_isWH);
  SetBranchAddressSafe(tr,eleLabel+"_isZH",ele_isZH);
  //
  TString tauLabel ="tau";
  if( block_label != "") 
    tauLabel += "_"+block_label;
  TString tauIndex = "n"+tauLabel;
  SetBranchAddressSafe(tr,tauIndex,&ntau);
  SetBranchAddressSafe(tr,tauLabel+"_E",tau_E);
  SetBranchAddressSafe(tr,tauLabel+"_pt",tau_pt);
  SetBranchAddressSafe(tr,tauLabel+"_phi",tau_phi);
  SetBranchAddressSafe(tr,tauLabel+"_eta",tau_eta);
  SetBranchAddressSafe(tr,tauLabel+"_ind",tau_ind);

  //
  TString mcLabel="mc";
  if( block_label != "")
    mcLabel+="_"+block_label;
  TString mcIndex="n"+mcLabel;
  SetBranchAddressSafe(tr,mcIndex,&nmc);
  SetBranchAddressSafe(tr,mcLabel+"_E",mc_e);
  SetBranchAddressSafe(tr,mcLabel+"_px",mc_px);
  SetBranchAddressSafe(tr,mcLabel+"_py",mc_py);
  SetBranchAddressSafe(tr,mcLabel+"_pz",mc_pz);
  SetBranchAddressSafe(tr,mcLabel+"_pvz",mc_pvz);
  SetBranchAddressSafe(tr,mcLabel+"_ind",mc_ind);
  SetBranchAddressSafe(tr,mcLabel+"_pdg",mc_pdg);
  SetBranchAddressSafe(tr,mcLabel+"_status",mc_status);
  SetBranchAddressSafe(tr,mcLabel+"_barcode",mc_barcode);
  
  TString eveLabel="eve";
  if( block_label != "") 
    eveLabel +="_"+block_label;
  SetBranchAddressSafe(tr,eveLabel+"_num",&eve_num);
  SetBranchAddressSafe(tr,eveLabel+"_run",&eve_run);
  SetBranchAddressSafe(tr,eveLabel+"_mc_num",&eve_mc_num);
  SetBranchAddressSafe(tr,eveLabel+"_pvz",&eve_pvz);
  SetBranchAddressSafe(tr,eveLabel+"_nv3",&eve_nv3);
  SetBranchAddressSafe(tr,eveLabel+"_mc_chan",&eve_mc_chan);
  SetBranchAddressSafe(tr,eveLabel+"_mc_w",&eve_mc_w);
  SetBranchAddressSafe(tr,eveLabel+"_isMC",&eve_isMC);


  TString metLabel="met";
  if( block_label != "") 
    metLabel +="_"+block_label;
  SetBranchAddressSafe(tr,metLabel+"_px",&met_px);
  SetBranchAddressSafe(tr,metLabel+"_py",&met_py);
  SetBranchAddressSafe(tr,metLabel+"_pt",&met_pt);
  SetBranchAddressSafe(tr,metLabel+"_phi",&met_phi);
  SetBranchAddressSafe(tr,metLabel+"_sumET",&met_sumET);
}


