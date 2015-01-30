#ifndef _METADATA_H_
#define _METADATA_H_

#include <string>
#include <map>
#include <vector>
#include "TObject.h"
#include <iostream>

/*
  Objects of this class contain information about the job that produced the file that the object is contained in. There should only be one object saved per output file. Examples of the kind of information it should store are:
   executable name
   list of input files - including full path and a TMD5 object storing the files hash
   list of command line arguments
   list of configuration objects

*/

class MetaData : public TObject  {
public:

  MetaData();
  ~MetaData();

  MetaData(const std::string & job);

  void JobName( const std::string & job) { jobName = job;}
  const std::string & JobName() const { return jobName;}
  
  void ExecutableName(const std::string & exe) { executableName = exe;}
  const std::string & ExecutableName()const  { return executableName;}

  void AddArgument(const std::string & argument) { 
    commandLineOptions.push_back(argument);
  }
  
  bool AddFile(const std::string & md5hash, const std::string & file) {
    if( fileData.find(md5hash) != fileData.end() )
      return false;
    else
      fileData[md5hash] = file;
  }
  
  std::string FindFile(const std::string & hash) const {
    std::map<std::string,std::string>::const_iterator mapIter = fileData.find(hash);
    std::string result="";
    if( mapIter != fileData.end() )
      result = mapIter->second;
    return result;
  }
  
  const std::string & Configuration() const { return configurationString;}
  void Configuration(const std::string & config) { configurationString = config;}

  void Print(std::ostream & os) const;
  std::ostream & Stream(std::ostream & os) const 
  {
    Print(os);
    return os;
  }
  
private:
  std::string jobName;
  std::string executableName;
  std::vector<std::string> commandLineOptions;
  std::map<std::string,std::string> fileData;
  std::string configurationString;

  ClassDef(MetaData,1);
};

#endif
