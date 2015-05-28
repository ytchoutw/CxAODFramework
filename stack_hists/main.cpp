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
    int color[] = {kOrange, kOrange-3, kOrange - 1,kGreen - 9, kGreen - 4,kGreen - 2, kAzure + 2, kAzure - 4, kViolet, kCyan, kRed, kBlue};
    
	bool TFflag = false;
	if( file_num  == 2) TFflag = true;
	
	 
	// set style for plots
	SetAtlasStyle();

	// stacked histograms and legends
	vector<THStack*> stacked_hists;
	vector<THStack*> not_stacked_hists;
	
	vector<TH1F*> hists_TF;
	hists_TF.reserve(200);	
	
	vector<TH1F*> error;
	vector<TLegend*> legends;
	stacked_hists.reserve(200);		// histograms here will stack
	not_stacked_hists.reserve(200);		// histograms here will overlay the stacked histograms
	error.reserve(200);
	legends.reserve(200);
	
	// use the first input file to set our histograms and legends
	TFile * first_hist_file = new TFile(argv[3]);

	// iterate over keys
	TIter next(first_hist_file->GetListOfKeys());
	TKey * first_key;
    int pass(0); 
    vector<double> norm;

	for(unsigned int i(0);i < 200;i++){
		norm.push_back(0);
	}
	
	while (first_key = (TKey*) next())		
	{   if(pass < 3){
			pass++; 
			continue;
		}
		
		//std::cout << first_key->GetName() << std::endl;
	    
		TH1F * hist = (TH1F*) first_hist_file->Get(first_key->GetName());
        
		char title[256];
		sprintf(title, "%s;%s;%s", first_key->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle());
		char title_TF[256];
		sprintf(title_TF, "%s;%s;%s", first_key->GetTitle(), hist->GetXaxis()->GetTitle(), "Znunu/Wmunu+jets");
		if(TFflag){
			TString hist_name(first_key->GetName());
			if(hist_name.Contains("#slash{E}_{T}")){
				stacked_hists.push_back(new THStack(first_key->GetName(), title));
				not_stacked_hists.push_back(new THStack(first_key->GetName(), title_TF));	
				legends.push_back(new TLegend(0.6, 0.4, 0.9, 0.9, first_key->GetTitle()));
				legends.back()->SetFillStyle(0);
				legends.back()->SetBorderSize(0);
			}
				
		}
		if(pass >= 3 && !TFflag){
		stacked_hists.push_back(new THStack(first_key->GetName(), title));
		not_stacked_hists.push_back(new THStack(first_key->GetName(), title));
		error.push_back(hist);//new TH1F(first_key->GetName(), first_key->GetTitle(),hist->GetXaxis()->GetNbins(),hist->GetXaxis()->GetXmin(),hist->GetXaxis()->GetXmax()));
		legends.push_back(new TLegend(0.6, 0.4, 0.9, 0.9, first_key->GetTitle()));
		legends.back()->SetFillStyle(0);
		legends.back()->SetBorderSize(0);
		
		} 
		
	}
	
	
	if(TFflag){
		TFile * hist_file = new TFile(argv[3]);   //Zvv
		TFile * hist_file_2 = new TFile(argv[6]);   //Zll

        std::cout << "E1" << std::endl;
		// histograms
		vector<TH1F*> hists;
		hists.reserve(200);

		vector<TH1F*> hists_2;
		hists_2.reserve(200);
		
		TIter next(hist_file->GetListOfKeys());
		TKey * key;		
		TIter next_2(hist_file_2->GetListOfKeys());
		TKey * key_2;
		
		int j = 0;
		int passn(0);
		std::cout << "E1-1" << std::endl;
		while (key = (TKey*) next())
		{   std::cout << "E1-2" << std::endl;
			TString histname(key->GetName());		
			if(histname.Contains("#slash{E}_{T}")){
				std::cout << "E1-2-1" << std::endl;
				hists.push_back((TH1F*) hist_file->Get(key->GetName()));
				hists.back()->SetLineColor(color[5]);
				hists.back()->SetMarkerColor(color[5]);
				hists.back()->Sumw2(false);
				stacked_hists.at(j)->Add(hists.back());
				legends.at(j)->AddEntry(hists.back(), argv[4], "l");
				j++;
			}			
					
		}	
        int j_2 = 0	;	
		while (key_2 = (TKey*) next_2()){
			std::cout << "E1-3" << std::endl;
			TString histname_2(key_2->GetName());
			if(histname_2.Contains("#slash{E}_{T}")){
				std::cout << "E1-3-1" << std::endl;
				hists_2.push_back((TH1F*) hist_file_2->Get(key_2->GetName()));	
				hists_2.back()->SetLineColor(color[6]);
				hists_2.back()->SetMarkerColor(color[6]);	
				hists_2.back()->Sumw2(false);
				stacked_hists.at(j_2)->Add(hists_2.back());
				legends.at(j_2)->AddEntry(hists_2.back(), argv[7], "l");
				j_2++;
			}		
		}		
		std::cout << "E2" << std::endl;
        if(hists.size() != hists_2.size()) std::cout << "ERROR" << std::endl;  
		for(unsigned int i(0); i < hists.size();i++ ){
			TH1F* hist_1(new TH1F(*hists[i])); 
			hist_1->Divide(hists_2[i]);
			hists_TF.push_back(hist_1);		
			not_stacked_hists.at(i)->Add(hists_TF.back());	
		}	
	    
		
	}
    else{
	for (int i = 0; i < file_num; i++)
	{
		// hist file
		TFile * hist_file = new TFile(argv[3 * i + 3]);
        
		// histograms
		vector<TH1F*> hists;
		hists.reserve(200);

		// iterate over keys
		TIter next(hist_file->GetListOfKeys());
		TKey * key;

		int j = 0;
		int passn(0);
		while (key = (TKey*) next())
		{   
			if(passn <3)
			{passn++; continue;}
	
		    //std::cout << key->GetName() << std::endl;
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
				//std::cout << key->GetName() << std::endl;
				error.at(j)->Add(hists.back());
				//std::cout << error.at(j)->GetName() << std::endl;
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
		hists.reserve(200);

		// iterate over keys
		TIter next(hist_file->GetListOfKeys());
		TKey * key;

		int j = 0;
		int passn(0);
		while (key = (TKey*) next())
		{   
			if(passn <3)
			{passn++; continue;}
	
		    //std::cout << key->GetName() << std::endl;
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
	TCanvas * canvas_TF = new TCanvas("canvas_TF", "canvas_TF", 1280, 960);
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

			
			// draw top figure
			canvas->cd(1);
			
			stacked_hists.at(k)->SetMaximum(maximum * 1.2);

			stacked_hists.at(k)->Draw("nostack");
			legends.at(k)->Draw("same");

			// draw bottom figure
			canvas->cd(2);
			not_stacked_hists.at(k)->Draw("nostack");

			char eps_file_name[256];
			
			sprintf(eps_file_name, "%s_%s.png", argv[1], stacked_hists.at(k)->GetName());
			canvas->SaveAs(eps_file_name);
			
			canvas_TF->cd();
			not_stacked_hists.at(k)->Draw("nostack");
			sprintf(eps_file_name, "%s_%s_TF.png", argv[1], stacked_hists.at(k)->GetName());

			canvas_TF->SaveAs(eps_file_name);  
			int num = 0;
			TString hist_name = stacked_hists.at(k)->GetName();
			for(int w(0); w< 7;w++){
				TString  s_num = std::to_string(w);
				if(hist_name.Contains(s_num)) num = w;
				
			}
			char root_file_name[256];
			sprintf(root_file_name, "%s_Curve:%i_TF.root", argv[1],num);
			TFile f(root_file_name,"recreate");
			hists_TF.at(k)->Write();
			f.Close();
			  
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
