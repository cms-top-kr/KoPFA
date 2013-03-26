// -*- C++ -*-
//
// Package:    EventInfo
// Class:      EventInfo
// 
/**\class EventInfo EventInfo.cc UserCode/EventInfo/src/EventInfo.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tae Jeong Kim,40 R-A32,+41227678602,
//         Created:  Fri Jun  4 17:19:29 CEST 2010
// $Id: EventInfo.cc,v 1.4 2010/06/11 20:35:51 tjkim Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TTree.h"
#include "TFile.h" 
#include "TH1.h"

//
// class declaration
//

class EventInfo : public edm::EDAnalyzer {
   public:
      explicit EventInfo(const edm::ParameterSet&);
      ~EventInfo();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      TTree* tree;

      // ----------member data ---------------------------

      //add run event data
      unsigned int EVENT;
      unsigned int RUN;
      unsigned int LUMI;
 
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
EventInfo::EventInfo(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for Event Infomation");

}


EventInfo::~EventInfo()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
EventInfo::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;

  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();
  //ESHandle<SetupData> pSetup;
  //iSetup.get<SetupRecord>().get(pSetup);
  tree->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
EventInfo::beginJob()
{
  tree->Branch("EVENT",&EVENT,"EVENT/i");
  tree->Branch("RUN",&RUN,"RUN/i");
  tree->Branch("LUMI",&LUMI,"LUMI/i");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EventInfo::endJob() {

}

//define this as a plug-in
DEFINE_FWK_MODULE(EventInfo);
