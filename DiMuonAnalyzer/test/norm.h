//normalization factor 
double norm_Zmm ;
double norm_Ztautau ;
double norm_Wmunu  ;
double norm_Wtautau ;
double norm_tt     ;
double norm_tt2l   ;
double norm_QCD    ;

void totalevent(){
  //unit pb
  double scale = 1.0;

  //luminosity
  double lumi_e=0.250;

  //cross section at D0 
  //double Zmm = 242 ;
  //double Ztt = 242 ;
  //double tt = 0.7 ;
  //double WW = 1.08 ;
  //double WZ = 0.1104 ;
  //double ZZ = 0.071;
  //double Wm = 2583 ;
  //double ZZ4mu = 0.001278;
  //cross section at CMS at 7 TeV 
  double Zmm     = 1300 ;
  double Ztautau = 1300 ;
  double Wmunu   = 7899;
  double Wtautau = 7899;
  double tt      = 94.3;
  double tt2l    = 17.3;
  double QCD     = 109853;
 
  TChain * nZmumu = new TChain("EventInfo/tree");
  TChain * nZtautau = new TChain("EventInfo/tree");
  TChain * nWmunu = new TChain("EventInfo/tree");
  TChain * nQCD = new TChain("EventInfo/tree");
  TChain * nTTbar = new TChain("EventInfo/tree");

  nZmumu->Add("mc/Summer10_v2/Zmumu/vallot_*.root");
  nZtautau->Add("mc/Summer10_v2/Ztautau/vallot_*.root");
  nWmunu->Add("mc/Summer10_v2/Wmunu/vallot_*.root");
  nQCD->Add("mc/Summer10_v2/InclusiveMu15/vallot_*.root");
  nTTbar->Add("mc/Summer10_v2/TTbar/vallot_*.root");

  //total number of events
  double N_Zmm     = 100000 ; //2076806
  double N_Ztautau = 100000 ; //1265250
  double N_Wmunu   = 50000;
  double N_Wtautau = 100000;
  double N_tt   = 100000 ; //103500
  double N_tt2l = 100000 ; //103500
  double N_QCD = 6000000;

  N_Zmm = nZmumu->GetEntries();
  N_Ztautau = nZtautau->GetEntries();
  N_Wmunu = nWmunu->GetEntries();
  N_QCD = nQCD->GetEntries();
  N_tt = nTTbar->GetEntries();

  cout << "Zmm= " << N_Zmm << endl;
  cout << "Ztautau= " << N_Ztautau << endl;
  cout << "Wmunu= " << N_Wmunu << endl;
  cout << "QCD= " << N_QCD << endl;
  cout << "tt= " << N_tt << endl;

  //luminosity for MC
  double L_Zmm     = N_Zmm/Zmm;
  double L_Ztautau = N_Ztautau/Ztautau;
  double L_Wmunu   = N_Wmunu/Wmunu;
  double L_Wtautau = N_Wtautau/Wtautau;
  double L_tt      = N_tt/tt;
  double L_tt2l    = N_tt2l/tt2l;
  double L_QCD     = N_QCD/QCD;

  //normalization factor 
  norm_Zmm      =   lumi_e / L_Zmm ;
  norm_Ztautau  =   lumi_e / L_Ztautau ;
  norm_Wmunu    =   lumi_e / L_Wmunu ;
  norm_Wtautau  =   lumi_e / L_Wtautau ;
  norm_tt       =   lumi_e / L_tt;
  norm_tt2l     =   lumi_e / L_tt2l;
  norm_QCD      =   lumi_e / L_QCD;


}
