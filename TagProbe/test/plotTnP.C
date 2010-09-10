void plotTnP(){

 //gROOT->LoadMacro("tdrstyle.C");
 //setTDRStyle();

 TFile * f = new TFile("testEfficiency.root"); 

 //c->Draw();
 plotEff(f,"tnpTree/pt/fit_eff_plots/pt_PLOT","hxy_fit_eff");
 plotEff(f,"tnpTree/abseta/fit_eff_plots/abseta_PLOT","hxy_fit_eff");
 //plotEff(f,"tnpTree/pt/cnt_eff_plots/pt_PLOT","hxy_cnt_eff");
 //plotEff(f,"tnpTree/abseta/cnt_eff_plots/abseta_PLOT","hxy_cnt_eff");


 //getObjects(c);
 //TCanvas * c1 = (TCanvas *) f->Get("tnpTree/pt/pt_bin0__gaussPlusLinear/fit_canvas");
 //c1->Draw();

}

void plotEff(TFile* f, const TString& dir, const TString& hName){
  TCanvas * c = (TCanvas *) f->Get(Form("%s",dir.Data()));
  //getObjects(c);
  RooHist* h = (RooHist*) c->FindObject(Form("%s",hName.Data()));
  h->SetLineWidth(2);
  h->SetLineColor(4);
  h->SetMarkerColor(4);
  h->SetMarkerStyle(20);
  h->SetMarkerSize(1.0);

  for(int i=0 ; i < h->GetMaxSize() ; i++){
    double x;
    double y;
    double yerrhi = h->GetErrorYhigh(i);
    double yerrlo = h->GetErrorYlow(i);
    double eff =  h->GetPoint(i,x,y);
    cout << "x= " << x << " eff= " << y << "(+" << yerrhi << " -" << yerrlo << ")" << endl;
  }
  c->Draw();
}

void getObjects( TCanvas *c){

  TObject *obj;
  TIter next(c->GetListOfPrimitives());
  while ((obj=next())) {
    cout << "Reading: " << obj->GetName() << endl;
    if (obj->InheritsFrom("TH1")) {
      cout << "histo: " << obj->GetName() << endl;
    }
    if (obj->InheritsFrom("RooHist")) {
      cout << "roohisto: " << obj->GetName() << endl;
    }
    if (obj->InheritsFrom("RooFit")) {
      cout << "roofit: " << obj->GetName() << endl;
    }
    if (obj->InheritsFrom("TCanvas")) {
      cout << "canvas: " << obj->GetName() << endl;
    }
    if (obj->InheritsFrom("TFit")) {
      cout << "fit: " << obj->GetName() << endl;
    }

  }
}


myPlot2(TString file1, TString dir1, TString plot1, TString file2, TString dir2, TString plot2){
    TFile * f1 = new TFile(file1);
    f1->cd(dir1);
    TCanvas* c1 = (TCanvas*) gDirectory->FindKey(plot1)->ReadObj();
    RooHist* h1 = (RooHist*) c1->FindObject("hxy_fit_eff");
    h1->SetLineWidth(2);
    h1->SetLineColor(209);
    h1->SetMarkerColor(209);
    h1->SetMarkerStyle(25);
    h1->SetMarkerSize(1.0);

    TFile * f2= new TFile(file2);
    f2->cd(dir2);
    TCanvas* c2 = (TCanvas*) gDirectory->FindKey(plot2)->ReadObj();
    RooHist* h2 = (RooHist*) c2->FindObject("hxy_fit_eff");

    h2->SetLineWidth(2);
    h2->SetLineColor(206);
    h2->SetMarkerColor(206);
    h2->SetMarkerStyle(20);
    h2->SetMarkerSize(1.);


    c1->Draw();
    h2->Draw("P SAME");

    doLegend(h1, h2, "deltaR02", "deltaR03");
    c1->SaveAs(plot1+".png");
/*
    doLegend(hfit,href,datalbl,reflbl);
    gPad->Print(prefix+alias+".png");
*/
}

void doLegend(TGraphAsymmErrors *g1, TGraphAsymmErrors *g2, TString lab1, TString lab2) {
    TLegend *leg = new TLegend(.65,.2 ,.85,.5 );
    leg->AddEntry(g1, lab1, "LP");
    leg->AddEntry(g2, lab2, "LP");
    leg->SetFillColor(0);
    leg->Draw();
}



