// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "RecoEgamma/ElectronIdentification/interface/ElectronMVAEstimator.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
//
// class declaration
//

using namespace std;
using namespace reco;
class ElectronIdMVA : public edm::EDFilter {
	public:
		explicit ElectronIdMVA(const edm::ParameterSet&);
		~ElectronIdMVA();

	private:
		virtual bool filter(edm::Event&, const edm::EventSetup&);


		// ----------member data ---------------------------
		edm::InputTag vertexTag;
		edm::InputTag electronTag;
                string mvaWeightFileEleID;
                string path_mvaWeightFileEleID;

		ElectronMVAEstimator *mvaID_;
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
ElectronIdMVA::ElectronIdMVA(const edm::ParameterSet& iConfig) {
	vertexTag = iConfig.getParameter<edm::InputTag>("vertexTag");
	electronTag = iConfig.getParameter<edm::InputTag>("electronTag");
	mvaWeightFileEleID = iConfig.getParameter<string>("HZZmvaWeightFile");

	//produces<reco::GsfElectronCollection>();
        produces<std::vector<pat::Electron> >("");
	path_mvaWeightFileEleID = edm::FileInPath ( mvaWeightFileEleID.c_str() ).fullPath();
	FILE * fileEleID = fopen(path_mvaWeightFileEleID.c_str(), "r");
	if (fileEleID) {
	  fclose(fileEleID);
	}
	else {
	  string err = "ElectronIdMVA: cannot open weight file '";
	  err += path_mvaWeightFileEleID;
	  err += "'";
	  throw invalid_argument( err );
	}

	mvaID_ = new ElectronMVAEstimator(path_mvaWeightFileEleID);
}


ElectronIdMVA::~ElectronIdMVA()
{
 
  delete mvaID_;
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool ElectronIdMVA::filter(edm::Event& iEvent, const edm::EventSetup& iSetup) {
	using namespace edm;

	//std::auto_ptr<reco::GsfElectronCollection> mvaElectrons(new reco::GsfElectronCollection);
        std::auto_ptr<std::vector<pat::Electron> > mvaElectrons(new std::vector<pat::Electron>());

	Handle<reco::VertexCollection>  vertexCollection;
	iEvent.getByLabel(vertexTag, vertexCollection);
	int nVtx = vertexCollection->size();

	//Handle<reco::GsfElectronCollection> egCollection;
        Handle<pat::ElectronCollection> egCollection;
	iEvent.getByLabel(electronTag,egCollection);
	const pat::ElectronCollection egCandidates = (*egCollection.product());
	for ( pat::ElectronCollection::const_iterator egIter = egCandidates.begin(); egIter != egCandidates.end(); ++egIter) {

	  double mvaVal = mvaID_->mva( *egIter, nVtx );

	  double eleEta = fabs(egIter->eta());
	  if (eleEta <= 1.485) {
	    mvaElectrons->push_back( *egIter );
	    reco::GsfElectron::MvaOutput myMvaOutput;
	    myMvaOutput.mva = mvaVal;
	    mvaElectrons->back().setMvaOutput(myMvaOutput);
	  }
	  else if (eleEta > 1.485) {
	    mvaElectrons->push_back( *egIter );
	    reco::GsfElectron::MvaOutput myMvaOutput;
	    myMvaOutput.mva = mvaVal;
	    mvaElectrons->back().setMvaOutput(myMvaOutput);
	  }
	  
	}
	

	iEvent.put(mvaElectrons);

	return true;
}

//define this as a plug-in
DEFINE_FWK_MODULE(ElectronIdMVA);
