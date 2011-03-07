#ifndef TTbarEvent_H
#define TTbarEvent_H

#include "DataFormats/Provenance/interface/EventID.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
//#include "DataFormats/PatCandidates/interface/Isolation.h"

#include <algorithm>

namespace Ko
{

class TTbarEvent
{
public:
  TTbarEvent();

  double m() const { return mass_; };
  double mass() const { return m(); };
  double m(const int massAlgoNum) const;
  double mass(const int massAlgoNum) const { return m(massAlgoNum); };
  double zM() const { return zM_; };
  int zSign() const { return l1Sign_ + l2Sign_; };
  double met() const { return met_; };

  double mLLBB() const { return (l1_+l2_+jets_[0]+jets_[1]).M(); };

  double relPFIso1() const { return relPFIso1_; };
  double relPFIso2() const { return relPFIso2_; };
  double relDetIso1() const { return relDetIso1_; };
  double relDetIso2() const { return relDetIso2_; };

  int nJets() const { return jets_.size(); };
  int nJets(const double minPt) const;
  int nJets(const double minPt, const double minBTag, const unsigned int algoNum) const;
  double bTag() const { return -999; }; // dummy function to the next function to be visible
  double bTag(const unsigned int i, const unsigned int algoNum) const;
  std::string algoName(const unsigned int algoNum) const;

  void clear(); // Initialize variables, must be called in every events
  void setEvent(const edm::EventID& eventId); // Set event number, etc
  void setLepton(const reco::Candidate* l1, const reco::Candidate* l2);
  void setMET(const double metX, const double metY);
  void setCorrMET(const double metX, const double metXLower, const double metXUpper,
                  const double metY, const double metYLower, const double metYUpper);
  void addJet(const pat::Jet* jet);
  void addCorrJet(const reco::Candidate::LorentzVector corrJetLVec, const double jecErr);
  void update(); // Finalize input and update internal variables

private:
  // Event variables
  int runNumber_, lumiNumber_, eventNumber_;

  // Leptons
  reco::Candidate::LorentzVector l1_, l2_;
  int l1Sign_, l2Sign_;
  double chIso1_, phIso1_, nhIso1_, relPFIso1_;
  double chIso2_, phIso2_, nhIso2_, relPFIso2_;
  double tkIso1_, ecIso1_, hcIso1_, relDetIso1_;
  double tkIso2_, ecIso2_, hcIso2_, relDetIso2_;

  // Jets
  std::vector<reco::Candidate::LorentzVector> jets_, unCorrJets_;
  std::vector<double> jecErrs_;
  std::vector<std::vector<double> > bTag_;
  std::vector<std::string> algoNames_;

  // Cached variables
  double nGoodJetsPt_, nGoodJetsPtBtag_;
  
  // MET
  double met_, metX_, metY_;
  double unCorrMet_, unCorrMetX_, unCorrMetY_;
  double metXLower_, metXUpper_, metYLower_, metYUpper_;
  
  // Composites
  double zM_;
  double mass_;

  // Mass variables with various algorithms
  double massWithMAOS_, massUser1_, massUser2_;

};


}

#endif

