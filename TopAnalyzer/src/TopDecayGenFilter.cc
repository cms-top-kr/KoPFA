#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <vector>

class TopDecayGenFilter : public edm::EDFilter
{
public:
  TopDecayGenFilter(const edm::ParameterSet& pset);
  ~TopDecayGenFilter() {};

  void beginJob() {};
  bool filter(edm::Event& event, const edm::EventSetup& eventSetup);
  void endJob() {};

private:
  bool applyFilter_;
  bool semiLeptonic_;
  bool semiLeptonicMuon_;
  bool semiLeptonicElectron_;
  bool diLeptonic_;
  bool diLeptonicMuoMuo_;
  bool diLeptonicEleEle_;
  bool diLeptonicMuoEle_;
};

TopDecayGenFilter::TopDecayGenFilter(const edm::ParameterSet& pset)
{
  applyFilter_= pset.getUntrackedParameter<bool>("applyFilter",false);

  semiLeptonic_ = pset.getParameter<bool>("semiLeptonic"),
  semiLeptonicMuon_ = pset.getParameter<bool>("semiLeptonicMuon"),
  semiLeptonicElectron_ = pset.getParameter<bool>("semiLeptonicElectron"),
  diLeptonic_ = pset.getParameter<bool>("diLeptonic");
  diLeptonicMuoMuo_ = pset.getParameter<bool>("diLeptonicMuoMuo");
  diLeptonicEleEle_ = pset.getParameter<bool>("diLeptonicEleEle");       
  diLeptonicMuoEle_ = pset.getParameter<bool>("diLeptonicMuoEle");
 
}

bool TopDecayGenFilter::filter(edm::Event& iEvent, const edm::EventSetup& eventSetup)
{
  if (!applyFilter_)
    return true;

  bool accepted = false;
  std::vector<bool> leptonic(2,static_cast<bool>(false));
  std::vector<bool> electronic(2,static_cast<bool>(false));
  std::vector<bool> muonic(2,static_cast<bool>(false));
  std::vector<bool> taunic(2,static_cast<bool>(false));
  std::vector<bool> hadronic(2,static_cast<bool>(false));

  using namespace std;
  using namespace edm;
  using namespace reco;

  const reco::GenParticleCollection* myGenParticles = 0;

  Handle<reco::GenParticleCollection> genEvt;
  bool genPart = iEvent.getByLabel("genParticles",genEvt);
  if ( genPart ) myGenParticles = &(*genEvt);
  if ( !myGenParticles ) return false;

  unsigned int nParticles = myGenParticles->size();
  int ntop = 0;
  for ( unsigned int ip=0; ip<nParticles; ++ip ) { 

    if ( ntop == 2 ) break;

    const reco::GenParticle& p = (*myGenParticles)[ip];
    if ( abs(p.pdgId()) != 6 ) continue;

    unsigned int nDaughters = p.numberOfDaughters();
    int nW = 0;
    for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
      const reco::Candidate* daugh = p.daughter(iDaughter);
      if ( nW == 1 ) break;
      if ( abs(daugh->pdgId()) != 24 ) continue; 
      unsigned int nWDaughters = daugh->numberOfDaughters();
      for ( unsigned iWDaughter=0; iWDaughter<nWDaughters; ++iWDaughter ) {
	const reco::Candidate* decay = daugh->daughter(iWDaughter);
	int decayId = abs(decay->pdgId());
	if ( decayId == 11 || decayId == 12 ) {  
	  electronic[ntop] = true;
	  leptonic[ntop] = true;
	  break; 
	} else if ( decayId == 13 || decayId == 14 ) {  
	  muonic[ntop] = true;
	  leptonic[ntop] = true;
	  break;
	} else if ( decayId == 15 || decayId == 16 ) {  
          taunic[ntop] = true;
          unsigned int nTauDaughters = decay->numberOfDaughters();
          for ( unsigned iTauDaughter=0; iTauDaughter<nTauDaughters; ++iTauDaughter ) {
            const reco::Candidate* tauDecay = decay->daughter(iTauDaughter);
            int tauDecayId = abs(tauDecay->pdgId());
            if ( tauDecayId == 11 || tauDecayId == 12 ) {
              electronic[ntop] = true;
              leptonic[ntop] = true;
              break;
            } else if ( tauDecayId == 13 || tauDecayId == 14 ) {
              muonic[ntop] = true;
              leptonic[ntop] = true;
              break;
            } else if (  tauDecayId == 15 || tauDecayId == 16 ) {
              unsigned int nTauGrandDaughters = tauDecay->numberOfDaughters();
              for ( unsigned iTauGrandDaughter=0; iTauGrandDaughter<nTauGrandDaughters; ++iTauGrandDaughter ) {
                const reco::Candidate* tauGrandDecay = tauDecay->daughter(iTauGrandDaughter);
                int tauGrandDecayId = abs(tauGrandDecay->pdgId());
                if ( tauGrandDecayId == 11 || tauGrandDecayId == 12 ) {
                  electronic[ntop] = true;
                  leptonic[ntop] = true;
                  break;
                } else if ( tauGrandDecayId == 13 || tauGrandDecayId == 14 ) {
                  muonic[ntop] = true;
                  leptonic[ntop] = true;
                  break;
                } else {
                  continue;
                }
              }
            } else{
              continue;
            }
          }
	} else if( decayId < 6 ){
          hadronic[ntop] = true;
        } else {  
	  continue;
	}
      }
      ++nW;
    }
    ++ntop;
  }

  if ( semiLeptonic_ && 
	( ( hadronic[0] && !hadronic[1] ) ||  
	  (!hadronic[0] &&  hadronic[1] ) ) ) {
     // All semi leptonic decays
    accepted = true;
    // Reject specific semi-leptonic decays
    // Electron
    if ( !semiLeptonicElectron_ && 
	  ( ( hadronic[0] && electronic[1] ) ||  
	    ( hadronic[1] && electronic[0] ) ) ) accepted = false; 
     // Muon
    if ( !semiLeptonicMuon_ && 
	  ( ( hadronic[0] && muonic[1] ) ||  
	    ( hadronic[1] && muonic[0] ) ) ) accepted = false; 
  }

  // Di-Leptonic
  if ( diLeptonic_ && leptonic[0] && leptonic[1] ) { 
    // All di-leptonic decays
    accepted = true;
    // Reject specific di-leptonic decays
    // Electron-Electron
    if ( !diLeptonicEleEle_ && 
      electronic[0] && electronic[1] ) accepted = false; 
    // Muon-Muon
    if ( !diLeptonicMuoMuo_ && 
      muonic[0] && muonic[1] ) accepted = false;
    // Electron-Muon
    if ( !diLeptonicMuoEle_ && 
      ( ( muonic[0] && electronic[1] ) || 
      ( muonic[1] && electronic[0] ) ) ) accepted = false; 
   }


  return accepted;
}

DEFINE_FWK_MODULE(TopDecayGenFilter);

