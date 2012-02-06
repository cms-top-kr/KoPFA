#ifndef KoPFA_CommonTools_KoMETSelector_h
#define KoPFA_CommonTools_KoMETSelector_h

// store the position of the W combinaison the closest to the W mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"


#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

class KoMETSelector : public edm::EDProducer
{
 public:

  explicit KoMETSelector(const edm::ParameterSet&);
  ~KoMETSelector();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  // Cut version
  edm::InputTag metLabel_;

  typedef pat::METCollection::const_iterator MEI;
  edm::Handle<pat::METCollection> met_;

  TTree *tree;

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

  std::vector<double>* eta;
  std::vector<double>* phi;
  std::vector<double>* pt;
  int multiplicity;

};


#endif

