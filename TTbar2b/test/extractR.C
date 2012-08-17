#include "TH2F.h"
#include "TMath.h"
#include "TRandom3.h"
#include "THStack.h"
#include "style.h"

int initbtag  = 0;
double fraction = 0.01;
bool draw = true;
const int nbins = 5;
bool combine = false;

double nttbb[nbins*3];
double nttcc[nbins*3];
double nttll[nbins*3];
double nbakg[nbins*3];
double ndbkg[nbins*3];

double N_ttjj = 0;

double nbtag(double *x, double *par)
{
    int ntag = x[0];

    return  par[1]*N_ttjj*(par[0]*nttbb[ntag] + (1-par[0])*nttll[ntag]) + par[1]*nbakg[ntag] + ndbkg[ntag];
    //return  par[1]*N_ttjj*(par[0]*nttbb[ntag] + (1-par[0])*nttll[ntag]);
    //return  par[2]*N_ttjj*(par[0]*nttbb[ntag] + par[1]*nttcc[ntag] + (1-par[0]-par[1])*nttll[ntag]);

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

    TCanvas * c= new TCanvas(Form("c%s_%s",decayMode.Data(),path.Data()),Form("c%s_%s",decayMode.Data(),path.Data()),1);
    c->SetLogy();
    TF1 *ftot = new TF1("ftot", nbtag , 0, n, 2);
    ftot->SetParameter(0, r);
    //ftot->SetParameter(1, kfract_initial);
    ftot->SetParameter(1, kttjj_initial);
    ftot->SetParLimits(0, 0.0, 1.0 );
    //ftot->SetParLimits(1, 0.0, 1.0 );
    ftot->SetParLimits(1, kttjj_initial*0.5, kttjj_initial*1.5 );
    hdata->Fit("ftot","LN","",0,n);

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

    httbb->SetFillColor(kRed+2);
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
    s->GetXaxis()->SetTitle("b-Jet Multiplicity ("+balgo+")");
    s->SetTitle("");
    s->SetMaximum(4000);
    s->SetMinimum(1);

    hdata->SetMarkerSize(1);
    hdata->SetMarkerStyle(20);
    hdata->Draw("samee");
    hdata->SetTitle(Form("%s",decayMode.Data()));

    SetLabel(0.2, 0.82, 4982);
    TLatex *label= new TLatex;
    //label->SetNDC();
    label->SetTextSize(0.05);
    label->DrawLatex(0.1,200,"#mu#mu");
    label->DrawLatex(nbins+0.1,200,"e#mu");
    label->DrawLatex(nbins*2+0.1,200,"ee");


    TLine* line = new TLine(nbins-0.5,400, nbins-0.5, 0);
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    line->Draw();
    TLine* line2 = new TLine(nbins*2-0.5,400, nbins*2-0.5, 0);
    line2->SetLineStyle(2);
    line2->SetLineWidth(2);
    line2->Draw();

    TLegend *l = new TLegend(0.75,0.74,0.92,0.88);
    l->AddEntry(hdata,"Data","PL");
    l->AddEntry(httll,"t#bar{t} + ll/cc","F");
    //l->AddEntry(httcc,"t#bar{t} + cc","F");
    l->AddEntry(httbb,"t#bar{t} + bb","F");
    l->SetTextSize(0.04);
    l->SetFillColor(0);
    l->SetLineColor(0);
    l->Draw();

    if(draw){
      c->Print(Form("%s/c_ttbb_fraction_%s_%s.eps",path.Data(),decayMode.Data(),balgo.Data()));
    }  

    return R;
}

TH1F* getHist(TFile * f, const TString & path, const TString & name){

  TH1F * hout = new TH1F(Form("%s",name.Data()),Form("%s",name.Data()),nbins,-0.5,nbins - 0.5);

  TH1F * h = (TH1F*) f->Get(Form("%s",path.Data()));

  for(int i=1 ; i <= nbins; i++){
    if( i < initbtag ) {
      hout->SetBinContent(i, 0);
    }else{
      double value = h->GetBinContent(i);
      hout->SetBinContent(i, value);
    }
  }

  double overflow = h->GetBinContent(nbins+1);
  if( combine) hout->AddBinContent(nbins, overflow);
  //cout << "overflow = " << overflow << endl;

  return hout;

}


TH1F* getHistBakg(TFile * f, const TString & name, const TString& balgo){

  TH1F * hout = new TH1F(Form("%s",name.Data()),Form("%s",name.Data()),nbins,-0.5,nbins - 0.5);

  TH1F * h1 = (TH1F*) f->Get("Step_5/hMC_TTbarOthers_Step_5_nbJet30_"+balgo);
  TH1F * h2 = (TH1F*) f->Get("Step_5/hMC_TTbarNonvis_Step_5_nbJet30_"+balgo);
  TH1F * h3 = (TH1F*) f->Get("Step_5/hMC_Wl_Step_5_nbJet30_"+balgo);
  TH1F * h4 = (TH1F*) f->Get("Step_5/hMC_VV_Step_5_nbJet30_"+balgo);
  TH1F * h5 = (TH1F*) f->Get("Step_5/hMC_SingleTop_Step_5_nbJet30_"+balgo);
  TH1F * h6 = (TH1F*) f->Get("Step_5/hMC_DYtt_Step_5_nbJet30_"+balgo);

  h1->Add(h2);
  h1->Add(h3);
  h1->Add(h4);
  h1->Add(h5);
  h1->Add(h6);

  for(int i=1 ; i <= nbins; i++){
    if( i < initbtag ){
      hout->SetBinContent(i, 0);
    }else{
      double value = h1->GetBinContent(i);
      hout->SetBinContent(i, value);
    }
  }

  double overflow = h1->GetBinContent(nbins+1);
  if( combine ) hout->AddBinContent(nbins, overflow);
  //cout << "bkg overflow = " << overflow << endl;
  return hout;

}

TH1F* getHistDbkg(TFile * f, const TString & name, const TString& balgo){

  TH1F * hout = new TH1F(Form("%s",name.Data()),Form("%s",name.Data()),nbins,-0.5,nbins - 0.5);

  TH1F * h7 = (TH1F*) f->Get("Step_5/hMC_DYll_Step_5_nbJet30_"+balgo);
  TH1F * h8 = (TH1F*) f->Get("Step_5/hDataBkg_QCD_Step_5_nbJet30_"+balgo);
  TH1F * h3 = (TH1F*) f->Get("Step_5/hMC_Wl_Step_5_nbJet30_"+balgo);
  TH1F * h4 = (TH1F*) f->Get("Step_5/hMC_VV_Step_5_nbJet30_"+balgo);
  TH1F * h5 = (TH1F*) f->Get("Step_5/hMC_SingleTop_Step_5_nbJet30_"+balgo);
  TH1F * h6 = (TH1F*) f->Get("Step_5/hMC_DYtt_Step_5_nbJet30_"+balgo);


  h7->Add(h8);
  //h7->Add(h3);
  //h7->Add(h4);
  //h7->Add(h5);
  //h7->Add(h6);

  for(int i=1 ; i <= nbins; i++){
    if( i < initbtag ) {
      hout->SetBinContent(i,0);
    }else{
      double value = h7->GetBinContent(i);
      hout->SetBinContent(i, value);
    }
  }

  double overflow = h7->GetBinContent(nbins+1);
  if( combine) hout->AddBinContent(nbins, overflow);
  //cout << "data bkg overflow = " << overflow << endl;
  return hout;

}


double extractR(const TString & path, const TString & balgo){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TFile * f_MuMu = new TFile(path+"/MuMu/MuMu.root");
  TFile * f_MuEl = new TFile(path+"/MuEl/MuEl.root");
  TFile * f_ElEl = new TFile(path+"/ElEl/ElEl.root");

  TH1F * h_ttbb_MuMu = getHist(f_MuMu, "Step_5/hMCSig_TTbarbb_Step_5_nbJet30_"+balgo+"","hFit_ttbb_"+balgo+"_MuMu");
  TH1F * h_ttcc_MuMu = getHist(f_MuMu, "Step_5/hMC_TTbarcc_Step_5_nbJet30_"+balgo+"","hFit_ttcc_"+balgo+"_MuMu");
  TH1F * h_ttll_MuMu = getHist(f_MuMu, "Step_5/hMC_TTbarll_Step_5_nbJet30_"+balgo+"","hFit_ttll"+balgo+"MuMu");
  TH1F * h_data_MuMu = getHist(f_MuMu, "Step_5/hData_Step_5_nbJet30_"+balgo+"","hFit_data"+balgo+"MuMu");
  TH1F * h_bakg_MuMu = getHistBakg(f_MuMu,"hFit_bakg"+balgo+"MuMu",balgo);
  TH1F * h_dbkg_MuMu = getHistDbkg(f_MuMu,"hFit_dbkg"+balgo+"MuMu",balgo);

  TH1F * h_ttbb_MuEl = getHist(f_MuEl, "Step_5/hMCSig_TTbarbb_Step_5_nbJet30_"+balgo+"","hFit_ttbb"+balgo+"MuEl");
  TH1F * h_ttcc_MuEl = getHist(f_MuEl, "Step_5/hMC_TTbarcc_Step_5_nbJet30_"+balgo+"","hFit_ttcc"+balgo+"MuEl");
  TH1F * h_ttll_MuEl = getHist(f_MuEl, "Step_5/hMC_TTbarll_Step_5_nbJet30_"+balgo+"","hFit_ttll"+balgo+"MuEl");
  TH1F * h_data_MuEl = getHist(f_MuEl, "Step_5/hData_Step_5_nbJet30_"+balgo+"","hFit_data"+balgo+"MuEl");
  TH1F * h_bakg_MuEl = getHistBakg(f_MuEl,"hFit_bakg"+balgo+"MuEl",balgo);
  TH1F * h_dbkg_MuEl = getHistDbkg(f_MuEl,"hFit_dbkg"+balgo+"MuEl",balgo);

  TH1F * h_ttbb_ElEl = getHist(f_ElEl, "Step_5/hMCSig_TTbarbb_Step_5_nbJet30_"+balgo+"","hFit_ttbb"+balgo+"ElEl");
  TH1F * h_ttcc_ElEl = getHist(f_ElEl, "Step_5/hMC_TTbarcc_Step_5_nbJet30_"+balgo+"","hFit_ttcc"+balgo+"ElEl");
  TH1F * h_ttll_ElEl = getHist(f_ElEl, "Step_5/hMC_TTbarll_Step_5_nbJet30_"+balgo+"","hFit_ttll"+balgo+"ElEl");
  TH1F * h_data_ElEl = getHist(f_ElEl, "Step_5/hData_Step_5_nbJet30_"+balgo+"","hFit_data"+balgo+"ElEl");
  TH1F * h_bakg_ElEl = getHistBakg(f_ElEl,"hFit_bakg"+balgo+"ElEl",balgo);
  TH1F * h_dbkg_ElEl = getHistDbkg(f_ElEl,"hFit_dbkg"+balgo+"ElEl",balgo);

  TH1F * h_data_all = new TH1F("hFit_data_"+balgo+"_all","hFit_data_"+balgo+"_all",nbins*3,-0.5,nbins*3 - 0.5);
  TH1F * h_ttll_all = new TH1F("hFit_ttll_"+balgo+"_all","hFit_ttll_"+balgo+"_all",nbins*3,-0.5,nbins*3 - 0.5);
  TH1F * h_ttbb_all = new TH1F("hFit_ttbb_"+balgo+"_all","hFit_ttbb_"+balgo+"_all",nbins*3,-0.5,nbins*3 - 0.5);
  TH1F * h_ttcc_all = new TH1F("hFit_ttcc_"+balgo+"_all","hFit_ttcc_"+balgo+"_all",nbins*3,-0.5,nbins*3 - 0.5);
  TH1F * h_bakg_all = new TH1F("hFit_bakg_"+balgo+"_all","hFit_bakg_"+balgo+"_all",nbins*3,-0.5,nbins*3 - 0.5);
  TH1F * h_dbkg_all = new TH1F("hFit_dbkg_"+balgo+"_all","hFit_dbkg_"+balgo+"_all",nbins*3,-0.5,nbins*3 - 0.5);

  for(int i=1 ; i <= nbins*3; i++){

    double nda = 0;
    double nll = 0;
    double nbb = 0;
    double ncc = 0;
    double nbk = 0;
    double ndb = 0;
    int tag = 0;
    if( i >= 1 && i <= nbins ){
      nda = h_data_MuMu->GetBinContent(i);
      nll = h_ttll_MuMu->GetBinContent(i);
      nbb = h_ttbb_MuMu->GetBinContent(i);
      ncc = h_ttcc_MuMu->GetBinContent(i);
      nbk = h_bakg_MuMu->GetBinContent(i);
      ndb = h_dbkg_MuMu->GetBinContent(i);
      tag = i - 1  ;
    }else if( i > nbins && i<= nbins*2){
      nda = h_data_MuEl->GetBinContent(i-nbins);
      nll = h_ttll_MuEl->GetBinContent(i-nbins);
      nbb = h_ttbb_MuEl->GetBinContent(i-nbins);
      ncc = h_ttcc_MuEl->GetBinContent(i-nbins);
      nbk = h_bakg_MuEl->GetBinContent(i-nbins);
      ndb = h_dbkg_MuEl->GetBinContent(i-nbins);
      tag = i - (1 + nbins) ;
    }else if( i > nbins*2){
      nda = h_data_ElEl->GetBinContent(i-nbins*2);
      nll = h_ttll_ElEl->GetBinContent(i-nbins*2);
      nbb = h_ttbb_ElEl->GetBinContent(i-nbins*2);
      ncc = h_ttcc_ElEl->GetBinContent(i-nbins*2);
      nbk = h_bakg_ElEl->GetBinContent(i-nbins*2);
      ndb = h_dbkg_ElEl->GetBinContent(i-nbins*2);
      tag = i - (1 + nbins*2) ;
    }
    //cout << "bin = " << i << " nda= " << nda << " nll= " << nll << " nbb= " << nbb << " ncc= " << ncc << " nbk= " << nbk << " ndb= " << ndb << endl;
    h_data_all->GetXaxis()->SetBinLabel(i, Form("%i",tag) );
    h_ttll_all->GetXaxis()->SetBinLabel(i, Form("%i",tag) );
    h_ttbb_all->GetXaxis()->SetBinLabel(i, Form("%i",tag) );
    h_ttcc_all->GetXaxis()->SetBinLabel(i, Form("%i",tag) );
    h_bakg_all->GetXaxis()->SetBinLabel(i, Form("%i",tag) );
    h_dbkg_all->GetXaxis()->SetBinLabel(i, Form("%i",tag) );
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


void extractR(){
  double R = extractR("TTBB_12072018_CSVM_jet30GeV_Tau_2tag_SF","CSVM");
  //double Rdwlight = extractR("TTBB_12072018_CSVMdwlight_jet30GeV_Tau_2tag_SF","CSVM");
  //double Ruplight = extractR("TTBB_12072018_CSVMuplight_jet30GeV_Tau_2tag_SF","CSVM");
  //extractR("TTBB_12072018_CSVTdw_jet30GeV_Tau_2tag_SF","CSVT");
  //extractR("TTBB_12072018_CSVTup_jet30GeV_Tau_2tag_SF","CSVT"); 
  //double dwlight = (Rdwlight-R)/R;
  //double uplight = (Ruplight-R)/R;
  //cout << "dwlight = " << dwlight << endl;
  //cout << "uplight = " << uplight << endl;
}
