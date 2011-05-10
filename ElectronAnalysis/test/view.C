void view()
{
  gStyle->SetOptStat(111111);
  view("HZZVeryLoose");
  view("Default");
}

void view(TString dirName)
{
  TFile* f = TFile::Open("analyzeEleId.root");

  TTree* tree = (TTree*)f->Get(dirName+"/tree");

  TH1F* hGenPt = new TH1F(dirName+"_hGenPt", "Pt;p_{T} (GeV/c);Entries", 20, 0, 100);
  TH1F* hGsfPt = new TH1F(dirName+"_hGsfPt", "Pt;p_{T} (GeV/c);Entries", 20, 0, 100);
  TH1F* hPfaPt = new TH1F(dirName+"_hPfaPt", "Pt;p_{T} (GeV/c);Entries", 20, 0, 100);

  TH1F* hGenEta = new TH1F(dirName+"_hGenEta", "Eta;#eta;Entries", 20, -3.15, 3.15);
  TH1F* hGsfEta = new TH1F(dirName+"_hGsfEta", "Eta;#eta;Entries", 20, -3.15, 3.15);
  TH1F* hPfaEta = new TH1F(dirName+"_hPfaEta", "Eta;#eta;Entries", 20, -3.15, 3.15);

  TH1F* hGenPhi = new TH1F(dirName+"_hGenPhi", "Phi;#phi;Entries", 20, -3.15, 3.15);
  TH1F* hGsfPhi = new TH1F(dirName+"_hGsfPhi", "Phi;#phi;Entries", 20, -3.15, 3.15);
  TH1F* hPfaPhi = new TH1F(dirName+"_hPfaPhi", "Phi;#phi;Entries", 20, -3.15, 3.15);

  TH1F* hGsfPtRes = new TH1F(dirName+"_hGsfPtRes", "Pt Residual;#Deltap_{T}/p_{T}^{Gen};Entries", 50, -3, 3);
  TH1F* hPfaPtRes = new TH1F(dirName+"_hPfaPtRes", "Pt Residual;#Deltap_{T}/p_{T}^{Gen};Entries", 50, -3, 3);

  TH1F* hGsfMva = new TH1F(dirName+"_hGsfMva", "Mva;MVA;Entries", 100, -2, 1.5);
  TH1F* hPfaMva = new TH1F(dirName+"_hPfaMva", "Mva;MVA;Entries", 100, -2, 1.5);

  TH1F* hGsfEoverP = new TH1F(dirName+"_hGsfEoverP", "EoverP;E/P;Entries", 100, 0, 2);
  TH1F* hPfaEoverP = new TH1F(dirName+"_hPfaEoverP", "EoverP;E/P;Entries", 100, 0, 2);

  tree->Project(dirName+"_hGenPt", "genPt");
  tree->Project(dirName+"_hGsfPt", "gsfPt", "gsfPt>0");
  tree->Project(dirName+"_hPfaPt", "pfaPt", "pfaPt>0&&pfaMva>-999");

  tree->Project(dirName+"_hGenEta", "genEta", "genPt>0");
  tree->Project(dirName+"_hGsfEta", "gsfEta", "gsfPt>0");
  tree->Project(dirName+"_hPfaEta", "pfaEta", "pfaPt>0&&pfaMva>-999");

  tree->Project(dirName+"_hGenPhi", "genPhi", "genPt>0");
  tree->Project(dirName+"_hGsfPhi", "gsfPhi", "gsfPt>0");
  tree->Project(dirName+"_hPfaPhi", "pfaPhi", "pfaPt>0&&pfaMva>-999");

  tree->Project(dirName+"_hGsfPtRes", "(gsfPt-genPt)/genPt", "gsfPt>0&&genPt>0&&gsfMva>-999");
  tree->Project(dirName+"_hPfaPtRes", "(pfaPt-genPt)/genPt", "pfaPt>0&&genPt>0&&pfaMva>-999");

  tree->Project(dirName+"_hGsfMva", "gsfMva", "gsfPt>0");
  tree->Project(dirName+"_hPfaMva", "pfaMva", "pfaPt>0&&pfaMva>-999");

  tree->Project(dirName+"_hGsfEoverP", "gsfEcalE/gsfP", "gsfPt>0");
  tree->Project(dirName+"_hPfaEoverP", "pfaEcalE/pfaP", "pfaPt>0&&pfaMva>-999");
  //tree->Project(dirName+"_hGsfEoverP", "gsfEcalE/gsfP", "gsfPt>0&&gsfMva<-0.1");
  //tree->Project(dirName+"_hPfaEoverP", "pfaEcalE/pfaP", "pfaPt>0&&pfaMva>-999&&pfaMva<-0.1");

  tree->Scan("gsfPt:pfaPt:gsfEcalE:pfaEcalE:gsfMva:pfaMva:gsfToPfaMatch", "gsfPt>0 && gsfMva<-0.1 && gsfMva>-1e9");

  //overlay(dirName+"_Pt", hGenPt, hGsfPt, hPfaPt);
  //overlay(dirName+"_Eta", hGenEta, hGsfEta, hPfaEta);
  //overlay(dirName+"_Phi", hGenPhi, hGsfPhi, hPfaPhi);
  //overlay(dirName+"_Res", 0, hGsfPtRes, hPfaPtRes);
  overlay(dirName+"_Mva", 0, hGsfMva, hPfaMva, "log");
  overlay(dirName+"_EoverP", 0, hGsfEoverP, hPfaEoverP, "log");

}

void overlay(TString name, TH1* h1, TH1* h2, TH1* h3, TString opt = "")
{
  TCanvas* c = new TCanvas("c"+name, name, 600, 600);
  double ymin = 0;
  if ( opt.Contains("log") )
  {
    ymin = 0.5;
    c->SetLogy();
    opt.ReplaceAll("log", "");
  }

  double statPosY = 0.98;
  const double dY = 0.25;
  if ( h1 ) 
  {
    h1->SetLineColor(kBlack);
    h1->SetMinimum(ymin);
    h1->Draw(opt);

    c->Update();
    TPaveStats* st = (TPaveStats*)c->GetPrimitive("stats");
    if ( st )
    {
      st->SetName(h1->GetName());
      st->SetLineColor(h1->GetLineColor());
      st->SetY1NDC(statPosY-dY);
      st->SetY2NDC(statPosY);
      statPosY-=dY;
    }

    opt = "sames";
  }

  if ( h2 )
  {
    h2->SetLineColor(kRed);
    h2->SetMinimum(ymin);
    h2->Draw(opt);

    c->Update();
    TPaveStats* st = (TPaveStats*)c->GetPrimitive("stats");
    if ( st )
    {
      st->SetName(h2->GetName());
      st->SetLineColor(h2->GetLineColor());
      st->SetY1NDC(statPosY-dY);
      st->SetY2NDC(statPosY);
      statPosY-=dY;
    }

    opt = "sames";
  }

  if ( h3 )
  {
    h3->SetLineColor(kBlue);
    h3->SetMinimum(ymin);
    h3->Draw(opt);

    c->Update();
    TPaveStats* st = (TPaveStats*)c->GetPrimitive("stats");
    if ( st )
    {
      st->SetName(h3->GetName());
      st->SetLineColor(h3->GetLineColor());
      st->SetY1NDC(statPosY-dY);
      st->SetY2NDC(statPosY);
      statPosY-=dY;
    }

    opt = "sames";
  }

  c->Print(name+".png");
}

