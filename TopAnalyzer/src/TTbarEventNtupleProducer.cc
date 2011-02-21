#include "FWCore/Framework/interface/MakerMacros.h"
#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "PFAnalyses/CommonTools/interface/CandidateSelector.h"
#include "PFAnalyses/CommonTools/interface/PatJetIdSelector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"

#include "KoPFA/DataFormats/interface/TTbarEvent.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "KoPFA/TopAnalyzer/interface/MaosTTbar.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

using namespace std;
using namespace edm;
using namespace reco;

template <typename Lepton1, typename Lepton2>
class TTbarEventNtupleProducer : public edm::EDAnalyzer
{
public:
  TTbarEventNtupleProducer(const edm::ParameterSet& pset);
  ~TTbarEventNtupleProducer();
  void beginJob();
  void endJob() {};
  void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);

private:
  edm::InputTag genParticleLabel_;
  edm::InputTag lepton1Label_, lepton2Label_;
  edm::InputTag metLabel_;
  edm::InputTag jetLabel_;

  PatJetIdSelector looseJetIdSelector_;
  bool doResJec_;
  double minJetIso1_, minJetIso2_;

  bool isLeptonsFromSameCollection_;
 
  Ko::TTbarGenEvent* ttbarGenEvent_;
  Ko::TTbarEvent* ttbarEvent_;
  TTree* tree_;

  FactorizedJetCorrector* resJetCorrector_;
};

template <typename Lepton1, typename Lepton2>
TTbarEventNtupleProducer<Lepton1, Lepton2>::TTbarEventNtupleProducer(const edm::ParameterSet& pset)
{
  genParticleLabel_ = pset.getParameter<edm::InputTag>("genParticle");

  lepton1Label_ = pset.getParameter<edm::InputTag>("lepton1");
  lepton2Label_ = pset.getParameter<edm::InputTag>("lepton2");
  metLabel_ = pset.getParameter<edm::InputTag>("met");
  jetLabel_ = pset.getParameter<edm::InputTag>("jet");

  looseJetIdSelector_.initialize(pset.getParameter<edm::ParameterSet> ("jetId"));
  doResJec_ = pset.getUntrackedParameter<bool>("doResJec", false);
  resJetCorrector_ = 0;
  minJetIso1_ = pset.getParameter<double>("minJetIso1");
  minJetIso2_ = pset.getParameter<double>("minJetIso2");

  isLeptonsFromSameCollection_ = lepton1Label_ == lepton2Label_;

  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("tree", "Tree for Top quark study");

  ttbarEvent_ = new Ko::TTbarEvent;
  ttbarGenEvent_ = new Ko::TTbarGenEvent;
}

template <typename Lepton1, typename Lepton2>
TTbarEventNtupleProducer<Lepton1, Lepton2>::~TTbarEventNtupleProducer()
{
  if ( resJetCorrector_ ) delete resJetCorrector_;
}

template <typename Lepton1, typename Lepton2>
void TTbarEventNtupleProducer<Lepton1, Lepton2>::beginJob()
{
  ttbarEvent_->clear();
  ttbarGenEvent_->clear();

  tree_->Branch("ttbar", "Ko::TTbarEvent", &ttbarEvent_);
  tree_->Branch("ttbarGen", "Ko::TTbarGenEvent", &ttbarGenEvent_);

  // Jet energy correction for 38X
  if ( doResJec_ )
  {
    edm::FileInPath jecFile("CondFormats/JetMETObjects/data/Spring10DataV2_L2L3Residual_AK5PF.txt");
    std::vector<JetCorrectorParameters> jecParams;
    jecParams.push_back(JetCorrectorParameters(jecFile.fullPath()));
    resJetCorrector_ = new FactorizedJetCorrector(jecParams);
  }

}

template <typename Lepton1, typename Lepton2>
void TTbarEventNtupleProducer<Lepton1, Lepton2>::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  // Start from the generator level info
  edm::Handle<reco::GenParticleCollection> genParticleHandle;
  event.getByLabel(genParticleLabel_, genParticleHandle);
  if ( genParticleHandle.isValid() )
  {
    ttbarGenEvent_->clear();
    ttbarGenEvent_->set(genParticleHandle->begin(), genParticleHandle->end());
  }

  // Find pair of leading leptons
  const Lepton1* leadingLepton1 = 0;
  const Lepton2* leadingLepton2 = 0;

  edm::Handle<edm::View<Lepton1> > lepton1Handle;
  edm::Handle<edm::View<Lepton2> > lepton2Handle;
  event.getByLabel(lepton1Label_, lepton1Handle);
  event.getByLabel(lepton2Label_, lepton2Handle);
  for ( typename edm::View<Lepton1>::const_iterator lepton1 = lepton1Handle->begin();
        lepton1 != lepton1Handle->end(); ++lepton1 )
  {
    if ( leadingLepton1 == 0 or
         lepton1->pfCandidateRef()->pt() > leadingLepton1->pfCandidateRef()->pt() )
    {
      leadingLepton1 = &*lepton1;
    }
  }

  if ( !leadingLepton1 ) return;

  for ( typename edm::View<Lepton2>::const_iterator lepton2 = lepton2Handle->begin();
        lepton2 != lepton2Handle->end(); ++lepton2 )
  {
    if ( leadingLepton2 == 0 or
         lepton2->pfCandidateRef()->pt() > leadingLepton2->pfCandidateRef()->pt() )
    {
      if ( isLeptonsFromSameCollection_ and
           leadingLepton1->pt() == lepton2->pt() and
           leadingLepton1->eta() == lepton2->eta() and
           leadingLepton1->phi() == lepton2->phi() ) continue;

      leadingLepton2 = &*lepton2;
    }
  }

  // Skip event if # of leptons < 2
  if ( !leadingLepton1 or !leadingLepton2 ) return;

  ttbarEvent_->clear();
  ttbarEvent_->setEvent(event.id());
  ttbarEvent_->setLepton(leadingLepton1, leadingLepton2);
  const double relIso1 = ttbarEvent_->relPFIso1();
  const double relIso2 = ttbarEvent_->relPFIso2();

  // Read jets
  edm::Handle<pat::JetCollection> jetHandle;
  event.getByLabel(jetLabel_, jetHandle);

  for ( pat::JetCollection::const_iterator jet = jetHandle->begin();
      jet != jetHandle->end(); ++jet )
  {
    if ( fabs(jet->eta()) >= 2.5 ) continue;
    if ( jet->et() < 5 ) continue;

    pat::strbitset looseJetIdSel = looseJetIdSelector_.getBitTemplate();
    if ( !looseJetIdSelector_(*jet, looseJetIdSel) ) continue;

    const double dR1 = deltaR(*jet, *leadingLepton1);
    const double dR2 = deltaR(*jet, *leadingLepton2);

    // jet cleaning
    bool isOverlap = false;
    if ( relIso1 < minJetIso1_ and dR1 < 0.4 ) isOverlap = true;
    if ( relIso2 < minJetIso2_ and dR2 < 0.4 ) isOverlap = true;
    if ( isOverlap ) continue;

    // Jet correction
    double scaleFactor = 1.0;
    if ( doResJec_ )
    {
      resJetCorrector_->setJetEta(jet->eta());
      resJetCorrector_->setJetPt(jet->pt());
      scaleFactor = resJetCorrector_->getCorrection();
    }

    ttbarEvent_->addJet(&*jet, scaleFactor);
  }

  edm::Handle<pat::METCollection> metHandle;
  event.getByLabel(metLabel_, metHandle);
  ttbarEvent_->setMET(&*metHandle->begin());

  ttbarEvent_->update();

  tree_->Fill();
}

typedef TTbarEventNtupleProducer<pat::Muon, pat::Muon> TTbarMuMuEventNtupleProducer;
typedef TTbarEventNtupleProducer<pat::Electron, pat::Muon> TTbarElMuEventNtupleProducer;
typedef TTbarEventNtupleProducer<pat::Electron, pat::Electron> TTbarElElEventNtupleProducer;

DEFINE_FWK_MODULE(TTbarMuMuEventNtupleProducer);
DEFINE_FWK_MODULE(TTbarElMuEventNtupleProducer);
DEFINE_FWK_MODULE(TTbarElElEventNtupleProducer);

