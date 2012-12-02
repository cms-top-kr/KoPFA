#ifndef KoPFA_CommonTools_pfElectronAnalyzer_h
#define KoPFA_CommonTools_pfElectronAnalyzer_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
//#include "PFAnalyses/CommonTools/interface/PatElectronSelector.h"
//#include "PFAnalyses/CommonTools/interface/PatLeptonSelector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

class pfElectronAnalyzer : public edm::EDAnalyzer
{
 public:

  explicit pfElectronAnalyzer(const edm::ParameterSet&);
  ~pfElectronAnalyzer();

  void beginJob();
  void analyze(const edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  // Cut version
  edm::InputTag electronLabel_;
  double ptcut_;
  double etacut_;
  
  edm::InputTag beamSpotLabel_;
 
  typedef pat::ElectronCollection::const_iterator MI;
  edm::Handle<pat::ElectronCollection> electrons_;
  edm::Handle<reco::BeamSpot> beamSpot_;

  std::vector<std::string> cutNames;

  TH2F * id2iso; 
  TH2F * id2isoQCD;

  TH1F * id;
  TH1F * idQCD;    

  TH1F * idLike;
  TH1F * idQCDLike;
 

};


#endif

