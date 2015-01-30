#ifndef CxAODTools_XSectionProvider_H
#define CxAODTools_XSectionProvider_H

#include <string>
#include <map>

class XSectionProvider {
  
private:
  
  struct XSection {
    std::string name;
    float xSection;
    float kFactor;
    float filterEff;
  };
  
  std::map<int, XSection> m_xSections;
  
public:
  
  XSectionProvider(std::string fileName);
  ~XSectionProvider() = default;
  
  float getXSection(int mc_channel_number);
  
};


#endif
