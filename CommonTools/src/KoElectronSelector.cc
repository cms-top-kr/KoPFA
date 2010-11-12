#include "KoPFA/CommonTools/interface/KoElectronSelector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "PhysicsTools/SelectorUtils/interface/SimpleCutBasedElectronIDSelectionFunctor.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

KoElectronSelector::KoElectronSelector(const edm::ParameterSet& cfg)
{
  version_ = cfg.getUntrackedParameter<int>("version", 1);
  usepflow_ = cfg.getUntrackedParameter<bool>("usepflow",true);
  ptcut_ = cfg.getUntrackedParameter<double>("ptcut",20);
  etacut_ = cfg.getUntrackedParameter<double>("etacut",2.4);
  electronLabel_ = cfg.getParameter<edm::InputTag>("electronLabel");
  electronIdSelector_.initialize( cfg.getParameter<edm::ParameterSet>("electronIdSelector") );
  electronIsoSelector_.initialize( cfg.getParameter<edm::ParameterSet>("electronIsoSelector") );
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");
  produces<std::vector<pat::Electron> >("");
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for electron study");

  id2mva = fs->make<TH2F>( "id2mva","id2mva", 200, -1,1, 8,0,8);  
  id2pfmva = fs->make<TH2F>( "id2pfmva","id2pfmva", 200, -1,1, 8,0,8);  
  pfMVA2patMVA_ = fs->make<TH2F>("pfMVA2patMVA", "PF based e_pi MVA vs standard MVA;PF based e_pi MVA;Standard MVA", 100, -1, 1, 100, -1, 1);

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

KoElectronSelector::~KoElectronSelector()
{

}

void KoElectronSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
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

  iEvent.getByLabel(electronLabel_, electrons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 
  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  std::auto_ptr<std::vector<pat::Electron> > pos(new std::vector<pat::Electron>());

  for (unsigned int i=0; i < electrons_->size();++i){
    pat::Electron electron = electrons_->at(i);

    if(usepflow_){
      electron.setP4(electron.pfCandidateRef()->p4());
    }

    pat::strbitset electronIdSel = electronIdSelector_.getBitTemplate();
    pat::strbitset electronIsoSel = electronIsoSelector_.getBitTemplate();
    electronIdSelector_( electron, beamSpot_->position(), electronIdSel );
    electronIsoSelector_( electron, electronIsoSel );

    bool passed = false;

    bool passPre = electron.pt() > ptcut_ && fabs(electron.eta()) < etacut_ && fabs(electron.gsfTrack()->dxy(beamSpot_->position())) < 0.04;
    bool passMVA = electron.mva() > 0.4;
    int result = (int)electron.electronID("simpleEleId90relIso");
    bool passWP90ID = ( result == 5 || result == 7)  ;

    if(version_ == 10){
      passed = passPre && passMVA;
    } else if (version_ == 5){
      passed = passPre && passWP90ID;
    }

    id2mva->Fill( electron.mva(), electron.electronID("simpleEleId90relIso"));
    id2pfmva->Fill( electron.pfCandidateRef()->mva_e_pi(), electron.electronID("simpleEleId90relIso"));
    pfMVA2patMVA_->Fill( electron.mva(), electron.pfCandidateRef()->mva_e_pi());

    if(passed){
      pos->push_back((*electrons_)[i]);

      pt->push_back(electron.pt());
      eta->push_back(electron.eta());
      phi->push_back(electron.phi());

      //chIso->push_back(electron.chargedHadronIso());
      //phIso->push_back(electron.photonIso());
      //nhIso->push_back(electron.neutralHadronIso());
      chIso->push_back(electron.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
      nhIso->push_back(electron.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
      phIso->push_back(electron.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);

      trackIso->push_back(electron.trackIso());
      ecalIso->push_back(electron.ecalIso());
      hcalIso->push_back(electron.hcalIso());

    }
  }

  multiplicity = (int) pos->size();

  iEvent.put(pos);
 
  tree->Fill(); 

}

void 
KoElectronSelector::beginJob(){
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
KoElectronSelector::endJob() {

  id2mva->GetXaxis()->SetTitle("mva");
  id2mva->GetYaxis()->SetTitle("id90");
  id2pfmva->GetXaxis()->SetTitle("mva");
  id2pfmva->GetYaxis()->SetTitle("id90");

  pfMVA2patMVA_->GetXaxis()->SetTitle("mva"); 
  pfMVA2patMVA_->GetYaxis()->SetTitle("pfCandidateRefmva"); 
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KoElectronSelector);



