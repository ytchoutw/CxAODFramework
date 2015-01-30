// Event Loop includes
#include "EventLoop/Job.h"
#include "EventLoop/StatusCode.h"
#include "EventLoop/Worker.h"
#include "EventLoop/OutputStream.h"
// xAOD includes
#include "xAODEventInfo/EventInfo.h"
#include "xAODJet/JetContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODJet/Jet.h"
#include "xAODEgamma/Electron.h"
#include "xAODMuon/Muon.h"
// packages includes
#include "TupleMaker/TupleMaker.h"
#include "TupleReader/Tuple.h"

// tools
#include "CxAODTools/ConfigStore.h"
// ROOT includes
#include "TTree.h"
#include "TFile.h"


// this is needed to distribute the algorithm to the workers
ClassImp(TupleMaker)



TupleMaker :: TupleMaker () :
  m_jetsNameIn("none"),
  m_fatJetsNameIn("none"),
  m_muonsNameIn("none"),
  m_electronsNameIn("none"),
  m_metNameIn("none"),
  m_eventName(""),
  m_useEventInfo(false),
  m_event(0),
  m_isMC(false),
  m_superDecorator()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
  
  
}


void TupleMaker::configure(std::string configPath) {
  ConfigStore* config = ConfigStore::createStore(configPath);
  m_jetsNameIn = config->get<std::string>("TupleMaker.JetsIn");
  m_fatJetsNameIn = config->get<std::string>("TupleMaker.FatJetsIn");
  m_muonsNameIn = config->get<std::string>("TupleMaker.MuonsIn");
  m_electronsNameIn = config->get<std::string>("TupleMaker.ElectronsIn");
  m_metNameIn = config->get<std::string>("TupleMaker.MetIn");
  m_filename = config->get<std::string>("TupleMaker.Label");
  config->getif<std::vector<std::string> >("TupleMaker.Variations",m_variations) ;
  if(m_variations.size()==0) {
    m_variations.push_back("Nominal");
  }
  m_variationMode = FILE;
  std::string variationModeStr="file";
  config->getif<std::string>("TupleMaker.VariationMode",variationModeStr);
  if( variationModeStr == "none") {
    m_variationMode = NONE;
  } else if( variationModeStr=="file")  {
    m_variationMode = FILE;
  } else if(variationModeStr=="tree") {
    m_variationMode = TREE;
  } else if(variationModeStr=="block") {
    m_variationMode = BLOCK;
  }

  m_nominalName="Nominal";
  config->getif<std::string>("TupleMaker.NominalName",m_nominalName);

  m_useEventInfo = false;
  config->getif<bool>("TupleMaker.UseEventInfo",m_useEventInfo);
  delete config;
}

EL::StatusCode TupleMaker :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  job.useXAOD();
  xAOD::Init( "TupleMaker" ).ignore();
  
  if( m_variationMode == FILE) {
    for( int i=0,n=m_variations.size();i<n;++i) {
      const std::string & variationName = m_variations[i];
      EL::OutputStream out(m_filename+"_"+variationName);
      job.outputAdd(out);
    }
  } else {
    EL::OutputStream out(m_filename);
    job.outputAdd(out);
  }
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TupleMaker :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TupleMaker :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TupleMaker :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TupleMaker :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  //------------------------------------------------------------
  // Create store from steerfile
  //------------------------------------------------------------
  //m_config = Store::createStore( m_steerFile.c_str() );
  //if ( ! m_config ) {
  //  Error("initialize()","Couldn't create Store! m_steerFile = %s",m_steerFile.c_str());
  //  return EL::StatusCode::FAILURE;
  //}
  
  Info( "initialize()" , " jetsNameIn      = %s" , m_jetsNameIn.c_str()      );
  Info( "initialize()" , " fatJetsNameIn   = %s" , m_fatJetsNameIn.c_str()      );
  Info( "initialize()" , " muonsNameIn     = %s" , m_muonsNameIn.c_str()     );
  Info( "initialize()" , " electronsNameIn = %s" , m_electronsNameIn.c_str() );

  m_eventCounter = 0;

  m_event = wk()->xaodEvent();

  Info("initialize()","Number of events = %lli", m_event->getEntries() );

  if( m_variationMode == NONE) {
    Info("initialize()"," variation mode = NONE");
  } else  if( m_variationMode == FILE) {
    Info("initialize()"," variation mode = FILE");
  } else if( m_variationMode == TREE) {
    Info("initialize()"," variation mode = TREE");
  } else if( m_variationMode == BLOCK) {
    Info("initialize()"," variation mode = BLOCK");
  }
  
  if( m_variationMode == NONE) {
    TupleInfo info;
    info.variation = "Nominal";
    info.doDeco=true;
    TFile * f = wk()->getOutputFile(m_filename);
    if( !f) { 
      Error( "initialize()" , "Failed to get output file");
      return EL::StatusCode::FAILURE;
    }
    TTree * tree = new TTree("tupletest","tupletest");
    tree->SetDirectory(f);
    if( !tree) {
      Error("initialize()","Failed to get the output tree!");
      return EL::StatusCode::FAILURE;
    }
    Tuple * tuple = new Tuple();
    tuple->DefineBranches(tree);
    Info("initialize()","Branches defined");
    info.tuple = tuple;
    info.tree = tree;
    m_tuples.push_back(info);
    m_trees.push_back(tree);
  } else if( m_variationMode == FILE) {
    for(int i = 0,n=m_variations.size();i<n;++i) {
      const std::string & variationName = m_variations[i];
      Info("initialize()" , variationName.c_str());
      TFile * f = wk()->getOutputFile(m_filename+"_"+variationName);
      if( !f) { 
	Error( "initialize()" , "Failed to get output file");
	return EL::StatusCode::FAILURE;
      }
      TTree * tree = new TTree("tupletest","tupletest");
      tree->SetDirectory(f);
      if( !tree) {
	Error("initialize()","Failed to get the output tree!");
	return EL::StatusCode::FAILURE;
      }
      Tuple * tuple = new Tuple();
      tuple->DefineBranches(tree);
      Info("initialize()","Branches defined");
      TupleInfo info;
      info.variation = variationName;
      info.tree = tree;
      info.tuple = tuple;
      if( variationName=="Original")
	info.doDeco=false;
      m_tuples.push_back(info);
      m_trees.push_back(tree);
    }
  } else if( m_variationMode == TREE) {
    TFile * f = wk()->getOutputFile(m_filename);
    if( !f) { 
      Error( "initialize()" , "Failed to get output file");
      return EL::StatusCode::FAILURE;
    }
    for(int i = 0,n=m_variations.size();i<n;++i) {
      const std::string & variationName = m_variations[i];
      std::string treeName = "tupletest_"+variationName;
      TTree * tree = new TTree(treeName.c_str(),treeName.c_str());
      tree->SetDirectory(f);
      if( !tree) {
	Error("initialize()","Failed to get the output tree!");
	return EL::StatusCode::FAILURE;
      }
      Tuple * tuple = new Tuple();
      tuple->DefineBranches(tree);
      Info("initialize()","Branches defined");
      
      TupleInfo info;
      info.variation = variationName;
      info.tree= tree;
      info.tuple = tuple;
      if(variationName=="Original")
	info.doDeco=false;
      m_tuples.push_back(info);
      m_trees.push_back(tree);
    }
  } else if(m_variationMode == BLOCK) {
    TFile * f = wk()->getOutputFile(m_filename);
    if( !f) { 
      Error( "initialize()" , "Failed to get output file");
      return EL::StatusCode::FAILURE;
    }
    std::string treeName = "tupletest";
    TTree * tree = new TTree(treeName.c_str(),treeName.c_str());
    tree->SetDirectory(f);
    for(int i = 0,n=m_variations.size();i<n;++i) {
      const std::string & variationName = m_variations[i];
      if( !tree) {
	Error("initialize()","Failed to get the output tree!");
	return EL::StatusCode::FAILURE;
      }
      Tuple * tuple = new Tuple(variationName);
      tuple->DefineBranches(tree);
      Info("initialize()","Branches defined");
      TupleInfo info;
      info.variation = variationName;
      info.tree = tree;
      info.tuple = tuple;
      if(variationName=="Original")
	info.doDeco=false;
      m_tuples.push_back(info);
    }
    m_trees.push_back(tree);
  }
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TupleMaker :: execute ()
{

  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  if( m_eventCounter % 1000 == 0) Info("execute()","Event number = %i",m_eventCounter);
  m_eventCounter++;
  
  m_isMC = isMC();
  if( m_variationMode == NONE ) {
    processEventInfo(m_tuples[0]); 
    processJets(m_tuples[0]);
    processFatJets(m_tuples[0]);
    processMuons(m_tuples[0]);
    processElectrons(m_tuples[0]);
    processMET(m_tuples[0]);
  } else {
    if( m_variationMode == BLOCK) 
      processEventInfo(m_tuples[0]);
    for( int i =0,n=m_variations.size();i<n;++i) {
      if( m_variationMode != BLOCK) {
	processEventInfo(m_tuples[i]);
      }
      processJets(m_tuples[i]);
      processFatJets(m_tuples[i]);
      processMuons(m_tuples[i]);
      processElectrons(m_tuples[i]);
      if(m_variations[i]!="Original")
	processMET(m_tuples[i]);
    }
  }
  //m_tree->Fill();
  for( int i=0,n=m_trees.size();i<n;++i) {
    (m_trees[i])->Fill();
  }
  // then process muons, taus, other collections etc
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TupleMaker :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TupleMaker :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.
  //m_file->Write();
  //m_file->Close();
  //m_tree->Write();
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TupleMaker :: histFinalize ()
{
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
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TupleMaker :: processJets(TupleInfo & info)
{
  //Info("processJets","1: %s",info.jetsName.c_str());
  const xAOD::JetContainer * jets = 0;
  if( info.jetsName=="") { // name hasn't been set yet
    std::string objName = m_jetsNameIn; // get the basename of the container
    if( info.variation!="") { // add the variation name
      objName+="___"+info.variation;
    }
    // now try to retrieve this
    if( m_event->retrieve(jets, objName ).isSuccess() ) {
      // it worked
      info.jetsName = objName; // remember the name for future reference
    } else {
      // ok, maybe this variation doesn't exist - lets look for the nominal input
      // unless we wanted original - in this case skip
      if( info.variation=="Original") {
	Error("execute","Original containers requested but not found");
	return EL::StatusCode::FAILURE;
      }
      objName = m_jetsNameIn+"___"+m_nominalName;
      if( m_event->retrieve(jets,objName).isSuccess() ) {
	// ok, the nominal version exists
	info.jetsName = objName;
      } else {
	// nothing found - could also look for the basename here.. error for now
	Error("execute","Failed to retrieve %s container.", objName.c_str());
	return EL::StatusCode::FAILURE;
      }
    }
  } else {
    if(!m_event->retrieve(jets,info.jetsName).isSuccess() ) {
      Error("execute","Failed to retrieve %s container.", info.jetsName.c_str());
      return EL::StatusCode::FAILURE;
    }
  }
  //Info("processJets","2: %s",info.jetsName.c_str());
  Tuple * tuple = info.tuple;
  // initialize the tuple
  tuple->njet=0;
  
  // loop over jets
  int ijet = 0;
  for( xAOD::JetContainer::const_iterator iter = jets->begin();
       iter!= jets->end(); ++iter) {
    if( ijet < Tuple::MAXJETS) {
      tuple->jet_pt[ijet] = (*iter)->pt();
      tuple->jet_phi[ijet] = (*iter)->phi();
      tuple->jet_eta[ijet] = (*iter)->eta();
      tuple->jet_E[ijet] = (*iter)->e();
      tuple->jet_ind[ijet] = m_indexDecorator.get(*iter, IndexIntProps::partIndex);

      if(info.doDeco) {
      
	//tuple->jet_good[ijet] = m_superDecorator.get(*iter, JetIntProps::goodJet);
	//tuple->jet_passOR[ijet] = m_superDecorator.get(*iter, JetIntProps::passOR);
	tuple->jet_isVetoJet[ijet] = m_superDecorator.get(*iter, JetIntProps::isVetoJet);
	tuple->jet_isSignal[ijet] = m_superDecorator.get(*iter, JetIntProps::isSignalJet);
	if(m_isMC) 
	  tuple->jet_truth[ijet] = m_superDecorator.get(*iter, JetIntProps::truthLabel);
      }
      ++ijet;
    }
    tuple->njet = ijet;
  }
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TupleMaker :: processMuons(TupleInfo & info)
{
  const xAOD::MuonContainer * muons = 0;
  if( info.muonsName=="") { // name hasn't been set yet
    std::string objName = m_muonsNameIn; // get the basename of the container
    if( info.variation!="") { // add the variation name
      objName+="___"+info.variation;
    }
    // now try to retrieve this
    if( m_event->retrieve(muons, objName ).isSuccess() ) {
      // it worked
      info.muonsName = objName; // remember the name for future reference
    } else {
      // ok, maybe this variation doesn't exist - lets look for the nominal input
      if( info.variation=="Original") {
	Error("execute","Original containers requested but not found");
	return EL::StatusCode::FAILURE;
      }
      objName = m_muonsNameIn+"___"+m_nominalName;
      if( m_event->retrieve(muons,objName).isSuccess() ) {
	// ok, the nominal version exists
	info.muonsName = objName;
      } else {
	// nothing found - could also look for the basename here.. error for now
	Error("execute","Failed to retrieve %s container.", objName.c_str());
	return EL::StatusCode::FAILURE;
      }
    }
    
  } else {
    if(!m_event->retrieve(muons,info.muonsName).isSuccess() ) {
      Error("execute","Failed to retrieve %s container.", info.muonsName.c_str());
      return EL::StatusCode::FAILURE;
    }
  }
  Tuple * tuple = info.tuple;
  // initialize the tuple
  tuple->nmuo=0;
  
  // loop over muons
  int imuo = 0;
  for( xAOD::MuonContainer::const_iterator iter = muons->begin();
       iter!= muons->end(); ++iter) {
    if( imuo < Tuple::MAXMUONS) {
      tuple->muo_pt[imuo] = (*iter)->pt();
      tuple->muo_phi[imuo] = (*iter)->phi();
      tuple->muo_eta[imuo] = (*iter)->eta();
      tuple->muo_E[imuo] = (*iter)->e();
      tuple->muo_ind[imuo] = m_superDecorator.get(*iter, MuonIntProps::partIndex);
      // this crashes with out_of_range at() ???
      //tuple->muo_passSel[imuo] = m_superDecorator.get(*iter, MuonIntProps::passSel);
      if(info.doDeco) {
	//tuple->muo_passOR[imuo] = m_superDecorator.get(*iter, MuonIntProps::passOR);
      tuple->muo_isVHL[imuo] = m_superDecorator.get(*iter, MuonIntProps::isVHLooseMuon);
      tuple->muo_isZH[imuo] = m_superDecorator.get(*iter, MuonIntProps::isZHSignalMuon);
      tuple->muo_isWH[imuo] = m_superDecorator.get(*iter, MuonIntProps::isWHSignalMuon);
      }
      // isolation
      (*iter)->isolation(tuple->muo_ptcone20[imuo], xAOD::Iso::ptcone20);
      (*iter)->isolation(tuple->muo_etcone30[imuo], xAOD::Iso::etcone30);
      ++imuo;
    }
    tuple->nmuo = imuo;
  }
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TupleMaker :: processElectrons(TupleInfo & info)
{
  const xAOD::ElectronContainer * eles = 0;
  if( info.electronsName=="") { // name hasn't been set yet
    std::string objName = m_electronsNameIn; // get the basename of the container
    if( info.variation!="") { // add the variation name
	objName+="___"+info.variation;
    }
    // now try to retrieve this
    if( m_event->retrieve(eles, objName ).isSuccess() ) {
      // it worked
      info.electronsName = objName; // remember the name for future reference
    } else {
      // ok, maybe this variation doesn't exist - lets look for the nominal input
      if( info.variation=="Original") {
	Error("execute","Original containers requested but not found");
	return EL::StatusCode::FAILURE;
      }
      objName = m_electronsNameIn+"___"+m_nominalName;
      if( m_event->retrieve(eles,objName).isSuccess() ) {
	// ok, the nominal version exists
	info.electronsName = objName;
      } else {
	// nothing found - could also look for the basename here.. error for now
	Error("execute","Failed to retrieve %s container.", objName.c_str());
	return EL::StatusCode::FAILURE;
      }
    }
  } else {
    if(!m_event->retrieve(eles,info.electronsName).isSuccess() ) {
      Error("execute","Failed to retrieve %s container.", info.electronsName.c_str());
      return EL::StatusCode::FAILURE;
    }
  }
  Tuple * tuple = info.tuple;
  // initialize the tuple
  tuple->nele=0;
  
  // loop over electrons
  int iele = 0;
  for( xAOD::ElectronContainer::const_iterator iter = eles->begin();
       iter!= eles->end(); ++iter) {
    if( iele < Tuple::MAXELECTRONS) {
      tuple->ele_pt[iele] = (*iter)->pt();
      tuple->ele_phi[iele] = (*iter)->phi();
      tuple->ele_eta[iele] = (*iter)->eta();
      tuple->ele_E[iele] = (*iter)->e();
      tuple->ele_ind[iele] = m_indexDecorator.get(*iter, IndexIntProps::partIndex);
      if(info.doDeco) {
      tuple->ele_isVTLH[iele] = m_superDecorator.get(*iter,ElecIntProps::isVeryTightLH);
      tuple->ele_isVHL[iele] = m_superDecorator.get(*iter,ElecIntProps::isVHLooseElectron);
      tuple->ele_isZH[iele] = m_superDecorator.get(*iter,ElecIntProps::isZHSignalElectron);
      tuple->ele_isWH[iele] = m_superDecorator.get(*iter,ElecIntProps::isWHSignalElectron);
      }
      tuple->ele_ptcone20[iele] = (*iter)->isolationValue(xAOD::Iso::ptcone20);
      tuple->ele_topoetcone30[iele]=(*iter)->isolationValue(xAOD::Iso::topoetcone30);
      ++iele;
    }
    tuple->nele = iele;
  }
  return EL::StatusCode::SUCCESS;
}

bool TupleMaker::isMC() {
  //std::cout << "Here" << std::endl;
  const xAOD::EventInfo * eventInfo = 0;
  if(m_event->retrieve( eventInfo, "EventInfo___"+m_nominalName).isSuccess() ) {
    //std::cout << "And here" << std::endl;
    return m_superDecorator.get(eventInfo,EventInfoIntProps::isMC);
  } else {
    Error("execute()","Failed to retrieve event info collection.");
    return false;
  }
}
EL::StatusCode TupleMaker::processEventInfo(TupleInfo & info) 
{
  const xAOD::EventInfo * eventInfo = 0;

  if(m_event->retrieve( eventInfo, "EventInfo___"+m_nominalName).isSuccess() ) {
    m_eventName="EventInfo___"+m_nominalName;
  } else {
    Error("execute()","Failed to retrieve event info collection. Exiting." );
    return EL::StatusCode::FAILURE;
  }
  // only do this once if variation mode is BLOCK
  Tuple * tuple = info.tuple;
  tuple->eve_isMC = false;
  if(info.doDeco) {
    tuple->eve_isMC = m_superDecorator.get(eventInfo,EventInfoIntProps::isMC);
    tuple->eve_nv3 = m_superDecorator.get(eventInfo,EventInfoIntProps::NVtx3Trks);
    tuple->eve_pvz = m_superDecorator.get(eventInfo,EventInfoFloatProps::ZPV);
    if( !tuple->eve_isMC) {
      tuple->eve_passGRL = m_superDecorator.get(eventInfo,EventInfoIntProps::passGRL);
      tuple->eve_isCleanEvent = m_superDecorator.get(eventInfo,EventInfoIntProps::isCleanEvent);
      tuple->eve_mc_w = 1.;
    } else {
      tuple->eve_mc_w = m_superDecorator.get(eventInfo,EventInfoFloatProps::MCEventWeight);
      tuple->eve_passGRL = true;
      tuple->eve_isCleanEvent = true;
    }
  }
  tuple->eve_num = eventInfo->eventNumber();
  tuple->eve_run = eventInfo->runNumber();
  tuple->eve_mu = eventInfo->averageInteractionsPerCrossing();
  if( tuple->eve_isMC) {
    tuple->eve_mc_num = eventInfo->mcEventNumber();
    tuple->eve_mc_chan = eventInfo->mcChannelNumber();
  } else {
    tuple->eve_mc_num = 0;
    tuple->eve_mc_chan =0;
  }
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TupleMaker::processMET(TupleInfo & info) 
{
  const xAOD::MissingETContainer * met = 0;
  if( info.metName=="") { // name hasn't been set yet
    std::string objName = m_metNameIn; // get the basename of the container
    if( info.variation!="") { // add the variation name
      objName+="___"+info.variation;
    }
    // now try to retrieve this
    if( m_event->retrieve(met, objName ).isSuccess() ) {
      // it worked
      info.metName = objName; // remember the name for future reference
    } else {
      // ok, maybe this variation doesn't exist - lets look for the nominal input
      // unless we wanted original - in this case skip
      if( info.variation=="Original") {
	Error("execute","Original containers requested but not found");
	return EL::StatusCode::FAILURE;
      }
      objName = m_metNameIn+"___"+m_nominalName;
      if( m_event->retrieve(met,objName).isSuccess() ) {
	// ok, the nominal version exists
	info.metName = objName;
      } else {
	// nothing found - could also look for the basename here.. error for now
	Error("execute","Failed to retrieve %s container.", objName.c_str());
	return EL::StatusCode::FAILURE;
      }
    }
  } else {
    if(!m_event->retrieve(met,info.metName).isSuccess() ) {
      Error("execute","Failed to retrieve %s container.", info.metName.c_str());
      return EL::StatusCode::FAILURE;
    }
  }
  Tuple * tuple = info.tuple;
  
  xAOD::MissingETContainer::const_iterator metIter = met->find("Final");
  if( metIter == met->end() ) {
    Error("execute","No ReFinal inside MET container");
    return EL::StatusCode::FAILURE;
  }
  tuple->met_px = (*metIter)->mpx();
  tuple->met_py = (*metIter)->mpy();
  tuple->met_pt = (*metIter)->met();
  tuple->met_phi = (*metIter)->phi();
  tuple->met_sumET = (*metIter)->sumet();

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TupleMaker :: processFatJets(TupleInfo & info)
{
  // simple copy&paste of processJets for now;
  //
  //Info("processFatJets","1: %s",info.fatJetsName.c_str());
  const xAOD::JetContainer * fatjets = 0;
  if( info.fatJetsName=="") { // name hasn't been set yet
    std::string objName = m_fatJetsNameIn; // get the basename of the container
    if( info.variation!="") { // add the variation name
      objName+="___"+info.variation;
    }
    // now try to retrieve this
    if( m_event->retrieve(fatjets, objName ).isSuccess() ) {
      // it worked
      info.fatJetsName = objName; // remember the name for future reference
    } else {
      // ok, maybe this variation doesn't exist - lets look for the nominal input
      // unless we wanted original - in this case skip
      if( info.variation=="Original") {
        Error("execute","Original containers requested but not found");
        return EL::StatusCode::FAILURE;
      }
      objName = m_fatJetsNameIn+"___"+m_nominalName;
      if( m_event->retrieve(fatjets,objName).isSuccess() ) {
        // ok, the nominal version exists
        info.fatJetsName = objName;
      } else {
        // nothing found - could also look for the basename here.. error for now
        Error("execute","Failed to retrieve %s container.", objName.c_str());
        return EL::StatusCode::FAILURE;
      }
    }
  } else {
    if(!m_event->retrieve(fatjets,info.fatJetsName).isSuccess() ) {
      Error("execute","Failed to retrieve %s container.", info.fatJetsName.c_str());
      return EL::StatusCode::FAILURE;
    }
  }
  //Info("processFatJets","2: %s",info.fatJetsName.c_str());
  Tuple * tuple = info.tuple;
  // initialize the tuple
  tuple->nfat=0;

  // loop over jets
  int ifat = 0;
  for( xAOD::JetContainer::const_iterator iter = fatjets->begin();
       iter!= fatjets->end(); ++iter) {
    if( ifat < Tuple::MAXFATJETS) {
      tuple->fat_pt[ifat] = (*iter)->pt();
      tuple->fat_phi[ifat] = (*iter)->phi();
      tuple->fat_eta[ifat] = (*iter)->eta();
      tuple->fat_E[ifat] = (*iter)->e();
      tuple->fat_ind[ifat] = m_indexDecorator.get(*iter, IndexIntProps::partIndex);
      
      if(info.doDeco) {
        tuple->fat_jvf[ifat] = m_superDecorator.get(*iter, FatJetFloatProps::JVF);
        tuple->fat_tau21[ifat] = m_superDecorator.get(*iter, FatJetFloatProps::Tau21);
        tuple->fat_tau32[ifat] = m_superDecorator.get(*iter, FatJetFloatProps::Tau32);
      }

      ++ifat;
    }
    tuple->nfat = ifat;
  }
  return EL::StatusCode::SUCCESS;
}
