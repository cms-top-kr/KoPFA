#include "KoPFA/CommonTools/interface/KoMuonSelector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

KoMuonSelector::KoMuonSelector(const edm::ParameterSet& cfg)
{
  version_ = cfg.getUntrackedParameter<int>("version", -1);
  cut_ = cfg.getParameter< std::vector<string> >("cut");
  isocut_ = cfg.getParameter< std::vector<string> >("isocut");
  muonLabel_ = cfg.getParameter<edm::InputTag>("muonLabel");
  muonIdSelector_.initialize( cfg.getParameter<edm::ParameterSet>("muonIdSelector") );
  muonIsoSelector_.initialize( cfg.getParameter<edm::ParameterSet>("muonIsoSelector") );
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");

  produces<std::vector<pat::Muon> >("");
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for muon study");

  cutNames.push_back("pre");
  cutNames.push_back("dxy");
  cutNames.push_back("isGlobal");
  cutNames.push_back("isTracker");
  cutNames.push_back("trackerHits");
  cutNames.push_back("chi2");
  cutNames.push_back("muonHits");
  cutNames.push_back("TOPDIL");

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

KoMuonSelector::~KoMuonSelector()
{

}

void KoMuonSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;

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

  std::auto_ptr<std::vector<pat::Muon> > pos(new std::vector<pat::Muon>());

  int cut[8];
  for(int i =0 ; i < (int)cutNames.size() ; i++){
    cut[i] = 0;
  }

  for (unsigned int i=0; i < muons_->size();++i){
    const pat::Muon muon = muons_->at(i);
    pat::strbitset muonIdSel = muonIdSelector_.getBitTemplate();
    pat::strbitset muonIsoSel = muonIsoSelector_.getBitTemplate();
    muonIdSelector_( muon, beamSpot_, muonIdSel );
    muonIsoSelector_( muon, muonIsoSel );

    bool C1 = muonIdSel.test("eta") && muonIdSel.test("pt");
    bool C2 = C1 && muonIdSel.test("dxy");
    bool C3 = C2 && muonIdSel.test("isGlobalMuon");
    bool C4 = C3 && muonIdSel.test("isTrackerMuon");
    bool C5 = C4 && muonIdSel.test("trackerHits");
    bool C6 = C5 && muonIdSel.test("globalNormChi2");
    bool C7 = C6 && muonIdSel.test("muonHits");
    bool C8 = C2 && muonIdSel.test("TOPDIL");
  
    if(C1) cut[0]++;
    if(C2) cut[1]++;
    if(C3) cut[2]++;
    if(C4) cut[3]++;
    if(C5) cut[4]++;
    if(C6) cut[5]++;    
    if(C7) cut[6]++;
    if(C8) cut[7]++;

    bool passed = false;
   
    if(version_==-1){
      bool passId = true;
      bool passIso = true;
      for(size_t i =0 ; i < cut_.size() ; i++){
        passId = muonIdSel.test(cut_[i]);
        if(!passId) break;
      }
      for(size_t i =0 ; i < isocut_.size() ; i++){
        passIso = muonIsoSel.test(isocut_[i]);
        if(!passIso) break;
      }
      passed = passId && passIso;
    } else if(version_==0) passed = C1;
    else if(version_==1) passed = C2;
    else if(version_==2) passed = muonIdSel.test("VBTF") && C2;
    else if(version_==3) passed = muonIdSel.test("TOPDIL") && C2;
    else if(version_==4) passed = C2 && muonIsoSel.test("pfOptimizedRel");
    if(passed){
      pos->push_back((*muons_)[i]);
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
KoMuonSelector::beginJob(){
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
KoMuonSelector::endJob() {
  for(int i=0 ; i < (int) cutNames.size(); i++){
    cutflow->GetXaxis()->SetBinLabel(i+1,cutNames[i].c_str());
  }
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KoMuonSelector);



