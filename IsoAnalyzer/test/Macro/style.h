void SetLatex(double x, double y){
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(x,y,"CMS Preliminary 2010");
  //label->DrawLatex(x,y-0.05,"11.4 nb^{-1} at #sqrt{s} = 7 TeV");
  label->DrawLatex(x,y-0.05,"#sqrt{s} = 7 TeV, #DeltaR=0.4");
}

void SetLatex2(double x, double y){
  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(x,y,"CMS Preliminary 2010");
  //label->DrawLatex(x,y-0.05,"11.4 nb^{-1} at #sqrt{s} = 7 TeV");
  label->DrawLatex(x,y-0.05,"#sqrt{s} = 7 TeV");
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

void SetLegend(TGraphAsymmErrors* h1, TGraphAsymmErrors* h2, TString& leg1, TString& leg2, TString& o1, TString& o2,double x1, double y1, double x2, double y2){
  TLegend *l= new TLegend(x1,y1,x2,y2);
  l->AddEntry(h1,Form("%s",leg1.Data()),Form("%s",o1.Data()));
  l->AddEntry(h2,Form("%s",leg2.Data()),Form("%s",o2.Data()));
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
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

  h2->SetFillStyle(1001);
  h2->SetFillColor(kRed-8);
  h2->SetLineWidth(4);
  h2->SetLineColor(2);
  h2->SetStats(0);
  h2->SetTitle(0);
  h2->GetXaxis()->SetTitle(xtitle.Data());
  h2->GetYaxis()->SetTitle(ytitle.Data());
}

void Style2( TGraphAsymmErrors * h1, TGraphAsymmErrors * h2){
  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(1.0);
  h2->SetMarkerColor(2);
  h2->Draw("PSame");

  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(1.0);
  h1->SetMarkerColor(1);
  h1->Draw("PSame");
}

void Print(TCanvas* c, TString& dir, TString& hName, TString& name, bool print){
  if(print){
    c->Print(Form("%s/c_%s_%s.pdf",dir.Data(),hName.Data(),name.Data()));
    c->Print(Form("%s/c_%s_%s.eps",dir.Data(),hName.Data(),name.Data()));   
    c->Print(Form("%s/c_%s_%s.png",dir.Data(),hName.Data(),name.Data()));
  }
}

string int2string(int i){
  stringstream ss;
  ss << i;
  string s= ss.str();
  return s;
}

//Counting experiment from binomial distribution sigma = sqrt(p(1-p)/n)  
double sigma(double nu, double de, int a){
  double err = 0;
  if( de != 0 ) {
    float p = nu/de;
    err = a*sqrt( p*(1-p)/de );
  }
  return err;
}

