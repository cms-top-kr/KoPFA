#include "KoPFA/CommonTools/interface/KoMETSelector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

KoMETSelector::KoMETSelector(const edm::ParameterSet& cfg)
{
  metLabel_ = cfg.getParameter<edm::InputTag>("metLabel");

  produces<std::vector<pat::MET> >("");
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for met study");

  pt = new std::vector<double>();
  eta = new std::vector<double>();
  phi = new std::vector<double>();
}

KoMETSelector::~KoMETSelector()
{

}

void KoMETSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;

  pt->clear();
  eta->clear();
  phi->clear();

  iEvent.getByLabel(metLabel_, met_);
  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  std::auto_ptr<std::vector<pat::MET> > pos(new std::vector<pat::MET>());

  for (unsigned int i=0; i < met_->size();++i){
    const pat::MET met = met_->at(i);
  
      pos->push_back((*met_)[i]);
      pt->push_back(met.pt());
      eta->push_back(met.eta());
      phi->push_back(met.phi());
  }

  multiplicity = (int) pos->size();

  iEvent.put(pos);
 
  tree->Fill(); 

}

void 
KoMETSelector::beginJob(){
   tree->Branch("EVENT",&EVENT,"EVENT/i");
   tree->Branch("RUN",&RUN,"RUN/i");
   tree->Branch("LUMI",&LUMI,"LUMI/i");

   tree->Branch("pt","std::vector<double>",&pt);
   tree->Branch("eta","std::vector<double>",&eta);
   tree->Branch("phi","std::vector<double>",&phi);
   tree->Branch("multiplicity",&multiplicity,"multiplicity/i");

}


void
KoMETSelector::endJob() {
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KoMETSelector);



