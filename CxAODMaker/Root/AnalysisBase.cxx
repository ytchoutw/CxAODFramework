#include "EventLoop/Job.h"
#include "EventLoop/StatusCode.h"
#include "EventLoop/Worker.h"
#include "EventLoop/OutputStream.h"
#include "xAODRootAccess/TStore.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/PhotonContainer.h"
// EDM includes:
#include "xAODCore/AuxInfoBase.h"
#include "xAODCore/ShallowAuxInfo.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODTracking/Vertex.h"
#include "xAODRootAccess/tools/ReturnCheck.h"

#include "CxAODMaker/AnalysisBase.h"

#include "CxAODMaker/MuonHandler.h"
#include "CxAODMaker/JetHandler.h"
#include "CxAODMaker/ElectronHandler.h"
#include "CxAODMaker/PhotonHandler.h"
#include "CxAODMaker/FatJetHandler.h"
#include "CxAODMaker/METHandler.h"
#include "CxAODMaker/TruthParticleHandler.h"
#include "CxAODMaker/EventInfoHandler.h"
#include "CxAODMaker/EventSelector.h"

#include "CxAODTools/VHbb0lepEvtSelection.h"
#include "CxAODTools/VHbb1lepEvtSelection.h"
#include "CxAODTools/VHbb2lepEvtSelection.h"
#include "CxAODTools/VBFbbAEvtSelection.h"

#include "TFile.h"
#include "TTree.h"
#include "TTreeFormula.h"

// this is needed to distribute the algorithm to the workers

ClassImp(AnalysisBase)

AnalysisBase::AnalysisBase() :
  m_jetHandler(nullptr),
  m_fatjetHandler(nullptr),
  m_muonHandler(nullptr),
  m_electronHandler(nullptr),
  m_photonHandler(nullptr),
  m_eventInfoHandler(nullptr),
  m_METHandler(nullptr),
  m_selector(nullptr),
  m_config(nullptr),
  m_configPath("none"),
  m_validate(false),
  m_event(nullptr),
  m_maxEvent(-999), 
  m_eventCounter(0),
  m_eventWeightCounter(0),
  m_histEventCount(0)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}

EL::StatusCode AnalysisBase::setupJob(EL::Job& job) {
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.
  job.useXAOD();

  // let's initialize the algorithm to use the xAODRootAccess package
  xAOD::Init("AnalysisBase").ignore(); // call before opening first file

  // tell EventLoop about our output xAOD:
  EL::OutputStream out("outputLabel");
  job.outputAdd (out);
 
  //xAOD::TReturnCode::enableFailure();
  //CP::SystematicCode::enableFailure();
 
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode AnalysisBase::histInitialize() {
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
  
  if (m_histEventCount) {
    // TODO why is histInitialize() called after fileExecute() ??
    Warning("histInitialize()", "Histograms already initialized! Skipping histInitialize()...");
    return EL::StatusCode::SUCCESS;
  }

  // event counts from meta data
  m_histEventCount = new TH1D("MetaData_EventCount", "MetaData_EventCount", 8, 0.5, 8.5);
  m_histEventCount -> GetXaxis() -> SetBinLabel(1, "nEvents initial");
  m_histEventCount -> GetXaxis() -> SetBinLabel(2, "nEvents selected in");
  m_histEventCount -> GetXaxis() -> SetBinLabel(3, "nEvents selected out");
  m_histEventCount -> GetXaxis() -> SetBinLabel(4, "sumOfWeights initial");
  m_histEventCount -> GetXaxis() -> SetBinLabel(5, "sumOfWeights selected in");
  m_histEventCount -> GetXaxis() -> SetBinLabel(6, "sumOfWeights selected out");
  m_histEventCount -> GetXaxis() -> SetBinLabel(7, "nEvents in this job");
  m_histEventCount -> GetXaxis() -> SetBinLabel(8, "sumOfWeights in this job");
  wk() -> addOutput(m_histEventCount);

  // event counts from meta data
  m_histDatasetInfo = new TH1D("MetaData_DatasetInfo", "MetaData_DataSetInfo", 1, 0.5, 1.5);
  m_histDatasetInfo -> GetXaxis() -> SetBinLabel(1, "dataset ID");
  wk() -> addOutput(m_histDatasetInfo);

  Info("histInitialize()", "Histograms initialized.");

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode AnalysisBase::fileExecute() {
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed

  if (!m_histEventCount) {
    // TODO why is histInitialize() called after fileExecute() ??
    Warning("fileExecute()", "Histograms not initialized! Calling histInitialize()...");
    histInitialize();
  }

  //----------------------------
  // Meta data
  //--------------------------- 

  // get the MetaData tree once a new file is opened, with
  TTree *MetaData = dynamic_cast<TTree*>(wk()->inputFile()->Get("MetaData"));
  if (!MetaData) {
    // TODO: report Error and return FAILURE?
    Warning("fileExecute()", "MetaData not found!");
    return EL::StatusCode::SUCCESS;
  }
  MetaData->LoadTree(0);

  // extract the information from the EventBookkeepers branch
  TTreeFormula tfNevents("tf", "EventBookkeepers.m_nAcceptedEvents", MetaData);
  TTreeFormula tfSumW("tf", "EventBookkeepers.m_nWeightedAcceptedEvents", MetaData);
  tfNevents.UpdateFormulaLeaves();
  tfSumW.UpdateFormulaLeaves();
  if (tfNevents.GetNdata() < 2 || tfSumW.GetNdata() < 2) {
    // TODO: report Error and return FAILURE?
    Warning("fileExecute()", "Could not read sum of weights from MetaData!");
    return EL::StatusCode::SUCCESS;
  }

  // read meta data
  Info("fileExecute()", "Meta data from this file:");
  Info("fileExecute()", "Initial  events         = %f", tfNevents.EvalInstance(1));
  Info("fileExecute()", "Selected events         = %f", tfNevents.EvalInstance(0));
  Info("fileExecute()", "Initial  sum of weights = %f", tfSumW.EvalInstance(1));
  Info("fileExecute()", "Selected sum of weights = %f", tfSumW.EvalInstance(0));
  m_histEventCount -> Fill(1, tfNevents.EvalInstance(1)); // nEvents initial
  m_histEventCount -> Fill(2, tfNevents.EvalInstance(0)); // nEvents selected in
  m_histEventCount -> Fill(4, tfSumW.EvalInstance(1)); // sumOfWeights initial
  m_histEventCount -> Fill(5, tfSumW.EvalInstance(0)); // sumOfWeights selected in

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode AnalysisBase::changeInput(bool firstFile) {
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode AnalysisBase::initialize() {
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  // get TEvent
  m_event = wk()->xaodEvent();
  
  // get configuration from steerfile
  m_config = ConfigStore::createStore(m_configPath);
  if ( ! m_config ) {
    Error("initialize()","Couldn't create ConfigStore from file : %s",m_configPath.c_str());
    return EL::StatusCode::FAILURE;
  }

  // sample name
  TString sampleName = wk()->metaData()->getString("sample_name");
  Info("initialize()", "Sample name = %s", sampleName.Data());
  // as a check, let's see the number of events in our xAOD (long long int)
  Info("initialize()", "Number of events in file   = %lli", m_event->getEntries());
  if(m_maxEvent < 0) m_maxEvent = m_event->getEntries() ;
  Info("initialize()", "Number of events to run on = %li", m_maxEvent);

  // count number of events
  m_eventCounter = 0;
  m_eventWeightCounter = 0;

  // initialize EventInfoHandler and read info of first event
  m_eventInfoHandler = new EventInfoHandler(*m_config);
  if (m_eventInfoHandler->initialize() != EL::StatusCode::SUCCESS) {
    Error("execute()", "Failed to initialize tools in EventInfoHandler!");
    return EL::StatusCode::FAILURE;
  }
  m_eventInfoHandler->executeEvent(m_event);
  int isMC = m_eventInfoHandler->get_isMC();
  Info("initialize()", "First event is MC          = %i ", isMC);


  //---------------------------
  // retrieve list of systematics
  //---------------------------
  
  m_variations.clear();
  // Nominal is always present
  m_variations.push_back("Nominal");
  // Original (not calibrated)
  bool storeOrig;
  m_config->getif<bool>("storeOriginal", storeOrig);
  if (storeOrig) {
    m_variations.push_back("Original");
  }
  // variations
  std::vector<std::string> variations;
  m_config->getif< std::vector<std::string> >("variations", variations);
  std::vector<std::string> pulls = {"1down", "1up"};
  for (std::string name : variations) {
    for (std::string pull : pulls) {
      m_variations.push_back((name + "__" + pull).c_str());
    }
  }
  // TODO add symmetric variations
  
  
  //---------------------------
  // initialize handlers
  //---------------------------
  
  std::string container;
  std::string name;
  name = "truthParticle";
  m_config->getif<std::string>(name+"Container",container);
  if( ! container.empty() && isMC ) {
    m_objectHandler.push_back( new TruthParticleHandler(name, *m_config, m_event, *m_eventInfoHandler) );
  }
  container.clear();
  name = "muon";
  m_config->getif<std::string>(name+"Container",container);
  if ( ! container.empty() ) {
    m_muonHandler = new MuonHandler(name, *m_config, m_event, *m_eventInfoHandler);
    m_objectHandler.push_back( m_muonHandler );
  }
  container.clear();
  name = "electron";
  m_config->getif<std::string>(name+"Container",container);
  if ( ! container.empty() ) {  
    m_electronHandler = new ElectronHandler(name, *m_config, m_event, *m_eventInfoHandler);
    m_objectHandler.push_back( m_electronHandler );
  }
  container.clear();
  name = "photon";
  m_config->getif<std::string>(name+"Container",container);
  if ( ! container.empty() ) {
    m_photonHandler = new PhotonHandler(name, *m_config, m_event, *m_eventInfoHandler);
    m_objectHandler.push_back( m_photonHandler );
  }
  container.clear();
  name = "jet";
  m_config->getif<std::string>(name+"Container",container);
  if ( ! container.empty() ) {
    m_jetHandler = new JetHandler(name, *m_config, m_event, *m_eventInfoHandler);
    m_objectHandler.push_back( m_jetHandler );
  }
  container.clear();
  name = "jetSpectator";
  m_config->getif<std::string>(name+"Container",container);
  if ( ! container.empty() ) {
    JetHandler* jet_spectator = new JetHandler(name, *m_config, m_event, *m_eventInfoHandler);
    m_objectHandler.push_back( jet_spectator );
  }
  container.clear();
  name = "fatJet";
  m_config->getif<std::string>(name+"Container",container);
  if ( ! container.empty() ) {
    m_fatjetHandler = new FatJetHandler(name, *m_config, m_event, *m_eventInfoHandler);
    m_objectHandler.push_back( m_fatjetHandler );
  }
  container.clear();

  
  
  //---------------------------
  // initialize tools and set systematics
  //---------------------------

  for (ObjectHandlerBase * handler : m_objectHandler) {
    if (handler->initializeTools() != EL::StatusCode::SUCCESS) {
      Error("execute()", "Failed to initialize tools!");
      return EL::StatusCode::FAILURE;
    }
    if (isMC) {
      if (handler->addCPVariations(m_variations) != EL::StatusCode::SUCCESS) {
        Error("execute()", "Failed to add CP variations!");
        return EL::StatusCode::FAILURE;
      }
    }
  }

  // check if collections for OR are defined
  if ( !m_muonHandler || !m_electronHandler || !m_jetHandler || !m_photonHandler) {
    Error("initialize()","Not all collections for Overlap Removal are defined!");
    return EL::StatusCode::FAILURE;
  }

  // initialize METHandler
  m_METHandler = new METHandler(m_config, m_event);


  // initialize EventSelector
  m_selector = new EventSelector(*m_config);

  //output xAOD
  TFile * file = wk()->getOutputFile ("outputLabel");
  if(!m_event->writeTo(file).isSuccess()){
    Error("initialize()", "Failed to write event to ouput file!");
    return EL::StatusCode::FAILURE;
  }
  
  
  
  //---------------------------
  // initialize event selection
  //---------------------------

  bool applySelection = false;
  m_config->getif<bool>("applyEventSelection", applySelection);
  if (applySelection) {
    bool autoDetermineSelection;
    m_config->getif<bool>("autoDetermineSelection", autoDetermineSelection);
    std::string selectionName;
    if (!autoDetermineSelection) {
      m_config->getif<std::string>("selectionName", selectionName);
    } else {
      if      (sampleName.Contains("HIGG5D1")) selectionName = "0lep";
      else if (sampleName.Contains("HIGG5D2")) selectionName = "1lep";
      else if (sampleName.Contains("HIGG2D4")) selectionName = "2lep";
      else if (sampleName.Contains("HIGR2D2")) selectionName = "vbfa"; // todo : check HIGR2d2
      else {
        Error("initialize()", "Could not auto determine selection!");
        return EL::StatusCode::FAILURE;
      }
    }

    Info("initialize()", "Applying selection: %s", selectionName.c_str());
    if      (selectionName == "0lep") m_selector->setSelection(new VHbb0lepEvtSelection());
    else if (selectionName == "1lep") m_selector->setSelection(new VHbb1lepEvtSelection());
    else if (selectionName == "2lep") m_selector->setSelection(new VHbb2lepEvtSelection());
    else if (selectionName == "vbfa") m_selector->setSelection(new VBFbbAEvtSelection());
    else {
      Error("initialize()", "Unknown selection requested!");
      return EL::StatusCode::FAILURE;
    }
  }

  m_selector->setJets(m_jetHandler);
  m_selector->setFatJets(m_fatjetHandler);
  m_selector->setMuons(m_muonHandler);
  m_selector->setElectrons(m_electronHandler);
  m_selector->setPhotons(m_photonHandler);
  m_selector->setMET(m_METHandler);
  m_selector->setEventInfo(m_eventInfoHandler);


  return EL::StatusCode::SUCCESS;

}


EL::StatusCode AnalysisBase::execute() {
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  // print every 100 events, so we know where we are:
  if ( (m_eventCounter % 100) == 0 ) {
    Info("execute()", "Event number = %li", m_eventCounter);
  }
  ++m_eventCounter;
   
  //----------------------------
  // Event information
  //--------------------------- 

  // first event was executed in initialize()
  if (m_eventCounter > 1) {
    m_eventInfoHandler->executeEvent(m_event);
  }

  // sum the weights of this job
  m_eventWeightCounter += m_eventInfoHandler->get_MCEventWeight();
  
  //---------------------------
  //perform object calibrations
  //---------------------------
  for (ObjectHandlerBase * handler : m_objectHandler) {
    if( handler->setObjects() !=  EL::StatusCode::SUCCESS ) {
      Error("execute()","Failed to set objects!");
      return EL::StatusCode::FAILURE;
    }

    if( handler->calibrate() !=  EL::StatusCode::SUCCESS ) {
      Error("execute()","Failed to calibrate objects!");
      return EL::StatusCode::FAILURE;
    }

    if( handler->select() !=  EL::StatusCode::SUCCESS ) {
      Error("execute()","Failed to select objects!");
      return EL::StatusCode::FAILURE;
    }
  }




  //------------------------
  //perform MET calculation
  //------------------------

  m_METHandler->setMET(m_electronHandler->getInParticles(),
		       m_muonHandler->getInParticles(),
		       m_jetHandler->getInParticles());



  //------------------------
  // do event selection
  //------------------------

  bool eventPassed = false;
  if(m_selector->performSelection(eventPassed) != EL::StatusCode::SUCCESS) {
    Error("execute()", "Failure during event selection");
    return EL::StatusCode::FAILURE;
  }

  //----------------------
  // fill output container
  //----------------------

  if (eventPassed) {
    // event info
    m_eventInfoHandler->fillOutputContainer(m_event);
    // objects
    for (ObjectHandlerBase * handler : m_objectHandler) {
      if (handler->fillOutputContainer() != EL::StatusCode::SUCCESS) {
        Error("execute()", "Failed to fill output container!");
        return EL::StatusCode::FAILURE;
      }
      if (m_validate)
	handler->counter(); // count the size of the arrays
    }
    // MET
    if (m_METHandler->fillOutputContainer() != EL::StatusCode::SUCCESS) {
      Error("execute()", "Failed to fill output container!");
      return EL::StatusCode::FAILURE;
    }
  }



  //-------------------------
  // clean memory allocations
  //-------------------------
  for (ObjectHandlerBase * handler : m_objectHandler) {
    if( handler->clearEvent() !=  EL::StatusCode::SUCCESS ) {
      Error("execute()","Failed to clear event!");
      return EL::StatusCode::FAILURE;
    }
  }
  m_METHandler->clearEvent();
  

  // skip all further execute() and postExecute() if !eventPassed
  if (!eventPassed) {
    // event info is cleared here or in postExecute()
    m_eventInfoHandler->clearEvent();
    wk()->skipEvent();
  }
  
  return EL::StatusCode::SUCCESS;

}


EL::StatusCode AnalysisBase::postExecute() {
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  
  
  //--------------------------
  //save the event in the xAOD
  //--------------------------
  if(m_event->fill() < 0){
    Error("execute()", "Failed writing event to output file!");
  };
  m_histEventCount -> Fill(3); // nEvents selected out
  m_histEventCount -> Fill(6, m_eventInfoHandler->get_MCEventWeight()); // sumOfWeights selected out
  m_eventInfoHandler->clearEvent();

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode AnalysisBase::finalize() {
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events

  // finalize and close our output xAOD file ( and write MetaData tree)
  TFile * file = wk()->getOutputFile("outputLabel");
  if( ! m_event->finishWritingTo( file ).isSuccess() ) {
    Error("finalize()","Failed to finish writing event to output file!");
    return EL::StatusCode::FAILURE;
  }

  // print counters
  std::cout<< "in validation " << m_validate << std::endl;
  if (m_validate)
    for (ObjectHandlerBase * handler : m_objectHandler) 
      handler->counter(1); // print the size of the arrays
    



  // delete handlers
  delete m_eventInfoHandler;
  for (ObjectHandlerBase * handler : m_objectHandler) {
    delete handler;
    handler = 0;
  }

  Info("finalize()", "Number of events:");
  Info("finalize()", "  in input file (meta data) = %li", (long) m_histEventCount -> GetBinContent(2));
  Info("finalize()", "  limit (config)            = %li", m_maxEvent);
  Info("finalize()", "  processed                 = %li", m_eventCounter);
  Info("finalize()", "  written to output         = %li", (long) m_histEventCount -> GetBinContent(3));

  return EL::StatusCode::SUCCESS;

}


EL::StatusCode AnalysisBase::histFinalize() {
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.

  // write meta-data histograms to CxAOD file directly, 
  TFile * file = wk()->getOutputFile("outputLabel");
  if (file && m_histEventCount) {
    m_histEventCount -> Fill(7, m_eventCounter); // events in this job
    m_histEventCount -> Fill(8, m_eventWeightCounter); // sumOfWeights in this job
    file->cd();
    m_histEventCount->Write();
  }

  return EL::StatusCode::SUCCESS;
}
