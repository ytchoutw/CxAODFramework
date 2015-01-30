// CxAODTools includes
#include "CxAODTools/BTaggingTool.h"
#include "CxAODTools/JetDecorator.h"

// Infra structure (can be omitted - also included through BTaggingEfficiencyTool.h)
#include "AsgTools/StatusCode.h"
#include "PATInterfaces/CorrectionCode.h"
#include "PATInterfaces/SystematicCode.h"
#include "PATInterfaces/SystematicVariation.h"
#include "PATInterfaces/SystematicSet.h"

// ROOT includes
#include "TError.h"

// STD includes
#include <map>
#include <utility>
#include <vector>
#include <string>



BTaggingTool::BTaggingTool() :
  m_tool(0)
{;}


BTaggingTool::~BTaggingTool() 
{
  
  delete m_tool;

}


bool BTaggingTool::initialize(const char * TaggerName, const char * OperatingPoint, const char * JetAuthor, const char * ScaleFactorFileName)
{

  // ARGUMENTS
  // =========
  // TaggerName          : MV1
  // OperatingPoint      : 0_8119
  // JetAuthor           : AntiKt4TopoEMJVF , AntiKt4TopoEMJVF0_5 
  // ScaleFactorFileName : testCDI.root , 2014-Winter-8TeV-MC12-CDI.root

  // create TStore -- needed ??
  xAOD::TStore store;

  // Initialize external tool
  m_tool = new BTaggingEfficiencyTool( "BTaggingEfficiencyTool" );
  m_tool->setProperty("TaggerName"         , TaggerName         );
  m_tool->setProperty("OperatingPoint"     , OperatingPoint     );
  m_tool->setProperty("JetAuthor"          , JetAuthor          );
  m_tool->setProperty("ScaleFactorFileName", ScaleFactorFileName );

  // initialize external tool
  StatusCode status = m_tool->initialize();

  // check initialization
  if ( status != StatusCode::SUCCESS ) {
    Error("BTaggingTool::initialize()","Initialization failed!");
    delete m_tool;
    m_tool = 0;
    return false;
  }

  // print list of allowed systematics
  const std::map<CP::SystematicVariation, std::vector<std::string> > allowed_variations = m_tool->listSystematics();
  Info("BTaggingTool::initialize()","Allowed systematics variations for tool %s : ", (m_tool->name()).c_str());
  for (const std::pair<CP::SystematicVariation, std::vector<std::string> > & var : allowed_variations) {
    std::string list;
    for (const std::string & entry : var.second) { 
      list += entry + " ";
    } 
    Info("BTaggingTool::initialize()","===> %-40s for flavours : %s", var.first.name().c_str(), list.c_str());  
  }

  // All okay
  return true;

}



float BTaggingTool::getEfficiency(const xAOD::Jet & jet) const
{

  // check if tool is initialized
  if ( ! m_tool ) {
    Error("BTaggingTool::getEfficiency()","tool is not initalized!");
    return -1.;
  }

  // check eta of jet 
  // the tool will initiate a core dump (!) if we feed a jet with
  // |eta| > 2.5 to it... it's a design choice, like it not...
  if ( fabs(jet.eta() ) > 2.5 ) return -1.;

  // get efficiency
  float eff;
  CP::CorrectionCode status = m_tool->getEfficiency( jet , eff );

  // check return code
  if ( status == CP::CorrectionCode::OutOfValidityRange ) {
    // out of extrapolation range of tool (high jet pt) - result should not be used
    return -1.;
  }
  else if ( status == CP::CorrectionCode::Error ) {
    // something went wrong - print error message
    Error("BTaggingTool::getEfficiency()","tool returned CP::CorrectionCode::Error");
    return -1.;
  }
  
  // All is okay
  return eff;
  
}


float BTaggingTool::getScaleFactor(const xAOD::Jet & jet) const
{
  
  // check if tool is initialized
  if ( ! m_tool ) {
    Error("BTaggingTool::getScaleFactor()","tool is not initalized!");
    return -1.;
  }
  
  // check eta of jet 
  // the tool will initiate a core dump (!) if we feed a jet with
  // |eta| > 2.5 to it... it's a design choice, like it not...
  if ( fabs(jet.eta() ) > 2.5 ) return -1.;

  // get scale factor
  float sf;
  CP::CorrectionCode status = m_tool->getScaleFactor( jet , sf );

  // check return code
  if ( status == CP::CorrectionCode::OutOfValidityRange ) {
    // out of extrapolation range of tool (high jet pt) - result should not be used
    return -1.;
  }
  else if ( status == CP::CorrectionCode::Error ) {
    // something went wrong - print error message
    Error("BTaggingTool::getScaleFactor()","tool returned CP::CorrectionCode::Error");
    return -1.;
  }
  
  // All is okay
  return sf;  

}


void BTaggingTool::getScaleFactor(const xAOD::JetContainer & jets, JetDecorator & decorator) const 
{

  // loop over jets and attach scale factor as decoration
  for (const xAOD::Jet * jet : jets) {
    
    // attach scale factor
    decorator.set( jet , JetFloatProps::btagSF, getScaleFactor( *jet ) );

  }

}


CP::SystematicSet BTaggingTool::affectingSystematics() const 
{
  
  // check if tool is initialized
  if ( ! m_tool ) {
    Error("BTaggingTool::affectingSystematics()","tool is not initalized - returning dummy!");
    CP::SystematicSet dummy;
    return dummy;
  }
  
  // return list of systematics
  return m_tool->affectingSystematics();

}


bool BTaggingTool::applySystematicVariation(const CP::SystematicSet & sysSet) 
{

  // check if tool is initialized
  if ( ! m_tool ) {
    Error("BTaggingTool::applySystematic()","tool is not initalized!");
    return false;
  }

  // apply systematic variation
  CP::SystematicCode status = m_tool->applySystematicVariation( sysSet );
  if( status != CP::SystematicCode::Ok ) {
    Error("BTaggingTool::applySystematic()","Could not apply systematic variation!");
    return false;
  }
  
  // all okay
  return true;

}


bool BTaggingTool::applyNominal() 
{

  // check if tool is initialized
  if ( ! m_tool ) {
    Error("BTaggingTool::applyNominal()","tool is not initalized!");
    return false;
  }
  
  // switch off systematics
  CP::SystematicSet defaultSet;
  CP::SystematicCode status = m_tool->applySystematicVariation( defaultSet );
  if ( status != CP::SystematicCode::Ok ) {
    Error("BTaggingTool::applyNominal()","Could not apply nominal!");
    return false;
  }
  
  // all okay
  return true;

}

