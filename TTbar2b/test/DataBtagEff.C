void ExtractBtagEff(TH1* h, TH1* extra){

 double eb1 = 0;
 double eb2 = 0;
 double el = 0;
 double correl = 0;

 double Nb0 = h->GetBinContent(1);
 double Nb1 = h->GetBinContent(2);
 double Nb2 = h->GetBinContent(3);
 double Nb3 = h->GetBinContent(4);

 eb1 = 1.0 / ( 2.0 * Nb0 / Nb1 + 1.0 );
 eb2 = 2.0 / ( 2.0  +  Nb1 / Nb2 );
 el = 1.9 / (2.0 * Nb2 / Nb3 + 1.0 );

 double nextra = extra->GetMean() - 2.0;
 correl = el * 2.0/  nextra ;

 cout << " eb1= " << eb1 << " eb2= " << eb2 << " el= " << el << " corrected el for extra jet " << nextra << " = " << correl << endl;

}

void MistagEff(TH1* hpt, TH1* eff){

 TH1* rescaled = (TH1*) hpt->Clone();
 int nbins = rescaled->GetNbinsX(); 
 for(int i=1; i < nbins ; i++){
   double bin = hpt->GetBinContent(i) * eff->GetBinContent(i);
   rescaled->SetBinContent(i, bin);
 }
 
 double num = rescaled->Integral();
 double den = hpt->Integral();
 double averaged = num / den;

 cout << " averaged light jet tagging efficiency = " << averaged << endl;

}

void DataBtagEff(){

 gSystem->CompileMacro("MistagFuncs.C", "k");

 TFile * f_L = new TFile("MuEl_TTbb_L/MuEl.root");
 TFile * f_M = new TFile("MuEl_TTbb_M/MuEl.root");
 TFile * f_T = new TFile("MuEl_TTbb_T/MuEl.root");

 TH1* Step_7_nJet_L = (TH1*) f_L->Get("Step_7/hMCSig_TTbar_Step_7_nJet");
 TH1* Step_7_nJet_M = (TH1*) f_M->Get("Step_7/hMCSig_TTbar_Step_7_nJet");
 TH1* Step_7_nJet_T = (TH1*) f_T->Get("Step_7/hMCSig_TTbar_Step_7_nJet");

 TH1* Step_7_jetpt_L = (TH1*) f_L->Get("Step_7/hMCSig_TTbar_Step_7_jetpt");
 TH1* Step_7_jetpt_M = (TH1*) f_M->Get("Step_7/hMCSig_TTbar_Step_7_jetpt");
 TH1* Step_7_jetpt_T = (TH1*) f_T->Get("Step_7/hMCSig_TTbar_Step_7_jetpt");

 TH1* Step_6_nbJet_CSVL = (TH1*) f_M->Get("Step_6/hMCSig_TTbar_Step_6_nbJet_CSVL");
 TH1* Step_6_nbJet_CSVM = (TH1*) f_M->Get("Step_6/hMCSig_TTbar_Step_6_nbJet_CSVM");
 TH1* Step_6_nbJet_CSVT = (TH1*) f_M->Get("Step_6/hMCSig_TTbar_Step_6_nbJet_CSVT");
 
 TF1* Mistag_L = GetMistagmean("CSV","L",0.0, 2.4);
 TF1* Mistag_M = GetMistagmean("CSV","M",0.0, 2.4);
 TF1* Mistag_T = GetMistagmean("CSV","T",0.0, 2.4);
 TH1* hMistag_L = Mistag_L->GetHistogram();
 TH1* hMistag_M = Mistag_M->GetHistogram();
 TH1* hMistag_T = Mistag_T->GetHistogram();

 TCanvas * c_Step_7_nJet_L = new TCanvas("c_Step_7_nJet_L","c_Step_7_nJet_L",1);
 Step_7_nJet_L->Draw("hText");

 TCanvas * c_Step_7_nJet_M = new TCanvas("c_Step_7_nJet_M","c_Step_7_nJet_M",1);
 Step_7_nJet_M->Draw("hText");

 TCanvas * c_Step_7_nJet_T = new TCanvas("c_Step_7_nJet_T","c_Step_7_nJet_T",1);
 Step_7_nJet_T->Draw("hText");

 TCanvas * c_Step_6_nbJet_CSVL = new TCanvas("c_Step_6_nbJet_CSVL","c_Step_6_nbJet_CSVL",1);
 Step_6_nbJet_CSVL->Draw("hText");

 TCanvas * c_Step_6_nbJet_CSVM = new TCanvas("c_Step_6_nbJet_CSVM","c_Step_6_nbJet_CSVM",1);
 Step_6_nbJet_CSVM->Draw("hText");

 TCanvas * c_Step_6_nbJet_CSVT = new TCanvas("c_Step_6_nbJet_CSVT","c_Step_6_nbJet_CSVT",1);
 Step_6_nbJet_CSVT->Draw("hText");

 cout << "CSVL" << endl;
 ExtractBtagEff( Step_6_nbJet_CSVL, Step_7_nJet_L );
 MistagEff( Step_7_jetpt_L, hMistag_L);
 cout << "CSVM" << endl;
 ExtractBtagEff( Step_6_nbJet_CSVM, Step_7_nJet_M );
 MistagEff( Step_7_jetpt_M, hMistag_M);
 cout << "CSVT" << endl;
 ExtractBtagEff( Step_6_nbJet_CSVT, Step_7_nJet_T );
 MistagEff( Step_7_jetpt_T, hMistag_T);

}


