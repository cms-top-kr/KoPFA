void singlePlot(TTree* tree1,  const TString& var, TCut& cut,  const TString& hName, const TString& xtitle,  const TString& ytitle,const TString& name, int nbin, double xlow, double xmax, double max, bool print){

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);

  tree1->Draw(Form("%s>>h_1_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"");

  h_1->SetStats(0);
  h_1->SetTitle(0);
  h_1->GetXaxis()->SetTitle(xtitle.Data());
  h_1->GetYaxis()->SetTitle(ytitle.Data());

  Print(c, dir, hName, name, print);

}

void plot(TTree* tree1, TTree* tree2, const TString& var, TCut& cut,  const TString& hName, const TString& xtitle,  const TString& ytitle,const TString& name, int nbin, double xlow, double xmax, double max, bool print){

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);
  TH1 *h_2 = new TH1D(Form("h_2_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);

  tree1->Draw(Form("%s>>h_1_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"");
  tree2->Draw(Form("%s>>h_2_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"same");

  h_1->Scale(1.0/h_1->Integral());
  h_2->Scale(1.0/h_2->Integral());

  h_1->SetMaximum(max);
  h_2->SetMaximum(max);

  StyleSimple(h_1, h_2, xtitle,ytitle);
  SetLegend(h_1, h_2, "no pile up", "pile up", "l", "l", 0.65,0.70,0.88,0.83);
  Print(c, dir, hName, name, print);

}

void normalized2Eventplot(TTree* tree1, TTree* tree2, const TString& var, TCut& cut,  const TString& hName, const TString& xtitle,  const TString& ytitle,const TString& name, int nbin, double xlow, double xmax, double max, bool print){

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);
  TH1 *h_2 = new TH1D(Form("h_2_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);

  tree1->Draw(Form("%s>>h_1_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"");
  tree2->Draw(Form("%s>>h_2_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"same");

  h_1->Scale(1.0/tree1->GetEntries());
  h_2->Scale(1.0/tree2->GetEntries());

  h_1->SetMaximum(max);
  h_2->SetMaximum(max);

  StyleSimple(h_1, h_2, xtitle,ytitle);
  SetLegend(h_1, h_2, "no pile up", "pile up", "l", "l", 0.60,0.65,0.85,0.80);
  Print(c, dir, hName, name, print);

}

void normalized2EventIsoplot(TTree* tree1, TTree* tree2, const TString& var, TCut& cut,  const TString& hName, const TString& xtitle,  const TString& ytitle,const TString& name, int nbin, double xlow, double xmax, double max, bool print){

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);
  TH1 *h_2 = new TH1D(Form("h_2_%s_%s",hName.Data(),name.Data()),"h",nbin,xlow,xmax);

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);

  tree2->Draw(Form("%s>>h_2_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"");
  tree1->Draw(Form("%s>>h_1_%s_%s",var.Data(),hName.Data(),name.Data()),cut,"psame");

  h_1->Scale(1.0/tree1->GetEntries());
  h_2->Scale(1.0/tree2->GetEntries());

  h_1->SetMaximum(max);
  h_2->SetMaximum(max);

  Style(h_1, h_2, xtitle, ytitle);
  SetLegend(h_1, h_2, "no pile up", "pile up", "p", "l", 0.60,0.65,0.85,0.80);
  Print(c, dir, hName, name, print);

}

void plotFromHist(TFile * file1, TFile * file2, const TString& hName, const TString& xtitle,  const TString& ytitle,const TString& name, double max, bool print){
  TH1F * h_1 = (TH1F *) file1->Get(Form("DiMuon/h_%s",hName.Data()));
  TH1F * h_2 = (TH1F *) file2->Get(Form("DiMuon/h_%s",hName.Data()));

  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);
  h_1->Draw();
  h_2->Draw("same");

  h_1->Scale(1.0/h_1->Integral());
  h_2->Scale(1.0/h_2->Integral());

  StyleSimple(h_1, h_2, "Jet Multiplicity","Normalized Entries");
  SetLegend(h_1, h_2, "no pile up", "pile up", "l", "l", 0.60,0.65,0.85,0.80);
  Print(c, dir, hName, name, print);
}

void plotEff(TH1* h_1, TH1* h_2, TString& hName, TString& name, TString& title,  int& nbin, const float* bins, double &p1, double &p2,  bool print){
  TCanvas* c_eff = new TCanvas(Form("c_eff_%s_%s",hName.Data(), name.Data()),Form("c_eff_%s_%s",hName.Data(), name.Data()),1);

  TGraphAsymmErrors *eff_1 = new TGraphAsymmErrors();
  TGraphAsymmErrors *eff_2 = new TGraphAsymmErrors();

  for(int i=1 ; i <= nbin ;i++ ){
    eff_1->SetPoint(i-1, h_1->GetBinCenter(i), h_1->Integral(1,i));
    eff_2->SetPoint(i-1, h_2->GetBinCenter(i), h_2->Integral(1,i));

    double eff1ErrHi = sigma( h_1->Integral(1,i),p1,1);
    double eff1ErrLo = sigma( h_1->Integral(1,i),p1,1);
    double eff2ErrHi = sigma( h_2->Integral(1,i),p2,1);
    double eff2ErrLo = sigma( h_2->Integral(1,i),p2,1);

    eff_1->SetPointEYhigh (i-1, eff1ErrHi );
    eff_1->SetPointEYlow (i-1, eff1ErrLo );
    eff_2->SetPointEYhigh (i-1, eff2ErrHi );
    eff_2->SetPointEYlow (i-1, eff2ErrLo );
  }

  TH1D *h = new TH1D(Form("h_%s_%s",hName.Data(),name.Data()),"h",nbin, bins);
  h->SetMinimum(0);
  h->SetMaximum(1.05);
  h->SetTitle("");
  h->SetStats(0);
  h->GetXaxis()->SetTitle(title.Data());
  h->GetYaxis()->SetTitle("Efficiency");
  h->Draw();

  Style2(eff_1, eff_2);
  SetLatex(0.40,0.65);
  SetLegend(eff_1, eff_2, leg1, leg2, "p", "p", 0.40,0.40,0.65,0.55);
  TString pre = "eff_";
  TString temp = pre + hName;
  Print(c_eff, dir, temp.Data(), name.Data(), print);

}

void plotRelCombined(TChain *tree1, TChain *tree2, int& nbin, const float* bins, TCut cut1, TCut cut2, double& p1, double& p2, bool print){

  TH1 *h_pt = new TH1F("h_pt","h_pt",100,0,100);
  tree2->Project("h_pt","pt",cut2);
  h_pt->Scale(1.0/p2);

  //TCanvas *c = new TCanvas("c_ptDep","c_ptDep",1); 
 // int nbin = 50;
 // double xlow = 0.0;
 // double xmax = 0.5;

  TH1 *h_temp = new TH1F("h_temp","h_temp",nbin,bins);
  //h_temp->Draw();
  h_temp->SetStats(0);
  h_temp->SetTitle(0);

  TH1 *h[10];
  TH1 *h_muon = new TH1F("h_muon","h_muon",nbin,bins);
  TH1 *h_final = new TH1F("h_final","h_final",nbin,bins);
  h_final->Sumw2();
  tree2->Project("h_muon","(chIso+nhIso+phIso)/pt",cut2);
  if(!obj1.Contains("random")){
    tree1->Project("h_final","(chIso+nhIso+phIso)/pt",cut1);
  }else( obj1.Contains("random")){
    cout << "Relative random sumpT calculation..." << endl;
    int i = 0;
    while( i < 10){
      TString s = int2string(i);
      h[i] = new TH1F(Form("h_%s",s.Data()),Form("h_%s",s.Data()),nbin,bins);
      h[i]->Sumw2();
      std::ostringstream cut;
      cut.str(std::string());
      int ptwidth = 10;
      float Pt = ptwidth/2 + i*ptwidth;
      tree1->Project(Form("h_%s",s.Data()),Form("(chIso+nhIso+phIso)/%f",Pt),cut1);
      //cout << cut.str() << ":" << " entries = " << h[i]->GetEntries() << endl;
      h[i]->SetLineColor(i+1);
      h[i]->SetLineWidth(3);
      h[i]->Scale(1.0/p1);
      double pdf = h_pt->Integral(i*ptwidth+1,i*ptwidth+ptwidth) ;
      double scaledentries = h[i]->GetEntries()*h_pt->Integral(i*ptwidth+1,i*ptwidth+ptwidth) ;
      //h[i]->Draw("same");
      h_final->Add(h[i],scaledentries);
      //cout << "h_final= " << h_final->GetEntries() << endl;
      i++;
    }
  }

  TCanvas *c2 = new TCanvas("c_rel_combined_sumpT","c_rel_combined_sumpT",1);
  c2->SetLogy();
  h_muon->Draw();
  h_final->Draw("same");
  //cout << "combined / pt= " << h_final->GetEntries() << endl;
  h_final->Scale(1.0/p1);
  h_muon->Scale(1.0/p2);

  Style(h_final, h_muon, "#Sigma pT/pT", "Probability");
  SetLatex(0.20,0.88);
  SetLegend(h_final, h_muon, leg1, leg2, "p", "l", 0.45,0.65,0.70,0.80);
  Print(c2, dir, "relative_combined", "sumpT", print);

  plotEff(h_final,h_muon, "rel", "combined", "#Sigma pT/pT", nbin, bins, p1, p2, print);
}

void plotAbsCombined(TChain *tree1, TChain *tree2, int& nbin, const float* bins, TCut cut1, TCut cut2, double& p1, double& p2, bool print){
  //int nbin = 40;
  //double xlow = 0.0;
 // double xmax = 4;
  TH1 *h_abs_1 = new TH1F("h_abs_1","h_abs_1",nbin,bins);
  TH1 *h_abs_2 = new TH1F("h_abs_2","h_abs_2",nbin,bins);
  h_abs_1->Sumw2();
  tree2->Project("h_abs_2","chIso+nhIso+phIso");
  tree1->Project("h_abs_1","chIso+nhIso+phIso");
  h_abs_1->Scale(1.0/p1);
  h_abs_2->Scale(1.0/p2);
  TCanvas *c = new TCanvas("c_abs_combined_sumpT","c_abs_combined_sumpT",1);
  c->SetLogy();
  h_abs_2->Draw();
  h_abs_1->Draw("same");
  Style(h_abs_1, h_abs_2, "#Sigma pT", "Probability");

  SetLatex(0.20,0.88);
  SetLegend(h_abs_1, h_abs_2, leg1, leg2, "p", "l", 0.45,0.65,0.70,0.80);
  Print(c, dir, "absolute_combined", "sumpT", print);

  plotEff(h_abs_1,h_abs_2, "abs", "combined", "#Sigma pT", nbin, bins, p1, p2, print);


}

void plotdNdR(TChain *tree_data, TChain *tree_mc, const TString &varRD, const TString &varMC, const TString& hName, const TString& xtitle, const TString& ytitle, int nbin, float xlow, float xmax, TCut cutRD, TCut cutMC, TString name, double &p1, double &p2, bool print){

  TH1 *h_data = new TH1D(Form("h_data_%s_%s",hName.Data(),name.Data()),"h_data",nbin,xlow,xmax);
  TH1 *h_mc = new TH1D(Form("h_mc_%s_%s",hName.Data(),name.Data()),"h_mc",nbin,xlow,xmax);
  h_data->Sumw2();
  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(),name.Data()),Form("c_%s_%s",hName.Data(),name.Data()),1);

  tree_mc->Draw(Form("%s>>h_mc_%s_%s",varMC.Data(),hName.Data(),name.Data()),cutMC,"");
  tree_data->Draw(Form("%s>>h_data_%s_%s",varRD.Data(),hName.Data(),name.Data()),cutRD,"Esame");

  h_data->Scale(1.0/p1/h_data->GetBinWidth(1));
  h_mc->Scale(1.0/p2/h_mc->GetBinWidth(1));
  h_mc->SetMaximum(7); // 2.5

  Style(h_data, h_mc, xtitle, ytitle);

  SetLatex2(0.20,0.88);
  SetLegend(h_data, h_mc, leg1, leg2, "p", "F", 0.20,0.67,0.45,0.82);
  Print(c, dir, hName, name, print);
}

void plotSumpT(TChain *tree1, TChain *tree2, const TString &var1, const TString &var2, const TString& hName, const TString& xtitle,  const TString& ytitle, int& nbin, const float* bins,  TCut cut1, TCut cut2, const TString& name, double& p1, double& p2, bool print){

  TH1 *h_1 = new TH1D(Form("h_1_%s_%s",hName.Data(),name.Data()),"h",nbin,bins);
  TH1 *h_2 = new TH1D(Form("h_2_%s_%s",hName.Data(),name.Data()),"h",nbin,bins);
  h_1->Sumw2();
  TCanvas* c = new TCanvas(Form("c_%s_%s",hName.Data(), name.Data()),Form("c_%s_%s",hName.Data(), name.Data()),1);
  gPad->SetLogy();

  tree2->Draw(Form("%s>>h_2_%s_%s",var2.Data(),hName.Data(),name.Data()),cut2,"");
  tree1->Draw(Form("%s>>h_1_%s_%s",var1.Data(),hName.Data(),name.Data()),cut1,"psame");

  h_1->SetMaximum(0.5);
  h_1->SetMinimum(0.0001);
  h_2->SetMaximum(0.5);
  h_2->SetMinimum(0.0001);

  h_1->Scale(1.0/p1);
  h_2->Scale(1.0/p2);

  Style(h_1, h_2, xtitle, ytitle);

  SetLatex(0.20,0.88);

  SetLegend(h_1, h_2, leg1, leg2, "p", "l", 0.45,0.65,0.70,0.80);
  Print(c, dir, hName, name, print);

  plotEff(h_1,h_2, hName,name, xtitle, nbin, bins,p1,p2, print);

}

