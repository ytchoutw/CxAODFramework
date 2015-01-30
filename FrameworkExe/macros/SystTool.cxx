// Author: Georges Aad

#include "SystTool.h"


SystTool::SystTool(){

  m_seed=9238476;
  m_rand=new TRandom3(m_seed);
  m_nExp=10000;

}
  
SystTool::~SystTool(){
  if(m_rand)delete m_rand;
}

std::vector<std::pair<double, double> >
SystTool::getExpData(TH1* h_default, 
		     const std::vector<SystTool::SystHolder>& systs) const{

  unsigned int nbins = h_default->GetNbinsX();

  std::vector<double> bindata(nbins, 0);

  for(unsigned int ibin=0; ibin<nbins; ++ibin){
    bindata[ibin]=h_default->GetBinContent(ibin+1);
  }

  for(unsigned int isyst=0; isyst<systs.size(); ++isyst){

    double mean = systs[isyst].m_shift;
    double sigma = systs[isyst].m_constraint;


    double rand = m_rand->Gaus(mean, sigma);

    TH1* h_syst = systs[isyst].m_systUp;

    if(rand < mean) h_syst = systs[isyst].m_systDo;

    for(unsigned int ibin=0; ibin<nbins; ++ibin){

      double systorig = h_syst->GetBinContent(ibin+1)-h_default->GetBinContent(ibin+1);
      
      double compsyst = TMath::Abs(rand)*systorig;

      bindata[ibin]+=compsyst;

    }
  }

  double default_int=0;
  double syst_int=0;

  for(unsigned int ibin=0; ibin<nbins; ++ibin){
    if(bindata[ibin]<0)bindata[ibin]=0;
  }

  for(unsigned int ibin=0; ibin<nbins; ++ibin){
    default_int+=h_default->GetBinContent(ibin+1);
    syst_int+=bindata[ibin];
  } 

  if(syst_int==0){
    //cout << " WARNING: toy converged to a negative integral - ignoring " << endl;
    return std::vector<std::pair<double, double> >();
  }

  std::vector<std::pair<double, double> > retVec(nbins);
  for(unsigned int ibin=0; ibin<nbins; ++ibin){
    retVec[ibin].first = bindata[ibin];
    retVec[ibin].second = bindata[ibin]*default_int/syst_int;
  }

  return retVec;
}


std::vector<SystTool::RawData> 
SystTool::computeMeanAndRMS(std::vector<double> bindataMean, 
			    std::vector<double> bindataRMS,
			    std::vector<double> bindataShapeMean, 
			    std::vector<double> bindataShapeRMS) const{

  std::vector<RawData> compbins(bindataMean.size());

  for(unsigned int ibins=0; ibins<bindataMean.size(); ++ibins){

    double mean = bindataMean[ibins]/m_nExp;
    double RMS = TMath::Sqrt( (bindataRMS[ibins]/m_nExp) - mean*mean );

    double shapeMean = bindataShapeMean[ibins]/m_nExp;
    double shapeRMS = TMath::Sqrt( (bindataShapeRMS[ibins]/m_nExp) - shapeMean*shapeMean );

    compbins[ibins].mean = mean;
    compbins[ibins].RMS = RMS;
    compbins[ibins].shapeMean = shapeMean;
    compbins[ibins].shapeRMS = shapeRMS;

  }

  return compbins;

}
 
std::vector<SystTool::RawData>
SystTool::getSymmetricShapeSystVector(TH1* h_default, 
				      const std::vector<SystTool::SystHolder>& systs, 
				      bool resetSeed) const{

  unsigned int nbins = h_default->GetNbinsX();

  std::vector<double>  bindataMean(nbins, 0.);
  std::vector<double>  bindataRMS(nbins, 0.);
  
  std::vector<double>  bindataShapeMean(nbins, 0.);
  std::vector<double>  bindataShapeRMS(nbins, 0.);
  
  if(resetSeed)m_rand->SetSeed(m_seed);

  for(unsigned int iexp=0; iexp<m_nExp; ++iexp){

    std::vector<std::pair<double, double> > expbins = getExpData(h_default, systs);

    if(expbins.size() == 0) continue;

    for(unsigned int ibin=0; ibin<bindataMean.size(); ++ibin){

      double expbin = expbins[ibin].first;
      double expbinShape = expbins[ibin].second;

      bindataMean[ibin]+=expbin;
      bindataRMS[ibin]+= (expbin*expbin);
      bindataShapeMean[ibin]+=expbinShape;
      bindataShapeRMS[ibin]+= (expbinShape*expbinShape);

    }

  }

  return computeMeanAndRMS(bindataMean, bindataRMS, bindataShapeMean, bindataShapeRMS);

}

TH1 ** SystTool::getSymmetricShapeUncertainties(TH1* h_default, 
						const std::vector<SystTool::SystHolder>& systs, 
						bool changeMean,
						bool resetSeed) const{

  std::vector<RawData> rawdata = getSymmetricShapeSystVector(h_default, systs, resetSeed);

  TH1* h_syst = (TH1*)h_default->Clone();
  h_syst->SetDirectory(0);
  TH1* h_shapeSyst = (TH1*)h_default->Clone();
  h_shapeSyst->SetDirectory(0);
  
  for(unsigned int ibin=0; ibin<rawdata.size(); ++ibin){
  
    double staterr = h_default->GetBinError(ibin+1);
    double toterr = TMath::Sqrt(rawdata[ibin].RMS*rawdata[ibin].RMS + staterr*staterr);
    double shapeerr = TMath::Sqrt(rawdata[ibin].shapeRMS*rawdata[ibin].shapeRMS + staterr*staterr);

    h_syst->SetBinError(ibin+1,toterr);
    h_shapeSyst->SetBinError(ibin+1,shapeerr);

    if(changeMean){
      h_syst->SetBinContent(ibin+1,rawdata[ibin].mean);
      h_shapeSyst->SetBinContent(ibin+1,rawdata[ibin].shapeMean);
    }

  }

  TH1 **h = new TH1*[2];
  h[0] = h_syst;
  h[1] = h_shapeSyst;

  return h;
}



SystTool::SystHolder::SystHolder(){

  m_systUp=0;
  m_systDo=0;
  m_nominal = 0;
  m_shift=0.;
  m_constraint=1.;

}

SystTool::SystHolder::~SystHolder(){
  /// does not own the pointers
}

bool SystTool::SystHolder::isValid() {

  return ( m_systUp != 0 &&
	   m_systDo != 0 &&
	   m_nominal != 0 );
}

int compareSystHolders(SystTool::SystHolder syst1, SystTool::SystHolder syst2) {

  double I0 = syst1.m_nominal->Integral(0, syst1.m_nominal->GetNbinsX()+1);
  double d1_Up = fabs(syst1.m_systUp->Integral(0, syst1.m_systUp->GetNbinsX()+1)-I0);
  double d1_Do = fabs(syst1.m_systDo->Integral(0, syst1.m_systDo->GetNbinsX()+1)-I0);
  double d2_Up = fabs(syst2.m_systUp->Integral(0, syst2.m_systUp->GetNbinsX()+1)-I0);
  double d2_Do = fabs(syst2.m_systDo->Integral(0, syst2.m_systDo->GetNbinsX()+1)-I0);

  double d1 = d1_Up > d1_Do ? d1_Up : d1_Do;
  double d2 = d2_Up > d2_Do ? d2_Up : d2_Do;

  return (d1 < d2 ? -1 : (d1 > d2 ? 1 : 0) );
}

std::vector<SystTool::SystHolder> sortSystHolders(std::vector<SystTool::SystHolder> systHolders) {

  if(systHolders.size() <= 1) {
    return systHolders;
  }

  SystTool::SystHolder pivot = systHolders[0];

  std::vector<SystTool::SystHolder> small;
  std::vector<SystTool::SystHolder> big;
  small.reserve(systHolders.size());
  big.reserve(systHolders.size());
  for(unsigned int i=1; i<systHolders.size(); i++) {
    if( compareSystHolders(systHolders[i], pivot) > 0 ) {
      small.push_back(systHolders[i]);
    }else{
      big.push_back(systHolders[i]);
    }
  }

  std::vector<SystTool::SystHolder> smallSorted = sortSystHolders(small);
  std::vector<SystTool::SystHolder> bigSorted = sortSystHolders(big);

  std::vector<SystTool::SystHolder> sorted;
  sorted.reserve(systHolders.size());
  for(unsigned int i=0; i<smallSorted.size(); i++) {
    sorted.push_back(smallSorted[i]);
  }
  sorted.push_back(pivot);
  for(unsigned int i=0; i<bigSorted.size(); i++) {
    sorted.push_back(bigSorted[i]);
  }

  return sorted;  
}
