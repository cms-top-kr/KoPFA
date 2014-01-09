#ifndef CSVWeight_H
#define CSVWeight_H

#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <cmath> 
#include <iomanip>
#include <algorithm>
#include "TVector.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1D.h"
#include "TH2D.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "AnalysisDataFormats/CMGTools/interface/BaseJet.h"
#include "AnalysisDataFormats/CMGTools/interface/PFJet.h"
#include "KoPFA/DataFormats/interface/Jet.h"

typedef vector<cmg::PFJet>::const_iterator JI;

namespace sysType{ enum sysType{ NA, JERup, JERdown, JESup, JESdown, hfSFup, hfSFdown, lfSFdown, lfSFup, TESup, TESdown, CSVLFup, CSVLFdown, CSVHFup, CSVHFdown, CSVHFStats1up, CSVHFStats1down, CSVLFStats1up, CSVLFStats1down, CSVHFStats2up, CSVHFStats2down, CSVLFStats2up, CSVLFStats2down, CSVup, CSVdown, CSVup2, CSVdown2, CSVCErr1up, CSVCErr1down, CSVCErr2up, CSVCErr2down,bOrigin }; }

using namespace std;

class CSVWeight
{
   public: 

    explicit CSVWeight(){
        // CSV reweighting
       for( int iSys=0; iSys<9; iSys++ ){
          for( int iPt=0; iPt<5; iPt++ ) h_csv_wgt_hf[iSys][iPt] = NULL;
          for( int iPt=0; iPt<3; iPt++ ){
               for( int iEta=0; iEta<3; iEta++ )h_csv_wgt_lf[iSys][iPt][iEta] = NULL;
          }
       }
/*       for( int iSys=0; iSys<5; iSys++ )
       {
          for( int iPt=0; iPt<5; iPt++ ) c_csv_wgt_hf[iSys][iPt] = NULL;
       }
*/
       f_CSVwgt_HF = NULL;
       f_CSVwgt_LF = NULL;
    }
    ~CSVWeight()
    {}

void SetUpCSVreweighting(){

  // Do not set it up if we're running on collision data
  //if(isData){ return; }
  f_CSVwgt_HF = new TFile ((string(getenv("CMSSW_BASE")) + "/src/KoPFA/CommonTools/data/csv_rwt_hf_IT.root").c_str());
  f_CSVwgt_LF = new TFile ((string(getenv("CMSSW_BASE")) + "/src/KoPFA/CommonTools/data/csv_rwt_lf_IT.root").c_str());

  f_ttbb_csv = new TFile ((string(getenv("CMSSW_BASE")) + "/src/KoPFA/CommonTools/data/ttbb_csv.root").c_str());
  TString ttbb_csv_first_C[4] = {"csv_first_30_35_center" ,
                                 "csv_first_35_40_center" ,
                                 "csv_first_40_50_center" ,
                                 "csv_first_50_center"};
  TString ttbb_csv_first_F[4] = {"csv_first_30_35_forward",
                                 "csv_first_35_40_forward",
                                 "csv_first_40_50_forward",
                                 "csv_first_50_forward"};  
  TString ttbb_csv_second_C[4] ={"csv_second_30_35_center" ,
                                 "csv_second_35_40_center" ,
                                 "csv_second_40_50_center" ,
                                 "csv_second_50_center"};
 TString ttbb_csv_second_F[4] = {"csv_second_30_35_forward",
                                 "csv_second_35_40_forward",
                                 "csv_second_40_50_forward",
                                 "csv_second_50_forward"};   

//    for( int iEta=0; iEta<2; iEta++ ) 
    for( int iPt=0; iPt<4; iPt++ ) 
    {
      h_ttbb_csv_LF_SF[0][0][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s",ttbb_csv_first_C[iPt].Data() ) );
      h_ttbb_csv_LF_SF[1][0][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s",ttbb_csv_second_C[iPt].Data() ) );
      h_ttbb_csv_LF_SF[0][1][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s",ttbb_csv_first_F[iPt].Data() ) );
      h_ttbb_csv_LF_SF[1][1][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s",ttbb_csv_second_F[iPt].Data() ) );

      h_ttbb_csv_LF_SFup[0][0][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s_Up_bFlavor",ttbb_csv_first_C[iPt].Data() ) );
      h_ttbb_csv_LF_SFup[1][0][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s_Up_bFlavor",ttbb_csv_second_C[iPt].Data() ) );
      h_ttbb_csv_LF_SFup[0][1][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s_Up_bFlavor",ttbb_csv_first_F[iPt].Data() ) );
      h_ttbb_csv_LF_SFup[1][1][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s_Up_bFlavor",ttbb_csv_second_F[iPt].Data() ) );

      h_ttbb_csv_LF_SFdw[0][0][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s_Dw_bFlavor",ttbb_csv_first_C[iPt].Data() ) );
      h_ttbb_csv_LF_SFdw[1][0][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s_Dw_bFlavor",ttbb_csv_second_C[iPt].Data() ) );
      h_ttbb_csv_LF_SFdw[0][1][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s_Dw_bFlavor",ttbb_csv_first_F[iPt].Data() ) );
      h_ttbb_csv_LF_SFdw[1][1][iPt] = (TH1F*)f_ttbb_csv->Get( Form("%s_Dw_bFlavor",ttbb_csv_second_F[iPt].Data() ) );


    }

//////////////////////
/*
// adderror
  f_addError = new TFile ((string(getenv("CMSSW_BASE")) + "/src/KoPFA/CommonTools/data/adderror.root").c_str());
  h_adderr = (TH1F*) f_addError->Get(Form("SFbfTnfT"));
*/
// new CSV SF
  f_new_CSV_SF = new TFile ((string(getenv("CMSSW_BASE")) + "/src/KoPFA/CommonTools/data/new_CSV_SF.root").c_str());
  for(int iPt=0;iPt<3;iPt++) for(int iEta=0;iEta<3;iEta++)
  {
     h_LF_CSV_SF[0][iPt][iEta] = (TH1F*) f_new_CSV_SF->Get(Form("LFPt%dEta%d",iPt,iEta));
     h_HF_CSV_SF[0][iPt][iEta] = (TH1F*) f_new_CSV_SF->Get(Form("HFPt%dEta%d",iPt,iEta));

     int bin = h_LF_CSV_SF[0][iPt][iEta]->GetNbinsX();
     h_LF_CSV_SF[1][iPt][iEta] = (TH1F *) f_new_CSV_SF->Get(Form("LFPt%dEta%dHFup",iPt,iEta));
     h_LF_CSV_SF[2][iPt][iEta] = (TH1F *) f_new_CSV_SF->Get(Form("LFPt%dEta%dHFdw",iPt,iEta));

     h_HF_CSV_SF[1][iPt][iEta] = (TH1F *) f_new_CSV_SF->Get(Form("HFPt%dEta%dHFup",iPt,iEta));
     h_HF_CSV_SF[2][iPt][iEta] = (TH1F *) f_new_CSV_SF->Get(Form("HFPt%dEta%dHFdw",iPt,iEta));

     h_LF_CSV_SF[3][iPt][iEta] = (TH1F *) f_new_CSV_SF->Get(Form("LFPt%dEta%dLFup",iPt,iEta));
     h_LF_CSV_SF[4][iPt][iEta] = (TH1F *) f_new_CSV_SF->Get(Form("LFPt%dEta%dLFdw",iPt,iEta));

     h_HF_CSV_SF[3][iPt][iEta] = (TH1F *) f_new_CSV_SF->Get(Form("HFPt%dEta%dLFup",iPt,iEta));
     h_HF_CSV_SF[4][iPt][iEta] = (TH1F *) f_new_CSV_SF->Get(Form("HFPt%dEta%dLFdw",iPt,iEta));
 
  }
///////////////////////
  // CSV reweighting
  for( int iSys=0; iSys<9; iSys++ ){
    TString syst_csv_suffix_hf = "final";
    TString syst_csv_suffix_c  = "final";
    TString syst_csv_suffix_lf = "final";
    
    switch( iSys ){
    case 0:
      // this is the nominal case
      break;
    case 1:
      // JESUp
      syst_csv_suffix_hf = "final_JESUp"; syst_csv_suffix_lf = "final_JESUp";
      syst_csv_suffix_c  = "final_cErr1Up";
      break;
    case 2:
      // JESDown
      syst_csv_suffix_hf = "final_JESDown"; syst_csv_suffix_lf = "final_JESDown";
      syst_csv_suffix_c  = "final_cErr1Down";
      break;
    case 3:
      // purity up
      syst_csv_suffix_hf = "final_LFUp"; syst_csv_suffix_lf = "final_HFUp";
      syst_csv_suffix_c  = "final_cErr2Up";
      break;
    case 4:
      // purity down
      syst_csv_suffix_hf = "final_LFDown"; syst_csv_suffix_lf = "final_HFDown";
      syst_csv_suffix_c  = "final_cErr2Down";
      break;
    case 5:
      // stats1 up
      syst_csv_suffix_hf = "final_Stats1Up"; syst_csv_suffix_lf = "final_Stats1Up";
      break;
    case 6:
      // stats1 down
      syst_csv_suffix_hf = "final_Stats1Down"; syst_csv_suffix_lf = "final_Stats1Down";
      break;
    case 7:
      // stats2 up
      syst_csv_suffix_hf = "final_Stats2Up"; syst_csv_suffix_lf = "final_Stats2Up";
      break;
    case 8:
      // stats2 down
      syst_csv_suffix_hf = "final_Stats2Down"; syst_csv_suffix_lf = "final_Stats2Down";
      break;
    }

    for( int iPt=0; iPt<5; iPt++ ) h_csv_wgt_hf[iSys][iPt] = (TH1D*)f_CSVwgt_HF->Get( Form("csv_ratio_Pt%i_Eta0_%s",iPt,syst_csv_suffix_hf.Data()) );
  
//    if( iSys<5 ){
//     for( int iPt=0; iPt<5; iPt++ ) c_csv_wgt_hf[iSys][iPt] = (TH1D*)f_CSVwgt_HF->Get( Form("c_csv_ratio_Pt%i_Eta0_%s",iPt,syst_csv_suffix_c.Data()) );
//    }
    for( int iPt=0; iPt<3; iPt++ ){
      for( int iEta=0; iEta<3; iEta++ )h_csv_wgt_lf[iSys][iPt][iEta] = (TH1D*)f_CSVwgt_LF->Get( Form("csv_ratio_Pt%i_Eta%i_%s",iPt,iEta,syst_csv_suffix_lf.Data()) );
    }
  }

}
////////////////////////
//for new CSV SF
double GetNewCSVweight(edm::Handle<std::vector<cmg::PFJet> >& iJets, int iSys=0){
// iLF : 0(normal), 1(up), 2(dw)
// iHF : 0(normal), 1(up), 2(dw)
  double csvWgthf = 1.;
  double csvWgtlf = 1.;

  for( JI iJet = iJets->begin(); iJet != iJets->end(); ++iJet ){ 
    double csv = iJet->bDiscriminator("combinedSecondaryVertexBJetTags");
    double jetPt = iJet->p4().pt();
    double jetAbsEta = fabs( iJet->p4().eta() );
    int flavor = abs( iJet->partonFlavour());
    int iPt = -1; int iEta = -1;
    if (jetPt >=30 && jetPt<50) iPt = 0;
    else if (jetPt >=50 && jetPt<80) iPt = 1;
    else if (jetPt >=80) iPt = 2;

    if (jetAbsEta >=0 &&  jetAbsEta<0.8) iEta = 0;
    else if ( jetAbsEta>=0.8 && jetAbsEta<1.6) iEta = 1;
    else if ( jetAbsEta>=1.6 && jetAbsEta<2.5) iEta = 2;

    if (iPt < 0 || iEta < 0) std::cout << "Error, couldn't find Pt, Eta bins for this b-flavor jet, jetPt = " << jetPt << ", jetAbsEta = " << jetAbsEta << std::endl;
    else if ( (abs(flavor) == 5) ){
      int useCSVBin = (csv>=0.) ? h_HF_CSV_SF[iSys][iPt][iEta]->FindBin(csv) : 1;
      double iCSVWgtHF = h_HF_CSV_SF[iSys][iPt][iEta]->GetBinContent(useCSVBin);
      if( iCSVWgtHF>0.05 ) csvWgthf *= iCSVWgtHF;

      // if( iSysHF==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      //                          flavor, jetPt, iJet->eta, csv, iCSVWgtHF );
    }
    else if ( (abs(flavor) == 4) ){
      int useCSVBin = (csv>=0.) ? h_LF_CSV_SF[iSys][iPt][iEta]->FindBin(csv) : 1;
      double iCSVWgtHF = h_LF_CSV_SF[iSys][iPt][iEta]->GetBinContent(useCSVBin);
      //if(iHF==1) iCSVWgtHF+= h_HF_CSV_SF[0][iPt][iEta]->GetBinError(useCSVBin); 
      //if(iHF==2) iCSVWgtHF-= h_HF_CSV_SF[iHF][iPt][iEta]->GetBinError(useCSVBin);
      if( iCSVWgtHF>0.05 ) csvWgthf *= iCSVWgtHF;

      // if( iSysHF==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      //                          flavor, jetPt, iJet->eta, csv, iCSVWgtHF );
    }
    else {
      if (iPt >=2) iPt=2;       /// [30-40], [40-60] and [60-10000] only 3 Pt bins for lf
      int useCSVBin = (csv>=0.) ? h_LF_CSV_SF[iSys][iPt][iEta]->FindBin(csv) : 1;
      double iCSVWgtLF = h_LF_CSV_SF[iSys][iPt][iEta]->GetBinContent(useCSVBin);
      if( iCSVWgtLF>0.05 ) csvWgtlf *= iCSVWgtLF;

      // if( iSysLF==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      //                          flavor, jetPt, iJet->eta, csv, iCSVWgtLF );
    }
  }

  double csvWgtTotal = csvWgthf* csvWgtlf;

  return csvWgtTotal;
}



/////////////////////////
double GetCSVweight(edm::Handle<std::vector<cmg::PFJet> >& iJets, const sysType::sysType iSysType, const bool & lightonly = false){
  //if (isData) return 1.0;

  //CheckSetUp();
  // IMPORTANT! iJets is the *SELECTED* jet collection which you use for your analysis

  bool usAdEr = false;
  int iSysHF = 0;
  switch(iSysType){
  case sysType::JESup:             iSysHF=1; break;
  case sysType::JESdown:         iSysHF=2; break;
  case sysType::CSVLFup:         iSysHF=3; break;
  case sysType::CSVLFdown:       iSysHF=4; break;
  case sysType::CSVHFStats1up:     iSysHF=5; break;
  case sysType::CSVHFStats1down: iSysHF=6; break;
  case sysType::CSVHFStats2up:     iSysHF=7; break;
  case sysType::CSVHFStats2down: iSysHF=8; break;
  case sysType::CSVup:         iSysHF=4; break;
  case sysType::CSVdown:       iSysHF=3; break;
  case sysType::CSVup2:         iSysHF=3; break;
  case sysType::CSVdown2:       iSysHF=4; break;
  case sysType::bOrigin:       iSysHF=1; usAdEr=true; break;
  default : iSysHF = 0; break;
  }

  int iSysC = 0;
  switch(iSysType){
  case sysType::CSVCErr1up:   iSysC=1; break;
  case sysType::CSVCErr1down: iSysC=2; break;
  case sysType::CSVCErr2up:   iSysC=3; break;
  case sysType::CSVCErr2down: iSysC=4; break;
  default : iSysC = 0; break;
  }

  int iSysLF = 0;
  switch(iSysType){
  case sysType::JESup:             iSysLF=1; break;
  case sysType::JESdown:         iSysLF=2; break;
  case sysType::CSVHFup:         iSysLF=3; break;
  case sysType::CSVHFdown:       iSysLF=4; break;
  case sysType::CSVLFStats1up:     iSysLF=5; break;
  case sysType::CSVLFStats1down: iSysLF=6; break;
  case sysType::CSVLFStats2up:     iSysLF=7; break;
  case sysType::CSVLFStats2down: iSysLF=8; break;
  case sysType::CSVup:         iSysLF=4; break;
  case sysType::CSVdown:       iSysLF=3; break;
  case sysType::CSVup2:         iSysLF=4; break;
  case sysType::CSVdown2:       iSysLF=3; break;
  default : iSysLF = 0; break;
  }

  double csvWgthf = 1.;
  double csvWgtC  = 1.;
  double csvWgtlf = 1.;

  for( JI iJet = iJets->begin(); iJet != iJets->end(); ++iJet ){ 
    double csv = iJet->bDiscriminator("combinedSecondaryVertexBJetTags");
    double jetPt = iJet->p4().pt();
    double jetAbsEta = fabs( iJet->p4().eta() );
    int flavor = abs( iJet->partonFlavour());
    int iPt = -1; int iEta = -1;
    if (jetPt >=29.99 && jetPt<40) iPt = 0;
    else if (jetPt >=40 && jetPt<60) iPt = 1;
    else if (jetPt >=60 && jetPt<100) iPt = 2;
    else if (jetPt >=100 && jetPt<160) iPt = 3;
    else if (jetPt >=160 && jetPt<10000) iPt = 4;

    if (jetAbsEta >=0 &&  jetAbsEta<0.8) iEta = 0;
    else if ( jetAbsEta>=0.8 && jetAbsEta<1.6) iEta = 1;
    else if ( jetAbsEta>=1.6 && jetAbsEta<2.5) iEta = 2;

    if (iPt < 0 || iEta < 0) std::cout << "Error, couldn't find Pt, Eta bins for this b-flavor jet, jetPt = " << jetPt << ", jetAbsEta = " << jetAbsEta << std::endl;
    //else if ( lightonly == false && (abs(flavor) == 5 || abs(flavor) == 4) ){
    else if ( lightonly == false && (abs(flavor) == 5 ||  abs(flavor) == 4) ){
      int useCSVBin = (csv>=0.) ? h_csv_wgt_hf[iSysHF][iPt]->FindBin(csv) : 1;
      double iCSVWgtHF = h_csv_wgt_hf[iSysHF][iPt]->GetBinContent(useCSVBin);

      int useCSVBin2 = (csv>=0.) ? h_adderr->FindBin(csv) : -1;
      double iCSVWgtHF2 = 1.;//h_adderr->GetBinContent(useCSVBin2);
      if(useCSVBin2>0) iCSVWgtHF2 = h_adderr->GetBinContent(useCSVBin2);

      if( iCSVWgtHF!=0 && usAdEr && iCSVWgtHF2!=0) csvWgthf *= iCSVWgtHF*iCSVWgtHF2;
      else if( iCSVWgtHF!=0 )                      csvWgthf *= iCSVWgtHF;


      // if( iSysHF==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      //                          flavor, jetPt, iJet->eta, csv, iCSVWgtHF );
    }
  /*  else if( abs(flavor) == 4 ){
      // do nothing
      int useCSVBin = (csv>=0.) ? c_csv_wgt_hf[iSysC][iPt]->FindBin(csv) : 1;
      double iCSVWgtC = c_csv_wgt_hf[iSysC][iPt]->GetBinContent(useCSVBin);
      if( iCSVWgtC!=0 ) csvWgtC *= iCSVWgtC;
      // if( iSysC==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      //                             flavor, jetPt, iJet->eta, csv, iCSVWgtC );
    }*/
    else {
      if (iPt >=2) iPt=2;       /// [30-40], [40-60] and [60-10000] only 3 Pt bins for lf
      int useCSVBin = (csv>=0.) ? h_csv_wgt_lf[iSysLF][iPt][iEta]->FindBin(csv) : 1;
      double iCSVWgtLF = h_csv_wgt_lf[iSysLF][iPt][iEta]->GetBinContent(useCSVBin);
      if( iCSVWgtLF!=0 ) csvWgtlf *= iCSVWgtLF;

      // if( iSysLF==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      //                          flavor, jetPt, iJet->eta, csv, iCSVWgtLF );
    }
  }

  //double csvWgtTotal = csvWgthf* csvWgtlf;
  double csvWgtTotal = csvWgthf * csvWgtC * csvWgtlf;


  return csvWgtTotal;
}

double CSVshape(double csv, double pt, double eta, int flavor, int JetN, double up=0, double dw=0 ){
   double weight = 1;//, up=0, dw=0;

   if( abs(flavor) == 5 ){

       // https://indico.cern.ch/getFile.py/access?contribId=3&sessionId=1&resId=1&materialId=slides&confId=252874 
       if(0.00<= csv && csv < 0.04 )     weight= 0.46 + up* 0.66  - dw*0.7  ;
       if(0.04<= csv && csv < 0.08 )     weight= 0.57 + up* 0.62  - dw*0.39 ;
       if(0.08<= csv && csv < 0.12 )     weight= 0.53 + up* 0.43  - dw*0.4  ;
       if(0.12<= csv && csv < 0.16 )     weight= 1.28 + up* 0.28  - dw*0.25 ;
       if(0.16<= csv && csv < 0.20 )     weight= 1.16 + up* 0.38  - dw*0.38 ;
       if(0.20<= csv && csv <0.244 )     weight= 1.06 + up* 0.25  - dw*0.24 ;
       if(0.244<= csv && csv<0.28  )     weight= 1.77 + up* 0.39  - dw*0.45 ;
       if(0.28<= csv && csv < 0.32 )     weight= 1.2  + up* 0.25  - dw*0.19 ;
       if(0.32<= csv && csv < 0.36 )     weight= 1.34 + up* 0.27  - dw*0.23 ;
       if(0.36<= csv && csv < 0.40 )     weight= 0.9  + up* 0.24  - dw*0.35 ;
       if(0.40<= csv && csv < 0.44 )     weight= 1.48 + up* 0.27  - dw*0.33 ;
       if(0.44<= csv && csv < 0.48 )     weight= 1.11 + up* 0.17  - dw*0.17 ;
       if(0.48<= csv && csv < 0.52 )     weight= 1.42 + up* 0.35  - dw*0.2  ;
       if(0.52<= csv && csv < 0.56 )     weight= 1.25 + up* 0.23  - dw*0.18 ;
       if(0.56<= csv && csv < 0.60 )     weight= 1.27 + up* 0.28  - dw*0.22 ;
       if(0.60<= csv && csv < 0.64 )     weight= 1.12 + up* 0.19  - dw*0.23 ;
       if(0.64<= csv && csv < 0.679)     weight= 1.16 + up* 0.2   - dw*0.17 ;
       if(0.679<= csv && csv < 0.72)     weight= 1.04 + up* 0.24  - dw*0.17 ;
       if(0.72<= csv && csv < 0.76 )     weight= 1.27 + up* 0.16  - dw*0.2  ;
       if(0.76<= csv && csv < 0.80 )     weight= 0.99 + up* 0.11  - dw*0.11 ;
       if(0.80<= csv && csv < 0.84 )     weight= 0.98 + up* 0.15  - dw*0.14 ;
       if(0.84<= csv && csv < 0.898)     weight= 0.91 + up* 0.08  - dw*0.06 ;
       if(0.898<= csv && csv < 0.92)     weight= 0.99 + up* 0.08  - dw*0.06 ;
       if(0.92<= csv && csv < 0.96 )     weight= 1.03 + up* 0.04  - dw*0.04 ;
       if(0.96<= csv && csv < 1.00 )     weight= 0.97 + up* 0.02  - dw*0.02 ;

   }
   else {
       //for additional jet of light flavor in TTBB
       int iPt = -1; int iEta = -1;
       if (pt >=30 && pt<35) iPt = 0;
       else if (pt >=35 && pt<40) iPt = 1;
       else if (pt >=40 && pt<50) iPt = 2;
       else if (pt >=50) iPt = 3;
       
       if(fabs(eta) < 1.1) iEta = 0;
       else                iEta = 1;
       
       if(iPt>-1)
       { 
         int JetN_ = JetN%2; 
         if(up==0 && dw==0)
         {
            int useCSVBin = h_ttbb_csv_LF_SF[JetN_][iEta][iPt]->FindBin(csv);
            double iCSVWgt = h_ttbb_csv_LF_SF[JetN_][iEta][iPt]->GetBinContent(useCSVBin);
            if( iCSVWgt!=0 ) weight =iCSVWgt;
         }
         else if(up==0)
         {
            int useCSVBin = h_ttbb_csv_LF_SFdw[JetN_][iEta][iPt]->FindBin(csv);
            double iCSVWgt = h_ttbb_csv_LF_SFdw[JetN_][iEta][iPt]->GetBinContent(useCSVBin);
            if( iCSVWgt!=0 ) weight =iCSVWgt;
         }
         else if(dw==0)
         {
            int useCSVBin = h_ttbb_csv_LF_SFup[JetN_][iEta][iPt]->FindBin(csv);
            double iCSVWgt = h_ttbb_csv_LF_SFup[JetN_][iEta][iPt]->GetBinContent(useCSVBin);
            if( iCSVWgt!=0 ) weight =iCSVWgt;
         }
       }
   }

   return weight;


}

  private:
        // CSV reweighting
       TH1D* h_csv_wgt_hf[9][5];
//       TH1D* c_csv_wgt_hf[9][5];
       TH1D* h_csv_wgt_lf[9][3][3];
       TFile* f_CSVwgt_HF;
       TFile* f_CSVwgt_LF;
       TH1F* h_ttbb_csv_LF_SF[2][2][4];
       TH1F* h_ttbb_csv_LF_SFup[2][2][4];
       TH1F* h_ttbb_csv_LF_SFdw[2][2][4];
       TFile* f_ttbb_csv;

       TFile *f_new_CSV_SF;
       TH1F *h_LF_CSV_SF[5][3][3];
       TH1F *h_HF_CSV_SF[5][3][3];

       TFile *f_addError;
       TH1F *h_adderr;

};
#endif



