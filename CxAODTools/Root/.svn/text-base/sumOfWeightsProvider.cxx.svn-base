
#include "CxAODTools/sumOfWeightsProvider.h"

#include <fstream>
#include <iostream>
#include <sstream>


sumOfWeightsProvider::sumOfWeightsProvider(std::string fileName) {
  
  std::ifstream file;
  file.open(fileName.c_str());
  if (!file.good()) {
    std::cout << "sumOfWeightsProvider::sumOfWeightsProvider() Error: Can't open file " << fileName << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "sumOfWeightsProvider::sumOfWeightsProvider() Info: Reading file " << fileName << std::endl;

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
    float nentries;
    float SumOfWeights;
    line >> sid >> nentries >> SumOfWeights >> name;
    m_sumOfWeights[sid] = {name, nentries, SumOfWeights};
  }
}

float sumOfWeightsProvider::getsumOfWeights(int mc_channel_number) {
  
  if (m_sumOfWeights.count(mc_channel_number) == 0) {
    std::cout << "sumOfWeightsProvider::sumOfWeightsProvider() Error: Unknown mc_channel_number " << mc_channel_number << std::endl;
    exit(EXIT_FAILURE);
  }
  
  sumOfWeights& sum = m_sumOfWeights[mc_channel_number];
  return sum.SumOfWeights;
}
