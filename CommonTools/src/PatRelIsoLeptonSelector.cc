#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
//#include "EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h" 
#include "Muon/MuonAnalysisTools/interface/MuonEffectiveArea.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"


#include <memory>
#include <vector>
#include <string>

using namespace reco;


template<typename Lepton>
class PatRelIsoLeptonSelector : public edm::EDFilter
{
public:
  PatRelIsoLeptonSelector(const edm::ParameterSet& pset);
  ~PatRelIsoLeptonSelector() {};

  bool filter(edm::Event& event, const edm::EventSetup& eventSetup);

private:
  double computeDz(const pat::Electron& electron, const reco::Vertex& pv);
  double computeDz(const pat::Muon& muon, const reco::Vertex& pv);
  void makeIsoVeto(const pat::Electron& electron, reco::IsoDeposit::AbsVetos& vetos_ch, reco::IsoDeposit::AbsVetos& vetos_nh, reco::IsoDeposit::AbsVetos& vetos_ph);
  void makeIsoVeto(const pat::Muon& muon, reco::IsoDeposit::AbsVetos& vetos_ch, reco::IsoDeposit::AbsVetos& vetos_nh, reco::IsoDeposit::AbsVetos& vetos_ph);
  double getEffectiveArea(const pat::Electron& electron);
  double getEffectiveArea(const pat::Muon& muon);

  MuonEffectiveArea::MuonEffectiveAreaType muonEAType_;
  MuonEffectiveArea::MuonEffectiveAreaTarget muonEATarget_;
  ElectronEffectiveArea::ElectronEffectiveAreaType electronEAType_;
  ElectronEffectiveArea::ElectronEffectiveAreaTarget electronEATarget_;

private:
  edm::InputTag rhoLabel_;
  edm::InputTag leptonLabel_;
  edm::InputTag vertexLabel_;
  double dz_;
  StringCutObjectSelector<Lepton, true>* select_;
  unsigned int minNumber_, maxNumber_;

  bool isMC_;
  double coneSize_;
};

template<typename Lepton>
PatRelIsoLeptonSelector<Lepton>::PatRelIsoLeptonSelector(const edm::ParameterSet& pset)
{
  // isMC_ = true as a default, determine it in the event loop.
  // Changing this default value of this flag should be done carefully,
  // modification can be needed in #ISMC_DEPENDENT_PART#
  isMC_ = true; 

  rhoLabel_ = pset.getParameter<edm::InputTag>("rho");
  leptonLabel_ = pset.getParameter<edm::InputTag>("src");
  std::string cut = pset.getParameter<std::string>("cut");
  vertexLabel_ =  pset.getUntrackedParameter<edm::InputTag>("vertexLabel");
  dz_ = pset.getUntrackedParameter<double>("dz",999);
  select_ = new StringCutObjectSelector<Lepton, true>(cut);
  minNumber_ = pset.getParameter<unsigned int>("minNumber");
  maxNumber_ = pset.getParameter<unsigned int>("maxNumber");

  coneSize_ = pset.getParameter<double>("coneSize");
  if ( coneSize_ == 0.3 )
  {
    electronEAType_ = ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03;
    muonEAType_ = MuonEffectiveArea::kMuGammaAndNeutralHadronIso03;
  }
  else
  {
    electronEAType_ = ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04;
    muonEAType_ = MuonEffectiveArea::kMuGammaAndNeutralHadronIso04;
  }

  // Set EA target for real data as a default value
  // the module will update this value if input is MC in the event loop.
  // #ISMC_DEPENDENT_PART#
  electronEATarget_ = ElectronEffectiveArea::kEleEAData2012; // Use Data2012 EA
  muonEATarget_ = MuonEffectiveArea::kMuEAData2012; // Use Data2012 EA
  // end of #ISMC_DEPENDENT_PART#

  produces<std::vector<Lepton> >();
}

template<typename Lepton>
bool PatRelIsoLeptonSelector<Lepton>::filter(edm::Event& event, const edm::EventSetup& eventSetup)
{
  // isMC_ is true by default, first decided here.
  if ( isMC_ and event.isRealData() )
  {
    // Give correct MC flag in case of conflict
    isMC_ = false;

    // #ISMC_DEPENDENT_PART#
    electronEATarget_ = ElectronEffectiveArea::kEleEAData2012;
    muonEATarget_ = MuonEffectiveArea::kMuEAData2012;
    // end of #ISMC_DEPENDENT_PART#
  }

  edm::Handle<edm::View<Lepton> > leptonHandle;
  event.getByLabel(leptonLabel_, leptonHandle);

  edm::Handle<double> rhoHandle;
  event.getByLabel(rhoLabel_, rhoHandle);
  const double rho = *(rhoHandle.product());

  std::auto_ptr<std::vector<Lepton> > selectedLeptons(new std::vector<Lepton>());

  edm::Handle<reco::VertexCollection> recVtxs_;
  event.getByLabel(vertexLabel_,recVtxs_);

  int nvertex = 0;
  std::auto_ptr<std::vector<reco::Vertex> > goodOfflinePrimaryVertices(new std::vector<reco::Vertex>());
  for(unsigned int i=0; i < recVtxs_->size();  ++i){
    reco::Vertex v = recVtxs_->at(i);
    if (!(v.isFake()) && (v.ndof()>4) && (fabs(v.z())<=24.0) && (v.position().Rho()<=2.0) ) {
      goodOfflinePrimaryVertices->push_back((*recVtxs_)[i]);
      nvertex++;
    }
  }

  if( nvertex == 0 ) return false;
  reco::Vertex pv = goodOfflinePrimaryVertices->at(0);

  for ( int i=0, n=leptonHandle->size(); i<n; ++i )
  {
    const Lepton& srcLepton = leptonHandle->at(i);
    if ( !(*select_)(srcLepton) ) continue;
    const double dz = computeDz(srcLepton, pv);
    if ( dz > dz_ ) continue;
  
    reco::IsoDeposit::AbsVetos vetos_ch, vetos_nh, vetos_ph;
    makeIsoVeto(srcLepton, vetos_ch, vetos_nh, vetos_ph);
    const double effArea = getEffectiveArea(srcLepton);

    const double chIso = srcLepton.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(coneSize_, vetos_ch).first;
    const double pcIso = srcLepton.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(coneSize_, vetos_ch).first;
    const double nhIso = srcLepton.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(coneSize_, vetos_nh).first;
    const double phIso = srcLepton.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(coneSize_, vetos_ph).first;

    const float relIso = (chIso+nhIso+phIso)/srcLepton.pt();
    const float relIsoDbeta = (chIso+max(0., nhIso+phIso-0.5*pcIso))/srcLepton.pt();
    const float relIsoRho = (chIso+max(0., nhIso+phIso-effArea*rho))/srcLepton.pt();

    // Build lepton
    Lepton lepton(srcLepton);

    lepton.setUserIso(relIso, 0);
    lepton.setUserIso(relIsoDbeta, 1);
    lepton.setUserIso(relIsoRho, 2);

    lepton.addUserFloat("dz", dz);

    selectedLeptons->push_back(lepton);
  }

  const unsigned int nLepton = selectedLeptons->size();

  event.put(selectedLeptons);

  return (nLepton >= minNumber_ and nLepton <= maxNumber_);
}

template<typename Lepton>
void PatRelIsoLeptonSelector<Lepton>::makeIsoVeto(const pat::Electron& electron, reco::IsoDeposit::AbsVetos& vetos_ch, reco::IsoDeposit::AbsVetos& vetos_nh, reco::IsoDeposit::AbsVetos& vetos_ph)
{
  reco::isodeposit::Direction dir(electron.superCluster()->eta(), electron.superCluster()->phi());

  if ( abs(electron.superCluster()->eta()) > 1.479 )
  {
    vetos_ch.push_back(new reco::isodeposit::ConeVeto(dir, 0.015));
    vetos_ph.push_back(new reco::isodeposit::ConeVeto(dir, 0.080));
  }
}

template<typename Lepton>
void PatRelIsoLeptonSelector<Lepton>::makeIsoVeto(const pat::Muon& muon, reco::IsoDeposit::AbsVetos& vetos_ch, reco::IsoDeposit::AbsVetos& vetos_nh, reco::IsoDeposit::AbsVetos& vetos_ph)
{
  vetos_nh.push_back(new reco::isodeposit::ThresholdVeto(0.5));
  vetos_ph.push_back(new reco::isodeposit::ThresholdVeto(0.5));
}

template<typename Lepton>
double PatRelIsoLeptonSelector<Lepton>::getEffectiveArea(const pat::Electron& electron)
{
  return ElectronEffectiveArea::GetElectronEffectiveArea(electronEAType_, electron.superCluster()->eta(), electronEATarget_);
}

template<typename Lepton>
double PatRelIsoLeptonSelector<Lepton>::getEffectiveArea(const pat::Muon& muon)
{
  return MuonEffectiveArea::GetMuonEffectiveArea(muonEAType_, muon.eta(), muonEATarget_);
}

template<typename Lepton>
double PatRelIsoLeptonSelector<Lepton>::computeDz(const pat::Electron& electron, const reco::Vertex& pv)
{
  return abs(electron.gsfTrack()->dz(pv.position()));
}

template<typename Lepton>
double PatRelIsoLeptonSelector<Lepton>::computeDz(const pat::Muon& muon, const reco::Vertex& pv)
{
  return abs(muon.innerTrack()->dz(pv.position()));
}

#include "FWCore/Framework/interface/MakerMacros.h"

typedef PatRelIsoLeptonSelector<pat::Muon> PatRelIsoMuonSelector;
typedef PatRelIsoLeptonSelector<pat::Electron> PatRelIsoElectronSelector;

DEFINE_FWK_MODULE(PatRelIsoMuonSelector);
DEFINE_FWK_MODULE(PatRelIsoElectronSelector);
