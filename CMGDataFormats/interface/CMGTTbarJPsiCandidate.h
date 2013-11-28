#ifndef CMGTTbarJPsiCandidate_H
#define CMGTTbarJPsiCandidate_H

#include "AnalysisDataFormats/CMGTools/interface/GenericTypes.h"
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

namespace vallot{

  class CMGTTbarJPsiCandidate{
  public:
    CMGTTbarJPsiCandidate(){}
    virtual ~CMGTTbarJPsiCandidate(){}

    typedef std::vector<math::XYZTLorentzVector> LorentzVectors;

    // status 3
    const math::XYZTLorentzVector tquarks1() const { return tquarks_[0]; }
    const math::XYZTLorentzVector tquarks2() const { return tquarks_[1]; }
    const math::XYZTLorentzVector bquarks1() const { return bquarks_[0]; }
    const math::XYZTLorentzVector bquarks2() const { return bquarks_[1]; }

    const math::XYZTLorentzVector lepton1() const { return leptons_[0]; }
    const math::XYZTLorentzVector lepton2() const { return leptons_[1]; }
    const math::XYZTLorentzVector priJPsi() const { return priJPsi_[0]; }
    const math::XYZTLorentzVector secJPsi() const { return secJPsi_[0]; }
    const math::XYZTLorentzVector tbJPsi() const { return tbJPsi_[0]; }
    const math::XYZTLorentzVector tbJPsilp() const { return tbJPsilp_[0]; }
    const math::XYZTLorentzVector tbJPsilm() const { return tbJPsilm_[0]; }
    const math::XYZTLorentzVector tbbJPsi() const { return tbbJPsi_[0]; }
    const math::XYZTLorentzVector tbbJPsilp() const { return tbbJPsilp_[0]; }
    const math::XYZTLorentzVector tbbJPsilm() const { return tbbJPsilm_[0]; }
    /*const math::XYZTLorentzVector JPsi1() const { return JPsi_[0]; }
    const math::XYZTLorentzVector JPsi2() const { return JPsi_[1]; }
    const math::XYZTLorentzVector lepJPsi1() const { return lepJPsi_[0]; }
    const math::XYZTLorentzVector lepJPsi2() const { return lepJPsi_[1]; }
    const math::XYZTLorentzVector JPsiB1() const { return JPsiB_[0]; }
    const math::XYZTLorentzVector JPsiB2() const { return JPsiB_[1]; }
    const math::XYZTLorentzVector JPsilepton1P() const { return JPsileptonP_[0]; }
    const math::XYZTLorentzVector JPsilepton1M() const { return JPsileptonM_[0]; }
    const math::XYZTLorentzVector JPsilepton2P() const { return JPsileptonP_[1]; }
    const math::XYZTLorentzVector JPsilepton2M() const { return JPsileptonM_[1]; }*/
    const math::XYZTLorentzVector nu1() const { return nus_[0]; }
    const math::XYZTLorentzVector nu2() const { return nus_[1]; }
    const math::XYZTLorentzVector taunu1() const { return taunus_[0]; }
    const math::XYZTLorentzVector taunu2() const { return taunus_[1]; }

    const math::XYZTLorentzVector bJets1() const { return bJets_[0]; }
    const math::XYZTLorentzVector bJets2() const { return bJets_[1]; }
    //const math::XYZTLorentzVector bJets3() const { return bJets_[2]; }
    //const math::XYZTLorentzVector bJets4() const { return bJets_[3]; }
   
    void building( const std::vector<cmg::GenJet>* genJets, const reco::GenParticleCollection* genParticles );

    double mass() const { return mass_; }
    double priJPsi3DlTrue() const { return priJPsi3DlTrue_; }
    double secJPsi3DlTrue() const { return secJPsi3DlTrue_; }
    double tbJPsi3DlTrue() const { return tbJPsi3DlTrue_; }
    double tbbJPsi3DlTrue() const { return tbbJPsi3DlTrue_; }
    double priJPsippdlTrue() const { return priJPsippdlTrue_; }
    double secJPsippdlTrue() const { return secJPsippdlTrue_; }
    double tbJPsippdlTrue() const { return tbJPsippdlTrue_; }
    double tbbJPsippdlTrue() const { return tbbJPsippdlTrue_; }
    double tbJPsidthetaTrue() const { return tbJPsidthetaTrue_; }
    double tbbJPsidthetaTrue() const { return tbbJPsidthetaTrue_; }

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
    ///int NbQuarksNoTop() const { return NbQuarksNoTop_ ; }
    int NbQuarks() const { return NbQuarks_ ; }
    int NbQuarks20() const { return NbQuarks20_ ; }
    ///int NcQuarks() const { return NcQuarks_; }
    int NpJPsi() const { return NpJPsi_ ; }
    int NbJPsi() const { return NbJPsi_ ; }
    int NtbJPsi() const { return NtbJPsi_ ; }
    int NtbJPsilp() const { return NtbJPsilp_ ; }
    int NtbJPsilm() const { return NtbJPsilm_ ; }
    int NtbbJPsi() const { return NtbbJPsi_ ; }
    int NtbbJPsilp() const { return NtbbJPsilp_ ; }
    int NtbbJPsilm() const { return NtbbJPsilm_ ; }

    int NbJets(int i=0) const {
      if( i == 0 ) return NbJetsBHad_;
      else return NbJets_ ; 
    }
    int NbJets10(int i=0) const {
      if( i == 0 ) return NbJets10BHad_;
      else return NbJets10_ ; 
    }
    int NbJets15(int i=0) const {
      if( i == 0 ) return NbJets15BHad_;
      else return NbJets15_ ;
    } 
    int NbJets20(int i=0) const {
      if( i == 0 ) return NbJets20BHad_;
      else return NbJets20_ ;
    }
    int NbJets25(int i=0) const {
      if( i == 0 ) return NbJets25BHad_;
      else return NbJets25_ ;
    }
    int NbJets30(int i=0) const {
      if( i == 0 ) return NbJets30BHad_;
      else return NbJets30_ ;
    }

    /*int NcJets(int i=0) const {
      if( i == 0 ) return NcJetsCHad_;
      else return NcJets_ ; 
    }
    int NcJets10(int i=0) const {
      if( i == 0 ) return NcJets10CHad_;
      else return NcJets10_ ;
    }
    int NcJets15(int i=0) const {
      if( i == 0 ) return NcJets15CHad_;
      else return NcJets15_ ;
    }
    int NcJets20(int i=0) const {
      if( i == 0 ) return NcJets20CHad_;
      else return NcJets20_ ;
    }
    int NcJets25(int i=0) const {
      if( i == 0 ) return NcJets25CHad_;
      else return NcJets25_ ;
    }
    int NcJets30(int i=0) const {
      if( i == 0 ) return NcJets30CHad_;
      else return NcJets30_ ;
    }*/

    int NbJetsNoTop() const { return NbJetsNoTop_ ; }
    int NbJets15NoTop() const { return NbJets15NoTop_ ; }
    int NbJets20NoTop() const { return NbJets20NoTop_ ; }
    int NbJets25NoTop() const { return NbJets25NoTop_ ; }
    int NbJets30NoTop() const { return NbJets30NoTop_ ; }

    int NJets() const { return NJets_ ;}
    int NJets10() const { return NJets10_ ;}
    int NJets15() const { return NJets15_ ;}
    int NJets20() const { return NJets20_ ;}
    int NJets25() const { return NJets25_ ;}
    int NJets30() const { return NJets30_ ;}

    //int NbJetJPsi() const { return NbJetJPsi_;}

  private:

    std::vector<const reco::Candidate *> getAncestors(const reco::Candidate &c);
    bool hasBottom(const reco::Candidate &c);
    bool hasCharm(const reco::Candidate &c);
    bool decayFromBHadron(const reco::Candidate &c);
    bool decayFromCHadron(const reco::Candidate &c);
    const reco::Candidate* lastBHadron(const reco::Candidate &c);
    const reco::Candidate* lastCHadron(const reco::Candidate &c);
    bool isLastbottom(const reco::GenParticle&);
    bool isLastcharm(const reco::GenParticle&);
    bool isLastParton(const reco::GenParticle&);
    bool isFromtop(const reco::GenParticle&);
    bool isFromt(const reco::GenParticle&);
    bool isFromtbar(const reco::GenParticle&);
    bool isFrombottom(const reco::GenParticle&);
    int fromWhichTopKind(const reco::GenParticle&);
    double getdthetaTrue( const reco::GenParticle&);
    std::pair<double, double> getJPsidlTrue(const reco::GenParticle&, const int);
    const reco::Candidate* getLast( const reco::Candidate& p );
    double deltaR( const reco::Candidate &pasObj, const reco::Candidate &proObj );


    LorentzVectors tquarks_;
    LorentzVectors bquarks_;
    LorentzVectors leptons_;
    LorentzVectors priJPsi_;
    LorentzVectors secJPsi_;
    LorentzVectors tbJPsi_;
    LorentzVectors tbJPsilp_;
    LorentzVectors tbJPsilm_;
    LorentzVectors tbbJPsi_;
    LorentzVectors tbbJPsilp_;
    LorentzVectors tbbJPsilm_;
   /* LorentzVectors JPsi_;
    LorentzVectors lepJPsi_;
    LorentzVectors JPsiB_;
    LorentzVectors JPsileptonP_;
    LorentzVectors JPsileptonM_;*/
    LorentzVectors nus_;
    LorentzVectors taunus_;
    LorentzVectors bJets_;

    double mass_;
    double priJPsi3DlTrue_;
    double secJPsi3DlTrue_;
    double tbJPsi3DlTrue_;
    double tbbJPsi3DlTrue_;
    double priJPsippdlTrue_;
    double secJPsippdlTrue_;
    double tbJPsippdlTrue_;
    double tbbJPsippdlTrue_;
    double tbJPsidthetaTrue_;
    double tbbJPsidthetaTrue_;

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
    int NbJets10_;
    int NbJets15_;
    int NbJets20_;
    int NbJets25_;
    int NbJets30_;

    int NbJetsBHad_;
    int NbJets10BHad_;
    int NbJets15BHad_;
    int NbJets20BHad_;
    int NbJets25BHad_;
    int NbJets30BHad_;

    int NbJetsNoTop_;
    int NbJets10NoTop_;
    int NbJets15NoTop_;
    int NbJets20NoTop_;
    int NbJets25NoTop_;
    int NbJets30NoTop_;

/*    int NcJets_;
    int NcJets10_;
    int NcJets15_;
    int NcJets20_;
    int NcJets25_;
    int NcJets30_;

    int NcJetsCHad_;
    int NcJets10CHad_;
    int NcJets15CHad_;
    int NcJets20CHad_;
    int NcJets25CHad_;
    int NcJets30CHad_;
*/
    int NbQuarks_;
    ///int NbQuarksNoTop_;
    int NbQuarksTop_;
    int NbQuarks20_;

    ///int NcQuarks_;
    int NpJPsi_;
    int NbJPsi_;
    int NtbJPsi_;
    int NtbJPsilp_;
    int NtbJPsilm_;
    int NtbbJPsi_;
    int NtbbJPsilp_;
    int NtbbJPsilm_;

    int NJets_;
    int NJets10_;
    int NJets15_;
    int NJets20_;
    int NJets25_;
    int NJets30_;
    
    //int NbJetJPsi_;

  };

}
#endif
