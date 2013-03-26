#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "PhysicsTools/SelectorUtils/interface/SimpleCutBasedElectronIDSelectionFunctor.h"

class KoElectronRefSelector : public edm::EDProducer
{
public:
  KoElectronRefSelector(const edm::ParameterSet& pset);
  ~KoElectronRefSelector();

  void beginJob() {};
  void produce(edm::Event& event, const edm::EventSetup& eventSetup);
  void endJob() {};

private:
  edm::InputTag beamSpotLabel_;
  edm::InputTag electronLabel_;

  // Cut values
  double minPt_, maxEta_, maxDxy_, maxRelIso_;
  double minMVA_;
  std::vector<int> idValues_;
};

KoElectronRefSelector::KoElectronRefSelector(const edm::ParameterSet& pset)
{
  electronLabel_ = pset.getParameter<edm::InputTag>("src");
  
  minPt_ = pset.getUntrackedParameter<double>("minPt", 20);
  maxEta_ = pset.getUntrackedParameter<double>("maxEta", 2.5);
  maxDxy_ = pset.getUntrackedParameter<double>("maxDxy", 0.04);
  maxRelIso_ = pset.getUntrackedParameter<double>("maxRelIso", 0.20);

  minMVA_ = pset.getUntrackedParameter<double>("minMVA", -100);
  std::vector<int> allWP90;
  for ( int i=0; i<=7; ++i ) allWP90.push_back(i);
  idValues_ = pset.getUntrackedParameter<std::vector<int> >("idValues", allWP90);
  
  produces<edm::PtrVector<reco::Candidate> >();
}

KoElectronRefSelector::~KoElectronRefSelector()
{
}

void KoElectronRefSelector::produce(edm::Event& event, const edm::EventSetup& eventSetup)
{
  using namespace std;
  using namespace edm;
  using namespace reco;
  using namespace isodeposit;

  std::auto_ptr<edm::PtrVector<reco::Candidate> > selectedElectrons(new edm::PtrVector<reco::Candidate>);

  edm::Handle<edm::View<pat::Electron> > electronHandle;
  event.getByLabel(electronLabel_, electronHandle);
  if ( !electronHandle.isValid() )
  {
    edm::LogError("KoElectronRefSelector") << "Cannot read electron collection\n";
    return;
  }

  edm::Handle<reco::BeamSpot> beamSpotHandle;
  event.getByLabel(edm::InputTag("offlineBeamSpot"), beamSpotHandle);
  if ( !beamSpotHandle.isValid() )
  {
    edm::LogError("KoElectronRefSelector") << "Cannot read beamSpot handle\n";
    return;
  }

  IsoDeposit::AbsVetos vetos_ch;
  IsoDeposit::AbsVetos vetos_nh;
  IsoDeposit::AbsVetos vetos_ph;

  for ( edm::View<pat::Electron>::const_iterator electron = electronHandle->begin();
        electron != electronHandle->end(); ++electron )
  {
    if ( minPt_ > electron->pfCandidateRef()->pt() ) continue;
    if ( maxEta_ < std::fabs(electron->pfCandidateRef()->eta()) ) continue;

    if ( electron->mva() < minMVA_ ) continue;

    bool passingEleId = false;
    const int eleId = electron->electronID("simpleEleId90relIso");
    for ( std::vector<int>::const_iterator idVal = idValues_.begin();
          idVal != idValues_.end(); ++idVal )
    {
      if ( eleId == *idVal )
      {
        passingEleId = true;
        break;
      }
    }
    if ( !passingEleId ) continue;

    const double dxy = fabs(electron->gsfTrack()->dxy(beamSpotHandle->position()));
    if ( dxy > maxDxy_ ) continue;

    const double chIso = electron->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first;
    const double nhIso = electron->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first;
    const double phIso = electron->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first;

    const double ptlRelIso = (chIso+nhIso+phIso)/electron->pfCandidateRef()->pt();

    const double tkIso = electron->trackIso();
    const double ecIso = electron->ecalIso();
    const double hcIso = electron->hcalIso();

    const double detRelIso = (tkIso+ecIso+hcIso)/electron->pt();

    if ( ptlRelIso > maxRelIso_ ) continue;

    const unsigned int electronIndex = electron - electronHandle->begin();
    selectedElectrons->push_back(electronHandle->ptrAt(electronIndex));
  }

  event.put(selectedElectrons);
}

DEFINE_FWK_MODULE(KoElectronRefSelector);

