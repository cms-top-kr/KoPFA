#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "AnalysisDataFormats/CMGTools/interface/BaseJet.h"
#include "AnalysisDataFormats/CMGTools/interface/PFJet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Common/interface/View.h"

#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "DataFormats/Math/interface/deltaR.h"

#include <memory>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "AnalysisDataFormats/CMGTools/interface/GenericTypes.h"
#include <TH1F.h>
#include <TH2F.h>

using namespace edm;
using namespace std;

class CMGCleanJetSelector : public edm::EDFilter
{
public:
  CMGCleanJetSelector(const edm::ParameterSet& pset);
  ~CMGCleanJetSelector() {};

private:
  void beginJob() {};
  bool filter(edm::Event& event, const edm::EventSetup& eventSetup);
  void endJob() {};

  bool doFilter_;
  double overlapDeltaR_;
  unsigned int minNumber_;
  unsigned int maxNumber_;

  edm::InputTag jetLabel_;
  std::vector<edm::InputTag> overlapCandLabels_;

  StringCutObjectSelector<cmg::PFJet, true>* isGoodJet_;
  double minPt_, maxEta_;

  int cleanMethodId_;

private:
  bool debug_;

  TH1F* hNPFJet_;
  TH1F* hNGenJet_;
  TH2F* hNGenJetVsNPFJet_;

};

CMGCleanJetSelector::CMGCleanJetSelector(const edm::ParameterSet& pset)
{
  doFilter_ = pset.getParameter<bool>("doFilter");
  debug_ = pset.getUntrackedParameter<bool>("debug",false);

  const std::string cleanMethodName = pset.getUntrackedParameter<std::string>("cleanMethod","subtract");
  if ( cleanMethodName == "subtract" ) cleanMethodId_ = 1;
  else if ( cleanMethodName == "subtractAndRestore" ) cleanMethodId_ = 2;
  else cleanMethodId_ = 0;

  jetLabel_ = pset.getParameter<edm::InputTag>("src");
  std::string jetCut = pset.getParameter<std::string>("cut");
  isGoodJet_ = new StringCutObjectSelector<cmg::PFJet, true>(jetCut);
  minPt_ = pset.getUntrackedParameter<double>("minPt", 30);
  maxEta_ = pset.getUntrackedParameter<double>("maxEta", 2.5);

  overlapDeltaR_ = pset.getParameter<double>("overlapDeltaR");
  overlapCandLabels_ = pset.getParameter<std::vector<edm::InputTag> >("overlapCands");

  minNumber_ = pset.getParameter<unsigned int>("minNumber");
  maxNumber_ = pset.getParameter<unsigned int>("maxNumber");

  produces<std::vector<cmg::PFJet> >("");

  if ( debug_ )
  {
    edm::Service<TFileService> fs;
    hNPFJet_ = fs->make<TH1F>("hNPFJet", "nPFJet;Number of PF Jet;Events", 10, 0, 10);
    hNGenJet_ = fs->make<TH1F>("hNGenJet", "nGenJet;Number of Gen Jet;Events", 10, 0, 10);
    hNGenJetVsNPFJet_ = fs->make<TH2F>("hNGenJetVsNPFJet", "nGenJet vs nPFJet;Number of Gen Jet;Number of PF Jet", 10, 0, 10, 10, 0, 10);
  }
}

bool CMGCleanJetSelector::filter(edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<std::vector<cmg::PFJet> > jetHandle;
  event.getByLabel(jetLabel_, jetHandle);

  std::auto_ptr<std::vector<cmg::PFJet> > cleanJets(new std::vector<cmg::PFJet>());

  std::vector<const reco::Candidate*> overlapCands;
  for ( int iLabel=0, nLabel=overlapCandLabels_.size(); iLabel<nLabel; ++iLabel )
  {
    edm::Handle<edm::View<reco::Candidate> > overlapCandHandle;
    event.getByLabel(overlapCandLabels_.at(iLabel), overlapCandHandle);

    //if ( !overlapCandHandle.isValid() ) continue;

    for ( int i=0, n=overlapCandHandle->size(); i<n; ++i )
    {
      overlapCands.push_back(&(overlapCandHandle->at(i)));
    }
  }

  for ( int i=0, n=jetHandle->size(); i<n; ++i )
  {
    cmg::PFJet jet = jetHandle->at(i);

    if ( !(*isGoodJet_)(jet) ) continue;

    reco::Candidate::LorentzVector jetP4 = jet.p4();
    bool isOverlap = false;
    for ( int j=0, m=overlapCands.size(); j<m; ++j )
    {
      if ( deltaR(jet.p4(), overlapCands.at(j)->p4()) < overlapDeltaR_ )
      {
        isOverlap = true;
        if ( cleanMethodId_ == 0 ) break;
        else if ( cleanMethodId_ == 1 or cleanMethodId_ == 2 ) jetP4 -= overlapCands.at(j)->p4();
      }
    }

    if ( isOverlap )
    {
      if ( cleanMethodId_ == 0 ) continue;
      else if ( cleanMethodId_ == 1 or cleanMethodId_ == 2 )
      {
        if ( jetP4.pt() < minPt_ ) continue;
        if ( abs(jetP4.eta()) > maxEta_ ) continue;
      }
    }
    
    if ( cleanMethodId_ == 1 ) jet.setP4(jetP4);

    cleanJets->push_back(jet);
  }

  const unsigned int nCleanJet = cleanJets->size();
  std::sort(cleanJets->begin(), cleanJets->end());

  event.put(cleanJets);

  if ( debug_ and !event.isRealData() )
  {
    edm::Handle<std::vector<cmg::GenJet> > genJetHandle;
    event.getByLabel(edm::InputTag("genJetSel"), genJetHandle);

    edm::Handle<std::vector<reco::GenParticle> > genLeptonHandle;
    event.getByLabel(edm::InputTag("genLeptons"), genLeptonHandle);

    int nGenJet = 0;
    for ( int i=0, n=genJetHandle->size(); i<n; ++i )
    {
      const cmg::GenJet& genJet = genJetHandle->at(i);
      if ( genJet.pt() < minPt_ or abs(genJet.eta()) > maxEta_ ) continue;
      const std::vector<const reco::GenParticle*> genConstituents = genJet.sourcePtr()->get()->getGenConstituents();
      if ( genConstituents.size() <= 1 ) continue;
      bool isOverlap = false;
      for ( int j=0, m=genConstituents.size(); j<m; ++j )
      {
        const reco::Candidate* p = genConstituents.at(j);
        if ( abs(p->pdgId()) != 11 and abs(p->pdgId()) != 13 ) continue;

        while ( (p = p->mother()) != 0 )
        {
          if ( p->status() != 3 ) continue;
          if ( abs(p->pdgId()) == 11 or abs(p->pdgId()) == 13 )
          {
            isOverlap = true;
            break;
          }
        }
      }
      if ( isOverlap ) continue;
      
/*
      for ( int j=0, m=genLeptonHandle->size(); j<m; ++j )
      {
        const reco::GenParticle& genLepton = genLeptonHandle->at(j);
        if ( deltaR(genJet, genLepton) > 0.05 ) continue;
        //if ( abs(genJet.pt()-genLepton.pt())/genJet.pt() < 0.1 ) continue;
        //cout << genJet.pt() << "   " << genLepton.pt() << " " << deltaR(genJet, genLepton) << endl;
        isOverlap = true;
        break;
      }
*/
      ++nGenJet;
    }
    hNPFJet_->Fill(nCleanJet);
    hNGenJet_->Fill(nGenJet);
    hNGenJetVsNPFJet_->Fill(nGenJet, nCleanJet);
  }

  if ( !doFilter_ ) return true;
  else if ( nCleanJet >= minNumber_ and nCleanJet <= maxNumber_ ) return true;

  return false;
}

DEFINE_FWK_MODULE(CMGCleanJetSelector);
