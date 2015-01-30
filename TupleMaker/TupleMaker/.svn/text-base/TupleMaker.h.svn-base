#ifndef Skimming_TupleMaker_H
#define Skimming_TupleMaker_H

#include <vector>
#include <string>

#include "EventLoop/Algorithm.h"

#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"

#ifndef __MAKECINT__
#include "CxAODTools/SuperDecorator.h"
#include "CxAODTools/IndexDecorator.h"
#endif // not __MAKECINT__


class Tuple;
class TFile;
class TTree;

class TupleMaker : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:

  enum VariationMode_e { NONE, FILE, TREE, BLOCK};
  
  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:
  void configure(std::string configPath); // hook to configure the algorithm before the driver does anything with it

  TupleMaker ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // this is needed to distribute the algorithm to the workers
  ClassDef(TupleMaker, 1);

 private:
  struct TupleInfo {
  TupleInfo() : tuple(0),tree(0),jetsName(""),fatJetsName(""),muonsName(""),electronsName(""),metName(""),variation(""), skip(false), doDeco(true) {;}
    Tuple * tuple;
    TTree * tree;
    std::string jetsName;
    std::string fatJetsName;
    std::string muonsName;
    std::string electronsName;
    std::string metName;
    std::string variation;
    bool skip;
    bool doDeco;
  };
  // 
  bool isMC();
  EL::StatusCode processJets(TupleInfo & info);
  EL::StatusCode processFatJets(TupleInfo & info);
  EL::StatusCode processMuons(TupleInfo & info);
  EL::StatusCode processElectrons(TupleInfo & info);
  EL::StatusCode processEventInfo(TupleInfo & info);
  EL::StatusCode processMET(TupleInfo & info);
  //Config * m_config;

  // container names
  std::string m_jetsNameIn;
  std::string m_fatJetsNameIn;
  std::string m_muonsNameIn;
  std::string m_electronsNameIn;
  std::string m_metNameIn;
  std::string m_filename; // output filename
  std::string m_nominalName;
  
  std::string m_eventName;
  bool m_useEventInfo;
  //
  VariationMode_e m_variationMode;
  std::vector<std::string> m_variations;
  // note the comment+pling is very important after m_event
  xAOD::TEvent *m_event; //!
  int m_eventCounter; //!
  
  std::vector<TupleInfo> m_tuples; //!
  std::vector<TTree *> m_trees; //!
  bool m_isMC;
#ifndef __MAKECINT__
  SuperDecorator m_superDecorator; //!
  IndexDecorator m_indexDecorator; //!
#endif // not __MAKECINT__
};

#endif
