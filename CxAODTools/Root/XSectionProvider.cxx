
#include "CxAODTools/XSectionProvider.h"

#include <fstream>
#include <iostream>
#include <sstream>


XSectionProvider::XSectionProvider(std::string fileName) {
  
  std::ifstream file;
  file.open(fileName.c_str());
  if (!file.good()) {
    std::cout << "XSectionProvider::XSectionProvider() Error: Can't open file " << fileName << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "XSectionProvider::XSectionProvider() Info: Reading file " << fileName << std::endl;

  // process file
  while (!file.eof()) {
    // read line
    std::string lineString;
    getline(file, lineString);
    //std::cout << lineString << std::endl;
    
    // skip lines starting with #
    if (lineString.find("#") == 0) {
      continue;
    }

    // store in map
    std::stringstream line(lineString);
    int sid;
    std::string name;
    float xSection;
    float kFactor;
    float filterEff;
    line >> sid >> xSection >> kFactor >> filterEff >> name;
    m_xSections[sid] = {name, xSection, kFactor, filterEff};
  }
}

float XSectionProvider::getXSection(int mc_channel_number) {
  
  if (m_xSections.count(mc_channel_number) == 0) {
    std::cout << "XSectionProvider::XSectionProvider() Error: Unknown mc_channel_number " << mc_channel_number << std::endl;
    exit(EXIT_FAILURE);
  }
  
  XSection& xSec = m_xSections[mc_channel_number];
  return xSec.xSection * xSec.kFactor * xSec.filterEff;
}
