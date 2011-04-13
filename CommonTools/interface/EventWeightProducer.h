#ifndef KoPFA_CommonTools_EventWeightProducer_h
#define KoPFA_CommonTools_EventWeightProducer_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "KoPFA/CommonTools/interface/MuonIDSelector.h"
#include "PFAnalyses/CommonTools/interface/PatMuonSelector.h"
#include "PFAnalyses/CommonTools/interface/PatLeptonSelector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"


class EventWeightProducer : public edm::EDProducer
{
 public:

  explicit EventWeightProducer(const edm::ParameterSet&);
  ~EventWeightProducer();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:
  vector<double> PUweight_;
  double PUdefault_;

};


#endif

