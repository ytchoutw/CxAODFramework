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
    int color[] = {kOrange, kOrange, kOrange - 1,kGreen - 9, kGreen - 9,kGreen - 9, kAzure + 2, kAzure - 4, kYellow, kCyan, kRed, kBlue};
     
	// set style for plots
	SetAtlasStyle();

	// stacked histograms and legends
	vector<THStack*> stacked_hists;
	vector<THStack*> not_stacked_hists;
	vector<TLegend*> legends;
	stacked_hists.reserve(100);		// histograms here will stack
	not_stacked_hists.reserve(100);		// histograms here will overlay the stacked histograms
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

		stacked_hists.push_back(new THStack(first_key->GetName(), title));
		not_stacked_hists.push_back(new THStack(first_key->GetName(), title));

		legends.push_back(new TLegend(0.6, 0.4, 0.9, 0.9, first_key->GetTitle()));
		legends.back()->SetFillStyle(0);
		legends.back()->SetBorderSize(0);
		
		
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
			//hists.back()->SetMarkerColor(color[i]);
			hists.back()->Sumw2(false);
			// add histogram to one of the histogram stacks
			if (atoi(argv[3 * i + 5]))
			{	
				
				hists.back()->SetFillColor(color[i]);
				hists.back()->SetFillStyle(1001);
				// add it to the stacked histograms
				stacked_hists.at(j)->Add(hists.back());
				norm.at(j) += hists.back()->Integral();
			}
			else
			{
				/*// add it to the not stacked histograms
				if( norm.at(j) ==0 ) hists.back()->Scale(1);
				else {
					hists.back()->Scale(norm.at(j)/hists.back()->Integral());
				}
				//hists.back()->Scale(40);
				not_stacked_hists.at(j)->Add(hists.back());*/
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
			//hists.back()->SetMarkerColor(color[i]);
			hists.back()->Sumw2(false);
			// add histogram to one of the histogram stacks
			if (atoi(argv[3 * i + 5]))
			{	
				
				/*hists.back()->SetFillColor(color[i]);
				hists.back()->SetFillStyle(1001);
				// add it to the stacked histograms
				stacked_hists.at(j)->Add(hists.back());
				norm.at(j) += hists.back()->Integral();*/
			}
			else
			{
				// add it to the not stacked histograms
				//if( norm.at(j) ==0 ) hists.back()->Scale(1);
				hists.back()->Scale(norm.at(j)/hists.back()->Integral());
				//hists.back()->Scale(40);
				not_stacked_hists.at(j)->Add(hists.back());
			}

			// add it to the legend
			//legends.at(j)->AddEntry(hists.back(), argv[3 * i + 4], "l");
            j++;
		}
	} 	
	
	// canvas for histogram eps files
	TCanvas * c1 = new TCanvas("c1", "c1", 640, 480);
    
	// write out histogram stack and legend
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
		not_stacked_hists.at(k)->Draw("samenostack");
		legends.at(k)->Draw("same");

		char eps_file_name[256];
		sprintf(eps_file_name, "%s_%s.png", argv[1], stacked_hists.at(k)->GetName());
		c1->SaveAs(eps_file_name);
	}
    
	return 0;
}
