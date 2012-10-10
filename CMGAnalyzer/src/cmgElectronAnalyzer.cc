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
  genParticlesLabel_= cfg.getParameter<edm::InputTag>("genParticlesLabel");
  vertexLabel_ =  cfg.getUntrackedParameter<edm::InputTag>("vertexLabel");
  rhoIsoLabel_ =  cfg.getUntrackedParameter<edm::InputTag>("rhoIsoLabel");
  useZMassWindow_ =  cfg.getUntrackedParameter<bool>("useZMassWindow");

  produces<std::vector<cmg::Electron> >("");

  edm::Service<TFileService> fs;

  ///////Electron loop
  for(int d=0 ; d < 2 ; d++){
    TString mainDirName = "";

    if( d == 0 ) mainDirName = "Signal";
    else mainDirName = "QCD";

    for(int i=0 ; i < 11 ; i++){

      TString selDirName = "";
      if(i==0) selDirName = "Preselection";
      if(i==1) selDirName = "IDMVA";
      if(i==2) selDirName = "IDVeto";
      if(i==3) selDirName = "IDLoose";
      if(i==4) selDirName = "IDMedium";
      if(i==5) selDirName = "IDTight";
      if(i==6) selDirName = "IDMediumIso";
      if(i==7) selDirName = "IDTightIso";
      if(i==8) selDirName = "IDMediumIsoPF";
      if(i==9) selDirName = "IDTightIsoPF";
      if(i==10) selDirName = "IDMVAPF";

      for(int k=0 ; k <2 ; k++){
        TString dirName = "";
        if(k==1){
          dirName = "Barrel";
        }else {
          dirName = "Endcap";
        }

        TFileDirectory dir = fs->mkdir(Form("%s/%s/%s",mainDirName.Data(), selDirName.Data(), dirName.Data()));

        h_mvaTrigV0[d][i][k] = dir.make<TH1F>( "h_mvaTrigV0", "h_mvaTrigV0", 200, -1, 1);
        h_pfRelIso03[d][i][k] = dir.make<TH1F>( "h_pfRelIso03", "h_pfRelIso03", 200, 0, 2);
        h_pfRelIso04[d][i][k] = dir.make<TH1F>( "h_pfRelIso04", "h_pfRelIso04", 200, 0, 2);
        h_pfRelIso03db[d][i][k] = dir.make<TH1F>( "h_pfRelIso03db", "h_pfRelIso03db", 200, 0, 2);
        h_pfRelIso04db[d][i][k] = dir.make<TH1F>( "h_pfRelIso04db", "h_pfRelIso04db", 200, 0, 2);
        h_pfRelIso03rho[d][i][k] = dir.make<TH1F>( "h_pfRelIso03rho", "h_pfRelIso03rho", 200, 0, 2);
        h_pfRelIso04rho[d][i][k] = dir.make<TH1F>( "h_pfRelIso04rho", "h_pfRelIso04rho", 200, 0, 2);
        h_dR[d][i][k] = dir.make<TH1F>( "h_dR", "h_dR", 300, 0, 3);
        h_njet[d][i][k] = dir.make<TH1F>( "h_njet", "h_njet", 10, 0, 10);
        h_pt[d][i][k] = dir.make<TH1F>( "h_pt", "h_pt", 40, 0, 200);
        h_eta[d][i][k] = dir.make<TH1F>( "h_eta", "h_eta", 30, 0, 3);
        h_pv[d][i][k] = dir.make<TH1F>( "h_pv", "h_pv", 60, 0, 60);

        h2_mvaTrigV0[d][i][k] = dir.make<TH2F>( "h2_mvaTrigV0", "h2_mvaTrigV0", 60,0,60,200, -1, 1);
        h2_pfRelIso03[d][i][k] = dir.make<TH2F>( "h2_pfRelIso03", "h2_pfRelIso03", 60,0,60,200, 0, 2);
        h2_pfRelIso04[d][i][k] = dir.make<TH2F>( "h2_pfRelIso04", "h2_pfRelIso04", 60,0,60,200, 0, 2);
        h2_pfRelIso03db[d][i][k] = dir.make<TH2F>( "h2_pfRelIso03db", "h2_pfRelIso03db", 60,0,60,200, 0, 2);
        h2_pfRelIso04db[d][i][k] = dir.make<TH2F>( "h2_pfRelIso04db", "h2_pfRelIso04db", 60,0,60,200, 0, 2);
        h2_pfRelIso03rho[d][i][k] = dir.make<TH2F>( "h2_pfRelIso03rho", "h2_pfRelIso03rho", 60,0,60,200, 0, 2);
        h2_pfRelIso04rho[d][i][k] = dir.make<TH2F>( "h2_pfRelIso04rho", "h2_pfRelIso04rho", 60,0,60,200, 0, 2);

      }
    }
  }
  //////////////// Event loop //////////////////////
  for(int d = 0 ; d < 2 ; d++){
    TString mainDirName = "";

    if( d == 0 ) mainDirName = "Signal";
    else mainDirName = "QCD";

    TFileDirectory dir = fs->mkdir(Form("%s",mainDirName.Data()));

    h_mtW[d]    = dir.make<TH1F>( "h_mtW", "h_mtW", 200, 0, 200);
    h_dimass[d] = dir.make<TH1F>( "h_dimass", "h_dimass", 200, 0, 200);
    h_met[d]    = dir.make<TH1F>( "h_met", "h_met", 20, 0, 200);
    h_nJet[d]   = dir.make<TH1F>( "h_nJet", "h_nJet", 10, 0, 10);

  }

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

  edm::Handle<double>  rho_;
  iEvent.getByLabel(rhoIsoLabel_, rho_);
  double rhoIso = *(rho_.product());

  edm::Handle<reco::GenParticleCollection> genParticles_;
  iEvent.getByLabel(genParticlesLabel_,genParticles_);

  iEvent.getByLabel(electronLabel_, electrons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 
  iEvent.getByLabel(jetLabel_, Jets);
  iEvent.getByLabel(vertexLabel_,recVtxs_);
  iEvent.getByLabel(metLabel_,MET_);
  std::vector<cmg::BaseMET>::const_iterator mi = MET_->begin();
  const double MET = mi->pt();

  std::auto_ptr<std::vector<reco::Vertex> > goodOfflinePrimaryVertices(new std::vector<reco::Vertex>());
  int nvertex = 0 ;
  for(unsigned int i=0; i < recVtxs_->size();  ++i){
    reco::Vertex v = recVtxs_->at(i);
    if (!(v.isFake()) && (v.ndof()>4) && (fabs(v.z())<=24.0) && (v.position().Rho()<=2.0) ) {
      goodOfflinePrimaryVertices->push_back((*recVtxs_)[i]);
      nvertex++;
    }
  }

  std::auto_ptr<std::vector<cmg::Electron> > triggeredElectrons(new std::vector<cmg::Electron>());
  std::auto_ptr<std::vector<cmg::Electron> > looseElectrons(new std::vector<cmg::Electron>());
  std::auto_ptr<std::vector<cmg::Electron> > mediumElectrons(new std::vector<cmg::Electron>());
  std::auto_ptr<std::vector<cmg::Electron> > tightElectrons(new std::vector<cmg::Electron>());
  std::auto_ptr<std::vector<cmg::Electron> > mvaElectrons(new std::vector<cmg::Electron>());

  //preselection
  for (unsigned int i=0; i < electrons_->size(); ++i){
    cmg::Electron electron = electrons_->at(i);
    double sceta = electron.sourcePtr()->get()->superCluster()->eta();

    //bool passPre = electron.pt() > 20 && fabs(electron.eta()) < 2.5 && fabs(electron.gsfTrack()->dxy(beamSpot_->position())) < 0.04;
    //if( goodOfflinePrimaryVertices->size() < 1 ) continue;
    //reco::Vertex pv = goodOfflinePrimaryVertices->at(0);
    //bool passPre = electron.pt() > 20 && fabs(electron.eta()) < 2.5 && fabs( electron.sourcePtr()->get()->gsfTrack()->dxy(pv.position()) ) < 0.04;
    bool passPre = electron.pt() > 20 && fabs(electron.eta()) < 2.5;

    bool passTrig = passPre && electron.getSelection("cuts_premvaTrig"); //->get());

    if( passTrig ) triggeredElectrons->push_back((*electrons_)[i]);

    double chIso03 = electron.chargedHadronIso(0.3);
    double nhIso03 = electron.neutralHadronIso(0.3);
    double phIso03 = electron.photonIso(0.3);

    //bool passLoose     = PassWP(EgammaCutBasedEleId::LOOSE, electron, chIso03, phIso03, nhIso03, rhoIso);
    //bool passMedium    = PassWP(EgammaCutBasedEleId::MEDIUM,electron, chIso03, phIso03, nhIso03, rhoIso);
    //bool passTight     = PassWP(EgammaCutBasedEleId::TIGHT, electron, chIso03, phIso03, nhIso03, rhoIso);
    bool passLoose     = electron.getSelection("cuts_looseNoVtx");
    bool passMedium     = electron.getSelection("cuts_mediumNoVtx");
    bool passTight     = electron.getSelection("cuts_tightNoVtx");
    bool passMva       = electron.sourcePtr()->get()->electronID("mvaTrigV0") > 0.0 ;

    if( passMva ) mvaElectrons->push_back((*electrons_)[i]);
    if( passLoose ) looseElectrons->push_back((*electrons_)[i]);
    if( passMedium ) mediumElectrons->push_back((*electrons_)[i]);
    if( passTight ) tightElectrons->push_back((*electrons_)[i]);

  }
 
  std::auto_ptr<std::vector<cmg::PFJet> > cleanedJets(new std::vector<cmg::PFJet>());

  for (unsigned int j=0 ; j < Jets->size(); j++) {
    cmg::PFJet jet = Jets->at(j);

    bool passLooseJetId = jet.getSelection("cuts_looseJetId");

    if( !passLooseJetId ) continue;
    if( !(jet.pt() > 30 && abs(jet.eta()) < 2.5) ) continue;

    bool overlap = false;
    
    for (unsigned int i=0; i < mediumElectrons->size(); ++i){
      cmg::Electron electron = mediumElectrons->at(i);
      double dR= sqrt( (electron.eta()-jet.eta())*(electron.eta()-jet.eta()) + (electron.phi()-jet.phi())*(electron.phi()-jet.phi()) );
      if( dR < 0.5 ) {
        overlap = true;
        break;
      }
    }

    if( !overlap ) cleanedJets->push_back( (*Jets)[j] );
  }

  int nJets = cleanedJets->size();
  int nLeps = mediumElectrons->size();

  double mtW = 0.0;
  double delphi = 0.0;
  if( mediumElectrons->size() >=1) {
    const cmg::Electron leading = mediumElectrons->at(0);
    mtW =  transverseMass( leading.p4() , mi->p4() );
    delphi = fabs(deltaPhi(leading.phi(), mi->p4().phi()));
  }

  double dimass = 0.;
  for( unsigned int i = 0 ; i < mediumElectrons->size() ; i++){
    for( unsigned int j = 0 ; j < looseElectrons->size() ; j++){
      cmg::Electron electron1 = mediumElectrons->at(i);
      cmg::Electron electron2 = looseElectrons->at(j);
      const bool match = MatchObjects( electron1.p4(), electron2.p4(), true);
      if(match) continue; 
      dimass = (electron1.p4() + electron2.p4()).M();
      break;
    }
  }
  
  //// QCD EVENT selection ////
  bool QCD =  dimass <= 0  && mtW < 20 && MET < 30 && nJets >=1 && delphi < 1.5;
  int d = 0;
  if(QCD ) d=1;

  h_mtW[d]->Fill(mtW);
  h_dimass[d]->Fill(dimass);
  h_met[d]->Fill(MET);
  h_nJet[d]->Fill(nJets);
 
  for (unsigned int j=0; j < triggeredElectrons->size(); ++j){
    cmg::Electron Lep1 = electrons_->at(j);

    bool isMatchedLep1 = true;
   
    if( !isRealData )isMatchedLep1 = isFromWorZ(Lep1.p4(), genParticles_);

    if( !isMatchedLep1 ) continue;

    double pt1  = Lep1.pt();
    double sceta1 = Lep1.sourcePtr()->get()->superCluster()->eta();

    float AEff03Lep1 = 0.00;
    float AEff04Lep1 = 0.00;

    if(isRealData){
      AEff03Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, sceta1, ElectronEffectiveArea::kEleEAData2011);
      AEff04Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04, sceta1, ElectronEffectiveArea::kEleEAData2012);
    }else{
      AEff03Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, sceta1, ElectronEffectiveArea::kEleEAFall11MC);
      AEff04Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04, sceta1, ElectronEffectiveArea::kEleEAFall11MC);
    }

    double chIso03Lep1 = Lep1.chargedHadronIso(0.3);
    double puChIso03Lep1 = Lep1.puChargedHadronIso(0.3);
    double nhIso03Lep1 = Lep1.neutralHadronIso(0.3);
    double phIso03Lep1 = Lep1.photonIso(0.3);
  
    double chIso04Lep1 = Lep1.chargedHadronIso(0.4);
    double puChIso04Lep1 = Lep1.puChargedHadronIso(0.4);
    double nhIso04Lep1 = Lep1.neutralHadronIso(0.4);
    double phIso04Lep1 = Lep1.photonIso(0.4);

    double mvaTrigV0Lep1 = Lep1.sourcePtr()->get()->electronID("mvaTrigV0");
    double relPfIso03Lep1 = ( chIso03Lep1 + nhIso03Lep1 + phIso03Lep1 )/ Lep1.pt(); 
    double relPfIso04Lep1 = ( chIso04Lep1 + nhIso04Lep1 + phIso04Lep1 )/ Lep1.pt();
    double relPfIso03dbLep1 = ( chIso03Lep1 + max(0.0, nhIso03Lep1 + phIso03Lep1 - 0.5*puChIso03Lep1) )/ Lep1.pt();
    double relPfIso04dbLep1 = ( chIso04Lep1 + max(0.0, nhIso04Lep1 + phIso04Lep1 - 0.5*puChIso04Lep1) )/ Lep1.pt();
    double relPfIso03rhoLep1 = ( chIso03Lep1 + max(0.0, nhIso03Lep1 + phIso03Lep1 - rhoIso*AEff03Lep1) )/ Lep1.pt();
    double relPfIso04rhoLep1 = ( chIso04Lep1 + max(0.0, nhIso04Lep1 + phIso04Lep1 - rhoIso*AEff04Lep1) )/ Lep1.pt();

    double dRLep1 = 999;

    for (unsigned jid = 0; jid < cleanedJets->size(); jid++){
      cmg::PFJet jet = cleanedJets->at(jid);
      double dRval = deltaR(Lep1.eta(), Lep1.phi(), jet.eta(), jet.phi());
      if( dRval < dRLep1 ) dRLep1 = dRval;
      break;//consider only leading jet
    }

    //////////////////////////
    /////for selections //////
    //////////////////////////

    //bool veto1      = PassWP(EgammaCutBasedEleId::LOOSE, Lep1, chIso03Lep1, phIso03Lep1, nhIso03Lep1, rhoIso);
    //bool loose1     = PassWP(EgammaCutBasedEleId::LOOSE, Lep1, chIso03Lep1, phIso03Lep1, nhIso03Lep1, rhoIso);
    //bool medium1    = PassWP(EgammaCutBasedEleId::MEDIUM,Lep1, chIso03Lep1, phIso03Lep1, nhIso03Lep1, rhoIso);
    //bool tight1     = PassWP(EgammaCutBasedEleId::TIGHT, Lep1, chIso03Lep1, phIso03Lep1, nhIso03Lep1, rhoIso);

    bool passMva      = Lep1.sourcePtr()->get()->electronID("mvaTrigV0") > 0.0;
    bool passVeto     = Lep1.getSelection("cuts_vetoNoVtx");
    bool passLoose     = Lep1.getSelection("cuts_looseNoVtx");
    bool passMedium    = Lep1.getSelection("cuts_mediumNoVtx");
    bool passTight     = Lep1.getSelection("cuts_tightNoVtx");
    bool passPF        = Lep1.sourcePtr()->get()->isPF();

    bool passIso = relPfIso03rhoLep1 < 0.15 ;

    bool isEB1 = fabs(sceta1) < 1.4790;

    for( int sel = 0 ; sel < 11 ; sel++){

      bool fill = true;
      if( sel == 1 ) fill = passMva;
      if( sel == 2 ) fill = passVeto;
      if( sel == 3 ) fill = passLoose;
      if( sel == 4 ) fill = passMedium;
      if( sel == 5 ) fill = passTight;
      if( sel == 6 ) fill = passMedium && passIso;
      if( sel == 7 ) fill = passTight && passIso;
      if( sel == 8 ) fill = passMedium && passIso && passPF;
      if( sel == 9 ) fill = passTight && passIso && passPF;
      if( sel == 10 ) fill = passMva && passPF;

      if( fill ){
        h_mvaTrigV0[d][sel][isEB1]->Fill( mvaTrigV0Lep1 );
        h_pfRelIso03[d][sel][isEB1]->Fill( relPfIso03Lep1 );
        h_pfRelIso04[d][sel][isEB1]->Fill( relPfIso04Lep1 );
        h_pfRelIso03db[d][sel][isEB1]->Fill( relPfIso03dbLep1 );
        h_pfRelIso04db[d][sel][isEB1]->Fill( relPfIso04dbLep1 );
        h_pfRelIso03rho[d][sel][isEB1]->Fill( relPfIso03rhoLep1 );
        h_pfRelIso04rho[d][sel][isEB1]->Fill( relPfIso04rhoLep1 );
        if( nJets >= 1 ) h_dR[d][sel][isEB1]->Fill(dRLep1);
        h_njet[d][sel][isEB1]->Fill(nJets);
        h_pt[d][sel][isEB1]->Fill(pt1);
        h_eta[d][sel][isEB1]->Fill(sceta1);
        h_pv[d][sel][isEB1]->Fill(nvertex);

        h2_mvaTrigV0[d][sel][isEB1]->Fill( nvertex, mvaTrigV0Lep1 );
        h2_pfRelIso03[d][sel][isEB1]->Fill( nvertex, relPfIso03Lep1 );
        h2_pfRelIso04[d][sel][isEB1]->Fill( nvertex, relPfIso04Lep1 );
        h2_pfRelIso03db[d][sel][isEB1]->Fill(nvertex, relPfIso03dbLep1 );
        h2_pfRelIso04db[d][sel][isEB1]->Fill( nvertex, relPfIso04dbLep1 );
        h2_pfRelIso03rho[d][sel][isEB1]->Fill( nvertex,  relPfIso03rhoLep1 );
        h2_pfRelIso04rho[d][sel][isEB1]->Fill( nvertex, relPfIso04rhoLep1 );
      }
    }
  }//electron loop

  iEvent.put(triggeredElectrons);
 
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

////////////////
bool cmgElectronAnalyzer::PassWP(EgammaCutBasedEleId::WorkingPoint workingPoint, const cmg::Electron &ele,
    const double &iso_ch,
    const double &iso_em,
    const double &iso_nh,
    const double &rho)
{
   // kinematic variables
    bool isEB           = ele.sourcePtr()->get()->isEB() ? true : false;
    float pt            = ele.sourcePtr()->get()->pt();
    float eta           = ele.sourcePtr()->get()->superCluster()->eta();

    // id variables
    float dEtaIn        = ele.sourcePtr()->get()->deltaEtaSuperClusterTrackAtVtx();
    float dPhiIn        = ele.sourcePtr()->get()->deltaPhiSuperClusterTrackAtVtx();
    float sigmaIEtaIEta = ele.sourcePtr()->get()->sigmaIetaIeta();
    float hoe           = ele.sourcePtr()->get()->hadronicOverEm();
    float ooemoop       = (1.0/ele.sourcePtr()->get()->ecalEnergy() - ele.sourcePtr()->get()->eSuperClusterOverP()/ele.sourcePtr()->get()->ecalEnergy());

    // impact parameter variables
    float d0vtx         = 0.0;
    float dzvtx         = 0.0;
    if (recVtxs_->size() > 0) {
        reco::VertexRef vtx(recVtxs_, 0);    
        d0vtx = ele.sourcePtr()->get()->gsfTrack()->dxy(vtx->position());
        dzvtx = ele.sourcePtr()->get()->gsfTrack()->dz(vtx->position());
    } else {
        d0vtx = ele.sourcePtr()->get()->gsfTrack()->dxy();
        dzvtx = ele.sourcePtr()->get()->gsfTrack()->dz();
    }

    // conversion rejection variables
    bool vtxFitConversion = ele.sourcePtr()->get()->passConversionVeto();// ConversionTools::hasMatchedConversion(ele, conversions, beamspot.position());
    float mHits = ele.sourcePtr()->get()->gsfTrack()->trackerExpectedHitsInner().numberOfHits(); 

    // get the mask value
    unsigned int mask = EgammaCutBasedEleId::TestWP(workingPoint, isEB, pt, eta, dEtaIn, dPhiIn,
        sigmaIEtaIEta, hoe, ooemoop, d0vtx, dzvtx, iso_ch, iso_em, iso_nh, vtxFitConversion, mHits, rho);

    // return the mask value
    if ((mask & PassAll) == PassAll) return true;
    return false;
}

bool cmgElectronAnalyzer::isFromWorZ( const reco::Candidate::LorentzVector& lepton, const edm::Handle<reco::GenParticleCollection> & genParticles_ ){

  bool out = false;

  for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
    int genId = mcIter->pdgId();

    if( abs(genId) != 11 ) continue;

    bool match = MatchObjects(lepton, mcIter->p4(), false);

    if( match != true) continue;
   
    const reco::Candidate* mother = mcIter->mother();
    while( mother != 0 ){
      if( abs(mother->pdgId()) == 24 || abs(mother->pdgId()) == 23 ) { 
        out = true;
      }
      mother = mother->mother();
    }
  }

  return out;
}

bool cmgElectronAnalyzer::MatchObjects( const reco::Candidate::LorentzVector& pasObj,
      const reco::Candidate::LorentzVector& proObj,
      bool exact ) {
    double proEta = proObj.eta();
    double proPhi = proObj.phi();
    double proPt  = proObj.pt();
    double pasEta = pasObj.eta();
    double pasPhi = pasObj.phi();
    double pasPt  = pasObj.pt();

    double dRval = deltaR(proEta, proPhi, pasEta, pasPhi);
    double dPtRel = 999.0;
    if( proPt > 0.0 ) dPtRel = fabs( pasPt - proPt )/proPt;
    // If we are comparing two objects for which the candidates should
    // be exactly the same, cut hard. Otherwise take cuts from user.
    if( exact ) return ( dRval < 1e-3 && dPtRel < 1e-3 );
    else        return ( dRval < 0.025 && dPtRel < 0.025 );
}



////////////////
#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(cmgElectronAnalyzer);



