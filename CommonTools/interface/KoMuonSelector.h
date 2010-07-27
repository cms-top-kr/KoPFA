#ifndef KoPFA_CommonTools_KoMuonSelector_h
#define KoPFA_CommonTools_KoMuonSelector_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "KoPFA/CommonTools/interface/MuonIDSelector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

class KoMuonSelector : public edm::EDProducer
{
 public:

  explicit KoMuonSelector(const edm::ParameterSet&);
  ~KoMuonSelector();

  void produce(edm::Event&, const edm::EventSetup&);

 private:

  // Cut version
  int version_; // 1 for PFMUON, 2 for VBTF, 3 for TOP
  edm::InputTag muonLabel_;
  MuonIDSelector   muonSelector_;
  edm::InputTag beamSpotLabel_;
 
  typedef pat::MuonCollection::const_iterator MI;
  edm::Handle<pat::MuonCollection> muons_;
  edm::Handle<reco::BeamSpot> beamSpot_;

};


#endif

