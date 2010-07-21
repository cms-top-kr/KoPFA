#include "KoPFA/CommonTools/interface/MuonSelector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

MuonSelector::MuonSelector(const edm::ParameterSet& cfg)
{

  muonLabel_ = cfg.getParameter<edm::InputTag>("muonLabel");
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");
  chi2_ = cfg.getUntrackedParameter<double>("chi2",0);
  nHits_ = cfg.getUntrackedParameter<double>("nHits",9999);
  d0_ = cfg.getUntrackedParameter<double>("d0",0);
  produces<std::vector<pat::Muon> >("");
}

MuonSelector::~MuonSelector()
{

}

void MuonSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  iEvent.getByLabel(muonLabel_, muons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 

  std::auto_ptr<std::vector<pat::Muon> > pos(new std::vector<pat::Muon>());

  for (unsigned int i=0; i < muons_->size();++i){
    const pat::Muon muon = muons_->at(i);

    int isGlobal = (int)muon.isGlobalMuon();
    int isTracker = (int)muon.isTrackerMuon();
    int nMatches = (int)muon.numberOfMatches();
    int tmLastStationAngTight = (int)muon::isGoodMuon(muon,muon::TMLastStationAngTight);

    // from global track
    int muonHits = 0.;
    double globalNormChi2 = 9999.;

    // from tracker track
    int trackerHits = 0.;
    int pixelHits = 0;
    int pixelLayersWithHits = 0;
    int trackNormChi2 = 9999.;
    double dxy = 9999;
    double dz = 9999;

    if(muon.isGlobalMuon()){
      //const reco::TrackRef& combinedMuon = muon.combinedMuon();    
      const reco::TrackRef& combinedMuon = muon.globalTrack();        
      globalNormChi2 = combinedMuon->normalizedChi2();
      muonHits = combinedMuon->hitPattern().numberOfValidMuonHits();
    }else{
      //cout<<" number of muon hits = "<<muonHits<<endl;
      // hack to remove cut for tracker (!global) muons
      muonHits = 999;
      globalNormChi2 = 0.;
    }

    if(!muon.track()){
    }else{
      const reco::TrackRef& track = muon.track();        
      trackerHits = track->hitPattern().numberOfValidTrackerHits();
      pixelHits = track->hitPattern().numberOfValidPixelHits();
      pixelLayersWithHits = track->hitPattern().pixelLayersWithMeasurement();
      trackNormChi2 = track->normalizedChi2();
      dxy = fabs(track->dxy(beamSpot_->position()));
      dz = fabs(track->dz(beamSpot_->position()));
    }
    cout << "dxy= " << dxy ;
    bool passed = dxy < d0_;

    if(passed){
      pos->push_back((*muons_)[i]);
    }
  }

  iEvent.put(pos);
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(MuonSelector);



