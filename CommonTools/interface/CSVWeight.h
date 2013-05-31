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

namespace sysType{ enum sysType{ NA, JERup, JERdown, JESup, JESdown, hfSFup, hfSFdown, lfSFdown, lfSFup, TESup, TESdown, CSVLFup, CSVLFdown, CSVHFup, CSVHFdown, CSVHFStats1up, CSVHFStats1down, CSVLFStats1up, CSVLFStats1down, CSVHFStats2up, CSVHFStats2down, CSVLFStats2up, CSVLFStats2down }; }

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


  // CSV reweighting
  for( int iSys=0; iSys<9; iSys++ ){
    TString syst_csv_suffix_hf = "final";
    TString syst_csv_suffix_lf = "final";
    
    switch( iSys ){
    case 0:
      // this is the nominal case
      break;
    case 1:
      // JESUp
      syst_csv_suffix_hf = "final_JESUp"; syst_csv_suffix_lf = "final_JESUp";
      break;
    case 2:
      // JESDown
      syst_csv_suffix_hf = "final_JESDown"; syst_csv_suffix_lf = "final_JESDown";
      break;
    case 3:
      // purity up
      syst_csv_suffix_hf = "final_LFUp"; syst_csv_suffix_lf = "final_HFUp";
      break;
    case 4:
      // purity down
      syst_csv_suffix_hf = "final_LFDown"; syst_csv_suffix_lf = "final_HFDown";
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

    for( int iPt=0; iPt<3; iPt++ ){
      for( int iEta=0; iEta<3; iEta++ )h_csv_wgt_lf[iSys][iPt][iEta] = (TH1D*)f_CSVwgt_LF->Get( Form("csv_ratio_Pt%i_Eta%i_%s",iPt,iEta,syst_csv_suffix_lf.Data()) );
    }
  }

}


double GetCSVweight(edm::Handle<std::vector<cmg::PFJet> >& iJets, const sysType::sysType iSysType, const bool & lightonly = false){
  //if (isData) return 1.0;

  //CheckSetUp();
  // IMPORTANT! iJets is the *SELECTED* jet collection which you use for your analysis

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
  default : iSysHF = 0; break;
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
  default : iSysLF = 0; break;
  }

  double csvWgthf = 1.;
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

    if ( lightonly == false && (abs(flavor) == 5 || abs(flavor) == 4) ){
      int useCSVBin = (csv>=0.) ? h_csv_wgt_hf[iSysHF][iPt]->FindBin(csv) : 1;
      double iCSVWgtHF = h_csv_wgt_hf[iSysHF][iPt]->GetBinContent(useCSVBin);
      if( iCSVWgtHF!=0 ) csvWgthf *= iCSVWgtHF;

      // if( iSysHF==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      //                          flavor, jetPt, iJet->eta, csv, iCSVWgtHF );
    }
    else {
      if (iPt >=2) iPt=2;       /// [30-40], [40-60] and [60-10000] only 3 Pt bins for lf
      int useCSVBin = (csv>=0.) ? h_csv_wgt_lf[iSysLF][iPt][iEta]->FindBin(csv) : 1;
      double iCSVWgtLF = h_csv_wgt_lf[iSysLF][iPt][iEta]->GetBinContent(useCSVBin);
      if( iCSVWgtLF!=0 ) csvWgtlf *= iCSVWgtLF;

      // if( iSysLF==0 ) printf(" iJet,\t flavor=%d,\t pt=%.1f,\t eta=%.2f,\t csv=%.3f,\t wgt=%.2f \n",
      //                          flavor, jetPt, iJet->eta, csv, iCSVWgtLF );
    }
  }

  double csvWgtTotal = csvWgthf* csvWgtlf;

  return csvWgtTotal;
}
double CSVshape(double csv, int flavor, double up=0, double dw=0 ){
   double weight = 1;//, up=0, dw=0;

   if( abs(flavor) == 5 || abs(flavor) == 4){

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

   return weight;


}

  private:
        // CSV reweighting
       TH1D* h_csv_wgt_hf[9][5];
       TH1D* h_csv_wgt_lf[9][3][3];
       TFile* f_CSVwgt_HF;
       TFile* f_CSVwgt_LF;
};
#endif



