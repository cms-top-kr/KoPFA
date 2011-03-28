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

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/Math/interface/LorentzVector.h"

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
class IsoAnalysis : public edm::EDAnalyzer {
public:
 explicit IsoAnalysis(const edm::ParameterSet& iConfig):
   collectionLabel_(iConfig.getParameter<edm::InputTag>("collectionLabel")),
   pfCandidateLabel_(iConfig.getParameter<edm::InputTag>("pfCandidateLabel")),
   genParticlesLabel_(iConfig.getParameter<edm::InputTag>("genParticlesLabel")),
   matchId_(iConfig.getParameter<int>("matchId"))
 {
   edm::Service<TFileService> fs;
   tree = fs->make<TTree>("tree", "Tree for isolation study");

   ph_dR = new std::vector<double>();
   ph_th = new std::vector<double>();
   ph_decaleta = new std::vector<double>();
   ph_decalphi = new std::vector<double>();
   ph_deta = new std::vector<double>();
   ph_dphi = new std::vector<double>();
   ph_charge = new std::vector<double>();

   fsr_photon_pt = new std::vector<double>();
   fsr_photon_eta = new std::vector<double>();
   fsr_photon_phi = new std::vector<double>();
   fsr_photon_dR = new std::vector<double>();

 }

 ~IsoAnalysis(){ }
   
private:
 virtual void beginJob(){
   //Add event and RUN BRANCHING         
   tree->Branch("EVENT",&EVENT,"EVENT/i");
   tree->Branch("RUN",&RUN,"RUN/i");
   tree->Branch("LUMI",&LUMI,"LUMI/i");
   
   tree->Branch("ph_dR","std::vector<double>",&ph_dR);
   tree->Branch("ph_th","std::vector<double>",&ph_th);
   tree->Branch("ph_decaleta","std::vector<double>",&ph_decaleta);
   tree->Branch("ph_decalphi","std::vector<double>",&ph_decalphi);
   tree->Branch("ph_deta","std::vector<double>",&ph_deta);
   tree->Branch("ph_dphi","std::vector<double>",&ph_dphi);
   tree->Branch("ph_charge","std::vector<double>",&ph_charge);

   tree->Branch("fsr_photon_pt","std::vector<double>",&fsr_photon_pt);
   tree->Branch("fsr_photon_eta","std::vector<double>",&fsr_photon_eta);
   tree->Branch("fsr_photon_phi","std::vector<double>",&fsr_photon_phi);
   tree->Branch("fsr_photon_dR","std::vector<double>",&fsr_photon_dR);

 }

 virtual void endJob(){
     
 }




 virtual void analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup){
    using namespace reco;
    using namespace isodeposit;
    using namespace edm;

    ph_dR->clear();
    ph_th->clear();
    ph_decaleta->clear();
    ph_decalphi->clear();
    ph_deta->clear();
    ph_dphi->clear();
    ph_charge->clear();

    fsr_photon_pt->clear();
    fsr_photon_eta->clear();
    fsr_photon_phi->clear();
    fsr_photon_dR->clear();

    edm::Handle<std::vector<T> > collection_;
    edm::Handle< reco::PFCandidateCollection > pfCandidates_;
    edm::Handle<reco::GenParticleCollection> genParticles_;
    typedef reco::PFCandidateCollection::const_iterator CI;

    iEvent.getByLabel(collectionLabel_,collection_);
    iEvent.getByLabel(pfCandidateLabel_,pfCandidates_);
    iEvent.getByLabel(genParticlesLabel_,genParticles_);

    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();

    for(unsigned i = 0; i != collection_->size(); i++){
      T it = collection_->at(i);
      //to calculate Ecal surface direction from IP
      math::XYZTLorentzVectorD lv(0,0,0,0);
      for(reco::PFCandidateCollection::const_iterator ci  = pfCandidates_->begin(); ci!=pfCandidates_->end(); ++ci) {
	const reco::PFCandidate& pfc = *ci;
	double dR = deltaR(it.eta(), it.phi(), pfc.eta(), pfc.phi());

        int particlePFID = 0;
        if( matchId_ == 11) particlePFID = 2;
        else if( matchId_ == 13) particlePFID = 3;
        else cout << "NO Match ID" << endl;
	if( pfc.particleId() == particlePFID && dR < 0.05 ){
	  double x = pfc.positionAtECALEntrance().x();
	  double y = pfc.positionAtECALEntrance().y();
	  double z = pfc.positionAtECALEntrance().z();
          //replace by ecal surface vector
	  lv.SetPx(x);
	  lv.SetPy(y);
	  lv.SetPz(z);
          lv.SetE(1);
	}
      }

      //for (IM im = it.isoDeposit(pat::PfGammaIso)->begin(); im != it.isoDeposit(pat::PfGammaIso)->end(); ++im) {
      //  ph_dR->push_back(im->dR());
      //  ph_th->push_back(im->value());
      //  double dphi = deltaPhi(im->phi(), it.phi());
      //  double deta = im->eta()-it.eta();
      //  ph_dphi->push_back(dphi);
      //  ph_deta->push_back(deta);
      //}

      for(CI ci = pfCandidates_->begin(); ci!=pfCandidates_->end(); ++ci) {
        const reco::PFCandidate& pfc = *ci;
        double dphi = deltaPhi(pfc.phi(), it.phi());
        double deta = pfc.eta() - it.eta();
        double dR = sqrt(deta*deta+dphi*dphi);

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
        if( pfc.particleId() == 4 && dR < 0.3) {
  
          double decaleta = -99;
          double decalphi = -99;

          if(lv.E() != 0 ){
            decaleta = pfc.eta() - lv.eta();
            decalphi = deltaPhi(pfc.phi(), lv.phi());
          }else{
            cout << "No Ecal surface extrapolated!" << endl;
          }

          ph_dR->push_back(dR);
          ph_th->push_back(pfc.pt());
          ph_deta->push_back(deta);
          ph_dphi->push_back(dphi);
          ph_decaleta->push_back(decaleta);
          ph_decalphi->push_back(decalphi);
          ph_charge->push_back(it.charge());

        }
      } 
	//for studying FSR using generated particles
      double fsr_pt = -1;
      double fsr_eta = -1;
      double fsr_phi = -1 ;
      double fsr_dR = -1;

      if(genParticles_.isValid()){
	for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
	  int genId = mcIter->pdgId();
	  if(abs(genId) == matchId_ && mcIter->numberOfDaughters() > 0 ) {
	    double dRval = deltaR(mcIter->eta(), mcIter->phi(), it.eta(), it.phi());
	    if(dRval < 0.05){
	      for ( GenParticle::const_iterator daughter_particle = mcIter->begin();daughter_particle !=mcIter->end(); ++daughter_particle ){
		int pdg_id = abs((*daughter_particle).pdgId());
		if(pdg_id == 22 && daughter_particle->numberOfDaughters() == 0){
		  fsr_pt = daughter_particle->pt();
		  fsr_eta = daughter_particle->eta() - mcIter->eta();
		  fsr_phi = daughter_particle->phi() - mcIter->phi();
		  while(fsr_phi >=  TMath::Pi() ) fsr_phi -= 2*TMath::Pi();
		  while(fsr_phi < -TMath::Pi() ) fsr_phi += 2*TMath::Pi();
		  fsr_dR = deltaR(daughter_particle->eta(), daughter_particle->phi(), it.eta(), it.phi());
		}
	      }
	    }
	  }
	}
      }

      fsr_photon_pt->push_back(fsr_pt);
      fsr_photon_eta->push_back(fsr_eta);
      fsr_photon_phi->push_back(fsr_phi);
      fsr_photon_dR->push_back(fsr_dR);

    }

    tree->Fill();
  }

  // ----------member data ---------------------------
  edm::InputTag collectionLabel_;
  edm::InputTag pfCandidateLabel_;
  edm::InputTag genParticlesLabel_;


  int matchId_;

  TTree *tree;

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

  std::vector<double>* ph_dR;
  std::vector<double>* ph_th;
  std::vector<double>* ph_decalphi;
  std::vector<double>* ph_decaleta;
  std::vector<double>* ph_dphi;
  std::vector<double>* ph_deta;
  std::vector<double>* ph_charge;

  std::vector<double>* fsr_photon_pt;
  std::vector<double>* fsr_photon_eta;
  std::vector<double>* fsr_photon_phi;
  std::vector<double>* fsr_photon_dR;



};


