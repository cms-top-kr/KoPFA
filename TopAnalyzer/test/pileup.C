#include "style.h"
#include "plot.h"

TString dir = "pileuptop_NoPileupSequence";
//TString dir = "pileuptop";

void pileup(){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  TFile * nopileupdata = new TFile("/home/tjkim/ntuple/data/pileupstudy/RD/vallot_nopileup.root");
  TFile * pileupfdata = new TFile("/home/tjkim/ntuple/data/pileupstudy/RD/vallot_pileup.root");
  //TFile * nopileupdata = new TFile("/home/tjkim/ntuple/data/pileupstudy/RD/noPileupSequence/vallot_nopileup.root");
  //TFile * pileupfdata = new TFile("/home/tjkim/ntuple/data/pileupstudy/RD/noPileupSequence/vallot_pileup.root");


  TTree * nopileuptree = (TTree *) nopileupdata->Get("DiMuon/tree");
  TTree * pileuptree = (TTree *) pileupfdata->Get("DiMuon/tree");
  TTree * vertextree = (TTree *) nopileupdata->Get("VertexFilter/tree");

  double t1 = nopileuptree->GetEntries();
  double t2 = pileuptree->GetEntries();
  cout << "no pile up event = " << t1 << endl;
  cout << "pile up event = " <<t2 << endl;

  bool printplot = false;
 
  singlePlot(vertextree, "multiplicity", "","vertex","Multiplicity","Events","multiplicity",8,0,8, -1, printplot);
 
  plot(nopileuptree, pileuptree, "@jets.size()", "", "jet", "Multiplicity", "Events" ,"multiplicity",10,0,10,1, printplot);
  plot(nopileuptree, pileuptree, "@jetspt30.size()", "", "jetpt30", "Multiplicity", "Events" ,"multiplicity",10,0,10,1, printplot);
  plot(nopileuptree, pileuptree, "jets.pt()", "",  "jet", "Jet p_{T}", "Entries","pt",35,5,75,0.2, printplot);
  plot(nopileuptree, pileuptree, "jets.eta()", "", "jet", "Jet #eta" , "Entries","eta",70,-3.5,3.5,0.04, printplot);
  plot(nopileuptree, pileuptree, "jets.phi()", "", "jet", "Jet #phi" , "Entries","phi",70,-3.5,3.5,0.04, printplot);

  plot(nopileuptree, pileuptree, "MET", "", "met", "MET", "Events", "et",100,0,100, 0.1, printplot);

}


