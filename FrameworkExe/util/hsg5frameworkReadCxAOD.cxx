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
  if(run==1)sample_names.push_back("ZnunuB");
  if(run==2)sample_names.push_back("ZnunuC");
  if(run==3)sample_names.push_back("ZnunuL");
  if(run==4)sample_names.push_back("WenuB");
  if(run==5)sample_names.push_back("WenuC");
  if(run==6)sample_names.push_back("WenuL");  
  if(run==7)sample_names.push_back("WmunuB");
  if(run==8)sample_names.push_back("WmunuC");
  if(run==9)sample_names.push_back("WmunuL");
  if(run==10)sample_names.push_back("WtaunuB");
  if(run==11)sample_names.push_back("WtaunuC");
  if(run==12)sample_names.push_back("WtaunuL");  
  if(run==13)sample_names.push_back("ttbarall");
  if(run==14)sample_names.push_back("ttbarnon1");
  if(run==15)sample_names.push_back("ttbarnon2");
  if(run==16)sample_names.push_back("singletop_t");
  if(run==17)sample_names.push_back("singletop_s");
  if(run==18)sample_names.push_back("singletop_Wt");
  if(run==19)sample_names.push_back("ZeeB");
  if(run==20)sample_names.push_back("ZeeC");
  if(run==21)sample_names.push_back("ZeeL");  
  if(run==22)sample_names.push_back("ZmumuB");
  if(run==23)sample_names.push_back("ZmumuC");
  if(run==24)sample_names.push_back("ZmumuL");
  if(run==25)sample_names.push_back("ZtautauB");
  if(run==26)sample_names.push_back("ZtautauC");
  if(run==27)sample_names.push_back("ZtautauL");
  if(run==28)sample_names.push_back("dijet1");  
  if(run==29)sample_names.push_back("dijet2");  
  if(run==30){
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
  sample_names.push_back("monoWjjWwxxm50");
  sample_names.push_back("monoWjjWwxxm1300");
  sample_names.push_back("monoWjjSimDesSsdMed100m50");
  sample_names.push_back("monoWjjSimDesSsdMed1500m50");
  sample_names.push_back("monoWjjSimDesSsdMed1500m1300");
  sample_names.push_back("monoWjjSimDesSvdMed100m50");
  sample_names.push_back("monoWjjSimDesSvdMed1500m50");
  sample_names.push_back("monoWjjSimDesSvdMed1500m1300");
  sample_names.push_back("monoWjjSimDesTsdMed100m50");
  sample_names.push_back("monoWjjSimDesTsdMed1500m50");
  sample_names.push_back("monoWjjSimDesTsdMed1500m1300");
  sample_names.push_back("monoWjjSimConSsdMed100m50");
  sample_names.push_back("monoWjjSimConSsdMed1500m50");
  sample_names.push_back("monoWjjSimConSsdMed1500m1300");
  sample_names.push_back("monoWjjSimConSvdMed100m50");
  sample_names.push_back("monoWjjSimConSvdMed1500m50");
  sample_names.push_back("monoWjjSimConSvdMed1500m1300");
  sample_names.push_back("monoZjjZzxxm50");
  sample_names.push_back("monoZjjZzxxm1300");
  sample_names.push_back("monoZjjSimSsdMed100m50");
  sample_names.push_back("monoZjjSimSsdMed1500m50");
  sample_names.push_back("monoZjjSimSsdMed1500m1300");
  sample_names.push_back("monoZjjSimSvdMed100m50");
  sample_names.push_back("monoZjjSimSvdMed1500m50");
  sample_names.push_back("monoZjjSimSvdMed1500m1300");
  sample_names.push_back("monoZjjSimTsdMed100m50");
  sample_names.push_back("monoZjjSimTsdMed1500m50");
  sample_names.push_back("monoZjjSimTsdMed1500m1300");
  sample_names.push_back("monoHbb_mx1_xdxhDh");
  sample_names.push_back("monoHbb_mx65_xdxhDh");
  sample_names.push_back("monoHbb_mx1000_xdxhDh");
  sample_names.push_back("monoHbb_mx1_xgxFhDh");
  sample_names.push_back("monoHbb_mx65_xgxFhDh");
  sample_names.push_back("monoHbb_mx1000_xgxFhDh");
  sample_names.push_back("monoHbb_mx1_zpzp100");
  sample_names.push_back("monoHbb_mx65_zpzp100");
  sample_names.push_back("monoHbb_mx1000_zpzp100");
  
  }
  if(run==31)sample_names.push_back("gamma0"); 
  if(run==32)sample_names.push_back("gamma1");
  if(run==33)sample_names.push_back("gamma2");
  if(run==34)sample_names.push_back("gamma3");
  if(run==35)sample_names.push_back("gamma4");
  if(run==36)sample_names.push_back("gamma5");
  if(run==37)sample_names.push_back("gamma6");
  if(run==38)sample_names.push_back("gamma7");


  // where to read data from
  bool eos(false);

  // datasets copied to afs
  //std::string afsdir("/afs/cern.ch/user/y/ychou/private/monoWZH/Dataset/");
  //std::string afsdir("/afs/cern.ch/work/t/thompson/public/DAOD/v0.0.5/");
  //std::string afsdir("/phys/groups/tev/scratch3/users/ytchou/monoWZ/Dataset_CxAOD/13TeV_Amelia/");
  //std::string afsdir("/phys/groups/tev/scratch3/users/ytchou/monoWZ/Dataset_CxAOD/13TeV_arturos/");
  //std::string afsdir("/phys/groups/tev/scratch3/users/ytchou/monoWZ/Dataset_CxAOD/13TeV_anelson/");
  //std::string afsdir("/phys/groups/tev/scratch3/users/ytchou/monoWZ/Dataset_CxAOD/13TeV_v01/");
  std::string afsdir("/phys/groups/tev/scratch4/users/ytchou/Dataset_CxAOD/HIGG5D1_v01/");
  //if(run >= 31)  afsdir = "/phys/groups/tev/scratch4/users/ytchou/Dataset_CxAOD/13TeV_v01/";
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


