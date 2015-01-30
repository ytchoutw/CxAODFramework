// Analysis includes 
#include "CxAODTools/ConfigStore.h"
#include "CxAODTools/ConfigField.h"

// STL includes
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

// ROOT includes
#include "TError.h"

#include "iostream"
#include <TSystem.h>

// namespaces
using std::vector;
using std::string;
using std::ifstream;


ConfigStore::ConfigStore() 
{

}


ConfigStore::ConfigStore(const ConfigStore& other)
{

  std::map<std::string,ConfigFieldBase*>::const_iterator it    = other.m_data.begin();
  std::map<std::string,ConfigFieldBase*>::const_iterator itEnd = other.m_data.end();

  for ( ; it != itEnd; ++it) {
 
    std::string key  = it->first;
    ConfigFieldBase* value = it->second->clone();
    
    m_data[key] = value;

  }

}


ConfigStore& ConfigStore::operator=(const ConfigStore& other)
{

  std::map<std::string,ConfigFieldBase*>::const_iterator it    = other.m_data.begin();
  std::map<std::string,ConfigFieldBase*>::const_iterator itEnd = other.m_data.end();

  for ( ; it != itEnd; ++it) {
 
    std::string key  = it->first;    
    ConfigFieldBase* value = it->second->clone();
    
    m_data[key] = value;

  }
  
  return *this;

}


ConfigStore::~ConfigStore()
{

  flush();

}


ConfigStore* ConfigStore::createStore(const char* filename)
{
  
  // Create store from steering file. 
  // The steering file is a flat text file with each line following this format:
  //
  // <type> <key> = <value>
  // 
  // <type>  : bool, int, float, double, string
  //           vector<T>, where T = bool, int, float, double, string
  // <key>   : name of parameter
  // <value> : value of parameter
  // 
  // E.g. :
  // bool           applyCorr   = true
  // double         Muons_ptmin = 25000.
  // vector<string> jetTools    = JetCleaning AnotherJetTool 
  //
  // Empty lines and lines beginning with '#' are ignored.

  //ifstream steerFile( filename ); // path conflicts on grid
  std::string configFile = Form("%s/%s",gSystem->Getenv("ROOTCOREBIN"),filename);
  std::cout << "Check file path used :" << configFile << std::endl;

  ifstream steerFile( configFile );
  if ( ! steerFile.is_open() ) {
    Error("createStore()","Couldn't open steerfile");
    return 0;
  }

  ConfigStore* store = new ConfigStore;
  
  string line;
  int lineNumber = 0;
  
  while ( ! steerFile.eof() ) {

    std::getline( steerFile , line );
    ++lineNumber;

    Info("ConfigStore::createStore()","%s",line.c_str());
    
    string buffer;
    std::stringstream ss( line );
    vector<string> tokens;
    while ( ss >> buffer ) tokens.push_back( buffer ); 
    
    unsigned int nTokens = tokens.size();
    
    if ( nTokens      == 0   ) continue; // ignore empty lines
    if ( tokens[0][0] == '#' ) continue; // ignore comments
    
    if ( nTokens < 4 ) {
      Error("createStore()","line %d in steer file : expected at least 4 tokens, but got %u",lineNumber,nTokens); 
      delete store;
      store = 0;
      break;
    }

    if ( tokens[2][0] != '=' ) {
      Error("createStore()","line %d in steer file : expected 3rd word to be =, but got %c",lineNumber,tokens[2][0]);      
      delete store;
      store = 0;
      break;
    }
    
    bool wrongType = false;
    bool wrongNumTokens = false;

    try {
      
      if ( tokens[0].compare("bool") == 0 ) {
	if ( nTokens == 4 ) store->put<bool>( tokens[1] , convertField<bool>( tokens[3] ) , true ); 
	else wrongNumTokens = true;
      }
      else if ( tokens[0].compare("int") == 0 ) {
	if ( nTokens == 4 ) store->put<int>( tokens[1] , convertField<int>( tokens[3] ) , true ); 
	else wrongNumTokens = true;
      }
      else if ( tokens[0].compare("float") == 0 ) {
	if ( nTokens == 4 ) store->put<float>( tokens[1] , convertField<float>( tokens[3] ) , true ); 
	else wrongNumTokens = true;
      }
      else if ( tokens[0].compare("double") == 0 ) {
	if ( nTokens == 4 ) store->put<double>( tokens[1] , convertField<double>( tokens[3] ) , true ); 
	else wrongNumTokens = true;
      }
      else if ( tokens[0].compare("string") == 0 ) {
	if ( nTokens == 4 ) store->put<string>( tokens[1] , tokens[3] , true );
	else wrongNumTokens = true;
      }
      else {      
	vector<string> vec(tokens.begin()+3,tokens.end());
	if      ( tokens[0].compare("vector<bool>")   == 0 ) store->put<vector<bool> >   ( tokens[1] , convertVector<vector<bool>,   bool>   ( vec ) , true );
	else if ( tokens[0].compare("vector<int>")    == 0 ) store->put<vector<int> >    ( tokens[1] , convertVector<vector<int>,    int>    ( vec ) , true );
	else if ( tokens[0].compare("vector<float>")  == 0 ) store->put<vector<float> >  ( tokens[1] , convertVector<vector<float>,  float>  ( vec ) , true );
	else if ( tokens[0].compare("vector<double>") == 0 ) store->put<vector<double> > ( tokens[1] , convertVector<vector<double>, double> ( vec ) , true );
	else if ( tokens[0].compare("vector<string>") == 0 ) store->put<vector<string> > ( tokens[1] , vec                                           , true );
	else wrongType = true;
      }
      
    }
    catch (...) {

      delete store;
      store = 0;
      break;

    }

    if ( wrongType ) {
      Error("createStore()","line %d in steer file : unknown type %s",lineNumber,tokens[0].c_str());      
      delete store;
      store = 0;
      break;
    }
    
    if ( wrongNumTokens ) {
      Error("createStore()","line %d in steer file : expected 1 token but got %u",lineNumber,nTokens-3);
      delete store;
      store = 0;
      break;
    }

  }
    
  return store;
  
}


void ConfigStore::remove(const std::string& key) 
{

  std::map<std::string,ConfigFieldBase*>::iterator it = m_data.find(key);
  
  if ( it == m_data.end() ) {
    Warning("remove()","field with name %s doesn't exist!",key.c_str());
  } 
  else {
    delete it->second; 
    it->second = 0;
    m_data.erase(key);
  }
  
}



void ConfigStore::flush() 
{

  std::map<std::string,ConfigFieldBase*>::iterator it    = m_data.begin();
  std::map<std::string,ConfigFieldBase*>::iterator itEnd = m_data.end();

  for ( ; it != itEnd; ++it) {
    delete it->second;
    it->second = 0;
  }

  m_data.clear();

}


