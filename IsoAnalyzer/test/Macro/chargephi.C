Chain * tree = new Chain("MuonIsoAnal/tree", "/tmp/tjkim/PFA/July2/Wmunu/isoNtuple_*.root");

void chargephi(){

  gSystem->Load("libFWCoreFWLite.so");
  gROOT->LoadMacro("../tdrstyle.C");
  setTDRStyle();

  //TCut jetcut = "random_jetpT > 7";
  TCut cut1 = "ph_charge > 0 && ph_dR < 0.2 && TMath::Abs(ph_deta) < 0.01";// && mu_ph_mpT < 25";
  TCut cut2 = "ph_charge < 0 && ph_dR < 0.2 && TMath::Abs(ph_deta) < 0.01";// && mu_ph_mpT < 25";

  int nbin = 40;
  double xlow = -0.2;
  double xmax = 0.2;

  TH1 *h_temp_phi = new TH1F("h_temp_phi","h_temp_phi", nbin, xlow, xmax);
  TH1 *h_temp_eta = new TH1F("h_temp_eta","h_temp_eta", nbin, xlow, xmax);

  TH1 *h_muon_pos_phi = new TH1F("h_muon_pos_phi","h_muon_pos_phi", nbin, xlow, xmax);
  TH1 *h_muon_neg_phi = new TH1F("h_muon_neg_phi","h_muon_neg_phi", nbin, xlow, xmax);
  TH1 *h_muon_pos_eta = new TH1F("h_muon_pos_eta","h_muon_pos_eta", nbin, xlow, xmax);
  TH1 *h_muon_neg_eta = new TH1F("h_muon_neg_eta","h_muon_neg_eta", nbin, xlow, xmax);

  h_muon_pos_phi->SetLineColor(4);
  h_muon_pos_phi->SetLineStyle(1);
  h_muon_neg_phi->SetLineColor(2);
  h_muon_neg_phi->SetLineStyle(2);

  h_muon_pos_phi->SetLineWidth(2);
  h_muon_neg_phi->SetLineWidth(2);

  h_muon_pos_eta->SetLineColor(4);
  h_muon_neg_eta->SetLineColor(2);

  TCanvas *c_phi = new TCanvas ("c_phi","c_phi",1);
  h_temp_phi->SetStats(0);
  h_temp_phi->GetXaxis()->SetTitle("#Delta#phi");
  h_temp_phi->GetYaxis()->SetTitle("Normalized Entries");
  h_temp_phi->SetTitle(0);
  h_temp_phi->SetMaximum(0.18);
  //h_temp_phi->SetMaximum(0.1);
  h_temp_phi->Draw();

  tree->Draw("ph_decalphi>>h_muon_pos_phi",cut1,"same");  
  tree->Draw("ph_decalphi>>h_muon_neg_phi",cut2,"same");

  h_muon_pos_phi->Scale(1.0/h_muon_pos_phi->GetEntries());
  h_muon_neg_phi->Scale(1.0/h_muon_neg_phi->GetEntries());

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(0.23,0.87,"W #rightarrow #mu#nu in MC");
  label->DrawLatex(0.23,0.82,"#Delta#phi = #phi_{#gamma} - #phi_{#mu}");


  TLegend * l_phi = new TLegend(0.6,0.75,0.8,0.9);
  l_phi->SetLineColor(0);
  l_phi->SetFillColor(0);
  l_phi->SetTextSize(0.04);
  l_phi->AddEntry("h_muon_pos_phi","#gamma around + #mu","l");
  l_phi->AddEntry("h_muon_neg_phi","#gamma around - #mu","l");
  l_phi->Draw();
  
  c_phi->Print("c_chargephi_atEcal.eps");
  c_phi->Print("c_chargephi_atEcal.pdf");
  c_phi->Print("c_chargephi_atEcal.png");

}
