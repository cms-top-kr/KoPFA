// reading a text file
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TH1.h"
#include "TGraphAsymmErrors.h"
#include "DXSectionParameters.h"

using namespace std;

void NLOMtt(){

  TH1F * h_mtt = new TH1F("h_mtt","h_mtt", 2708, 0, 2708); 
  TH1F * h_mtt_up = new TH1F("h_mtt_up","h_mtt_up", 2708, 0, 2708); 
  TH1F * h_mtt_dw = new TH1F("h_mtt_dw","h_mtt_dw", 2708, 0, 2708); 
 
  string line;
  ifstream myfile ("Mtt_7000_172.5_Mtt_fin.dat");

  while ( myfile.good() )
  {
    double mttbar, central, scaleup, scaledw, pdfup, pdfdw, pdfalphasup, pdfalphasdw;
    myfile >> mttbar >> central >> scaleup >> scaledw >> pdfup >> pdfdw >> pdfalphasup >> pdfalphasdw ; 
    cout << mttbar << " " << central << " " << scaleup << " " << scaledw << " " << pdfup << " " << pdfdw << " " << pdfalphasup << " " << pdfalphasdw << endl;
    int bin = (int) mttbar;
    h_mtt->SetBinContent(bin+1, central);
    h_mtt_up->SetBinContent(bin+1, central + scaleup + pdfalphasup);
    h_mtt_dw->SetBinContent(bin+1, central + scaledw + pdfalphasdw);
  }

  myfile.close();

  h_mtt->Scale(1.0/(double)h_mtt->Integral());
  h_mtt_up->Scale(1.0/(double)h_mtt_up->Integral());
  h_mtt_dw->Scale(1.0/(double)h_mtt_dw->Integral());

  TH1F* h_mtt2 = (TH1F*)h_mtt->Rebin(nDet,"h_mtt2",detBins);
  TH1F* h_mtt2_up = (TH1F*)h_mtt_up->Rebin(nDet,"h_mtt2_up",detBins);
  TH1F* h_mtt2_dw = (TH1F*)h_mtt_dw->Rebin(nDet,"h_mtt2_dw",detBins);

  h_mtt2->SetLineWidth(0.4);
  h_mtt2->SetLineColor(1);
  h_mtt2_up->SetLineWidth(0.4);
  h_mtt2_up->SetLineColor(2);
  h_mtt2_dw->SetLineWidth(0.4);
  h_mtt2_dw->SetLineColor(4);

  h_mtt2_up->Draw();
  h_mtt2->Draw("same");
  h_mtt2_dw->Draw("same");

  TFile* f = TFile::Open("NLOMtt.root", "recreate");
  h_mtt->Write();
  h_mtt_up->Write();
  h_mtt_dw->Write();
  f->Write();
  f->Close();

}
