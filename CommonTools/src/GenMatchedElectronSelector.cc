#ifndef KoPFA_CommonTools_GenMatchedElectronSelector_H
#define KoPFA_CommonTools_GenMatchedElectronSelector_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Math/interface/deltaR.h"

class GenMatchedElectronSelector : public edm::EDFilter
{
public:
  GenMatchedElectronSelector(const edm::ParameterSet& pset);
  ~GenMatchedElectronSelector() {};

  void beginJob() {};
  bool filter(edm::Event& event, const edm::EventSetup&);
  void endJob() {};

  const reco::GenParticle* findMother(const reco::GenParticle* p, const int pdgId);

private:
  //edm::InputTag genMatchLabel_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag electronLabel_;
  double maxDR_;
  unsigned int minNumber_;
  unsigned int motherPdgId_;
  
};

GenMatchedElectronSelector::GenMatchedElectronSelector(const edm::ParameterSet& pset)
{
  genParticlesLabel_ = pset.getParameter<edm::InputTag>("genParticles");
  electronLabel_ = pset.getParameter<edm::InputTag>("electrons");
  maxDR_ = pset.getUntrackedParameter<double>("maxDR", 0.5);
  minNumber_ = pset.getUntrackedParameter<unsigned int>("minNumber", 0);
  motherPdgId_ = pset.getUntrackedParameter<unsigned int>("motherPdgId", 24);

  produces<std::vector<pat::Electron> >("");
}

bool GenMatchedElectronSelector::filter(edm::Event& event, const edm::EventSetup&)
{
  edm::Handle<reco::GenParticleCollection> genParticleHandle;
  edm::Handle<edm::View<pat::Electron> > electronHandle;

  event.getByLabel(genParticlesLabel_, genParticleHandle);
  event.getByLabel(electronLabel_, electronHandle);

  if ( !genParticleHandle.isValid() or !electronHandle.isValid() ) return false;

  std::auto_ptr<std::vector<pat::Electron> > matchedElectrons(new std::vector<pat::Electron>());

  // Manually match electron->genParticle
  for ( int i=0, n=electronHandle->size(); i<n; ++i )
  {
    const pat::Electron& electron = electronHandle->at(i);
    double bestDR = 999;

    for ( int j=0, m=genParticleHandle->size(); j<m; ++j )
    {
      const reco::GenParticle& genParticle = genParticleHandle->at(j);

      if ( abs(genParticle.pdgId()) != 11 ) continue;
      if ( genParticle.status() != 1 ) continue;

      // Check mother particles
      if ( !findMother(&genParticle, motherPdgId_) ) continue;

      const double dR = deltaR(electron, genParticle);
      if ( dR < bestDR )
      {
        bestDR = dR;
      }
    }

    if ( bestDR < maxDR_ )
    {
      matchedElectrons->push_back(electron);
    }
  }

  const unsigned int nMatched = matchedElectrons->size();
  event.put(matchedElectrons);

  return nMatched >= minNumber_;
}

const reco::GenParticle* GenMatchedElectronSelector::findMother(const reco::GenParticle* p, const int pdgId)
{
  if ( !p ) return 0;

  const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p->mother());
  if ( !mother ) return 0;

  if ( abs(mother->pdgId()) != pdgId or mother->status() != 3 ) return findMother(mother, pdgId);

  return mother;
}

#endif

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(GenMatchedElectronSelector);

