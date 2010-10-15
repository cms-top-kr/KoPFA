#ifndef KoPFA_CommonTools_KoElectronSelector_h
#define KoPFA_CommonTools_KoElectronSelector_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "PFAnalyses/CommonTools/interface/PatElectronSelector.h"
#include "PFAnalyses/CommonTools/interface/PatLeptonSelector.h"

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

class KoElectronSelector : public edm::EDProducer
{
 public:

  explicit KoElectronSelector(const edm::ParameterSet&);
  ~KoElectronSelector();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  // Cut version
  int version_; // 1 for PFMUON, 2 for VBTF, 3 for TOP , 4 for PFMUON && ISO
  edm::InputTag electronLabel_;
  PatElectronSelector   electronIdSelector_;
  PatElectronIsolationSelector electronIsoSelector_;
  edm::InputTag beamSpotLabel_;
 
  typedef pat::ElectronCollection::const_iterator MI;
  edm::Handle<pat::ElectronCollection> electrons_;
  edm::Handle<reco::BeamSpot> beamSpot_;
  TH1F * cutflow;
  vector<std::string> cutNames;

  TTree *tree;

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;

  std::vector<double>* eta;
  std::vector<double>* phi;
  std::vector<double>* pt;
  int multiplicity;

  std::vector<double>* chIso;
  std::vector<double>* nhIso;
  std::vector<double>* phIso;

  std::vector<double>* chIsoOpt;
  std::vector<double>* phIsoOpt;
  std::vector<double>* nhIsoOpt;

  std::vector<double>* trackIso;
  std::vector<double>* ecalIso;
  std::vector<double>* hcalIso;

};


#endif

