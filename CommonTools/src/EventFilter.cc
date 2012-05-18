// -*- C++ -*-
//
// Package:    EventFilter
// Class:      EventFilter
// 
/**\class EventFilter EventFilter.cc UserCode/EventFilter/src/EventFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: EventFilter.cc,v 1.6 2011/03/07 16:35:00 taeyeon Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "DataFormats/Provenance/interface/ProcessHistory.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include <TTree.h>

//
// class declaration
//
using namespace edm;
using namespace std;

class EventFilter : public edm::EDFilter {
   public:
      explicit EventFilter(const edm::ParameterSet&);
      ~EventFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      // ----------member data ---------------------------

      edm::InputTag triggerResultsLabel_;
      std::vector<std::string> filters_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
EventFilter::EventFilter(const edm::ParameterSet& ps)
{
  triggerResultsLabel_ = ps.getUntrackedParameter<edm::InputTag>("triggerResults", edm::InputTag("TriggerResults", "", "PAT"));
  filters_ = ps.getParameter<std::vector<std::string> >("filters");
   //now do what ever initialization is needed

}


EventFilter::~EventFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
EventFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  bool accepted;
 
  accepted = true;

  const bool isRealData = iEvent.isRealData();

  edm::Handle<edm::TriggerResults> triggerResults;
  iEvent.getByLabel( triggerResultsLabel_, triggerResults);
  const edm::TriggerNames & triggerNames = iEvent.triggerNames(*triggerResults);
  edm::TriggerNames::Strings const& names = triggerNames.triggerNames();

  std::map<std::string, bool> triggerMap;
  for(edm::TriggerNames::Strings::const_iterator it = names.begin(); it != names.end() ; ++it){
    const unsigned int i = triggerNames.triggerIndex(*it);
    if( i >= triggerNames.size()) continue;
    triggerMap[*it] = triggerResults->wasrun(i) && triggerResults->accept(i);
  }

  for(int i=0; i < (int) filters_.size() ; i++){
    if( isRealData ){
      if( filters_[i] == "totalKinematicsFilterPath") continue;
      if( triggerMap[filters_[i]] == false ) accepted = false; 
    }else {
      if( filters_[i] != "totalKinematicsFilterPath") continue;
      if( triggerMap[filters_[i]] == false ) accepted = false;
    } 
  }

  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
EventFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EventFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(EventFilter);



