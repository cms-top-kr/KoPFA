#ifndef KoPFA_CommonTools_MuonSelector_h
#define KoPFA_CommonTools_MuonSelector_h

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

class MuonSelector : public edm::EDProducer
{
 public:

  explicit MuonSelector(const edm::ParameterSet&);
  ~MuonSelector();

  void produce(edm::Event&, const edm::EventSetup&);

 private:
  
  edm::InputTag muonLabel_;
  MuonIDSelector   muonSelector_;
  edm::InputTag beamSpotLabel_;
 
  typedef pat::MuonCollection::const_iterator MI;
  edm::Handle<pat::MuonCollection> muons_;
  edm::Handle<reco::BeamSpot> beamSpot_;

};


#endif

