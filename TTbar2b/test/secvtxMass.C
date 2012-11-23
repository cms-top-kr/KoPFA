void secvtxMass(){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TFile * f = new TFile("/afs/cern.ch/work/y/youngjo/public/For8Tev/v20121120/vallot_TTbarFullLepMGDecays.root");

  TH1F* h_secvtx_ttbb[3][4];
  TH1F* h_secvtx_ttcc[3][4];
  TH1F* h_secvtx_ttLF[3][4];

  TH1F* h_flavor_ttbb[3][4];
  TH1F* h_flavor_ttcc[3][4];
  TH1F* h_flavor_ttLF[3][4];

  TH1F* h_topdecay_ttbb[3][4];
  TH1F* h_topdecay_ttcc[3][4];
  TH1F* h_topdecay_ttLF[3][4];

  for(int i=0; i < 3; i++){
    for(int j=0; j < 4; j++){
      h_secvtx_ttbb[i][j] = new TH1F(Form("h_secvtx_ttbb_%i_%i",i,j),"h_secvtx_ttbb",12,0.001,6.001);
      h_secvtx_ttcc[i][j] = new TH1F(Form("h_secvtx_ttcc_%i_%i",i,j),"h_secvtx_ttcc",12,0.001,6.001);
      h_secvtx_ttLF[i][j] = new TH1F(Form("h_secvtx_ttLF_%i_%i",i,j),"h_secvtx_ttLF",12,0.001,6.001);
      h_flavor_ttbb[i][j] = new TH1F(Form("h_flavor_ttbb_%i_%i",i,j),"h_flavor_ttbb",23,0,23);
      h_flavor_ttcc[i][j] = new TH1F(Form("h_flavor_ttcc_%i_%i",i,j),"h_flavor_ttcc",23,0,23);
      h_flavor_ttLF[i][j] = new TH1F(Form("h_flavor_ttLF_%i_%i",i,j),"h_flavor_ttLF",23,0,23); 
      h_topdecay_ttbb[i][j] = new TH1F(Form("h_topdecay_ttbb_%i_%i",i,j),"h_topdecay_ttbb",12,-10,2);
      h_topdecay_ttcc[i][j] = new TH1F(Form("h_topdecay_ttcc_%i_%i",i,j),"h_topdecay_ttcc",12,-10,2);
      h_topdecay_ttLF[i][j] = new TH1F(Form("h_topdecay_ttLF_%i_%i",i,j),"h_topdecay_ttLF",12,-10,2);       
    }
  }

  TCut visible = "ttbarGen.NJets20() >= 4 && ttbarGen.NbJets20() >=2 && ttbarGen.lepton1().pt() > 20 && ttbarGen.lepton2().pt() > 20 && abs(ttbarGen.lepton1().eta()) < 2.5 && abs(ttbarGen.lepton2().eta()) < 2.5" ;
  TCut ttbb = "ttbarGen.NbJets20() >= 4";
  TCut ttcc = "ttbarGen.NcJets20() >= 2";
  TCut reco = "nJet30 >= 4";

  TString id1 = "ttbarKin.jid(0)";
  TString id2 = "ttbarKin.jid(1)";

  for(int j = 0; j < 3 ; j++){ 

    TString decaymode = "";
    if( j == 0 ) decaymode = "MuEl";
    if( j == 1 ) decaymode = "MuMu";
    if( j == 2 ) decaymode = "ElEl";

    TTree * t = (TTree* ) f->Get(Form("%s/tree", decaymode.Data()) );

    t->Project(Form("h_secvtx_ttbb_0_%i",j), Form("jets[%s].secvtxMass()",id1.Data()),reco+ visible + ttbb);
    t->Project(Form("h_secvtx_ttbb_1_%i",j), Form("jets[%s].secvtxMass()",id2.Data()),reco + visible + ttbb);
    t->Project(Form("h_secvtx_ttcc_0_%i",j), Form("jets[%s].secvtxMass()",id1.Data()),reco + visible + !ttbb + ttcc);
    t->Project(Form("h_secvtx_ttcc_1_%i",j), Form("jets[%s].secvtxMass()",id2.Data()),reco + visible + !ttbb + ttcc);
    t->Project(Form("h_secvtx_ttLF_0_%i",j), Form("jets[%s].secvtxMass()",id1.Data()),reco + visible + !ttbb + !ttcc);
    t->Project(Form("h_secvtx_ttLF_1_%i",j), Form("jets[%s].secvtxMass()",id2.Data()),reco + visible + !ttbb + !ttcc);

    t->Project(Form("h_flavor_ttbb_0_%i",j), Form("abs(jets[%s].flavor())",id1.Data()),reco+ visible + ttbb);
    t->Project(Form("h_flavor_ttbb_1_%i",j), Form("abs(jets[%s].flavor())",id2.Data()),reco + visible + ttbb);
    t->Project(Form("h_flavor_ttcc_0_%i",j), Form("abs(jets[%s].flavor())",id1.Data()),reco + visible + !ttbb + ttcc);
    t->Project(Form("h_flavor_ttcc_1_%i",j), Form("abs(jets[%s].flavor())",id2.Data()),reco + visible + !ttbb + ttcc);
    t->Project(Form("h_flavor_ttLF_0_%i",j), Form("abs(jets[%s].flavor())",id1.Data()),reco + visible + !ttbb + !ttcc);
    t->Project(Form("h_flavor_ttLF_1_%i",j), Form("abs(jets[%s].flavor())",id2.Data()),reco + visible + !ttbb + !ttcc);

    t->Project(Form("h_topdecay_ttbb_0_%i",j), Form("jets[%s].topdecay()",id1.Data()),reco + visible + ttbb);
    t->Project(Form("h_topdecay_ttbb_1_%i",j), Form("jets[%s].topdecay()",id2.Data()),reco + visible + ttbb);
    t->Project(Form("h_topdecay_ttcc_0_%i",j), Form("jets[%s].topdecay()",id1.Data()),reco + visible + !ttbb + ttcc);
    t->Project(Form("h_topdecay_ttcc_1_%i",j), Form("jets[%s].topdecay()",id2.Data()),reco + visible + !ttbb + ttcc);
    t->Project(Form("h_topdecay_ttLF_0_%i",j), Form("jets[%s].topdecay()",id1.Data()),reco + visible + !ttbb + !ttcc);
    t->Project(Form("h_topdecay_ttLF_1_%i",j), Form("jets[%s].topdecay()",id2.Data()),reco + visible + !ttbb + !ttcc);

    h_secvtx_ttbb[2][3]->Add(h_secvtx_ttbb[0][j]);
    h_secvtx_ttbb[2][3]->Add(h_secvtx_ttbb[1][j]);
    h_secvtx_ttcc[2][3]->Add(h_secvtx_ttcc[0][j]);
    h_secvtx_ttcc[2][3]->Add(h_secvtx_ttcc[1][j]);
    h_secvtx_ttLF[2][3]->Add(h_secvtx_ttLF[0][j]);
    h_secvtx_ttLF[2][3]->Add(h_secvtx_ttLF[1][j]);

    h_flavor_ttbb[2][3]->Add(h_flavor_ttbb[0][j]);
    h_flavor_ttbb[2][3]->Add(h_flavor_ttbb[1][j]);
    h_flavor_ttcc[2][3]->Add(h_flavor_ttcc[0][j]);
    h_flavor_ttcc[2][3]->Add(h_flavor_ttcc[1][j]);
    h_flavor_ttLF[2][3]->Add(h_flavor_ttLF[0][j]);
    h_flavor_ttLF[2][3]->Add(h_flavor_ttLF[1][j]);

    h_topdecay_ttbb[2][3]->Add(h_topdecay_ttbb[0][j]);
    h_topdecay_ttbb[2][3]->Add(h_topdecay_ttbb[1][j]);
    h_topdecay_ttcc[2][3]->Add(h_topdecay_ttcc[0][j]);
    h_topdecay_ttcc[2][3]->Add(h_topdecay_ttcc[1][j]);
    h_topdecay_ttLF[2][3]->Add(h_topdecay_ttLF[0][j]);
    h_topdecay_ttLF[2][3]->Add(h_topdecay_ttLF[1][j]);

  }
  
  DrawPlot( h_topdecay_ttbb[2][3], h_topdecay_ttcc[2][3], h_topdecay_ttLF[2][3],"c_topdecay", "Decay category","Normalized Entries", 1.0);
  DrawPlot( h_secvtx_ttbb[2][3],   h_secvtx_ttcc[2][3],   h_secvtx_ttLF[2][3],  "c_secvtx", "Secondary Vertex Mass","Normalized Entries", 0.4);
  DrawPlot( h_flavor_ttbb[2][3],   h_flavor_ttcc[2][3],   h_flavor_ttLF[2][3],  "c_flavor", "Jet Flavor","Normalized Entries", 0.7);

}

void DrawPlot(TH1F* h_ttbb, TH1F* h_ttcc, TH1F* h_ttLF, TString name, TString xtitle, TString ytitle, double max){

  TCanvas * c = new TCanvas(Form("%s",name.Data()),Form("%s",name.Data()),500,500);
  double s_ttbb = h_ttbb->Integral();
  double s_ttcc = h_ttcc->Integral();
  double s_ttLF = h_ttLF->Integral();
  h_ttbb->Scale(1.0/s_ttbb);
  h_ttcc->Scale(1.0/s_ttcc);
  h_ttLF->Scale(1.0/s_ttLF);
  SetStyle(h_ttbb, xtitle, ytitle,2, max);
  SetStyle(h_ttcc, xtitle, ytitle,3, max);
  SetStyle(h_ttLF, xtitle, ytitle,4, max);
  h_ttbb->Draw("Hist");
  h_ttcc->Draw("sameHist");
  h_ttLF->Draw("sameHist");
  SetLegend(h_ttbb, h_ttcc, h_ttLF);
  c->Print(Form("%s.eps",name.Data()));

}

void SetStyle( TH1F* h1, TString xtitle, TString ytitle, int col, double max = 0.3){
  h1->SetLineColor(col);
  h1->SetLineWidth(0.4);
  h1->SetStats(0);
  h1->SetMaximum(max);
  h1->SetTitle("");
  h1->GetYaxis()->SetTitle(ytitle);
  h1->GetXaxis()->SetTitle(xtitle);
}

void SetLegend( TH1F* h1, TH1F* h2, TH1F* h3){

  TLegend *l = new TLegend(0.65,0.70,0.88,0.88);
  l->AddEntry(h1,"t#bar{t} + b#bar{b}","L");
  l->AddEntry(h2,"t#bar{t} + c#bar{c}","L");
  l->AddEntry(h3,"t#bar{t} + LF","L");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

}



