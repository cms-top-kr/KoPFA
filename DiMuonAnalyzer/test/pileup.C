#include "style.h"
#include "plot.h"

TString dir = "pileuptop";

void pileup(){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  TFile * nopileupdata = new TFile("/home/tjkim/ntuple/data/pileupstudy/RD/nopileup/vallot.root");
  TFile * pileupfdata = new TFile("/home/tjkim/ntuple/data/pileupstudy/RD/pileup/vallot.root");

  TTree * nopileuptree = (TTree *) nopileupdata->Get("DiMuon/tree");
  TTree * pileuptree = (TTree *) pileupfdata->Get("DiMuon/tree");

  TTree * vertextree = (TTree *) nopileupdata->Get("VertexFilter/tree");
  TH1 * h1 = new TH1F("h1","h1",8, 0,8);
  vertextree->Draw("multiplicity>>h1");
  h1->SetStats(0);
  h1->SetTitle(0);
  h1->GetXaxis()->SetTitle("Multiplicity");
  h1->GetYaxis()->SetTitle("Events");

  double t1 = nopileuptree->GetEntries();
  double t2 = pileuptree->GetEntries();
  cout << "no pile up event = " << t1 << endl;
  cout << "pile up event = " <<t2 << endl;

  bool printplot = true;
  
  plot(nopileuptree, pileuptree, "@jets.size()", "",  "jet", "Normalized Events", "Multiplicity","multiplicity",10,0,10,0.5, printplot);
  plot(nopileuptree, pileuptree, "jets.pt()", "",  "jet", "Normalized Entries", "Jet p_{T}","pt",35,5,75,0.2, printplot);
  plot(nopileuptree, pileuptree, "jets.eta()", "", "jet", "Normalized Entries", "Jet #eta","eta",70,-3.5,3.5,0.04, printplot);
  plot(nopileuptree, pileuptree, "jets.phi()", "", "jet", "Normalized Entries", "Jet #phi","phi",70,-3.5,3.5,0.04, printplot);

  plot(nopileuptree, pileuptree, "MET", "", "met", "Normalized Events", "MET","met",100,0,100, 0.04, printplot);

}


