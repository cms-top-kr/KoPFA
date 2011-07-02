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
  PileUpRD_ = cfg.getParameter< std::vector<double> >("PileUpRD"),
  PileUpMC_ = cfg.getParameter< std::vector<double> >("PileUpMC"),
  produces <double> ( "" );
}

EventWeightProducer::~EventWeightProducer()
{

}

void EventWeightProducer::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;

  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);

  std::vector<PileupSummaryInfo>::const_iterator PVI;

  int npv = -1;
  for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {

    int BX = PVI->getBunchCrossing();

    if(BX == 0) { 
      npv = PVI->getPU_NumInteractions();
      continue;
    }

  }

  double w = LumiWeights_.weight( npv );

  std::auto_ptr<double> weight( new double(w) );

  iEvent.put(weight);

}

void 
EventWeightProducer::beginJob(){
  std::vector< float > Wlumi ;
  std::vector< float > TrueDist2011;

  for( int i=0; i<25; ++i) {
    TrueDist2011.push_back((float)PileUpRD_[i]);
    Wlumi.push_back((float)PileUpMC_[i]);
  }

  LumiWeights_ = edm::LumiReWeighting(Wlumi, TrueDist2011);

}


void
EventWeightProducer::endJob() {
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(EventWeightProducer);



