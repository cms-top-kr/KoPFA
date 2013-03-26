#include "KoPFA/CMGAnalyzer/interface/cmgMuonAnalyzer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include <time.h>

using namespace std;

cmgMuonAnalyzer::cmgMuonAnalyzer(const edm::ParameterSet& config)
{
  muonLabel_ = config.getParameter<edm::InputTag>("muonLabel");
  beamSpotLabel_ = config.getParameter<edm::InputTag>("beamSpotLabel");
  metLabel_ = config.getParameter<edm::InputTag>("metLabel");
  jetLabel_ = config.getParameter<edm::InputTag>("jetLabel");
  genParticlesLabel_= config.getParameter<edm::InputTag>("genParticlesLabel");
  vertexLabel_ =  config.getUntrackedParameter<edm::InputTag>("vertexLabel");
  useZMassWindow_ =  config.getUntrackedParameter<bool>("useZMassWindow");
  applyPFId_ = config.getUntrackedParameter<bool>("applyPFId", false); 
  numberOfLeptons_ = config.getUntrackedParameter<unsigned int>("numberOfLeptons",1); 
  numberOfJets_ = config.getUntrackedParameter<unsigned int>("numberOfJets",1); 
  filters_ = config.getUntrackedParameter<std::vector<std::string> >("filters");
  useEventCounter_ = config.getParameter<bool>("useEventCounter");

  produces<std::vector<cmg::Muon> >("");

  edm::Service<TFileService> fs;

  tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());
  ranNum = fs->make<TH1F>("Random number","Random number",2,0,2);
  ///////Muon loop
  for(int d=0 ; d < 2 ; d++){
    TString mainDirName = "";

    if( d == 0 ) mainDirName = "Signal";
    else mainDirName = "QCD";

    for(int i=0 ; i < 10 ; i++){

      TString selDirName = "";
      if(i==0) selDirName = "Preselection";
      if(i==1) selDirName = "IDVbtf";
      if(i==2) selDirName = "IDLoose";
      if(i==3) selDirName = "IDSoft";
      if(i==4) selDirName = "IDTight";
      if(i==5) selDirName = "IDLooseIso";
      if(i==6) selDirName = "IDTightIso";
      if(i==7) selDirName = "IDMediumIsoPF";
      if(i==8) selDirName = "IDTightIsoPF";
      if(i==9) selDirName = "IDPF";

      for(int k=0 ; k <2 ; k++){
        TString dirName = "";
        if(k==1){
          dirName = "Barrel";
        }else {
          dirName = "Endcap";
        }

        TFileDirectory dir = fs->mkdir(Form("%s/%s/%s",mainDirName.Data(), selDirName.Data(), dirName.Data()));

        h_pfRelIso02[d][i][k] = dir.make<TH1F>( "h_pfRelIso02", "h_pfRelIso02", 1000, 0, 10);
        h_pfRelIso03[d][i][k] = dir.make<TH1F>( "h_pfRelIso03", "h_pfRelIso03", 1000, 0, 10);
        h_pfRelIso04[d][i][k] = dir.make<TH1F>( "h_pfRelIso04", "h_pfRelIso04", 1000, 0, 10);
        h_pfRelIso02db[d][i][k] = dir.make<TH1F>( "h_pfRelIso02db", "h_pfRelIso02db", 1000, 0, 10);
        h_pfRelIso03db[d][i][k] = dir.make<TH1F>( "h_pfRelIso03db", "h_pfRelIso03db", 1000, 0, 10);
        h_pfRelIso03dbmod[d][i][k] = dir.make<TH1F>( "h_pfRelIso03dbmod", "h_pfRelIso03dbmod", 1000, 0, 10);
        h_pfRelIso04db[d][i][k] = dir.make<TH1F>( "h_pfRelIso04db", "h_pfRelIso04db", 1000, 0, 10);
        h_dR[d][i][k] = dir.make<TH1F>( "h_dR", "h_dR", 300, 0, 3);
        h_njet[d][i][k] = dir.make<TH1F>( "h_njet", "h_njet", 10, 0, 10);
        h_pt[d][i][k] = dir.make<TH1F>( "h_pt", "h_pt", 40, 0, 200);
        h_eta[d][i][k] = dir.make<TH1F>( "h_eta", "h_eta", 25, 0, 2.5);
        h_pv[d][i][k] = dir.make<TH1F>( "h_pv", "h_pv", 50, 0, 50);

        h2_pfRelIso03[d][i][k] = dir.make<TH2F>( "h2_pfRelIso03", "h2_pfRelIso03", 50,0,50,1000, 0, 10);
        h2_pfRelIso04[d][i][k] = dir.make<TH2F>( "h2_pfRelIso04", "h2_pfRelIso04", 50,0,50,1000, 0, 10);
        h2_pfRelIso03db[d][i][k] = dir.make<TH2F>( "h2_pfRelIso03db", "h2_pfRelIso03db", 50,0,50,1000, 0, 10);
        h2_pfRelIso04db[d][i][k] = dir.make<TH2F>( "h2_pfRelIso04db", "h2_pfRelIso04db", 50,0,50,1000, 0, 10);

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
    h_nMuon[d]   = dir.make<TH1F>( "h_nMuon", "h_nMuon", 10, 0, 10);
    h_delphi[d]   = dir.make<TH1F>( "h_delphi", "h_delphi", 32, 0, 3.2);

  }

}

cmgMuonAnalyzer::~cmgMuonAnalyzer()
{

}

void cmgMuonAnalyzer::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;

  const bool isRealData = iEvent.isRealData();

  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  edm::Handle<reco::GenParticleCollection> genParticles_;
  iEvent.getByLabel(genParticlesLabel_,genParticles_);

  iEvent.getByLabel(muonLabel_, muons_);
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

  std::auto_ptr<std::vector<cmg::Muon> > triggeredMuons(new std::vector<cmg::Muon>());

  //preselection
  for (unsigned int i=0; i < muons_->size(); ++i){
    cmg::Muon muon = muons_->at(i);

    ////use dxy with respect to beamspot
    //bool passPre = muon.pt() > 20 && fabs(muon.eta()) < 2.5 && fabs(muon.gsfTrack()->dxy(beamSpot_->position())) < 0.04;
    //// use dxy with respect to PV
    if( nvertex < 1 ) continue;
    //reco::Vertex pv = goodOfflinePrimaryVertices->at(0);
    //bool passPre = muon.pt() > 20 && fabs(muon.eta()) < 2.5 && fabs( muon.sourcePtr()->get()->gsfTrack()->dxy(pv.position()) ) < 0.04;
    bool passPre = muon.pt() > 20 && fabs(muon.eta()) < 2.5;
    bool passPF = muon.isPF(); 
    bool passId = muon.sourcePtr()->get()->isPFMuon() && ( muon.sourcePtr()->get()->isGlobalMuon() ||  muon.sourcePtr()->get()->isTrackerMuon() );

    //bool passPF = muon.sourcePtr()->get()->isPF();
    //bool passTrig = passPre && muon.getSelection("cuts_premvaTrig"); //->get());
    ////////////////////////////////////////////////////////////////////////////////////////
    //bool passTrig = passPre && trainTrigPresel(muon, numberOfHits_ ); 
    ////////////////////////////////////////////////////////////////////////////////////////
    bool passTrig = passPre; 

//    if( applyPreTrigSel_ ) {
//      if( !passTrig ) continue; 
//    }
//    if( applyPFId_ ){
      if( !(passPre && passId) ) continue;
//    }

    triggeredMuons->push_back((*muons_)[i]);
  }
 
  std::auto_ptr<std::vector<cmg::PFJet> > cleanedJets(new std::vector<cmg::PFJet>());

  for (unsigned int j=0 ; j < Jets->size(); j++) {
    cmg::PFJet jet = Jets->at(j);

    bool passLooseJetId = jet.getSelection("cuts_looseJetId");

    if( !passLooseJetId ) continue;
    if( !(jet.pt() > 30 && abs(jet.eta()) < 2.5) ) continue;

    bool overlap = false;
    
    for (unsigned int i=0; i < triggeredMuons->size(); ++i){
      cmg::Muon muon = triggeredMuons->at(i);
      double dR =  deltaR(muon.eta(), muon.phi(), jet.eta(), jet.phi());
      if( dR < 0.5 ) {
        overlap = true;
        break;
      }
    }

    if( !overlap ) cleanedJets->push_back( (*Jets)[j] );
  }

  int nJets = cleanedJets->size();
  int nMuons = triggeredMuons->size();

  double mtW = 0.0;
  double delphi = 0.0;
  if( triggeredMuons->size() >=1) {
    const cmg::Muon leading = triggeredMuons->at(0);
    mtW =  transverseMass( leading.p4() , mi->p4() );
    delphi = fabs(deltaPhi(leading.phi(), mi->p4().phi()));
  }

  srand( time(NULL) ); //Randomize seed initialization
  int rNumInt = rand() % 2; // Generate a random number between 0 and 1
  ranNum->Fill(rNumInt);

  double dimass = 0.;
  double charge = 0;
  int tid = -1;
  double tagged_iso = -1.0;

  for( unsigned int i = 0 ; i < triggeredMuons->size() ; i++){
    for( unsigned int j = 0 ; j < triggeredMuons->size() ; j++){
      cmg::Muon muon1 = triggeredMuons->at(i);
      cmg::Muon muon2 = triggeredMuons->at(j);
      const bool match = MatchObjects( muon1.p4(), muon2.p4(), true);
      if(match) continue; 
      dimass = (muon1.p4() + muon2.p4()).M();
      charge = muon1.charge()*muon2.charge();
      if( rNumInt == 0 ) tid = i;
      if( rNumInt == 1 ) tid = j;
      tagged_iso = (triggeredMuons->at(tid).chargedHadronIso(0.3) + max( 0.0, triggeredMuons->at(tid).neutralHadronIso(0.3) + triggeredMuons->at(tid).photonIso(0.3) - 0.5*triggeredMuons->at(tid).puChargedHadronIso(0.3) ) ) / triggeredMuons->at(tid).pt();
      break;
    }
  }
  

  //// QCD EVENT selection ////
  //int nLeps = triggeredMuons->size();
  //bool QCD =  nLeps <= 1  && mtW < 20 && MET < 20 && nJets == 1 && delphi < 1.5;
  bool QCD =  charge > 0 && fabs(dimass-91) > 15 && mtW < 40 && MET < 30 && nJets >= 2 && tagged_iso > 0.25;
  //bool QCD =  fabs(dimass-91) > 15 && mtW < 20 && MET < 30 && nJets >= 1 && delphi < 1.5;

  int d = 0;
  if(QCD ) d=1;

  bool eventsel = triggeredMuons->size() >= numberOfLeptons_ && nJets >=  (int) numberOfJets_ ;

  if( eventsel ){
    h_mtW[d]->Fill(mtW);
    h_dimass[d]->Fill(dimass);
    h_met[d]->Fill(MET);
    h_nJet[d]->Fill(nJets);
    h_nMuon[d]->Fill(nMuons);
    h_delphi[d]->Fill(delphi);
  } 

  for (unsigned int j=0; j < triggeredMuons->size() && eventsel ; ++j){
    cmg::Muon Lep1 = triggeredMuons->at(j);

    bool isMatchedLep1 = true;

    if( d == 1 ) {
      if( j == (unsigned int) tid ) {
        continue;
      }
    }   

    if( !isRealData )isMatchedLep1 = isFromWorZ(Lep1.p4(), genParticles_, 13);
    if( !isMatchedLep1 ) continue;

    double pt1  = Lep1.pt();
//    double sceta1 = Lep1.sourcePtr()->get()->superCluster()->eta();
//    double sceta1 = Lep1.sourcePtr()->get()->generalTracks()->eta();
    double sceta1 = Lep1.eta();

    double chIso02Lep1 = Lep1.chargedHadronIso(0.2);
    double puChIso02Lep1 = Lep1.puChargedHadronIso(0.2);
    double nhIso02Lep1 = Lep1.neutralHadronIso(0.2);
    double phIso02Lep1 = Lep1.photonIso(0.2);

    double chIso03Lep1 = Lep1.chargedHadronIso(0.3);
    double puChIso03Lep1 = Lep1.puChargedHadronIso(0.3);
    double nhIso03Lep1 = Lep1.neutralHadronIso(0.3);
    double phIso03Lep1 = Lep1.photonIso(0.3);
  
    double chIso04Lep1 = Lep1.chargedHadronIso(0.4);
    double puChIso04Lep1 = Lep1.puChargedHadronIso(0.4);
    double nhIso04Lep1 = Lep1.neutralHadronIso(0.4);
    double phIso04Lep1 = Lep1.photonIso(0.4);
    double sf = 0.5;
    if( fabs(sceta1) > 2.1 ) sf = 1.0; 
    double relPfIso02Lep1 = ( chIso02Lep1 + nhIso02Lep1 + phIso02Lep1 )/ Lep1.pt(); 
    double relPfIso03Lep1 = ( chIso03Lep1 + nhIso03Lep1 + phIso03Lep1 )/ Lep1.pt(); 
    double relPfIso04Lep1 = ( chIso04Lep1 + nhIso04Lep1 + phIso04Lep1 )/ Lep1.pt();
    double relPfIso02dbLep1 = ( chIso02Lep1 + max(0.0, nhIso02Lep1 + phIso02Lep1 - 0.5*puChIso02Lep1) )/ Lep1.pt();
    double relPfIso03dbLep1 = ( chIso03Lep1 + max(0.0, nhIso03Lep1 + phIso03Lep1 - 0.5*puChIso03Lep1) )/ Lep1.pt();
    double relPfIso03dbmodLep1 = ( max(0.0, chIso03Lep1 + nhIso03Lep1 + phIso03Lep1 - sf*puChIso03Lep1) )/ Lep1.pt();
    double relPfIso04dbLep1 = ( chIso04Lep1 + max(0.0, nhIso04Lep1 + phIso04Lep1 - 0.5*puChIso04Lep1) )/ Lep1.pt();
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

    bool passVbtf     = Lep1.getSelection("cuts_vbtfmuon");
    bool passLoose     = Lep1.getSelection("cuts_loosemuon");
    bool passSoft    = Lep1.getSelection("cuts_softmuonNoVtx");
    bool passTight     = Lep1.getSelection("cuts_tightmuonNoVtx");
    //bool passPF        = Lep1.sourcePtr()->get()->isPF();
    bool passPF        = Lep1.isPF();

    bool passIso = relPfIso03dbLep1 < 0.15 ;

    bool isEB1 = fabs(sceta1) < 1.4790;

    for( int sel = 0 ; sel < 10 ; sel++){

      bool fill = true;
      if( sel == 1 ) fill = passVbtf;
      if( sel == 2 ) fill = passLoose;
      if( sel == 3 ) fill = passSoft;
      if( sel == 4 ) fill = passTight;
      if( sel == 5 ) fill = passLoose && passIso;
      if( sel == 6 ) fill = passTight && passIso;
      if( sel == 7 ) fill = passLoose && passIso && passPF;
      if( sel == 8 ) fill = passTight && passIso && passPF;
      if( sel == 9 ) fill = passPF;

      if( fill ){
        h_pfRelIso02[d][sel][isEB1]->Fill( relPfIso02Lep1 );
        h_pfRelIso03[d][sel][isEB1]->Fill( relPfIso03Lep1 );
        h_pfRelIso04[d][sel][isEB1]->Fill( relPfIso04Lep1 );
        h_pfRelIso02db[d][sel][isEB1]->Fill( relPfIso02dbLep1 );
        h_pfRelIso03db[d][sel][isEB1]->Fill( relPfIso03dbLep1 );
        h_pfRelIso03dbmod[d][sel][isEB1]->Fill( relPfIso03dbmodLep1 );
        h_pfRelIso04db[d][sel][isEB1]->Fill( relPfIso04dbLep1 );
        if( nJets >= 1 ) h_dR[d][sel][isEB1]->Fill(dRLep1);
        h_njet[d][sel][isEB1]->Fill(nJets);
        h_pt[d][sel][isEB1]->Fill(pt1);
        h_eta[d][sel][isEB1]->Fill(sceta1);
        h_pv[d][sel][isEB1]->Fill(nvertex);

        h2_pfRelIso03[d][sel][isEB1]->Fill( nvertex, relPfIso03Lep1 );
        h2_pfRelIso04[d][sel][isEB1]->Fill( nvertex, relPfIso04Lep1 );
        h2_pfRelIso03db[d][sel][isEB1]->Fill(nvertex, relPfIso03dbLep1 );
        h2_pfRelIso04db[d][sel][isEB1]->Fill( nvertex, relPfIso04dbLep1 );
      }
    }
    //break;
  }//muon loop

  iEvent.put(triggeredMuons);
 
}

void 
cmgMuonAnalyzer::beginJob(){

}

void
cmgMuonAnalyzer::endJob() {
}

/*
bool cmgMuonAnalyzer::trainTrigPresel(const cmg::Muon& ele, unsigned int numberOfHits) {
  
  bool myTrigPresel = false;
  if(fabs(ele.sourcePtr()->get()->superCluster()->eta()) < 1.479) {
    if(ele.sourcePtr()->get()->sigmaIetaIeta() < 0.014 &&
       ele.sourcePtr()->get()->hadronicOverEm() < 0.15 &&
       ele.sourcePtr()->get()->dr03TkSumPt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->dr03EcalRecHitSumEt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->dr03HcalTowerSumEt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() <= (int) numberOfHits
      )
      myTrigPresel = true;
  }
  else {
    if(ele.sourcePtr()->get()->sigmaIetaIeta() < 0.035 &&
       ele.sourcePtr()->get()->hadronicOverEm() < 0.10 &&
       ele.sourcePtr()->get()->dr03TkSumPt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->dr03EcalRecHitSumEt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->dr03HcalTowerSumEt()/ele.sourcePtr()->get()->pt() < 0.2 &&
       ele.sourcePtr()->get()->gsfTrack()->trackerExpectedHitsInner().numberOfLostHits() <= (int) numberOfHits
      )
      myTrigPresel = true;
  }
  
  
  return myTrigPresel;
}
*/
double cmgMuonAnalyzer::transverseMass( const reco::Candidate::LorentzVector& lepton,
                                     const reco::Candidate::LorentzVector& met) {

  reco::Candidate::LorentzVector leptonT(lepton.Px(),lepton.Py(),0.,lepton.E()*sin(lepton.Theta()));
  reco::Candidate::LorentzVector sumT=leptonT+met;
  return std::sqrt(sumT.M2());
}

////////////////
/*bool cmgMuonAnalyzer::PassWP(EgammaCutBasedEleId::WorkingPoint workingPoint, const cmg::Muon &ele,
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
*/
bool cmgMuonAnalyzer::isFromWorZ( const reco::Candidate::LorentzVector& lepton, const edm::Handle<reco::GenParticleCollection> & genParticles_, int id ){

  bool out = false;

  for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
    int genId = mcIter->pdgId();

    if( abs(genId) != (int) id ) continue;

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

bool cmgMuonAnalyzer::MatchObjects( const reco::Candidate::LorentzVector& pasObj,
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

void cmgMuonAnalyzer::endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & setup){
  if(useEventCounter_){
    for(unsigned int i=0;i<filters_.size();++i) {
      std::string name = filters_[i];
      edm::Handle<edm::MergeableCounter> numEventsCounter;
      lumi.getByLabel(name, numEventsCounter);
      if( numEventsCounter.isValid()){
        tmp->AddBinContent(i+1, numEventsCounter->value);
        tmp->GetXaxis()->SetBinLabel(i+1,filters_[i].c_str());
      }
    }
  }
//  return true;
}



////////////////
#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(cmgMuonAnalyzer);



