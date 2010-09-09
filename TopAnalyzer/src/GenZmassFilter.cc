// -*- C++ -*-
//
// Package:    GenZmassFilter
// Class:      GenZmassFilter
// 
/**\class GenZmassFilter GenZmassFilter.cc UserCode/GenZmassFilter/src/GenZmassFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: GenZmassFilter.cc,v 1.1 2010/07/22 20:10:20 tjkim Exp $
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


#include "TTree.h"
#include "TFile.h"
#include "TH1.h"



//
// class declaration
//
using namespace edm;
using namespace std;

class GenZmassFilter : public edm::EDFilter {
   public:
      explicit GenZmassFilter(const edm::ParameterSet&);
      ~GenZmassFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      // ----------member data ---------------------------
      edm::InputTag genParticlesLabel_;
      int min_;
      int max_;

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
GenZmassFilter::GenZmassFilter(const edm::ParameterSet& ps)
{
   //now do what ever initialization is needed
  genParticlesLabel_= ps.getParameter<edm::InputTag>("genParticlesLabel");
  min_ = ps.getUntrackedParameter<int>("min",0);
  max_ = ps.getUntrackedParameter<int>("max",999);
}


GenZmassFilter::~GenZmassFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
GenZmassFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  bool accepted = false;
  using namespace edm;
  using namespace std;
  using namespace reco;

  edm::Handle<reco::GenParticleCollection> genParticles_;
  iEvent.getByLabel(genParticlesLabel_,genParticles_);

  double genZmass;

  if(genParticles_.isValid()){
    for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
      int genId = mcIter->pdgId();
      if( abs(genId) == 23 && mcIter->status() ==3 ){
        double gmass =  mcIter->p4().M();
        genZmass = gmass;
        break;
      }
    }
  }

  if( genZmass > min_ && genZmass < max_) accepted = true; 

  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
GenZmassFilter::beginJob(){

}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenZmassFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenZmassFilter);



