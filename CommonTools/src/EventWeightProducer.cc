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

  produces<int>("npileup");
  produces<double>("weightin");
  produces<double>("weight");
  produces<double>("weightplus");
  produces<double>("weightminus");

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
  int npvin = -1;
  double w = 1.0;
  double win = 1.0;
  double wplus = 1.0;
  double wminus = 1.0;
  float sum_nvtx = 0;
  float ave_nvtx = 0;

  if( PupInfo.isValid()){
    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
      int tmpnpv = PVI->getPU_NumInteractions();
      sum_nvtx += float(tmpnpv);

      int BX = PVI->getBunchCrossing();

      if(BX == 0) {
	npvin = PVI->getPU_NumInteractions();
	npv = PVI->getTrueNumInteractions();
	continue;
      }

    }

    ave_nvtx = sum_nvtx/3.;

    win = LumiWeights_.weight( npvin );
    w = LumiWeights_.weight( npv );
    //w = LumiWeights_.weight3BX( ave_nvtx );
    wplus  = w*PShiftUp_.ShiftWeight( npv );
    wminus = w*PShiftDown_.ShiftWeight( npv );

  }

  std::auto_ptr<int> npileup( new int(npv) );
  std::auto_ptr<double> weightin( new double(win) );
  std::auto_ptr<double> weight( new double(w) );
  std::auto_ptr<double> weightplus( new double(wplus) );
  std::auto_ptr<double> weightminus( new double(wminus) );

  iEvent.put(npileup, "npileup");
  iEvent.put(weightin, "weightin");
  iEvent.put(weight, "weight");
  iEvent.put(weightplus, "weightplus");
  iEvent.put(weightminus, "weightminus");

}

void 
EventWeightProducer::beginJob(){
  std::vector< float > Wlumi ;
  std::vector< float > TrueDist2011;

  for( int i=0; i<50; ++i) {
    TrueDist2011.push_back((float)PileUpRD_[i]);
    Wlumi.push_back((float)PileUpMC_[i]);
  }

  LumiWeights_ = edm::LumiReWeighting(Wlumi, TrueDist2011);

  PShiftDown_ = reweight::PoissonMeanShifter(-0.5);
  PShiftUp_ = reweight::PoissonMeanShifter(0.5);

}


void
EventWeightProducer::endJob() {
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(EventWeightProducer);



