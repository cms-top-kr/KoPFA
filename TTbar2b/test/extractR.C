void extractR(const TString& decayMode = "MuEl"){

  TFile * f = new TFile(Form("%s_ttbb_v0/%s.root", decayMode.Data(), decayMode.Data()));

  TH1F * h_ttbb_CSVM = (TH1F*) f->Get("Step_6/hMCSig_TTbarbb_Step_6_nbJet_CSVM");
  TH1F * h_ttll_CSVM = (TH1F*) f->Get("Step_6/hMC_TTbarll_Step_6_nbJet_CSVM");
  TH1F * h_data_CSVM = (TH1F*) f->Get("Step_6/hDataSub_Step_6_nbJet_CSVM");
  h_data_CSVM->Add(h_ttll_CSVM);

  TH1F * h_ttbb_CSVT = (TH1F*) f->Get("Step_6/hMCSig_TTbarbb_Step_6_nbJet_CSVT");
  TH1F * h_ttll_CSVT = (TH1F*) f->Get("Step_6/hMC_TTbarll_Step_6_nbJet_CSVT");
  TH1F * h_data_CSVT = (TH1F*) f->Get("Step_6/hDataSub_Step_6_nbJet_CSVT");
  h_data_CSVT->Add(h_ttll_CSVT);
 
  double fraction = 0.05;
  double total_ttbb = 4982.0 * 161.9 * fraction; 
  double total_ttll = 4982.0 * 161.9 * (1-fraction); 

  double N_data_tag1 = h_data_CSVM->Integral(4,6); 
  double A_ttbb_tag1 = h_ttbb_CSVM->Integral(4,6)/total_ttbb;
  double A_ttll_tag1 = h_ttll_CSVM->Integral(4,6)/total_ttll;

  double N_data_tag2 = h_data_CSVT->Integral(4,6); 
  double A_ttbb_tag2 = h_ttbb_CSVT->Integral(4,6)/total_ttbb;
  double A_ttll_tag2 = h_ttll_CSVT->Integral(4,6)/total_ttll;

  double R = ( N_data_tag1 * A_ttll_tag2 - N_data_tag2 * A_ttll_tag1) / ( N_data_tag2 * ( A_ttbb_tag1 - A_ttll_tag1) - N_data_tag1 * ( A_ttbb_tag2 - A_ttll_tag2));

  cout << "R= " << R << endl;

}
