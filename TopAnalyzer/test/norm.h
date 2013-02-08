//normalization factor 
double norm_Zmm ;
double norm_Ztautau ;
double norm_Wmunu  ;
double norm_Wtaunu ;
double norm_tt     ;
double norm_tt2l   ;
double norm_QCD    ;

void totalevent( TFile* fdata, TFile* fZmumu, TFile* fZtautau, TFile* fWmunu, TFile* fQCD, TFile* fTTbar){
  using namespace std;

  TH1F * evtdata = (TH1F *) fdata->Get("DiMuon/EventSummary");
  TH1F * evtZmumu = (TH1F *) fZmumu->Get("DiMuon/EventSummary");
  TH1F * evtZtautau = (TH1F *) fZtautau->Get("DiMuon/EventSummary");
  TH1F * evtWmunu = (TH1F *) fWmunu->Get("DiMuon/EventSummary");
  TH1F * evtQCD = (TH1F *) fQCD->Get("DiMuon/EventSummary");  
  TH1F * evtTTbar = (TH1F *) fTTbar->Get("DiMuon/EventSummary");

  int nData = evtdata->GetBinContent(1);
  int nZmumu = evtZmumu->GetBinContent(1);  
  int nZtautau = evtZtautau->GetBinContent(1);
  int nWmunu = evtWmunu->GetBinContent(1);
  int nQCD = evtQCD->GetBinContent(1);
  int nTTbar = evtTTbar->GetBinContent(1);

  //unit pb
  //double scale = 1.0;

  //luminosity
  double lumi_e=2.88;

  //double Zmm     = 1660 ;
  double Zmm     = 3048 ;
  double Ztautau = 1660 ;
  double Wmunu = 31314;
  //double Wmunu   = 7899;
  double Wtaunu = 7899;
  double tt      = 157.5;
  double tt2l    = 17.3;
  //double QCD     = 109853;
  double QCD     = 79688 ;
 
  //TChain * nZmumu = new TChain("EventInfo/tree");
  //TChain * nZtautau = new TChain("EventInfo/tree");
  //TChain * nWmunu = new TChain("EventInfo/tree");
  //TChain * nQCD = new TChain("EventInfo/tree");
  //TChain * nTTbar = new TChain("EventInfo/tree");

  //nZmumu->Add("mc/Summer10_v2/Zmumu/vallot_*.root");
  //nZtautau->Add("mc/Summer10_v2/Ztautau/vallot_*.root");
  //nWmunu->Add("mc/Summer10_v2/Wmunu/vallot_*.root");
  //nQCD->Add("mc/Summer10_v2/InclusiveMu15/vallot_*.root");
  //nTTbar->Add("mc/Summer10_v2/TTbar/vallot_*.root");

  //total number of events
  double N_Zmm     = nZmumu; //100000 ;
  double N_Ztautau = nZtautau; //100000 ; 
  double N_Wmunu   = nWmunu; // 50000;
  double N_Wtaunu = 100000;
  double N_tt   = nTTbar; //100000 ; //103500
  double N_tt2l = nTTbar; //100000 ; //103500
  double N_QCD = nQCD;// 6000000;

  //N_Zmm = nZmumu->GetEntries();
  //N_Ztautau = nZtautau->GetEntries();
  //N_Wmunu = nWmunu->GetEntries();
  //N_QCD = nQCD->GetEntries();
  //N_tt = nTTbar->GetEntries();
  cout << "Lumi-----------" << endl; 
  cout << "Data= " << lumi_e << "(" << nData << ")" << endl;
  cout << "Zmm= " << N_Zmm/Zmm << "(" << N_Zmm << ")" << endl;
  cout << "Ztautau= " << N_Ztautau/Ztautau << "(" << N_Ztautau << ")" << endl;
  cout << "Wmunu= " << N_Wmunu/Wmunu << "(" << N_Wmunu << ")" << endl;
  cout << "QCD= " << N_QCD/QCD << "(" << N_QCD << ")" << endl;
  cout << "tt= " << N_tt/tt << "(" << N_tt << ")" << endl;
  cout << "---------------" << endl;

  //luminosity for MC
  double L_Zmm     = N_Zmm/Zmm;
  double L_Ztautau = N_Ztautau/Ztautau;
  double L_Wmunu   = N_Wmunu/Wmunu;
  double L_Wtaunu = N_Wtaunu/Wtaunu;
  double L_tt      = N_tt/tt;
  double L_tt2l    = N_tt2l/tt2l;
  double L_QCD     = N_QCD/QCD;

  //normalization factor 
  norm_Zmm      =   lumi_e / L_Zmm ;
  norm_Ztautau  =   lumi_e / L_Ztautau ;
  norm_Wmunu    =   lumi_e / L_Wmunu ;
  norm_Wtaunu  =   lumi_e / L_Wtaunu ;
  norm_tt       =   lumi_e / L_tt;
  norm_tt2l     =   lumi_e / L_tt2l;
  norm_QCD      =   lumi_e / L_QCD;


}
