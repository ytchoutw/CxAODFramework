
#include "CxAODTools/DerivEffProvider.h"

#include "iostream"

#include "TKey.h"
#include "TSystem.h"
#include "TRegexp.h"

DerivEffProvider::DerivEffProvider() {

  TString fileName = "data/CxAODTools/DxAODefficiency_141109.root";
  fileName = Form("%s/%s", gSystem->Getenv("ROOTCOREBIN"), fileName.Data());
  m_effFile = TFile::Open(fileName, "read");

}

DerivEffProvider::~DerivEffProvider() {

  m_effFile->Close();
  delete m_effFile;

}
bool DerivEffProvider::getMCResult(int type, int derivation, int mcChannelNumber, double &result) {
  TString match("mc.*");
  match += TString::Format("%i", mcChannelNumber);
  match += ".*DAOD_";
  switch (derivation) {
    case HIGG5D1: match += "HIGG5D1"; break;
    case HIGG5D2: match += "HIGG5D2"; break;
    case HIGG2D4: match += "HIGG2D4"; break;
  }
  match += ".*";
  return getResult(type, match, result);
}

bool DerivEffProvider::getDataResult(int type, int derivation, int stream, double &result) {
  TString match("data.*physics_");
  switch (stream) {
    case JetTauEtmiss: match += "JetTauEtmiss"; break;
    case Muons: match += "Muons"; break;
    case Egamma: match += "Egamma"; break;
  }
  match += ".*DAOD_";
  switch (derivation) {
    case HIGG5D1: match += "HIGG5D1"; break;
    case HIGG5D2: match += "HIGG5D2"; break;
    case HIGG2D4: match += "HIGG2D4"; break;
  }
  match += ".*";
  return getResult(type, match, result);
}

bool DerivEffProvider::getResult(int type, const TString &match, double &result) {

  TH1* histo = getHistogram(match);
  if (!histo) {
    return false;
  }

  result = histo -> GetBinContent(type);
  if (type == efficiency) {
    result = histo -> GetBinContent(nSelected);
    result /= histo -> GetBinContent(sumOfWeights);
  }
  return true;
}

TH1* DerivEffProvider::getHistogram(const TString &match) {

  if (m_effHistos.count(match)) {
    return m_effHistos[match];
  }

  TKey* key;
  int matches = 0;
  TH1* histo = 0;
  
  TIter nextkey(m_effFile->GetListOfKeys());
  while ((key = (TKey*) nextkey())) {

    TString name = key->GetName();
    if (!name.Contains(TRegexp(match)))
      continue;

    if (matches == 0) {
      // rely on TFile.Close() to delete histogram later
      histo = (TH1*) key -> ReadObj() -> Clone();
      m_effHistos[match] = histo;
    } else {
      histo -> Add((TH1*) key -> ReadObj());
    }
    matches++;
  }

  return histo;
}
