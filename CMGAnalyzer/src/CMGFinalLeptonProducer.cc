#include "KoPFA/CMGAnalyzer/interface/CMGFinalLeptonProducer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

CMGFinalLeptonProducer::CMGFinalLeptonProducer(const edm::ParameterSet& cfg)
{
  MuMuLep1Label_ = cfg.getUntrackedParameter<edm::InputTag>("MuMuLep1Label");
  MuMuLep2Label_ = cfg.getUntrackedParameter<edm::InputTag>("MuMuLep2Label");
  MuElLep1Label_ = cfg.getUntrackedParameter<edm::InputTag>("MuElLep1Label");
  MuElLep2Label_ = cfg.getUntrackedParameter<edm::InputTag>("MuElLep2Label");
  ElElLep1Label_ = cfg.getUntrackedParameter<edm::InputTag>("ElElLep1Label");
  ElElLep2Label_ = cfg.getUntrackedParameter<edm::InputTag>("ElElLep2Label");

  produces<std::vector<cmg::Muon> >("Muons");
  produces<std::vector<cmg::Electron> >("Electrons");

}

CMGFinalLeptonProducer::~CMGFinalLeptonProducer()
{

}

void CMGFinalLeptonProducer::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;

  std::auto_ptr<std::vector<cmg::Muon> > muons(new std::vector<cmg::Muon>());
  std::auto_ptr<std::vector<cmg::Electron> > electrons(new std::vector<cmg::Electron>());

  iEvent.getByLabel(MuMuLep1Label_, mmlep1_);
  iEvent.getByLabel(MuMuLep2Label_, mmlep2_);
  iEvent.getByLabel(MuElLep1Label_, melep1_);
  iEvent.getByLabel(MuElLep2Label_, melep2_);
  iEvent.getByLabel(ElElLep1Label_, eelep1_);
  iEvent.getByLabel(ElElLep2Label_, eelep2_);

  if( mmlep1_.isValid() && mmlep2_.isValid()  ) {
    if( mmlep1_->size() > 0 && mmlep2_->size() > 0 ){
     muons->push_back((*mmlep1_)[0]);
     muons->push_back((*mmlep2_)[0]);
    }
  }

  if( melep1_.isValid() && melep2_.isValid()  ) {
    if( melep1_->size() > 0 && melep2_->size() > 0 ){
     muons->push_back((*melep1_)[0]);
     electrons->push_back((*melep2_)[0]);
    }
  }

  if( eelep1_.isValid() && eelep2_.isValid()  ) {
    if( eelep1_->size() > 0 && eelep2_->size() > 0 ){
     electrons->push_back((*eelep1_)[0]);
     electrons->push_back((*eelep2_)[0]);
    }
  }

  iEvent.put(muons,"Muons");
  iEvent.put(electrons,"Electrons");
 
}

void 
CMGFinalLeptonProducer::beginJob(){
}


void
CMGFinalLeptonProducer::endJob() {
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(CMGFinalLeptonProducer);



