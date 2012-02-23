#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "TMath.h"

using namespace Ko;

void TTbarGenEvent::clear()
{
  tt_.SetPxPyPzE(0,0,0,0);
  tQuarks_.clear();
  bQuarks_.clear();
  leptons_.clear();

  mumuDecay = 0;
  eeDecay = 0;
  emuDecay = 0;
  tauDecay = 0;

  electrons_.clear();
  muons_.clear();
  taus_.clear();
  met_ = metX_ = metY_ = 0;

  stableElectrons_.clear();
  stableMuons_.clear();
  jets_.clear();
  jetsBMatch_.clear();
}

void TTbarGenEvent::set(const reco::GenParticleCollection* genParticles,
                        const reco::GenJetCollection* genJets,
                        const reco::GenMET* genMET)
{
  clear();

  // Do parton level variables
  for ( reco::GenParticleCollection::const_iterator genParticle = genParticles->begin();
        genParticle != genParticles->end(); ++genParticle )
  {
    if ( genParticle->status() != 3 ) continue;

    const int absPdgId = abs(genParticle->pdgId());

    if ( absPdgId == 6 )
    {
      tt_ += genParticle->p4();
      tQuarks_.push_back(genParticle->p4());
      continue;
    }

    // Find mother particle with status == 3
    const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(genParticle->mother());
    while ( mother != 0 and mother->status() != 3 )
    {
      mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
    }
    if ( !mother or mother->status() != 3 ) continue;
    const int motherAbsPdgId = abs(mother->pdgId());

    if ( absPdgId == 5 and motherAbsPdgId == 6 )
    {
      bQuarks_.push_back(genParticle->p4());
    }
    if ( motherAbsPdgId == 24 )
    {
      if ( absPdgId == 11 )
      {
        electrons_.push_back(genParticle->p4());
        leptons_.push_back(genParticle->p4());
      }
      else if ( absPdgId == 13 ) 
      {
        muons_.push_back(genParticle->p4());
        leptons_.push_back(genParticle->p4());
      }
      else if ( absPdgId ==  15 )
      {
        int nlep = 0;
        unsigned int nTauDaughters = genParticle->numberOfDaughters();
        for ( unsigned iTauDaughter=0; iTauDaughter<nTauDaughters; ++iTauDaughter ) {
          if( nlep == 1) break;
          const reco::Candidate* decay = genParticle->daughter(iTauDaughter);
          if ( abs(decay->pdgId()) == 11 ) {
            taus_.push_back(decay->p4());
            electrons_.push_back(genParticle->p4());
            leptons_.push_back(decay->p4());
            ++nlep;
          }else if( abs(decay->pdgId()) == 13  ){
            taus_.push_back(decay->p4());
            muons_.push_back(genParticle->p4());
            leptons_.push_back(decay->p4());
            ++nlep;
          }else if( abs(decay->pdgId()) == 15 ){
            unsigned int nTauGrandDaughters = decay->numberOfDaughters();
            for ( unsigned iTauGrandDaughter=0; iTauGrandDaughter<nTauGrandDaughters; ++iTauGrandDaughter ) {
              const reco::Candidate* granddecay = decay->daughter(iTauGrandDaughter);
              if ( abs(granddecay->pdgId()) == 11 ) {
                taus_.push_back(granddecay->p4());
                electrons_.push_back(genParticle->p4());
                leptons_.push_back(granddecay->p4());
                ++nlep;
              }else if( abs(granddecay->pdgId()) == 13){
                taus_.push_back(granddecay->p4());
                muons_.push_back(genParticle->p4());
                leptons_.push_back(granddecay->p4());
                ++nlep;
              }else{
                continue;
              }
            }
          }else {
           continue;
          }
        }
      }
      else if ( absPdgId == 12 or absPdgId == 14 or absPdgId == 16 )
      {
        metX_ += genParticle->px();
        metY_ += genParticle->py();
      }
    }
  }

  if( leptons_.size() >= 2 ){

    if( taus_.size() > 0 ){
      tauDecay = 1;
    }
   
    if( muons_.size() >= 2 ){
      mumuDecay = 1;
    }else if( electrons_.size() >= 2){
      eeDecay = 1;
    }else if( electrons_.size() == 1 && muons_.size() == 1){
      emuDecay = 1;
    }else{
      std::cout << "it should not reach here" << std::endl;
    }

  }
  met_ = hypot(metX_, metY_);

  // Do particle level variables
  // For a clearity, genParticle loop will be done separately
  std::vector<const reco::GenParticle*> bHadrons;
  std::vector<const reco::GenParticle*> finalBQuarks;
  for ( int i=0, n=genParticles->size(); i<n; ++i )
  {
    const reco::GenParticle& p = genParticles->at(i);

    const int status = p.status();
    const int absPdgId = p.pdgId();

    if ( status == 1 )
    {
      if ( absPdgId == 11 and p.pt() >= 20 and abs(p.eta()) <= 2.4 )
      {
        stableElectrons_.push_back(p.p4());
      }
      else if ( absPdgId == 13 and p.pt() >= 20 and abs(p.eta()) <= 2.4 )
      {
        stableMuons_.push_back(p.p4());
      }
    }
    else
    {
      if ( absPdgId == 5 )
      {
        bool isFinalBquark = true;
        for ( int j=0,m=p.numberOfDaughters(); j<m; ++j )
        {
          const reco::GenParticle* dau = dynamic_cast<const reco::GenParticle*>(p.daughter(j));
          if ( !dau ) continue;

          if ( abs(dau->pdgId()) == 5 )
          {
            isFinalBquark = false;
            break;
          }
        }
        if ( isFinalBquark ) finalBQuarks.push_back(&p);
      }
      else if ( isBHadron(absPdgId) )
      {
        bool hasBDaughter = false;
        for ( int j=0,m=p.numberOfDaughters(); j<m; ++j )
        {
          const reco::GenParticle* dau = dynamic_cast<const reco::GenParticle*>(p.daughter(j));
          if ( !dau ) continue;

          if ( isBHadron(dau->pdgId()) )
          {
            hasBDaughter = true;
            break;
          }
        }
        if ( !hasBDaughter ) bHadrons.push_back(&p);
      }
    }
  }

  // Collect genJets
  std::vector<const reco::GenJet*> selectedGenJets;
  for ( int i=0, n=genJets->size(); i<n; ++i )
  {
    const reco::GenJet& jet = genJets->at(i);
    if ( jet.pt() < 30 or abs(jet.eta()) > 2.4 ) continue;

    selectedGenJets.push_back(&jet);
    jets_.push_back(jet.p4());
    jetsBMatch_.push_back(0);
  }
  // First try to find BHadron to jet association
  std::vector<const reco::GenParticle*> bHadronDaughters;
  using namespace std;
  
  for ( int i=0, n=bHadrons.size(); i<n; ++i )
  {
    const reco::GenParticle* bHadron = bHadrons[i];
    bHadronDaughters.clear();
    findStableDaughters(bHadron, bHadronDaughters);

    int bestNMatch = 0;
    double bestDR = 999;
    const reco::GenJet* bestMatchedJet = 0;
    int bestMatchedJetIndex = -1;
    for ( int j=0, m=selectedGenJets.size(); j<m; ++j )
    {
      const reco::GenJet* jet = selectedGenJets.at(j);
      int nMatch = 0;
      if ( isOverlap(jet->getGenConstituents(), bHadronDaughters, nMatch) )
      {
        const double dR = deltaR(*jet, *bHadron);
        if ( dR < bestDR )
        {
          bestDR = dR;
          bestMatchedJet = jet;
          bestMatchedJetIndex = j;
          bestNMatch = nMatch;
        }
      }
    }
    if ( bestMatchedJet ) jetsBMatch_[bestMatchedJetIndex] = bestNMatch;
  }

}

bool TTbarGenEvent::isOverlap(const std::vector<const reco::GenParticle*>& pColl1,
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

using namespace std;
void TTbarGenEvent::findStableDaughters(const reco::GenParticle* p,
                                        std::vector<const reco::GenParticle*>& stableDaughters)
{
  for ( int i=0, n=p->numberOfDaughters(); i<n; ++i )
  {
    const reco::GenParticle* dau = dynamic_cast<const reco::GenParticle*>(p->daughter(i));
    if ( !dau ) continue;
    if ( dau->status() != 1 ) findStableDaughters(dau, stableDaughters);

    const int absPdgId = abs(dau->pdgId());
    if ( absPdgId == 12 or absPdgId == 14 or absPdgId == 16 ) continue;

    stableDaughters.push_back(dau);
  }
}

bool TTbarGenEvent::isBHadron(const int pdgId)
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

int TTbarGenEvent::nBJets() const
{
  const unsigned int nJetsBMatch = jetsBMatch_.size();
  if ( jets_.size() != nJetsBMatch )
  {
    std::cout << "TTbarGenEvent::nBJets() : Jets and jetBMatch size does not match\n";
    return -1;
  }
  int retVal = 0;
  for ( unsigned int i=0, n=nJetsBMatch; i<n; ++i )
  {
    if ( jetsBMatch_[i] ) ++retVal;
  }
  return retVal;
}

std::vector<math::XYZTLorentzVector> TTbarGenEvent::bJets() const
{
  std::vector<math::XYZTLorentzVector> retVal;
  const unsigned int nJetsBMatch = jetsBMatch_.size();
  if ( jets_.size() != nJetsBMatch )
  {
    std::cout << "TTbarGenEvent::bJets() : Jets and jetBMatch size does not match\n";
    return retVal;
  }
  retVal.reserve(nJetsBMatch);
  for ( unsigned int i=0, n=nJetsBMatch; i<n; ++i )
  {
    if ( jetsBMatch_[i] ) retVal.push_back(jets_[i]);
  }
  return retVal;
}

math::XYZTLorentzVector TTbarGenEvent::partonTTbar() const
{
  return tt_;
}

math::XYZTLorentzVector TTbarGenEvent::partonLLBBMet() const
{
  math::XYZTLorentzVector retVal;
  if ( leptons_.size() < 2 ) return retVal;
  if ( bQuarks_.size() < 2 ) return retVal;

  retVal += leptons_[0]+leptons_[1];
  retVal += bQuarks_[0]+bQuarks_[1];

  retVal += math::XYZTLorentzVector(metX_, metY_, 0, met_);

  return retVal;
}

math::XYZTLorentzVector TTbarGenEvent::particleLLJJMet() const
{
  math::XYZTLorentzVector retVal;
  if ( emuDecay > 0 and stableElectrons_.size() > 0 and stableMuons_.size() > 0 )
  {
    retVal += stableElectrons_[0];
    retVal += stableMuons_[0];
  }
  else if ( eeDecay > 0 and stableElectrons_.size() > 1 )
  {
    retVal += stableElectrons_[0] + stableElectrons_[1];
  }
  else if ( mumuDecay > 0 and stableMuons_.size() > 1 )
  {
    retVal += stableMuons_[0] + stableMuons_[1];
  }
  else return math::XYZTLorentzVector();

  if ( jets_.size() > 1 ) retVal += jets_[0] + jets_[1];
  else return math::XYZTLorentzVector();

  retVal += math::XYZTLorentzVector(metX_, metY_, 0, TMath::Hypot(metX_, metY_));

  return retVal;
}

math::XYZTLorentzVector TTbarGenEvent::particleLLBjBjMet() const
{
  math::XYZTLorentzVector retVal;
  if ( emuDecay > 0 and stableElectrons_.size() > 0 and stableMuons_.size() > 0 )
  {
    retVal += stableElectrons_[0];
    retVal += stableMuons_[0];
  }
  else if ( eeDecay > 0 and stableElectrons_.size() > 1 )
  {
    retVal += stableElectrons_[0] + stableElectrons_[1];
  }
  else if ( mumuDecay > 0 and stableMuons_.size() > 1 )
  {
    retVal += stableMuons_[0] + stableMuons_[1];
  }
  else return math::XYZTLorentzVector();

  std::vector<math::XYZTLorentzVector> bJets = TTbarGenEvent::bJets();
  if ( bJets.size() > 1 ) retVal += bJets[0] + bJets[1];
  else return math::XYZTLorentzVector();

  return retVal;
}

