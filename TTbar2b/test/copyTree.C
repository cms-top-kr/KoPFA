#include "TFile.h"
#include "TTree.h"
#include <iostream>

void copyTree(){

  std::cout << "TEST" << std::endl;

  TFile *f = new TFile("vallot_TTbarTuneZ2_new.root");
  TTree *t = (TTree* ) f->Get("MuMu/tree");

  TFile *f2 = new TFile("vallot_dummy.root","recreate");
  TTree *c = t->CopyTree("ttbarGen.diLeptonic(1) == 1");
  c->Write("/MuMu");
  //t->Draw("ttbarGen.mass()");

  std::cout << "old=" <<  t->GetEntries() << std::endl;
  std::cout << "new=" <<  c->GetEntries() << std::endl;
  
}
