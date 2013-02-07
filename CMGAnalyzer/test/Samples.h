#ifndef Samples_h
#define Samples_h

#include "TGraphAsymmErrors.h"

double lumi_=10000.;
TString dir_="ElectronAnalysis";

class Sample {
public : 

  TString name;
  TFile *file;
  double norm;
  int fillcolor;
  int linecolor;
  TString label;

  Sample(TFile *file_, const TString & name_, const TString & label_, int fillcolor_, double X = -1.0, int linecolor_ = 1)
  {
      file = file_;
      name = name_;
      label = label_;
      fillcolor = fillcolor_;
      linecolor = linecolor_;
      if( X == -1.0){
        norm =1.0;
      }else{
        TH1F* h = (TH1F*) file_->Get(Form("%s/EventSummary",dir_.Data()));
        double nTotal = h->GetBinContent(1);
        norm =getNorm( nTotal, X, lumi_);
      }
  };
  ~Sample(){};

  double getNorm( double nTotal, double X, double lumi){
     double SF = lumi * X / nTotal;
     return SF;
  };
};

class Samples {
public : 

   std::vector<Sample> sample;
   
   Samples(){};
   ~Samples();
   void Add(const Sample sample_){ sample.push_back(sample_);};

   TH1F* plotSample(const TString & histName,const TString & sampleName, bool in=true)
   {
      TH1F *hSample;
      bool p=false;
      for( unsigned int i = 0 ; i < sample.size() ; i++){
          bool p2 = sample.at(i).name.Contains(sampleName.Data());
          if(!in ) p2 = !p2;

          if(!p && p2 ) {
              hSample = (TH1F *) sample.at(i).file->Get(Form("%s/%s", dir_.Data(), histName.Data()));
              hSample->Scale( sample.at(i).norm );
              p=true;
          }
          else if( p2 ){
             TH1F *h = (TH1F *) sample.at(i).file->Get(Form("%s/%s", dir_.Data(), histName.Data()));
             hSample->Scale( sample.at(i).norm );
             hSample->Add(h);
          }
      }
      return hSample;
   };
   TH1F* plotData(const TString & histName){   return  plotSample(histName.Data(),"Run"); };
   TH1F* plotMC(const TString & histName)  {   return  plotSample(histName.Data(),"Run",false);};     
   TH1F* plotSub( const TString & histName){
      TH1F *hData =  plotData(histName.Data());
      hData->Add(    plotMC(histName.Data()),-1);
      return hData;
   };
   void plotStack(const TString & histName, const TString & canvasName, const TString & title,  double min, double max, bool log = false)
   {

       TCanvas * c = new TCanvas(Form("c_%s",canvasName.Data()), Form("c_%s",canvasName.Data()) ,1);
       if(log) c->SetLogy(); 
         
       TLegend *l= new TLegend(0.7,0.7,0.87,0.87);
       l->SetTextSize(0.04);
       l->SetFillColor(0);
       l->SetLineColor(0);
       l->Draw();

       TH1F *hData = (TH1F *) sample[0].file->Get(Form("%s/%s", dir_.Data(), histName.Data()));
       hData->SetMarkerSize(0.4);
       hData->SetMarkerStyle(20);
       l->AddEntry(hData, sample[0].label, "P");
       cout << "Data = " << hData->Integral() << endl;
       double totalBkg = 0;

       THStack *hs = new THStack("hs",Form("%s",histName.Data()));       
       for( unsigned int i = 1 ; i < sample.size() ; i++){
          TH1F * h = (TH1F*) sample[i].file->Get(Form("%s/%s", dir_.Data(), histName.Data()));
          h->SetFillColor( sample[i].fillcolor );
          h->SetLineColor( sample[i].linecolor );
          h->Scale( sample.at(i).norm );
          hs->Add(h);
          if( sample[i].linecolor == 1 ){
             l->AddEntry( h, sample[i].label, "F" );
          }
          cout << sample[i].name << "(" << histName.Data() << ") = " << h->Integral() << endl;
          totalBkg += h->Integral();
       }
       double DataSub = hData->Integral() - totalBkg;
       cout << "DataSub= " << DataSub << endl;

       hs->SetMaximum( max );
       hs->SetMinimum( min );
       hs->SetTitle(title.Data());
       
       hs->Draw();
       hData->Draw("sameP");
       l->Draw();

       c->Print(Form("%s.eps",canvasName.Data()));
   };
////////////
  void plotCutOpt(const TString & canvasName, const TString & title, TH1F* hSig, TH1F* hBkg)
  {

     TCanvas * c_opt = new TCanvas(Form("c_opt_%s",canvasName.Data()),Form("c_opt_%s",canvasName.Data()),500,500);
     int nbin = hSig->GetNbinsX();
     double xmin=hSig->GetBinLowEdge(1)-hSig->GetBinWidth(1)/2;
     double xmax=hSig->GetBinLowEdge(nbin)-hSig->GetBinWidth(nbin)/2;
     
     TH1* h_opt = new TH1F("h_opt","h_opt",nbin,xmin,xmax);
     
     for(int i=0; i < nbin ; i++){
       double Si = hSig->Integral(i+1,nbin);
       double Bi = hBkg->Integral(i+1,nbin);
       double soverb = Si/sqrt(Si+Bi);
       h_opt->SetBinContent(i+1, soverb);
     } 
     SetFrame( h_opt, title.Data(), "S/#sqrt{S+B}");
     h_opt->Draw();
     
     c_opt->Print("c_opt_%s.eps",canvasName.Data());
     
     TCanvas * c_eff = new TCanvas(Form("c_eff_%s",canvasName.Data()),Form("c_eff_%s",canvasName.Data()),500,500);

     TH1* h_eff = new TH1F("h_eff","h_eff",nbin,xmin,xmax);
     double total = hSig->Integral(1,nbin); 
     for(int i=0; i < nbin ; i++){
       double Si = hSig->Integral(i+1,nbin);
       double Ei = Si/total;
       h_eff->SetBinContent(i+1, Ei);
     }
    
     SetFrame( h_eff, title.Data(), "Efficiency");
     h_eff->Draw();
     c_eff->Print("c_eff_%s.eps",canvasName.Data());
  };
  void plotSigBkg(const TString & canvasName, const TString & xtitle, TH1F* hSig, TH1F* hBkg)
  {
    TCanvas * c = new TCanvas(Form("c_%s",canvasName.Data()),Form("c_%s",canvasName.Data()),500,500);
    c->SetLogy();
    SetFrame( hSig, xtitle.Data(),"Entries");
    SetFrame( hBkg, xtitle.Data(),"Entries");
    hSig->SetLineColor(4);
    hSig->SetLineWidth(0.4);
    hBkg->SetLineColor(2);
    hBkg->SetLineWidth(0.4);
    
    hSig->Draw();
    hBkg->Draw("same"); 
    
    TLegend *l= new TLegend(0.4,0.7,0.6,0.87);
    l->AddEntry(hSig,"Signal","L");
    l->AddEntry(hBkg,"Background","L");
    l->SetTextSize(0.04);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->Draw();
    
    c->Print(Form("c_%s.eps",canvasName.Data()));
  };

  void plotMulti(const TString & canvasName, const TString & xtitle, const TString & ytitle, std::vector<TH1F*> hSample, std::vector<TString> labels)
  {

    TCanvas * c = new TCanvas(Form("c_%s",canvasName.Data()),Form("c_%s",canvasName.Data()),500,500);
  //  c->SetLogy();
    TLegend *l= new TLegend(0.6,0.4,0.8,0.87);
    l->SetTextSize(0.04);
    l->SetFillColor(0);
    l->SetLineColor(0);

    for(int i=0;i<hSample.size();i++){
       TH1F* h = (TH1F*) hSample.at(i); 
       if(i==0) SetFrame( h, xtitle.Data(),ytitle.Data());
       if(i<9) h->SetLineColor(i+1);
       else h->SetLineColor(i+2);
       h->SetLineWidth(0.4);
       l->AddEntry(h,labels.at(i).Data(),"L");

       if(i==0)  h->Draw();
       else     h->Draw("same");

    } 
    l->Draw();
    c->Print(Form("c_%s.eps",canvasName.Data()));
  };

  TGraphAsymmErrors* ROC( TH1* hSignal, TH1* hQCD){
      TGraphAsymmErrors* out = new TGraphAsymmErrors();
      int nbins = hSignal->GetNbinsX();
      double totalS = hSignal->Integral();//GetEntries();
      double totalB = hQCD->Integral();//GetEntries();
      cout << "totalS = " << totalS << " totalB= " << totalB << endl;
      for(int i=0 ; i < nbins; i++){
        double Bi = hQCD->Integral(i+1,nbins);
        double Si = hSignal->Integral(i+1,nbins);
        double eff_qcd = Bi / totalB;
        double eff_signal = Si/ totalS; 
        double err_qcd = sqrt(Bi) / totalB;
        double soverb = Si/Bi;
        cout << "i= " << 0.01*(i+1) << " signal eff = " << eff_signal << " background eff = " << eff_qcd << " s/s+b= " << soverb << endl ;
        out->SetPoint(i, eff_qcd, eff_signal);
        out->SetPointEXhigh(i,err_qcd);
        out->SetPointEXlow(i, err_qcd);
      }   
      return out;
 };


  void SetLabel(const TString & region){
    TLatex *label= new TLatex;
    label->SetNDC();
    label->SetTextSize(0.05);
    label->DrawLatex(0.2,0.8,"t#bar{t} simulation in 53X");
    label->DrawLatex(0.2,0.8-0.05,Form("%s, at #sqrt{s} = 8 TeV",region.Data()));
    label->Draw();
  };
  void SetFrame( TH1 * h, const TString & xtitle, const TString & ytitle){
    h->SetTitle("");
    h->GetXaxis()->SetTitle(Form("%s",xtitle.Data()));
    h->GetYaxis()->SetTitle(Form("%s",ytitle.Data()));
    h->GetXaxis()->SetTitleSize(0.06);
    h->GetYaxis()->SetTitleSize(0.06);
    h->GetXaxis()->SetTitleOffset(0.9);
    h->GetYaxis()->SetTitleOffset(1.2);
    h->GetXaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetLabelSize(0.04);
    h->GetXaxis()->SetLabelOffset(0.007);
    h->GetYaxis()->SetLabelOffset(0.007);
    h->Draw();
  };
  void Style(TGraphAsymmErrors* g, int c, int style){
    g->SetLineWidth(2);
    g->SetLineStyle(style);
    g->SetLineColor(c);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(c);
    g->SetMarkerSize(0.4);
    g->SetFillColor(c);
    g->SetFillStyle(3001);
    g->GetXaxis()->SetTitle("QCD efficiency");
    g->GetYaxis()->SetTitle("Signal efficiency");
  };
  void Style(TGraph* g, int c, int style){
    g->SetLineWidth(2);
    g->SetLineStyle(style);
    g->SetLineColor(c);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(c);
    g->SetMarkerSize(0.4);
    g->SetFillColor(c);
    g->SetFillStyle(3001);
    g->GetXaxis()->SetTitle("QCD efficiency");
    g->GetYaxis()->SetTitle("Signal efficiency");
  };



/////////////
};

#endif
