// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include <TFile.h>
#include <TTree.h>

using namespace std;
//
// class decleration
//
class MuonIsolationAnalyzer : public edm::EDAnalyzer {
public:
  explicit MuonIsolationAnalyzer(const edm::ParameterSet&);
  ~MuonIsolationAnalyzer();
   
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

 // ----------member data ---------------------------
  edm::InputTag collectionLabel_;

  TTree *tree;

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

  std::vector<double>* eta;
  std::vector<double>* phi;
  std::vector<double>* pt;
  std::vector<double>* chi2dof;

  int multiplicity;

  std::vector<double>* chIso;
  std::vector<double>* nhIso;
  std::vector<double>* phIso;

  std::vector<double>* chIsoOpt03;
  std::vector<double>* phIsoOpt03;
  std::vector<double>* nhIsoOpt03;

  std::vector<double>* chIsoOpt04;
  std::vector<double>* phIsoOpt04;
  std::vector<double>* nhIsoOpt04;

  std::vector<double>* chIsoOpt05;
  std::vector<double>* phIsoOpt05;
  std::vector<double>* nhIsoOpt05;


  std::vector<double>* trackIso;
  std::vector<double>* ecalIso;
  std::vector<double>* hcalIso;

};

MuonIsolationAnalyzer::MuonIsolationAnalyzer(const edm::ParameterSet& iConfig)
{
   collectionLabel_ =  iConfig.getParameter<edm::InputTag>("collectionLabel");
   edm::Service<TFileService> fs;
   tree = fs->make<TTree>("tree", "Tree for isolation study");

   pt = new std::vector<double>();
   eta = new std::vector<double>();
   phi = new std::vector<double>();

   chi2dof= new std::vector<double>();

   chIso = new std::vector<double>();
   nhIso = new std::vector<double>();
   phIso = new std::vector<double>();

   chIsoOpt03 = new std::vector<double>;
   phIsoOpt03 = new std::vector<double>;
   nhIsoOpt03 = new std::vector<double>;

   chIsoOpt04 = new std::vector<double>;
   phIsoOpt04 = new std::vector<double>;
   nhIsoOpt04 = new std::vector<double>;

   chIsoOpt05 = new std::vector<double>;
   phIsoOpt05 = new std::vector<double>;
   nhIsoOpt05 = new std::vector<double>;


   trackIso = new std::vector<double>();
   ecalIso = new std::vector<double>();
   hcalIso = new std::vector<double>();

}

MuonIsolationAnalyzer::~MuonIsolationAnalyzer()
{
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}



void MuonIsolationAnalyzer::beginJob(){
   //Add event and RUN BRANCHING         
   tree->Branch("EVENT",&EVENT,"EVENT/i");
   tree->Branch("RUN",&RUN,"RUN/i");
   tree->Branch("LUMI",&LUMI,"LUMI/i");
   
   tree->Branch("pt","std::vector<double>",&pt);
   tree->Branch("eta","std::vector<double>",&eta);
   tree->Branch("phi","std::vector<double>",&phi);
   tree->Branch("chi2dof","std::vector<double>",&chi2dof);

   tree->Branch("multiplicity",&multiplicity,"multiplicity/i");

   tree->Branch("chIso","std::vector<double>",&chIso);
   tree->Branch("nhIso","std::vector<double>",&nhIso);
   tree->Branch("phIso","std::vector<double>",&phIso);
  
   tree->Branch("chIsoOpt03","std::vector<double>", &chIsoOpt03);
   tree->Branch("phIsoOpt03","std::vector<double>", &phIsoOpt03);
   tree->Branch("nhIsoOpt03","std::vector<double>", &nhIsoOpt03);

   tree->Branch("chIsoOpt04","std::vector<double>", &chIsoOpt04);
   tree->Branch("phIsoOpt04","std::vector<double>", &phIsoOpt04);
   tree->Branch("nhIsoOpt04","std::vector<double>", &nhIsoOpt04);

   tree->Branch("chIsoOpt05","std::vector<double>", &chIsoOpt05);
   tree->Branch("phIsoOpt05","std::vector<double>", &phIsoOpt05);
   tree->Branch("nhIsoOpt05","std::vector<double>", &nhIsoOpt05);

   tree->Branch("trackIso","std::vector<double>",&trackIso);
   tree->Branch("ecalIso","std::vector<double>",&ecalIso);
   tree->Branch("hcalIso","std::vector<double>",&hcalIso);
 
}

void MuonIsolationAnalyzer::endJob(){
     
}

void MuonIsolationAnalyzer::analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup){

    using namespace edm;
    using namespace std;
    using namespace reco;
    using namespace isodeposit;

    pt->clear();
    eta->clear();
    phi->clear();

    chi2dof->clear();

    chIso->clear();
    nhIso->clear();
    phIso->clear();

    chIsoOpt03->clear();
    phIsoOpt03->clear();
    nhIsoOpt03->clear();

    chIsoOpt04->clear();
    phIsoOpt04->clear();
    nhIsoOpt04->clear();

    chIsoOpt05->clear();
    phIsoOpt05->clear();
    nhIsoOpt05->clear();

 
    trackIso->clear();
    ecalIso->clear();
    hcalIso->clear();

    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();
 
    edm::Handle<pat::MuonCollection> collection_;
    iEvent.getByLabel(collectionLabel_,collection_);

    multiplicity = (int) collection_->size();

    typedef pat::MuonCollection::const_iterator MI;

    for(MI mi = collection_->begin() ; mi != collection_->end(); mi++){

      pt->push_back(mi->pt());
      eta->push_back(mi->eta());
      phi->push_back(mi->phi());
      
      if( mi->isGlobalMuon() == true ){ 
        chi2dof->push_back( mi->normChi2() );
      }else if( mi->isTrackerMuon() == true ){
        chi2dof->push_back( mi->innerTrack()->normalizedChi2() );
      }else if( mi->isStandAloneMuon() == true ){
        chi2dof->push_back( mi->outerTrack()->normalizedChi2() );
      } 

      chIso->push_back(mi->chargedHadronIso());
      phIso->push_back(mi->photonIso());
      nhIso->push_back(mi->neutralHadronIso());

      IsoDeposit::AbsVetos vetos_ch;
      IsoDeposit::AbsVetos vetos_nh;
      vetos_nh.push_back(new ThresholdVeto( 0.5 ));
      IsoDeposit::AbsVetos vetos_ph;
      vetos_ph.push_back(new ThresholdVeto( 0.5 ));

      chIsoOpt03->push_back(mi->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first);
      nhIsoOpt03->push_back(mi->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first);
      phIsoOpt03->push_back(mi->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph).first);

      chIsoOpt04->push_back(mi->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
      nhIsoOpt04->push_back(mi->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh).first);
      phIsoOpt04->push_back(mi->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph).first);

      chIsoOpt05->push_back(mi->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.5, vetos_ch).first);
      nhIsoOpt05->push_back(mi->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.5, vetos_nh).first);
      phIsoOpt05->push_back(mi->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.5, vetos_ph).first);


      trackIso->push_back(mi->trackIso());
      ecalIso->push_back(mi->ecalIso());
      hcalIso->push_back(mi->hcalIso());

    }

    tree->Fill();
}


//define this as a plug-in
DEFINE_FWK_MODULE(MuonIsolationAnalyzer);
