// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "AnalysisDataFormats/PFAnalyses/interface/RandomCone.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"

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
template<typename T>
class IsoNtuple : public edm::EDAnalyzer {
public:
 explicit IsoNtuple(const edm::ParameterSet& iConfig):
   collectionLabel_(iConfig.getParameter<edm::InputTag>("collectionLabel")),
   pfCandidateLabel_(iConfig.getParameter<edm::InputTag>("pfCandidateLabel")),
   dRch_(iConfig.getUntrackedParameter<double>("dRch",0.4)),
   dRnh_(iConfig.getUntrackedParameter<double>("dRnh",0.4)),
   dRph_(iConfig.getUntrackedParameter<double>("dRph",0.4)),
   vetoCHThreshold_(iConfig.getUntrackedParameter<double>("vetoCHThreshold",0.0)),
   vetoNHThreshold_(iConfig.getUntrackedParameter<double>("vetoNHThreshold",0.0)),
   vetoPHThreshold_(iConfig.getUntrackedParameter<double>("vetoPHThreshold",0.0)),
   vetoCHdR_(iConfig.getUntrackedParameter<double>("vetoCHdR",0.0)),
   vetoNHdR_(iConfig.getUntrackedParameter<double>("vetoNHdR",0.0)),
   vetoPHdR_(iConfig.getUntrackedParameter<double>("vetoPHdR",0.0)),
   vetoCHre_(iConfig.getUntrackedParameter< std::vector<double> >("vetoCHre")),
   vetoNHre_(iConfig.getUntrackedParameter< std::vector<double> >("vetoNHre")),
   vetoPHre_(iConfig.getUntrackedParameter< std::vector<double> >("vetoPHre"))
 {
   edm::Service<TFileService> fs;
   tree = fs->make<TTree>("tree", "Tree for isolation study");

   pt = new std::vector<double>();
   eta = new std::vector<double>();
   phi = new std::vector<double>();

   chIso = new std::vector<double>();
   nhIso = new std::vector<double>();
   phIso = new std::vector<double>();
   chN = new std::vector<double>();
   nhN = new std::vector<double>();
   phN = new std::vector<double>();

   ch_dR = new std::vector<double>();
   ch_th = new std::vector<double>();
   ch_deta = new std::vector<double>();
   ch_dphi = new std::vector<double>();

   nh_dR = new std::vector<double>();
   nh_th = new std::vector<double>();
   nh_deta = new std::vector<double>();
   nh_dphi = new std::vector<double>();

   ph_dR = new std::vector<double>();
   ph_th = new std::vector<double>();
   ph_deta = new std::vector<double>();
   ph_dphi = new std::vector<double>();

   chargedhadron_pt = new std::vector<double>();
   chargedhadron_eta = new std::vector<double>();
   chargedhadron_phi = new std::vector<double>();
 }

 ~IsoNtuple(){ }
   
private:
 virtual void beginJob(){
   //Add event and RUN BRANCHING         
   tree->Branch("EVENT",&EVENT,"EVENT/i");
   tree->Branch("RUN",&RUN,"RUN/i");
   tree->Branch("LUMI",&LUMI,"LUMI/i");
   
   tree->Branch("pt","std::vector<double>",&pt);
   tree->Branch("eta","std::vector<double>",&eta);
   tree->Branch("phi","std::vector<double>",&phi);

   tree->Branch("chIso","std::vector<double>",&chIso);
   tree->Branch("nhIso","std::vector<double>",&nhIso);
   tree->Branch("phIso","std::vector<double>",&phIso);
   tree->Branch("chN","std::vector<double>",&chN);
   tree->Branch("nhN","std::vector<double>",&nhN);
   tree->Branch("phN","std::vector<double>",&phN);

   tree->Branch("ch_dR","std::vector<double>",&ch_dR);
   tree->Branch("ch_th","std::vector<double>",&ch_th);
   tree->Branch("ch_deta","std::vector<double>",&ch_deta);
   tree->Branch("ch_dphi","std::vector<double>",&ch_dphi);

   tree->Branch("nh_dR","std::vector<double>",&nh_dR);
   tree->Branch("nh_th","std::vector<double>",&nh_th);
   tree->Branch("nh_deta","std::vector<double>",&nh_deta);
   tree->Branch("nh_dphi","std::vector<double>",&nh_dphi);

   tree->Branch("ph_dR","std::vector<double>",&ph_dR);
   tree->Branch("ph_th","std::vector<double>",&ph_th);
   tree->Branch("ph_deta","std::vector<double>",&ph_deta);
   tree->Branch("ph_dphi","std::vector<double>",&ph_dphi);

   tree->Branch("chargedhadron_pt","std::vector<double>",&chargedhadron_pt);
   tree->Branch("chargedhadron_phi","std::vector<double>",&chargedhadron_phi);
   tree->Branch("chargedhadron_eta","std::vector<double>",&chargedhadron_eta);
    
 }

 virtual void endJob(){
     
 }




 virtual void analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup){
    using namespace reco;
    using namespace isodeposit;
    using namespace edm;

    pt->clear();
    eta->clear();
    phi->clear();

    chIso->clear();
    nhIso->clear();
    phIso->clear();
    chN->clear();
    nhN->clear();
    phN->clear();

    ch_dR->clear();
    ch_th->clear();
    ch_deta->clear();
    ch_dphi->clear();

    nh_dR->clear();
    nh_th->clear();
    nh_deta->clear();
    nh_dphi->clear();

    ph_dR->clear();
    ph_th->clear();
    ph_deta->clear();
    ph_dphi->clear();

    chargedhadron_pt->clear();
    chargedhadron_eta->clear();
    chargedhadron_phi->clear();

    edm::Handle<std::vector<T> > collection_;
    edm::Handle< reco::PFCandidateCollection > pfCandidates_;
    typedef reco::PFCandidateCollection::const_iterator CI;

    iEvent.getByLabel(collectionLabel_,collection_);
    iEvent.getByLabel(pfCandidateLabel_,pfCandidates_);

    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();

    for(unsigned i = 0; i != collection_->size(); i++){
      T it = collection_->at(i);

      pt->push_back(it.pt());
      eta->push_back(it.eta());
      phi->push_back(it.phi());

      reco::IsoDeposit::Direction Dir = Direction(it.eta(),it.phi());

      IsoDeposit::AbsVetos vetos_ch;
      vetos_ch.push_back(new ConeVeto( Dir, vetoCHdR_ ));
      vetos_ch.push_back(new ThresholdVeto( vetoCHThreshold_ ));
      vetos_ch.push_back(new RectangularEtaPhiVeto( Dir, vetoCHre_[0], vetoCHre_[1], vetoCHre_[2], vetoCHre_[3]));
      
      IsoDeposit::AbsVetos vetos_nh;
      vetos_nh.push_back(new ConeVeto( Dir, vetoNHdR_ ));    
      vetos_nh.push_back(new ThresholdVeto( vetoNHThreshold_ ));
      vetos_nh.push_back(new RectangularEtaPhiVeto( Dir, vetoNHre_[0], vetoNHre_[1], vetoNHre_[2], vetoNHre_[3]));

      IsoDeposit::AbsVetos vetos_ph;
      vetos_ph.push_back(new ConeVeto( Dir, vetoPHdR_ ));
      vetos_ph.push_back(new ThresholdVeto( vetoPHThreshold_ ));
      vetos_ph.push_back(new RectangularEtaPhiVeto( Dir, vetoPHre_[0], vetoPHre_[1], vetoPHre_[2], vetoPHre_[3]));

      double chiso = it.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(dRch_, vetos_ch).first;
      double nhiso = it.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(dRnh_, vetos_nh).first;
      double phiso = it.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(dRph_, vetos_ph).first;
      double chn = it.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(dRch_, vetos_ch).second;
      double nhn = it.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(dRnh_, vetos_nh).second;
      double phn = it.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(dRph_, vetos_ph).second;
      chIso->push_back(chiso);
      nhIso->push_back(nhiso);
      phIso->push_back(phiso);
      chN->push_back(chn);
      nhN->push_back(nhn);
      phN->push_back(phn);

      //to study surrounding particles
      typedef reco::IsoDeposit::const_iterator IM;

      //usrrounding charged hadrons
      for (IM im = it.isoDeposit(pat::PfChargedHadronIso)->begin(); im != it.isoDeposit(pat::PfChargedHadronIso)->end(); ++im) {
	ch_dR->push_back(im->dR());
        ch_th->push_back(im->value());
        double dphi = deltaPhi(im->phi(), it.phi());
        double deta = im->eta()-it.eta();
	ch_dphi->push_back(dphi);
        ch_deta->push_back(deta);
      }
      for (IM im = it.isoDeposit(pat::PfNeutralHadronIso)->begin(); im != it.isoDeposit(pat::PfNeutralHadronIso)->end(); ++im) {
        nh_dR->push_back(im->dR());
        nh_th->push_back(im->value());
        double dphi = deltaPhi(im->phi(), it.phi());
        double deta = im->eta()-it.eta();
        nh_dphi->push_back(dphi);
        nh_deta->push_back(deta);
      }
      for (IM im = it.isoDeposit(pat::PfGammaIso)->begin(); im != it.isoDeposit(pat::PfGammaIso)->end(); ++im) {
        ph_dR->push_back(im->dR());
        ph_th->push_back(im->value());
        double dphi = deltaPhi(im->phi(), it.phi());
        double deta = im->eta()-it.eta();
        ph_dphi->push_back(dphi);
        ph_deta->push_back(deta);
      }

//      for(CI ci = pfCandidates_->begin(); ci!=pfCandidates_->end(); ++ci) {
//        const reco::PFCandidate& pfc = *ci;
//        double dphi = deltaPhi(pfc.phi(), it.phi());
//        double deta = pfc.eta() - it.eta();
//        double dR = sqrt(deta*deta+dphi*dphi);

//        if( pfc.particleId() == 1 && dR < 1.0) {
//          ch_dR->push_back(dR);
//          ch_th->push_back(pfc.pt());
//          ch_dphi->push_back(dphi);
//          ch_deta->push_back(deta);
//        }
//        if( pfc.particleId() == 5 && dR < 1.0) {
//          nh_dR->push_back(dR);
//          nh_th->push_back(pfc.pt());
//          nh_dphi->push_back(dphi);
//          nh_deta->push_back(deta);
//        }
//        if( pfc.particleId() == 4 && dR < 1.0) {
//          ph_dR->push_back(dR);
//          ph_th->push_back(pfc.pt());
//          ph_dphi->push_back(dphi);
//          ph_deta->push_back(deta);
//        }
//      } 
    }

    for(CI ci = pfCandidates_->begin(); ci!=pfCandidates_->end(); ++ci) {
      const reco::PFCandidate& pfc = *ci;
      if( pfc.particleId() == 1 ) {
	chargedhadron_pt->push_back( pfc.pt()); 
	chargedhadron_eta->push_back( pfc.eta()); 
	chargedhadron_phi->push_back( pfc.phi()); 
      }
    }

    tree->Fill();
  }

  // ----------member data ---------------------------
  edm::InputTag collectionLabel_;
  edm::InputTag pfCandidateLabel_;

  double dRch_;
  double dRnh_;
  double dRph_;
  double vetoCHThreshold_;
  double vetoNHThreshold_;
  double vetoPHThreshold_;
  double vetoCHdR_;
  double vetoNHdR_;
  double vetoPHdR_;
  vector<double> vetoCHre_;
  vector<double> vetoNHre_;
  vector<double> vetoPHre_;

  TTree *tree;

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

  std::vector<double>* eta;
  std::vector<double>* phi;
  std::vector<double>* pt;

  std::vector<double>* chIso;
  std::vector<double>* nhIso;
  std::vector<double>* phIso;
  std::vector<double>* chN;
  std::vector<double>* nhN;
  std::vector<double>* phN;

  std::vector<double>* ch_dR;
  std::vector<double>* ch_th;
  std::vector<double>* ch_dphi;
  std::vector<double>* ch_deta;

  std::vector<double>* nh_dR;
  std::vector<double>* nh_th;
  std::vector<double>* nh_dphi;
  std::vector<double>* nh_deta;

  std::vector<double>* ph_dR;
  std::vector<double>* ph_th;
  std::vector<double>* ph_dphi;
  std::vector<double>* ph_deta;

  std::vector<double>* chargedhadron_pt;
  std::vector<double>* chargedhadron_eta;
  std::vector<double>* chargedhadron_phi;
 

};


