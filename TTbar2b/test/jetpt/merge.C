void merge(){
	TFile* fMuMu = new TFile("resultMuMuntag3.root");
	TFile* fElEl = new TFile("resultElElntag3.root");
	TFile* fMuEl = new TFile("resultMuElntag3.root");
	
    gROOT->ProcessLine(".L ../tdrstyle.C");
    defaultStyle();
	
	TH1F* h_jet1_ttbb_ntag3_MuMu = (TH1F*)fMuMu->Get("h_jet1_ttbb_ntag3_MuMu"); 
	TH1F* h_jet2_ttbb_ntag3_MuMu = (TH1F*)fMuMu->Get("h_jet2_ttbb_ntag3_MuMu"); 
	TH1F* h_jet3_ttbb_ntag3_MuMu = (TH1F*)fMuMu->Get("h_jet3_ttbb_ntag3_MuMu"); 
	TH1F* h_jet4_ttbb_ntag3_MuMu = (TH1F*)fMuMu->Get("h_jet4_ttbb_ntag3_MuMu"); 
	TH1F* h_jet1_ttbb_ntag3_ElEl = (TH1F*)fElEl->Get("h_jet1_ttbb_ntag3_ElEl"); 
	TH1F* h_jet2_ttbb_ntag3_ElEl = (TH1F*)fElEl->Get("h_jet2_ttbb_ntag3_ElEl"); 
	TH1F* h_jet3_ttbb_ntag3_ElEl = (TH1F*)fElEl->Get("h_jet3_ttbb_ntag3_ElEl"); 
	TH1F* h_jet4_ttbb_ntag3_ElEl = (TH1F*)fElEl->Get("h_jet4_ttbb_ntag3_ElEl"); 
	TH1F* h_jet1_ttbb_ntag3_MuEl = (TH1F*)fMuEl->Get("h_jet1_ttbb_ntag3_MuEl"); 
	TH1F* h_jet2_ttbb_ntag3_MuEl = (TH1F*)fMuEl->Get("h_jet2_ttbb_ntag3_MuEl"); 
	TH1F* h_jet3_ttbb_ntag3_MuEl = (TH1F*)fMuEl->Get("h_jet3_ttbb_ntag3_MuEl"); 
	TH1F* h_jet4_ttbb_ntag3_MuEl = (TH1F*)fMuEl->Get("h_jet4_ttbb_ntag3_MuEl");
	
	TH1F* h_jet1_ttjj_ntag3_MuMu = (TH1F*)fMuMu->Get("h_jet1_ttjj_ntag3_MuMu"); 
	TH1F* h_jet2_ttjj_ntag3_MuMu = (TH1F*)fMuMu->Get("h_jet2_ttjj_ntag3_MuMu"); 
	TH1F* h_jet3_ttjj_ntag3_MuMu = (TH1F*)fMuMu->Get("h_jet3_ttjj_ntag3_MuMu"); 
	TH1F* h_jet4_ttjj_ntag3_MuMu = (TH1F*)fMuMu->Get("h_jet4_ttjj_ntag3_MuMu"); 
	TH1F* h_jet1_ttjj_ntag3_ElEl = (TH1F*)fElEl->Get("h_jet1_ttjj_ntag3_ElEl"); 
	TH1F* h_jet2_ttjj_ntag3_ElEl = (TH1F*)fElEl->Get("h_jet2_ttjj_ntag3_ElEl"); 
	TH1F* h_jet3_ttjj_ntag3_ElEl = (TH1F*)fElEl->Get("h_jet3_ttjj_ntag3_ElEl"); 
	TH1F* h_jet4_ttjj_ntag3_ElEl = (TH1F*)fElEl->Get("h_jet4_ttjj_ntag3_ElEl"); 
	TH1F* h_jet1_ttjj_ntag3_MuEl = (TH1F*)fMuEl->Get("h_jet1_ttjj_ntag3_MuEl"); 
	TH1F* h_jet2_ttjj_ntag3_MuEl = (TH1F*)fMuEl->Get("h_jet2_ttjj_ntag3_MuEl"); 
	TH1F* h_jet3_ttjj_ntag3_MuEl = (TH1F*)fMuEl->Get("h_jet3_ttjj_ntag3_MuEl"); 
	TH1F* h_jet4_ttjj_ntag3_MuEl = (TH1F*)fMuEl->Get("h_jet4_ttjj_ntag3_MuEl");
	
	TCanvas* can1 = new TCanvas("can1","leading jet",1200,1200);
	TCanvas* can2 = new TCanvas("can2","second leading jet",1200,1200);
	TCanvas* can3 = new TCanvas("can3","third leading jet",1200,1200);
	TCanvas* can4 = new TCanvas("can4","fourth leading jet",1200,1200);
	
	can1->cd();
	h_jet1_ttbb_ntag3_MuMu->Add(h_jet1_ttbb_ntag3_ElEl);
	h_jet1_ttbb_ntag3_MuMu->Add(h_jet1_ttbb_ntag3_MuEl);
	h_jet1_ttbb_ntag3_MuMu->Scale(1.0/(h_jet1_ttbb_ntag3_MuMu->Integral()+h_jet1_ttbb_ntag3_ElEl->Integral()+h_jet1_ttbb_ntag3_MuEl->Integral()));
	h_jet1_ttjj_ntag3_MuMu->Add(h_jet1_ttjj_ntag3_ElEl);
	h_jet1_ttjj_ntag3_MuMu->Add(h_jet1_ttjj_ntag3_MuEl);
	h_jet1_ttjj_ntag3_MuMu->Scale(1.0/(h_jet1_ttjj_ntag3_MuMu->Integral()+h_jet1_ttjj_ntag3_ElEl->Integral()+h_jet1_ttjj_ntag3_MuEl->Integral()));
	h_jet1_ttbb_ntag3_MuMu->Draw();
	h_jet1_ttjj_ntag3_MuMu->Draw("same");
	h_jet1_ttbb_ntag3_MuMu->SetTitle("leading jet pt distibution");
	h_jet1_ttbb_ntag3_MuMu->SetStats(0);
	h_jet1_ttbb_ntag3_MuMu->SetMaximum(0.3);
	h_jet1_ttbb_ntag3_MuMu->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
	h_jet1_ttbb_ntag3_MuMu->GetYaxis()->SetTitle("Normalized Entries");
  	SetLegend(h_jet1_ttbb_ntag3_MuMu, h_jet1_ttjj_ntag3_MuMu);
	can2->cd();
	h_jet2_ttbb_ntag3_MuMu->Add(h_jet2_ttbb_ntag3_ElEl);
	h_jet2_ttbb_ntag3_MuMu->Add(h_jet2_ttbb_ntag3_MuEl);
	h_jet2_ttbb_ntag3_MuMu->Scale(1.0/(h_jet2_ttbb_ntag3_MuMu->Integral()+h_jet2_ttbb_ntag3_ElEl->Integral()+h_jet2_ttbb_ntag3_MuEl->Integral()));
	h_jet2_ttjj_ntag3_MuMu->Add(h_jet2_ttjj_ntag3_ElEl);
	h_jet2_ttjj_ntag3_MuMu->Add(h_jet2_ttjj_ntag3_MuEl);
	h_jet2_ttjj_ntag3_MuMu->Scale(1.0/(h_jet2_ttjj_ntag3_MuMu->Integral()+h_jet2_ttjj_ntag3_ElEl->Integral()+h_jet2_ttjj_ntag3_MuEl->Integral()));
	h_jet2_ttbb_ntag3_MuMu->Draw();
	h_jet2_ttjj_ntag3_MuMu->Draw("same");
	h_jet2_ttbb_ntag3_MuMu->SetStats(0);
	h_jet2_ttbb_ntag3_MuMu->SetMaximum(0.3);
	h_jet2_ttbb_ntag3_MuMu->SetTitle("second leading jet pt distibution");
	h_jet2_ttbb_ntag3_MuMu->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
	h_jet2_ttbb_ntag3_MuMu->GetYaxis()->SetTitle("Normalized Entries");
  	SetLegend(h_jet2_ttbb_ntag3_MuMu, h_jet2_ttjj_ntag3_MuMu);
	can3->cd();
	h_jet3_ttbb_ntag3_MuMu->Add(h_jet3_ttbb_ntag3_ElEl);
	h_jet3_ttbb_ntag3_MuMu->Add(h_jet3_ttbb_ntag3_MuEl);
	h_jet3_ttbb_ntag3_MuMu->Scale(1.0/(h_jet3_ttbb_ntag3_MuMu->Integral()+h_jet3_ttbb_ntag3_ElEl->Integral()+h_jet3_ttbb_ntag3_MuEl->Integral()));
	h_jet3_ttjj_ntag3_MuMu->Add(h_jet3_ttjj_ntag3_ElEl);
	h_jet3_ttjj_ntag3_MuMu->Add(h_jet3_ttjj_ntag3_MuEl);
	h_jet3_ttjj_ntag3_MuMu->Scale(1.0/(h_jet3_ttjj_ntag3_MuMu->Integral()+h_jet3_ttjj_ntag3_ElEl->Integral()+h_jet3_ttjj_ntag3_MuEl->Integral()));
	h_jet3_ttbb_ntag3_MuMu->Draw();
	h_jet3_ttjj_ntag3_MuMu->Draw("same");
	h_jet3_ttbb_ntag3_MuMu->SetStats(0);
	h_jet3_ttbb_ntag3_MuMu->SetMaximum(0.3);
	h_jet3_ttbb_ntag3_MuMu->SetTitle("third leading jet pt distibution");
	h_jet3_ttbb_ntag3_MuMu->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
	h_jet3_ttbb_ntag3_MuMu->GetYaxis()->SetTitle("Normalized Entries");
  	SetLegend(h_jet3_ttbb_ntag3_MuMu, h_jet3_ttjj_ntag3_MuMu);
	can4->cd();
	h_jet4_ttbb_ntag3_MuMu->Add(h_jet4_ttbb_ntag3_ElEl);
	h_jet4_ttbb_ntag3_MuMu->Add(h_jet4_ttbb_ntag3_MuEl);
	h_jet4_ttbb_ntag3_MuMu->Scale(1.0/(h_jet4_ttbb_ntag3_MuMu->Integral()+h_jet4_ttbb_ntag3_ElEl->Integral()+h_jet4_ttbb_ntag3_MuEl->Integral()));
	h_jet4_ttjj_ntag3_MuMu->Add(h_jet4_ttjj_ntag3_ElEl);
	h_jet4_ttjj_ntag3_MuMu->Add(h_jet4_ttjj_ntag3_MuEl);
	h_jet4_ttjj_ntag3_MuMu->Scale(1.0/(h_jet4_ttjj_ntag3_MuMu->Integral()+h_jet4_ttjj_ntag3_ElEl->Integral()+h_jet4_ttjj_ntag3_MuEl->Integral()));
	h_jet4_ttbb_ntag3_MuMu->Draw();
	h_jet4_ttjj_ntag3_MuMu->Draw("same");
	h_jet4_ttbb_ntag3_MuMu->SetStats(0);
	h_jet4_ttbb_ntag3_MuMu->SetMaximum(0.3);
	h_jet4_ttbb_ntag3_MuMu->SetTitle("fourth leading jet pt distibution");
	h_jet4_ttbb_ntag3_MuMu->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
	h_jet4_ttbb_ntag3_MuMu->GetYaxis()->SetTitle("Normalized Entries");
  	SetLegend(h_jet4_ttbb_ntag3_MuMu, h_jet4_ttjj_ntag3_MuMu);
	
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

