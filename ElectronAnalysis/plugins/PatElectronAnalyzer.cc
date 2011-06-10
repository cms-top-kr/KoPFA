#ifndef KoPFA_ElectronAnalysis_KoPatElectronAnalyzer_H
#define KoPFA_ElectronAnalysis_KoPatElectronAnalyzer_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

#include <memory>
#include <vector>
#include <map>
#include <string>

class KoPatElectronAnalyzer : public edm::EDAnalyzer
{
public:
  KoPatElectronAnalyzer(const edm::ParameterSet& pset);
  ~KoPatElectronAnalyzer() {};

  void beginJob();
  void endJob();
  void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);

private:
  double getIsolation(const pat::Electron& electron, const pat::IsolationKeys num);

private:
  edm::InputTag electronLabel_;
  std::vector<std::string> idNames_;
  int idMask_;

private:
  TTree* tree_;
  int run_, event_, lumi_;
  reco::Candidate::LorentzVector* brE1P4_, * brE2P4_;
  int brNE_;
  double brE1Q_, brE1ChIso_, brE1PhIso_, brE1NhIso_, brE1RelIso_;
  double brE2Q_, brE2ChIso_, brE2PhIso_, brE2NhIso_, brE2RelIso_;
  double brEEQ_, brEEM_, brEEDR_, brEEDPhi_;
  std::map<std::string, int> brE1Id_, brE2Id_;
  
};

KoPatElectronAnalyzer::KoPatElectronAnalyzer(const edm::ParameterSet& pset)
{
  electronLabel_ = pset.getUntrackedParameter<edm::InputTag>("electronLabel");
  idNames_ = pset.getUntrackedParameter<std::vector<std::string> >("idNames");
  idMask_ = pset.getUntrackedParameter<int>("idMask", 5);

  brE1P4_ = new reco::Candidate::LorentzVector;
  brE2P4_ = new reco::Candidate::LorentzVector;

  for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
        idName != idNames_.end(); ++idName )
  {
    brE1Id_[*idName] = 0;
    brE2Id_[*idName] = 0;
  }
}

void KoPatElectronAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("tree", "tree");

  tree_->Branch("event", &event_, "event/i");
  tree_->Branch("run", &run_, "run/i");
  tree_->Branch("lumi", &lumi_, "lumi/i");

  tree_->Branch("e1P4", "reco::Candidate::LorentzVector", &brE1P4_);
  tree_->Branch("e2P4", "reco::Candidate::LorentzVector", &brE2P4_);

  tree_->Branch("nE", &brNE_, "nE/i");
  tree_->Branch("e1Q"     , &brE1Q_     , "e1Q/d"     );
  tree_->Branch("e1ChIso" , &brE1ChIso_ , "e1ChIso/d" );
  tree_->Branch("e1PhIso" , &brE1PhIso_ , "e1PhIso/d" );
  tree_->Branch("e1NhIso" , &brE1NhIso_ , "e1NhIso/d" );
  tree_->Branch("e1RelIso", &brE1RelIso_, "e1RelIso/d");
  tree_->Branch("e2Q"     , &brE2Q_     , "e2 Q/d"     );
  tree_->Branch("e2ChIso" , &brE2ChIso_ , "e2ChIso/d" );
  tree_->Branch("e2PhIso" , &brE2PhIso_ , "e2PhIso/d" );
  tree_->Branch("e2NhIso" , &brE2NhIso_ , "e2NhIso/d" );
  tree_->Branch("e2RelIso", &brE2RelIso_, "e2RelIso/d");
  tree_->Branch("eeQ"   , &brEEQ_   , "eeQ/d"   );
  tree_->Branch("eeM"   , &brEEM_   , "eeM/d"   );
  tree_->Branch("eeDR"  , &brEEDR_  , "eeDR/d"  );
  tree_->Branch("eeDPhi", &brEEDPhi_, "eeDPhi/d");

  for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
        idName != idNames_.end(); ++idName )
  {
    tree_->Branch(("e1Id_"+*idName).c_str(), &(brE1Id_[*idName]), ("e1Id_"+*idName+"/i").c_str());
    tree_->Branch(("e2Id_"+*idName).c_str(), &(brE2Id_[*idName]), ("e2Id_"+*idName+"/i").c_str());
  }
}

void KoPatElectronAnalyzer::endJob()
{
}

void KoPatElectronAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  run_ = event.id().run();
  lumi_ = event.id().luminosityBlock();
  event_ = event.id().event();

  *brE1P4_ = *brE2P4_ = reco::Candidate::LorentzVector(0,0,0,0);
  brNE_ = 0;
  brE1Q_ = brE2Q_ = 0;
  brE1ChIso_ = brE1PhIso_ = brE1NhIso_ = brE1RelIso_ = -999;
  brE2ChIso_ = brE2PhIso_ = brE2NhIso_ = brE2RelIso_ = -999;
  brEEQ_ = 0;
  brEEM_ = brEEDR_ = brEEDPhi_ = -999;
  for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
        idName != idNames_.end(); ++idName )
  {
    brE1Id_[*idName] = 0;
    brE2Id_[*idName] = 0;
  }

  edm::Handle<edm::View<pat::Electron> > electronHandle;
  event.getByLabel(electronLabel_, electronHandle);
  brNE_ = electronHandle->size();

  // Pick leading and 2nd reading electrons
  edm::View<pat::Electron>::const_iterator e1 = electronHandle->end();
  edm::View<pat::Electron>::const_iterator e2 = electronHandle->end();
  if ( brNE_ > 0 ) e1 = electronHandle->begin();
  if ( brNE_ > 1 ) e2 = e1+1;

  if ( brNE_ > 0 )
  {
    *brE1P4_ = e1->p4();
    brE1Q_= e1->charge();

    brE1ChIso_ = getIsolation(*e1, pat::PfChargedHadronIso);
    brE1NhIso_ = getIsolation(*e1, pat::PfNeutralHadronIso);
    brE1PhIso_ = getIsolation(*e1, pat::PfGammaIso);
    brE1RelIso_ = (brE1ChIso_+brE1PhIso_+brE1PhIso_)/brE1P4_->pt();

    for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
          idName != idNames_.end(); ++idName )
    {
      brE1Id_[*idName] = ((int)e1->electronID(*idName) & idMask_) == idMask_;
    }
  }

  if ( brNE_ > 1 )
  {
    *brE2P4_ = e2->p4();
    brE2Q_ = e2->charge();

    brE2ChIso_ = getIsolation(*e2, pat::PfChargedHadronIso);
    brE2NhIso_ = getIsolation(*e2, pat::PfNeutralHadronIso);
    brE2PhIso_ = getIsolation(*e2, pat::PfGammaIso);
    brE2RelIso_ = (brE2ChIso_+brE2PhIso_+brE2PhIso_)/brE2P4_->pt();

    for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
          idName != idNames_.end(); ++idName )
    {
      brE2Id_[*idName] = ((int)e2->electronID(*idName) & idMask_) == idMask_;
    }
  }

  if ( brNE_ > 1 )
  {
    brEEQ_ = brE1Q_+brE2Q_;
    brEEM_ = (*brE1P4_+*brE2P4_).mass();
    brEEDR_ = deltaR(*e1, *e2);
    brEEDPhi_ = deltaPhi(e1->phi(), e2->phi());
  }
  
  tree_->Fill();
}

double KoPatElectronAnalyzer::getIsolation(const pat::Electron& electron, const pat::IsolationKeys num)
{
  reco::isodeposit::Direction dir(electron.eta(), electron.phi());
  reco::isodeposit::AbsVetos vetos;
  vetos.push_back(new reco::isodeposit::ThresholdVeto( 0.5 ));
  return electron.isoDeposit(num)->depositAndCountWithin(0.3, vetos).first;
}

DEFINE_FWK_MODULE(KoPatElectronAnalyzer);

#endif

