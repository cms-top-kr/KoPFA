#include "TH2F.h"
#include "TMath.h"
#include "TRandom3.h"
#include "THStack.h"
#include "style.h"

int initbtag  = 0;
double fraction = 0.01;
bool draw = true;
const int nbins = 11; 
const int channel = 3;
const int nt = 2;
const int ntotalbin = nbins*channel*nt;
bool combine = false;

double nttbb[ntotalbin];
double nttcc[ntotalbin];
double nttll[ntotalbin];
double nbakg[ntotalbin];
double ndbkg[ntotalbin];

double N_ttjj = 0;

double nbtag(double *x, double *par)
{
    int ntag = x[0];

    return  par[1]*N_ttjj*(par[0]*nttbb[ntag] + (1-par[0])*nttll[ntag]) + par[1]*nbakg[ntag] + ndbkg[ntag];

}

double Fit(TH1* data, TH1* ttbb, TH1* ttcc, TH1* ttll, TH1* bakg, TH1* dbkg, const TString & decayMode, const TString & path, const TString & balgo)
{

    cout << " ============ " << path << " ============ (" << decayMode << ") =================="  << endl;

    double kfract_initial = fraction;
    double kttjj_initial = 1.0;

    ttll->Add(ttcc);
    //data->Add(bakg,-1);
    //data->Add(dbkg,-1);

    TH1* hdata = (TH1*) data->Clone();
    TH1* httbb = (TH1*) ttbb->Clone();
    TH1* httcc = (TH1*) ttcc->Clone();
    TH1* httll = (TH1*) ttll->Clone();
    TH1* hbakg = (TH1*) bakg->Clone();
    TH1* hdbkg = (TH1*) dbkg->Clone();

    double N_data = hdata->Integral();
    double N_ttbb = httbb->Integral();
    double N_ttcc = httcc->Integral();
    double N_ttll = httll->Integral();

    N_ttjj = N_ttbb + N_ttll;
    //N_ttjj = N_ttbb + N_ttcc + N_ttll;
    double r = N_ttbb / N_ttjj;
    cout << "MC r= " << r << endl;
    //cout << "Total number of background subtracted data= " << N_data << " Total number of tt signal= " << N_ttjj << endl;

    httbb->Sumw2();
    httcc->Sumw2();
    httll->Sumw2();
    httll->Scale(1.0/N_ttll);
    httbb->Scale(1.0/N_ttbb);
    httcc->Scale(1.0/N_ttcc);

    int n = data->GetXaxis()->GetNbins();

    for(int i = 0 ; i < n; i++){
      nttbb[i] = httbb->GetBinContent(i+1);
      nttcc[i] = httcc->GetBinContent(i+1);
      nttll[i] = httll->GetBinContent(i+1);
      nbakg[i] = hbakg->GetBinContent(i+1);
      ndbkg[i] = hdbkg->GetBinContent(i+1);
    }

    TCanvas * c= new TCanvas(Form("c%s_%s",decayMode.Data(),path.Data()),Form("c%s_%s",decayMode.Data(),path.Data()),800,400);
    c->SetLogy();
    TF1 *ftot = new TF1("ftot", nbtag , 0, n, 2);
    ftot->SetParameter(0, r);
    //ftot->SetParameter(1, kfract_initial);
    ftot->SetParameter(1, kttjj_initial);
    ftot->SetParLimits(0, 0.0, 1.0 );
    //ftot->SetParLimits(1, 0.0, 1.0 );
    ftot->SetParLimits(1, kttjj_initial*0.5, kttjj_initial*1.5 );
    hdata->Fit("ftot","LN","", 0, n);

    double chi2 = ftot->GetChisquare();
    double ndf = ftot->GetNDF();
    double chi2ndf = chi2/ndf;
    cout << " ============ chi2= " << chi2 << " ndf= " << ndf << " chi2ndf= " << chi2ndf << " =================" << endl;

    double R = ftot->GetParameter(0);
    //double Rcc = ftot->GetParameter(1);
    double k = ftot->GetParameter(1);
    httbb->Scale( k*N_ttjj*R );
    //httcc->Scale( k*N_ttjj*Rcc );
    //httll->Scale( k*N_ttjj*(1 - R - Rcc) );
    httll->Scale( k*N_ttjj*(1 - R) );

    hbakg->Scale( k );
    hdata->Add(hbakg,-1.0);
    hdata->Add(hdbkg,-1.0);

    httbb->SetFillColor(kRed+3);
    //httcc->SetFillColor(kRed+1);
    httll->SetFillColor(kRed);

    //httcc->SetFillStyle(1001);
    httbb->SetFillStyle(1001);
    httll->SetFillStyle(1001);

    THStack * s = new THStack("tt","tt");
    s->Add(httbb);
    //s->Add(httcc);
    s->Add(httll);
    s->Draw("FHIST");
    s->GetYaxis()->SetTitle("Events");
    s->GetXaxis()->SetTitle("Secondary Vertex Mass (GeV)");
    s->SetTitle("");
    s->SetMaximum(4000);
    s->SetMinimum(1);

    hdata->SetMarkerSize(1);
    hdata->SetMarkerStyle(20);
    hdata->Draw("samee");
    hdata->SetTitle(Form("%s",decayMode.Data()));

    SetLabel(0.2, 0.82, 12000, 8);
    TLatex *label= new TLatex;
    //label->SetNDC();
    label->SetTextSize(0.05);
    label->DrawLatex(1.5,200,"#mu#mu");
    label->DrawLatex(nbins+1.5,200,"e#mu");
    label->DrawLatex(nbins*2+1.5,200,"ee");
    label->DrawLatex(nbins*3+1.5,200,"#mu#mu");
    label->DrawLatex(nbins*4+1.5,200,"e#mu");
    label->DrawLatex(nbins*5+1.5,200,"ee");

    TLine* line = new TLine(nbins-0.5,400, nbins-0.5, 0);
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    //line->Draw();
    TLine* line2 = new TLine(nbins*2-0.5,400, nbins*2-0.5, 0);
    line2->SetLineStyle(2);
    line2->SetLineWidth(2);
    //line2->Draw();

    TLegend *l = new TLegend(0.73,0.74,0.90,0.88);
    l->AddEntry(hdata,"Data","PL");
    l->AddEntry(httll,"t#bar{t} + cc/LF","F");
    //l->AddEntry(httcc,"t#bar{t} + cc","F");
    l->AddEntry(httbb,"t#bar{t} + bb","F");
    l->SetTextSize(0.04);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->Draw();

    if(draw){
      c->Print(Form("c_ttbb_fraction_%s_%s.eps",path.Data(),decayMode.Data(),balgo.Data()));
      //c->Print(Form("c_ttbb_fraction_%s_%s.C",path.Data(),decayMode.Data(),balgo.Data()));
    }  

    return R;
}

TH1F* getHist(TFile * f, const TString & path, const TString & name){

  TH1F * hout = new TH1F(Form("%s",name.Data()),Form("%s",name.Data()),nbins,0,nbins);

  TH1F * h1 = (TH1F*) f->Get(Form("%s1",path.Data()));
  TH1F * h2 = (TH1F*) f->Get(Form("%s2",path.Data()));

  for(int i=1 ; i <= nbins; i++){
    if( i < initbtag ) {
      hout->SetBinContent(i, 0);
    }else{
      double value = h1->GetBinContent(i) + h2->GetBinContent(i);
      hout->SetBinContent(i, value);
    }
  }

  double overflow = h1->GetBinContent(nbins+1) + h2->GetBinContent(nbins+1);
  if( combine) hout->AddBinContent(nbins, overflow);
  //cout << "overflow = " << overflow << endl;

  return hout;

}


TH1F* getHistBakg(TFile * f, const TString & name, const TString& balgo, bool datadriven = false){

  TH1F * hout = new TH1F(Form("%s",name.Data()),Form("%s",name.Data()),nbins,0.0,nbins);

  if( datadriven ){

    TH1F * h1_1 = (TH1F*) f->Get("Step_1/hMC_DYll_Step_1_"+balgo+"1");
    //no QCD yet
    //TH1F * h2_1 = (TH1F*) f->Get("Step_1/hDataBkg_QCD_Step_1_"+balgo+"1");
    //h1_1->Add(h2_1);

    TH1F * h1_2 = (TH1F*) f->Get("Step_1/hMC_DYll_Step_1_"+balgo+"2");
    //no QCD yet
    //TH1F * h2_2 = (TH1F*) f->Get("Step_1/hDataBkg_QCD_Step_1_"+balgo+"2");
    //h1_2->Add(h2_2);

  }else{
    TH1F * h1_1 = (TH1F*) f->Get("Step_1/hMC_TTbarOthers_Step_1_"+balgo+"1");
    TH1F * h2_1 = (TH1F*) f->Get("Step_1/hMC_Wl_Step_1_"+balgo+"1");
    TH1F * h3_1 = (TH1F*) f->Get("Step_1/hMC_VV_Step_1_"+balgo+"1");
    TH1F * h4_1 = (TH1F*) f->Get("Step_1/hMC_SingleTop_Step_1_"+balgo+"1");

    h1_1->Add(h2_1);
    h1_1->Add(h3_1);
    h1_1->Add(h4_1);

    TH1F * h1_2 = (TH1F*) f->Get("Step_1/hMC_TTbarOthers_Step_1_"+balgo+"2");
    TH1F * h2_2 = (TH1F*) f->Get("Step_1/hMC_Wl_Step_1_"+balgo+"2");
    TH1F * h3_2 = (TH1F*) f->Get("Step_1/hMC_VV_Step_1_"+balgo+"2");
    TH1F * h4_2 = (TH1F*) f->Get("Step_1/hMC_SingleTop_Step_1_"+balgo+"2");

    h1_2->Add(h2_2);
    h1_2->Add(h3_2);
    h1_2->Add(h4_2);
  }


  for(int i=1 ; i <= nbins; i++){
    if( i < initbtag ){
      hout->SetBinContent(i, 0);
    }else{
      double value = h1_1->GetBinContent(i) + h1_2->GetBinContent(i);
      hout->SetBinContent(i, value);
    }
  }

  double overflow = h1_1->GetBinContent(nbins+1) + h1_2->GetBinContent(nbins+1);
  if( combine ) hout->AddBinContent(nbins, overflow);
  //cout << "bkg overflow = " << overflow << endl;
  return hout;

}

double extractR(const TString & path, const TString & balgo){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TH1F * h_ttbb[3][nt];
  TH1F * h_ttcc[3][nt];
  TH1F * h_ttll[3][nt];
  TH1F * h_data[3][nt]; 
  TH1F * h_bakg[3][nt]; 
  TH1F * h_dbkg[3][nt]; 

  

  for(int i=0; i < 3 ; i++){
    for(int j=0; j < nt; j++){
      TString decay = "";
      if( i == 0 ) decay = "MuMu";
      if( i == 1 ) decay = "ElEl";
      if( i == 2 ) decay = "MuEl";
      TString ntag = "";
      if( j == 0 ) ntag = "tag2";
      if( j == 1 ) ntag = "tag3";

      TFile * f = new TFile( Form("%s_%s/%s/%s.root", path.Data(), ntag.Data(), decay.Data(), decay.Data()  ));

      h_ttbb[i][j] = getHist(f, "Step_1/hMCSig_TTbarbb_Step_1_"+balgo+"","hFit_ttbb"+balgo+"_"+decay+"_"+ntag);
      h_ttcc[i][j] = getHist(f, "Step_1/hMC_TTbarcc_Step_1_"+balgo+"","hFit_ttcc"+balgo+"_"+decay+"_"+ntag);
      h_ttll[i][j] = getHist(f, "Step_1/hMC_TTbarll_Step_1_"+balgo+"","hFit_ttll"+balgo+"_"+decay+"_"+ntag);
      h_data[i][j] = getHist(f, "Step_1/hData_Step_1_"+balgo+"","hFit_data"+balgo+"_"+decay+"_"+ntag);
      h_bakg[i][j] = getHistBakg(f,"hFit_bakg"+balgo+"_"+decay+"_"+ntag,balgo, false);
      h_dbkg[i][j] = getHistBakg(f,"hFit_dbkg"+balgo+"_"+decay+"_"+ntag,balgo, true);
    }
  }

  TH1F * h_data_all = new TH1F("hFit_data_"+balgo+"_all","hFit_data_"+balgo+"_all",nbins*6,0 ,nbins*6 );
  TH1F * h_ttll_all = new TH1F("hFit_ttll_"+balgo+"_all","hFit_ttll_"+balgo+"_all",nbins*6,0 ,nbins*6 );
  TH1F * h_ttbb_all = new TH1F("hFit_ttbb_"+balgo+"_all","hFit_ttbb_"+balgo+"_all",nbins*6,0 ,nbins*6 );
  TH1F * h_ttcc_all = new TH1F("hFit_ttcc_"+balgo+"_all","hFit_ttcc_"+balgo+"_all",nbins*6,0 ,nbins*6 );
  TH1F * h_bakg_all = new TH1F("hFit_bakg_"+balgo+"_all","hFit_bakg_"+balgo+"_all",nbins*6,0 ,nbins*6 );
  TH1F * h_dbkg_all = new TH1F("hFit_dbkg_"+balgo+"_all","hFit_dbkg_"+balgo+"_all",nbins*6,0 ,nbins*6 );

  for(int i=1 ; i <= ntotalbin; i++){

    int dec = 0;
    int tag = 0;
    if( i <= nbins*3) {
      tag = 0;
      if( i <= nbins ) dec = 0;
      if( i > nbins && i <= nbins*2 ) dec = 0;
      if( i > nbins*2 && i <= nbins*3 ) dec = 0;
    }else{
      tag = 1;
      if( i <= nbins ) dec = 0;
      if( i > nbins && i <= nbins*2 ) dec = 0;
      if( i > nbins*2 && i <= nbins*3 ) dec = 0;
    }   

    int nb = i%nbins;
    if( !nb ) nb = nbins; 

    //nb = nb + 1;

    double nda = h_data[dec][tag]->GetBinContent(nb);
    double nll = h_ttll[dec][tag]->GetBinContent(nb);
    double nbb = h_ttbb[dec][tag]->GetBinContent(nb);
    double ncc = h_ttcc[dec][tag]->GetBinContent(nb);
    double nbk = h_bakg[dec][tag]->GetBinContent(nb);
    double ndb = h_dbkg[dec][tag]->GetBinContent(nb);
    //cout << "bin = " << i << " nda= " << nda << " nll= " << nll << " nbb= " << nbb << " ncc= " << ncc << " nbk= " << nbk << " ndb= " << ndb << endl;

    double ln = (nb-2)*0.5;

    //need to be fixed
    h_data_all->GetXaxis()->SetBinLabel(i, Form("%1.2f",ln) );
    h_ttll_all->GetXaxis()->SetBinLabel(i, Form("%1.2f",ln) );
    h_ttbb_all->GetXaxis()->SetBinLabel(i, Form("%1.2f",ln) );
    h_ttcc_all->GetXaxis()->SetBinLabel(i, Form("%1.2f",ln) );
    h_bakg_all->GetXaxis()->SetBinLabel(i, Form("%1.2f",ln) );
    h_dbkg_all->GetXaxis()->SetBinLabel(i, Form("%1.2f",ln) );
    h_data_all->SetBinContent(i,nda);
    h_ttll_all->SetBinContent(i,nll);
    h_ttbb_all->SetBinContent(i,nbb);
    h_ttcc_all->SetBinContent(i,ncc);
    h_bakg_all->SetBinContent(i,nbk);
    h_dbkg_all->SetBinContent(i,ndb);

  }

  double R = Fit( h_data_all, h_ttbb_all, h_ttcc_all,  h_ttll_all, h_bakg_all, h_dbkg_all, "Combined", path, balgo);
  //Fit( h_data_MuMu, h_ttbb_MuMu, h_ttcc_MuMu, h_ttll_MuMu, h_bakg_MuMu, h_dbkg_MuMu, "MuMu", path, balgo);
  //Fit( h_data_MuEl, h_ttbb_MuEl, h_ttcc_MuEl, h_ttll_MuEl, h_bakg_MuEl, h_dbkg_MuEl, "MuEl", path, balgo);
  //Fit( h_data_ElEl, h_ttbb_ElEl, h_ttcc_ElEl, h_ttll_ElEl, h_bakg_ElEl, h_dbkg_ElEl, "ElEl", path, balgo);

  return R;
}


void extractRSec(){
  double R = extractR("TTBB_15Dec2012_CSVM","secM");
  double Rdwlight = extractR("TTBB_15Dec2012_CSVMdwlight","secM");
  double Ruplight = extractR("TTBB_15Dec2012_CSVMuplight","secM");
}
