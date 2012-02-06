#ifndef KoPFA_CommonTools_KoMETRefSelector_h
#define KoPFA_CommonTools_KoMETRefSelector_h

// store the position of the W combinaison the closest to the W mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/METReco/interface/METFwd.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/RefToBaseVector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/Ptr.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

class KoMETRefSelector : public edm::EDProducer
{
 public:

  explicit KoMETRefSelector(const edm::ParameterSet&);
  ~KoMETRefSelector();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  edm::InputTag metLabel_;
 
  edm::Handle<edm::View<pat::MET> > met_;

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

