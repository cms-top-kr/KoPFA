#ifndef PFAnalyses_CommonTools_LeadLeptonSelector_h
#define PFAnalyses_CommonTools_LeadLeptonSelector_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

using namespace std;

template<typename T>
class LeadLeptonSelector : public edm::EDProducer
{
 public:

  explicit LeadLeptonSelector(const edm::ParameterSet& cfg){
    src_ = cfg.getParameter<edm::InputTag>("src");
    produces<std::vector<T> >("");
  }
  ~LeadLeptonSelector(){}

  void produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
    iEvent.getByLabel(src_, leptons_);

    std::auto_ptr<std::vector<T> > pos(new std::vector<T>());

    if(leptons_->size()){
      typedef map< double, T, greater<double> > PtMap;
      PtMap sortedMuons;
      // muons passing identification criteria are sorted by decreasing pT
      for (unsigned int i=0; i < leptons_->size();++i){
        T muon = leptons_->at(i);
	sortedMuons.insert( make_pair(muon.pt(), muon) );
      }

      T leading = sortedMuons.begin()->second;
      pos->push_back(leading);
    }
    iEvent.put(pos);

  }
 private:
  
  edm::InputTag src_;
  edm::Handle<vector<T> > leptons_;

};

#endif

