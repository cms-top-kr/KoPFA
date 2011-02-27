#include "KoPFA/CommonTools/interface/KoMuonRefSelector.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

KoMuonRefSelector::KoMuonRefSelector(const edm::ParameterSet& cfg)
{
  cut_ = cfg.getParameter< std::vector<string> >("cut");
  isocut_ = cfg.getParameter< std::vector<string> >("isocut");
  muonLabel_ = cfg.getParameter<edm::InputTag>("muonLabel");
  muonIdSelector_.initialize( cfg.getParameter<edm::ParameterSet>("muonIdSelector") );
  muonIsoSelector_.initialize( cfg.getParameter<edm::ParameterSet>("muonIsoSelector") );
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");
  produces<edm::PtrVector<reco::Candidate> >();
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for muon study");

  cutNames.push_back("pre");
  cutNames.push_back("dxy");
  cutNames.push_back("isGlobal");
  cutNames.push_back("isTracker");
  cutNames.push_back("trackerHits");
  cutNames.push_back("chi2");
  //for(size_t i=0 ; i < IdCuts_.size() ; i++){
  //  cutNames.push_back(IdCuts_[i]);
  //}
  //for(size_t i=0 ; i < IsoCuts_.size() ; i++){
  //  cutNames.push_back(IsoCuts_[i]);
  //}

  int nBins = (int) cutNames.size();
  cutflow   = fs->make<TH1F>( "cutflow", "cutflow", nBins,-0.5,nBins-0.5);

  pt = new std::vector<double>();
  eta = new std::vector<double>();
  phi = new std::vector<double>();

  chIso = new std::vector<double>();
  nhIso = new std::vector<double>();
  phIso = new std::vector<double>();

  trackIso = new std::vector<double>();
  ecalIso = new std::vector<double>();
  hcalIso = new std::vector<double>();

}

KoMuonRefSelector::~KoMuonRefSelector()
{

}

void KoMuonRefSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;
  using namespace edm; 

  pt->clear();
  eta->clear();
  phi->clear();
  chIso->clear();
  nhIso->clear();
  phIso->clear();

  trackIso->clear();
  ecalIso->clear();
  hcalIso->clear();

  IsoDeposit::AbsVetos vetos_ch;
  IsoDeposit::AbsVetos vetos_nh;
  IsoDeposit::AbsVetos vetos_ph;

  iEvent.getByLabel(muonLabel_, muons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 
  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  std::auto_ptr<PtrVector<reco::Candidate> > pos(new PtrVector<reco::Candidate>());

  int cut[6] = {0,0,0,0,0,0};
  //vector<int> cut;
  for (unsigned int i=0; i < muons_->size();++i){
    Ptr<pat::Muon> muonRef = muons_->ptrAt(i);
    const pat::Muon & muon = *muonRef;

    pat::strbitset muonIDSel = muonIdSelector_.getBitTemplate();
    pat::strbitset muonIsoSel = muonIsoSelector_.getBitTemplate();
    muonIdSelector_( muon, beamSpot_, muonIDSel );
    muonIsoSelector_( muon, muonIsoSel );

    bool C1 = muonIDSel.test("eta") && muonIDSel.test("pt");
    bool C2 = C1 && muonIDSel.test("dxy");
    bool C3 = C2 && muonIDSel.test("isGlobalMuon");
    bool C4 = C3 && muonIDSel.test("isTrackerMuon");
    bool C5 = C4 && muonIDSel.test("trackerHits");
    bool C6 = C5 && muonIDSel.test("globalNormChi2");
  
    if(C1) cut[0]++;
    if(C2) cut[1]++;
    if(C3) cut[2]++;
    if(C4) cut[3]++;
    if(C5) cut[4]++;
    if(C6) cut[5]++;    

    bool passed = true;

    for(size_t i =0 ; i < cut_.size() ; i++){
      if( !muonIDSel.test(cut_[i]) ){
        passed = false;
        break;
      }
    } 

    for(size_t i =0 ; i < isocut_.size() ; i++){
      if( !muonIsoSel.test(isocut_[i]) ){
        passed = false;
        break;
      }
    }

    if(passed){
      pos->push_back(muonRef);

      pt->push_back(muon.pt());
      eta->push_back(muon.eta());
      phi->push_back(muon.phi());
      //chIso->push_back(muon.chargedHadronIso());
      //phIso->push_back(muon.photonIso());
      //nhIso->push_back(muon.neutralHadronIso());
      chIso->push_back(muon.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
      nhIso->push_back(muon.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
      phIso->push_back(muon.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);

      trackIso->push_back(muon.trackIso());
      ecalIso->push_back(muon.ecalIso());
      hcalIso->push_back(muon.hcalIso());

    }
  }

  for(int i=0; i < (int) cutNames.size() ; i++){
    cutflow->AddBinContent(i+1, cut[i]);
  }

  multiplicity = (int) pos->size();

  iEvent.put(pos);
  
  tree->Fill(); 

}

void 
KoMuonRefSelector::beginJob(){
   tree->Branch("EVENT",&EVENT,"EVENT/i");
   tree->Branch("RUN",&RUN,"RUN/i");
   tree->Branch("LUMI",&LUMI,"LUMI/i");

   tree->Branch("pt","std::vector<double>",&pt);
   tree->Branch("eta","std::vector<double>",&eta);
   tree->Branch("phi","std::vector<double>",&phi);
   tree->Branch("multiplicity",&multiplicity,"multiplicity/i");

   tree->Branch("chIso","std::vector<double>",&chIso);
   tree->Branch("nhIso","std::vector<double>",&nhIso);
   tree->Branch("phIso","std::vector<double>",&phIso);

   tree->Branch("trackIso","std::vector<double>",&trackIso);
   tree->Branch("ecalIso","std::vector<double>",&ecalIso);
   tree->Branch("hcalIso","std::vector<double>",&hcalIso);
}


void
KoMuonRefSelector::endJob() {
  for(int i=0 ; i < 6; i++){
    cutflow->GetXaxis()->SetBinLabel(i+1,cutNames[i].c_str());
  }
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KoMuonRefSelector);



