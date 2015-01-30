#include "PlottingTool/Config.h"
#include "PlottingTool/PlotMaker.h"

#include <iostream>


void makePlots0Lepton() {

  Config config;

  // should we overwrite existing plots or only do missing ones?
  config.setOverwrite(true);


  /////////
  /// Input 

  // path to the input file: can be local or on eos
  config.setInputPath("./");

  // Since your input file name might not follow the conventions above,
  // it can be overwritten using the line below
  // Note: specify the name WITHOUT ".root" at the end
  config.setInputFile("inputsFile");

  // If input histograms are stored in a subdirectory of the input file, specify below
  // config.setInputTDirectory("OneLepton");

  // read lumi from input file
  std::string lumi_str("20.2578");
  TFile* inputfile=TFile::Open(config.getInputFileFullName("").c_str(),"READ");
  TH1* hlumi= (inputfile) ? (TH1*)inputfile->Get("lumi") : 0;  
  if(hlumi) {
    float lumi_fb=hlumi->GetBinContent(1)/1000.0;
    lumi_str=Form("%.2f",lumi_fb);
    inputfile->Close();
  }
  cout << "Using luminosity " << lumi_str << endl;

  ////////////////
  /// General info
  config.setAnalysis( Config::TwoLepton,  // Type = ZeroLepton, OneLepton or TwoLepton: Appears on the plots
		      "Internal",         // Status: Appear on the plots next to ATLAS label
		      "Moriond2016",      // Name = "LHCP2013": only useful for the above naming convention
		      "8",                // Center of mass energy: Appears on the plots
		      lumi_str,           // Integrated luminosity: Appears on the plots
		      "125",              // Mass of the generated higgs boson: only useful for the above naming convention
		      "Sinica",           // Name of your institute: only usefule for the above naming convention
		      "fram15");          // Input file version: only useful for the above naming convention


  //////////
  /// Output

  // path to output plots
  config.setOutputPath("./plots");

  // BDT transformations:
  config.addBDTTransformation(""); // no transformation

  /// Samples
 
  // declare the samples
  config.addDataSample("data",       // name: as it appears in the histogram names
		       "Data",       // title: as it should appear in the legend 
		       1);           // color: this is marker(line+fill) color for data(MC) 
  //  config.addSignalSample("qqZllH125", "ZH 125", kRed);
  //  config.addSignalSample("ggZllH125", "ZH 125", kRed);
  //  config.addSignalSample("qqZvvH125", "ZH 125", kRed); 
  //  config.addSignalSample("ggZvvH125", "ZH 125", kRed); 
  //  config.addSignalSample("WlvH125", "WH 125", kRed + 1);
  config.addBackgroundSample("ttbar", "ttbar", kOrange);
  //  config.addBackgroundSample("stop_s", "s+t chan", kOrange - 1); // Two samples sharing the same title appear only once in the legend
  //  config.addBackgroundSample("stop_t", "s+t chan", kOrange - 1);
  //  config.addBackgroundSample("stop_Wt", "Wt", kYellow - 7);
  //  config.addBackgroundSample("Wbb", "W+bb", kGreen + 3);
  //  config.addBackgroundSample("Wbc", "W+bb", kGreen + 3);
  //  config.addBackgroundSample("Wbl", "W+bl", kGreen + 2);
  //  config.addBackgroundSample("Wcl", "W+cl", kGreen - 6);
  //  config.addBackgroundSample("Wcc", "W+cc", kGreen + 1);
  //  config.addBackgroundSample("Wl", "W+l", kGreen - 9);
  //  config.addBackgroundSample("Zbl", "Z+bl", kAzure + 1);
  //  config.addBackgroundSample("Zbb", "Z+bb", kAzure + 2);
  //  config.addBackgroundSample("Zbc", "Z+bc", kAzure + 2);
  //  config.addBackgroundSample("Zcl", "Z+cl", kAzure - 8);
  //  config.addBackgroundSample("Zcc", "Z+cc", kAzure - 4);
  //  config.addBackgroundSample("Zl", "Z+l", kAzure - 9);
  //  config.addBackgroundSample("multijetEl", "multijet", kPink + 1);
  //  config.addBackgroundSample("multijetMu", "multijet", kPink + 1);
  //  config.addBackgroundSample("WW", "WW", kGray + 3);
  //  config.addBackgroundSample("WZ", "WZ", kGray);
  //  config.addBackgroundSample("ZZ", "ZZ", kGray + 1);
  config.addBackgroundSample("Zb", "Z+b", kAzure + 1);
  config.addBackgroundSample("Zc", "Z+c", kAzure - 4);
  config.addBackgroundSample("Zl", "Z+l", kAzure - 9);
  config.addBackgroundSample("Wb", "W+b", kGreen + 2);
  config.addBackgroundSample("Wc", "W+c", kGreen + 1);
  config.addBackgroundSample("Wl", "W+l", kGreen - 9);


  //  std::string scaleFactorsTag = "SF_1L_nJ_0107";
  // config.readScaleFactors("scaleFactors/"+scaleFactorsTag+".txt");
  // config.setOutputPath(config.getOutputPath()+"/"+scaleFactorsTag);

  // To optimize plot readability , samples that contribute less than a fraction X are dropped from the legend
  //  config.setLegendThreshold(0.05);

  // To draw the histograms in no-stack mode
  //  config.setNoStack();

  // set total background name
  // this is not mandatory but would save CPU and memory
  // Note: if any background scale factors are different than one, 
  //       this cannot be used and will be ignored
  // config.setTotalBackgroundName("bkg");



  ////////////
  // Variables

  config.addVariable(Config::BDTInput, "mBB", "m(bb) [GeV]", 0, 500, 5);
  config.addVariable(Config::BDTInput, "MET", "MET [GeV]", 0, 500, 4);
  config.addVariable(Config::BDTInput, "mBBJ", "m(bbj) [GeV]", 0, 750, 5);
  config.addVariable(Config::BDTInput, "dRBB", "#DeltaR(b,b)", 0, 5.99, 4);
  config.addVariable(Config::BDTInput, "dEtaBB", "#Delta#eta(b,b)", 0, 4.99, 4);
  config.addVariable(Config::BDTInput, "dPhiVBB", "#Delta#phi(V,bb)", 2.5, 3.15, 1);
  config.addVariable(Config::BDTInput, "MEff", "MEff = p_{T}(b_{1}) + p_{T}(b_{2}) + MET [GeV]", 200, 1000, 4);
  config.addVariable(Config::BDTInput, "MEff3", "MEff3 = p_{T}(b_{1}) + p_{T}(b_{2}) + p_{T}(b_{3}) + MET [GeV]", 200, 1000, 4);
  config.addVariable(Config::BDTInput, "pTB1", "p_{T}(b_{1}) [GeV]", 40, 500, 4);
  config.addVariable(Config::BDTInput, "pTB2", "p_{T}(b_{2}) [GeV]", 0, 250, 4);
  config.addVariable(Config::BDTInput, "pTJ3", "p_{T}(j_{3}) [GeV]", 0, 150, 4);
  //config.addVariable(Config::BDTInput, "MV1cB1", "MV1c(b_{1})", 0, 1, 5);
  //config.addVariable(Config::BDTInput, "MV1cB2", "MV1c(b_{2})", 0, 1, 5);


  // config.addRegion("2tag3jet_vpt120",                      // name: as it appears in histogram name
  //               "2 tags, 3 jets, p_{T}^{V} >= 120 GeV", // title: as it appears on the plots
  //               "2 tags");                              // slide title: used to decide which plots to appear on the same slide
  config.clearRegions();
  config.addRegion("pretag2jet_vpt120","","");
  //  config.addRegion("2j","","");
  // config.addRegion("3j","","");

  config.clearSystematics();
  
  // or with a reduced set of systematics
  // Note: first clear the systematics as shown above
  // config.addSystematic("SysMETScaleSoftTerms", // name
  //  		       false);         // is one sided?
  // config.addSystematic("SysMETResoSoftTerms", false);
  // config.addSystematic("SysJetEResol", true);
  // config.addSystematic("SysBJetReso", true);
  // config.addSystematic("SysMJShape", false);
  // config.addSystematic("SysMETScaleSoftTerms", false);
  // config.addSystematic("SysWDPhi", false);
  // config.addSystematic("SysWPtV", false);
  // config.addSystematic("SysWbbMbbGS", false);
  // config.addSystematic("SysWMbb", false);
  // config.addSystematic("SysTopPt", false);
  // config.addSystematic("SysTtbarPtWCont", false);
  // config.addSystematic("SysTtbarMBBCont", false);
  // config.addSystematic("SysTtbarPtB1Cont", false);
  // config.addSystematic("SysTtbarMetCont", false);
  // config.addSystematic("SysWtChanAcerMC", false);
  // config.addSystematic("SysWtChanPythiaHerwig", false);
  // config.addSystematic("SysTChanPtB2", false);
  // config.addSystematic("SysVVJetScalePtST1", false);
  // config.addSystematic("SysVVJetScalePtST2", false);
  // config.addSystematic("SysVVMbb", false);
  //config.addSystematic("SysMuonScale", false);
  
  ////////////////////////
  /// Detailed systematics
  
  // One can ask for detailed systematic plots for specific variables in specific region
  // This will make one plot per nuisance parameter
  // config.addDetailedSystematicsPlots("mva",               // name of the variable: as declared above
  // 				     "trafo6",            // name of the transformation: relevant for BDT outputs
  // 				     "2tag2jet_vpt0_120", // name of the region: as declared above
  // 				     "Systematics: ");    // slide title: used to decide which plots to appear on the same slide
  // config.addDetailedSystematicsPlots("mva", "trafo6", "2tag2jet_vpt120", "Systematics: ");
  // config.addDetailedSystematicsPlots("mBB", "", "2tag2jet_vpt0_120", "Systematics: ");
  // config.addDetailedSystematicsPlots("mBB", "", "2tag2jet_vpt120", "Systematics: ");
  // config.addDetailedSystematicsPlots("pTB1", "", "2tag2jet_vpt0_120", "Systematics: ");
  // config.addDetailedSystematicsPlots("pTB1", "", "2tag2jet_vpt120", "Systematics: ");
  // config.addDetailedSystematicsPlots("pTB2", "", "2tag2jet_vpt0_120", "Systematics: ");
  // config.addDetailedSystematicsPlots("pTB2", "", "2tag2jet_vpt120", "Systematics: ");
  // config.addDetailedSystematicsPlots("MET", "", "2tag2jet_vpt0_120", "Systematics: ");
  // config.addDetailedSystematicsPlots("MET", "", "2tag2jet_vpt120", "Systematics: ");
  
  // config.addDetailedSystematicsPlots("mvaWlvH125", "trafo6", "2lltag2jet_vpt120", "Systematics (high pTV): ");
  // config.addDetailedSystematicsPlots("mvaWlvH125", "trafo6", "2mmtag2jet_vpt120", "Systematics (high pTV): ");
  // config.addDetailedSystematicsPlots("mvaWlvH125", "trafo6", "2tttag2jet_vpt120", "Systematics (high pTV): ");

  // config.addDetailedSystematicsPlots("mvaWlvH125", "trafo6", "2lltag2jet_vpt0_120", "Systematics (low pTV): ");
  // config.addDetailedSystematicsPlots("mvaWlvH125", "trafo6", "2mmtag2jet_vpt0_120", "Systematics (low pTV): ");
  // config.addDetailedSystematicsPlots("mvaWlvH125", "trafo6", "2tttag2jet_vpt0_120", "Systematics (low pTV): ");
  
  // config.addDetailedSystematicsPlots("mBB", "", "2lltag2jet_vpt120", "Systematics (high pTV): ");
  // config.addDetailedSystematicsPlots("mBB", "", "2mmtag2jet_vpt120", "Systematics (high pTV): ");
  // config.addDetailedSystematicsPlots("mBB", "", "2tttag2jet_vpt120", "Systematics (high pTV): ");

  // config.addDetailedSystematicsPlots("mBB", "", "2lltag2jet_vpt0_120", "Systematics (low pTV): ");
  // config.addDetailedSystematicsPlots("mBB", "", "2mmtag2jet_vpt0_120", "Systematics (low pTV): ");
  // config.addDetailedSystematicsPlots("mBB", "", "2tttag2jet_vpt0_120", "Systematics (low pTV): ");

  // config.addDetailedSystematicsPlots("mva", "trafoF", "1tag2jet_vpt0_120",   "Systematics 2J (low pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2lltag2jet_vpt0_120", "Systematics 2J (low pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2mmtag2jet_vpt0_120", "Systematics 2J (low pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2tttag2jet_vpt0_120", "Systematics 2J (low pTV): ");

  // config.addDetailedSystematicsPlots("mva", "trafoF", "1tag2jet_vpt120",   "Systematics 2J (high pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2lltag2jet_vpt120", "Systematics 2J (high pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2mmtag2jet_vpt120", "Systematics 2J (high pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2tttag2jet_vpt120", "Systematics 2J (high pTV): ");

  // config.addDetailedSystematicsPlots("mva", "trafoF", "1tag3jet_vpt0_120",   "Systematics 3J (low pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2lltag3jet_vpt0_120", "Systematics 3J (low pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2mmtag3jet_vpt0_120", "Systematics 3J (low pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2tttag3jet_vpt0_120", "Systematics 3J (low pTV): ");

  // config.addDetailedSystematicsPlots("mva", "trafoF", "1tag3jet_vpt120",   "Systematics 3J (high pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2lltag3jet_vpt120", "Systematics 3J (high pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2mmtag3jet_vpt120", "Systematics 3J (high pTV): ");
  // config.addDetailedSystematicsPlots("mva", "trafoF", "2tttag3jet_vpt120", "Systematics 3J (high pTV): ");
  
  // for(int iCR=0; iCR<config.getNRegions(); iCR++) {
  //   Config::Region region = config.getRegion(iCR);
  //   for(int iVar=0; iVar<config.getNVariables(); iVar++) {
  //     Config::Variable var = config.getVariable(iVar);
  //     std::string title = "Systematics: "+var.name+" ";
  //     if(region.name.find("0tag") != std::string::npos ) {
  // 	title += "0 tag";
  //     }else if(region.name.find("1tag") != std::string::npos) {
  // 	title += "1 tag";
  //     }else{
  // 	title += "2 tag";
  // 	if(region.name.find("2jet") != std::string::npos) {
  // 	  title += " , 2 jets";
  // 	}else{
  // 	  title += " , 3 jets";
  // 	}
  // 	if(region.name.find("vpt120") != std::string::npos) {
  // 	  title += " (high pTV)";
  // 	}else {
  // 	  title += " (low pTV)";
  // 	}
  //     }
  //     config.addDetailedSystematicsPlots(var.name, 
  // 					 "", //var.type == Config::BDTOutput ? "trafo6" : "", 
  // 					 region.name,
  // 					 title);
  //   }
  // }
					 


   /////////////////////////
   /// Computing sensitivity
   
   // One can output expected sensitivity numbers based on some specific plots and regions
   // The sensitivity metric used is one of two:
   //  - Normal approximation:
   //    S/sqrt(B + dB*dB)
   //  - Log likelihood ratio:
   //    sqrt(2*((S+B)*lob(1+S/B)-S))
   // It is computed for each bin and then added in quadrature
   // Several histograms from different regions can be combined (one variable per region)
   // NOTE: the concerned variables and regions and transformations 
   //       need to be added for ploting above.
   
   // define the regions to combine
   //   config.addSensitivityPlot( "mva",             // name to uniquely identify a sensitivity calculation
   // 			     "mva",             // variable name used for this region
   // 			     "2tag2jet_vpt120", // name of the region
   // 			     "trafo6");         // name of the transformation in case of BDT
   //   config.addSensitivityPlot( "mva", "mva", "2tag3jet_vpt120", "trafo6");
   //   config.addSensitivityPlot( "mva", "mva", "2tag2jet_vpt0_120", "trafo6");
   //   config.addSensitivityPlot( "mva", "mva", "2tag3jet_vpt0_120", "trafo6");
   
   //   // you can combine the same plots in different ways
   //   config.addSensitivityPlot( "mva 2t2j", "mva", "2tag2jet_vpt120", "trafo6");
   //   config.addSensitivityPlot( "mva 2t2j", "mva", "2tag2jet_vpt0_120", "trafo6");
   //   config.addSensitivityPlot( "mva 2t3j", "mva", "2tag3jet_vpt120", "trafo6");
   //   config.addSensitivityPlot( "mva 2t3j", "mva", "2tag3jet_vpt0_120", "trafo6");
   
   //   config.addSensitivityPlot( "mva high ptv", "mva", "2tag2jet_vpt120", "trafo6");
   //   config.addSensitivityPlot( "mva high ptv", "mva", "2tag3jet_vpt120", "trafo6");
   //   config.addSensitivityPlot( "mva low ptv", "mva", "2tag2jet_vpt0_120", "trafo6");
   //   config.addSensitivityPlot( "mva low ptv", "mva", "2tag3jet_vpt0_120", "trafo6");
   
   //   config.addSensitivityPlot( "cuts", "mjj", "2lltag3jet_vpt200", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2lltag2jet_vpt200", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2mmtag3jet_vpt200", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2mmtag2jet_vpt200", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2tttag3jet_vpt200", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2tttag2jet_vpt200", "");
   
   //   config.addSensitivityPlot( "cuts", "mjj", "2lltag3jet_vpt160_200", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2lltag2jet_vpt160_200", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2mmtag3jet_vpt160_200", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2mmtag2jet_vpt160_200", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2tttag3jet_vpt160_200", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2tttag2jet_vpt160_200", "");
   
   //   config.addSensitivityPlot( "cuts", "mjj", "2lltag3jet_vpt120_160", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2lltag2jet_vpt120_160", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2mmtag3jet_vpt120_160", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2mmtag2jet_vpt120_160", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2tttag3jet_vpt120_160", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2tttag2jet_vpt120_160", "");
   
   //   config.addSensitivityPlot( "cuts", "mjj", "2lltag3jet_vpt90_120", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2lltag2jet_vpt90_120", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2mmtag3jet_vpt90_120", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2mmtag2jet_vpt90_120", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2tttag3jet_vpt90_120", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2tttag2jet_vpt90_120", "");
   
   //   config.addSensitivityPlot( "cuts", "mjj", "2lltag3jet_vpt0_90", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2lltag2jet_vpt0_90", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2mmtag3jet_vpt0_90", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2mmtag2jet_vpt0_90", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2tttag3jet_vpt0_90", "");
   //   config.addSensitivityPlot( "cuts", "mjj", "2tttag2jet_vpt0_90", "");
   
   

  ///////////////////////////
  /// Now ready to make plots

  // check for errors in configuration
  if(!config.isValid()) {
    std::cout << "Error in configuration: ===> Aborting..." << std::endl;
    return;
  }

  // we have all what we need to know
  // ==> now make the plots
  PlotMaker plotter;
  plotter.makePlots(config);
}
