// -*- C++ -*-
//
// Package:    DiMuonAnalyzer
// Class:      DiMuonAnalyzer
// 
/**\class DiMuonAnalyzer DiMuonAnalyzer.cc UserCode/DiMuonAnalyzer/src/DiMuonAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tae Jeong Kim,40 R-A32,+41227678602,
//         Created:  Fri Jun  4 17:19:29 CEST 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "TTree.h"
#include "TFile.h" 

//
// class declaration
//

class DiMuonAnalyzer : public edm::EDAnalyzer {
   public:
      explicit DiMuonAnalyzer(const edm::ParameterSet&);
      ~DiMuonAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      std::string outputFile_;
      edm::InputTag muonLabel_;
      TTree* tree;
      TFile* file;
      std::vector<double>* pt;
      // ----------member data ---------------------------
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
DiMuonAnalyzer::DiMuonAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  outputFile_ = iConfig.getParameter< std::string > ("outputFile");
  muonLabel_ =  iConfig.getParameter<edm::InputTag>("muonLabel");
  file = new TFile(outputFile_.c_str(),"RECREATE");
  pt = new std::vector<double>();
}


DiMuonAnalyzer::~DiMuonAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
DiMuonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   
   pt->clear();

   typedef pat::MuonCollection::const_iterator MI;
   edm::Handle<pat::MuonCollection> muons_;
   iEvent.getByLabel(muonLabel_,muons_);

   for(MI mi = muons_->begin(); mi != muons_->end(); mi++){
    pt->push_back(mi->pt());
   }
   
   //ESHandle<SetupData> pSetup;
   //iSetup.get<SetupRecord>().get(pSetup);
   tree->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonAnalyzer::beginJob()
{
  tree = new TTree("DiMuonTree", "Tree for Top quark study");
  tree->Branch("pt", "std::vector<double>", &pt);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DiMuonAnalyzer::endJob() {
  file->Write();
  file->Close();
}

//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonAnalyzer);
