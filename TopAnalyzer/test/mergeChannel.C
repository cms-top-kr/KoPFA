void mergeChannel (TString filename, TString step, TString histotype, bool logscale=true, float hmax=0, float hmin=0.02)
{
  
  TFile *_file0 = TFile::Open(filename);
  
  const int n = 6;
  
  TString hist = TString("_Step_")+ TString(step) + TString("_") + TString(histotype);
  TString data = TString("hData") + TString(hist);
  TString mc[n];
  mc[0] = TString("hMC_TTbar") + TString(hist);
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
  hData->GetXaxis()->SetTitleOffset(0.8);
  hData->GetYaxis()->SetTitleOffset(0.8);
  
  TH1F* hMc[n];
  THStack *hStack = new THStack("hStack",TString("MC")+hist);
  for(int i=0; i<n; ++i) {
    cout << mc[i] << endl;
    hMc[i] = (TH1F*)(gROOT->FindObject(mc[i]));
    hMc[i]->SetTitle("");
    hMc[i]->GetXaxis()->SetTitleOffset(1.3);
    hMc[i]->GetYaxis()->SetTitleOffset(1.3);
    hMc[i]->SetStats(0);
    
    hStack->Add(hMc[i]);
  }
  
  TCanvas *c1 = new TCanvas("c1","c1",0,0,700,500);
  c1->Divide(2,3);
  for(int i=0; i<n; ++i) {
    c1->cd(i+1); hMc[i]->Draw();
  }
  
  TCanvas *c2 = new TCanvas("c2","c2",100,100,700,500);
  hData->Draw();
  hStack->Draw("same");
  hData->Draw("same");
  
  hData->SetTitle("");
  if(hmax!=0) hData->SetMaximum(hmax);
  hData->SetMinimum(hmin);
  
  gPad->RedrawAxis();
  gPad->SetTicks();
  
  if(logscale) gPad->SetLogy();
  
  TLegend *leg = new TLegend(0.70,0.57,0.88,0.88,NULL,"brNDC");
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
    if (hMc[j]->GetEntries()>0) leg->AddEntry(hMc[j],legMc[j],"f");
  }
  leg->Draw();
  
  c2->Print(TString("c")+hist+TString(".png"));
  c2->Print(TString("c")+hist+TString(".eps"));
  c2->Print(TString("c")+hist+TString(".pdf"));
  
}
