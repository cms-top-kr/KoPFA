#include "style.h"

void vertex(){
  Chain * tree1 = new Chain("VertexAnalysis/tree", "data/muon/full_v2/isoNtuple_old.root");
  Chain * tree2 = new Chain("VertexAnalysis/tree", "data/muon/full_v2/isoNtuple_latest.root");

  TH1 * h1 = new TH1F("h1","h1",8, 0,8);
  TH1 * h2 = new TH1F("h2","h2",8, 0,8);


  TCanvas * c= new TCanvas("c","c",1);

  tree1->Draw("multiplicity>>h1");
  tree2->Draw("multiplicity>>h2","","same");

  h1->Scale(1.0/tree1->GetEntries());
  h2->Scale(1.0/tree2->GetEntries());

  StyleSimple(h1,h2,"Multiplicity","Normalized Events");
  SetLegend(h1,h2,"old","latest","l","l",0.6,0.6,0.9,0.8);
}
