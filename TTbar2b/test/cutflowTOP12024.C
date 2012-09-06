#include <iostream>
#include <iomanip>

void cutflowTOP12024(){

  gROOT->ProcessLine(".L tdrstyle.C");
  defaultStyle();

  print("TTBB_01Sep2012_CSVM_CutFlow","CSVM");
  print("TTBB_01Sep2012_CSVT_CutFlow","CSVT");

  //print("TTBB_01Sep2012_CSVM","CSVM", true, 0.079, 0.88);
  //print("TTBB_01Sep2012_CSVT","CSVT", true, 0.080, 0.93);

}

void print(const TString & p, const TString & b, bool fit=false, double R=1.0, double k=1.0){
  
  TH1 * h[10][4];
  double cutflow[11][4];

  TString path = p;
  TString balgo = b;

  for(int i=0; i < 3; i++){
    TString decayPath = "";
    if(i == 0) decayPath = path + "/ElEl/ElEl.root";
    if(i == 1) decayPath = path + "/MuMu/MuMu.root";
    if(i == 2) decayPath = path + "/MuEl/MuEl.root";
 
    TFile * f = new TFile(decayPath);

    h[0][i] = (TH1F*) f->Get("Step_5/hMCSig_TTbarbb_Step_5_nbJet30_"+balgo);
    h[1][i] = (TH1F*) f->Get("Step_5/hMC_TTbarcc_Step_5_nbJet30_"+balgo);
    h[2][i] = (TH1F*) f->Get("Step_5/hMC_TTbarll_Step_5_nbJet30_"+balgo);
    h[3][i] = (TH1F*) f->Get("Step_5/hMC_TTbarOthers_Step_5_nbJet30_"+balgo);
    h[4][i] = (TH1F*) f->Get("Step_5/hDataBkg_QCD_Step_5_nbJet30_"+balgo);
    h[5][i] = (TH1F*) f->Get("Step_5/hMC_Wl_Step_5_nbJet30_"+balgo);
    h[6][i] = (TH1F*) f->Get("Step_5/hMC_VV_Step_5_nbJet30_"+balgo);
    h[7][i] = (TH1F*) f->Get("Step_5/hMC_SingleTop_Step_5_nbJet30_"+balgo);
    h[8][i] = (TH1F*) f->Get("Step_5/hMC_DYll_Step_5_nbJet30_"+balgo);
    h[9][i] = (TH1F*) f->Get("Step_5/hData_Step_5_nbJet30_"+balgo);

    double ttjj = h[0][i]->Integral() + h[1][i]->Integral() + h[2][i]->Integral();
    double ttbb = ttjj*R*k;
    double ttcc = ttjj*(1-R)*k*h[1][i]->Integral() / ( h[1][i]->Integral() + h[2][i]->Integral() );  
    double ttLF = ttjj*(1-R)*k*h[2][i]->Integral() / ( h[1][i]->Integral() + h[2][i]->Integral() );
    double newttjj = ttbb + ttcc + ttLF;
  
    if( fit ){
      cutflow[0][i] = ttbb;
      cutflow[1][i] = ttcc;
      cutflow[2][i] = ttLF;
    }else{
      k == 1.0;
      cutflow[0][i] = h[0][i]->Integral();
      cutflow[1][i] = h[1][i]->Integral();
      cutflow[2][i] = h[2][i]->Integral();    
    }

    for(int j=0; j < 9; j++){

      if( j == 4 || j == 8 )  cutflow[j][i] = h[j][i]->Integral(); 
      else cutflow[j][i] = h[j][i]->Integral()*k;

      if( j > 0 && j < 9) cutflow[9][i] += cutflow[j][i];

    }   

    cutflow[10][i] = h[9][i]->Integral();     

  }

  cout << "Final state ("<< balgo.Data() << ")          ~&~  $ee$            ~&~  $\mu\mu$       ~&~ $e\mu$          ~&~  All             \\ \hline " << endl; 

  for(int j = 0; j < 11; j++){
    cutflow[j][3] = cutflow[j][0] + cutflow[j][1] + cutflow[j][2];
    cout << fixed << setprecision (2)  << "&\t" <<  cutflow[j][0] << "\t&\t" << cutflow[j][1] << "\t&\t" << cutflow[j][2] << "\t&\t" << cutflow[j][3] << "\\\\" <<  endl;
  }

}

