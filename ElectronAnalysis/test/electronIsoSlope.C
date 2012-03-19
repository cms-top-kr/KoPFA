TH1* getSlope(TH2* h2, TString name){
  int nbins = 30;
  TH1* out = new TH1F(Form("mean_%s",name.Data()),"mean",30,0,30);
  for(int i=1; i<=30; i++){
    TH1D *h = h2->ProjectionY(Form("py_%s",name.Data()),i,i);
    double mean = h->GetMean();
    out->SetBinContent(i,mean);
    cout << "mean " << "(" << i << ") = " << mean << endl; 
  }

  return out;
}

void electronIsoSlope(){
  //TFile* f_data = new TFile("batch/Out/ElEl/Res/vallot_newIso.root");
  TFile* f_data = new TFile("batch/Out/ElEl/Res/vallot_TTbarTuneZ2_newIso_filter.root");

  TTree* t_data = (TTree*)f_data->Get("eleOpt/tree");

  TH2 * h_puCharged = new TH2F("h_puCharged","h_puCharged",30, 0,30,50000,0.0,5000.0) ; 
  TH2 * h_puCharged1 = (TH2F*) h_puCharged->Clone("h_puCharged1");
  TH2 * h_puCharged2 = (TH2F*) h_puCharged->Clone("h_puCharged2");
  TH2 * h_charged = new TH2F("h_charged","h_charged",30, 0,30,50000,0.0,5000.0) ;                     
  TH2 * h_charged1 = (TH2F*) h_charged->Clone("h_charged1");
  TH2 * h_charged2 = (TH2F*) h_charged->Clone("h_charged2");
  TH2 * h_neutral = new TH2F("h_neutral","h_neutral",30, 0,30,50000,0.0,5000.0) ;      
  TH2 * h_neutral1 = (TH2F*) h_neutral->Clone("h_neutral1");
  TH2 * h_neutral2 = (TH2F*) h_neutral->Clone("h_neutral2");
  TH2 * h_corrneutral = new TH2F("h_corrneutral","h_corrneutral",30, 0,30,50000,-5.0,5000.0) ;
  TH2 * h_corrneutral1 = (TH2F*) h_corrneutral->Clone("h_corrneutral1");
  TH2 * h_corrneutral2 = (TH2F*) h_corrneutral->Clone("h_corrneutral2");
  TH2 * h_overcorrneutral = new TH2F("h_overcorrneutral","h_overcorrneutral",30, 0,30,10000,0.0,1000.0) ;
  TH2 * h_overcorrneutral1 = (TH2F*) h_overcorrneutral->Clone("h_overcorrneutral1");
  TH2 * h_overcorrneutral2 = (TH2F*) h_overcorrneutral->Clone("h_overcorrneutral2");
 
  //TCut acceptance = "abs(ele1_eta) < 1.49 || abs(ele2_eta) < 1.49";
  TCut acceptance;
//  TCut acceptance1 = "ele2_mva > 0.0 && ele2_relIso < 0.05 && dimass > 70 && dimass < 110" + acceptance;// && ele1_charge*ele2_charge < 0" ;
//  TCut acceptance2 = "ele1_mva > 0.0 && ele1_relIso < 0.05 && dimass > 70 && dimass < 110" + acceptance;// && ele1_charge*ele2_charge < 0" ;
  TCut acceptance1 = "ele1_mva > 0.0 && ele1_isFromW == 1";
  TCut acceptance2 = "ele2_mva > 0.0 && ele2_isFromW == 1";

  //TCut acceptance1 = "dimass > 80 && dimass < 100" + acceptance;
  //TCut acceptance2 = "dimass > 80 && dimass < 100" + acceptance;
 
  //TCut acceptance = " (dimass < 70 || dimass > 110) && ele1_charge*ele2_charge > 0" ;
  //TCut acceptance = "dimass < 50 && ele1_charge*ele2_charge > 0";

  t_data->Project("h_puCharged1","ele1_puChIso:nVertex", acceptance1);
  t_data->Project("h_puCharged2","ele2_puChIso:nVertex", acceptance2);
  h_puCharged = h_puCharged1;
  h_puCharged->Add(h_puCharged2);

  t_data->Project("h_charged1","ele1_chIso:nVertex", acceptance1);
  t_data->Project("h_charged2","ele2_chIso:nVertex", acceptance2);
  h_charged = h_charged1;
  h_charged->Add(h_charged2);

  t_data->Project("h_neutral1","(ele1_nhIso+ele1_phIso):nVertex", acceptance1);
  t_data->Project("h_neutral2","(ele2_nhIso+ele2_phIso):nVertex", acceptance2); 
  h_neutral = h_neutral1;
  h_neutral->Add(h_neutral2);

  t_data->Project("h_corrneutral1","(ele1_nhIso+ele1_phIso-0.5*ele1_puChIso):nVertex", acceptance1);
  t_data->Project("h_corrneutral2","(ele2_nhIso+ele2_phIso-0.5*ele2_puChIso):nVertex", acceptance2);
  h_corrneutral = h_corrneutral1;
  h_corrneutral->Add(h_corrneutral2);

  t_data->Project("h_overcorrneutral1","min(0.0, ele1_nhIso+ele1_phIso-0.5*ele1_puChIso):nVertex", acceptance1);
  t_data->Project("h_overcorrneutral2","min(0.0, ele2_nhIso+ele2_phIso-0.5*ele2_puChIso):nVertex", acceptance2);
  h_overcorrneutral = h_overcorrneutral1;
  h_overcorrneutral->Add(h_overcorrneutral2);

  TH1* h_chSlope = getSlope(h_charged,"charged");
  TH1* h_puSlope = getSlope(h_puCharged,"puCharged");
  TH1* h_neSlope = getSlope(h_neutral,"neutral");
  TH1* h_corrneSlope = getSlope(h_corrneutral,"corrneutral");
  TH1* h_overcorrneSlope = getSlope(h_overcorrneutral,"overcorrneutral");
 
  TF1 *fun = new TF1( "fun", "[0]*x+[1]", 0, 30);
  h_puSlope->Fit(fun,"","",1,25);
  h_neSlope->Fit(fun,"","",1,25);
  //h_overcorrneSlope->Fit(fun);
 
  TCanvas* c = new TCanvas("c","c",1);
  h_neSlope->SetTitle("");
  h_neSlope->SetStats(0);
  gStyle->SetOptFit(0);
  h_neSlope->GetYaxis()->SetTitle("<Isolation> (GeV)");
  h_neSlope->GetXaxis()->SetTitle("Number of Reconstructed Vertices");
  h_neSlope->SetMaximum(10);
  //h_chSlope->SetMinimum(-3);
  h_neSlope->Draw("p");
  h_chSlope->Draw("samep");
  h_puSlope->Draw("samep");
  h_neSlope->SetMarkerColor(4);
  h_neSlope->SetMarkerStyle(20);
  h_neSlope->SetMarkerSize(1);
  h_chSlope->SetMarkerColor(3);
  h_chSlope->SetMarkerStyle(20);
  h_chSlope->SetMarkerSize(1);
  h_puSlope->SetMarkerColor(2);
  h_puSlope->SetMarkerStyle(20);
  h_puSlope->SetMarkerSize(1);

  h_corrneSlope->Draw("samep");
  h_corrneSlope->SetMarkerColor(4);
  h_corrneSlope->SetMarkerStyle(24);
  h_corrneSlope->SetMarkerSize(1);

  //h_overcorrneSlope->Draw("samep");
  //h_overcorrneSlope->SetMarkerColor(2);
  //h_overcorrneSlope->SetMarkerStyle(25);
  //h_overcorrneSlope->SetMarkerSize(1);

  TLegend *l = new TLegend(0.2,0.65,0.4,0.85);
  l->AddEntry(h_puSlope,"pileup charged hadron","P");
  l->AddEntry(h_chSlope,"charged hadron","P");
  l->AddEntry(h_neSlope,"neutral particle","P");
  l->AddEntry(h_corrneSlope,"neutral particle with #Delta #beta","P");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  c->Print("c_isolation_slope.eps");
}
