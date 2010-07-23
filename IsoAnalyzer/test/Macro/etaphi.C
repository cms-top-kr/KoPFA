Chain * tree1 = new Chain("MuonIso/tree", "/tmp/tjkim/PFA/July2/Wmunu/isoNtuple_*.root");
Chain * tree2 = new Chain("RandomIsoForMuon/tree", "/tmp/tjkim/PFA/July2/Wmunu/isoNtuple_*.root");
Chain * tree3 = new Chain("MuonIsoAnal/tree", "/tmp/tjkim/PFA/July2/Wmunu/isoNtuple_*.root");

void etaphi(){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("../tdrstyle.C");
  setTDRStyle();

  TCut jetcut;
  //TCut jetcut = "random_jetpT > 7";
  TCut cut1 = "ph_dR < 0.3";
  TCut cut2 = "ph_dR < 0.3";

  TH1 *h_muon = new TH1F("h_muon", "h_muon", 500, -2.5, 2.5);
  TH1 *h_random = new TH1F("h_random","h_random", 500, -2.5, 2.5);
  tree1->Project("h_muon","eta");
  tree2->Project("h_random","eta");
  cout << "muon = " << h_muon->GetEntries() << endl;
  cout << "random = " << h_random->GetEntries() << endl;
  double p1 = h_muon->GetEntries();
  double p2 = h_random->GetEntries();
  cout << "p1 = " << p1 << endl;
  cout << "p2 = " << p2 << endl;

  bool printplot = false;
  plot("ph_deta", "ph_deta", "deta", "#Delta#eta", 0.015 , cut1, cut2, p1, p2, printplot);
  plot("ph_dphi", "ph_dphi", "dphi", "#Delta#phi", 0.015 , cut1, cut2, p1, p2, printplot);
  plot2D("dphi_deta",printplot);
  fsr(printplot);
 
}

void plot(TString& var1, TString& var2, TString& hName , TString& xtitle, double max,  TCut cut1, TCut cut2, double& p1, double& p2, bool print){

  TH1 *h_1 = new TH1F(Form("h_1_%s",hName.Data()),Form("h_1_%s",hName.Data()), 80, -0.4, 0.4);
  TH1 *h_2 = new TH1F(Form("h_2_%s",hName.Data()),Form("h_2_%s",hName.Data()), 80, -0.4, 0.4);

  h_1->SetLineColor(2);
  h_2->SetLineColor(4);

  TCanvas *c = new TCanvas(Form("c_%s",hName.Data()),Form("c_%s",hName.Data()),1);
  TH1 *h_temp = new TH1F(Form("h_temp_%s",hName.Data()),Form("h_temp_%s",hName.Data()), 80, -0.4, 0.4);
  h_temp->SetStats(0);
  h_temp->GetXaxis()->SetTitle(xtitle.Data());
  h_temp->SetTitle(0);
  h_temp->SetMaximum(max);
  h_temp->Draw();

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.05);
  label->DrawLatex(0.18,0.87,"  #sqrt{s} =7 TeV");
  label->DrawLatex(0.18,0.82,"  W #rightarrow #mu#nu MC");

  tree2->Draw(Form("%s>>h_2_%s",var2.Data(),hName.Data()),cut2,"same");
  tree1->Draw(Form("%s>>h_1_%s",var1.Data(),hName.Data()),cut1,"same");
  h_2->Scale(1.0/p2);
  h_1->Scale(1.0/p1);

  TLegend * l = new TLegend(0.6,0.7,0.8,0.9);
  l->SetLineColor(0);
  l->SetFillColor(0);
  l->SetTextSize(0.04);
  l->AddEntry(h_1,"#gamma around muon","l");
  l->AddEntry(h_2,"#gamma around random","l");
  l->Draw();

  if(print){
   c->Print(Form("c_%s.png",hName.Data()));
   c->Print(Form("c_%s.eps",hName.Data()));
   c->Print(Form("c_%s.pdf",hName.Data()));
  }
}

void plot2D(TString& hName, bool print){

  TCanvas *c = new TCanvas("c_mu_eta_phi","c_mu_eta_phi",1);
  TH2 *h2_eta_phi = new TH2F("h2_eta_phi","h2_eta_phi",40,-0.4,0.4,40,-0.4,0.4);
  tree1->Draw("ph_dphi:ph_deta>>h2_eta_phi","ph_th > 0.5");
  h2_eta_phi->SetContour(100);
  h2_eta_phi->Draw("Colz");
  h2_eta_phi->SetStats(0);
  h2_eta_phi->GetXaxis()->SetTitle("#Delta#eta");
  h2_eta_phi->GetYaxis()->SetTitle("#Delta#phi");
 
  if(print){
    c->Print(Form("c_%s.png",hName.Data()));
    c->Print(Form("c_%s.eps",hName.Data()));
    c->Print(Form("c_%s.pdf",hName.Data()));
  }
}

void fsr(bool print){

  TCut isFSR = "fsr_photon_dR > -1";

  //TH1 *h_pt_fsr = new TH1F("h_pt_fsr","h_pt_sr",10,0,10);
  //TH1 *h_pt = new TH1F("h_pt","h_pt",10,0,10);
  //tree2->Project("h_pt_fsr","muon_pt",isFSR);
  //tree2->Project("h_pt","muon_pt");
  //double nmuon = h_pt->GetEntries() ;
  //double nfsr = h_pt_fsr->GetEntries();
  //cout << "muons= " << nmuon << endl; 
  //cout << "muons which have fsr= " << nfsr << endl; 
  //cout << "fraction of fsr= " << nfsr/nmuon << endl; 

  
  TH2 *h2_fsr_phi_eta = new TH2F("h2_fsr_phi_eta","phi_eta",40,-0.4,0.4,40,-0.4,0.4);
  TH2 *h2_fsr_pt_dR = new TH2F("h2_fsr_pt_dR","pt_dR",50,0,0.5,100,0,10);
  TH2 *h2_reco_pt_dR = new TH2F("h2_reco_pt_dR","pt_dR",50,0,0.5,100,0,10);

  TCanvas *c_fsr_phi_eta = new TCanvas("c_fsr_phi_eta","c_fsr_phi_eta",1);
  tree3->Project("h2_fsr_phi_eta","fsr_photon_phi:fsr_photon_eta",isFSR);
  h2_fsr_phi_eta->SetContour(100);
  h2_fsr_phi_eta->Draw("Colz");
  h2_fsr_phi_eta->SetStats(0);
  h2_fsr_phi_eta->GetXaxis()->SetTitle("#Delta#eta");
  h2_fsr_phi_eta->GetYaxis()->SetTitle("#Delta#phi");

  TCanvas *c_fsr_pt_dR = new TCanvas("c_fsr_pt_dR","c_fsr_pt_dR",1);
  //tree2->Project("h2_fsr_pt_dR","fsr_photon_pt:fsr_photon_dR","fsr_photon_dR > -1");
  tree3->Project("h2_fsr_pt_dR","fsr_photon_pt:TMath::Sqrt(fsr_photon_phi*fsr_photon_phi+fsr_photon_eta*fsr_photon_eta)",isFSR);
  h2_fsr_pt_dR->SetContour(100);
  h2_fsr_pt_dR->Draw("Colz");
  h2_fsr_pt_dR->SetStats(0);
  h2_fsr_pt_dR->GetXaxis()->SetTitle("R");
  h2_fsr_pt_dR->GetYaxis()->SetTitle("pT (GeV)");

  TCanvas *c_reco_pt_dR = new TCanvas("c_reco_pt_dR","c_reco_pt_dR",1);
  tree1->Project("h2_reco_pt_dR","ph_th:ph_dR","ph_dR > -1");
  h2_reco_pt_dR->SetContour(100);
  h2_reco_pt_dR->Draw("Colz");
  h2_reco_pt_dR->SetStats(0);
  h2_reco_pt_dR->GetXaxis()->SetTitle("R");
  h2_reco_pt_dR->GetYaxis()->SetTitle("pT (GeV)");

  if(print){
    c_fsr_phi_eta->Print("c_fsr_dphi_deta.eps");
    c_fsr_phi_eta->Print("c_fsr_dphi_deta.png");
    c_fsr_phi_eta->Print("c_fsr_dphi_deta.pdf");
    c_fsr_pt_dR->Print("c_fsr_pt_dR.eps");
    c_fsr_pt_dR->Print("c_fsr_pt_dR.png");
    c_fsr_pt_dR->Print("c_fsr_pt_dR.pdf");
    c_reco_pt_dR->Print("c_reco_pt_dR.eps");
    c_reco_pt_dR->Print("c_reco_pt_dR.png");
    c_reco_pt_dR->Print("c_reco_pt_dR.pdf");
  }
}
