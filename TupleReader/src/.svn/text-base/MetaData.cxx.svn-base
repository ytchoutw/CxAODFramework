#include "TupleAnalyze/MetaData.h"
#include <iostream>

ClassImp(MetaData)

MetaData::MetaData() {;}
MetaData::MetaData(const std::string & job) { jobName = job;}
MetaData::~MetaData() {;}
void MetaData::Print(std::ostream & os) const {
  os << "MetaData : " << jobName << std::endl;
  os << "Exe : " << executableName << std::endl;
  os << "Arguments : ";
  for( int i =0,n=commandLineOptions.size();i<n;++i) 
    os << commandLineOptions[i] << " ";
  os << std::endl;
  os << "Config : " << configurationString << std::endl;
  os << "Input Files : " << fileData.size() << std::endl;
  for(std::map<std::string,std::string>::const_iterator mapIter = fileData.begin();
      mapIter != fileData.end(); ++mapIter) 
    os << "      " << mapIter->second << " " << mapIter->first << std::endl;
}
