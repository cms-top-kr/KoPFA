#include "KoPFA/DataFormats/interface/TTbarEvent.h"

using namespace Ko;

const double cacheJetMinPt = 30;
const double cacheJetMinBtag = 1.70;

TTbarEvent::TTbarEvent()
{
  algoNames_.push_back("trackCountingHighEffBJetTags");
  algoNames_.push_back("simpleSecondaryVertexBJetTags");
  algoNames_.push_back("combinedSecondaryVertexBJetTags");

}

void TTbarEvent::clear()
{
  runNumber_ = lumiNumber_ = eventNumber_ = -999;

  l1_.SetPxPyPzE(0,0,0,0);
  l2_.SetPxPyPzE(0,0,0,0);
  l1Sign_ = l2Sign_ = -999;
  chIso1_ = phIso1_ = nhIso1_ = relPFIso1_ = -999;
  chIso2_ = phIso2_ = nhIso2_ = relPFIso2_ = -999;
  tkIso1_ = ecIso1_ = hcIso1_ = relDetIso1_ = -999;
  tkIso2_ = ecIso2_ = hcIso2_ = relDetIso2_ = -999;

  jets_.clear();
  unCorrJets_.clear();
  jecErrs_.clear();
  bTag_.clear();

  nGoodJetsPt_ = nGoodJetsPtBtag_ = 0;
  
  met_ = metX_ = metY_ = 0;
  unCorrMet_ = unCorrMetX_ = unCorrMetY_ = 0;
  metXUpper_ = metXLower_ = metYUpper_ = metYLower_ = 0;

  zM_ = mass_ = -999;
  massWithMAOS_ = -999;
  massUser1_ = -999;
  massUser2_ = -999;
}

void TTbarEvent::addJet(const pat::Jet* jet)
{
  const int nAlgo = algoNames_.size();
  std::vector<double> bTagVars(nAlgo);
  for ( int i=0; i<nAlgo; ++i )
  {
    bTagVars[i] = jet->bDiscriminator(algoNames_[i]);
  }

  unCorrJets_.push_back(jet->p4());
  bTag_.push_back(bTagVars);
}

void TTbarEvent::addCorrJet(const reco::Candidate::LorentzVector corrJetLVec, const double jecErr)
{
  jets_.push_back(corrJetLVec);
  jecErrs_.push_back(jecErr);
}

void TTbarEvent::setMET(const double metX, const double metY)
{
  unCorrMetX_ = metX;
  unCorrMetY_ = metY;
  unCorrMet_ = hypot(metX, metY);
}

void TTbarEvent::setCorrMET(const double metX, const double metXLower, const double metXUpper,
                            const double metY, const double metYLower, const double metYUpper)
{
  metX_ = metX;
  metY_ = metY;
  metXLower_ = metXLower;
  metXUpper_ = metXUpper;
  metYLower_ = metYLower;
  metYUpper_ = metYUpper;

  met_ = hypot(metX, metY);
}

void TTbarEvent::setEvent(const edm::EventID& eventId)
{
  eventNumber_ = eventId.event();
  runNumber_ = eventId.run();
  lumiNumber_ = eventId.luminosityBlock();
}

void TTbarEvent::update()
{
  // Calculate number of jets with Pt, btag cuts
  const unsigned int nJet = jets_.size();
  for ( unsigned int i = 0; i < nJet; ++i )
  {
    const reco::Candidate::LorentzVector& jet = jets_[i];
    const double jetPt = jet.Pt();

    if ( jetPt >= cacheJetMinPt )
    {
      ++nGoodJetsPt_;
      if ( bTag(i, 0) > cacheJetMinBtag )
      {
        ++nGoodJetsPtBtag_;
      }
    }
  }

  // Calculate M(llbbmet) if nJet >= 2
  if ( nJet >= 2 )
  {
    // Find 2 leading jets
    int j1Index = -1, j2Index = -1;
    double j1Pt = 0, j2Pt = 0;
    for ( unsigned int i = 0; i < nJet; ++i )
    {
      const reco::Candidate::LorentzVector& jet = jets_[i];
      const double jetPt = jet.Pt();

      if ( j2Pt < jetPt ) 
      {
        j2Index = int(i);
        j2Pt = jetPt;
      }
      if ( j1Pt < j2Pt ) 
      {
        std::swap(j1Pt, j2Pt);
        std::swap(j1Index, j2Index);
      }
    }

    if ( j1Index >= 0 and j2Index >= 0 )
    {
      const reco::Candidate::LorentzVector& j1 = jets_[j1Index];
      const reco::Candidate::LorentzVector& j2 = jets_[j2Index];

      const reco::Candidate::LorentzVector met(metX_, metY_, 0, hypot(metX_, metY_));
      mass_ = (l1_+l2_+j1+j2+met).M();
    }
  }
}

int TTbarEvent::nJets(const double minPt) const
{
  const int nJet = nJets();
  int nGoodJet = 0;
  for ( int i=0; i<nJet; ++i )
  {
    const double et = jets_[i].Pt();
    if ( et < minPt ) continue;
    ++nGoodJet;
  }
  return nGoodJet;
}

int TTbarEvent::nJets(const double minPt, const double minBTag, const int unsigned algoNum) const
{
  const int nJet = nJets();
  int nGoodJet = 0;
  for ( int i=0; i<nJet; ++i )
  {
    if ( jets_[i].Pt() < minPt ) continue;
    if ( bTag(i, algoNum) < minBTag) continue;

    ++nGoodJet;
  }
  return nGoodJet;
}

double TTbarEvent::bTag(const unsigned int i, const unsigned int algoNum) const
{
  if ( i >= bTag_.size() ) return -999;
  if ( algoNum >= bTag_[i].size() ) return -999;
  return bTag_[i][algoNum];
}

void TTbarEvent::setLepton(const reco::Candidate* l1, const reco::Candidate* l2)
{
  const pat::Electron* e1 = dynamic_cast<const pat::Electron*>(l1);
  const pat::Electron* e2 = dynamic_cast<const pat::Electron*>(l2);
  const pat::Muon* mu1 = dynamic_cast<const pat::Muon*>(l1);
  const pat::Muon* mu2 = dynamic_cast<const pat::Muon*>(l2);

  if ( e1 ) 
  {
    l1Sign_ = e1->charge();

    tkIso1_ = e1->trackIso();
    ecIso1_ = e1->ecalIso();
    hcIso1_ = e1->hcalIso();

    l1_ = e1->pfCandidateRef()->p4();

    chIso1_ = e1->chargedHadronIso();
    phIso1_ = e1->photonIso();
    nhIso1_ = e1->neutralHadronIso();

    relPFIso1_ = (chIso1_+phIso1_+nhIso1_)/e1->pfCandidateRef()->pt();
    relDetIso1_ = (tkIso1_+ecIso1_+hcIso1_)/e1->pfCandidateRef()->pt();
  }
  else if ( mu1 ) 
  {
    l1Sign_ = mu1->charge();

    tkIso1_ = mu1->trackIso();
    ecIso1_ = mu1->ecalIso();
    hcIso1_ = mu1->hcalIso();

    l1_ = mu1->pfCandidateRef()->p4();

    chIso1_ = mu1->chargedHadronIso();
    phIso1_ = mu1->photonIso();
    nhIso1_ = mu1->neutralHadronIso();

    relPFIso1_ = (chIso1_+phIso1_+nhIso1_)/mu1->pfCandidateRef()->pt();
    relDetIso1_ = (tkIso1_+ecIso1_+hcIso1_)/mu1->pfCandidateRef()->pt();
  }

  if ( e2 )
  {
    l2Sign_ = e2->charge();

    tkIso2_ = e2->trackIso();
    ecIso2_ = e2->ecalIso();
    hcIso2_ = e2->hcalIso();

    l2_ = e2->pfCandidateRef()->p4();

    chIso2_ = e2->chargedHadronIso();
    phIso2_ = e2->photonIso();
    nhIso2_ = e2->neutralHadronIso();

    relPFIso2_ = (chIso2_+phIso2_+nhIso2_)/e2->pfCandidateRef()->pt();
    relDetIso2_ = (tkIso2_+ecIso2_+hcIso2_)/e2->pfCandidateRef()->pt();
  }
  else if ( mu2 )
  {
    l2Sign_ = mu2->charge();

    tkIso2_ = mu2->trackIso();
    ecIso2_ = mu2->ecalIso();
    hcIso2_ = mu2->hcalIso();

    l2_ = mu2->pfCandidateRef()->p4();

    chIso2_ = mu2->chargedHadronIso();
    phIso2_ = mu2->photonIso();
    nhIso2_ = mu2->neutralHadronIso();

    relPFIso2_ = (chIso2_+phIso2_+nhIso2_)/mu2->pfCandidateRef()->pt();
    relDetIso2_ = (tkIso2_+ecIso2_+hcIso2_)/mu2->pfCandidateRef()->pt();
  }

  zM_ = (l1_+l2_).M();
}

std::string TTbarEvent::algoName(const unsigned int algoNum) const
{
  if ( algoNames_.size() <= algoNum ) return "";
  return algoNames_[algoNum];
}

double TTbarEvent::m(const int massAlgoNum) const
{
  switch ( massAlgoNum )
  {
  case 0: return mass_; break;
  case 1: return massWithMAOS_; break;
  case 2: return massUser1_; break;
  case 3: return massUser2_; break;
  }
  return -999;
}

