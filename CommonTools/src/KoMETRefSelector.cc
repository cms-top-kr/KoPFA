#include "KoPFA/CommonTools/interface/KoMETRefSelector.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

KoMETRefSelector::KoMETRefSelector(const edm::ParameterSet& cfg)
{
  metLabel_ = cfg.getParameter<edm::InputTag>("metLabel");
  produces<edm::PtrVector<reco::Candidate> >();
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for met study");

  pt = new std::vector<double>();
  eta = new std::vector<double>();
  phi = new std::vector<double>();

}

KoMETRefSelector::~KoMETRefSelector()
{

}

void KoMETRefSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace edm; 

  pt->clear();
  eta->clear();
  phi->clear();

  iEvent.getByLabel(metLabel_, met_);
  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  std::auto_ptr<PtrVector<reco::Candidate> > pos(new PtrVector<reco::Candidate>());

  for (unsigned int i=0; i < met_->size();++i){
    Ptr<pat::MET> metRef = met_->ptrAt(i);
    const pat::MET & met = *metRef;

      pos->push_back(metRef);

      pt->push_back(met.pt());
      eta->push_back(met.eta());
      phi->push_back(met.phi());
  }

  multiplicity = (int) pos->size();

  iEvent.put(pos);
  
  tree->Fill(); 

}

void 
KoMETRefSelector::beginJob(){
   tree->Branch("EVENT",&EVENT,"EVENT/i");
   tree->Branch("RUN",&RUN,"RUN/i");
   tree->Branch("LUMI",&LUMI,"LUMI/i");

   tree->Branch("pt","std::vector<double>",&pt);
   tree->Branch("eta","std::vector<double>",&eta);
   tree->Branch("phi","std::vector<double>",&phi);
   tree->Branch("multiplicity",&multiplicity,"multiplicity/i");
}


void
KoMETRefSelector::endJob() {
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KoMETRefSelector);



