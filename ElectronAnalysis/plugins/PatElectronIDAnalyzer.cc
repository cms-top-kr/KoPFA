#ifndef KoPFA_ElectronAnalysis_PatElectronIDAnalyzer_H
#define KoPFA_ElectronAnalysis_PatElectronIDAnalyzer_H

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
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TLorentzVector.h"

#include <memory>
#include <vector>
#include <map>
#include <string>

using namespace std;

class PatElectronIDAnalyzer : public edm::EDAnalyzer
{
public:
  PatElectronIDAnalyzer(const edm::ParameterSet& pset);
  ~PatElectronIDAnalyzer() {};

  void beginJob();
  void endJob();
  void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);

private:
  double getIsolation(const pat::Electron& electron, const pat::IsolationKeys num);

private:
  edm::InputTag electronLabel_;
  edm::InputTag metLabel_;
  std::vector<std::string> idNames_;
  int idMask_;

private:
  TTree* tree_;
  int run_, event_, lumi_;
  std::map<std::string, vector<int> > EId_;
  std::map<std::string, double> ZMass_;
  std::map<std::string, int> Mva_;
  double Met_;
};

PatElectronIDAnalyzer::PatElectronIDAnalyzer(const edm::ParameterSet& pset)
{
  electronLabel_ = pset.getUntrackedParameter<edm::InputTag>("electronLabel");
  metLabel_ = pset.getUntrackedParameter<edm::InputTag>("metLabel");
  idNames_ = pset.getUntrackedParameter<std::vector<std::string> >("idNames");
  idMask_ = pset.getUntrackedParameter<int>("idMask", 5);
  idNames_.push_back("probe");
}

void PatElectronIDAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("tree", "tree");

  tree_->Branch("event", &event_, "event/i");
  tree_->Branch("run", &run_, "run/i");
  tree_->Branch("lumi", &lumi_, "lumi/i");

  for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
        idName != idNames_.end(); ++idName )
  {
    tree_->Branch(("ZMass_"+*idName).c_str(), &(ZMass_[*idName]), ("ZMass_"+*idName+"/d").c_str());
    tree_->Branch(("Mva_"+*idName).c_str(), &(ZMass_[*idName]), ("Mva_"+*idName+"/i").c_str());
  }
  tree_->Branch("met", &Met_, "met/d");
}

void PatElectronIDAnalyzer::endJob()
{
}

void PatElectronIDAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  run_ = event.id().run();
  lumi_ = event.id().luminosityBlock();
  event_ = event.id().event();

  for ( std::vector<std::string>::const_iterator idName = idNames_.begin(); idName != idNames_.end(); ++idName ){
    ZMass_[*idName] = -9.9;
    Mva_[*idName] = -9;
    EId_[*idName].clear();
  }

  Met_ = -999;

  edm::Handle<edm::View<pat::Electron> > electronHandle;
  event.getByLabel(electronLabel_, electronHandle);

  edm::Handle<edm::View<pat::MET> > metHandle;
  event.getByLabel(metLabel_, metHandle);
  Met_ = metHandle->begin()->pt();

  for (unsigned int i=0; i < electronHandle->size();++i){
    const pat::Electron ele = electronHandle->at(i);

    for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
          idName != idNames_.end(); ++idName )
    {
      bool iso = (ele.chargedHadronIso() + ele.neutralHadronIso() + ele.photonIso())/ele.pt() < 0.01;
      if( *idName == "probe"){
        if( iso ) EId_[*idName].push_back(i);  
      }else{
        bool pass = ((int)ele.electronID(*idName) & idMask_) == idMask_;
        if( pass && iso){ 
          EId_[*idName].push_back(i);
        }
      }
    }

  }

  // Pick leading and 2nd reading electrons
  for ( std::vector<std::string>::const_iterator idName = idNames_.begin(); idName != idNames_.end(); ++idName ){

    if( EId_[*idName].size() >= 2 ){
      int index1 = EId_[*idName][0];
      int index2 = EId_[*idName][1];

      const pat::Electron ele1 = electronHandle->at(index1);
      const pat::Electron ele2 = electronHandle->at(index2);
      bool mva = ele1.mva() > -0.1 && ele2.mva() > -0.1; 

      TLorentzVector e1(ele1.px(),ele1.py(),ele1.pz(),ele1.energy()); 
      TLorentzVector e2(ele2.px(),ele2.py(),ele2.pz(),ele2.energy()); 
      TLorentzVector Z = e1 + e2;
      ZMass_[*idName] = Z.M();
      Mva_[*idName] = mva;
      //cout << *idName << " " << ZMass_[*idName] << " " << mva << endl;
    }
  
  }

  tree_->Fill();
}

DEFINE_FWK_MODULE(PatElectronIDAnalyzer);

#endif

