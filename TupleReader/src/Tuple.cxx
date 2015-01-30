#include "TupleReader/Tuple.h"

// ROOT includes
#include "TTree.h"

Tuple::Tuple() {
  njet = 0;
  nfat = 0;
  nmuo=0;
  nele=0;
  nvtx=0;
  eve_num=0;
  eve_run=0;
  phy_met=0;
  phy_ht=0;
}

Tuple::~Tuple() {;}

void Tuple::DefineBranches(TTree * tr) {

  // jets
  tr->Branch("njet",  &njet, "njet/I");
  tr->Branch("jet_E",  jet_E,  "jet_E[njet]/F");
  tr->Branch("jet_pt", jet_pt, "jet_pt[njet]/F");
  tr->Branch("jet_phi",jet_phi,"jet_phi[njet]/F");
  tr->Branch("jet_eta",jet_eta,"jet_eta[njet]/F");

  // fat jets
  tr->Branch("nfat",  &nfat, "nfat/I");
  tr->Branch("fat_E",  fat_E,  "fat_E[nfat]/F");
  tr->Branch("fat_pt", fat_pt, "fat_pt[nfat]/F");
  tr->Branch("fat_phi",fat_phi,"fat_phi[nfat]/F");
  tr->Branch("fat_eta",fat_eta,"fat_eta[nfat]/F");

  // muons
  tr->Branch("nmuo",   &nmuo,  "nmuo/I");
  tr->Branch("muo_E",  muo_E,  "muo_E[nmuo]/F");
  tr->Branch("muo_pt" ,muo_pt, "muo_pt[nmuo]/F");
  tr->Branch("muo_phi",muo_phi,"muo_phi[nmuo]/F");
  tr->Branch("muo_eta",muo_eta,"muo_eta[nmuo]/F");
  
  // electrons
  tr->Branch("nele",   &nele,  "nele/I");
  tr->Branch("ele_E",  ele_E,  "ele_E[nele]/F");
  tr->Branch("ele_pt", ele_pt, "ele_pt[nele]/F");
  tr->Branch("ele_phi",ele_phi,"ele_phi[nele]/F");
  tr->Branch("ele_eta",ele_eta,"ele_eta[nele]/F");
  
  // taus
  tr->Branch("ntau",   &ntau,  "ntau/I");
  tr->Branch("tau_E",  tau_E,  "tau_E[ntau]/F");
  tr->Branch("tau_pt", tau_pt, "tau_pt[ntau]/F");
  tr->Branch("tau_phi",tau_phi,"tau_phi[ntau]/F");
  tr->Branch("tau_eta",tau_eta,"tau_eta[ntau]/F");

  // vertices
  tr->Branch("nvtx",   &nvtx,  "nvtx/I");
  tr->Branch("vtx_x",  vtx_x,  "vtx_x[nvtx]/F");
  tr->Branch("vtx_y", vtx_y, "vtx_y[nvtx]/F");
  tr->Branch("vtx_z",vtx_z,"vtx_z[nvtx]/F");

  // event properties

  tr->Branch("eve_num",&eve_num,"eve_num/I");
  tr->Branch("eve_run",&eve_run,"eve_run/I");
  
  // physics event properties

  tr->Branch("phy_met",&phy_met,"phy_met/F");
  tr->Branch("phy_ht",&phy_ht,"phy_ht/F");
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
  SetBranchAddressSafe(tr,"njet",&njet);
  SetBranchAddressSafe(tr,"jet_E",jet_E);
  SetBranchAddressSafe(tr,"jet_pt",jet_pt);
  SetBranchAddressSafe(tr,"jet_phi",jet_phi);
  SetBranchAddressSafe(tr,"jet_eta",jet_eta);

  SetBranchAddressSafe(tr,"nfat",&nfat);
  SetBranchAddressSafe(tr,"fat_E",fat_E);
  SetBranchAddressSafe(tr,"fat_pt",fat_pt);
  SetBranchAddressSafe(tr,"fat_phi",fat_phi);
  SetBranchAddressSafe(tr,"fat_eta",fat_eta);

  SetBranchAddressSafe(tr,"nmuo",&nmuo);
  SetBranchAddressSafe(tr,"muo_E",muo_E);
  SetBranchAddressSafe(tr,"muo_pt",muo_pt);
  SetBranchAddressSafe(tr,"muo_phi",muo_phi);
  SetBranchAddressSafe(tr,"muo_eta",muo_eta);

  SetBranchAddressSafe(tr,"nele",&nele);
  SetBranchAddressSafe(tr,"ele_E",ele_E);
  SetBranchAddressSafe(tr,"ele_pt",ele_pt);
  SetBranchAddressSafe(tr,"ele_phi",ele_phi);
  SetBranchAddressSafe(tr,"ele_eta",ele_eta);

  SetBranchAddressSafe(tr,"ntau",&ntau);
  SetBranchAddressSafe(tr,"tau_E",tau_E);
  SetBranchAddressSafe(tr,"tau_pt",tau_pt);
  SetBranchAddressSafe(tr,"tau_phi",tau_phi);
  SetBranchAddressSafe(tr,"tau_eta",tau_eta);

  SetBranchAddressSafe(tr,"nvtx",&nvtx);
  SetBranchAddressSafe(tr,"vtx_x",vtx_x);
  SetBranchAddressSafe(tr,"vtx_y",vtx_y);
  SetBranchAddressSafe(tr,"vtx_z",vtx_z);

  SetBranchAddressSafe(tr,"eve_num",&eve_num);
  SetBranchAddressSafe(tr,"eve_run",&eve_run);

  SetBranchAddressSafe(tr,"phy_met",&phy_met);
  SetBranchAddressSafe(tr,"phy_ht",&phy_ht);
}


