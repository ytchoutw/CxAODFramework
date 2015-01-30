#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/DiskListLocal.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "EventLoopGrid/PrunDriver.h"

#include "iostream"
#include "fstream"
#include <TSystem.h> 
#include <stdlib.h> 

#include "CxAODMaker/AnalysisBase.h"
#include "CxAODTools/ConfigStore.h"
#include "TupleMaker/TupleMaker.h"


int main(int argc, char* argv[]) {

  // Take the submit directory from the input if provided:
  std::string submitDir = "submitDir";
  std::string configPath = "data/FrameworkExe/framework-run.cfg";
  std::string sample_in="mc14_13TeV.110401.PowhegPythia_P2012_ttbar_nonallhad.merge.AOD.e2928_s1982_s2008_r5787_r5853_tid01597980_00";
  std::string sample_out="CxAOD"; 
  std::string ana_tag = "";
  std::string aod_tag = "";
  //
  if (argc > 1) sample_in = argv[1];
  if (argc > 2) sample_out = argv[2];
  if (argc > 3) submitDir = argv[3];
  if (argc > 4) configPath = argv[4];

  // define if interactive or grid job, taken from 'grid' existing in name of submission text file
  // see https://twiki.cern.ch/twiki/bin/view/AtlasProtected/CxAODFramework#Grid_running
  bool grid = sample_in.find("grid") != std::string::npos;
  std::cout << "run grid=" << grid << std::endl;

  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  SH::SampleHandler sampleHandler;

  // create algorithm, set job options, maniplate members and add our analysis to the job:
  AnalysisBase* algorithm = new AnalysisBase();

  // read run config
  static ConfigStore* config = ConfigStore::createStore(configPath);

  // COM - used only for deciding which test file to run - useful for validation tests
  TString comEnergy(config->get<std::string>("COMEnergy"));
  std::cout << "COM Energy for validation sample=" << comEnergy << std::endl;

  // validation
  bool validate(config->get<bool>("validate"));
  if (validate) {
    std::cout << "Running validation" << std::endl;
    algorithm->setValidation(true);
  }

  if (!grid) {
    // AOD    
    // 13TeV default
    SH::DiskListLocal list("/afs/cern.ch/atlas/project/PAT/xAODs/r5787/"+sample_in);
    if(comEnergy=="8TeV") {
      std::string sample_in_8TeV="mc14_8TeV.117050.PowhegPythia_P2011C_ttbar.recon.AOD.e1727_s1933_s1911_r5591";
      list="/afs/cern.ch/atlas/project/PAT/xAODs/r5591/"+sample_in_8TeV;
    }
    SH::scanSingleDir (sampleHandler, sample_out, list);
    // CxAOD
    //SH::scanDir(sampleHandler, "/afs/cern.ch/work/d/dbuesche/public/xAODs/DAOD_HIGG5D1/"); // 0-lepton
    //SH::scanDir(sampleHandler, "/afs/cern.ch/work/d/dbuesche/public/xAODs/DAOD_HIGG5D2/"); // 1-lepton
    //SH::scanDir(sampleHandler, "/afs/cern.ch/work/d/dbuesche/public/xAODs/DAOD_HIGG2D4/"); // 2-lepton
  }
  else {
    // read input file
    std::ifstream infile;
    infile.open(sample_in);
    std::string line;
    std::vector<std::string> sample_name_in;

    while (!infile.eof()) {
      getline(infile, line);
      // don't run over commented lines
      if (line.find("#") != std::string::npos) continue;
      //
      sample_name_in.push_back(line);
    }
    infile.close();
    // form tags name
    aod_tag = "CAOD";
    if (sample_name_in[0].find("CAOD") != std::string::npos) aod_tag = "FINAL"; // if we produce teh final histos at this step, maybe useless
    //
    static ConfigStore* config_ana = ConfigStore::createStore(config->get<std::string>("CxAODConfig"));
    bool run_xAOD = !config_ana->get<bool>("autoDetermineSelection");
    //
    if (run_xAOD) {
      std::string selectionName = config_ana->get<std::string>("selectionName");
      if (selectionName == "0lep") ana_tag = "HIGG5D1";
      if (selectionName == "1lep") ana_tag = "HIGG5D2";
      if (selectionName == "2lep") ana_tag = "HIGG2D4";
    }
    else {
      if (sample_name_in[0].find("HIGG5D1") != std::string::npos) ana_tag = "HIGG5D1";
      if (sample_name_in[0].find("HIGG5D2") != std::string::npos) ana_tag = "HIGG5D2";
      if (sample_name_in[0].find("HIGG2D4") != std::string::npos) ana_tag = "HIGG2D4";
    }
    // declare the jobs
    const int n_sample_name_in = sample_name_in.size()-1;
    for (int isam = 0; isam < n_sample_name_in; isam++) {
      SH::scanDQ2 (sampleHandler, sample_name_in[isam]);
      //std::cout << "sample -> " << sample_name_in[isam] << std::endl;
    }
  }
  // Set the name of the input TTree. It's always "CollectionTree"
  // for xAOD files.
  sampleHandler.setMetaString("nc_tree", "CollectionTree");
  //sampleHandler.setMetaString("nc_grid_filter", "AOD.01512594._000099.pool.root.1"); // use only 1 file to run on

  // Print what we found:
  sampleHandler.print();

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler(sampleHandler);

  // remove submit dir before running the job
  //job.options()->setDouble(EL::Job::optRemoveSubmitDir, 1);


  //limit number of events to maxEvents - set in config
  job.options()->setDouble (EL::Job::optMaxEvents, config->get<int>("maxEvents"));
  algorithm->m_maxEvent = (int)job.options()->getDouble(EL::Job::optMaxEvents);
  algorithm->setConfig(config->get<std::string>("CxAODConfig"));

  TupleMaker * tupleMaker = new TupleMaker();
  tupleMaker->configure(config->get<std::string>("TupleConfig"));
 
  job.algsAdd(algorithm);
  job.algsAdd(tupleMaker);

  // Run the job using the local/direct driver:
  if (!grid) {
    EL::DirectDriver driver;
    driver.submit(job, submitDir);
  }
  else {
    EL::PrunDriver driver;
    // form needed names
    std::ostringstream ostr_sample_out;
    ostr_sample_out << "user.%nickname%.%in:name[1]%.%in:name[2]%.%in:name[3]%." << aod_tag << "_" << ana_tag << "." << config->get<std::string>("vtag");
    sample_out = ostr_sample_out.str();
    // useless but could be re-used if needed
    //std::ostringstream ostr_submitDir;
    //ostr_submitDir << "tmp/submit_" << do_what_you_want; // this tmp needs to be created
    //submitDir = ostr_submitDir.str();
    // options
    driver.options()->setString("nc_outputSampleName", sample_out); // output job name
    //
    double nFilesPerJob = config->get<double>("nFilesPerJob");
    if (nFilesPerJob > 0) driver.options()->setDouble("nc_nFilesPerJob", nFilesPerJob);
    //
    double nGBPerJob = config->get<double>("nGBPerJob");
    if (nGBPerJob > 0) driver.options()->setDouble("nc_nGBPerJob", nGBPerJob);
    //
    std::string excludedSite = config->get<std::string>("excludedSite");
    if (excludedSite != "none") driver.options()->setString("nc_excludedSite", excludedSite);
    //
    if (!config->get<bool>("submit")) {
      driver.options()->setDouble("nc_noSubmit", 1);
      driver.options()->setDouble("nc_showCmd", 1);
    }
    // tmp fix
//    driver.options()->setString("nc_rootVer", "5.34.22");
//    driver.options()->setString("nc_cmtConfig", "x86_64-slc6-gcc48-opt");

    //driver.options()->setDouble("nc_mergeOutput", 1); // can't do for CxAOD
    driver.options()->setDouble("nc_mergeOutput", 0); // force to no merge
    // run
    //driver.submit(job, submitDir); // with monitoring
    driver.submitOnly(job, submitDir); // no monitoring
  }

  return 0;
}

