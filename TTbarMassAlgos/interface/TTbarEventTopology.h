#ifndef KoPFA_MassAlgos_TTbarEventTopology_H
#define KoPFA_MassAlgos_TTbarEventTopology_H

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/METReco/interface/MET.h"

#include <TLorentzVector.h>

#include "TopQuarkAnalysis/TopKinFitter/interface/TtFullLepKinSolver.h"

class TTbarEventTopology
{
public:
  TTbarEventTopology();
  ~TTbarEventTopology();

  void set(const reco::Candidate* l1, const reco::Candidate* l2,
           const reco::Jet* j1, const reco::Jet* j2,
           const reco::MET* met);
  void setMetErr(const double metErr) { metErr_ = metErr; };
  void solve();

  reco::Candidate::LorentzVector vsum();
  reco::Candidate::LorentzVector nwt();
  reco::Candidate::LorentzVector maos();
  reco::Candidate::LorentzVector kin();
  double symb() { return m_symb_; };

  double mt2_maos() { return mt2_maos_; };

public:
  reco::Candidate::LorentzVector l1_, l2_;
  reco::Candidate::LorentzVector j1_, j2_;
  reco::Candidate::LorentzVector met_;

  // Errors
  double metErr_;

  // Cache
  reco::Candidate::LorentzVector vis11_, vis12_, vis21_, vis22_;

  // Solutions
  reco::Candidate::LorentzVector nu1_maos_, nu2_maos_;
  reco::Candidate::LorentzVector nu1_nwt_, nu2_nwt_;
  reco::Candidate::LorentzVector nu1_kin_, nu2_kin_;

  int combination_maos_;
  int combination_nwt_;
  int combination_kin_;
  double mt2_maos_;
  double m_symb_;
  double weight_kin_;

private:
  void solveNWT();
  void solveMAOS();
  void solveSymbolic();
  void solveKin();

  void solveNu(const double eta, const double mTop,
               const reco::Candidate::LorentzVector& lep,
               const reco::Candidate::LorentzVector& jet,
               std::vector<reco::Candidate::LorentzVector>& nu); 

  TLorentzVector convLV(const reco::Candidate::LorentzVector& lv)
  {
    return TLorentzVector(lv.px(), lv.py(), lv.pz(), lv.e());
  };

  reco::Candidate::LorentzVector convLV(const TLorentzVector& lv)
  {
    return reco::Candidate::LorentzVector(lv.Px(), lv.Py(), lv.Pz(), lv.E());
  };

  inline const double sqr(const double x) { return x*x; };

private:
  TtFullLepKinSolver* kinSolver_;

};

#endif

