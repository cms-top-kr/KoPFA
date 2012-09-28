#include "KoPFA/CMGAnalyzer/interface/cmgElectronAnalyzer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "PhysicsTools/SelectorUtils/interface/SimpleCutBasedElectronIDSelectionFunctor.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"

using namespace std;

cmgElectronAnalyzer::cmgElectronAnalyzer(const edm::ParameterSet& cfg)
{
  electronLabel_ = cfg.getParameter<edm::InputTag>("electronLabel");
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");
  metLabel_ = cfg.getParameter<edm::InputTag>("metLabel");
  jetLabel_ = cfg.getParameter<edm::InputTag>("jetLabel");
  vertexLabel_ =  cfg.getUntrackedParameter<edm::InputTag>("vertexLabel");
  rhoIsoLabel_ =  cfg.getUntrackedParameter<edm::InputTag>("rhoIsoLabel");
  useZMassWindow_ =  cfg.getUntrackedParameter<bool>("useZMassWindow");

  produces<std::vector<cmg::Electron> >("");

  edm::Service<TFileService> fs;

  for(int d=0 ; d < 2 ; d++){
    for(int i=0 ; i < 3 ; i++){
      for(int k=0 ; k <2 ; k++){
      TString dirName = "";
        if(d == 0){
          if(k==1){
            if(i==0) dirName = "ID/Barrel";
            if(i==1) dirName = "Iso/Barrel";
            if(i==2) dirName = "Passed/Barrel";
          }else if(k==0){
            if(i==0) dirName = "ID/Endcap";
            if(i==1) dirName = "Iso/Endcap";
            if(i==2) dirName = "Passed/Endcap";
          }
        }else if(d == 1){
          if(k==1){
            if(i==0) dirName = "ID/Barrel/QCD";
            if(i==1) dirName = "Iso/Barrel/QCD";
            if(i==2) dirName = "Passed/Barrel/QCD";
          }else if(k==0){
            if(i==0) dirName = "ID/Endcap/QCD";
            if(i==1) dirName = "Iso/Endcap/QCD";
            if(i==2) dirName = "Passed/Endcap/QCD";
          }
        }
        TFileDirectory dir = fs->mkdir(Form("%s",dirName.Data()));
        h_mvaTrigV0[d][i][k] = dir.make<TH1F>( "h_mvaTrigV0", "h_mvaTrigV0", 200, -1, 1);
        h_pfRelIso03[d][i][k] = dir.make<TH1F>( "h_pfRelIso03", "h_pfRelIso03", 500, 0, 5);
        h_pfRelIso04[d][i][k] = dir.make<TH1F>( "h_pfRelIso04", "h_pfRelIso04", 500, 0, 5);
        h_pfRelIso03db[d][i][k] = dir.make<TH1F>( "h_pfRelIso03db", "h_pfRelIso03db", 500, 0, 5);
        h_pfRelIso04db[d][i][k] = dir.make<TH1F>( "h_pfRelIso04db", "h_pfRelIso04db", 500, 0, 5);
        h_pfRelIso03rho[d][i][k] = dir.make<TH1F>( "h_pfRelIso03rho", "h_pfRelIso03rho", 500, 0, 5);
        h_pfRelIso04rho[d][i][k] = dir.make<TH1F>( "h_pfRelIso04rho", "h_pfRelIso04rho", 500, 0, 5);
        h_mtW[d][i][k] = dir.make<TH1F>( "h_mtW", "h_mtW", 200, 0, 200);
        h_dimass[d][i][k] = dir.make<TH1F>( "h_dimass", "h_dimass", 200, 0, 200);
        h_dR[d][i][k] = dir.make<TH1F>( "h_dR", "h_dR", 100, 0, 1);
        h_nJet[d][i][k] = dir.make<TH1F>( "h_nJet", "h_nJet", 10, 0, 10);
        h_met[d][i][k] = dir.make<TH1F>( "h_met", "h_met", 20, 0, 200);

        h2_mvaTrigV0[d][i][k] = dir.make<TH2F>( "h2_mvaTrigV0", "h2_mvaTrigV0", 60,0,60,200, -1, 1);
        h2_pfRelIso03[d][i][k] = dir.make<TH2F>( "h2_pfRelIso03", "h2_pfRelIso03", 60,0,60,500, 0, 5);
        h2_pfRelIso04[d][i][k] = dir.make<TH2F>( "h2_pfRelIso04", "h2_pfRelIso04", 60,0,60,500, 0, 5);
        h2_pfRelIso03db[d][i][k] = dir.make<TH2F>( "h2_pfRelIso03db", "h2_pfRelIso03db", 60,0,60,500, 0, 5);
        h2_pfRelIso04db[d][i][k] = dir.make<TH2F>( "h2_pfRelIso04db", "h2_pfRelIso04db", 60,0,60,500, 0, 5);
        h2_pfRelIso03rho[d][i][k] = dir.make<TH2F>( "h2_pfRelIso03rho", "h2_pfRelIso03rho", 60,0,60,500, 0, 5);
        h2_pfRelIso04rho[d][i][k] = dir.make<TH2F>( "h2_pfRelIso04rho", "h2_pfRelIso04rho", 60,0,60,500, 0, 5);

      }
    }
  }
//////////////////////////
  for(int d=0 ; d < 2 ; d++){
    for(int i=0 ; i < 2 ; i++){
      TString dirName = "";
        if(d == 0){
            if(i==1) dirName = "GoodIDed/Barrel";
            if(i==0) dirName = "GoodIDed/Endcap";
        }else if(d==1){
            if(i==1) dirName = "PFIDed/Barrel";
            if(i==0) dirName = "PFIDed/Endcap";
        }
        TFileDirectory dir2 = fs->mkdir(Form("%s",dirName.Data()));
        h_pt[d][i] = dir2.make<TH1F>( "h_pt", "h_pt", 200, 0, 200);
        h_eta[d][i] = dir2.make<TH1F>( "h_eta", "h_eta", 50, -2.5, 2.5);
        h_pv[d][i] = dir2.make<TH1F>( "h_pv", "h_pv", 200, 0, 80);
        h_njet[d][i] = dir2.make<TH1F>( "h_njet", "h_njet", 20, 0, 20);
    }
  }  
////////////////////////
}

cmgElectronAnalyzer::~cmgElectronAnalyzer()
{

}

void cmgElectronAnalyzer::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;

  const bool isRealData = iEvent.isRealData();

  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  iEvent.getByLabel(electronLabel_, electrons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 
  iEvent.getByLabel(jetLabel_, Jets);
  iEvent.getByLabel(vertexLabel_,recVtxs_);
  iEvent.getByLabel(metLabel_,MET_);
  std::vector<cmg::BaseMET>::const_iterator mi = MET_->begin();
  //cmg::METCollection::const_iterator mi = MET_->begin();
  const double MET = mi->pt();

  int nvertex = recVtxs_->size();
  
  std::auto_ptr<std::vector<cmg::Electron> > pos(new std::vector<cmg::Electron>());

  //preselection
  for (unsigned int i=0; i < electrons_->size(); ++i){

    cmg::Electron electron = electrons_->at(i);

    //bool passPre = electron.pt() > 20 && fabs(electron.eta()) < 2.5 && fabs(electron.gsfTrack()->dxy(beamSpot_->position())) < 0.04;
    bool passPre = electron.pt() > 20 && fabs(electron.eta()) < 2.5;
    bool passTrig = trainTrigPresel(electron);//->get());

    if( !passPre ) continue;
    if( !passTrig ) continue;

    pos->push_back((*electrons_)[i]);

  }

 
  std::auto_ptr<std::vector<cmg::PFJet> > cleanedJets(new std::vector<cmg::PFJet>());

  for (unsigned int j=0 ; j < Jets->size(); j++) {
    cmg::PFJet jet = Jets->at(j);

    if( !(jet.pt() > 30 && abs(jet.eta()) < 2.5) ) continue;
    bool overlap = false;
    
    for (unsigned int i=0; i < pos->size(); ++i){
      cmg::Electron electron = pos->at(i);

      /*
      reco::isodeposit::Direction Dir = Direction(electron.sourcePtr()->get()->superCluster()->eta(), electron.sourcePtr()->get()->superCluster()->phi());

      reco::IsoDeposit::AbsVetos vetos_ch;
      reco::IsoDeposit::AbsVetos vetos_ph;
      reco::IsoDeposit::AbsVetos vetos_nh;

      if( abs( electron.sourcePtr()->get()->superCluster()->eta() ) > 1.479 ){
        vetos_ch.push_back(new ConeVeto( Dir, 0.015 ));
        vetos_ph.push_back(new ConeVeto( Dir, 0.08 ));
      }*/

      double chIso03 = electron.chargedHadronIso(0.3);
      double puChIso03 = electron.puChargedHadronIso(0.3);
      double nhIso03 = electron.neutralHadronIso(0.3);
      double phIso03 = electron.photonIso(0.3);

      double relPfIso03 = ( chIso03 + nhIso03 + phIso03 )/ electron.pt();
      double mvaTrigV0 = electron.sourcePtr()->get()->electronID("mvaTrigV0");
 
      bool pass = mvaTrigV0 > 0.0 && relPfIso03 < 0.2;
      if( !pass ) continue;

      double dR= sqrt( (electron.eta()-jet.eta())*(electron.eta()-jet.eta()) + (electron.phi()-jet.phi())*(electron.phi()-jet.phi()) );
      if( dR < 0.5 ) {
        overlap = true;
        break;
      }
    }

    if( !overlap ) cleanedJets->push_back( (*Jets)[j] );
  }

  int nJets = cleanedJets->size();

  edm::Handle<double>  rho_;
  iEvent.getByLabel(rhoIsoLabel_, rho_);
  double rhoIso = *(rho_.product());

  double mtW = 0.0;
  if( pos->size() >=1) {
    const cmg::Electron leading = pos->at(0);
    mtW =  transverseMass( leading.p4() , mi->p4() );
  }

  if( pos->size() >=2 ){  
    for (unsigned int i=0; i < pos->size()-1; ++i){
      for (unsigned int j=i+1; j < pos->size(); ++j){
	cmg::Electron Lep1 = electrons_->at(i);
	cmg::Electron Lep2 = electrons_->at(j);

        float AEff03Lep1 = 0.00;
        float AEff03Lep2 = 0.00; 
        float AEff04Lep1 = 0.00;
        float AEff04Lep2 = 0.00;

        if(isRealData){
          AEff03Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, Lep1.sourcePtr()->get()->superCluster()->eta(), ElectronEffectiveArea::kEleEAData2011);
          AEff03Lep2 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, Lep2.sourcePtr()->get()->superCluster()->eta(), ElectronEffectiveArea::kEleEAData2011);
          AEff04Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04, Lep1.sourcePtr()->get()->superCluster()->eta(), ElectronEffectiveArea::kEleEAData2012);
          AEff04Lep2 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04, Lep2.sourcePtr()->get()->superCluster()->eta(), ElectronEffectiveArea::kEleEAData2011);
        }else{
          AEff03Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, Lep1.sourcePtr()->get()->superCluster()->eta(), ElectronEffectiveArea::kEleEAFall11MC);
          AEff03Lep2 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, Lep2.sourcePtr()->get()->superCluster()->eta(), ElectronEffectiveArea::kEleEAFall11MC);
          AEff04Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04, Lep1.sourcePtr()->get()->superCluster()->eta(), ElectronEffectiveArea::kEleEAFall11MC);
          AEff04Lep2 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04, Lep2.sourcePtr()->get()->superCluster()->eta(), ElectronEffectiveArea::kEleEAFall11MC);
        }

	double chIso03Lep1 = Lep1.chargedHadronIso(0.3);
	double puChIso03Lep1 = Lep1.puChargedHadronIso(0.3);
	double nhIso03Lep1 = Lep1.neutralHadronIso(0.3);
	double phIso03Lep1 = Lep1.photonIso(0.3);
  
        double chIso03Lep2 = Lep2.chargedHadronIso(0.3);
        double puChIso03Lep2 = Lep2.puChargedHadronIso(0.3);
        double nhIso03Lep2 = Lep2.neutralHadronIso(0.3);
        double phIso03Lep2 = Lep2.photonIso(0.3);
 
        double chIso04Lep1 = Lep1.chargedHadronIso(0.4);
        double puChIso04Lep1 = Lep1.puChargedHadronIso(0.4);
        double nhIso04Lep1 = Lep1.neutralHadronIso(0.4);
        double phIso04Lep1 = Lep1.photonIso(0.4);

        double chIso04Lep2 = Lep2.chargedHadronIso(0.4);
        double puChIso04Lep2 = Lep2.puChargedHadronIso(0.4);
        double nhIso04Lep2 = Lep2.neutralHadronIso(0.4);
        double phIso04Lep2 = Lep2.photonIso(0.4);

	double mvaTrigV0Lep1 = Lep1.sourcePtr()->get()->electronID("mvaTrigV0");
	double relPfIso03Lep1 = ( chIso03Lep1 + nhIso03Lep1 + phIso03Lep1 )/ Lep1.pt(); 
	double relPfIso04Lep1 = ( chIso04Lep1 + nhIso04Lep1 + phIso04Lep1 )/ Lep1.pt();
        double relPfIso03dbLep1 = ( chIso03Lep1 + max(0.0, nhIso03Lep1 + phIso03Lep1 - 0.5*puChIso03Lep1) )/ Lep1.pt();
        double relPfIso04dbLep1 = ( chIso04Lep1 + max(0.0, nhIso04Lep1 + phIso04Lep1 - 0.5*puChIso04Lep1) )/ Lep1.pt();
        double relPfIso03rhoLep1 = ( chIso03Lep1 + max(0.0, nhIso03Lep1 + phIso03Lep1 - rhoIso*AEff03Lep1) )/ Lep1.pt();
        double relPfIso04rhoLep1 = ( chIso04Lep1 + max(0.0, nhIso04Lep1 + phIso04Lep1 - rhoIso*AEff04Lep1) )/ Lep1.pt();


	double mvaTrigV0Lep2 = Lep2.sourcePtr()->get()->electronID("mvaTrigV0");
	double relPfIso03Lep2 = ( chIso03Lep2 + nhIso03Lep2 + phIso03Lep2 )/ Lep2.pt();
	double relPfIso04Lep2 = ( chIso04Lep2 + nhIso04Lep2 + phIso04Lep2 )/ Lep2.pt();
        double relPfIso03dbLep2 = ( chIso03Lep2 + max(0.0, nhIso03Lep2 + phIso03Lep2 - 0.5*puChIso03Lep2) )/ Lep2.pt();
        double relPfIso04dbLep2 = ( chIso04Lep2 + max(0.0, nhIso04Lep2 + phIso04Lep2 - 0.5*puChIso04Lep2) )/ Lep2.pt();
        double relPfIso03rhoLep2 = ( chIso03Lep2 + max(0.0, nhIso03Lep2 + phIso03Lep2 - rhoIso*AEff03Lep2) )/ Lep2.pt();
        double relPfIso04rhoLep2 = ( chIso04Lep2 + max(0.0, nhIso04Lep2 + phIso04Lep2 - rhoIso*AEff04Lep2) )/ Lep2.pt();

	double dimass = (Lep1.p4() + Lep2.p4()).M(); 
        double dRLep1 = 999;
        double dRLep2 = 999;

        for (unsigned jid = 0; jid < cleanedJets->size(); jid++){
          cmg::PFJet jet = cleanedJets->at(jid);
          double tmpLep1= sqrt( (Lep1.eta()-jet.eta())*(Lep1.eta()-jet.eta()) + (Lep1.phi()-jet.phi())*(Lep1.phi()-jet.phi()) );
          double tmpLep2= sqrt( (Lep2.eta()-jet.eta())*(Lep2.eta()-jet.eta()) + (Lep2.phi()-jet.phi())*(Lep2.phi()-jet.phi()) );
          if( tmpLep1 < dRLep1 ) dRLep1 = tmpLep1;
          if( tmpLep2 < dRLep2 ) dRLep2 = tmpLep2;
          break;//consider only leading jet
        }

        //bool QCD1 = relPfIso03Lep2 > 0.2 && MET < 30 && nJets >= 1 && abs( dimass-91 ) > 15 ;
        //bool QCD2 = relPfIso03Lep1 > 0.2 && MET < 30 && nJets >= 1 && abs( dimass-91 ) > 15 ;
        bool QCD1 = relPfIso03Lep2 > 0.3 && Lep1.charge()*Lep2.charge() > 0 ;//&& MET < 30 && nJets >= 1 && mtW < 20;
        bool QCD2 = relPfIso03Lep1 > 0.3 && Lep1.charge()*Lep2.charge() > 0 ;//&& MET < 30 && nJets >= 1 && mtW < 20;
        //bool QCD1 = relPfIso03Lep2 > 0.3 && Lep1.charge()*Lep2.charge() > 0 && MET < 30 && nJets >= 1 ;//&& fabs( dimass-91.2 ) > 15.;// mtW < 20;
        //bool QCD2 = relPfIso03Lep1 > 0.3 && Lep1.charge()*Lep2.charge() > 0 && MET < 30 && nJets >= 1 ;//&& fabs( dimass-91.2 ) > 15.;// mtW < 20;

        bool passID = mvaTrigV0Lep1 > 0.0 && mvaTrigV0Lep2 > 0.0;
        bool passIso = relPfIso03Lep1 < 0.15 && relPfIso03Lep2 < 0.15 ;
        bool passDimass = fabs( dimass-91.2 ) < 15.;

        int isEB;
        if( fabs(Lep1.sourcePtr()->get()->superCluster()->eta()) < 1.479 && fabs(Lep2.sourcePtr()->get()->superCluster()->eta()) < 1.479){
          isEB = 1;
        }else{
          isEB = 0;
        }
//////////////////////
       for(int d = 0 ; d < 2 ; d++){

            bool passGoodIDBarrel = Lep1.sourcePtr()->get()->electronID("mvaTrigV0") > 0.0; // 
            bool passGoodIDEndCaps = Lep1.sourcePtr()->get()->electronID("mvaTrigV0") > 0.0; // 
            bool passPFID = Lep1.sourcePtr()->get()->isPF();
            bool PASSID = false;
            bool isEB1 = fabs(Lep1.sourcePtr()->get()->superCluster()->eta()) < 1.4790;
            
            // d=0: goodid , d=1: pfid 
            if(d==0 && isEB1==1 ) PASSID = passGoodIDBarrel;
            if(d==0 && isEB1==0 ) PASSID = passGoodIDEndCaps; 

            if(d==1 && isEB1==1 ) PASSID = passGoodIDBarrel && passPFID;
            if(d==1 && isEB1==0 ) PASSID = passGoodIDEndCaps && passPFID; 


            if(PASSID)
            {
               h_pt[d][isEB1]->Fill(Lep1.pt());
               h_eta[d][isEB1]->Fill(Lep1.eta());
               h_pv[d][isEB1]->Fill(nvertex);
               h_njet[d][isEB1]->Fill(nJets);
            }

        }
////////////////////////
        for(int k = 0 ; k < 3 ; k++){

          bool pass = true;
          if( k == 1 ) pass = passID;
          if( k == 2 ) pass = passID && passIso;
          if( !pass ) break;

          for(int d = 0 ; d < 2 ; d++){

            bool fillLep1 = false;  
            bool fillLep2 = false;  

            //Is this event QCD when d=1?
            if( d == 0 ){  //for Signal

               if(useZMassWindow_ && !passDimass ) continue;

               if( k == 0){
                fillLep1 = relPfIso03Lep1 < 0.15;
                fillLep2 = relPfIso03Lep2 < 0.15;
              }else{
                fillLep1 = true;
                fillLep2 = true;
              }
            }
            if( d == 1){ //for QCD 
              fillLep1 = QCD1;
              fillLep2 = QCD2;
            }


            if(fillLep1){
	      h_mvaTrigV0[d][k][isEB]->Fill( mvaTrigV0Lep1 );
	      h_pfRelIso03[d][k][isEB]->Fill( relPfIso03Lep1 );
	      h_pfRelIso04[d][k][isEB]->Fill( relPfIso04Lep1 );
              h_pfRelIso03db[d][k][isEB]->Fill( relPfIso03dbLep1 );
              h_pfRelIso04db[d][k][isEB]->Fill( relPfIso04dbLep1 );
              h_pfRelIso03rho[d][k][isEB]->Fill( relPfIso03rhoLep1 );
              h_pfRelIso04rho[d][k][isEB]->Fill( relPfIso04rhoLep1 );
              if( nJets >= 1 ) h_dR[d][k][isEB]->Fill(dRLep1);

              h2_mvaTrigV0[d][k][isEB]->Fill( nvertex, mvaTrigV0Lep1 );
              h2_pfRelIso03[d][k][isEB]->Fill( nvertex, relPfIso03Lep1 );
              h2_pfRelIso04[d][k][isEB]->Fill( nvertex, relPfIso04Lep1 );
              h2_pfRelIso03db[d][k][isEB]->Fill(nvertex, relPfIso03dbLep1 );
              h2_pfRelIso04db[d][k][isEB]->Fill( nvertex, relPfIso04dbLep1 );
              h2_pfRelIso03rho[d][k][isEB]->Fill( nvertex,  relPfIso03rhoLep1 );
              h2_pfRelIso04rho[d][k][isEB]->Fill( nvertex, relPfIso04rhoLep1 );

            }

            if(fillLep2){
	      h_mvaTrigV0[d][k][isEB]->Fill( mvaTrigV0Lep2 );
	      h_pfRelIso03[d][k][isEB]->Fill( relPfIso03Lep2 );
	      h_pfRelIso04[d][k][isEB]->Fill( relPfIso04Lep2 );
              h_pfRelIso03db[d][k][isEB]->Fill( relPfIso03dbLep2 );
              h_pfRelIso04db[d][k][isEB]->Fill( relPfIso04dbLep2 );
              h_pfRelIso03rho[d][k][isEB]->Fill( relPfIso03rhoLep2 );
              h_pfRelIso04rho[d][k][isEB]->Fill( relPfIso04rhoLep2 );
              if( nJets >= 1) h_dR[d][k][isEB]->Fill(dRLep2);     

              h2_mvaTrigV0[d][k][isEB]->Fill( nvertex, mvaTrigV0Lep2 );
              h2_pfRelIso03[d][k][isEB]->Fill( nvertex, relPfIso03Lep2 );
              h2_pfRelIso04[d][k][isEB]->Fill( nvertex, relPfIso04Lep2 );
              h2_pfRelIso03db[d][k][isEB]->Fill(nvertex, relPfIso03dbLep2 );
              h2_pfRelIso04db[d][k][isEB]->Fill( nvertex, relPfIso04dbLep2 );
              h2_pfRelIso03rho[d][k][isEB]->Fill( nvertex,  relPfIso03rhoLep2 );
              h2_pfRelIso04rho[d][k][isEB]->Fill( nvertex, relPfIso04rhoLep2 );

            }

            if( fillLep1 || fillLep2 ) {
              h_mtW[d][k][isEB]->Fill(mtW);
	      h_dimass[d][k][isEB]->Fill(dimass);
              h_nJet[d][k][isEB]->Fill(nJets);
              h_met[d][k][isEB]->Fill(MET);
            }

          }

        }//fill histogram 

      }//electron double loop
    }//check if two leptons
  }

  iEvent.put(pos);
 
}

void 
cmgElectronAnalyzer::beginJob(){

}

void
cmgElectronAnalyzer::endJob() {
}

bool cmgElectronAnalyzer::trainTrigPresel(const cmg::Electron& ele) {
  
  bool myTrigPresel = false;
  if(fabs(ele.sourcePtr()->get()->superCluster()->eta()) < 1.479) {
    if(ele.sourcePtr()->get()->sigmaIetaIeta() < 0.014 &&
       ele.sourcePtr()->get()->hadronicOverEm() < 0.15 &&
       ele.sourcePtr()->get()->dr03TkSumPt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->dr03EcalRecHitSumEt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->dr03HcalTowerSumEt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() == 0)
      myTrigPresel = true;
  }
  else {
    if(ele.sourcePtr()->get()->sigmaIetaIeta() < 0.035 &&
       ele.sourcePtr()->get()->hadronicOverEm() < 0.10 &&
       ele.sourcePtr()->get()->dr03TkSumPt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->dr03EcalRecHitSumEt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->dr03HcalTowerSumEt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() == 0)
      myTrigPresel = true;
  }
  
  
  return myTrigPresel;
}

double cmgElectronAnalyzer::transverseMass( const reco::Candidate::LorentzVector& lepton,
                                     const reco::Candidate::LorentzVector& met) {

  reco::Candidate::LorentzVector leptonT(lepton.Px(),lepton.Py(),0.,lepton.E()*sin(lepton.Theta()));
  reco::Candidate::LorentzVector sumT=leptonT+met;
  return std::sqrt(sumT.M2());
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(cmgElectronAnalyzer);



