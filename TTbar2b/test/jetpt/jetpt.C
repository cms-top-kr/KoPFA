void jetpt(){

  gROOT->ProcessLine(".L ../tdrstyle.C");
  defaultStyle();

  TString path = "TTbarTuneZ2";

  TFile* f_mm = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v1/vallot_%s.root",path.Data()));
  TFile* f_ee = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v1/vallot_%s.root",path.Data()));
  TFile* f_em = new TFile(Form("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v1/vallot_%s.root",path.Data()));

  TTree* t_mm = (TTree*) f_mm->Get("MuMu/tree");
  TTree* t_ee = (TTree*) f_ee->Get("ElEl/tree");
  TTree* t_em = (TTree*) f_em->Get("MuEl/tree");

  TCut cut1 = "nbjets30_CSVM == 1";
  TCut cut2 = "nbjets30_CSVM == 2";
  TCut cut3 = "nbjets30_CSVM >= 3";
  TCut cut4 = "nbjets30_CSVM == 4";

  //plots( t_mm, cut1, "ntag1", "MuMu");
  //plots( t_mm, cut2, "ntag2", "MuMu");
  //plots( t_mm, cut3, "ntag3", "MuMu");
  
  //plots( t_ee, cut1, "ntag1", "ElEl");
  //plots( t_ee, cut2, "ntag2", "ElEl");
  //plots( t_ee, cut3, "ntag3", "ElEl");

  //plots( t_em, cut1, "ntag1", "MuEl");
  //plots( t_em, cut2, "ntag2", "MuEl");
  //plots( t_em, cut3, "ntag3", "MuEl");

}

void SetLegend(TH1F* h1, TH1F* h2){

  TLegend *l = new TLegend(0.75,0.68,0.92,0.88);
  l->AddEntry(h1,"tt + bb","L");
  l->AddEntry(h2,"tt + jj","L");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);

  l->Draw();
}

void plots( TTree* t, TCut cut, const TString & name, const TString & decayMode){

  TCut visible = "ttbarGen.NJets15() >= 4 && ttbarGen.NbJets15() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut ttbb = "ttbarGen.NbJets15() >= 4";

  TCut final = "";

  if( decayMode == "MuEl" ){
    final= "ZMass > 12 && isIso > 0 && PairSign < 0 && @jetspt30.size() >= 4 " + cut;
  }else{
    final= "ZMass > 12 && isIso > 0 && PairSign < 0 && abs(ZMass-91.2) > 15 && MET > 30 && @jetspt30.size() >= 4 " + cut;
  } 

  TH1F * h_jet1_ttbb = new TH1F(Form("h_jet1_ttbb_%s_%s",name.Data(),decayMode.Data()),Form("h_jet1_ttbb_%s_%s",name.Data(),decayMode.Data()),25,0,500); 
  TH1F * h_jet2_ttbb = new TH1F(Form("h_jet2_ttbb_%s_%s",name.Data(),decayMode.Data()),Form("h_jet2_ttbb_%s_%s",name.Data(),decayMode.Data()),25,0,500); 
  TH1F * h_jet3_ttbb = new TH1F(Form("h_jet3_ttbb_%s_%s",name.Data(),decayMode.Data()),Form("h_jet3_ttbb_%s_%s",name.Data(),decayMode.Data()),40,0,200); 
  TH1F * h_jet4_ttbb = new TH1F(Form("h_jet4_ttbb_%s_%s",name.Data(),decayMode.Data()),Form("h_jet4_ttbb_%s_%s",name.Data(),decayMode.Data()),40,0,200); 

  TH1F * h_jet1_ttjj = new TH1F(Form("h_jet1_ttjj_%s_%s",name.Data(),decayMode.Data()),Form("h_jet1_ttjj_%s_%s",name.Data(),decayMode.Data()),25,0,500);
  TH1F * h_jet2_ttjj = new TH1F(Form("h_jet2_ttjj_%s_%s",name.Data(),decayMode.Data()),Form("h_jet2_ttjj_%s_%s",name.Data(),decayMode.Data()),25,0,500);
  TH1F * h_jet3_ttjj = new TH1F(Form("h_jet3_ttjj_%s_%s",name.Data(),decayMode.Data()),Form("h_jet3_ttjj_%s_%s",name.Data(),decayMode.Data()),40,0,200);
  TH1F * h_jet4_ttjj = new TH1F(Form("h_jet4_ttjj_%s_%s",name.Data(),decayMode.Data()),Form("h_jet4_ttjj_%s_%s",name.Data(),decayMode.Data()),40,0,200);

  t->Project(Form("h_jet1_ttbb_%s_%s",name.Data(),decayMode.Data()),"jetspt30[0].pt()" ,visible+ttbb+final); 
  t->Project(Form("h_jet2_ttbb_%s_%s",name.Data(),decayMode.Data()),"jetspt30[1].pt()" ,visible+ttbb+final); 
  t->Project(Form("h_jet3_ttbb_%s_%s",name.Data(),decayMode.Data()),"jetspt30[2].pt()" ,visible+ttbb+final); 
  t->Project(Form("h_jet4_ttbb_%s_%s",name.Data(),decayMode.Data()),"jetspt30[3].pt()" ,visible+ttbb+final); 

  t->Project(Form("h_jet1_ttjj_%s_%s",name.Data(),decayMode.Data()),"jetspt30[0].pt()" ,visible+final);
  t->Project(Form("h_jet2_ttjj_%s_%s",name.Data(),decayMode.Data()),"jetspt30[1].pt()" ,visible+final);
  t->Project(Form("h_jet3_ttjj_%s_%s",name.Data(),decayMode.Data()),"jetspt30[2].pt()" ,visible+final);
  t->Project(Form("h_jet4_ttjj_%s_%s",name.Data(),decayMode.Data()),"jetspt30[3].pt()" ,visible+final);

  double s_jet1_ttbb = h_jet1_ttbb->Integral(); 
  double s_jet2_ttbb = h_jet2_ttbb->Integral(); 
  double s_jet3_ttbb = h_jet3_ttbb->Integral(); 
  double s_jet4_ttbb = h_jet4_ttbb->Integral(); 

  double s_jet1_ttjj = h_jet1_ttjj->Integral();
  double s_jet2_ttjj = h_jet2_ttjj->Integral();
  double s_jet3_ttjj = h_jet3_ttjj->Integral();
  double s_jet4_ttjj = h_jet4_ttjj->Integral();
  
  h_jet1_ttbb->Scale(1.0/s_jet1_ttbb);
  h_jet2_ttbb->Scale(1.0/s_jet2_ttbb);
  h_jet3_ttbb->Scale(1.0/s_jet3_ttbb);
  h_jet4_ttbb->Scale(1.0/s_jet4_ttbb);
  
  h_jet1_ttjj->Scale(1.0/s_jet1_ttjj);
  h_jet2_ttjj->Scale(1.0/s_jet2_ttjj);
  h_jet3_ttjj->Scale(1.0/s_jet3_ttjj);
  h_jet4_ttjj->Scale(1.0/s_jet4_ttjj);

  TCanvas* c_jet1 = new TCanvas(Form("c_jet1_%s_%s",name.Data(),decayMode.Data()),Form("c_jet1_%s_%s",name.Data(),decayMode.Data()),1);
  h_jet1_ttjj->SetTitle("");
  h_jet1_ttjj->SetMaximum(0.3);
  h_jet1_ttjj->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  h_jet1_ttjj->GetYaxis()->SetTitle("Normalized Entries");
  h_jet1_ttbb->SetLineColor(2);
  h_jet1_ttbb->SetLineWidth(2);
  h_jet1_ttjj->SetLineWidth(2);
  //h_jet1_ttjj->Draw();
  //h_jet1_ttbb->Draw("same");
  SetLegend(h_jet1_ttbb, h_jet1_ttjj);

  TCanvas* c_jet2 = new TCanvas(Form("c_jet2_%s_%s",name.Data(),decayMode.Data()),Form("c_jet2_%s_%s",name.Data(),decayMode.Data()),1);
  h_jet2_ttjj->SetTitle("");
  h_jet2_ttjj->SetMaximum(0.5);
  h_jet2_ttjj->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  h_jet2_ttjj->GetYaxis()->SetTitle("Normalized Entries");
  h_jet2_ttbb->SetLineColor(2);
  h_jet2_ttbb->SetLineWidth(2);
  h_jet2_ttjj->SetLineWidth(2);
  //h_jet2_ttjj->Draw();
  //h_jet2_ttbb->Draw("same");
  SetLegend(h_jet2_ttbb, h_jet2_ttjj);

  TCanvas* c_jet3 = new TCanvas(Form("c_jet3_%s_%s",name.Data(),decayMode.Data()),Form("c_jet3_%s_%s",name.Data(),decayMode.Data()),1);
  h_jet3_ttjj->SetTitle("");
  h_jet3_ttjj->SetMaximum(0.5);
  h_jet3_ttjj->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  h_jet3_ttjj->GetYaxis()->SetTitle("Normalized Entries");
  h_jet3_ttbb->SetLineColor(2);
  h_jet3_ttbb->SetLineWidth(2);
  h_jet3_ttjj->SetLineWidth(2);
  //h_jet3_ttjj->Draw();
  //h_jet3_ttbb->Draw("same");
  SetLegend(h_jet3_ttbb, h_jet3_ttjj);

  TCanvas* c_jet4 = new TCanvas(Form("c_jet4_%s_%s",name.Data(),decayMode.Data()),Form("c_jet4_%s_%s",name.Data(),decayMode.Data()),1);
  h_jet4_ttjj->SetTitle("");
  h_jet4_ttjj->SetMaximum(0.5);
  h_jet4_ttjj->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  h_jet4_ttjj->GetYaxis()->SetTitle("Normalized Entries");
  h_jet4_ttbb->SetLineColor(2);
  h_jet4_ttbb->SetLineWidth(2);
  h_jet4_ttjj->SetLineWidth(2);
  //h_jet4_ttjj->Draw();
  //h_jet4_ttbb->Draw("same");
  SetLegend(h_jet4_ttbb, h_jet4_ttjj);

  TFile *result = new TFile("result.root","recreate");
  h_jet1_ttbb->Write();
  h_jet2_ttbb->Write();
  h_jet3_ttbb->Write();
  h_jet4_ttbb->Write();
  
  h_jet1_ttjj->Write();
  h_jet2_ttjj->Write();
  h_jet3_ttjj->Write();
  h_jet4_ttjj->Write();

  //c_jet1->Print(Form("results/c_jet1_%s_%s.eps",name.Data(),decayMode.Data()));
  //c_jet2->Print(Form("results/c_jet2_%s_%s.eps",name.Data(),decayMode.Data()));
  //c_jet3->Print(Form("results/c_jet3_%s_%s.eps",name.Data(),decayMode.Data()));
  //c_jet4->Print(Form("results/c_jet4_%s_%s.eps",name.Data(),decayMode.Data()));

}

