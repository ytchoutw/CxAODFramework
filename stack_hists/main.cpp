// C++ headers
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <numeric>

// C headers
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

// ROOT headers
#include "TROOT.h"
#include "TSystem.h"
#include "TChain.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TH1.h"
#include "THStack.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TImage.h"
#include "TLeaf.h"
#include "TLorentzVector.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TKey.h"

#include "AtlasLabels.h"
#include "AtlasStyle.h"

using namespace std;

int main (int argc, char * argv[])
{
        // command line input
	// arguments are hard to follow
	if ((argc - 3) % 3 != 0)
	{
		fprintf(stderr, "ERROR - wrong number of arguments\n");
		fprintf(stderr, "usage: %s title legend file_path_1 sample_name_1 stack_1 file_path_2 sample_name_2 stack_2...\n", argv[0]);
		return 1;
	}

	int file_num = (argc - 3) / 3;
	//             ttbarall nonall, singletop,   Wlv(ev/muv/taumu),                   Zll,      Zvv         gamma   dijet  monoW monoH
    int color[] = {kOrange, kOrange, kOrange - 1,kGreen - 9, kGreen - 4,kGreen - 2, kAzure + 2, kAzure - 4, kYellow, kCyan, kRed, kBlue};
    
	bool TFflag = false;
	if( file_num  == 2) TFflag = true;
	
	 
	// set style for plots
	SetAtlasStyle();

	// stacked histograms and legends
	vector<THStack*> stacked_hists;
	vector<THStack*> not_stacked_hists;
	vector<TH1F*> error;
	
	vector<TLegend*> legends;
	stacked_hists.reserve(100);		// histograms here will stack
	not_stacked_hists.reserve(100);		// histograms here will overlay the stacked histograms
	error.reserve(100);
	legends.reserve(100);
	
	// use the first input file to set our histograms and legends
	TFile * first_hist_file = new TFile(argv[3]);

	// iterate over keys
	TIter next(first_hist_file->GetListOfKeys());
	TKey * first_key;
    int pass(0); 
    vector<double> norm;

	for(unsigned int i(0);i < 100;i++){
		norm.push_back(0);
	}
	
	while (first_key = (TKey*) next())		
	{   if(pass < 3)
		{pass++; continue;}
		
		std::cout << first_key->GetName() << std::endl;
	    
		TH1F * hist = (TH1F*) first_hist_file->Get(first_key->GetName());
        
		char title[256];
		sprintf(title, "%s;%s;%s", first_key->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle());
		if(TFflag){
			TString hist_name(first_key->GetName());
			if(hist_name.Contains("Curve1: #slash{E}_{T}")){
				stacked_hists.push_back(new THStack(first_key->GetName(), title));
				not_stacked_hists.push_back(new THStack(first_key->GetName(), title));
				error.push_back(new TH1F(first_key->GetName(), title,hist->GetXaxis()->GetNbins(),hist->GetXaxis()->GetXmin(),hist->GetXaxis()->GetXmax()));
				
				legends.push_back(new TLegend(0.6, 0.4, 0.9, 0.9, first_key->GetTitle()));
				legends.back()->SetFillStyle(0);
				legends.back()->SetBorderSize(0);
			}
				
		}
		else{
		stacked_hists.push_back(new THStack(first_key->GetName(), title));
		not_stacked_hists.push_back(new THStack(first_key->GetName(), title));
		error.push_back(new TH1F(first_key->GetName(), title,hist->GetXaxis()->GetNbins(),hist->GetXaxis()->GetXmin(),hist->GetXaxis()->GetXmax()));
		
		legends.push_back(new TLegend(0.6, 0.4, 0.9, 0.9, first_key->GetTitle()));
		legends.back()->SetFillStyle(0);
		legends.back()->SetBorderSize(0);
		} 
		
	}
	
	
	if(TFflag){
		TFile * hist_file = new TFile(argv[3]);   //Zvv
		TFile * hist_file_2 = new TFile(argv[6]);   //Zll

		// histograms
		vector<TH1F*> hists;
		hists.reserve(100);

		vector<TH1F*> hists_2;
		hists_2.reserve(100);
		
		vector<TH1F*> hists_TF;
		hists_TF.reserve(100);
	
		
		TIter next(hist_file->GetListOfKeys());
		TKey * key;		
		

		int j = 0;
		int passn(0);
		while (key = (TKey*) next())
		{   
			TString histname(key->GetName());
			hists.push_back((TH1F*) hist_file->Get(key->GetName()));
			if(histname.Contains("Curve1: #slash{E}_{T}")){
			//if(1){
				TIter next_2(hist_file_2->GetListOfKeys());
				TKey * key_2;	
				while (key_2 = (TKey*) next_2()){
				TString histname_2(key_2->GetName());
				hists_2.push_back((TH1F*) hist_file_2->Get(key_2->GetName()));
				hists_TF.push_back((TH1F*) hist_file->Get(key->GetName()));
				if( histname.EqualTo(histname_2)) {
					std::cout<<  histname_2 <<endl;
					hists.back()->SetLineColor(color[5]);
					hists.back()->SetMarkerColor(color[5]);
					hists_2.back()->SetLineColor(color[6]);
					hists_2.back()->SetMarkerColor(color[6]);
					stacked_hists.at(j)->Add(hists.back());
					stacked_hists.at(j)->Add(hists_2.back());
					hists_TF.back()->Divide(hists_2.back());
					not_stacked_hists.at(j)->Add(hists_TF.back());
					legends.at(j)->AddEntry(hists.back(), argv[4], "l");
					legends.at(j)->AddEntry(hists_2.back(), argv[7], "l");
					j++;
				}
				}	
			}

		}
		
	
		
	}
    else{
	for (int i = 0; i < file_num; i++)
	{
		// hist file
		TFile * hist_file = new TFile(argv[3 * i + 3]);
        
		// histograms
		vector<TH1F*> hists;
		hists.reserve(100);

		// iterate over keys
		TIter next(hist_file->GetListOfKeys());
		TKey * key;

		int j = 0;
		int passn(0);
		while (key = (TKey*) next())
		{   
			if(passn <3)
			{passn++; continue;}
	
		    std::cout << key->GetName() << std::endl;
			// get a histogram
			hists.push_back((TH1F*) hist_file->Get(key->GetName()));
			hists.back()->SetLineColor(color[i]);
			hists.back()->SetMarkerColor(color[i]);
			// add histogram to one of the histogram stacks
			if (atoi(argv[3 * i + 5]))
			{	
				
				hists.back()->SetFillColor(color[i]);
				hists.back()->SetFillStyle(1001);
				// add it to the stacked histograms
				error.at(j)->Add(hists.back());
				hists.back()->Sumw2(false);
				stacked_hists.at(j)->Add(hists.back());
				
				norm.at(j) += hists.back()->Integral();
			}
			else
			{
			}

			// add it to the legend
			legends.at(j)->AddEntry(hists.back(), argv[3 * i + 4], "l");
            j++;
		}
	} 

	
	for (int i = 0; i < file_num; i++)
	{
		// hist file
		TFile * hist_file = new TFile(argv[3 * i + 3]);
        
		// histograms
		vector<TH1F*> hists;
		hists.reserve(100);

		// iterate over keys
		TIter next(hist_file->GetListOfKeys());
		TKey * key;

		int j = 0;
		int passn(0);
		while (key = (TKey*) next())
		{   
			if(passn <3)
			{passn++; continue;}
	
		    std::cout << key->GetName() << std::endl;
			// get a histogram
			hists.push_back((TH1F*) hist_file->Get(key->GetName()));
			hists.back()->SetLineColor(color[i]);
			//hists.back()->SetMarkerStyle(25);
			//hists.back()->Sumw2(false);
			// add histogram to one of the histogram stacks
			if (atoi(argv[3 * i + 5]))
			{	
				

			}
			else
			{
				// add it to the not stacked histograms
				hists.back()->SetLineColor(color[i]);
				hists.back()->SetMarkerColor(color[i]);
				hists.back()->Scale(norm.at(j)/hists.back()->Integral());
				not_stacked_hists.at(j)->Add(hists.back());
			}


            j++;
		}
	} 	
	} 
	// canvas for histogram eps files
	TCanvas * canvas = new TCanvas("canvas", "canvas", 1280, 960);
    
	// write out histogram stack and legend
	if(TFflag){
		canvas->Divide(1, 2);
		TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
		TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");
 
		// define the size
		double up_height     = 0.8; // please tune so that the upper figures size will meet your requirement
		double dw_correction = 1.40; // please tune so that the smaller canvas size will work in your environment
		double font_size_dw  = 0.1; // please tune the font size parameter for bottom figure
  
		double dw_height    = (1. - up_height) * dw_correction;
 
		// set pad size
		canvas_up->SetPad(0., 1 - up_height, 1., 1.);
		canvas_dw->SetPad(0., 0., 1., dw_height);
		canvas_up->SetFrameFillColor(0);
		canvas_up->SetFillColor(0);
		canvas_dw->SetFillColor(0);
		canvas_dw->SetFrameFillColor(0);
		  
		// set top margin 0 for bottom figure
		canvas_dw->SetTopMargin(0);
		  
		
		for (int k = 0; k < stacked_hists.size(); k++)
		{
			float maximum = stacked_hists.at(k)->GetMaximum("nostack");

			//if (not_stacked_hists.at(k)->GetMaximum("nostack") > maximum)
			//{
			//	maximum = not_stacked_hists.at(k)->GetMaximum("nostack");
			//}
			
			// draw top figure
			canvas_up->cd();
			
			stacked_hists.at(k)->SetMaximum(maximum * 1.2);
			//not_stacked_hists.at(k)->SetMaximum(maximum * 1.2);

			stacked_hists.at(k)->Draw("nostack");
			legends.at(k)->Draw("same");

			// draw bottom figure
			canvas_dw->cd();
			// font size
			//not_stacked_hists.at(k)->GetXaxis()->SetLabelSize(font_size_dw);
			//not_stacked_hists.at(k)->GetXaxis()->SetTitleSize(font_size_dw);
			//not_stacked_hists.at(k)->GetYaxis()->SetLabelSize(font_size_dw);
			//not_stacked_hists.at(k)->GetYaxis()->SetTitleSize(font_size_dw);
			not_stacked_hists.at(k)->Draw("nostack");

			char eps_file_name[256];
			sprintf(eps_file_name, "%s_%s.png", argv[1], stacked_hists.at(k)->GetName());
			canvas->SaveAs(eps_file_name);
		}
	  
	}
	else{
		for (int k = 0; k < stacked_hists.size(); k++)
		{
			float maximum = stacked_hists.at(k)->GetMaximum();

			if (not_stacked_hists.at(k)->GetMaximum("nostack") > maximum)
			{
				maximum = not_stacked_hists.at(k)->GetMaximum("nostack");
			}
			
			
			
			stacked_hists.at(k)->SetMaximum(maximum * 1.2);
			not_stacked_hists.at(k)->SetMaximum(maximum * 1.2);

			stacked_hists.at(k)->Draw();
			error.at(k)->Draw("SAME");
			not_stacked_hists.at(k)->Draw("samenostack");
			legends.at(k)->Draw("same");

			char eps_file_name[256];
			sprintf(eps_file_name, "%s_%s.png", argv[1], stacked_hists.at(k)->GetName());
			canvas->SaveAs(eps_file_name);
		}  
    }
	return 0;
}
