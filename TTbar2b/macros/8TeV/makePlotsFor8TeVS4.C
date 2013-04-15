#include <iostream>
#include <iomanip>
#include "tdrstyle.C"

////////////////
 const char* ZMass[2] =  	    {"ZMass", 	   "Dilepton mass;Dilepton Mass (GeV/c^{2}};Events/5 GeV/c^{2}" };
 const char* ZMassFinal[2] =    {"ZMassFinal",   "Dilepton mass;Dilepton Mass (GeV/c^{2}};Events/40 GeV/c^{2}"};
                 
 const char* nJetlog[2] =  	    {"nJetlog", 	   "Jet Multiplicity;Jet Multiplicity;Events"      };
 const char* nVertexlog[2] =    {"nVertexlog",   "Vertex Multiplicity;Vertex Multiplicity;Events"};
 const char* nVertex[2] =  	    {"nVertex", 	   "Vertex Multiplicity;Vertex Multiplicity;Events"};
 const char* METlog[2] =  	    {"METlog", 	   "Missing E_{T};Missing E_{T} (GeV};Events"      };
 const char* nJet[2] =  	    {"nJet", 	   "Jet Multiplicity;Jet Multiplicity;Events"      };
 const char* MET[2] =  	    {"MET", 	   "Missing E_{T};Missing E_{T} (GeV};Events"      };
 const char* METQCD[2] =  	    {"METQCD", 	   "Missing E_{T};Missing E_{T} (GeV};Events"      };
                 
 const char* pt1[2] =  	    {"pt1", 	   "Leading lepton p_{T};p_{T} (GeV/c};Events/5 GeV/c"           };
 const char* pt2[2] =  	    {"pt2", 	   "Second leading lepton p_{T};p_{T} (GeV/c};Events/5 GeV/c"    };
 const char* eta1[2] =  	    {"eta1", 	   "Leading #eta;#eta;Events/0.2"                                };
 const char* eta2[2] =  	    {"eta2", 	   "Second leading lepton #eta;#eta;Events/0.2"                  };
                 
 const char* jet1pt30[2] =       {"jet1pt30", 	 	 "Leading jet p_{T};p_{T} (GeV/c};Events/10 GeV/c"       };
 const char* jet1eta30[2] =      {"jet1eta30",   	 "Leading #eta;#eta;Events/0.2"                          };
 const char* jet1phi30[2] =      {"jet1phi30",   	 "Leading #phi;#phi (Radian};Events/0.2 rad."            };
                 
 const char* jet2pt30[2] =       {"jet2pt30", 	 	 "Second leading jet p_{T};p_{T} (GeV/c};Events/10 GeV/c"};
 const char* jet2eta30[2] =      {"jet2eta30",   	 "Second leading jet #eta;#eta;Events/0.2"               };
 const char* jet2phi30[2] =      {"jet2phi30",   	 "Second leading jet #phi;#phi (Radian};Events/0.2 rad." };
                 
 const char* jet3pt30[2] =       {"jet3pt30", 	 	 "Third jet p_{T};p_{T} (GeV/c};Events/10 GeV/c"  };
 const char* jet3eta30[2] =      {"jet3eta30",   	 "Third jet #eta;#eta;Events/0.2"                 };
 const char* jet3phi30[2] =      {"jet3phi30",   	 "Third jet #phi;#phi (Radian};Events/0.2 rad."   };
                 
 const char* jet4pt30[2] =       {"jet4pt30", 	 	 "Fourth jet p_{T};p_{T} (GeV/c};Events/10 GeV/c" };
 const char* jet4eta30[2] =      {"jet4eta30", 	 "Fourth jet #eta;#eta;Events/0.2"                };
 const char* jet4phi30[2] =      {"jet4phi30", 	 "Fourth jet #phi;#phi (Radian};Events/0.2 rad."  };
                 
 const char* Iso03lep1[2] =      {"Iso03lep1", 	 "relIso03lep1;relIso;Events"};
 const char* Iso03lep2[2] =      {"Iso03lep2", 	 "relIso03lep2;relIso;Events"};
                 
 const char* nbJet30_CSVL[2] =   {"nbJet30_CSVL", 	 "b-Jet Multiplicity;b-Jet Multiplicity (CSVL};Events"};
 const char* nbJet30_CSVM[2] =   {"nbJet30_CSVM", 	 "b-Jet Multiplicity;b-Jet Multiplicity (CSVM};Events"};
 const char* nbJet30_CSVT[2] =   {"nbJet30_CSVT", 	 "b-Jet Multiplicity;b-Jet Multiplicity (CSVT};Events"};
 const char* nbJet30_JPM[2] =    {"nbJet30_JPM", 	 "b-Jet Multiplicity;b-Jet Multiplicity (JPM};Events"};
 const char* nbJet30_JPT[2] =    {"nbJet30_JPT", 	 "b-Jet Multiplicity;b-Jet Multiplicity (JPT};Events"};
                 
 const char* addjet1_bDisCSV[2] = {"addjet1_bDisCSV", 	 "b-Discriminator; b-Discriminator (CSV};Events/0.1"};
 const char* addjet2_bDisCSV[2] = {"addjet2_bDisCSV", 	 "b-Discriminator; b-Discriminator (CSV};Events/0.1"};
                 
 const char* addjet1_bDisJP[2] = {"addjet1_bDisJP", 	 "b-Discriminator; b-Discriminator (JP};Events"};
 const char* addjet2_bDisJP[2] = {"addjet2_bDisJP", 	 "b-Discriminator; b-Discriminator (JP};Events"};
                 
 const char* addjet1_secvtxm[2] = {"addjet1_secvtxm", 	 "Secondary Vertex Mass;Secondary Vertex Mass (GeV};Events"};
 const char* addjet2_secvtxm[2] = {"addjet2_secvtxm", 	 "Secondary Vertex Mass;Secondary Vertex Mass (GeV};Events"};
//////////////////

TFile* fEE, * fME, * fMM;
TString outDirName = ".";
    
const int nBkg = 5;
const char* bkgNames[] = {//"hMCSig_TTbarbb",
 "hMC_TTbarcc","hMC_TTbarll","hMC_TTbarOthers",//"hMC_Wl", "hMC_VV",
 "hMC_SingleTop", "hMC_DYll"
//,"hDataBkg_QCD"
};
const char* bkgLabels[] = {//"t#bar{t}+bb",
  "t#bar{t}+cc", "t#bar{t}+LF","t#bar{t} others",
//"W #rightarrow l#nu", "Dibosons",
 "Single top", "Z/#gamma* #rightarrow ll"
//,"QCD"
};
const Color_t color_sig = kBlue+2;
const int style_sig = 3354;
const Color_t color[] = {//kRed+3,
    kOrange+2,kRed,kRed-7,
//kGreen-3,kGray+4,
kMagenta,kAzure-2
//,kYellow
};
const int     style[] = {//1001,
1001,  1001,  1001,    1001,   1001//,    1001,    1001
//,   1001
};

const int nSig = 1;
const char* sigNames[] = {"hMCSig_TTbarbb"};//"hMCSig_TTbarH125"};
const char* sigLabels[] = {"t#bar{t}+bb"};//"t#bar{t}+H"};
bool stackSig = true;

void cutStepPlots(const char* cutStep, const char* histNameTitle[2],
                  double minY, double maxY, bool doLogY);

//void cutStepPlots(const char* cutStep, const char* histName, const char* histTitle,
//                  double minY, double maxY, bool doLogY);
TLegend* buildLegend();
TPaveText* getHeader(double lumi, TString channelName = "");

void makePlotsFor8TeVS4(TString noteNumber = "TTBB_CSVT_Plots")
{
  setTDRStyle();

  TString path = "TTBB_CSVT"; 

  fEE = TFile::Open(path+"/ElEl/ElEl.root");
  fME = TFile::Open(path+"/MuEl/MuEl.root");
  fMM = TFile::Open(path+"/MuMu/MuMu.root");

  if ( !fEE || !fME || !fMM ) return;

  outDirName += "/"+noteNumber;
  gSystem->Exec("mkdir "+outDirName);
/////////////


//  plot(1,ZMass); plot(1,nJet); plot(1,pt1); plot(1,pt2); plot(1,eta1); plot(1,eta2); plot(1,Iso03lep1); plot(1,Iso03lep2); plot(1,nVertex); plot(1,MET);
//  plot(2,ZMass); plot(2,nJet); plot(2,pt1); plot(2,pt2); plot(2,eta1); plot(2,eta2); plot(2,Iso03lep1); plot(2,Iso03lep2); plot(2,nVertex); plot(2,MET);
//  plot(3,ZMass); plot(3,nJet); plot(3,pt1); plot(3,pt2); plot(3,eta1); plot(3,eta2); plot(3,Iso03lep1); plot(3,Iso03lep2); plot(3,nVertex); plot(3,MET);
  plot(4,nJet); //plot(4,nbJet30_CSVM); 
  plot(4,nbJet30_CSVT); plot(4,ZMass); plot(4,MET); plot(4,nVertex); plot(4,jet1pt30); plot(4,jet2pt30); plot(4,jet3pt30); plot(4,jet4pt30); plot(4,jet1eta30); plot(4,jet2eta30); plot(4,jet3eta30); plot(4,jet4eta30); plot(4,jet1phi30); plot(4,jet2phi30); plot(4,jet3phi30); plot(4,jet4phi30); plot(4,jet4phi30);

  plot(5,nJet); plot(5,addjet1_bDisCSV); plot(5,addjet2_bDisCSV); //plot(5,bJet30_CSVM); 
  plot(5,nbJet30_CSVT); plot(5,ZMass); plot(5,MET); plot(5,nVertex); plot(5,jet1pt30); plot(5,jet2pt30); plot(5,jet3pt30); plot(5,jet4pt30); plot(5,jet1eta30); plot(5,jet2eta30); plot(5,jet3eta30); plot(5,jet4eta30); plot(5,jet1phi30); plot(5,jet2phi30); plot(5,jet3phi30); plot(5,jet4phi30); plot(5,jet4phi30); plot(5,addjet1_bDisJP); plot(5,addjet2_bDisJP);




}
/*
    S1("ZMass,nJet,pt1,pt2,eta1,eta2,Iso03lep1,Iso03lep2,nVertex,MET");
    S2("ZMass,nJet,pt1,pt2,eta1,eta2,Iso03lep1,Iso03lep2,nVertex,MET");
    S3("ZMass,nJet,pt1,pt2,eta1,eta2,Iso03lep1,Iso03lep2,nVertex,MET");
    S4("nJet,nbJet30_CSVM,nbJet30_CSVT,ZMass,MET,nVertex,jet1pt30,jet2pt30,jet3pt30,jet4pt30,jet1eta30,jet2eta30,jet3eta30,jet4eta30,jet1phi30,jet2phi30,jet3phi30,jet4phi30,jet4phi30");
    S5("nJet,addjet1_bDisCSV,addjet2_bDisCSV,bJet30_CSVM,nbJet30_CSVT,ZMass,MET,nVertex,jet1pt30,jet2pt30,jet3pt30,jet4pt30,jet1eta30,jet2eta30,jet3eta30,jet4eta30,jet1phi30,jet2phi30,jet3phi30,jet4phi30,jet4phi30,addjet1_bDisJP,addjet2_bDisJP");

  analyzer->addCutStep(cut, "addjet1_bDisCSV", 0.5, "jets_bDisCSVweight[csvd_jetid[2]]");
  analyzer->addCutStep(cut, "addjet2_bDisCSV", 0.5, "jets_bDisCSVweight[csvd_jetid[3]]");
*/
void plot(int S, const char* histNameTitle[2])
{
      TString cutStep = Form("Step_%d",S); 
      cutStepPlots(cutStep.Data(), histNameTitle, 0.01,   2000, false);
      cutStepPlots(cutStep.Data(), histNameTitle, 0.01,   2000, true);
}

void rescalePlots(TString cutStep, TString bkgName, TString histNamesStr, double mumuScale, double elelScale, double muelScale)
{
  TObjArray* histNames = histNamesStr.Tokenize(",");

  for ( int i=0; i<histNames->GetEntries(); ++i )
  {
    TString histName = histNames->At(i)->GetName();

    TH1F* hEE = (TH1F*)fEE->Get(Form("%s/hMC_%s_%s_%s", cutStep.Data(), bkgName.Data(), cutStep.Data(), histName.Data()));
    TH1F* hME = (TH1F*)fME->Get(Form("%s/hMC_%s_%s_%s", cutStep.Data(), bkgName.Data(), cutStep.Data(), histName.Data()));
    TH1F* hMM = (TH1F*)fMM->Get(Form("%s/hMC_%s_%s_%s", cutStep.Data(), bkgName.Data(), cutStep.Data(), histName.Data()));

    if ( !hEE || !hME || !hMM ) continue;

    hEE->Scale(elelScale);
    hMM->Scale(mumuScale);
    hME->Scale(muelScale);
  }
}

// Function to draw EE, ME, MM channel and all channel merged plot
void cutStepPlots(const char* cutStep, const char* histNameTitle[2],
                  double minY, double maxY, bool doLogY)
{
 const char* histName = histNameTitle[0];
 const char* histTitle = histNameTitle[1];

  //cout << histName << " : " << histTitle << endl;

  TH1F* hDataEE = (TH1F*)fEE->Get(Form("%s/hData_%s_%s", cutStep, cutStep, histName));
  TH1F* hDataME = (TH1F*)fME->Get(Form("%s/hData_%s_%s", cutStep, cutStep, histName));
  TH1F* hDataMM = (TH1F*)fMM->Get(Form("%s/hData_%s_%s", cutStep, cutStep, histName));

  if ( !hDataEE ) { cout << Form("%s/hData_%s_%s", cutStep, cutStep, histName) << " for EE " << "\n"; return; }
  if ( !hDataME ) { cout << Form("%s/hData_%s_%s", cutStep, cutStep, histName) << " for ME " << "\n"; return; }
  if ( !hDataMM ) { cout << Form("%s/hData_%s_%s", cutStep, cutStep, histName) << " for MM " << "\n"; return; }


  TH1F* hDataLL = (TH1F*)hDataEE->Clone(Form("hData_%s_%s", cutStep, histName));
  hDataLL->Reset();
  hDataLL->Add(hDataEE);
  hDataLL->Add(hDataME);
  hDataLL->Add(hDataMM);

  THStack* hStackEE = new THStack(TString("hEE_")+cutStep+"_"+histName, histTitle);
  THStack* hStackME = new THStack(TString("hME_")+cutStep+"_"+histName, histTitle);
  THStack* hStackMM = new THStack(TString("hMM_")+cutStep+"_"+histName, histTitle);
  THStack* hStackLL = new THStack(TString("hLL_")+cutStep+"_"+histName, histTitle);

  TH1F* hSigEE = (TH1F*)fEE->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName));
  TH1F* hSigME = (TH1F*)fME->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName));
  TH1F* hSigMM = (TH1F*)fMM->Get(Form("%s/%s_%s_%s", cutStep, sigNames[0], cutStep, histName));

  hSigEE->SetFillColor(color_sig);
  hSigME->SetFillColor(color_sig);
  hSigMM->SetFillColor(color_sig);

  hSigEE->SetFillStyle(style_sig);
  hSigME->SetFillStyle(style_sig);
  hSigMM->SetFillStyle(style_sig);

  //hSigEE->SetLineColor(color_sig);
  //hSigME->SetLineColor(color_sig);
  //hSigMM->SetLineColor(color_sig);




  if ( !hSigEE || !hSigME || !hSigMM ) { cout << "No signal hist for " << histName << "\n"; return; }

  TH1F* hSigLL = (TH1F*)hSigEE->Clone(Form("%s_%s_%s", sigNames[0], cutStep, histName));
  hSigLL->Reset();
  hSigLL->Add(hSigEE);
  hSigLL->Add(hSigME);
  hSigLL->Add(hSigMM);

  if( stackSig ){
    hStackEE->Add(hSigEE);
    hStackME->Add(hSigME);
    hStackMM->Add(hSigMM);
    hStackLL->Add(hSigLL);
  }

  // Build legends
  TLegend* legEE = buildLegend();
  TLegend* legME = buildLegend();
  TLegend* legMM = buildLegend();
  TLegend* legLL = buildLegend();

  if ( hDataEE->GetEntries() > 0 ) legEE->AddEntry(hDataEE, "Data", "p");
  if ( hDataME->GetEntries() > 0 ) legME->AddEntry(hDataME, "Data", "p");
  if ( hDataMM->GetEntries() > 0 ) legMM->AddEntry(hDataMM, "Data", "p");
  if ( hDataLL->GetEntries() > 0 ) legLL->AddEntry(hDataLL, "Data", "p");

  TH1F* hEEs[nBkg];
  TH1F* hMEs[nBkg];
  TH1F* hMMs[nBkg];
  TH1F* hLLs[nBkg];

  for ( int i=0; i<nBkg; ++i )
  {
    TH1F* hEE = (TH1F*)fEE->Get(Form("%s/%s_%s_%s", cutStep, bkgNames[i], cutStep, histName));
    TH1F* hME = (TH1F*)fME->Get(Form("%s/%s_%s_%s", cutStep, bkgNames[i], cutStep, histName));
    TH1F* hMM = (TH1F*)fMM->Get(Form("%s/%s_%s_%s", cutStep, bkgNames[i], cutStep, histName));

    hEE->SetFillColor(color[i]);
    hME->SetFillColor(color[i]);
    hMM->SetFillColor(color[i]);

    hEE->SetFillStyle(style[i]);
    hME->SetFillStyle(style[i]);
    hMM->SetFillStyle(style[i]);

   // hEE->SetLineColor(color[i]);
   // hME->SetLineColor(color[i]);
   // hMM->SetLineColor(color[i]);


    if ( !hEE || !hME || !hMM ) { cout << "No bkg hist " << bkgNames[i] << endl; continue; }

    TH1F* hLL = (TH1F*)hEE->Clone(Form("%s_%s_%s", bkgNames[i], cutStep, histName));
    hLL->Reset();
    hLL->Add(hEE);
    hLL->Add(hME);
    hLL->Add(hMM);

    hEEs[i] = hEE;
    hMEs[i] = hME;
    hMMs[i] = hMM;
    hLLs[i] = hLL;

    hStackEE->Add(hEE);
    hStackME->Add(hME);
    hStackMM->Add(hMM);
    hStackLL->Add(hLL);
  }

  for ( int i=nBkg-1; i>=0; --i )
  {
    legEE->AddEntry(hEEs[i], bkgLabels[i], "f");
    legME->AddEntry(hMEs[i], bkgLabels[i], "f");
    legMM->AddEntry(hMMs[i], bkgLabels[i], "f");
    legLL->AddEntry(hLLs[i], bkgLabels[i], "f");
  }

  legEE->AddEntry(hSigEE, sigLabels[0], "f");
  legME->AddEntry(hSigME, sigLabels[0], "f");
  legMM->AddEntry(hSigMM, sigLabels[0], "f");
  legLL->AddEntry(hSigLL, sigLabels[0], "f");


  // Be ready for draw
  double YmaxEE = 0, YmaxMM=0, YmaxME=0, YmaxLL=0;
  YmaxEE = hDataEE->GetMaximum();
  YmaxMM = hDataMM->GetMaximum();
  YmaxME = hDataME->GetMaximum();
  YmaxLL = hDataLL->GetMaximum();

  hDataEE->SetMinimum(minY);
  hDataME->SetMinimum(minY);
  hDataMM->SetMinimum(minY);
  hDataLL->SetMinimum(minY);

  if(YmaxEE >YmaxMM) YmaxMM=YmaxEE;
  else               YmaxEE=YmaxMM;

  if(doLogY)
  {
    hDataEE->SetMaximum(YmaxEE*10000);
    hDataME->SetMaximum(YmaxME*10000);
    hDataMM->SetMaximum(YmaxMM*10000);
    hDataLL->SetMaximum(YmaxLL*10000);
  }
  else
  {
    hDataEE->SetMaximum(YmaxEE*2.5);
    hDataME->SetMaximum(YmaxME*2.5);
    hDataMM->SetMaximum(YmaxMM*2.5);
    hDataLL->SetMaximum(YmaxLL*2.5);
  }


  TCanvas* cEE = new TCanvas(TString("cEE_")+cutStep+"_"+histName, TString("cEE_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cEE->SetLogy();
  hDataEE->Draw();
  legEE->Draw();
  getHeader(19.6, "ee channel")->Draw();
  hStackEE->Draw("same");
  hSigEE->Draw("same");
  hDataEE->Draw("same");
  hDataEE->Draw("sameaxis");

  if(doLogY)
  {
    cEE->Print(Form("%s/log/cEE_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cEE->Print(Form("%s/log/cEE_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cEE->Print(Form("%s/log/cEE_%s_%s.png", outDirName.Data(), cutStep, histName));
  }
  else
  {
    cEE->Print(Form("%s/linear/cEE_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cEE->Print(Form("%s/linear/cEE_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cEE->Print(Form("%s/linear/cEE_%s_%s.png", outDirName.Data(), cutStep, histName));
  }

  TCanvas* cME = new TCanvas(TString("cME_")+cutStep+"_"+histName, TString("cME_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cME->SetLogy();
  hDataME->Draw();
  legME->Draw();
  getHeader(19.6, "#mue channel")->Draw();
  hStackME->Draw("same");
  if( nSig > 0 ) hSigME->Draw("same");
  hDataME->Draw("same");
  hDataME->Draw("sameaxis");

  if(doLogY)
  {
    cME->Print(Form("%s/log/cME_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cME->Print(Form("%s/log/cME_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cME->Print(Form("%s/log/cME_%s_%s.png", outDirName.Data(), cutStep, histName));
  }
  else
  {
    cME->Print(Form("%s/linear/cME_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cME->Print(Form("%s/linear/cME_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cME->Print(Form("%s/linear/cME_%s_%s.png", outDirName.Data(), cutStep, histName));
  }


  TCanvas* cMM = new TCanvas(TString("cMM_")+cutStep+"_"+histName, TString("cMM_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cMM->SetLogy();
  hDataMM->Draw();
  legMM->Draw();
  getHeader(19.6, "#mu#mu channel")->Draw();
  hStackMM->Draw("same");
  hSigMM->Draw("same");
  hDataMM->Draw("same");
  hDataMM->Draw("sameaxis");

  if(doLogY)
  {
    cMM->Print(Form("%s/log/cMM_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cMM->Print(Form("%s/log/cMM_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cMM->Print(Form("%s/log/cMM_%s_%s.png", outDirName.Data(), cutStep, histName));
  }
  else
  {
    cMM->Print(Form("%s/linear/cMM_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cMM->Print(Form("%s/linear/cMM_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cMM->Print(Form("%s/linear/cMM_%s_%s.png", outDirName.Data(), cutStep, histName));
  } 

  TCanvas* cLL = new TCanvas(TString("cLL_")+cutStep+"_"+histName, TString("cLL_")+cutStep+"_"+histName, 1);
  if ( doLogY ) cLL->SetLogy();
  hDataLL->Draw();
  legLL->Draw();
  getHeader(19.6, "All channel")->Draw();
  hStackLL->Draw("same");
  if( !stackSig ) hSigLL->Draw("same");
  hDataLL->Draw("same");
  hDataLL->Draw("sameaxis");

  if(doLogY)
  {
    cLL->Print(Form("%s/log/cLL_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cLL->Print(Form("%s/log/cLL_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cLL->Print(Form("%s/log/cLL_%s_%s.png", outDirName.Data(), cutStep, histName));
  } 
  else
  {
    cLL->Print(Form("%s/linear/cLL_%s_%s.eps", outDirName.Data(), cutStep, histName));
    cLL->Print(Form("%s/linear/cLL_%s_%s.pdf", outDirName.Data(), cutStep, histName));
    cLL->Print(Form("%s/linear/cLL_%s_%s.png", outDirName.Data(), cutStep, histName));
  }
}

TLegend* buildLegend()
{
  TLegend* leg = new TLegend(0.73,0.69,0.85,0.90,NULL,"brNDC");

  leg->SetBorderSize(1);
  leg->SetTextFont(62);
  leg->SetTextSize(0.04);
  leg->SetLineColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);

  return leg;
}

TPaveText* getHeader(double lumi, TString channelName)
{
  TPaveText* pt = new TPaveText(0.18,0.75,0.18,0.90,"brNDC");

  pt->SetBorderSize(1);
  pt->SetTextFont(42);
  pt->SetTextSize(0.04);
  pt->SetLineColor(0);
  pt->SetLineStyle(1);
  pt->SetLineWidth(1);
  pt->SetFillColor(0);
  pt->SetFillStyle(1001);
  pt->SetTextAlign(12);
  pt->AddText("CMS Preliminary");
  pt->AddText(Form("%.1f fb^{-1} at  #sqrt{s} = 8 TeV", lumi));
  if ( channelName != "" ) pt->AddText(channelName);

  return pt;
}
