#ifndef _TUPLE_HPP_
#define _TUPLE_HPP_

#include <string>

class TTree;
// this is really a struct
// and as such just a simple holder for the data
class Tuple {
 public:
 Tuple(const std::string & block_label="") : block_label(block_label) 
  {
    reset();
  }


  ~Tuple();

  const static int MAXJETS=10;
  const static int MAXFATJETS=10;
  const static int MAXMUONS=10;
  const static int MAXELECTRONS=10;
  const static int MAXTAUS=10;
  const static int MAXMC=10;

  void  reset() {
  njet =0;
  nfat =0;
  nmuo=0;
  nele=0;
  ntau=0;
  nmc=0;
  eve_num=0;
  eve_run=0;
  eve_mc_num=0;
  eve_pvz=0;
  eve_nv3=0;
  eve_mc_chan=0;
  eve_mc_w=0;
  eve_mu=0;
  eve_isMC=false;
  eve_passGRL=true;
  eve_isCleanEvent=true;
  met_px=0;
  met_py=0;
  met_pt=0;
  met_phi=0;
  met_sumET=0;
  eve_isMC=true;
  }

  //
  int njet;
  float jet_E[MAXJETS];
  float jet_pt[MAXJETS];
  float jet_phi[MAXJETS];
  float jet_eta[MAXJETS];
  int jet_ind[MAXJETS];
  // add other jet properties here
  //bool jet_passOR[MAXJETS];
  bool jet_isVetoJet[MAXJETS];
  bool jet_isSignal[MAXJETS];
  int jet_truth[MAXJETS];
  //
  int nfat;
  float fat_E[MAXFATJETS];
  float fat_pt[MAXFATJETS];
  float fat_phi[MAXFATJETS];
  float fat_eta[MAXFATJETS];
  int fat_ind[MAXFATJETS];
  // add other fat jet properties here
  //int fat_truth[MAXFATJETS];
  float fat_tau21[MAXFATJETS];
  float fat_tau32[MAXFATJETS];
  float fat_jvf[MAXFATJETS];
  //
  int nmuo;
  float muo_E[MAXMUONS];
  float muo_pt[MAXMUONS];
  float muo_phi[MAXMUONS];
  float muo_eta[MAXMUONS];
  int muo_ind[MAXMUONS];
  //bool muo_passOR[MAXMUONS];
  // add other muon properties here
  bool muo_isVHL[MAXMUONS];
  bool muo_isZH[MAXMUONS];
  bool muo_isWH[MAXMUONS];
  int muo_type[MAXMUONS];
  float muo_ptcone20[MAXMUONS];
  float muo_etcone30[MAXMUONS];

  int nele;
  float ele_E[MAXELECTRONS];
  float ele_pt[MAXELECTRONS];
  float ele_phi[MAXELECTRONS];
  float ele_eta[MAXELECTRONS];
  int ele_ind[MAXELECTRONS];
  bool ele_passSel[MAXELECTRONS];
  //bool ele_passOR[MAXELECTRONS];
  // add other electron properties here for now - eventually this should be pruned
  bool ele_isVTLH[MAXELECTRONS];
  bool ele_isVHL[MAXELECTRONS];
  bool ele_isZH[MAXELECTRONS];
  bool ele_isWH[MAXELECTRONS];
  //float ele_ideff[MAXELECTRONS];
  float ele_ptcone20[MAXELECTRONS];
  float ele_topoetcone30[MAXELECTRONS];

  int ntau;
  float tau_E[MAXTAUS];
  float tau_pt[MAXTAUS];
  float tau_phi[MAXTAUS];
  float tau_eta[MAXTAUS];
  int tau_ind[MAXTAUS];
  
  // add other tau properties here


  // MC Truth particles
  int nmc;
  float mc_px[MAXMC];
  float mc_py[MAXMC];
  float mc_pz[MAXMC];
  float mc_e[MAXMC];
  float mc_pvz[MAXMC];
  int mc_ind[MAXMC];
  int mc_pdg[MAXMC];
  int mc_status[MAXMC];
  int mc_barcode[MAXMC];
  
  //  int nvtx;
  //float vtx_x[MAXVERTICES];
  //float vtx_y[MAXVERTICES];
  //float vtx_z[MAXVERTICES];
  // add other vertex properties here
  
  // Event level properties
  int eve_num;
  int eve_run;
  float eve_mu;
  float eve_pvz;

  bool eve_isMC;
  bool eve_passGRL;
  bool eve_isCleanEvent;
  int  eve_nv3;
  float eve_mc_w;
  int eve_mc_num;
  int eve_mc_chan;
  
  // Event level physics properties
  float met_px;
  float met_py;
  float met_pt;
  float met_phi;
  float met_sumET;
  
  void DefineBranches(TTree * tr); // could also take some extra parameters to define different versions of the output
  bool ValidateBranches(TTree * tr); // check that the tree passed as an argument has the correct branches
  void SetBranchAddresses(TTree * tr);
  
 private:

  template<class T> void SetBranchAddressSafe(TTree * tr, const char * label, T * var);

  std::string block_label; // this could be, for example, used to put variations into the same tree

  
};
#endif // _TUPLE_HPP
