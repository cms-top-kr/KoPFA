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
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include "KoPFA/DataFormats/interface/TTbarEvent.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "KoPFA/DataFormats/interface/Maos.h"

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
  double minJetIso1_, minJetIso2_;

  bool isLeptonsFromSameCollection_;
 
  Ko::TTbarGenEvent* ttbarGenEvent_;
  Ko::TTbarEvent* ttbarEvent_;
  TTree* tree_;

  bool doResJec_;
  FactorizedJetCorrector* resJetCorrector_;
  JetCorrectionUncertainty* jecUncert_;
  std::string resJecFileName_;
  std::string jecUncertFileName_;

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
  resJetCorrector_ = 0;
  jecUncert_ = 0;
  doResJec_ = pset.getUntrackedParameter<bool>("doResJec");
  resJecFileName_ = pset.getUntrackedParameter<std::string>("resJecFileName");
  jecUncertFileName_ = pset.getUntrackedParameter<std::string>("jecUncertFileName");
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
  if ( jecUncert_ ) delete jecUncert_;
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
    edm::FileInPath jecFile(resJecFileName_);
    std::vector<JetCorrectorParameters> jecParams;
    jecParams.push_back(JetCorrectorParameters(jecFile.fullPath()));
    resJetCorrector_ = new FactorizedJetCorrector(jecParams);
  }

  edm::FileInPath jecUncFile(jecUncertFileName_);
  jecUncert_ = new JetCorrectionUncertainty(jecUncFile.fullPath());

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
  edm::Handle<edm::View<Lepton1> > lepton1Handle;
  edm::Handle<edm::View<Lepton2> > lepton2Handle;
  event.getByLabel(lepton1Label_, lepton1Handle);
  event.getByLabel(lepton2Label_, lepton2Handle);

  double leadingLepton1Pt = 0;
  int leadingLepton1Index = -1;
  const int lepton1Size(lepton1Handle->size());
  for ( int i = 0; i < lepton1Size; ++i )
  {
    const Lepton1& lepton1 = lepton1Handle->at(i);
    const double lepton1Pt = lepton1.pfCandidateRef()->pt();

    if ( lepton1Pt > leadingLepton1Pt )
    {
      leadingLepton1Index = i;
      leadingLepton1Pt = lepton1Pt;
    }
  }

  if ( leadingLepton1Index < 0 ) return;

  double leadingLepton2Pt = 0;
  int leadingLepton2Index = -1;
  const int lepton2Size(lepton2Handle->size());
  for ( int i = 0; i < lepton2Size; ++i )
  {
    // Check duplication if leptons are from the same collection
    if ( isLeptonsFromSameCollection_ and leadingLepton1Index == i ) continue;

    const Lepton2& lepton2 = lepton2Handle->at(i);
    const double lepton2Pt = lepton2.pfCandidateRef()->pt();

    if ( lepton2Pt > leadingLepton2Pt )
    {
      leadingLepton2Index = i;
      leadingLepton2Pt = lepton2Pt;
    }
  }

  // Skip event if # of leptons < 2
  if ( leadingLepton2Index < 0 ) return;

  const Lepton1& leadingLepton1 = lepton1Handle->at(leadingLepton1Index);
  const Lepton2& leadingLepton2 = lepton2Handle->at(leadingLepton2Index);

  ttbarEvent_->clear();
  ttbarEvent_->setEvent(event.id());
  ttbarEvent_->setLepton(&leadingLepton1, &leadingLepton2);
  const double relIso1 = ttbarEvent_->relPFIso1();
  const double relIso2 = ttbarEvent_->relPFIso2();

  // Read MET
  edm::Handle<pat::METCollection> metHandle;
  event.getByLabel(metLabel_, metHandle);
  const pat::MET& met = *(metHandle->begin());

  double metX = met.px(), metY = met.py();
  double metXUpper = metX, metXLower = metX;
  double metYUpper = metY, metYLower = metY;

  ttbarEvent_->setMET(metX, metY);

  // Read jets
  edm::Handle<pat::JetCollection> jetHandle;
  event.getByLabel(jetLabel_, jetHandle);

  for ( pat::JetCollection::const_iterator jet = jetHandle->begin();
      jet != jetHandle->end(); ++jet )
  {
    // Jet and MET correction
    const double jetEta = jet->eta();
    const double jetPt = jet->pt();

    double scaleFactor = 1.0;
    if ( doResJec_ )
    {
      resJetCorrector_->setJetEta(jetEta);
      resJetCorrector_->setJetPt(jetPt);
      scaleFactor = resJetCorrector_->getCorrection();
    }
    const reco::Candidate::LorentzVector corrJetLVec = jet->p4()*scaleFactor;
    const double corrJetPt = corrJetLVec.pt();

    jecUncert_->setJetEta(jetEta);
    jecUncert_->setJetPt(corrJetPt);

    metX += jet->px()*scaleFactor;
    metY += jet->py()*scaleFactor;

    // Calculate jec error sources
    double jecErr2 = 0;
    const double jecErrSelf = jecUncert_->getUncertainty(true);
    jecErr2 += jecErrSelf* jecErrSelf;
    jecErr2 += 0.015*0.015; // Release differences and calibration changes
    jecErr2 += (0.2*0.8*2.2)*(0.2*0.8*2.2)/corrJetPt/corrJetPt; // Pileup
    // BJet uncertainty
    if ( corrJetPt > 50 && corrJetPt < 200 && fabs(jetEta < 2.0) ) jecErr2 += 0.02*0.02;
    else jecErr2 += 0.03*0.03;
    const double jecErr = sqrt(jecErr2);

    const double metCorrFactor = scaleFactor*jecErr;
    metXUpper -= jet->px()*metCorrFactor;
    metXLower += jet->px()*metCorrFactor;
    metYUpper -= jet->py()*metCorrFactor;
    metYLower += jet->py()*metCorrFactor;

    // Cut on jet quality
    if ( fabs(jet->eta()) >= 2.5 ) continue;

    pat::strbitset looseJetIdSel = looseJetIdSelector_.getBitTemplate();
    if ( !looseJetIdSelector_(*jet, looseJetIdSel) ) continue;

    const double dR1 = deltaR(*jet, leadingLepton1);
    const double dR2 = deltaR(*jet, leadingLepton2);

    // jet cleaning
    bool isOverlap = false;
    if ( relIso1 < minJetIso1_ and dR1 < 0.4 ) isOverlap = true;
    if ( relIso2 < minJetIso2_ and dR2 < 0.4 ) isOverlap = true;
    if ( isOverlap ) continue;

    ttbarEvent_->addJet(&*jet);
    ttbarEvent_->addCorrJet(corrJetLVec, jecErr);
  }

  ttbarEvent_->setCorrMET(metX, metXLower, metXUpper, metY, metYLower, metYUpper);

  ttbarEvent_->update();

  tree_->Fill();
}

typedef TTbarEventNtupleProducer<pat::Muon, pat::Muon> TTbarMuMuEventNtupleProducer;
typedef TTbarEventNtupleProducer<pat::Electron, pat::Muon> TTbarElMuEventNtupleProducer;
typedef TTbarEventNtupleProducer<pat::Electron, pat::Electron> TTbarElElEventNtupleProducer;

DEFINE_FWK_MODULE(TTbarMuMuEventNtupleProducer);
DEFINE_FWK_MODULE(TTbarElMuEventNtupleProducer);
DEFINE_FWK_MODULE(TTbarElElEventNtupleProducer);

