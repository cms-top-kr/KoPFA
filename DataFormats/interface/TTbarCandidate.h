#ifndef TTbarCandidate_H
#define TTbarCandidate_H

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "TLorentzVector.h"

#include <vector>

namespace Ko{

  class TTbarCandidate{
  public:
    TTbarCandidate(){}
    virtual ~TTbarCandidate(){}

    typedef std::vector<math::XYZTLorentzVector> LorentzVectors;

    // status 3
    const math::XYZTLorentzVector bquarks1() const { return bquarks_[0]; }
    const math::XYZTLorentzVector bquarks2() const { return bquarks_[1]; }
    const math::XYZTLorentzVector bquarks3() const { return bquarks_[2]; }
    const math::XYZTLorentzVector bquarks4() const { return bquarks_[3]; }

    const math::XYZTLorentzVector lepton1() const { return leptons_[0]; }
    const math::XYZTLorentzVector lepton2() const { return leptons_[1]; }

    const math::XYZTLorentzVector bJets1() const { return bJets_[0]; }
    const math::XYZTLorentzVector bJets2() const { return bJets_[1]; }
    const math::XYZTLorentzVector bJets3() const { return bJets_[2]; }
    const math::XYZTLorentzVector bJets4() const { return bJets_[3]; }
   
    void building( const reco::GenJetCollection* genJets, const reco::GenParticleCollection* genParticles );

    double mass() const { return mass_; }

    bool taunic(int i = -1) const { 
      bool hasTau = false;
      if( i == -1) hasTau = taunic1_ || taunic2_;
      if( i == 0 ) hasTau = taunic1_;
      if( i == 1 ) hasTau = taunic2_;
      return hasTau;
    }

    bool allHadronic() const { return allHadronic_; }

    bool semiLeptonic(int i = -1) const { 
      bool decay = false;
      if( i == -1) decay = semiLeptonic_;
      if( i == 0) decay = semiLeptonicMuo_ || semiLeptonicEle_;
      if( i == 1) decay = ( semiLeptonicMuo_ || semiLeptonicEle_ ) && !semiLeptonicTau_;
      return decay;
    }

    bool semiLeptonicMuo() const { return semiLeptonicMuo_; }
    bool semiLeptonicEle() const { return semiLeptonicEle_; }
    bool semiLeptonicTau() const { return semiLeptonicTau_; }

    bool diLeptonic(int i = -1) const { 
      bool decay = false;
      if( i == -1) decay = diLeptonic_;
      if( i == 0) decay = diLeptonicMuoMuo_ || diLeptonicMuoEle_ || diLeptonicEleEle_;
      if( i == 1) decay = ( diLeptonicMuoMuo_ || diLeptonicMuoEle_ || diLeptonicEleEle_) && !( diLeptonicTauMuo_ || diLeptonicTauEle_ || diLeptonicTauTau_);
      return decay; 
    }

    bool diLeptonicMuoMuo() const { return diLeptonicMuoMuo_; }
    bool diLeptonicMuoEle() const { return diLeptonicMuoEle_; }
    bool diLeptonicEleEle() const { return diLeptonicEleEle_; }
    bool diLeptonicTauMuo() const { return diLeptonicTauMuo_; }
    bool diLeptonicTauEle() const { return diLeptonicTauEle_; }
    bool diLeptonicTauTau() const { return diLeptonicTauTau_; }

    int NbQuarksTop() const { return NbQuarksTop_ ; }
    int NbQuarksNoTop() const { return NbQuarksNoTop_ ; }
    int NbQuarks() const { return NbQuarks_ ; }
    int NbQuarks20() const { return NbQuarks20_ ; }
    int NcQuarks() const { return NcQuarks_; }

    int NbJets() const { return NbJets_ ; }
    int NbJets15() const { return NbJets15_ ; }
    int NbJets20() const { return NbJets20_ ; }

    int NbJetsBHad() const { return NbJetsBHad_ ; }
    int NbJets15BHad() const { return NbJets15BHad_ ; }
    int NbJets20BHad() const { return NbJets20BHad_ ; }

    int NbJetsNoTop() const { return NbJetsNoTop_ ; }
    int NbJets15NoTop() const { return NbJets15NoTop_ ; }
    int NbJets20NoTop() const { return NbJets20NoTop_ ; }

    int NcJets() const { return NcJets_; }
    int NcJets10() const { return NcJets10_; }
    int NcJets15() const { return NcJets15_; }
    int NcJets20() const { return NcJets20_; }

    int NJets() const { return NJets_ ;}
    int NJets10() const { return NJets10_ ;}
    int NJets15() const { return NJets15_ ;}
    int NJets20() const { return NJets20_ ;}
    int NJets25() const { return NJets25_ ;}
    int NJets30() const { return NJets30_ ;}

  private:

    std::vector<const reco::Candidate *> getAncestors(const reco::Candidate &c);
    bool hasBottom(const reco::Candidate &c);
    bool decayFromBHadron(const reco::Candidate &c);
    const reco::Candidate* lastBHadron(const reco::Candidate &c);
    bool isLastbottom(const reco::GenParticle&);
    bool isLastcharm(const reco::GenParticle&);
    bool isFromtop(const reco::GenParticle&);
    double deltaR( const reco::Candidate &pasObj, const reco::GenJet &proObj );


    LorentzVectors bquarks_;
    LorentzVectors leptons_;
    LorentzVectors bJets_;

    double mass_;

    bool allHadronic_;
    bool semiLeptonic_;
    bool semiLeptonicMuo_;
    bool semiLeptonicEle_;
    bool semiLeptonicTau_;
    bool diLeptonic_;
    bool diLeptonicMuoMuo_;
    bool diLeptonicMuoEle_;
    bool diLeptonicEleEle_;
    bool diLeptonicTauMuo_;
    bool diLeptonicTauEle_;
    bool diLeptonicTauTau_;

    bool ttbbDecay_;

    bool taunic1_;
    bool taunic2_;

    int NbJets_;
    int NbJets15_;
    int NbJets20_;

    int NbJetsBHad_;
    int NbJets15BHad_;
    int NbJets20BHad_;

    int NbJetsNoTop_;
    int NbJets15NoTop_;
    int NbJets20NoTop_;

    int NcJets_;
    int NcJets10_;
    int NcJets15_;
    int NcJets20_;

    int NbQuarks_;
    int NbQuarksNoTop_;
    int NbQuarksTop_;
    int NbQuarks20_;

    int NcQuarks_;

    int NJets_;
    int NJets10_;
    int NJets15_;
    int NJets20_;
    int NJets25_;
    int NJets30_;
  };

}
#endif
