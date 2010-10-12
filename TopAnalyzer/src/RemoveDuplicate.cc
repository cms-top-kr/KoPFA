// -*- C++ -*-
//
// Package:    RemoveDuplicate
// Class:      RemoveDuplicate
// 
/**\class RemoveDuplicate RemoveDuplicate.cc UserCode/RemoveDuplicate/src/RemoveDuplicate.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: RemoveDuplicate.cc,v 1.1 2010/09/09 15:15:54 tjkim Exp $
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "KoPFA/DataFormats/interface/Event.h"
//
// class declaration
//
using namespace edm;
using namespace std;

class RemoveDuplicate : public edm::EDFilter {
   public:
      explicit RemoveDuplicate(const edm::ParameterSet&);
      ~RemoveDuplicate();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      // ----------member data ---------------------------
      bool applyFilter_;

      unsigned int EVENT;
      unsigned int RUN;
      unsigned int LUMI;

      std::vector<Ko::Event>* events;
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
RemoveDuplicate::RemoveDuplicate(const edm::ParameterSet& ps)
{
  applyFilter_=ps.getUntrackedParameter<bool>("applyFilter",true);
   //now do what ever initialization is needed
}


RemoveDuplicate::~RemoveDuplicate()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
RemoveDuplicate::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if (!applyFilter_)
    return true;

  bool accepted = false;
  using namespace edm;
  using namespace std;
  using namespace reco;

  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  bool duplicate = false;
  for(size_t i = 0; i < events->size() ; i++){
    duplicate = events->at(i).run() == RUN && events->at(i).lumi() == LUMI && events->at(i).event() == EVENT;
    if(duplicate) break;
  }

  if(!duplicate) {
    accepted = true;
    Ko::Event event(RUN, LUMI, EVENT); 
    events->push_back(event);
  }

  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
RemoveDuplicate::beginJob(){
  events = new std::vector<Ko::Event>();
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RemoveDuplicate::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RemoveDuplicate);



