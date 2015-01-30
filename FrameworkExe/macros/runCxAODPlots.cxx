#include <TSystem.h>
#include <TROOT.h>
void runCxAODPlots(const std::string& submitDir="");
using namespace std;

// macro for plotting histograms made by CxAODReader
// Run using e.g.
// root -b -q 'FrameworkExe/macros/runCxAODPlots.cxx("mysubmitDir")' 
// 
// Prerequisites:
//  The PlottingTool
//  svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/InputsProcessingTools/PlottingTool/trunk PlottingTool
//
//

void runCxAODPlots(const std::string& submitDir)
{

  // Write inputs and use PlotMaker to plot
  bool writeInputs=true;
  bool doPlotMaker=true;

  //  
  if (writeInputs) {
    // Load the libraries for all packages - for SampleHandler/Derivation
    gROOT->ProcessLine (".x $ROOTCOREDIR/scripts/load_packages.C");
    TString libdir="FrameworkExe/macros/"; 
    gROOT->ProcessLine(".L "+libdir+"AtlasStyle.cxx+");

    TString run_command(".x FrameworkExe/macros/PlotCxAODReader.cxx+(\"XXX\")");
    run_command.ReplaceAll("XXX",submitDir);
    cout << " run command " << run_command << endl; 
    gROOT->ProcessLine(run_command);

  }

  // PlotMaker from Remi
  if (!doPlotMaker) return;
  TString libdir="PlottingTool/"; 
  TString includePath = gSystem->GetIncludePath();  
  cout << "includePath: " << includePath << endl;
  gSystem->SetIncludePath(includePath+" -I"+libdir+"transform");
  cout << "includePath update: " << gSystem->GetIncludePath() << endl;

  gROOT->ProcessLine(".L "+libdir+"transform/HistoTransform.C+");

  gROOT->ProcessLine(".L "+libdir+"Utils.cxx+");
  gROOT->ProcessLine(".L "+libdir+"SystTool.cxx+");
  gROOT->ProcessLine(".L "+libdir+"Config.cxx+");
  gROOT->ProcessLine(".L "+libdir+"LatexMaker.cxx+");
  gROOT->ProcessLine(".L "+libdir+"PlotMaker.cxx+");

  TString input(".x FrameworkExe/macros/makePlots2Lepton.cxx+()");
  //  TString input(".x FrameworkExe/macros/makePlots0Lepton.cxx+()");
  gROOT->ProcessLine(input);

}



