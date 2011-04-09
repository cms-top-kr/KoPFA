#include "style.h"
#include "plot.h"

#include <vector>
using namespace std;
//reco::IsoDeposit::Vetos dVetos;
TString typeCh;
TString typeNh;
TString typePh;

bool printplot = true;

TString obj1 = "muon";
TString obj2 = "muon";
TString leg1 = obj1+" in PV > 1 (default)";
TString leg2 = obj2+" in PV > 1 (enabled)";

//TString dir = "Random400DataVsMuonWmunuWith0MeVForCH";
//TString dir = "pileupiso_NoPileupSequence";
  TString dir = "plotMt70_defaultVsenabled_PVs_opt";
//Chain * tree3 = new Chain("MuonIso/tree", "/tmp/tjkim/PFA/July5/Wmunu/isoNtuple_*.root");

void isoPlot(){
  //TFile * file1 = new TFile("/home/tjkim/ntuple/data/pileupstudy/RD_Mt70/vallot_pileup.root");
  //TFile * file1 = new TFile("/home/tjkim/ntuple/data/pileupstudy/RD_Mt70/noPileupSequence/vallot_nopileup.root");
  //TFile * file2 = new TFile("/home/tjkim/ntuple/data/pileupstudy/RD_Mt70/noPileupSequence/vallot_pileup.root");
  //TFile * file2 = new TFile("/home/tjkim/ntuple/data/pileupstudy/RD_Mt70/noPileupSequence/vallot_pileup.root");

  //TChain * tree1 = (TChain *) file1->Get("MuonIso/tree");
  //TChain * tree2 = (TChain *) file2->Get("MuonIso/tree");

  //TChain * treeAna1 = (TChain *) file1->Get("MuonAna/tree");
  //TChain * treeAna2 = (TChain *) file2->Get("MuonAna/tree");

  TChain * tree1 = new TChain("MuonIso/tree");
  TChain * tree2 = new TChain("MuonIso/tree");
  tree1->Add("rfio:/castor/cern.ch/user/t/tjkim/ntuple/pileupstudy/RD_Mt70/pileup4/*.root");
  tree2->Add("rfio:/castor/cern.ch/user/t/tjkim/ntuple/pileupstudy/RD_Mt70/noPileupSequence/pileup4/*.root");

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  //TCut cutjet = "random_ch_jetpT > 8";
  TCut cut1 = "pt > 20 && abs(eta) < 2.5"; 
  TCut cut2 = "pt > 20 && abs(eta) < 2.5";
 
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

  float bins[21];//21 for without Mt cut
  float bins2[21];//21 for without Mt cut
  for(int i=0; i < 21 ; i++){ 
    bins[i] = 0.0+ 0.2*i;//0.5 for without Mt cut
  }
  for(int i=0; i < 21 ; i++){
    bins2[i] = 0.0+ 0.02*i;//0.2 for without Mt cut
  }

  int Nbin = sizeof(bins)/sizeof(float) - 1;
  int Nbin2 = sizeof(bins2)/sizeof(float) - 1;

  //normalized2Eventplot(tree1, tree2, "pt","",  "Muon" , "GeV", "Entries", "pt",90,10,100, 0.065 , printplot);
  //normalized2Eventplot(tree1, tree2, "eta","",  "Muon" , "#eta", "Entries", "eta",70,-3.5,3.5, 0.065 , printplot);
  //normalized2Eventplot(tree1, tree2, "phi","",  "Muon" , "#phi", "Entries", "phi",70,-3.5,3.5, 0.065 , printplot);
  //normalized2EventIsoplot(tree1, tree2, "chargedhadron_pt","", "CH" , "Charged Hadron p_{T} (GeV)", "Entries", "pt", 50,0,5, 12, printplot);

  //plotSumpT(tree1, tree2, "chIso", "chIso", hNameSumpT[0], titleSumpT[0], "Probability", 40, 0, 4, cut1, cut2, "CH", p1, p2, printplot);
  //plotSumpT(tree1, tree2, "nhIso", "nhIso", hNameSumpT[1], titleSumpT[1], "Probability", 40, 0, 4, cut1, cut2, "NH", p1, p2, printplot);
  //plotSumpT(tree1, tree2, "phIso", "phIso", hNameSumpT[2], titleSumpT[2], "Probability", 40, 0, 4, cut1, cut2, "PH", p1, p2, printplot);

  //plotSumpT(treeAna1, treeAna2, "chIsoOpt", "chIsoOpt", hNameSumpT[0], titleSumpT[0], "Probability", Nbin, bins, cut1, cut2, "CH_default", p1, p2, printplot);
  //plotSumpT(treeAna1, treeAna2, "nhIsoOpt", "nhIsoOpt", hNameSumpT[1], titleSumpT[1], "Probability", Nbin, bins, cut1, cut2, "NH_default", p1, p2, printplot);
  //plotSumpT(treeAna1, treeAna2, "phIsoOpt", "phIsoOpt", hNameSumpT[2], titleSumpT[2], "Probability", Nbin, bins, cut1, cut2, "PH_default", p1, p2, printplot);

  plotSumpT(tree1, tree2, "chIso", "chIso", hNameSumpT[0], titleSumpT[0], "Probability", Nbin, bins, cut1, cut2, "CH", p1, p2, printplot);
  plotSumpT(tree1, tree2, "nhIso", "nhIso", hNameSumpT[1], titleSumpT[1], "Probability", Nbin, bins, cut1, cut2, "NH", p1, p2, printplot);
  plotSumpT(tree1, tree2, "phIso", "phIso", hNameSumpT[2], titleSumpT[2], "Probability", Nbin, bins, cut1, cut2, "PH", p1, p2, printplot);

  //plotdNdR(tree1, tree2, "ch_dR", "ch_dR", hNamedNdR[0], "R", titledNdR[0], 40, 0, 0.4, cutRD4, cutMC4, "pre", p1, p2, printplot);
  //plotdNdR(tree1, tree2, "nh_dR", "nh_dR", hNamedNdR[1], "R", titledNdR[1], 40, 0, 0.4, cutRD5, cutMC5, "pre", p1, p2, printplot);
  //plotdNdR(tree1, tree2, "ph_dR", "ph_dR", hNamedNdR[2], "R", titledNdR[2], 40, 0, 0.4, cutRD6, cutMC6, "pre", p1, p2, printplot);

 // plotAbsCombined( tree1, tree2, Nbin, bins, cut1, cut2, p1, p2,printplot);
  plotRelCombined( tree1, tree2, Nbin2, bins2, cut1, cut2, p1, p2,printplot);
}

//void plotSumpT(TChain *tree1, TChain *tree2, const TString &var1, const TString &var2, const TString& hName, const TString& xtitle,  const TString& ytitle, int nbin, double xlow, double xmax,  TCut cut1, TCut cut2, const TString& name, double& p1, double& p2, bool print){

