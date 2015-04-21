#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/DiskListLocal.h"
#include "SampleHandler/DiskListEOS.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"

#include "SampleHandler/Sample.h"

#include <stdlib.h> 
#include <vector> 

#include <TSystem.h> 
#include <TFile.h> 

#include "CxAODTools/ConfigStore.h"
#include "CxAODTools/XSectionProvider.h"
#include "CxAODReader/AnalysisReader.h"

void tag(SH::SampleHandler& sh, const std::string& tag);

int main(int argc, char* argv[]) {

  // Take the submit directory from the input if provided:
  std::string submitDir = "submitDir";
  std::string configPath = "data/FrameworkExe/framework-read.cfg";
  if (argc > 1) submitDir = argv[1];
  //if (argc > 2) configPath = argv[2];
  int run(0);
  if (argc > 2) run = atoi(argv[2]);
  // read run config
  static ConfigStore* config = ConfigStore::createStore(configPath);

  // analysis type
  int analysisType(-1);
  analysisType=config->get<int>("analysisType");

  // COM - used for cross section setting and dataset directory reading
  TString comEnergy(config->get<std::string>("COMEnergy"));
  std::cout << "COM Energy for cross sections=" << comEnergy << std::endl;

  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  SH::SampleHandler sampleHandler;

  // choose D4 samples
  std::vector<std::string> sample_names;
  // list all samples here - if they don't exist it will skip
  if(run==0)sample_names.push_back("test");
  //sample_names.push_back("muonData");
  //sample_names.push_back("egammaData");
  //sample_names.push_back("metData");
  if(run==1)sample_names.push_back("Zvv");
  if(run==2)sample_names.push_back("Wev");
  if(run==3)sample_names.push_back("Wmuv");
  if(run==4)sample_names.push_back("Wtauv");
  if(run==5)sample_names.push_back("ttbarallhad");
  if(run==6)sample_names.push_back("ttbarnonall1");
  if(run==7)sample_names.push_back("ttbarnonall2");
  if(run==8)sample_names.push_back("dijet1");  
  //sample_names.push_back("Wlv");
  if(run==9)sample_names.push_back("dijet2");  
  if(run==10)sample_names.push_back("singletop");
  //sample_names.push_back("top");
  if(run==11){
  sample_names.push_back("monoWjjIsrDesD1m50");
  sample_names.push_back("monoWjjIsrDesD1m1300");
  sample_names.push_back("monoWjjIsrDesD5m50");
  sample_names.push_back("monoWjjIsrDesD5m1300");
  sample_names.push_back("monoWjjIsrDesD9m50");
  sample_names.push_back("monoWjjIsrDesD9m1300");
  sample_names.push_back("monoWjjIsrConD1m50");
  sample_names.push_back("monoWjjIsrConD1m1300");
  sample_names.push_back("monoWjjIsrConD5m50");
  sample_names.push_back("monoWjjIsrConD5m1300");
  sample_names.push_back("monoWjjIsrConD9m50");
  sample_names.push_back("monoWjjIsrConD9m1300");
  sample_names.push_back("monoZjjIsrD1m50");
  sample_names.push_back("monoZjjIsrD1m1300");
  sample_names.push_back("monoZjjIsrD5m50");
  sample_names.push_back("monoZjjIsrD5m1300");
  sample_names.push_back("monoZjjIsrD9m50");
  sample_names.push_back("monoZjjIsrD9m1300");
  }
  if(run==12)sample_names.push_back("gamma1");
  if(run==13)sample_names.push_back("gamma2");
  if(run==14)sample_names.push_back("gamma3");
  if(run==15)sample_names.push_back("gamma4");
  if(run==16)sample_names.push_back("gamma5");
  if(run==17)sample_names.push_back("gamma6");
  if(run==18)sample_names.push_back("gamma7");
  if(run==19)sample_names.push_back("Zee");
  if(run==20)sample_names.push_back("Zmumu");
  if(run==21)sample_names.push_back("Ztautau");
  /*sample_names.push_back("191211");
  sample_names.push_back("191212");
  sample_names.push_back("191213");
  sample_names.push_back("191214");
  sample_names.push_back("191215");
  sample_names.push_back("191216");
  sample_names.push_back("191217");
  sample_names.push_back("191218");
  sample_names.push_back("191219");
  sample_names.push_back("191220");
  sample_names.push_back("191221");
  sample_names.push_back("191222");
  sample_names.push_back("191223");
  sample_names.push_back("191224");
  sample_names.push_back("191225");
  sample_names.push_back("191226");
  sample_names.push_back("191227");
  sample_names.push_back("191234");
  sample_names.push_back("191235");
  sample_names.push_back("191236");
  sample_names.push_back("191237");
  sample_names.push_back("191238");
  sample_names.push_back("191239");
  sample_names.push_back("191240");
  sample_names.push_back("191241");
  sample_names.push_back("191242");
  sample_names.push_back("191243");
  sample_names.push_back("191244");*/
  // sample_names.push_back("ZeeB");
  // sample_names.push_back("ZeeC");
  // sample_names.push_back("ZeeL");
  // sample_names.push_back("ZmumuB");
  // sample_names.push_back("ZmumuC");
  // sample_names.push_back("ZmumuL");
  // sample_names.push_back("ZnunuB");
  // sample_names.push_back("ZnunuC");
  // sample_names.push_back("ZnunuL");
  // sample_names.push_back("WenuB");
  // sample_names.push_back("WenuC");
  // sample_names.push_back("WenuL");
  // sample_names.push_back("WmunuB");
  // sample_names.push_back("WmunuC");
  // sample_names.push_back("WmunuL");
  // sample_names.push_back("WtaunuB");
  // sample_names.push_back("WtaunuC");
  // sample_names.push_back("WtaunuL");
  //sample_names.push_back("ttbar");
  // sample_names.push_back("singletop_t");
  // sample_names.push_back("singletop_s");
  // sample_names.push_back("singletop_Wt");

  // where to read data from
  bool eos(false);

  // datasets copied to afs
  //std::string afsdir("/afs/cern.ch/user/y/ychou/private/monoWZH/Dataset/");
  //std::string afsdir("/afs/cern.ch/work/t/thompson/public/DAOD/v0.0.5/");
  //std::string afsdir("/phys/groups/tev/scratch3/users/ytchou/monoWZ/Dataset_CxAOD/13TeV_Amelia/");
  //std::string afsdir("/phys/groups/tev/scratch3/users/ytchou/monoWZ/Dataset_CxAOD/13TeV_arturos/");
  //std::string afsdir("/phys/groups/tev/scratch3/users/ytchou/monoWZ/Dataset_CxAOD/13TeV_anelson/");
  std::string afsdir("/phys/groups/tev/scratch3/users/ytchou/monoWZ/Dataset_CxAOD/13TeV_v01/");
  //std::string afsdir("/phys/groups/tev/scratch3/users/ytchou/monoWZ/Dataset_CxAOD/8TeV/");
  // datasets copied to eos
  TString CxAODver("CxAOD_00-00-05");
  TString xAODver("_p1784");
  TString eosdir("/eos/atlas/atlasgroupdisk/phys-higgs/HSG5/Run2/VH/");
  if (analysisType==0) 
    eosdir+="HIGG5D1_";
  else if (analysisType==1) 
    eosdir+="HIGG5D2_";
  else if (analysisType==2) 
    eosdir+="HIGG2D4_";
  else
    std::cout << "Unknown Analysis Type " << analysisType << std::endl;
  // 
  eosdir+=comEnergy+xAODver+"/"+CxAODver+"/";

  if (eos)
    std::cout << " Looking for directory " << eosdir << std::endl;

  std::string dataset_dir(eosdir);
  if (!eos) dataset_dir=afsdir;

  // Query - I had to put each background in a separate directory
  // for samplehandler to have sensible sample names etc.
  // Is it possible to define a search string for directories and assign all those to a sample name?
  //  SH::scanDir (sampleHandler, list); // apparently it will come

  // tuples are downloaded to same directory so specify CxAOD root file pattern
  for (unsigned int isamp(0) ; isamp<sample_names.size() ; isamp++) {
    std::string sample_name(sample_names.at(isamp));
    std::string sample_dir(dataset_dir+sample_name);

    if (!eos) {
      bool direxists=gSystem->OpenDirectory (sample_dir.c_str());
      if (!direxists) {
	std::cout << " No sample exists: " << sample_name << " , skipping: "  << sample_dir << std::endl;
	continue;
      }
    }

    // eos, local disk or afs
    if (eos) {
      SH::DiskListEOS list(sample_dir,"root://eosatlas/"+sample_dir );
      //SH::DiskListEOS list("eosatlas.cern.ch", sample_dir);
      SH::scanSingleDir (sampleHandler, sample_name, list, "*outputLabel*") ;
    } else {
      SH::DiskListLocal list(sample_dir);
      //SH::scanSingleDir (sampleHandler, sample_name, list, "*outputLabel*") ;
      SH::scanSingleDir (sampleHandler, sample_name, list, "*data_CxAOD*") ;
    }

    //
    SH::Sample* sample=sampleHandler.get(sample_name);
    int nsampleFiles=sample->numFiles();

    std::cout << "Sample name " << sample_name << " with nfiles : " <<  nsampleFiles  << std::endl;
  }


  // Set the name of the input TTree. It's always "CollectionTree"
  // for xAOD files.
  sampleHandler.setMetaString("nc_tree", "CollectionTree");

  // Print what we found:
  sampleHandler.print();

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler(sampleHandler);

  // remove submit dir before running the job
  //job.options()->setDouble(EL::Job::optRemoveSubmitDir, 1);

  // create algorithm, set job options, maniplate members and add our analysis to the job:
  AnalysisReader* algorithm = new AnalysisReader();
 

  //limit number of events to maxEvents - set in config
  job.options()->setDouble (EL::Job::optMaxEvents, config->get<int>("maxEvents"));

  // try different access
  // https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/EventLoop#Access_the_Data_Through_xAOD_EDM
  //job.options()->setString (EL::Job::optXaodAccessMode, EL::Job::optXaodAccessMode_class);
  //job.options()->setString (EL::Job::optXaodAccessMode, EL::Job::optXaodAccessMode_class);

  // set the lepton analysis type and COM
  algorithm->SetAnalysisType(analysisType);
  algorithm->SetCOMEnergy(comEnergy);


  // uncomment me
  job.algsAdd(algorithm);

  //  return 0;

  // Run the job using the local/direct driver:
  EL::DirectDriver driver;
  driver.submit(job, submitDir);

  return 0;
}


