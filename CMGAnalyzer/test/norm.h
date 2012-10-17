//cross section at 7TeV
double X_DYM50_7TeV     = 3048;
double X_DYM10To50_7TeV = 11098.83;
double X_TTbar_7TeV     = 165.9;
double X_WJets_7TeV     = 31314;
double X_SingletW_7TeV  = 15.74;

//cross section at 8TeV
double X_DYM50_8TeV     = 3503.71;
double X_DYM10To50_8TeV = 860.5; //need to be updated
double X_TTbar_8TeV     = 225.197;
double X_WJets_8TeV     = 36257.2;
double X_SingletW_8TeV  = 22.2;

//data lumi
double Lumi2011 = 4982;
double Lumi2012 = 1616;

TString dir_ = "";

struct Sample{
  TFile *file;
  TString name;
  double norm;
  int fillcolor;
  int linecolor;
  TString label;
};

double getNorm( double nTotal, double X, double lumi){

  double SF = lumi * X / nTotal;
  return SF;

}

Sample Add(TFile * file, const TString & name, const TString & label, int fillcolor, double X = -1.0, int linecolor = 1){
  Sample out;
  out.file = file;
  out.name = name;
  out.label = label;
  out.fillcolor = fillcolor;
  out.linecolor = linecolor;
  if( X == -1.0){
    out.norm = 1.0;
  }else{
    TH1F* h = (TH1F*) file->Get(Form("%s/EventSummary",dir_.Data()));
    double nTotal = h->GetBinContent(1);
    out.norm = getNorm( nTotal, X, 10000) ;
  }
  return out;
}

void plot( std::vector<Sample> sample, const TString & histName, const TString & canvasName, const TString & title,  double min, double max, bool log = false){

  TCanvas * c = new TCanvas(Form("c_%s",canvasName.Data()), Form("c_%s",canvasName.Data()) ,1);
  if(log) c->SetLogy();

  TLegend *l= new TLegend(0.7,0.7,0.87,0.87);
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();

  TH1F *hData = (TH1F *) sample[0].file->Get(Form("%s/%s", dir_.Data(), histName.Data()));
  hData->SetMarkerSize(0.4);
  hData->SetMarkerStyle(20);
  l->AddEntry(hData, sample[0].label, "P");
  cout << "Data = " << hData->Integral() << endl;
  double totalBkg = 0;

  THStack *hs = new THStack("hs",Form("%s",histName.Data()));
  for( unsigned int i = 1 ; i < sample.size() ; i++){
    TH1F *h = (TH1F *) sample[i].file->Get(Form("%s/%s", dir_.Data(), histName.Data()));
    h->SetFillColor( sample[i].fillcolor );
    h->SetLineColor( sample[i].linecolor );
    h->Scale( sample[i].norm );
    hs->Add(h);
    if( sample[i].linecolor == 1 ){
      l->AddEntry( h, sample[i].label, "F" );
    }
    cout << sample[i].name << "(" << histName.Data() << ") = " << h->Integral() << endl;
    totalBkg += h->Integral();
  }

  double DataSub = hData->Integral() - totalBkg;
  cout << "DataSub= " << DataSub << endl;

  hs->SetMaximum( max );
  hs->SetMinimum( min );
  hs->SetTitle(title.Data());

  hs->Draw();
  hData->Draw("sameP");
  l->Draw();
}



