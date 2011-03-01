#ifndef KoPFA_CommonTools_KoMuonRefSelector_h
#define KoPFA_CommonTools_KoMuonRefSelector_h

// store the position of the Z combinaison the closest to the Z mass

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/RefToBaseVector.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/Ptr.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "KoPFA/CommonTools/interface/MuonIDSelector.h"
#include "PFAnalyses/CommonTools/interface/PatMuonSelector.h"
#include "PFAnalyses/CommonTools/interface/PatLeptonSelector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

class KoMuonRefSelector : public edm::EDProducer
{
 public:

  explicit KoMuonRefSelector(const edm::ParameterSet&);
  ~KoMuonRefSelector();

  void beginJob();
  void produce(edm::Event&, const edm::EventSetup&);
  void endJob();

 private:

  // Cut version
  int version_; // 1 for PFMUON, 2 for VBTF, 3 for TOP , 4 for PFMUON && ISO
  vector<std::string> cut_;
  vector<std::string> isocut_;
  edm::InputTag muonLabel_;
  PatMuonSelector   muonIdSelector_;
  PatMuonIsolationSelector muonIsoSelector_;
  edm::InputTag beamSpotLabel_;
 
  edm::Handle<edm::View<pat::Muon> > muons_;
  edm::Handle<reco::BeamSpot> beamSpot_;
  TH1F * cutflow;
  //vector<std::string> IdCuts_;
  //string IsoCut_;
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

