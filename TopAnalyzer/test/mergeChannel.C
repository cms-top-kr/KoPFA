void mergeChannel (TString filename, TString step, TString histname, bool logscale=true, float hmax=0, float hmin=0.02)
{

  TFile *_file0 = TFile::Open(filename);

  TString channel = TString("");
  //channel = TString("Events with ee/#mu#mu/e#mu");
  if(filename=="ElEl.root") channel = TString("Events with ee");
  else if(filename=="MuMu.root") channel = TString("Events with #mu#mu");
  else if(filename=="MuEl.root") channel = TString("Events with e#mu");

  TString lumi = "35";
  lumi = "36.1";

  TString title[3];
  title[0] = TString("CMS Preliminary");
  title[1] = TString(lumi) + TString(" pb^{-1} at  #sqrt{s} = 7 TeV");
  if(channel!="NULL") title[2] = TString(channel);

  TPaveText *pt = new TPaveText(0.18,0.74,0.18,0.88,"brNDC");
  pt->SetBorderSize(1);
  pt->SetTextFont(42);
  pt->SetTextSize(0.04);
  pt->SetLineColor(0);
  pt->SetLineStyle(1);
  pt->SetLineWidth(1);
  pt->SetFillColor(0);
  pt->SetFillStyle(1001);
  pt->SetTextAlign(12);
  pt->AddText(title[0]);
  pt->AddText(title[1]); 
  pt->AddText(title[2]);

  const int n = 6;
 
  TString hist = TString("_Step_")+ TString(step) + TString("_") + TString(histname);
  TString data = TString("hData") + TString(hist);
  TString mc[n];
  mc[0] = TString("hMCSig_TTbar") + TString(hist);
  mc[1] = TString("hMC_Wl") + TString(hist);
  mc[2] = TString("hMC_VV") + TString(hist);
  mc[3] = TString("hMC_SingleTop") + TString(hist);
  mc[4] = TString("hMC_DYtt") + TString(hist);
  mc[5] = TString("hMC_DYll") + TString(hist);

  TString legMc[n];
  legMc[0] = TString("t#bar{t}");
  legMc[1] = TString("W #rightarrow l#nu");
  legMc[2] = TString("Dibosons");
  legMc[3] = TString("Single top");
  legMc[4] = TString("Z/#gamma* #rightarrow #tau#tau");
  legMc[5] = TString("Z/#gamma* #rightarrow ll");

  TH1F* hData = (TH1F*)(gROOT->FindObject(data));
  if(histname=="toptotal") hData->GetXaxis()->SetTitle("t#bar{t} invariant mass");
  if(histname=="nJet" || histname=="nJetlog") {
    TAxis *xaxis = hData->GetXaxis();
    xaxis->SetNdivisions(-414);
    for(int i=1; i<=xaxis->GetNbins(); ++i) {
      xaxis->SetBinLabel(i,Form("%i",i-1));
      if(i==xaxis->GetNbins()) xaxis->SetBinLabel(i,Form("#geq%i",i-1));     
    }
  }
  //hData->GetXaxis()->SetTitleOffset(0.8);
  //hData->GetYaxis()->SetTitleOffset(0.8);

  Int_t nData = hData->GetEntries();
  Int_t nMcTotal = 0;
  Int_t nMc[n];
  TH1F* hMc[n];
  THStack *hStack = new THStack("hStack",TString("MC")+hist);
  for(int i=0; i<n; ++i) {
    hMc[i] = (TH1F*)(gROOT->FindObject(mc[i]));
    nMc[i] = hMc[i]->GetEntries();
    nMcTotal += nMc[i];
    cout << "MC type " << i << ": " << Form("%25s",mc[i].Data()) << ", Entries = " << Form("%10d",nMc[i]) << endl;
    hMc[i]->SetTitle("");
    //hMc[i]->GetXaxis()->SetTitleOffset(1.3);
    //hMc[i]->GetYaxis()->SetTitleOffset(1.3);
    hMc[i]->SetStats(0);
    
    hStack->Add(hMc[i]);
  }
  cout << "----------------------------------------------------------- " << endl;
  cout << "MC total before normalization                 = " << Form("%10d",nMcTotal) << endl;
  cout << "Data                                          = " << Form("%10d",nData) << endl << endl;

  TCanvas *c1 = new TCanvas("c1","c1",1);
  c1->Divide(2,3);
  for(int i=0; i<n; ++i) {
    c1->cd(i+1); hMc[i]->Draw();
  }
 
  TCanvas *c2 = new TCanvas("c2","c2",1);
  hData->Draw();
  pt->Draw();
  hStack->Draw("same");
  hData->Draw("same");
  hData->Draw("sameaxis");
 
  hData->SetTitle("");
  hData->SetMinimum(hmin);

  if(hmax!=0) hData->SetMaximum(hmax);
  if(logscale) gPad->SetLogy();
  
  gPad->SetTicks();
  //gPad->RedrawAxis();
  
  TLegend *leg = new TLegend(0.73,0.57,0.88,0.88,NULL,"brNDC");
  leg->SetBorderSize(1);
  leg->SetTextFont(62);
  leg->SetTextSize(0.04);
  leg->SetLineColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  if (hData->GetEntries()>0) leg->AddEntry(hData,"Data","p");
  for(int i=0; i<n; ++i) {
    int j = n-i-1;
    leg->AddEntry(hMc[j],legMc[j],"f");
  }
  leg->Draw();

  c2->Print(TString("c")+hist+TString(".eps"));
  c2->Print(TString("c")+hist+TString(".pdf"));
  //c2->Print(TString("c")+hist+TString(".png"));

}
