#ifndef CxAODTools_sumOfWeightsProvider_H
#define CxAODTools_sumOfWeightsProvider_H

#include <string>
#include <map>

class sumOfWeightsProvider {
  
private:
  
  struct sumOfWeights {
    std::string name;
    float nentries;
    float SumOfWeights;
  };
  
  std::map<int, sumOfWeights> m_sumOfWeights;
  
public:
  
  sumOfWeightsProvider(std::string fileName);
  ~sumOfWeightsProvider() = default;
  
  float getsumOfWeights(int mc_channel_number);
  
};


#endif
