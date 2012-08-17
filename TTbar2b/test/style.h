#include "TLatex.h"
#include "TPaveText.h"

void SetLatex(double x, double y){
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  //label->DrawLatex(x,y,"CMS Preliminary 2010");
  //label->DrawLatex(x,y-0.05,"11.4 nb^{-1} at #sqrt{s} = 7 TeV");
  label->DrawLatex(x,y-0.05,"#sqrt{s} = 7 TeV, #DeltaR=0.4");
}

void SetLabel(double x, double y, double lumi){
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(x,y,"CMS Preliminary");
  label->DrawLatex(x,y-0.05,Form("%1.1f fb^{-1} at #sqrt{s} = 7 TeV",lumi/1000));
}

void SetLegendStyle(TLegend *l, bool dynamic=false){
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);

  if( dynamic ){
    l->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.25);
    l->SetY1NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength() - 0.05 - (double)l->GetNRows()*0.04);
    l->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
    l->SetY2NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength());
  }
}

void SetLegend(TH1* h1, TH1* h2, TString& leg1, TString& leg2, TString& o1, TString& o2,double x1, double y1, double x2, double y2){
  TLegend *l= new TLegend(x1,y1,x2,y2);
  l->AddEntry(h1,Form("%s",leg1.Data()),Form("%s",o1.Data()));
  l->AddEntry(h2,Form("%s",leg2.Data()),Form("%s",o2.Data()));
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void SetLegend(TH1* h1, TGraphAsymmErrors* h2, TString& leg1, TString& leg2, TString& o1, TString& o2, double x1, double y1, double x2, double y2){
  TLegend *l= new TLegend(x1,y1,x2,y2);
  l->AddEntry(h1,Form("%s",leg1.Data()),Form("%s",o1.Data()));
  l->AddEntry(h2,Form("%s",leg2.Data()),Form("%s",o2.Data()));
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}


void SetLegend(TH1* h1, TH1* h2, TH1* h3, TGraphAsymmErrors* h4, TString& leg1, TString& leg2, TString& leg3, TString& leg4, TString& o1, TString& o2, TString& o3, TString& o4, double x1, double y1, double x2, double y2){
  TLegend *l= new TLegend(x1,y1,x2,y2);
  l->AddEntry(h4,Form("%s",leg4.Data()),Form("%s",o4.Data()));
  l->AddEntry(h1,Form("%s",leg1.Data()),Form("%s",o1.Data()));
  l->AddEntry(h2,Form("%s",leg2.Data()),Form("%s",o2.Data()));
  l->AddEntry(h3,Form("%s",leg3.Data()),Form("%s",o3.Data()));
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void SetLegend(TGraph* h1, TGraph* h2, TGraph* h3, TGraph* h4, TString& leg1, TString& leg2, TString& leg3, TString& leg4, TString& o1, TString& o2, TString& o3, TString& o4, double x1, double y1, double x2, double y2){
  TLegend *l= new TLegend(x1,y1,x2,y2);
  l->AddEntry(h1,Form("%s",leg1.Data()),Form("%s",o1.Data()));
  l->AddEntry(h2,Form("%s",leg2.Data()),Form("%s",o2.Data()));
  l->AddEntry(h3,Form("%s",leg3.Data()),Form("%s",o3.Data()));
  l->AddEntry(h4,Form("%s",leg4.Data()),Form("%s",o4.Data()));
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void SetLegend(TGraph* h1, TGraph* h2, TGraph* h3, TString& leg1, TString& leg2, TString& leg3, TString& o1, TString& o2, TString& o3, double x1, double y1, double x2, double y2){
  TLegend *l= new TLegend(x1,y1,x2,y2);
  l->AddEntry(h1,Form("%s",leg1.Data()),Form("%s",o1.Data()));
  l->AddEntry(h2,Form("%s",leg2.Data()),Form("%s",o2.Data()));
  l->AddEntry(h3,Form("%s",leg3.Data()),Form("%s",o3.Data()));
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void SetLegend(TGraph* h1, TGraph* h2, TString& leg1, TString& leg2, TString& o1, TString& o2, double x1, double y1, double x2, double y2){
  TLegend *l= new TLegend(x1,y1,x2,y2);
  l->AddEntry(h1,Form("%s",leg1.Data()),Form("%s",o1.Data()));
  l->AddEntry(h2,Form("%s",leg2.Data()),Form("%s",o2.Data()));
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}



void SetLegend(TGraphAsymmErrors* h4, TH1* h1, TH1* h2, TH1* h3, TString& leg4, TString& leg1, TString& leg2, TString& leg3, TString& o4, TString& o1, TString& o2, TString& o3, double x1, double y1, double x2, double y2){
  TLegend *l= new TLegend(x1,y1,x2,y2);
  l->AddEntry(h1,Form("%s",leg1.Data()),Form("%s",o1.Data()));
  l->AddEntry(h2,Form("%s",leg2.Data()),Form("%s",o2.Data()));
  l->AddEntry(h3,Form("%s",leg3.Data()),Form("%s",o3.Data()));
  l->AddEntry(h4,Form("%s",leg4.Data()),Form("%s",o4.Data()));
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void SetLegend(TGraphAsymmErrors* h5, TGraphAsymmErrors* h4, TH1* h1, TH1* h2, TH1* h3, TString& leg5, TString& leg4, TString& leg1, TString& leg2, TString& leg3, TString& o5, TString& o4, TString& o1, TString& o2, TString& o3, double x1, double y1, double x2, double y2){
  TLegend *l= new TLegend(x1,y1,x2,y2);
  l->AddEntry(h1,Form("%s",leg1.Data()),Form("%s",o1.Data()));
  l->AddEntry(h2,Form("%s",leg2.Data()),Form("%s",o2.Data()));
  l->AddEntry(h3,Form("%s",leg3.Data()),Form("%s",o3.Data()));
  l->AddEntry(h4,Form("%s",leg4.Data()),Form("%s",o4.Data()));
  l->AddEntry(h5,Form("%s",leg5.Data()),Form("%s",o5.Data()));
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void SetLegend(TGraphAsymmErrors* h1, TGraphAsymmErrors* h2, TString& leg1, TString& leg2, TString& o1, TString& o2,double x1, double y1, double x2, double y2){
  TLegend *l= new TLegend(x1,y1,x2,y2);
  l->AddEntry(h1,Form("%s",leg1.Data()),Form("%s",o1.Data()));
  l->AddEntry(h2,Form("%s",leg2.Data()),Form("%s",o2.Data()));
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
}

void SetGraphStyle(TGraph* h, double lwidth, double lcolor, double lstyle, double msize, double mcolor, double mstyle, double min, double max, TString& xtitle, TString& ytitle){
  h->SetLineWidth(lwidth);
  h->SetLineColor(lcolor);
  h->SetLineStyle(lstyle);
  h->SetMarkerSize(msize);
  h->SetMarkerColor(mcolor);
  h->SetMarkerStyle(mstyle);
  h->SetMaximum(max);
  h->SetMinimum(min);
  h->SetTitle(0);
  h->GetXaxis()->SetTitle(xtitle.Data());
  h->GetYaxis()->SetTitle(ytitle.Data());
}

void SetHistoStyle(TH1* h, double lwidth, double lcolor, double lstyle, double msize, double mcolor, double mstyle, double min, double max, TString& xtitle, TString& ytitle){
  h->SetLineWidth(lwidth);
  h->SetLineColor(lcolor);
  h->SetLineStyle(lstyle);
  h->SetMarkerSize(msize);
  h->SetMarkerColor(mcolor);
  h->SetMarkerStyle(mstyle);
  h->SetMaximum(max);
  h->SetMinimum(min);
  h->SetStats(0);
  h->SetTitle(0);
  h->GetXaxis()->SetTitle(xtitle.Data());
  h->GetYaxis()->SetTitle(ytitle.Data());
}

void SetHistoStyle_TOP11013(TH1* h, double lwidth, double lcolor, double lstyle, double msize, double mcolor, double mstyle, double min, double max, TString& xtitle, TString& ytitle){
  h->SetLineWidth(lwidth);
  h->SetLineColor(lcolor);
  h->SetLineStyle(lstyle);
  h->SetMarkerSize(msize);
  h->SetMarkerColor(mcolor);
  h->SetMarkerStyle(mstyle);
  h->SetMaximum(max);
  h->SetMinimum(min);
  h->SetStats(0);
  h->SetTitle(0);
  h->GetXaxis()->SetTitle(xtitle.Data());
  h->GetYaxis()->SetTitle(ytitle.Data());
  h->GetXaxis()->SetTitleSize(0.04);
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetXaxis()->SetTitleOffset(1.25);
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetTitleOffset(1.6);
  h->GetYaxis()->SetTitleFont(42);
  h->GetZaxis()->SetLabelFont(42);
  h->GetZaxis()->SetLabelOffset(0.007);
  h->GetZaxis()->SetTitleFont(42);
}

void StyleSimple(TH1* h1, TH1* h2, TString& xtitle, TString& ytitle ){

  h1->SetLineWidth(4);
  h1->SetLineColor(2);
  h1->SetStats(0);
  h1->SetTitle(0);
  h1->GetXaxis()->SetTitle(xtitle.Data());
  h1->GetYaxis()->SetTitle(ytitle.Data());
  
  h2->SetLineWidth(4);
  h2->SetLineColor(4);
  h2->SetStats(0);
  h2->SetTitle(0);
  h2->GetXaxis()->SetTitle(xtitle.Data());
  h2->GetYaxis()->SetTitle(ytitle.Data());

}

void Style(TH1* h1, TH1* h2, TString& xtitle, TString& ytitle ){

  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(1.0);
  h1->SetMarkerColor(1);
  h1->SetStats(0);
  h1->SetTitle(0);
  h1->GetXaxis()->SetTitle(xtitle.Data());
  h1->GetYaxis()->SetTitle(ytitle.Data());

  //h2->SetFillStyle(1001);
  //h2->SetFillColor(kRed-8);
  //h2->SetLineWidth(4);
  //h2->SetLineColor(2);
  h2->SetLineColor(1);
  h2->SetStats(0);
  h2->SetTitle(0);
  h2->GetXaxis()->SetTitle(xtitle.Data());
  h2->GetYaxis()->SetTitle(ytitle.Data());
}

void Style2( TGraphAsymmErrors * h1, TGraphAsymmErrors * h2){
  //h2->SetMarkerStyle(20);
  h2->SetMarkerStyle(24);
  h2->SetMarkerSize(1.0);
  //h2->SetMarkerColor(2);
  h2->SetMarkerColor(1);
  h2->Draw("PSame");

  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(1.0);
  h1->SetMarkerColor(1);

  h1->Draw("PSame");
}

void Print(TCanvas* c, TString& dir, const TString& hName, const TString& name, bool print){
  if(print){
//    c->Print(Form("%s/c_%s_%s.pdf",dir.Data(),hName.Data(),name.Data()));
    c->Print(Form("%s/c_%s_%s.eps",dir.Data(),hName.Data(),name.Data()));   
    c->Print(Form("%s/c_%s_%s.png",dir.Data(),hName.Data(),name.Data()));
    c->Print(Form("%s/c_%s_%s.C",dir.Data(),hName.Data(),name.Data()));
  }
}

//string int2string(int i){
//  stringstream ss;
//  ss << i;
//  string s= ss.str();
//  return s;
//}

//Counting experiment from binomial distribution sigma = sqrt(p(1-p)/n)  
double sigma(double nu, double de, int a){
  double err = 0;
  if( de != 0 ) {
    float p = nu/de;
    err = a*sqrt( p*(1-p)/de );
  }
  return err;
}

void clearXErrorBar(TGraphAsymmErrors * gr)
{
   for (Int_t i=0; i< gr->GetN(); ++i) {
      gr->SetPointEXhigh(i,0);
      gr->SetPointEXlow(i,0);
   }
}

//This is for Hamburg style
void DrawCMSLabels(bool cmsprelim=true, double luminosity=0.0, double textSize=0.04)
{
  // Draw official labels (CMS Preliminary, luminosity and CM energy) above plot

  TPaveText *label = new TPaveText();

  label -> SetX1NDC(gStyle->GetPadLeftMargin());
  label -> SetY1NDC(1.0-gStyle->GetPadTopMargin());
  label -> SetX2NDC(1.0-gStyle->GetPadRightMargin());
  label -> SetY2NDC(1.0);
  label -> SetTextFont(42);

  if (cmsprelim)
    {
      label -> AddText(Form("CMS Preliminary, %3.1f fb^{-1} at #sqrt{s}=7 TeV",luminosity/1000));
    }
  else
    {
      label -> AddText(Form("CMS, %3.1f fb^{-1} at #sqrt{s}=7 TeV",luminosity/1000));
    }

  label->SetFillStyle(0);
  label->SetBorderSize(0);
  if(textSize!=0) label->SetTextSize(textSize);
  label->SetTextAlign(32);
  label->Draw("same");
}

void DrawDecayChLabel(TString decaychannel="", double textSize=0.04)
{
  // Draw label for Decay Channel in upper left corner of plot

  TPaveText *decch = new TPaveText();

  decch -> AddText(decaychannel);

  decch -> SetX1NDC(      gStyle->GetPadLeftMargin() + gStyle->GetTickLength()        );
  decch -> SetY1NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() - 0.05 );
  decch -> SetX2NDC(      gStyle->GetPadLeftMargin() + gStyle->GetTickLength() + 0.15 );
  decch -> SetY2NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength()        );

  decch -> SetFillStyle(0);
  decch -> SetBorderSize(0);
  if(textSize!=0) decch->SetTextSize(textSize);
  decch -> SetTextAlign(12);
  decch -> Draw("same");
}

