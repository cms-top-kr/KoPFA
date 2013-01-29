// reading a text file
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "DXSectionParameters.h"

using namespace std;

void NLOMtt(){

  TH1F * h_mtt = new TH1F("h_mtt","NLO+NNLL", 2720, 0, 2720);
  TH1F * h_mtt_up = new TH1F("h_mtt_up","NLO+NNLL", 2720, 0, 2720);
  TH1F * h_mtt_dw = new TH1F("h_mtt_dw","NLO+NNLL", 2720, 0, 2720);
 
  string line;
  ifstream myfile;
  myfile.open ("Mtt_7000_172.5_Mtt_fin.dat");
  double total = 0;
  double total_up = 0;
  double total_dw = 0;
  int index = 0;
  while ( !myfile.eof() && index < 95 )
  {
    double mttbar, central, scaleup, scaledw, pdfup, pdfdw, pdfalphasup, pdfalphasdw;
    myfile >> mttbar >> central >> scaleup >> scaledw >> pdfup >> pdfdw >> pdfalphasup >> pdfalphasdw ; 
    cout << mttbar << " " << central << " " << scaleup << " " << scaledw << " " << pdfup << " " << pdfdw << " " << pdfalphasup << " " << pdfalphasdw << endl;
    int bin = 346+index*25;
    for(int i = 0 ; i < 25 ; i++){
      h_mtt->SetBinContent(bin+i, central);
      h_mtt_up->SetBinContent(bin+i, central + scaleup + pdfalphasup);
      h_mtt_dw->SetBinContent(bin+i, central + scaledw + pdfalphasdw);
    }
    index++;
    total = total + central*25;
    total_up = total_up + (central+scaleup + pdfalphasup)*25;
    total_dw = total_dw + (central+scaledw + pdfalphasdw)*25;
  }

  myfile.close();

  TH1* h_mtt2 = (TH1*)h_mtt->Rebin(nDet,"h_mtt2",detBins);
  TH1* h_mtt2_up = (TH1*)h_mtt_up->Rebin(nDet,"h_mtt2_up",detBins);
  TH1* h_mtt2_dw = (TH1*)h_mtt_dw->Rebin(nDet,"h_mtt2_dw",detBins);

  double rebin = 0;
  double rebin_up = 0;
  double rebin_dw = 0;
  for(int i = 1; i <= h_mtt2->GetNbinsX() ; i++){
    h_mtt2->SetBinContent(i, h_mtt2->GetBinContent(i)/h_mtt2->GetBinWidth(i) );
    h_mtt2_up->SetBinContent(i, h_mtt2_up->GetBinContent(i)/h_mtt2_up->GetBinWidth(i) );
    h_mtt2_dw->SetBinContent(i, h_mtt2_dw->GetBinContent(i)/h_mtt2_dw->GetBinWidth(i) );
    rebin = rebin + h_mtt2->GetBinContent(i)*h_mtt2->GetBinWidth(i);
    rebin_up = rebin_up + h_mtt2_up->GetBinContent(i)*h_mtt2->GetBinWidth(i);
    rebin_dw = rebin_dw + h_mtt2_dw->GetBinContent(i)*h_mtt2->GetBinWidth(i);
  }

  cout << "total = " << total << " +" << total_up << " -" << total_dw << endl;
  cout << "check = " << rebin << " +" << rebin_up << " -" << rebin_dw << endl;

  h_mtt->Scale(1.0/total);
  h_mtt_up->Scale(1.0/total_up);
  h_mtt_dw->Scale(1.0/total_dw);
  h_mtt2->Scale(1.0/total);
  h_mtt2_up->Scale(1.0/total_up);
  h_mtt2_dw->Scale(1.0/total_dw); 

  for(int i = 1; i <= h_mtt2->GetNbinsX() ; i++){
    cout << "mass = " << h_mtt2->GetBinCenter(i) << " = " << h_mtt2->GetBinContent(i) << endl;
  }

  TCanvas * c = new TCanvas("c","c",1);
  h_mtt->SetLineWidth(0.4);
  h_mtt->SetLineColor(1);
  h_mtt_up->SetLineWidth(0.4);
  h_mtt_up->SetLineColor(2);
  h_mtt_dw->SetLineWidth(0.4);
  h_mtt_dw->SetLineColor(4);
  h_mtt->SetStats(0);
  h_mtt_up->SetStats(0);
  h_mtt_dw->SetStats(0);

  h_mtt_up->Draw();
  h_mtt->Draw("same");
  h_mtt_dw->Draw("same");
  c->Print("c_NLO_NNLL_norm.png");

  TCanvas * c2 = new TCanvas("c2","c2",1);
  h_mtt2->SetLineWidth(0.4);
  h_mtt2->SetLineColor(1);
  h_mtt2_up->SetLineWidth(0.4);
  h_mtt2_up->SetLineColor(2);
  h_mtt2_dw->SetLineWidth(0.4);
  h_mtt2_dw->SetLineColor(4);
  h_mtt2->SetStats(0);
  h_mtt2_up->SetStats(0);
  h_mtt2_dw->SetStats(0);  

  h_mtt2_up->Draw();
  h_mtt2->Draw("same");
  h_mtt2_dw->Draw("same");
  c2->Print("c2_NLO_NNLL_norm.png");

  TFile* f = TFile::Open("NLOMtt_norm.root", "recreate");
  h_mtt->Write();
  h_mtt_up->Write();
  h_mtt_dw->Write();
  h_mtt2->Write();
  h_mtt2_up->Write();
  h_mtt2_dw->Write();
  f->Write();
  f->Close();

}
