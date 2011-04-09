void draw(TTree * t2010, TTree * t2011, TString & type, TString & var, TString &ytitle, TString &xtitle, int nbins, double min, double max, TCut cut, double scale, double ymax, double labelx = 0.18 , double labely = 0.87, bool logscale = false, double lx1=0.63,double ly1=0.72,double lx2=0.88, double ly2=0.88 ){

  TCanvas * c = new TCanvas(Form("c%s",type.Data()),Form("c%s",type.Data()),1);
  if(logscale){
    c->SetLogy();
  }

  TH1* h_2010 = new TH1F(Form("h_2010_%s",type.Data()),"h_2010",nbins,min,max); 
  TH1* h_2011 = new TH1F(Form("h_2011_%s",type.Data()),"h_2011",nbins,min,max); 

  t2010->Project(Form("h_2010_%s",type.Data()),Form("%s",var.Data()),cut);
  t2011->Project(Form("h_2011_%s",type.Data()),Form("%s",var.Data()),cut);

  h_2010->SetTitle(0);
  h_2010->SetStats(0);
  h_2010->GetXaxis()->SetTitle(xtitle.Data());
  h_2010->GetYaxis()->SetTitle(ytitle.Data());
  h_2010->Draw();
  h_2010->SetFillColor(2);
  h_2010->Scale(scale);
  h_2010->SetMaximum(ymax);
  h_2010->AddBinContent(nbins, h_2010->GetBinContent(nbins+1));

  h_2011->Draw("Same");
  h_2011->Sumw2();
  h_2011->SetMarkerStyle(20);
  h_2011->SetMarkerSize(1);
  h_2011->AddBinContent(nbins, h_2011->GetBinContent(nbins+1));

  TLegend *l= new TLegend(lx1,ly1,lx2,ly2);
  l->AddEntry(h_2011,"2011 Data","p");
  l->AddEntry(h_2010,"2010 Data","f");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  TLatex *label= new TLatex;
  label->SetNDC();
  label->SetTextSize(0.04);
  label->DrawLatex(labelx,labely,"#sqrt{s} = 7 TeV,22 pb^{-1}");

  c->Print(Form("c_%s.pdf",type.Data()));
  c->Print(Form("c_%s.eps",type.Data()));
  c->Print(Form("c_%s.png",type.Data()));
}

void compare(){
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  TFile * f2010 = new TFile("vallot_run2010.root");
  TFile * f2011 = new TFile("vallot_run2011a.root");

  TTree * t2010 = (TTree *) f2010->Get("MuMu/tree");
  TTree * t2011 = (TTree *) f2011->Get("MuMu/tree");
  TTree * t2010vtx = (TTree *) f2010->Get("VertexFilter/tree");
  TTree * t2011vtx = (TTree *) f2011->Get("VertexFilter/tree");


  
  TCut Zveto = "abs(Z.mass() - 91) > 15";
  TCut twojet = "@jetspt30.size() >= 2";
  TCut metcut = "MET > 30";
  TCut onebjet = "@bjets.size() >= 1";
  TCut iso = "(chIso1+nhIso1+phIso1)/Z.leg1().pt() < 0.21 && (chIso2+nhIso2+phIso2)/Z.leg2().pt() < 0.21";
  TCut opp = "Z.sign() < 0";
  TCut lowmass = "Z.mass() > 12";
  TCut pre;
  TCut cut3 = lowmass && iso && opp;
  TCut cut4 = cut3 && Zveto; 
  TCut cut5 = cut4 && twojet;
  TCut cut6 = cut5 && metcut;
  TCut cut7 = cut6 && onebjet;

  double scale = 22.0/36.0;

  //draw(t2010vtx, t2011vtx, "Vertex","multiplicity","Events","Vertex Multiplicity", 15, 0, 15,pre,scale,15000, 0.38, 0.87, true);

  //iso
  //draw(t2010, t2011, "Iso04lep1","relIso04lep1","Events","relIso", 20, 0, 0.4,pre,scale,15000, 0.38, 0.87, true);
  //draw(t2010, t2011, "Iso03lep1","relIso03lep1","Events","relIso", 20, 0, 0.4,pre,scale,15000, 0.38, 0.87, true);
  draw(t2010, t2011, "chIso1","chIso1","Events/0.2 GeV","Charged Hadron #Sigma p_{T} (GeV)", 20, 0, 4,pre,scale,15000, 0.38, 0.87, true);
  draw(t2010, t2011, "nhIso1","nhIso1","Events/0.2 GeV","Neutral Hadron #Sigma p_{T} (GeV)", 20, 0, 4,pre,scale,15000, 0.38, 0.87, true);
  draw(t2010, t2011, "phIso1","phIso1","Events/0.2 GeV","Photon #Sigma p_{T} (GeV)", 20, 0, 4,pre,scale,15000, 0.38, 0.87, true);

  //draw(t2010, t2011, "Iso04lep2","relIso04lep2","Events","relIso", 20, 0, 0.4,pre,scale,15000, 0.38, 0.87, true);
  //draw(t2010, t2011, "Iso03lep2","relIso03lep2","Events","relIso", 20, 0, 0.4,pre,scale,15000, 0.38, 0.87, true);
  //draw(t2010, t2011, "chIso2","chIso2","Events","chIso", 20, 0, 4,pre,scale,15000, 0.38, 0.87, true);
  //draw(t2010, t2011, "nhIso2","nhIso2","Events","nhIso", 20, 0, 4,pre,scale,15000, 0.38, 0.87, true);
  //draw(t2010, t2011, "phIso2","phIso2","Events","phIso", 20, 0, 4,pre,scale,15000, 0.38, 0.87, true);

  //step3
  //draw(t2010, t2011, "Zmass","Z.mass()","Events","Dilepton Mass (GeV/c^{2})", 40,0,200,cut3,scale,10000, 0.18, 0.87, true);
  //draw(t2010, t2011, "ZDeltaR","Z.deltaR()","Events","#DeltaR", 30,0,6,cut3,scale,10000, 0.18, 0.87, true,0.68,0.72,0.93,0.88);
  //draw(t2010, t2011, "ZDeltaPhi","abs(Z.deltaPhi())","Events","#Delta#Phi", 35,0,3.5,cut3,scale,10000, 0.18, 0.87, true,0.33,0.72,0.58,0.88);
  //draw(t2010, t2011, "MET","MET","Events","Missing E_{T} (GeV)", 10, 0, 100,cut3,scale,10000, 0.38, 0.87, true);
  //draw(t2010, t2011, "sumET","sumEt","Events/20 GeV","#Sigma E_{T} (GeV)", 50, 0, 1000,cut3,scale,10000, 0.38, 0.87, true);
  //draw(t2010, t2011, "photonET","photonEt","Events/5 GeV","Photon #Sigma E_{T} (GeV)", 40, 0, 200,cut3,scale,10000, 0.38, 0.87, true);
  //draw(t2010, t2011, "chargedET","chargedHadronEt","Events/5 GeV","Charged Hadron #Sigma E_{T} (GeV)", 40, 0, 200,cut3,scale,10000, 0.38, 0.87, true);
  //draw(t2010, t2011, "neutralET","neutralHadronEt","Events/5 GeV","Neutral Hadron #Sigma E_{T} (GeV)", 40, 0, 200,cut3,scale,10000, 0.38, 0.87, true);
  //draw(t2010, t2011, "nJets","@jetspt30.size()","Events","Jet Multiplicity", 5, 0, 5,cut3,scale,15000, 0.38, 0.87, true);
 
  //step3 + two jets
  //draw(t2010, t2011, "HT","Z.leg1().pt()+Z.leg2().pt()+jetspt30[0].pt() + jetspt30[1].pt() + MET","Events","H_{T} (GeV)", 40,0,1000,cut3 && twojet,scale, 100, 0.18, 0.87, true);

  //step6
  //draw(t2010, t2011, "vsumM","vsumttbarM","Events","t#bar{t} invariant mass", 20, 0, 1000,cut6,scale,10, 0.38, 0.87, false);

}

