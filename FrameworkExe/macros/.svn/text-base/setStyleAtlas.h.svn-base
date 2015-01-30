#include "TStyle.h"
#include "TLatex.h"

void setStyleAtlas() {

    Int_t icol = 0;
    gStyle->SetFrameBorderMode(icol);
    gStyle->SetFrameFillColor(icol);
    gStyle->SetCanvasBorderMode(icol);
    gStyle->SetCanvasColor(icol);
    gStyle->SetPadBorderMode(icol);
    gStyle->SetPadColor(icol);
    gStyle->SetStatColor(icol);
    //gStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

    // set the paper & margin sizes
    gStyle->SetPaperSize(20, 26);

    // set margin sizes
    gStyle->SetPadTopMargin(0.05);
    gStyle->SetPadRightMargin(0.05);
    gStyle->SetPadBottomMargin(0.16);
    gStyle->SetPadLeftMargin(0.16);

    // set title offsets (for axis label)
    gStyle->SetTitleXOffset(1.4);
    gStyle->SetTitleYOffset(1.4);

    // use large fonts
    //Int_t font=72; // Helvetica italics
    Int_t font = 42; // Helvetica
    Double_t tsize = 0.05;
    gStyle->SetTextFont(font);

    gStyle->SetTextSize(tsize);
    gStyle->SetLabelFont(font, "x");
    gStyle->SetTitleFont(font, "x");
    gStyle->SetLabelFont(font, "y");
    gStyle->SetTitleFont(font, "y");
    gStyle->SetLabelFont(font, "z");
    gStyle->SetTitleFont(font, "z");

    gStyle->SetLabelSize(tsize, "x");
    gStyle->SetTitleSize(tsize, "x");
    gStyle->SetLabelSize(tsize, "y");
    gStyle->SetTitleSize(tsize, "y");
    gStyle->SetLabelSize(tsize, "z");
    gStyle->SetTitleSize(tsize, "z");

    // use bold lines and markers
    gStyle->SetMarkerStyle(20);
    gStyle->SetMarkerSize(1.2);
    gStyle->SetHistLineWidth((Width_t) 2.);
    gStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes

    // get rid of X error bars 
    //gStyle->SetErrorX(0.001);
    // get rid of error bar caps
    //gStyle->SetEndErrorSize(0.);

    // do not display any of the standard histogram decorations
    gStyle->SetOptTitle(0);
    //gStyle->SetOptStat(1111);
    gStyle->SetOptStat(0);
    //gStyle->SetOptFit(1111); 
    gStyle->SetOptFit(0);

    // put tick marks on top and RHS of plots
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);

}

void myText(Double_t x,Double_t y,Color_t color, const char *text) {

  //Double_t tsize=0.05;
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextColor(color);
  l.DrawLatex(x,y,text);
}
 

void ATLAS_LABEL(Double_t x,Double_t y,Color_t color) 
{
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextFont(72);
  l.SetTextColor(color);
  l.DrawLatex(x,y,"ATLAS");
}
