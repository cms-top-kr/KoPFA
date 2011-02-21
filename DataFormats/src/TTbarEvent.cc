#include "KoPFA/DataFormats/interface/TTbarEvent.h"

using namespace Ko;

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
  bTag_.clear();
  
  met_ = metX_ = metY_ = 0;

  zM_ = mass_ = -999;
}

void TTbarEvent::addJet(const pat::Jet* jet, const double scaleFactor = 1.0)
{
  const int nAlgo = algoNames_.size();
  std::vector<double> bTagVars(nAlgo);
  for ( int i=0; i<nAlgo; ++i )
  {
    bTagVars[i] = jet->bDiscriminator(algoNames_[i]);
  }

  jets_.push_back(jet->p4()*scaleFactor);
  bTag_.push_back(bTagVars);
}

void TTbarEvent::setMET(const pat::MET* met)
{
  met_ = met->pt();
  metX_ = met->px();
  metY_ = met->py();
}

void TTbarEvent::setEvent(const edm::EventID& eventId)
{
  eventNumber_ = eventId.event();
  runNumber_ = eventId.run();
  lumiNumber_ = eventId.luminosityBlock();
}

void TTbarEvent::update()
{
  // Calculate M(llbbmet) if nJet >= 2
  if ( jets_.size() >= 2 )
  {
    // Find 2 leading jets
    reco::Candidate::LorentzVector j1, j2;
    for ( std::vector<reco::Candidate::LorentzVector>::const_iterator jet = jets_.begin();
          jet != jets_.end(); ++jet )
    {
      if ( j2.Et() < jet->Et() ) j2 = *jet;
      if ( j1.Et() < j2.Et() ) std::swap(j1, j2);
    }

    const reco::Candidate::LorentzVector met(metX_, metY_, 0, hypot(metX_, metY_));
    mass_ = (l1_+l2_+j1+j2+met).M();
  }
}

int TTbarEvent::numberOfJets(const double minEt) const
{
  const int nJet = numberOfJets();
  int nGoodJet = 0;
  for ( int i=0; i<nJet; ++i )
  {
    const double et = jets_[i].Et();
    if ( et < minEt ) continue;
    ++nGoodJet;
  }
  return nGoodJet;
}

int TTbarEvent::numberOfJets(const double minEt, const double minBTag, const int unsigned algoNum) const
{
  const int nJet = numberOfJets();
  int nGoodJet = 0;
  for ( int i=0; i<nJet; ++i )
  {
    if ( jets_[i].Et() < minEt ) continue;
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
    l2Sign_ = mu1->charge();

    tkIso2_ = mu1->trackIso();
    ecIso2_ = mu1->ecalIso();
    hcIso2_ = mu1->hcalIso();

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

  zM_ = (l1_+l2_).mag();
}

std::string TTbarEvent::algoName(const unsigned int algoNum) const
{
  if ( algoNames_.size() <= algoNum ) return "";
  return algoNames_[algoNum];
}

