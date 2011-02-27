// -*- C++ -*-
//
// Package:    VertexFilter
// Class:      VertexFilter
// 
/**\class VertexFilter VertexFilter.cc UserCode/VertexFilter/src/VertexFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: VertexFilter.cc,v 1.1 2010/07/22 20:10:20 tjkim Exp $
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

class VertexFilter : public edm::EDFilter {
   public:
      explicit VertexFilter(const edm::ParameterSet&);
      ~VertexFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      // ----------member data ---------------------------
      edm::InputTag vertexLabel_;
      int min_;
      int max_;

      TTree* tree;

      int multiplicity;

      std::vector<double>* ntrk;
      std::vector<double>* chi2;
      std::vector<double>* ndof;
      std::vector<double>* x;
      std::vector<double>* dx;
      std::vector<double>* y;
      std::vector<double>* dy;
      std::vector<double>* z;
      std::vector<double>* dz;
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
VertexFilter::VertexFilter(const edm::ParameterSet& ps)
{
   //now do what ever initialization is needed
  vertexLabel_ =  ps.getParameter<edm::InputTag>("vertexLabel");
  min_ = ps.getUntrackedParameter<int>("min",1);
  max_ = ps.getUntrackedParameter<int>("max",999);

  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for pile up study");

  ntrk = new std::vector<double>();
  chi2 = new std::vector<double>();
  ndof = new std::vector<double>();
  x = new std::vector<double>();
  dx = new std::vector<double>();
  y = new std::vector<double>();
  dy = new std::vector<double>();
  z = new std::vector<double>();
  dz = new std::vector<double>();

}


VertexFilter::~VertexFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
VertexFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  bool accepted = false;
  using namespace edm;
  using namespace std;
  using namespace reco;

  ntrk->clear();
  chi2->clear();
  ndof->clear();
  x->clear();
  dx->clear();
  y->clear();
  dy->clear();
  z->clear();
  dz->clear();

  edm::Handle<reco::VertexCollection> recVtxs_;
  iEvent.getByLabel(vertexLabel_,recVtxs_);

  multiplicity = 0 ;

  for(reco::VertexCollection::const_iterator v=recVtxs_->begin();  v!=recVtxs_->end(); ++v){
    if (!(v->isFake()) && (v->ndof()>4) && (fabs(v->z())<=24.0) && (v->position().Rho()<=2.0) ) {
            multiplicity++;
    }

    ntrk->push_back(v->tracksSize());
    chi2->push_back(v->chi2());
    ndof->push_back(v->ndof());
    x->push_back(v->x());
    dx->push_back(v->xError());
    y->push_back(v->y());
    dy->push_back(v->yError());
    z->push_back(v->z());
    dz->push_back(v->zError());
  }
  //iSetup.get<SetupRecord>().get(pSetup);
  tree->Fill();

  if( multiplicity >= min_ && multiplicity <= max_) accepted = true;
  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
VertexFilter::beginJob()
{
  tree->Branch("multiplicity",&multiplicity,"multiplicity/i");
  tree->Branch("ntrk","std::vector<double>",&ntrk);
  tree->Branch("chi2","std::vector<double>",&chi2);
  tree->Branch("ndof","std::vector<double>",&ndof);
  tree->Branch("x","std::vector<double>",&x);
  tree->Branch("dx","std::vector<double>",&dx);
  tree->Branch("y","std::vector<double>",&y);
  tree->Branch("dy","std::vector<double>",&dy);
  tree->Branch("z","std::vector<double>",&z);
  tree->Branch("dz","std::vector<double>",&dz);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
VertexFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(VertexFilter);



