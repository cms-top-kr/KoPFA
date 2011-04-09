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
  etacut_ = cfg.getUntrackedParameter<double>("etacut",2.5);

  eidName_ = cfg.getUntrackedParameter<string>("eidName");
  eidBitMask_ = cfg.getUntrackedParameter<int>("eidBitMask", -1);

  electronLabel_ = cfg.getParameter<edm::InputTag>("electronLabel");
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");
  bool saveTree = cfg.getUntrackedParameter<bool>("saveTree", false);

  produces<std::vector<pat::Electron> >("");

  tree = 0;
  if ( saveTree )
  {
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
}

KoElectronSelector::~KoElectronSelector()
{

}

void KoElectronSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;

  if ( tree )
  {
    pt->clear();
    eta->clear();
    phi->clear();

    chIso->clear();
    nhIso->clear();
    phIso->clear();

    trackIso->clear();
    ecalIso->clear();
    hcalIso->clear();

    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();
  }

  IsoDeposit::AbsVetos vetos_ch;
  IsoDeposit::AbsVetos vetos_nh;
  IsoDeposit::AbsVetos vetos_ph;

  iEvent.getByLabel(electronLabel_, electrons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 

  std::auto_ptr<std::vector<pat::Electron> > pos(new std::vector<pat::Electron>());

  for (unsigned int i=0; i < electrons_->size();++i){
    pat::Electron electron = electrons_->at(i);

    if(usepflow_){
      electron.setP4(electron.pfCandidateRef()->p4());
    }

    bool passed = false;
    bool passPre = electron.pt() > ptcut_ && fabs(electron.eta()) < etacut_ && fabs(electron.gsfTrack()->dxy(beamSpot_->position())) < 0.04;
    const double eleMva = electron.mva();
    const int eidBit = (int)electron.electronID(eidName_);

    const bool passMVA = eleMva > 0.4;
    const bool passEId = eidBitMask_ < 0 or ((eidBit & eidBitMask_) == eidBitMask_);

    if(version_ == 10){
      passed = passPre && passMVA;
    } else if (version_ == 5){
      passed = passPre && passEId;
    }

    if ( passed ) pos->push_back((*electrons_)[i]);

    if ( tree )
    {
      id2mva->Fill(eleMva, eidBit);
      if(usepflow_){
        id2pfmva->Fill( electron.pfCandidateRef()->mva_e_pi(), eidBit);
        pfMVA2patMVA_->Fill(eleMva, electron.pfCandidateRef()->mva_e_pi());
      }

      if(passed){

        pt->push_back(electron.pt());
        eta->push_back(electron.eta());
        phi->push_back(electron.phi());

        if(usepflow_){
          chIso->push_back(electron.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
          nhIso->push_back(electron.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
          phIso->push_back(electron.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);
        }

        trackIso->push_back(electron.trackIso());
        ecalIso->push_back(electron.ecalIso());
        hcalIso->push_back(electron.hcalIso());
      }

    }
  }

  iEvent.put(pos);

  if ( tree )
  {
    multiplicity = (int) pos->size();
    tree->Fill(); 
  }

}

void 
KoElectronSelector::beginJob(){
  if ( tree ) 
  {
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
}

void
KoElectronSelector::endJob() {
  if ( tree )
  {
    id2mva->GetXaxis()->SetTitle("mva");
    id2mva->GetYaxis()->SetTitle("id90");
    id2pfmva->GetXaxis()->SetTitle("mva");
    id2pfmva->GetYaxis()->SetTitle("id90");

    pfMVA2patMVA_->GetXaxis()->SetTitle("mva"); 
    pfMVA2patMVA_->GetYaxis()->SetTitle("pfCandidateRefmva"); 
  }
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KoElectronSelector);



