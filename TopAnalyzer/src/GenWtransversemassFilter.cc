// -*- C++ -*-
//
// Package:    GenWtransversemassFilter
// Class:      GenWtransversemassFilter
// 
/**\class GenWtransversemassFilter GenWtransversemassFilter.cc UserCode/GenWtransversemassFilter/src/GenWtransversemassFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: GenWtransversemassFilter.cc,v 1.4 2010/11/01 20:59:19 tjkim Exp $
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

class GenWtransversemassFilter : public edm::EDFilter {
   public:
      explicit GenWtransversemassFilter(const edm::ParameterSet&);
      ~GenWtransversemassFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      // ----------member data ---------------------------
      edm::InputTag genParticlesLabel_;
      bool applyFilter_;
      std::vector<int> decayMode_;
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
GenWtransversemassFilter::GenWtransversemassFilter(const edm::ParameterSet& ps)
{
   //now do what ever initialization is needed
  genParticlesLabel_= ps.getParameter<edm::InputTag>("genParticlesLabel");
  applyFilter_=ps.getUntrackedParameter<bool>("applyFilter",false);
  decayMode_ = ps.getUntrackedParameter<std::vector<int> >("decayMode");
  min_ = ps.getUntrackedParameter<int>("min",0);
  max_ = ps.getUntrackedParameter<int>("max",999);
}


GenWtransversemassFilter::~GenWtransversemassFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
GenWtransversemassFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  if (!applyFilter_)
    return true;


  bool accepted = false;
  using namespace edm;
  using namespace std;
  using namespace reco;

  edm::Handle<reco::GenParticleCollection> genParticles_;
  iEvent.getByLabel(genParticlesLabel_,genParticles_);

  double genWtransversemass;

  if(genParticles_.isValid()){
    for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
      int genId = mcIter->pdgId();
      bool passMode = false;
      for(size_t i = 0 ; i < decayMode_.size() ;i++){
        if(abs(genId) == decayMode_[i]) passMode = true;
      }

      if( passMode ){
        int moid = -99;
        int gmoid = -99;
        const reco::Candidate *mcand = mcIter->mother();
        if( mcand != 0) {
          moid = mcand->pdgId();
          if( mcand->pdgId() == mcIter->pdgId() ) {
            if( mcand->mother() != 0 ){
              const reco::Candidate *gcand = mcand->mother();
              gmoid = gcand->pdgId();
              if( gmoid == 24 ) {
                genWtransversemass = gcand->p4().Mt();
                if( genWtransversemass > min_ && genWtransversemass < max_) accepted = true;
                break;
              }
            }
          }

          if( moid == 24 ) {
            genWtransversemass = mcand->p4().Mt();
            if( genWtransversemass > min_ && genWtransversemass < max_) accepted = true;
            break;
          }
        }
      }
    }
  }

  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
GenWtransversemassFilter::beginJob(){

}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenWtransversemassFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenWtransversemassFilter);



