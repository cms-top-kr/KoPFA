#include "KoPFA/CommonTools/interface/EventWeightProducer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"


using namespace std;

EventWeightProducer::EventWeightProducer(const edm::ParameterSet& cfg)
{
  PUweight_ = cfg.getParameter< std::vector<double> >("PUweight"),
  PUdefault_ = cfg.getParameter< double >("PUdefault"),
  produces <double> ( "" );
}
 
EventWeightProducer::~EventWeightProducer()
{

}

void EventWeightProducer::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;

  edm::Handle<reco::VertexCollection> recVtxs;
  iEvent.getByLabel("offlinePrimaryVertices",recVtxs);
  int mNPV = 0;

  for(unsigned int ind=0;ind<recVtxs->size();ind++) {
    if (!((*recVtxs)[ind].isFake()) && ((*recVtxs)[ind].ndof()>4)
          && (fabs((*recVtxs)[ind].z())<=24.0) &&
          ((*recVtxs)[ind].position().Rho()<=2.0) ) {
            mNPV++;
    }
  } 

  double w = PUdefault_;
  if(mNPV <= (int) PUweight_.size()) w = PUweight_[mNPV-1];

  std::auto_ptr<double> weight( new double(w) );

  iEvent.put(weight);

}

void 
EventWeightProducer::beginJob(){
}


void
EventWeightProducer::endJob() {
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(EventWeightProducer);



