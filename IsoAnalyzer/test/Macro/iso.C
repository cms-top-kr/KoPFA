#include "style.h"
#include <vector>
using namespace std;
//reco::IsoDeposit::Vetos dVetos;
TString typeCh;
TString typeNh;
TString typePh;

bool printplot =false;

TString obj1 = "muon";
TString obj2 = "random";
TString leg1 = obj1+" in data";
TString leg2 = obj2+" in data";

//TString dir = "Random400DataVsMuonWmunuWith0MeVForCH";
TString dir = "test";
//Chain * tree3 = new Chain("MuonIso/tree", "/tmp/tjkim/PFA/July5/Wmunu/isoNtuple_*.root");

void iso(){
  //Chain * tree1 = new Chain("MuonIso/tree", "/tmp/tjkim/isolation/Wjets/isoNtuple_*.root");
  //Chain * tree2 = new Chain("MuonIso/tree", "/tmp/tjkim/isolation/WjetsPU/isoNtuple_*.root");

  //Chain * tree1 = new Chain("RandomIsoForElec/tree", "data/elec/isoNtuple_50GeV_PV1.root");
  //Chain * tree2 = new Chain("RandomIsoForElec/tree", "data/elec/isoNtuple_PV1.root");
  //Chain * tree1 = new Chain("RandomIsoForElec/tree", "/tmp/tjkim/PFA/July2/Wenu/isoNtuple_1.root");
  //Chain * tree2 = new Chain("ElecIso/tree", "/tmp/tjkim/PFA/July2/Wenu/isoNtuple_*.root");

  //Chain * tree1 = new Chain("RandomIsoForMuon/tree", "data/muon/latest/isoNtuple.root");
  //Chain * tree1 = new Chain("RandomIsoForMuon/tree", "data/muon/full_v2/isoNtuple_PV1.root");
  //Chain * tree1 = new Chain("RandomIsoForMuon/tree", "/tmp/tjkim/PFA/July5/SDIso_old_PV1/isoNtuple_*.root");
  //Chain * tree1 = new Chain("MuonIso/tree", "data/muon/full_v2/isoNtuple_*.root");
  //Chain * tree1 = new Chain("RandomIsoForMuon/tree", "/tmp/tjkim/PFA/July2/Wmunu/isoNtuple_0.root");
  //Chain * tree2 = new Chain("MuonIso/tree", "/tmp/tjkim/PFA/July5/Wmunu_Summer10/isoNtuple_*.root");
  //Chain * tree2 = new Chain("MuonIso/tree", "/tmp/tjkim/PFA/July5/Wmunu/isoNtuple_*.root");
  //Chain * tree1 = new Chain("MuonIso/tree", "/tmp/tjkim/PFA/July15/SDIso/isoNtuple_*.root");
  //Chain * tree1 = new Chain("MuonIso/tree", "rfio:/castor/cern.ch/user/t/tjkim/pfa/source/July15/SDIso/isoNtuple_*.root");
  //Chain * tree2 = new Chain("RandomIsoForMuon/tree", "/tmp/tjkim/PFA/July15/SDIso/isoNtuple_*.root");
  //Chain * tree2 = new Chain("RandomIsoForMuon/tree", "rfio:/castor/cern.ch/user/t/tjkim/pfa/source/July15/SDIso/isoNtuple_*.root");
  TChain * tree1 = new TChain("MuonIso/tree");
  TChain * tree2 = new TChain("RandomIsoForMuon/tree");
  tree1->Add("rfio:/castor/cern.ch/user/t/tjkim/pfa/source/July15/SDIso/isoNtuple_*.root");
  tree2->Add("rfio:/castor/cern.ch/user/t/tjkim/pfa/source/July15/SDIso/isoNtuple_*.root");


  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();


  //TCut cutjet = "random_ch_jetpT > 8";
  TCut cut1 = "abs(eta) < 2.1"; 
  TCut cut2 = "abs(eta) < 2.1";
 
  TCut cutRD4; 
  TCut cutRD5; 
  TCut cutRD6; 
  TCut cutMC4;
  TCut cutMC5;
  TCut cutMC6;

  //muon : chIso0, nhIso, phIso3 
  //elec : chIso2, nhIso2, phIso5
  if(obj2.Contains("muon") || obj1.Contains("muon")){
    cout<<"MUON"<<endl;
    typeCh = "chIso";
    typeNh = "nhIso";
    typePh = "phIso";
    cutRD4 = "ch_th > 0.0";
    cutRD5 = "nh_th > 0.5";
    cutRD6 = "ph_th > 0.5 && !( abs(ph_deta) < 0.1 && abs(ph_dphi) < 0.2 )";
    cutMC4 = cutRD4;
    cutMC5 = cutRD5;
    cutMC6 = cutRD6;
  }else if(obj2.Contains("elec") || obj1.Contains("elec")){
    cout <<"ELEC" <<endl;
    typeCh = "chIso";
    typeNh = "nhIso";
    typePh = "phIso";
    cutRD4 = "ch_th > 0.0";
    cutRD5 = "nh_th > 0.5 && nh_dR > 0.1";
    cutRD6 = "ph_th > 0.5 && !(fabs(ph_deta) < 0.025 && fabs(ph_dphi) < 3.14 )";
    cutMC4 = cutRD4;
    cutMC5 = cutRD5;
    cutMC6=  cutRD6;
  }else{
    cout<<"ERROR"<<endl;
  }
  

  cout << "number of events in tree1 = " << tree1->GetEntries() << endl;
  cout << "number of events in tree2 = " << tree2->GetEntries() << endl;
  cout << "number of events after cut1 = " << tree1->GetEntries(cut1) << endl;
  cout << "number of events after cut2 = " << tree2->GetEntries(cut2) << endl;

  double p1 = 0;
  double p2 = 0;
  TH1 *h_1= new TH1F("h_1_eta","h_2_eta",60,-3,3);
  TH1 *h_2= new TH1F("h_2_eta","h_2_eta",60,-3,3);
  tree1->Project("h_1_eta","eta",cut1);
  tree2->Project("h_2_eta","eta",cut2);
  p1 = h_1->GetEntries();
  p2 = h_2->GetEntries();
  //p1 = tree1->GetEntries()*400;
  //p2 = tree2->GetEntries();
  h_1->Delete();
  h_2->Delete();
  cout << "pivotal 1= " << p1 << endl;
  cout << "pivotal 2= " << p2 << endl;

  vector<string> hNameSumpT;
  hNameSumpT.push_back("charged_deposit_4");
  hNameSumpT.push_back("neutral_deposit_4");
  hNameSumpT.push_back("photon_deposit_4");
  vector<string> hNamedNdR;
  hNamedNdR.push_back("charged_deltaR");
  hNamedNdR.push_back("neutral_deltaR");
  hNamedNdR.push_back("photon_deltaR");

  vector<string> titleSumpT;
  titleSumpT.push_back("Charged hadron #Sigma p_{T} [GeV/c]");
  titleSumpT.push_back("Neutral hadron #Sigma p_{T} [GeV/c]");
  titleSumpT.push_back("Photon #Sigma p_{T} [GeV]");
  vector<string> titledNdR;
  titledNdR.push_back("Charged hadron dN/dR");
  titledNdR.push_back("Neutral hadron dN/dR");
  titledNdR.push_back("Photon dN/dR");

  float bins[] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0 ,1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6 ,3.8, 4.0};
  float bins2[] = {0.0,0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.22, 0.24, 0.26, 0.28, 0.3, 0.32, 0.34, 0.36, 0.38, 0.4};

  int Nbin = sizeof(bins)/sizeof(float) - 1;
  int Nbin2 = sizeof(bins2)/sizeof(float) - 1;

  plotCH(tree1, tree2, "CH" , "GeV", "Entries", "pt", printplot);

  //plotSumpT(tree1, tree2, "chIso", "chIso", hNameSumpT[0], titleSumpT[0], "Probability", 40, 0, 4, cut1, cut2, "CH", p1, p2, printplot);
  //plotSumpT(tree1, tree2, "nhIso", "nhIso", hNameSumpT[1], titleSumpT[1], "Probability", 40, 0, 4, cut1, cut2, "NH", p1, p2, printplot);
  //plotSumpT(tree1, tree2, "phIso", "phIso", hNameSumpT[2], titleSumpT[2], "Probability", 40, 0, 4, cut1, cut2, "PH", p1, p2, printplot);

  plotSumpT(tree1, tree2, "chIso", "chIso", hNameSumpT[0], titleSumpT[0], "Probability", Nbin, bins, cut1, cut2, "CH", p1, p2, printplot);
  plotSumpT(tree1, tree2, "nhIso", "nhIso", hNameSumpT[1], titleSumpT[1], "Probability", Nbin, bins, cut1, cut2, "NH", p1, p2, printplot);
  plotSumpT(tree1, tree2, "phIso", "phIso", hNameSumpT[2], titleSumpT[2], "Probability", Nbin, bins, cut1, cut2, "PH", p1, p2, printplot);

  //plotdNdR(tree1, tree2, "ch_dR", "ch_dR", hNamedNdR[0], "R", titledNdR[0], 40, 0, 0.4, cutRD4, cutMC4, "pre", p1, p2, printplot);
  //plotdNdR(tree1, tree2, "nh_dR", "nh_dR", hNamedNdR[1], "R", titledNdR[1], 40, 0, 0.4, cutRD5, cutMC5, "pre", p1, p2, printplot);
  //plotdNdR(tree1, tree2, "ph_dR", "ph_dR", hNamedNdR[2], "R", titledNdR[2], 40, 0, 0.4, cutRD6, cutMC6, "pre", p1, p2, printplot);

 // plotAbsCombined( tree1, tree2, Nbin, bins, cut1, cut2, p1, p2,printplot);
 // plotRelCombined( tree1, tree2, Nbin2, bins2, cut1, cut2, p1, p2,printplot);
}

plotCH(TChain* tree1, TChain* tree2, const TString& hName, const TString& xtitle,  const TString& ytitle,const TString& name, bool print){

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",50,0,5);
  TH1 *h_2 = new TH1D(Form("h_2_%s_%s",hName.Data(),name.Data()),"h",50,0,5);
  h_1->Sumw2();
  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);
 
  tree2->Draw(Form("chargedhadron_pt>>h_2_%s_%s",hName.Data(),name.Data()),"","");
  tree1->Draw(Form("chargedhadron_pt>>h_1_%s_%s",hName.Data(),name.Data()),"","psame");

  h_1->Scale(1.0/tree1->GetEntries());
  h_2->Scale(1.0/tree2->GetEntries());

  h_1->SetMaximum(11);
  h_2->SetMaximum(11);

  Style(h_1, h_2, xtitle, ytitle);

  SetLatex(0.25,0.88);
  SetLegend(h_1, h_2, "Data", "MC", "p", "l", 0.60,0.65,0.85,0.80);
  Print(c, dir, hName, name, print);

}

//void plotSumpT(TChain *tree1, TChain *tree2, const TString &var1, const TString &var2, const TString& hName, const TString& xtitle,  const TString& ytitle, int nbin, double xlow, double xmax,  TCut cut1, TCut cut2, const TString& name, double& p1, double& p2, bool print){
void plotSumpT(TChain *tree1, TChain *tree2, const TString &var1, const TString &var2, const TString& hName, const TString& xtitle,  const TString& ytitle, int& nbin, const float* bins,  TCut cut1, TCut cut2, const TString& name, double& p1, double& p2, bool print){

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",nbin,bins);
  TH1 *h_2 = new TH1D(Form("h_2_%s_%s",hName.Data(),name.Data()),"h",nbin,bins);
  h_1->Sumw2();
  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1); 
  gPad->SetLogy();

  tree2->Draw(Form("%s>>h_2_%s_%s",var2.Data(),hName.Data(),name.Data()),cut2,"");
  tree1->Draw(Form("%s>>h_1_%s_%s",var1.Data(),hName.Data(),name.Data()),cut1,"psame");

  h_2->SetMaximum(1.2);
  h_2->SetMinimum(0.0001);

  h_1->Scale(1.0/p1);
  h_2->Scale(1.0/p2);

  Style(h_1, h_2, xtitle, ytitle);

  SetLatex(0.20,0.88);

  SetLegend(h_1, h_2, leg1, leg2, "p", "l", 0.45,0.65,0.70,0.80);
  Print(c, dir, hName, name, print);
  
  plotEff(h_1,h_2, hName,name, xtitle, nbin, bins,p1,p2, print);

}

void plotdNdR(TChain *tree_data, TChain *tree_mc, const TString &varRD, const TString &varMC, const TString& hName, const TString& xtitle, const TString& ytitle, int nbin, float xlow, float xmax, TCut cutRD, TCut cutMC, TString name, double &p1, double &p2, bool print){

  TH1 *h_data = new TH1D(Form("h_data_%s_%s",hName.Data(),name.Data()),"h_data",nbin,xlow,xmax);
  TH1 *h_mc = new TH1D(Form("h_mc_%s_%s",hName.Data(),name.Data()),"h_mc",nbin,xlow,xmax);
  h_data->Sumw2();
  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(),name.Data()),Form("c_%s_%s",hName.Data(),name.Data()),1);

  tree_mc->Draw(Form("%s>>h_mc_%s_%s",varMC.Data(),hName.Data(),name.Data()),cutMC,"");
  tree_data->Draw(Form("%s>>h_data_%s_%s",varRD.Data(),hName.Data(),name.Data()),cutRD,"Esame");

  h_data->Scale(1.0/p1/h_data->GetBinWidth(1));
  h_mc->Scale(1.0/p2/h_mc->GetBinWidth(1));
  h_mc->SetMaximum(7); // 2.5

  Style(h_data, h_mc, xtitle, ytitle);

  SetLatex2(0.20,0.88);
  SetLegend(h_data, h_mc, leg1, leg2, "p", "F", 0.20,0.67,0.45,0.82); 
  Print(c, dir, hName, name, print);
}

void plotAbsCombined(TChain *tree1, TChain *tree2, int& nbin, const float* bins, TCut cut1, TCut cut2, double& p1, double& p2, bool print){
  //int nbin = 40;
  //double xlow = 0.0;
 // double xmax = 4;
  TH1 *h_abs_1 = new TH1F("h_abs_1","h_abs_1",nbin,bins);
  TH1 *h_abs_2 = new TH1F("h_abs_2","h_abs_2",nbin,bins);
  h_abs_1->Sumw2();
  tree2->Project("h_abs_2","chIso+nhIso+phIso");   
  tree1->Project("h_abs_1","chIso+nhIso+phIso");   
  h_abs_1->Scale(1.0/p1);
  h_abs_2->Scale(1.0/p2);
  TCanvas *c = new TCanvas("c_abs_combined_sumpT","c_abs_combined_sumpT",1);
  c->SetLogy();
  h_abs_2->Draw();
  h_abs_1->Draw("same");
  Style(h_abs_1, h_abs_2, "#Sigma pT", "Probability");

  SetLatex(0.20,0.88);
  SetLegend(h_abs_1, h_abs_2, leg1, leg2, "p", "l", 0.45,0.65,0.70,0.80);
  Print(c, dir, "absolute_combined", "sumpT", print);

  plotEff(h_abs_1,h_abs_2, "abs", "combined", "#Sigma pT", nbin, bins, p1, p2, print);

  
}
void plotRelCombined(TChain *tree1, TChain *tree2, int& nbin, const float* bins, TCut cut1, TCut cut2, double& p1, double& p2, bool print){
  
  TH1 *h_pt = new TH1F("h_pt","h_pt",100,0,100);
  tree2->Project("h_pt","pt",cut2);
  h_pt->Scale(1.0/p2);

  //TCanvas *c = new TCanvas("c_ptDep","c_ptDep",1); 
 // int nbin = 50;
 // double xlow = 0.0;
 // double xmax = 0.5;

  TH1 *h_temp = new TH1F("h_temp","h_temp",nbin,bins);
  //h_temp->Draw();
  h_temp->SetStats(0);
  h_temp->SetTitle(0);

  TH1 *h[10];
  TH1 *h_muon = new TH1F("h_muon","h_muon",nbin,bins);
  TH1 *h_final = new TH1F("h_final","h_final",nbin,bins);
  h_final->Sumw2();
  tree2->Project("h_muon","(chIso+nhIso+phIso)/pt",cut2);  
  if(!obj1.Contains("random")){
    tree1->Project("h_final","(chIso+nhIso+phIso)/pt",cut1);
  }else( obj1.Contains("random")){
    cout << "Relative random sumpT calculation..." << endl;
    int i = 0;
    while( i < 10){ 
      TString s = int2string(i);
      h[i] = new TH1F(Form("h_%s",s.Data()),Form("h_%s",s.Data()),nbin,bins);
      h[i]->Sumw2();
      std::ostringstream cut;
      cut.str(std::string());
      int ptwidth = 10;
      float Pt = ptwidth/2 + i*ptwidth;
      tree1->Project(Form("h_%s",s.Data()),Form("(chIso+nhIso+phIso)/%f",Pt),cut1); 
      //cout << cut.str() << ":" << " entries = " << h[i]->GetEntries() << endl;
      h[i]->SetLineColor(i+1);
      h[i]->SetLineWidth(3);
      h[i]->Scale(1.0/p1);
      double pdf = h_pt->Integral(i*ptwidth+1,i*ptwidth+ptwidth) ;
      double scaledentries = h[i]->GetEntries()*h_pt->Integral(i*ptwidth+1,i*ptwidth+ptwidth) ;
      //h[i]->Draw("same");
      h_final->Add(h[i],scaledentries);
      //cout << "h_final= " << h_final->GetEntries() << endl;
      i++;
    }
  }

  TCanvas *c2 = new TCanvas("c_rel_combined_sumpT","c_rel_combined_sumpT",1);
  c2->SetLogy();
  h_muon->Draw();
  h_final->Draw("same");
  //cout << "combined / pt= " << h_final->GetEntries() << endl;
  h_final->Scale(1.0/p1);
  h_muon->Scale(1.0/p2);

  Style(h_final, h_muon, "#Sigma pT/pT", "Probability");
  SetLatex(0.20,0.88);
  SetLegend(h_final, h_muon, leg1, leg2, "p", "l", 0.45,0.65,0.70,0.80);
  Print(c2, dir, "relative_combined", "sumpT", print);

  plotEff(h_final,h_muon, "rel", "combined", "#Sigma pT/pT", nbin, bins, p1, p2, print);
}

void plotEff(TH1* h_1, TH1* h_2, TString& hName, TString& name, TString& title,  int& nbin, const float* bins, double &p1, double &p2,  bool print){
  TCanvas* c_eff = new TCanvas(Form("c_eff_%s_%s",hName.Data(), name.Data()),Form("c_eff_%s_%s",hName.Data(), name.Data()),1);

  TGraphAsymmErrors *eff_1 = new TGraphAsymmErrors();
  TGraphAsymmErrors *eff_2 = new TGraphAsymmErrors();

  for(int i=1 ; i <= nbin ;i++ ){
    eff_1->SetPoint(i-1, h_1->GetBinCenter(i), h_1->Integral(1,i));
    eff_2->SetPoint(i-1, h_2->GetBinCenter(i), h_2->Integral(1,i));
 
    double eff1ErrHi = sigma( h_1->Integral(1,i),p1,1);
    double eff1ErrLo = sigma( h_1->Integral(1,i),p1,1);
    double eff2ErrHi = sigma( h_2->Integral(1,i),p2,1);
    double eff2ErrLo = sigma( h_2->Integral(1,i),p2,1);

    eff_1->SetPointEYhigh (i-1, eff1ErrHi );
    eff_1->SetPointEYlow (i-1, eff1ErrLo );
    eff_2->SetPointEYhigh (i-1, eff2ErrHi );
    eff_2->SetPointEYlow (i-1, eff2ErrLo );
  }

  TH1D *h = new TH1D(Form("h_%s_%s",hName.Data(),name.Data()),"h",nbin, bins);
  h->SetMinimum(0);
  h->SetMaximum(1.05);
  h->SetTitle("");
  h->SetStats(0);
  h->GetXaxis()->SetTitle(title.Data());
  h->GetYaxis()->SetTitle("Efficiency");
  h->Draw();

  Style2(eff_1, eff_2);
  SetLatex(0.40,0.65);
  SetLegend(eff_1, eff_2, leg1, leg2, "p", "p", 0.40,0.40,0.65,0.55);
  TString pre = "eff_";
  TString temp = pre + hName;
  Print(c_eff, dir, temp.Data(), name.Data(), print);

}

