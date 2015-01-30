#ifndef CxAODTools_DerivEffProvider_H
#define CxAODTools_DerivEffProvider_H

#include <map>

#include "TFile.h"
#include "TString.h"
#include "TH1.h"

class DerivEffProvider {
public:
  
  enum {
    // efficiency = nSelected/sumOfWeights
    efficiency = 0,
    sumOfWeights,
    nTotal,
    nSelected
  };
  
  enum {
    HIGG5D1 = 0, // 0-lep
    HIGG5D2,     // 1-lep
    HIGG2D4      // 2-lep
  };

  enum {
    JetTauEtmiss = 0,
    Muons,
    Egamma
  };
  
  DerivEffProvider();
  ~DerivEffProvider();

  bool getMCResult(int type, int derivation, int mcChannelNumber, double &result);
  bool getDataResult(int type, int derivation, int stream, double &result);
  
  // get via sampleName.Contains(RegExp(match))
  // multiple matches are summed up
  bool getResult(int type, const TString &match, double &result);

private:

  TFile* m_effFile;
  std::map<TString, TH1*> m_effHistos;

  TH1* getHistogram(const TString &match);

};

#endif
