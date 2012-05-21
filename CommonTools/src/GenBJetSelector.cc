#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "TMath.h"

#include <memory>
#include <vector>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"

using namespace std;
using namespace edm;
using namespace reco;

class GenBJetSelector : public edm::EDProducer
{
public:
  GenBJetSelector(const edm::ParameterSet& pset);
  ~GenBJetSelector() {};

  virtual void beginJob();
  virtual void endJob() {};
  virtual void produce(edm::Event& event, const edm::EventSetup& eventSetup);

private:
  bool isBHadron(const int pdgId);
  bool isOverlap(const std::vector<const reco::GenParticle*>& pColl1,
                 const std::vector<const reco::GenParticle*>& pColl2,
                 int& nMatch);
  void collectStableDaughters(const reco::GenParticle* p, std::vector<const reco::GenParticle*>& stables);

private:
  edm::InputTag genParticleLabel_;
  edm::InputTag genJetLabel_;

  bool matchByBquarkDeltaR_;
  bool matchByBHadronDeltaR_;
  bool matchByBquarkOverlap_;
  bool matchByBHadronOverlap_;
  bool matchByBquarkFrac_;
  bool matchByBHadronFrac_;

  double cut_maxDeltaR_;
  double cut_maxMatchDeltaR_;
  int cut_minNMatchBquark_;
  int cut_minNMatchBHadron_;
  double cut_minFracBquark_;
  double cut_minFracBHadron_;

  bool doHist_;

  TH1F* hDPt_BquarkDR_;
  TH1F* hDPt_BHadronDR_;
  TH1F* hDPt_BquarkOverlap_;
  TH1F* hDPt_BHadronOverlap_;
  TH1F* hDPt_BquarkFrac_;
  TH1F* hDPt_BHadronFrac_;

  TH1F* hDR_BquarkDR_;
  TH1F* hDR_BHadronDR_;
  TH1F* hDR_BquarkOverlap_;
  TH1F* hDR_BHadronOverlap_;
  TH1F* hDR_BquarkFrac_;
  TH1F* hDR_BHadronFrac_;

  TH1F* hN_BquarkDR_;
  TH1F* hN_BHadronDR_;
  TH1F* hN_BquarkOverlap_;
  TH1F* hN_BHadronOverlap_;
  TH1F* hN_BquarkFrac_;
  TH1F* hN_BHadronFrac_;

  TH1F* hNFrac_BquarkDR_;
  TH1F* hNFrac_BHadronDR_;
  TH1F* hNFrac_BquarkOverlap_;
  TH1F* hNFrac_BHadronOverlap_;
  TH1F* hNFrac_BquarkFrac_;
  TH1F* hNFrac_BHadronFrac_;

  TH2F* hDRVsDPt_BquarkDR_;
  TH2F* hDRVsDPt_BHadronDR_;
  TH2F* hNVsDPt_BquarkOverlap_;
  TH2F* hNVsDPt_BHadronOverlap_;
  TH2F* hNVsDPt_BquarkFrac_;
  TH2F* hNVsDPt_BHadronFrac_;
  TH2F* hNVsDR_BquarkOverlap_;
  TH2F* hNVsDR_BHadronOverlap_;
  TH2F* hNVsDR_BquarkFrac_;
  TH2F* hNVsDR_BHadronFrac_;

  TH2F* hNFracVsDPt_BquarkOverlap_;
  TH2F* hNFracVsDPt_BHadronOverlap_;
  TH2F* hNFracVsDPt_BquarkFrac_;
  TH2F* hNFracVsDPt_BHadronFrac_;

  TH2F* hNFracVsDR_BquarkOverlap_;
  TH2F* hNFracVsDR_BHadronOverlap_;
  TH2F* hNFracVsDR_BquarkFrac_;
  TH2F* hNFracVsDR_BHadronFrac_;

  
};

GenBJetSelector::GenBJetSelector(const edm::ParameterSet& pset)
{
  genParticleLabel_ = pset.getParameter<edm::InputTag>("genParticle");
  genJetLabel_ = pset.getParameter<edm::InputTag>("genJet");

  // Matching algorithms
  typedef std::vector<std::string> VString;
  const VString matchAlgos = pset.getParameter<VString>("matchAlgos");
  matchByBquarkDeltaR_ = matchByBHadronDeltaR_ = false;
  matchByBquarkOverlap_ = matchByBHadronOverlap_ = false;
  matchByBquarkFrac_ = matchByBHadronFrac_ = false;
  for ( int i=0, n=matchAlgos.size(); i<n; ++i )
  {
    const std::string& algoName = matchAlgos[i];

    if      ( algoName == "BquarkDeltaR"   ) matchByBquarkDeltaR_   = true;
    else if ( algoName == "BHadronDeltaR"  ) matchByBHadronDeltaR_  = true;
    else if ( algoName == "BquarkOverlap"  ) matchByBquarkOverlap_  = true;
    else if ( algoName == "BHadronOverlap" ) matchByBHadronOverlap_ = true;
    else if ( algoName == "BquarkFrac"     ) matchByBquarkFrac_     = true;
    else if ( algoName == "BHadronFrac"    ) matchByBHadronFrac_    = true;
  }

  if ( matchByBquarkDeltaR_ or matchByBHadronDeltaR_ )
  {
    cut_maxDeltaR_ = pset.getParameter<double>("maxDeltaR");
  }

  if ( matchByBquarkOverlap_ or matchByBHadronOverlap_ )
  {
    cut_maxMatchDeltaR_ = pset.getParameter<double>("maxMatchDeltaR");
    cut_minNMatchBquark_ = cut_minNMatchBHadron_ = 0;
    if ( matchByBquarkOverlap_ )
    {
      cut_minNMatchBquark_ = pset.getParameter<int>("minNMatchBquark");
    }
    if ( matchByBHadronOverlap_ )
    {
      cut_minNMatchBHadron_ = pset.getParameter<int>("minNMatchBHadron");
    }
  }

  if ( matchByBquarkFrac_ or matchByBHadronFrac_ )
  {
    cut_maxMatchDeltaR_ = pset.getParameter<double>("maxMatchDeltaR");
    cut_minFracBquark_ = cut_minFracBHadron_ = 0;
    if ( matchByBquarkFrac_ )
    {
      cut_minFracBquark_ = pset.getParameter<double>("minFracBquark");
    }
    if ( matchByBHadronFrac_ )
    {
      cut_minFracBHadron_ = pset.getParameter<double>("minFracBHadron");
    }
  }

  produces<reco::GenJetCollection>("");

  doHist_ = pset.getUntrackedParameter<bool>("doHist", false);
}

void GenBJetSelector::beginJob()
{
  hDPt_BquarkDR_ = hDPt_BHadronDR_ = 0;
  hDPt_BquarkOverlap_ = hDPt_BHadronOverlap_ = 0;
  hDPt_BquarkFrac_ = hDPt_BHadronFrac_ = 0;

  hDR_BquarkDR_ = hDR_BHadronDR_ = 0;
  hDR_BquarkOverlap_ = hDR_BHadronOverlap_ = 0;
  hDR_BquarkFrac_ = hDR_BHadronFrac_ = 0;

  hN_BquarkDR_ = hN_BHadronDR_ = 0;
  hN_BquarkOverlap_ = hN_BHadronOverlap_ = 0;
  hN_BquarkFrac_ = hN_BHadronFrac_ = 0;

  hNFrac_BquarkDR_ = hNFrac_BHadronDR_ = 0;
  hNFrac_BquarkOverlap_ = hNFrac_BHadronOverlap_ = 0;
  hNFrac_BquarkFrac_ = hNFrac_BHadronFrac_ = 0;

  hDRVsDPt_BquarkDR_ = hDRVsDPt_BHadronDR_ = 0;
  hNVsDPt_BquarkOverlap_ = hNVsDPt_BHadronOverlap_ = 0;
  hNVsDPt_BquarkFrac_ = hNVsDPt_BHadronFrac_ = 0;
  hNVsDR_BquarkOverlap_ = hNVsDR_BHadronOverlap_ = 0;
  hNVsDR_BquarkFrac_ = hNVsDR_BHadronFrac_ = 0;
  
  hNFracVsDPt_BquarkOverlap_ = hNFracVsDPt_BHadronOverlap_ = 0;
  hNFracVsDPt_BquarkFrac_ = hNFracVsDPt_BHadronFrac_ = 0;
  hNFracVsDR_BquarkOverlap_ = hNFracVsDR_BHadronOverlap_ = 0;
  hNFracVsDR_BquarkFrac_ = hNFracVsDR_BHadronFrac_ = 0;

  if ( doHist_ )
  {
    try
    {
      edm::Service<TFileService> fs;

      hDPt_BquarkDR_ = fs->make<TH1F>("hDPt_BquarkDR", "Match by #DeltaR(b quark, Jet);#Deltap_{T} (b-jet) [GeV/c]", 50, -100, 100);
      hDPt_BHadronDR_ = fs->make<TH1F>("hDPt_BHadronDR", "Match by #DeltaR(B hadron, Jet);#Deltap_{T} (b-jet) [GeV/c]", 50, -100, 100);
      hDPt_BquarkOverlap_ = fs->make<TH1F>("hDPt_BquarkOverlap", "Match by overlap(b quark, Jet);#Deltap_{T} (b-jet) [GeV/c]", 50, -100, 100);
      hDPt_BHadronOverlap_ = fs->make<TH1F>("hDPt_BHadronOverlap", "Match by overlap(B hadron, Jet);#Deltap_{T} (b-jet) [GeV/c]", 50, -100, 100);
      hDPt_BquarkFrac_ = fs->make<TH1F>("hDPt_BquarkFrac", "Match by overlap(b quark, Jet);#Deltap_{T} (b-jet) [GeV/c]", 50, -100, 100);
      hDPt_BHadronFrac_ = fs->make<TH1F>("hDPt_BHadronFrac", "Match by overlap(B hadron, Jet);#Deltap_{T} (b-jet) [GeV/c]", 50, -100, 100);

      hDR_BquarkDR_ = fs->make<TH1F>("hDR_BquarkDR", "Match by #DeltaR(b quark, Jet);#DeltaR", 50, 0, 2);
      hDR_BHadronDR_ = fs->make<TH1F>("hDR_BHadronDR", "Match by #DeltaR(B hadron, Jet);#DeltaR", 50, 0, 2);
      hDR_BquarkOverlap_ = fs->make<TH1F>("hDR_BquarkOverlap", "Match by overlap(b quark, Jet);#DeltaR", 50, 0, 2);
      hDR_BHadronOverlap_ = fs->make<TH1F>("hDR_BHadronOverlap", "Match by overlap(B hadron, Jet);#DeltaR", 50, 0, 2);
      hDR_BquarkFrac_ = fs->make<TH1F>("hDR_BquarkFrac", "Match by overlap(b quark, Jet);#DeltaR", 50, 0, 2);
      hDR_BHadronFrac_ = fs->make<TH1F>("hDR_BHadronFrac", "Match by overlap(B hadron, Jet);#DeltaR", 50, 0, 2);

      hN_BquarkDR_ = fs->make<TH1F>("hN_BquarkDR", "Match by #DeltaR(b quark, Jet);Number of overlapping particles", 200, 0, 200);
      hN_BHadronDR_ = fs->make<TH1F>("hN_BHadronDR", "Match by #DeltaR(B hadron, Jet);Number of overlapping particles", 50, 0, 50);
      hN_BquarkOverlap_ = fs->make<TH1F>("hN_BquarkOverlap", "Match by overlap(b quark, Jet);Number of overlapping particles", 200, 0, 200);
      hN_BHadronOverlap_ = fs->make<TH1F>("hN_BHadronOverlap", "Match by overlap(B hadron, Jet);Number of overlapping particles", 50, 0, 50);
      hN_BquarkFrac_ = fs->make<TH1F>("hN_BquarkFrac", "Match by overlap(b quark, Jet);Number of overlapping particles", 200, 0, 200);
      hN_BHadronFrac_ = fs->make<TH1F>("hN_BHadronFrac", "Match by overlap(B hadron, Jet);Number of overlapping particles", 50, 0, 50);

      hNFrac_BquarkDR_ = fs->make<TH1F>("hNFrac_BquarkDR", "Match by #DeltaR(b quark, Jet);Overlap fraction", 50, 0, 1);
      hNFrac_BHadronDR_ = fs->make<TH1F>("hNFrac_BHadronDR", "Match by #DeltaR(B hadron, Jet);Overlap fraction", 50, 0, 1);
      hNFrac_BquarkOverlap_ = fs->make<TH1F>("hNFrac_BquarkOverlap", "Match by overlap(b quark, Jet);Overlap fraction", 50, 0, 1);
      hNFrac_BHadronOverlap_ = fs->make<TH1F>("hNFrac_BHadronOverlap", "Match by overlap(B hadron, Jet);Overlap fraction", 50, 0, 1);
      hNFrac_BquarkFrac_ = fs->make<TH1F>("hNFrac_BquarkFrac", "Match by overlap(b quark, Jet);Overlap fraction", 50, 0, 1);
      hNFrac_BHadronFrac_ = fs->make<TH1F>("hNFrac_BHadronFrac", "Match by overlap(B hadron, Jet);Overlap fraction", 50, 0, 1);

      hDRVsDPt_BquarkDR_ = fs->make<TH2F>("hDRVsDPt_BquarkDR", "Match by #DeltaR(b quark, Jet);#DeltaR;#Deltap_{T} [GeV/c]", 50, 0, 2, 50, -100, 100);
      hDRVsDPt_BHadronDR_ = fs->make<TH2F>("hDRVsDPt_BHadronDR", "Match by #DeltaR(B hadron, Jet);#DeltaR;#Deltap_{T} [GeV/c]", 50, 0, 2, 50, -100, 100);
      hNVsDPt_BquarkOverlap_ = fs->make<TH2F>("hNVsDPt_BquarkOverlap", "Match by overlap(b quark, Jet);Number of overlapping particles;#Deltap_{T} [GeV/c]", 200, 0, 200, 50, -100, 100);
      hNVsDPt_BHadronOverlap_ = fs->make<TH2F>("hNVsDPt_BHadronOverlap", "Match by overlap(b hadron, Jet);Number of overlapping particles;#Deltap_{T} [GeV/c]",50, 0, 50, 50, -100, 100);
      hNVsDPt_BquarkFrac_ = fs->make<TH2F>("hNVsDPt_BquarkFrac", "Match by overlap(b quark, Jet);Number of overlapping particles;#Deltap_{T} [GeV/c]", 200, 0, 200, 50, -100, 100);
      hNVsDPt_BHadronFrac_ = fs->make<TH2F>("hNVsDPt_BHadronFrac", "Match by overlap(b hadron, Jet);Number of overlapping particles;#Deltap_{T} [GeV/c]",50, 0, 50, 50, -100, 100);
      hNVsDR_BquarkOverlap_ = fs->make<TH2F>("hNVsDR_BquarkOverlap", "Match by overlap(b quark, Jet);Number of overlapping particles;#DeltaR", 200, 0, 200, 50, 0, 2);
      hNVsDR_BHadronOverlap_ = fs->make<TH2F>("hNVsDR_BHadronOverlap", "Match by overlap(b hadron, Jet);Number of overlapping particles;#DeltaR", 50, 0, 50, 50, 0, 2);
      hNVsDR_BquarkFrac_ = fs->make<TH2F>("hNVsDR_BquarkFrac", "Match by overlap(b quark, Jet);Number of overlapping particles;#DeltaR", 200, 0, 200, 50, 0, 2);
      hNVsDR_BHadronFrac_ = fs->make<TH2F>("hNVsDR_BHadronFrac", "Match by overlap(b hadron, Jet);Number of overlapping particles;#DeltaR", 50, 0, 50, 50, 0, 2);

      hNFracVsDPt_BquarkOverlap_ = fs->make<TH2F>("hNFracVsDPt_BquarkOverlap", "Match by overlap(b quark, Jet);Overlap fraction;#Deltap_{T} [GeV/c]", 50, 0, 1, 50, -100, 100);
      hNFracVsDPt_BHadronOverlap_ = fs->make<TH2F>("hNFracVsDPt_BHadronOverlap", "Match by overlap(b hadron, Jet);Overlap fraction;#Deltap_{T} [GeV/c]",50, 0, 1, 50, -100, 100);
      hNFracVsDPt_BquarkFrac_ = fs->make<TH2F>("hNFracVsDPt_BquarkFrac", "Match by overlap(b quark, Jet);Overlap fraction;#Deltap_{T} [GeV/c]", 50, 0, 1, 50, -100, 100);
      hNFracVsDPt_BHadronFrac_ = fs->make<TH2F>("hNFracVsDPt_BHadronFrac", "Match by overlap(b hadron, Jet);Overlap fraction;#Deltap_{T} [GeV/c]",50, 0, 1, 50, -100, 100);

      hNFracVsDR_BquarkOverlap_ = fs->make<TH2F>("hNFracVsDR_BquarkOverlap", "Match by overlap(b quark, Jet);Overlap fraction;#DeltaR", 50, 0, 1, 50, 0, 2);
      hNFracVsDR_BHadronOverlap_ = fs->make<TH2F>("hNFracVsDR_BHadronOverlap", "Match by overlap(b hadron, Jet);Overlap fraction;#DeltaR", 50, 0, 1, 50, 0, 2);
      hNFracVsDR_BquarkFrac_ = fs->make<TH2F>("hNFracVsDR_BquarkFrac", "Match by overlap(b quark, Jet);Overlap fraction;#DeltaR", 50, 0, 1, 50, 0, 2);
      hNFracVsDR_BHadronFrac_ = fs->make<TH2F>("hNFracVsDR_BHadronFrac", "Match by overlap(b hadron, Jet);Overlap fraction;#DeltaR", 50, 0, 1, 50, 0, 2);
    }
    catch(...)
    {
      doHist_ = false;
    }
  }
}

void GenBJetSelector::produce(edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<reco::GenParticleCollection> genParticleHandle;
  event.getByLabel(genParticleLabel_, genParticleHandle);

  edm::Handle<reco::GenJetCollection> genJetHandle;
  event.getByLabel(genJetLabel_, genJetHandle);

  // Collect all stables particles, flavor changing b quarks and b hadrons
  std::vector<const reco::GenParticle*> stables;
  std::vector<const reco::GenParticle*> bQuarks;
  std::vector<const reco::GenParticle*> bHadrons;
  for ( int i=0, n=genParticleHandle->size(); i<n; ++i )
  {
    const reco::GenParticle* p = &genParticleHandle->at(i);

    const int absPdgId = abs(p->pdgId());

    if ( p->status() == 1 ) stables.push_back(p);
    else
    {
      if ( absPdgId == 5 )
      {
/*
        // Exclusive selection
        bool isFinal = true;
        for ( int j=0, m=p->numberOfDaughters(); j<m; ++j )
        {
          if ( abs(p->daughter(j)->pdgId()) == absPdgId )
          {
            isFinal = false;
            break;
          }
        }
        if ( isFinal ) bQuarks.push_back(p);
*/

        // Inclusive selection
        bool isFirst = true;
        for ( int j=0, m=p->numberOfMothers(); j<m; ++j )
        {
          if ( abs(p->mother(j)->pdgId()) == absPdgId )
          {
            isFirst = false;
            break;
          }
        }
        if ( isFirst ) bQuarks.push_back(p);
      }
      else if ( isBHadron(absPdgId) )
      {
        // Ignore if it has B hadron mother
        // Thus, take only B* for B* -> B+ gamma decay
        bool isFinal = true;
        for ( int j=0, m=p->numberOfMothers(); j<m; ++j )
        {
          if ( isBHadron(p->mother(j)->pdgId()) )
          {
            isFinal = false;
            break;
          }
        }
        if ( isFinal ) bHadrons.push_back(p);
      }
    }
  }

  // Save list of matched jet's indicies
  // This is needed if user wants to mix different matching algorithms without duplication
  std::set<int> matchedJetsIndex;

  // Loop over genJets and find b quark matching : match by DeltaR(bQuark, genJet)
  if ( matchByBquarkDeltaR_ )
  {
    for ( int i=0, n=bQuarks.size(); i<n; ++i )
    {
      const reco::GenParticle* p = bQuarks[i];

      double minDR = cut_maxDeltaR_;
      int matchedJetIndex = -1;

      for ( int j=0, m=genJetHandle->size(); j<m; ++j )
      {
        const reco::GenJet& jet = genJetHandle->at(j);

        const double dR = deltaR(*p, jet);
        if ( minDR <= dR ) continue;

        minDR = dR;
        matchedJetIndex = j;
      }

      if ( matchedJetIndex >= 0 )
      {
        matchedJetsIndex.insert(matchedJetIndex);
        if ( doHist_ )
        {
          const double dPt = p->pt()-genJetHandle->at(matchedJetIndex).pt();
          hDPt_BquarkDR_->Fill(dPt);
          hDR_BquarkDR_->Fill(minDR);
          hDRVsDPt_BquarkDR_->Fill(minDR, dPt);

          std::vector<const reco::GenParticle*> bDaughters;
          collectStableDaughters(p, bDaughters);

          int nMatchBest = 0;
          isOverlap(genJetHandle->at(matchedJetIndex).getGenConstituents(), bDaughters, nMatchBest);
          hN_BquarkDR_->Fill(nMatchBest);

          const double nFrac = 1.*nMatchBest/bDaughters.size();
          hNFrac_BquarkDR_->Fill(nFrac);
        }
      }
    }
  }

  // Loop over genJets and find b hadron matching : match by DeltaR(bHadron, genJet)
  if ( matchByBHadronDeltaR_ )
  {
    for ( int i=0, n=bHadrons.size(); i<n; ++i )
    {
      const reco::GenParticle* p = bHadrons[i];

      double minDR = cut_maxDeltaR_;
      int matchedJetIndex = -1;

      for ( int j=0, m=genJetHandle->size(); j<m; ++j )
      {
        const reco::GenJet& jet = genJetHandle->at(j);

        const double dR = deltaR(*p, jet);
        if ( minDR <= dR ) continue;

        minDR = dR;
        matchedJetIndex = j;
      }

      if ( matchedJetIndex >= 0 )
      {
        matchedJetsIndex.insert(matchedJetIndex);
        if ( doHist_ )
        {
          const double dPt = p->pt()-genJetHandle->at(matchedJetIndex).pt();
          hDPt_BHadronDR_->Fill(dPt);
          hDR_BHadronDR_->Fill(minDR);
          hDRVsDPt_BHadronDR_->Fill(minDR, dPt);

          std::vector<const reco::GenParticle*> bDaughters;
          collectStableDaughters(p, bDaughters);

          int nMatchBest = 0;
          isOverlap(genJetHandle->at(matchedJetIndex).getGenConstituents(), bDaughters, nMatchBest);
          hN_BHadronDR_->Fill(nMatchBest);

          const double nFrac = 1.*nMatchBest/bDaughters.size();
          hNFrac_BHadronDR_->Fill(nFrac);
        }
      }
    }
  }

  // Loop over genJets and find b quark matching 
  if ( matchByBquarkOverlap_ )
  {
    for ( int i=0, n=bQuarks.size(); i<n; ++i )
    {
      const reco::GenParticle* p = bQuarks[i];
      std::vector<const reco::GenParticle*> bDaughters;
      collectStableDaughters(p, bDaughters);

      double minDR = cut_maxMatchDeltaR_;
      int matchedJetIndex = -1;

      int nMatchBest = 0;
      for ( int j=0, m=genJetHandle->size(); j<m; ++j )
      {
        const reco::GenJet& jet = genJetHandle->at(j);

        const double dR = deltaR(*p, jet);
        if ( dR >= minDR ) continue;
        int nMatch = 0;
        if ( !isOverlap(jet.getGenConstituents(), bDaughters, nMatch) ) continue;
        if ( nMatch < cut_minNMatchBquark_ ) continue;

        minDR = dR;
        matchedJetIndex = j;
        nMatchBest = nMatch;
      }

      if ( matchedJetIndex >= 0 )
      {
        matchedJetsIndex.insert(matchedJetIndex);
        if ( doHist_ )
        {
          const double dPt = p->pt()-genJetHandle->at(matchedJetIndex).pt();
          hDPt_BquarkOverlap_->Fill(dPt);
          hDR_BquarkOverlap_->Fill(minDR);

          hN_BquarkOverlap_->Fill(nMatchBest);
          hNVsDPt_BquarkOverlap_->Fill(nMatchBest, dPt);
          hNVsDR_BquarkOverlap_->Fill(nMatchBest, minDR);

          const double nFrac = 1.*nMatchBest/bDaughters.size();
          hNFrac_BquarkOverlap_->Fill(nFrac);
          hNFracVsDPt_BquarkOverlap_->Fill(nFrac, dPt);
          hNFracVsDR_BquarkOverlap_->Fill(nFrac, minDR);
        }
      }
    }
  }

  // Match by b quark overlap fraction 
  if ( matchByBquarkFrac_ )
  {
    for ( int i=0, n=bQuarks.size(); i<n; ++i )
    {
      const reco::GenParticle* p = bQuarks[i];
      std::vector<const reco::GenParticle*> bDaughters;
      collectStableDaughters(p, bDaughters);

      double minDR = cut_maxMatchDeltaR_;
      int matchedJetIndex = -1;
      int nMatchBest = 0;

      double bestFrac = 0;
      for ( int j=0, m=genJetHandle->size(); j<m; ++j )
      {
        const reco::GenJet& jet = genJetHandle->at(j);

        const double dR = deltaR(*p, jet);
        if ( dR >= minDR ) continue;
        int nMatch = 0;
        if ( !isOverlap(jet.getGenConstituents(), bDaughters, nMatch) ) continue;
        const double frac = 1.*nMatch/bDaughters.size();
        if ( frac < cut_minFracBquark_ ) continue;

        minDR = dR;
        matchedJetIndex = j;
        nMatchBest = nMatch;
        bestFrac = frac;
      }

      if ( matchedJetIndex >= 0 )
      {
        matchedJetsIndex.insert(matchedJetIndex);
        if ( doHist_ )
        {
          const double dPt = p->pt()-genJetHandle->at(matchedJetIndex).pt();
          hDPt_BquarkFrac_->Fill(dPt);
          hDR_BquarkFrac_->Fill(minDR);

          hN_BquarkFrac_->Fill(nMatchBest);
          hNVsDPt_BquarkFrac_->Fill(nMatchBest, dPt);
          hNVsDR_BquarkFrac_->Fill(nMatchBest, minDR);

          hNFrac_BquarkFrac_->Fill(bestFrac);
          hNFracVsDPt_BquarkFrac_->Fill(bestFrac, dPt);
          hNFracVsDR_BquarkFrac_->Fill(bestFrac, minDR);
        }
      }
    }
  }

  // Loop over genJets and find b hadron matching
  if ( matchByBHadronOverlap_ )
  {
    for ( int i=0, n=bHadrons.size(); i<n; ++i )
    {
      const reco::GenParticle* p = bHadrons[i];
      std::vector<const reco::GenParticle*> bDaughters;
      collectStableDaughters(p, bDaughters);

      double minDR = cut_maxMatchDeltaR_;
      int matchedJetIndex = -1;

      int nMatchBest = 0;
      for ( int j=0, m=genJetHandle->size(); j<m; ++j )
      {
        const reco::GenJet& jet = genJetHandle->at(j);

        const double dR = deltaR(*p, jet);
        if ( dR >= minDR ) continue;
        int nMatch = 0;
        if ( !isOverlap(jet.getGenConstituents(), bDaughters, nMatch) ) continue;
        if ( nMatch < cut_minNMatchBHadron_ ) continue;

        minDR = dR;
        matchedJetIndex = j;
        nMatchBest = nMatch;
      }

      if ( matchedJetIndex >= 0 )
      {
        matchedJetsIndex.insert(matchedJetIndex);
        if ( doHist_ )
        {
          const double dPt = p->pt()-genJetHandle->at(matchedJetIndex).pt();
          hDPt_BHadronOverlap_->Fill(dPt);
          hDR_BHadronOverlap_->Fill(minDR);

          hN_BHadronOverlap_->Fill(nMatchBest);
          hNVsDPt_BHadronOverlap_->Fill(nMatchBest, dPt);
          hNVsDR_BHadronOverlap_->Fill(nMatchBest, minDR);

          const double nFrac = 1.*nMatchBest/bDaughters.size();
          hNFrac_BHadronOverlap_->Fill(nFrac);
          hNFracVsDPt_BHadronOverlap_->Fill(nFrac, dPt);
          hNFracVsDR_BHadronOverlap_->Fill(nFrac, minDR);
        }
      }
    }
  }

  if ( matchByBHadronFrac_ )
  {
    for ( int i=0, n=bHadrons.size(); i<n; ++i )
    {
      const reco::GenParticle* p = bHadrons[i];
      std::vector<const reco::GenParticle*> bDaughters;
      collectStableDaughters(p, bDaughters);

      double minDR = cut_maxMatchDeltaR_;
      int matchedJetIndex = -1;
      int nMatchBest = 0;

      double bestFrac = 0;
      for ( int j=0, m=genJetHandle->size(); j<m; ++j )
      {   
        const reco::GenJet& jet = genJetHandle->at(j);
          
        const double dR = deltaR(*p, jet);
        if ( dR >= minDR ) continue;
        int nMatch = 0;
        if ( !isOverlap(jet.getGenConstituents(), bDaughters, nMatch) ) continue;
        const double frac = 1.*nMatch/bDaughters.size();
        if ( frac < cut_minFracBHadron_ ) continue;
    
        minDR = dR;
        matchedJetIndex = j;
        nMatchBest = nMatch;
        bestFrac = frac;
      }

      if ( matchedJetIndex >= 0 )
      {
        matchedJetsIndex.insert(matchedJetIndex);
        if ( doHist_ )
        {
          const double dPt = p->pt()-genJetHandle->at(matchedJetIndex).pt();
          hDPt_BHadronFrac_->Fill(dPt);
          hDR_BHadronFrac_->Fill(minDR);

          hN_BHadronFrac_->Fill(nMatchBest);
          hNVsDPt_BHadronFrac_->Fill(nMatchBest, dPt);
          hNVsDR_BHadronFrac_->Fill(nMatchBest, minDR);

          hNFrac_BHadronFrac_->Fill(bestFrac);
          hNFracVsDPt_BHadronFrac_->Fill(bestFrac, dPt);
          hNFracVsDR_BHadronFrac_->Fill(bestFrac, minDR);
        }
      }
    }
  }

  // Now we have non-duplicated indicies of b matched jets.
  auto_ptr<reco::GenJetCollection> matchedJets(new reco::GenJetCollection);
  for ( std::set<int>::const_iterator iter = matchedJetsIndex.begin();
        iter != matchedJetsIndex.end(); ++iter )
  {
    const int i = *iter;
    matchedJets->push_back(genJetHandle->at(i));
  }

  event.put(matchedJets);

}

void GenBJetSelector::collectStableDaughters(const reco::GenParticle* p, std::vector<const reco::GenParticle*>& stables)
{
  if ( !p ) return;
  const int absPdgId = abs(p->pdgId());
  if ( p->status() == 1 )
  {
    if ( absPdgId != 12 and absPdgId != 14 and absPdgId != 16 )
    {
     stables.push_back(p);
    }
  }
  else
  {
    for ( int i=0, n=p->numberOfDaughters(); i<n; ++i )
    {
      const reco::GenParticle* d = dynamic_cast<const reco::GenParticle*>(p->daughter(i));
      collectStableDaughters(d, stables);
    }
  }
}

bool GenBJetSelector::isBHadron(const int pdgId)
{
  int absPdgId = abs(pdgId);
  if ( absPdgId <= 100 ) return false; // Fundamental particles and MC internals
  if ( absPdgId >= 1000000000 ) return false; // Nuclears, +-10LZZZAAAI

  // General form of PDG ID is 7 digit form
  // +- n nr nL nq1 nq2 nq3 nJ
  //const int nJ = absPdgId % 10; // Spin
  const int nq3 = (absPdgId / 10) % 10;
  const int nq2 = (absPdgId / 100) % 10;
  const int nq1 = (absPdgId / 1000) % 10;

  if ( nq3 == 0 ) return false; // Diquarks
  if ( nq1 == 0 and nq2 == 5 ) return true; // B Mesons
  if ( nq1 == 5 ) return true; // B Baryons

  else return false;

}

bool GenBJetSelector::isOverlap(const std::vector<const reco::GenParticle*>& pColl1,
                                const std::vector<const reco::GenParticle*>& pColl2,
                                int& nMatch)
{
  nMatch = 0;
  for ( int i=0, n=pColl1.size(); i<n; ++i )
  {
    const reco::GenParticle* p1 = pColl1[i];
    if ( !p1 ) continue;
    for ( int j=0, m=pColl2.size(); j<m; ++j )
    {
      const reco::GenParticle* p2 = pColl2[j];
      if ( !p2 ) continue;

      if ( p1 == p2 ) ++nMatch;
    }
  }

  return nMatch > 0;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(GenBJetSelector);
