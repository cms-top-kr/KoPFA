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
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"


class EventWeightProducer : public edm::EDProducer
{
 public:

  explicit EventWeightProducer(const edm::ParameterSet&);
  ~EventWeightProducer();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  edm::LumiReWeighting LumiWeights_;
  edm::LumiReWeighting LumiWeightsUP_;
  edm::LumiReWeighting LumiWeightsDN_;

  std::vector<double> PileUpRD_;
  std::vector<double> PileUpRDup_;
  std::vector<double> PileUpRDdn_;
  std::vector<double> PileUpMC_;

  unsigned int npileup;
  double weightin;
  double weight;
  double weightplus;
  double weightminus;

  //reweight::PoissonMeanShifter PShiftUp_;
  //reweight::PoissonMeanShifter PShiftDown_;

};


#endif

