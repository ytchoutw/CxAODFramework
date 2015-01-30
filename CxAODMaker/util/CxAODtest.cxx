#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/DiskListLocal.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"

#include <stdlib.h> 

#include "CxAODMaker/AnalysisBase.h"
#include "CxAODTools/ConfigStore.h"

int main(int argc, char* argv[]) {

  // Take the submit directory from the input if provided:
  std::string submitDir = "submitDir";
  std::string configPath = "data/FrameworkExe/framework-run.cfg";
  if (argc > 1) submitDir = argv[1];
  if (argc > 2) configPath = argv[2];

  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  SH::SampleHandler sampleHandler;
 // SH::scanDir (sampleHandler, "/afs/cern.ch/atlas/project/PAT/xAODs/r5597/"); //data
  //SH::scanDir(sampleHandler, "./testInput/");
  //SH::scanDir(sampleHandler, "./testOut/data-outputLabel/");
  //SH::scanDir(sampleHandler, "/afs/cern.ch/work/d/dbuesche/public/xAODs/goetz_140901/");
  //SH::scanDir(sampleHandler, "/afs/cern.ch/atlas/project/PAT/xAODs/r5591/"); //MC
  SH::DiskListLocal list("/afs/cern.ch/atlas/project/PAT/xAODs/r5591");
  SH::scanDir(sampleHandler, list, "AOD.01494882._111853.pool.root.1");
  //SH::scanDir(sampleHandler, "./inputDir/"); //MC
  //SH::scanDir(sampleHandler, "/afs/cern.ch/work/d/dbuesche/public/xAODs/r5591/");

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
  AnalysisBase* algorithm = new AnalysisBase();
 
  // read run config
  static ConfigStore* config = ConfigStore::createStore(configPath);

  //limit number of events to maxEvents - set in config
  job.options()->setDouble (EL::Job::optMaxEvents, config->get<int>("maxEvents"));
  algorithm->m_maxEvent = (int)job.options()->getDouble(EL::Job::optMaxEvents);
  algorithm->setConfig(config->get<std::string>("CxAODConfig"));

  job.algsAdd(algorithm);

  // Run the job using the local/direct driver:
  EL::DirectDriver driver;
  driver.submit(job, submitDir);

  return 0;
}

