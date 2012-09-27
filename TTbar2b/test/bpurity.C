void bpurity(){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  TFile* f1 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v3/vallot_TTbarTuneZ2.root");
  TFile* f2 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v3/vallot_TTbarTuneZ2.root");
  TFile* f3 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v3/vallot_TTbarTuneZ2.root");

  TTree* treeMuMu = (TTree*)f1->Get("MuMu/tree");
  TTree* treeElEl = (TTree*)f2->Get("ElEl/tree");
  TTree* treeMuEl = (TTree*)f3->Get("MuEl/tree");

  TH2F* h2_mm = new TH2F("h2_mm","h2_mm",1000,0,1,25,0,25);
  TH2F* h2_ee = new TH2F("h2_ee","h2_ee",1000,0,1,25,0,25);
  TH2F* h2_em = new TH2F("h2_em","h2_em",1000,0,1,25,0,25);
  TH2F* h2 = new TH2F("h2","h2",100,0,1,25,0,25);

  TH1F* h_mm = new TH1F("h_mm","h_mm",25,0,25);
  TH1F* h_ee = new TH1F("h_ee","h_ee",25,0,25);
  TH1F* h_em = new TH1F("h_em","h_em",25,0,25);
  TH1F* h = new TH1F("h","h",25,0,25);

  //treeMuMu->Project("h2_mm","abs(jetspt30flavor):jetspt30bDiscriminator","ttbarGen.NbJets20() >= 4 && nJet30 >=4 && nbjets30_CSVM >= 2");
  //treeElEl->Project("h2_ee","abs(jetspt30flavor):jetspt30bDiscriminator","ttbarGen.NbJets20() >= 4 && nJet30 >=4 && nbjets30_CSVM >= 2");
  //treeMuEl->Project("h2_em","abs(jetspt30flavor):jetspt30bDiscriminator","ttbarGen.NbJets20() >= 4 && nJet30 >=4 && nbjets30_CSVM >= 2");

  //h2->Add(h2_mm);
  //h2->Add(h2_ee);
  //h2->Add(h2_em);

  //TCanvas * c2= new TCanvas("c2","c2",1);
  //h2->SetTitle("");
  //h2->GetXaxis()->SetTitle("b-Jet multiplicity (CSVM)");
  //h2->GetYaxis()->SetTitle("b-Jet multiplicity (CSVT)");
  //h2->Draw("Textcolz");
 
  treeMuMu->Project("h_mm","abs(jetspt30flavor)","jetspt30bDiscriminator > 0.679 && ttbarGen.NbJets20() >= 4 && nJet30 >=4 && nbjets30_CSVM >= 2"); 
  treeElEl->Project("h_ee","abs(jetspt30flavor)","jetspt30bDiscriminator > 0.679 && ttbarGen.NbJets20() >= 4 && nJet30 >=4 && nbjets30_CSVM >= 2"); 
  treeMuEl->Project("h_em","abs(jetspt30flavor)","jetspt30bDiscriminator > 0.679 && ttbarGen.NbJets20() >= 4 && nJet30 >=4 && nbjets30_CSVM >= 2"); 

  h->Add(h_mm);
  h->Add(h_ee);
  h->Add(h_em);

  double total = h->Integral();
  double nb = h->GetBinContent(6);

  double fraction = (total - nb)/total;
  TCanvas * c= new TCanvas("c","c",1);
  h->SetTitle("");
  h->GetXaxis()->SetTitle("Jet Entries");
  h->GetYaxis()->SetTitle("flavor");
  h->Draw();

  cout << "total= " << total << " b= " << nb << " fraction= " << fraction << endl;

}
