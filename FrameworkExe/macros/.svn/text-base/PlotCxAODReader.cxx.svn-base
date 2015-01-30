#include <iostream>
#include <TString.h>
#include <TH1F.h>
#include <TFile.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TRandom.h>
#include <iostream>
#include <fstream>
#include <vector>
//
#include "AtlasStyle.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/Sample.h"
#include "CxAODTools/DerivEffProvider.h"

// Anything global gets an m_

// directory for plots - must exist!
TString m_outdir("plots_common");

//
std::string m_subDir;  // submitDir where histograms are stored
// sample handler to read back histograms
SH::SampleHandler m_sh;
// sample normalisations
map<string, float > m_sampleLumiWeight;
// run/lumi map and total
std::map<int, float> m_lumi;
float m_tot_datalumi;
// scale the MC normalisation 
float m_scaleMC_inputs=1.0;

// Analysis type (NEW!)
int m_leptype=2;

// NEW!
bool makePseudoData=true;

TCanvas* m_canv;

void PlotCxAODReader(const std::string& submitDir="submitDir");
//
void fillLumiMap();
float calcLumi();
bool ReadSamples(); // set up normalisation of samples
void MakeInputs();
void PlotHists(std::string histName, TString tit="",float xmin=0,float xmax=0);

void PlotVptTruth(TString samplename);
void PlotBTaggers(TString samplename);

using namespace std;


void PlotCxAODReader(const std::string& submitDir) {

  AtlasStyle astyle=AtlasStyle();
 
  m_subDir=submitDir;

  // lumi from Run-I
  //  m_tot_datalumi=calcLumi();
  //  m_tot_datalumi=20257.8; // 0-lepton run1
  m_tot_datalumi = 1000; // 13TeV example

  bool readSamples=ReadSamples();
  if (!readSamples) {
    cout << " No samples found in: " << m_subDir << " , please check " << endl;
    return;
  }
  MakeInputs();

  // plots useful for all channels
  m_canv= new TCanvas();
  m_canv->Draw();
  m_canv->SetLogy(0);

  PlotVptTruth("ZeeL");
  PlotVptTruth("ZeeC");
  PlotVptTruth("ZeeB");

  PlotBTaggers("ttbar");

  // for quick plots
  //  PlotHists("Njets","Number of signal jets; N^{sig}_{Jets}; Jets");
  // PlotHists("Mmumu");
  
  

}

void PlotVptTruth(TString samplename) {

  // make Vpt truth plot for sample samplename
  SH::Sample *sample = m_sh.get(samplename.Data());
  if (!sample) return;
  TH1* vpthist=(TH1*)sample->readHist("VptTruth");
  if(!vpthist) return;
  vpthist->SetTitle(samplename);
  vpthist->Draw();
  TString outstem(m_outdir+"/VPtTruth."+samplename);
  m_canv->Print(outstem+".eps");
  m_canv->SetLogy(1);
  m_canv->Print(outstem+".Log.eps");
  m_canv->SetLogy(0);
}


void PlotBTaggers(TString samplename) {

  // tagger plots - just one sample at a time
  SH::Sample* sample=m_sh.get(samplename.Data());
  TString taggers[6]={"SV1_IP3D","MV1","MV2c00","MV2c10","MV2c20","MVb"};
  TString flavs[3]={" L"," C"," B"};
  TH1* hists[3];
  TLegend* leg=new TLegend(0.7,0.7,0.9,0.9);//,NULL,"brNDC");
  leg->SetLineColor(0);
  leg->SetLineStyle(0);
  leg->SetLineWidth(1);
  leg->SetFillColor(10);
  leg->SetFillStyle(1001);
  leg->SetBorderSize(0);

  bool first=true;
  for (auto &tagger : taggers) {
    TString hbasename(tagger);
    float maxhist=-999;
    int maxindex=-1;
    for (int flav(0) ; flav<3 ; ++flav) {
      TString hname(hbasename); 
      hname+=flavs[flav];
      std::string fullname("Taggers/"+hname);
      TH1* hist=(TH1*)sample->readHist(fullname);
      if (!hist) {
	cout << " No histogram found with name " << fullname << endl;
       break;
      }
      hist->SetMarkerSize(0);
      if (flavs[flav]==" C") {hist->SetLineColor(kBlue);} 
      if (flavs[flav]==" B") hist->SetLineColor(kRed); 
      hists[flav]=hist;
      if(hist->GetMaximum() > maxhist) {
	maxhist=hist->GetMaximum(); 
	maxindex=flav;
      }
    }
    
    // plot maximum first
    if (maxindex<0) continue;
    hists[maxindex]->GetXaxis()->SetTitle(hbasename);
    hists[maxindex]->Draw("hist");
    hists[maxindex]->Draw("same");
    for (int flav(0) ; flav<3 ; ++flav) {
      if (flav==maxindex) continue;
      hists[flav]->Draw("same hist");
      hists[flav]->Draw("same");
    }

    if (first) {
      leg->AddEntry(hists[0],"L","l");
      leg->AddEntry(hists[1],"C","l");
      leg->AddEntry(hists[2],"B","l");
      first=false;
    }
    leg->Draw();
    TString plotstem(m_outdir+"/"+hbasename);
    m_canv->Print(plotstem+".eps");	
    m_canv->SetLogy(1);
    m_canv->Print(plotstem+".Log.eps");	

    // normalised
    m_canv->SetLogy(0);
    hists[maxindex]->GetYaxis()->SetTitle("Normalized");
    hists[maxindex]->DrawNormalized("hist");
    hists[maxindex]->DrawNormalized("same");
    for (int flav(0) ; flav<3 ; ++flav) {
      if (flav==maxindex) continue;
      hists[flav]->DrawNormalized("same hist");
      hists[flav]->DrawNormalized("same");
    }
    leg->Draw();
    m_canv->Print(plotstem+".Norm.eps");	
    m_canv->SetLogy(1);
    m_canv->Print(plotstem+".Norm.Log.eps");	
  }
}


bool ReadSamples() {

  //
  // Read samples from submit directory, normalise to data lumi 
  //
  std::cout << " m_subDir is: " << m_subDir << std::endl;

  // open sample handler in directory
  std::string dir(m_subDir);
  if (gSystem->OpenDirectory(dir.c_str())) {
    std::cout << " load " << dir  << std::endl;
    m_sh.load (dir + "/hist");
    m_sh.print();
  } else {
    cout << " ReadSamples, no directory existing, please check: " << dir << endl;
    return false;
  }

  int ndatasets=m_sh.size(); // number of sample handler datasets

  cout << " Found " << ndatasets  << " datasets " << endl;

  for (int isamp(0) ; isamp<ndatasets ; isamp++) {
    SH::Sample *sample = m_sh.at (isamp);
    cout << endl;
    cout << "Sample Name " << sample->name() << endl;
    TH1 *nevhist =(TH1*)sample->readHist ("EventLoop_EventCount");
    if (nevhist) {
      cout << " N events " << nevhist->GetBinContent(1) << endl;
    }

    if (!(sample->name().find ("Data") == std::string::npos)) {
      m_sampleLumiWeight[sample->name()]=1.0;  // data unweighted
        continue;
    }

    // weights are now applied in the filling
    // we have corrected for MC lumi, so just scale by data lumi
    m_sampleLumiWeight[sample->name()]=(m_tot_datalumi);

    if (m_scaleMC_inputs != 1) {
      cout << "scaling MC inputs " << m_scaleMC_inputs << endl;
      m_sampleLumiWeight[sample->name()]=m_scaleMC_inputs;
    }
  }
  return true;
  
} 

void MakeInputs() {

  std::vector<TH1*> hists;

  // no flavour histograms yet - just separate by sample for now
  map<string, string> sampleNames;
  //  sampleNames["muonData"]="data";
  sampleNames["ZmumuL"]="Zmumul";
  sampleNames["ZmumuC"]="Zmumuc";
  sampleNames["ZmumuB"]="Zmumub";
  sampleNames["ZeeL"]="Zeel";
  sampleNames["ZeeC"]="Zeec";
  sampleNames["ZeeB"]="Zeeb";
  sampleNames["ZtautauL"]="Ztautaul";
  sampleNames["ZtautauC"]="Ztautauc";
  sampleNames["ZtautauB"]="Ztautaub";
  sampleNames["ttbar"]="ttbar";
  sampleNames["singletop_t"]="stop_t";
  sampleNames["singletop_s"]="stop_s";
  sampleNames["singletop_Wt"]="stop_Wt";
  sampleNames["ZnunuB"]="Zb";
  sampleNames["ZnunuC"]="Zc";
  sampleNames["ZnunuL"]="Zl";
  sampleNames["WenuB"]="Wenub";
  sampleNames["WenuC"]="Wenuc";
  sampleNames["WenuL"]="Wenul";
  sampleNames["WmunuB"]="Wmunub";
  sampleNames["WmunuC"]="Wmunuc";
  sampleNames["WmunuL"]="Wmunul";
  sampleNames["WtaunuB"]="Wtaunub";
  sampleNames["WtaunuC"]="Wtaunuc";
  sampleNames["WtaunuL"]="Wtaunul";


  //
  map<string, string> histnames;
  if (m_leptype==0) {
    histnames["2j_dRBB"]   ="pretag2jet_vpt120_dRBB";
    histnames["2j_dEtaBB"] ="pretag2jet_vpt120_dEtaBB";
    histnames["2j_dPhiVBB"]="pretag2jet_vpt120_dPhiVBB";
    histnames["2j_mBB"]    ="pretag2jet_vpt120_mBB";
    histnames["2j_MEff"]   ="pretag2jet_vpt120_MEff";
    histnames["2j_pTB1"]   ="pretag2jet_vpt120_pTB1";
    histnames["2j_pTB2"]   ="pretag2jet_vpt120_pTB2";
    histnames["2j_MET"]    ="pretag2jet_vpt120_MET";
    histnames["3j_dRBB"]   ="pretag3jet_vpt120_dRBB";
    histnames["3j_dEtaBB"] ="pretag3jet_vpt120_dEtaBB";
    histnames["3j_dPhiVBB"]="pretag3jet_vpt120_dPhiVBB";
    histnames["3j_mBB"]    ="pretag3jet_vpt120_mBB";
    histnames["3j_MEff3"]  ="pretag3jet_vpt120_MEff3";
    histnames["3j_pTB1"]   ="pretag3jet_vpt120_pTB1";
    histnames["3j_pTB2"]   ="pretag3jet_vpt120_pTB2";
    histnames["3j_MET"]    ="pretag3jet_vpt120_MET";
    histnames["3j_MBBJ"]   ="pretag3jet_vpt120_mBBJ";
    histnames["3j_pTJ3"]   ="pretag3jet_vpt120_pTJ3";
  } else if (m_leptype==2) {
    histnames["NJets"]="0tag_njet";
    histnames["Mmumu"]="0tag_Mmumu";
    histnames["Mee"]="0tag_Mee";
    histnames["ZPV"]="0tag_zpv";
    histnames["PtJets"]="0tag_ptj";
    histnames["EtaJets"]="0tag_etaj";
    histnames["MET"]="0tag_met";
    histnames["PtZ"]="0tag_ptz";
    histnames["DPhiJets"]="0tag_dphijj";
  }   


  int ndatasets=m_sh.size(); // number of sample handler datasets


  for (std::map<string,string>::iterator it=histnames.begin(); it!=histnames.end(); ++it) {
    std::cout << it->first << " => " << it->second << '\n';

    TH1* h_pseudodata=0;

      
    for (int isamp(0) ; isamp<ndatasets ; isamp++) {
      SH::Sample *sample = m_sh.at (isamp);

      TH1 *hist =(TH1*)sample->readHist(it->first);
    
      if (!hist) {
	std::cout << it->first << " not found for sample " << sample->name() << endl;
	continue;
      }

      //      cout << "sample->name() " <<  sample->name() << endl;
      //cout << "sampleNames[sample->name()] " <<  sampleNames[sample->name()] << endl;
      TString histname(sampleNames[sample->name()]);
      if (histname=="") 
	cout << " no sample in map for " << sample->name() << endl;
      cout << histname << endl;
      histname+="_"+it->second;
      cout << histname << endl;

      TH1* copyhist=(TH1*)hist->Clone(histname);

      // scale the MC to account for cross section and DxAOD efficiency
      float mcweight=m_sampleLumiWeight[sample->name()];
      //cout << " Applying weight " << mcweight << " for sample " << sample->name() << endl;
      copyhist->Scale(mcweight);

      // fill the array
      hists.push_back(copyhist);

      //make pseudo data from MC sum
      if (makePseudoData) {
	TString datahistname("data_");
	datahistname+=it->second;
	if (!h_pseudodata) h_pseudodata=(TH1*)copyhist->Clone(datahistname);
	else h_pseudodata->Add(copyhist);
      }
    } // samples
    // smear pseudo data before writing
    if (makePseudoData && h_pseudodata)  {
      static TRandom rand;
      for (int i=1; i<=h_pseudodata->GetNbinsX(); i++){
	h_pseudodata->SetBinContent(i,rand.Poisson(h_pseudodata->GetBinContent(i)));
	h_pseudodata->SetBinError(i,sqrt(h_pseudodata->GetBinContent(i)));
      }
      hists.push_back( h_pseudodata);
    }
  }

  //TString sysName = "SysMuonScaleDo";
  //TString sysName = "SysMuonScaleUp";
  TString sysName = "";

  TFile* inputsFile=TFile::Open("inputsFile.root","RECREATE");
  inputsFile->cd();
  if (sysName != "") {
    inputsFile->mkdir(sysName)->cd();
  }
  int nhists=hists.size();
  for (int i(0);i<nhists;++i) {
    cout << i << " " << hists[i]->GetName() << endl;

    if (sysName == "") {
      hists[i]->Write();
    } else {
      hists[i]->Write(hists[i]->GetName() + ("_" + sysName));
    }
  }

  // make a histogram of the lumi
  TH1F* hlumi=new TH1F("lumi","lumi",1,0,1);
  hlumi->Fill(0.5, m_tot_datalumi);
  hlumi->Write();
  inputsFile->Close();

}


void PlotHists(std::string histName, TString tit, float xmin, float xmax) {

  // these vectors contain the data and mc histograms
  std::vector<TH1*> data;
  std::vector<TH1*> mc;
  
  int ndatasets=m_sh.size(); // number of sample handler datasets


  TH1* bkg=0;
  TH1* Zbkg=0; // Z background
  for (int isamp(0) ; isamp<ndatasets ; isamp++) {
    // the sample we are plotting
    SH::Sample *sample = m_sh.at (isamp);
    TH1 *hist =(TH1*)sample->readHist (histName);
    
    if (!hist) {
      continue;
    }


    if (!(sample->name().find ("Data") == std::string::npos))
      data.push_back(hist);
    else {
      // scale the MC to account for cross section and DxAOD efficiency
      float mcweight=m_sampleLumiWeight[sample->name()];
      cout << " Applying weight " << mcweight << " for sample " << sample->name() << endl;
      hist->Scale(mcweight);

      mc.push_back(hist);
      if (!bkg) bkg=(TH1*)hist->Clone();
      else
	bkg->Add(hist);      
      //
      if (!(sample->name().find ("ZmumuL") == std::string::npos)) {
	if (!Zbkg) Zbkg=(TH1*)hist->Clone();
	else
	  Zbkg->Add(hist);      
      }
    }
  } 

  TH1* datahist=0;
  for (unsigned idata = 0; idata < data.size(); ++idata) {
    TH1* hist=data.at(idata);
    hist->SetLineColor(1);
    if (!datahist) datahist=(TH1*)hist->Clone();
    else datahist->Add(hist);
  } 


  // Plot
  m_canv->SetLogy(0);

  if (datahist&&tit)
    datahist->SetTitle(tit);
  datahist->Draw();
  bkg->Draw("same hist");

  for (unsigned imc = 0; imc < mc.size(); ++imc) {
    TH1* hist=mc.at(imc);
    hist->SetLineColor(imc+2);
    hist->Draw("same hist");
  } 

  TString outname(histName.c_str());
  m_canv->Print(m_outdir+"/"+outname+".eps");
  m_canv->Print(m_outdir+"/"+outname+".png");
  m_canv->Print(m_outdir+"/"+outname+".pdf");
  m_canv->SetLogy(1);
  m_canv->Print(m_outdir+"/"+outname+"Log.eps");
  m_canv->Print(m_outdir+"/"+outname+"Log.png");
  m_canv->Print(m_outdir+"/"+outname+"Log.pdf");

  // normalised
  m_canv->SetLogy(0);
  datahist->DrawNormalized();
  Zbkg->DrawNormalized("same hist");

  m_canv->Print(m_outdir+"/"+outname+"Norm.eps");
  m_canv->Print(m_outdir+"/"+outname+"Norm.png");
  m_canv->Print(m_outdir+"/"+outname+"Norm.pdf");
  m_canv->SetLogy(1);
  m_canv->Print(m_outdir+"/"+outname+"Norm_Log.eps");
  m_canv->Print(m_outdir+"/"+outname+"Norm_Log.png");
  m_canv->Print(m_outdir+"/"+outname+"Norm_Log.pdf");

}

float calcLumi() {

  // run I analysis lumi map using GRL
  fillLumiMap();

  // D4 2 lepton runs
  //TString lumiruns("FrameworkExe/macros/runs.D4.v0.0.6.txt");
  TString lumiruns="FrameworkExe/macros/runs.D4.v0.0.6AOD.txt";

  ifstream runfile (lumiruns);
 

  float lumi_tot=0;
  int run;
  int nruns=0;
  cout << "run    lumi "<< endl;
  if (runfile.is_open()) {
    while (runfile>>run) {
      float rlumi=m_lumi[run];
      cout << run << " "  <<  rlumi << endl;
      lumi_tot+=rlumi;
      nruns++;
    }
    runfile.close();
  }
  cout << " Total lumi " << lumi_tot << " pb-1 in n runs, n=" << nruns << endl;

  return lumi_tot;

}


void fillLumiMap() {

  m_lumi.clear();

  m_lumi [ 200842 ] = 0.189710419467 ;
  m_lumi [ 200863 ] = 3.24038519153 ;
  m_lumi [ 200913 ] = 2.21086735349 ;
  m_lumi [ 200926 ] = 8.2748459976 ;
  m_lumi [ 200965 ] = 1.12803451563 ;
  m_lumi [ 200967 ] = 16.8559674968 ;
  m_lumi [ 200982 ] = 3.5416762085 ;
  m_lumi [ 200987 ] = 50.545571918 ;
  m_lumi [ 201006 ] = 39.0576675605 ;
  m_lumi [ 201052 ] = 18.8801307739 ;
  m_lumi [ 201113 ] = 34.6138285469 ;
  m_lumi [ 201120 ] = 16.0822392203 ;
  m_lumi [ 201138 ] = 45.8788410064 ;
  m_lumi [ 201190 ] = 34.0409878004 ;
  m_lumi [ 201191 ] = 41.8941968223 ;
  m_lumi [ 201257 ] = 79.3379981133 ;
  m_lumi [ 201269 ] = 71.6872586885 ;
  m_lumi [ 201280 ] = 10.1300585625 ;
  m_lumi [ 201289 ] = 76.551408918 ;
  m_lumi [ 201489 ] = 51.6264228818 ;
  m_lumi [ 201494 ] = 39.1966005661 ;
  m_lumi [ 201555 ] = 35.6307298208 ;
  m_lumi [ 201556 ] = 113.420818802 ;
  m_lumi [ 202660 ] = 0.824584874527 ;
  m_lumi [ 202668 ] = 22.3473563798 ;
  m_lumi [ 202712 ] = 28.270753051 ;
  m_lumi [ 202740 ] = 6.00694597656 ;
  m_lumi [ 202798 ] = 47.141556987 ;
  m_lumi [ 202965 ] = 16.9231988438 ;
  m_lumi [ 202991 ] = 36.9334338989 ;
  m_lumi [ 203027 ] = 84.506032397 ;
  m_lumi [ 203169 ] = 4.83411112793 ;
  m_lumi [ 203191 ] = 5.67423527344 ;
  m_lumi [ 203195 ] = 42.9289025313 ;
  m_lumi [ 203228 ] = 23.9697305352 ;
  m_lumi [ 203256 ] = 5.06239430469 ;
  m_lumi [ 203258 ] = 112.65228763 ;
  m_lumi [ 203277 ] = 42.2543614219 ;
  m_lumi [ 203335 ] = 56.2023375918 ;
  m_lumi [ 203336 ] = 92.9624335332 ;
  m_lumi [ 203353 ] = 90.179076077 ;
  m_lumi [ 203432 ] = 61.6540078068 ;
  m_lumi [ 203454 ] = 15.3499146367 ;
  m_lumi [ 203456 ] = 38.0496688496 ;
  m_lumi [ 203523 ] = 19.1052527637 ;
  m_lumi [ 203524 ] = 66.4052538711 ;
  m_lumi [ 203602 ] = 159.249553571 ;
  m_lumi [ 203605 ] = 6.22108527344 ;
  m_lumi [ 203636 ] = 171.831763322 ;
  m_lumi [ 203680 ] = 74.1418925388 ;
  m_lumi [ 203719 ] = 101.75348138 ;
  m_lumi [ 203739 ] = 92.3231358457 ;
  m_lumi [ 203745 ] = 100.701911578 ;
  m_lumi [ 203760 ] = 7.77782284375 ;
  m_lumi [ 203779 ] = 83.4161132227 ;
  m_lumi [ 203792 ] = 6.35565490234 ;
  m_lumi [ 203875 ] = 18.0272223945 ;
  m_lumi [ 203876 ] = 149.726235076 ;
  m_lumi [ 203934 ] = 123.257763332 ;
  m_lumi [ 204025 ] = 23.3578541758 ;
  m_lumi [ 204026 ] = 111.609452718 ;
  m_lumi [ 204071 ] = 31.6233446602 ;
  m_lumi [ 204073 ] = 68.4864956816 ;
  m_lumi [ 204134 ] = 28.4259232227 ;
  m_lumi [ 204153 ] = 54.7469430252 ;
  m_lumi [ 204158 ] = 140.327548176 ;
  m_lumi [ 204240 ] = 157.665791086 ;
  m_lumi [ 204265 ] = 220.919841627 ;
  m_lumi [ 204416 ] = 83.2960950273 ;
  m_lumi [ 204442 ] = 14.2129944414 ;
  m_lumi [ 204474 ] = 113.923358135 ;
  m_lumi [ 204564 ] = 190.493922825 ;
  m_lumi [ 204633 ] = 48.4564685044 ;
  m_lumi [ 204668 ] = 151.046704575 ;
  m_lumi [ 204726 ] = 30.9840296758 ;
  m_lumi [ 204763 ] = 185.898863343 ;
  m_lumi [ 204769 ] = 103.814412546 ;
  m_lumi [ 204772 ] = 80.0526346309 ;
  m_lumi [ 204796 ] = 8.94520999023 ;
  m_lumi [ 204853 ] = 39.7481866331 ;
  m_lumi [ 204857 ] = 23.5175128516 ;
  m_lumi [ 204910 ] = 105.60657167 ;
  m_lumi [ 204932 ] = 133.233842726 ;
  m_lumi [ 204954 ] = 68.2777504495 ;
  m_lumi [ 204955 ] = 86.5587074377 ;
  m_lumi [ 204976 ] = 63.4100838789 ;
  m_lumi [ 205010 ] = 36.2689021406 ;
  m_lumi [ 205016 ] = 93.236646027 ;
  m_lumi [ 205017 ] = 70.489766309 ;
  m_lumi [ 205055 ] = 188.445969028 ;
  m_lumi [ 205071 ] = 220.520144212 ;
  m_lumi [ 205112 ] = 62.1625637742 ;
  m_lumi [ 205113 ] = 39.8774595664 ;
  m_lumi [ 206368 ] = 33.1578738073 ;
  m_lumi [ 206369 ] = 96.0201707293 ;
  m_lumi [ 206409 ] = 140.582310032 ;
  m_lumi [ 206497 ] = 6.46322120313 ;
  m_lumi [ 206573 ] = 22.2137510898 ;
  m_lumi [ 206614 ] = 19.8449648906 ;
  m_lumi [ 206955 ] = 21.7459615156 ;
  m_lumi [ 206962 ] = 135.223403959 ;
  m_lumi [ 206971 ] = 107.864914616 ;
  m_lumi [ 207044 ] = 55.5848590005 ;
  m_lumi [ 207046 ] = 115.054938225 ;
  m_lumi [ 207221 ] = 163.252181177 ;
  m_lumi [ 207262 ] = 17.1120041278 ;
  m_lumi [ 207304 ] = 106.411763352 ;
  m_lumi [ 207306 ] = 68.4357088301 ;
  m_lumi [ 207332 ] = 157.777657736 ;
  m_lumi [ 207397 ] = 139.271864668 ;
  m_lumi [ 207447 ] = 164.525317342 ;
  m_lumi [ 207490 ] = 112.206841506 ;
  m_lumi [ 207528 ] = 7.29196442578 ;
  m_lumi [ 207531 ] = 23.4892800195 ;
  m_lumi [ 207532 ] = 62.3554937021 ;
  m_lumi [ 207582 ] = 57.3897992109 ;
  m_lumi [ 207589 ] = 69.0090039629 ;
  m_lumi [ 207620 ] = 174.290759262 ;
  m_lumi [ 207664 ] = 89.5531196947 ;
  m_lumi [ 207696 ] = 126.097913894 ;
  m_lumi [ 207749 ] = 69.3698162812 ;
  m_lumi [ 207772 ] = 16.7231106563 ;
  m_lumi [ 207800 ] = 1.86646416406 ;
  m_lumi [ 207809 ] = 152.523685855 ;
  m_lumi [ 207845 ] = 50.5453005431 ;
  m_lumi [ 207864 ] = 27.0307753828 ;
  m_lumi [ 207865 ] = 81.2124379589 ;
  m_lumi [ 207931 ] = 15.8960409259 ;
  m_lumi [ 207934 ] = 126.308155253 ;
  m_lumi [ 207975 ] = 51.6244715938 ;
  m_lumi [ 207982 ] = 111.926913074 ;
  m_lumi [ 208123 ] = 65.5834047431 ;
  m_lumi [ 208126 ] = 24.4730549492 ;
  m_lumi [ 208179 ] = 5.67707427162 ;
  m_lumi [ 208184 ] = 96.6267762383 ;
  m_lumi [ 208189 ] = 36.2034794323 ;
  m_lumi [ 208258 ] = 86.2235687626 ;
  m_lumi [ 208261 ] = 95.1195882109 ;
  m_lumi [ 208354 ] = 124.660724042 ;
  m_lumi [ 208485 ] = 135.531916632 ;
  m_lumi [ 208631 ] = 0.719697461914 ;
  m_lumi [ 208642 ] = 3.44845699414 ;
  m_lumi [ 208662 ] = 137.994910611 ;
  m_lumi [ 208705 ] = 2.16080291602 ;
  m_lumi [ 208717 ] = 46.2109412665 ;
  m_lumi [ 208720 ] = 20.590578043 ;
  m_lumi [ 208780 ] = 40.5681247264 ;
  m_lumi [ 208781 ] = 138.116634261 ;
  m_lumi [ 208811 ] = 205.724849696 ;
  m_lumi [ 208870 ] = 11.6670006562 ;
  m_lumi [ 208930 ] = 52.8324467305 ;
  m_lumi [ 208931 ] = 96.5284355297 ;
  m_lumi [ 208970 ] = 98.0161885624 ;
  m_lumi [ 208982 ] = 164.689134596 ;
  m_lumi [ 209024 ] = 0.0521610993042 ;
  m_lumi [ 209025 ] = 7.72994816016 ;
  m_lumi [ 209074 ] = 60.7850017325 ;
  m_lumi [ 209084 ] = 77.4664889517 ;
  m_lumi [ 209109 ] = 122.502183092 ;
  m_lumi [ 209161 ] = 46.3665026563 ;
  m_lumi [ 209183 ] = 164.877930008 ;
  m_lumi [ 209214 ] = 12.6065755217 ;
  m_lumi [ 209254 ] = 120.150306393 ;
  m_lumi [ 209265 ] = 2.78438748438 ;
  m_lumi [ 209269 ] = 52.0117925312 ;
  m_lumi [ 209353 ] = 5.04179526562 ;
  m_lumi [ 209381 ] = 159.479095824 ;
  m_lumi [ 209550 ] = 117.181653235 ;
  m_lumi [ 209580 ] = 158.248228589 ;
  m_lumi [ 209608 ] = 84.0347666304 ;
  m_lumi [ 209628 ] = 81.1839818969 ;
  m_lumi [ 209629 ] = 153.339455684 ;
  m_lumi [ 209736 ] = 121.412306765 ;
  m_lumi [ 209776 ] = 22.4083282821 ;
  m_lumi [ 209787 ] = 96.155800438 ;
  m_lumi [ 209812 ] = 105.123396306 ;
  m_lumi [ 209864 ] = 134.132334589 ;
  m_lumi [ 209866 ] = 7.0037139935 ;
  m_lumi [ 209899 ] = 51.0047650105 ;
  m_lumi [ 209980 ] = 162.441893674 ;
  m_lumi [ 209995 ] = 125.920568053 ;
  m_lumi [ 210302 ] = 154.111138348 ;
  m_lumi [ 210308 ] = 128.50764746 ;
  m_lumi [ 211620 ] = 16.6724708496 ;
  m_lumi [ 211670 ] = 18.1411438592 ;
  m_lumi [ 211697 ] = 10.1083205645 ;
  m_lumi [ 211772 ] = 94.8079426414 ;
  m_lumi [ 211787 ] = 129.999325737 ;
  m_lumi [ 211867 ] = 140.095614626 ;
  m_lumi [ 211902 ] = 16.2154705807 ;
  m_lumi [ 211937 ] = 103.209384969 ;
  m_lumi [ 212034 ] = 76.9916739185 ;
  m_lumi [ 212103 ] = 5.02055775279 ;
  m_lumi [ 212142 ] = 48.9113505484 ;
  m_lumi [ 212144 ] = 168.306900384 ;
  m_lumi [ 212172 ] = 162.904841767 ;
  m_lumi [ 212199 ] = 147.421921197 ;
  m_lumi [ 212272 ] = 136.003050053 ;
  m_lumi [ 212619 ] = 0.289823536133 ;
  m_lumi [ 212663 ] = 40.9402817376 ;
  m_lumi [ 212687 ] = 71.8393819175 ;
  m_lumi [ 212721 ] = 111.87425072 ;
  m_lumi [ 212742 ] = 98.0623370256 ;
  m_lumi [ 212809 ] = 14.0881161797 ;
  m_lumi [ 212815 ] = 143.650134433 ;
  m_lumi [ 212858 ] = 154.443740357 ;
  m_lumi [ 212967 ] = 96.1991826172 ;
  m_lumi [ 212993 ] = 117.277334823 ;
  m_lumi [ 213039 ] = 137.430040521 ;
  m_lumi [ 213079 ] = 102.702586636 ;
  m_lumi [ 213092 ] = 78.3701058842 ;
  m_lumi [ 213130 ] = 70.1217074567 ;
  m_lumi [ 213155 ] = 48.5089720586 ;
  m_lumi [ 213157 ] = 19.9394051602 ;
  m_lumi [ 213204 ] = 18.1206289922 ;
  m_lumi [ 213250 ] = 87.8834079287 ;
  m_lumi [ 213359 ] = 33.1932214023 ;
  m_lumi [ 213431 ] = 77.9749525707 ;
  m_lumi [ 213479 ] = 9.54781790234 ;
  m_lumi [ 213486 ] = 142.740869311 ;
  m_lumi [ 213539 ] = 192.109002432 ;
  m_lumi [ 213627 ] = 26.0262161902 ;
  m_lumi [ 213640 ] = 43.2813935388 ;
  m_lumi [ 213684 ] = 26.6672046206 ;
  m_lumi [ 213695 ] = 79.4239917266 ;
  m_lumi [ 213702 ] = 45.4368734536 ;
  m_lumi [ 213754 ] = 171.877149579 ;
  m_lumi [ 213796 ] = 74.0254460296 ;
  m_lumi [ 213816 ] = 58.8317404513 ;
  m_lumi [ 213819 ] = 68.3207734841 ;
  m_lumi [ 213900 ] = 133.638060313 ;
  m_lumi [ 213951 ] = 92.9426242997 ;
  m_lumi [ 213964 ] = 8.96518804687 ;
  m_lumi [ 213968 ] = 29.7547312227 ;
  m_lumi [ 214021 ] = 168.026457031 ;
  m_lumi [ 214086 ] = 183.819374269 ;
  m_lumi [ 214160 ] = 173.904663528 ;
  m_lumi [ 214176 ] = 62.2441560313 ;
  m_lumi [ 214216 ] = 117.303785719 ;
  m_lumi [ 214388 ] = 20.4808672148 ;
  m_lumi [ 214390 ] = 70.565205624 ;
  m_lumi [ 214494 ] = 139.754618587 ;
  m_lumi [ 214523 ] = 147.239287975 ;
  m_lumi [ 214544 ] = 124.987851089 ;
  m_lumi [ 214553 ] = 152.206600778 ;
  m_lumi [ 214618 ] = 59.3274950151 ;
  m_lumi [ 214651 ] = 23.8364756133 ;
  m_lumi [ 214680 ] = 160.952446463 ;
  m_lumi [ 214714 ] = 7.88902242187 ;
  m_lumi [ 214721 ] = 59.8859230312 ;
  m_lumi [ 214758 ] = 152.025273077 ;
  m_lumi [ 214777 ] = 130.387350381 ;
  m_lumi [ 215027 ] = 110.568687402 ;
  m_lumi [ 215061 ] = 34.870136582 ;
  m_lumi [ 215063 ] = 88.6606237363 ;
  m_lumi [ 215091 ] = 142.099968006 ;
  m_lumi [ 215414 ] = 107.531466994 ;
  m_lumi [ 215433 ] = 105.769035638 ;
  m_lumi [ 215456 ] = 107.062526132 ;
  m_lumi [ 215464 ] = 152.429314269 ;
  m_lumi [ 215473 ] = 137.316146243 ;
  m_lumi [ 215541 ] = 64.3852344042 ;
  m_lumi [ 215571 ] = 57.7598615215 ;
  m_lumi [ 215589 ] = 64.0214443467 ;
  m_lumi [ 215643 ] = 43.4902693672 ;

}

