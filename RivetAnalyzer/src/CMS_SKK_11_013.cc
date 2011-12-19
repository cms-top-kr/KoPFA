#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/AnalysisLoader.hh"
#include "Rivet/RivetAIDA.hh"
#include "Rivet/Tools/Logging.hh"

namespace Rivet {


  class CMS_SKK_11_013 : public Analysis {
  public:

    /// Minimal constructor
    CMS_SKK_11_013() : Analysis("CMS_SKK_11_013")
    {
      _sumwPassedLepJetMET = 0;
      _sumwPassedJetID = 0;
      _sumwPassedWMass = 0;
    }

    /// @name Analysis methods
    //@{

    /// Set up projections and book histograms
    void init() {

      // A FinalState is used to select particles within |eta| < 4.2 and with pT
      // > 30 GeV, out of which the ChargedLeptons projection picks only the
      // electrons and muons, to be accessed later as "LFS".
      addProjection(ChargedLeptons(FinalState(-2.4, 2.4, 20*GeV)), "LFS");
      // A second FinalState is used to select all particles in |eta| < 4.2,
      // with no pT cut. This is used to construct jets and measure missing
      // transverse energy.
      FinalState fs(-2.4, 2.4, 0*GeV);

      MissingMomentum missing(fs);
      addProjection(missing, "MET");

      addProjection(FastJets(fs, FastJets::ANTIKT, 0.5), "Jets");
      //addProjection(MissingMomentum(fs), "MissingET");

      // Booking of histograms
      _h_njets = bookHistogram1D("jet_mult", 11, -0.5, 10.5);
      _h_bjets = bookHistogram1D("bjet_mult", 11, -0.5, 10.5);
      //
      _h_lepton_1_pT = bookHistogram1D("lepton_1_pT", 50, 0, 500);
      _h_jet_1_pT = bookHistogram1D("jet_1_pT", 50, 0, 500);
      _h_jet_2_pT = bookHistogram1D("jet_2_pT", 50, 0, 500);
      _h_jet_3_pT = bookHistogram1D("jet_3_pT", 50, 0, 500);
      _h_jet_4_pT = bookHistogram1D("jet_4_pT", 50, 0, 500);
      _h_jet_HT   = bookHistogram1D("jet_HT", logspace(1, 2000, 50));
      //
      _h_bjet_1_pT = bookHistogram1D("bjet_1_pT", 50, 0, 500);
      _h_bjet_2_pT = bookHistogram1D("bjet_2_pT", 50, 0, 500);
      //
      _h_ljet_1_pT = bookHistogram1D("jetl_1_pT", 50, 0, 500);
      _h_ljet_2_pT = bookHistogram1D("jetl_2_pT", 50, 0, 500);
      //
      _h_W_mass = bookHistogram1D("W_mass", 75, 0, 700);
      _h_t_mass = bookHistogram1D("t_mass", 50, 0, 700);
      _h_t_mass_W_cut = bookHistogram1D("t_mass_W_cut", 75, 0, 700);
      _h_ttbar_mass = bookHistogram1D("ttbar_mass", 50, 0, 1400);
      _h_ttbar_mass_W_cut = bookHistogram1D("ttbar_mass_W_cut", 75, 0, 1400);

      _h_ttbar_mass_ref = bookHistogram1D(1, 1, 1);

      _hist_met1 = bookHistogram1D("Etmiss1", 50, 0.0, 700);
      _hist_met2 = bookHistogram1D("Etmiss2", 50, 0.0, 700);
    }


    void analyze(const Event& event) {
      const double weight = event.weight();

      // Use the "LFS" projection to require at least one hard charged
      // lepton. This is an experimental signature for the leptonically decaying
      // W. This helps to reduce pure QCD backgrounds.
      const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(event, "LFS");
      //const LFS alleptons = lfs.chargedLeptons();
      MSG_DEBUG("Charged lepton multiplicity = " << lfs.chargedLeptons().size());
      foreach (const Particle& lepton, lfs.chargedLeptons()) {
        MSG_DEBUG("Lepton pT = " << lepton.momentum().pT());
      _h_lepton_1_pT->fill(lepton.momentum().pT()/GeV, weight);
      }

      if (lfs.chargedLeptons().empty()) {
        MSG_DEBUG("Event failed lepton multiplicity cut");
        vetoEvent;
      }

      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MET");
      _hist_met1->fill(met.vectorET()/GeV);

      // Use a missing ET cut to bias toward events with a hard neutrino from
      // the leptonically decaying W. This helps to reduce pure QCD backgrounds.
//      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MissingET");
      MSG_DEBUG("Vector ET = " << met.vectorET()/GeV << " GeV");
//      if (met.vectorET().mod() < 30*GeV) {
//      if (met.vectorEt()/GeV < 30) {
      if (met.vectorET()/GeV < 30) {
        MSG_DEBUG("Event failed missing ET cut");
        vetoEvent;
      }

      _hist_met2->fill(met.vectorET()/GeV);

      // Use the "Jets" projection to check that there are at least 4 jets of
      // any pT. Getting the jets sorted by pT ensures that the first jet is the
      // hardest, and so on. We apply no pT cut here only because we want to
      // plot all jet pTs to help optimise our jet pT cut.
      const FastJets& jetpro = applyProjection<FastJets>(event, "Jets");
      const Jets alljets = jetpro.jetsByPt();
      if (alljets.size() < 4) {
        MSG_DEBUG("Event failed jet multiplicity cut");
        vetoEvent;
      }

      // Update passed-cuts counter and fill all-jets histograms
      _sumwPassedLepJetMET += weight;

      _h_jet_1_pT->fill(alljets[0].momentum().pT()/GeV, weight);
      _h_jet_2_pT->fill(alljets[1].momentum().pT()/GeV, weight);
      _h_jet_3_pT->fill(alljets[2].momentum().pT()/GeV, weight);
      _h_jet_4_pT->fill(alljets[3].momentum().pT()/GeV, weight);

      // Insist that the hardest 4 jets pass pT hardness cuts. If we don't find
      // at least 4 such jets, we abandon this event.
      const Jets jets = jetpro.jetsByPt(30*GeV);
      _h_njets->fill(jets.size(), weight);
      double ht = 0.0;
      foreach (const Jet& j, jets) { ht += j.momentum().pT(); }
      _h_jet_HT->fill(ht/GeV, weight);
      if (jets.size() < 4 ||
          jets[0].momentum().pT() < 60*GeV ||
          jets[1].momentum().pT() < 50*GeV ||
          jets[3].momentum().pT() < 30*GeV) {
        MSG_DEBUG("Event failed jet cuts");
        vetoEvent;
      }

      // Sort the jets into b-jets and light jets. We expect one hard b-jet from
      // each top decay, so our 4 hardest jets should include two b-jets. The
      // Jet::containsBottom() method is equivalent to perfect experimental
      // b-tagging, in a generator-independent way.
      Jets bjets, ljets;
      foreach (const Jet& jet, jets) {
        // // Don't count jets that overlap with the hard leptons
        bool isolated = true;
        foreach (const Particle& lepton, lfs.chargedLeptons()) {
          if (deltaR(jet.momentum(), lepton.momentum()) < 0.3) {
            isolated = false;
            break;
          }
        }
        if (!isolated) {
          MSG_DEBUG("Jet failed lepton isolation cut");
          break;
        }
        if (jet.containsBottom()) {
          bjets.push_back(jet);
        } else {
          ljets.push_back(jet);
        }
      }

      _h_bjets->fill(bjets.size(), weight);

      MSG_DEBUG("Number of b-jets = " << bjets.size());
      if (bjets.size() != 2) {
        MSG_DEBUG("Event failed post-lepton-isolation b-tagging cut");
        vetoEvent;
      }
      if (ljets.size() < 2) {
        MSG_DEBUG("Event failed since not enough light jets remaining after lepton-isolation");
        vetoEvent;
      }

      // Plot the pTs of the identified jets.
      _sumwPassedJetID += weight;
      _h_bjet_1_pT->fill(bjets[0].momentum().pT(), weight);
      _h_bjet_2_pT->fill(bjets[1].momentum().pT(), weight);
      _h_ljet_1_pT->fill(ljets[0].momentum().pT(), weight);
      _h_ljet_2_pT->fill(ljets[1].momentum().pT(), weight);

      // Construct the hadronically decaying W momentum 4-vector from pairs of
      // non-b-tagged jets. The pair which best matches the W mass is used. We start
      // with an always terrible 4-vector estimate which should always be "beaten" by
      // a real jet pair.
      FourMomentum W(10*sqrtS(), 0, 0, 0);
      for (size_t i = 0; i < ljets.size()-1; ++i) {
        for (size_t j = i + 1; j < ljets.size(); ++j) {
          const FourMomentum Wcand = ljets[i].momentum() + ljets[j].momentum();
          MSG_TRACE(i << "," << j << ": candidate W mass = " << Wcand.mass()/GeV
                    << " GeV, vs. incumbent candidate with " << W.mass()/GeV << " GeV");
          if (fabs(Wcand.mass() - 80.4*GeV) < fabs(W.mass() - 80.4*GeV)) {
            W = Wcand;
          }
        }
      }
      MSG_DEBUG("Candidate W mass = " << W.mass() << " GeV");

      // There are two b-jets with which this can be combined to make the
      // hadronically decaying top, one of which is correct and the other is
      // not... but we have no way to identify which is which, so we construct
      // both possible top momenta and fill the histograms with both.
      const FourMomentum t1 = W + bjets[0].momentum();
      const FourMomentum t2 = W + bjets[1].momentum();
      const FourMomentum ttbar = t1+t2;
      _h_W_mass->fill(W.mass(), weight);
      _h_t_mass->fill(t1.mass(), weight);
      _h_t_mass->fill(t2.mass(), weight);
      _h_ttbar_mass->fill(ttbar.mass(), weight);

      // Placing a cut on the well-known W mass helps to reduce backgrounds
      if (inRange(W.mass(), 70, 90)) {
        MSG_DEBUG("W found with mass " << W.mass() << " GeV");
        _sumwPassedWMass += weight;
        _h_t_mass_W_cut->fill(t1.mass(), weight);
        _h_t_mass_W_cut->fill(t2.mass(), weight);
        _h_ttbar_mass_W_cut->fill(ttbar.mass(), weight);
        _h_ttbar_mass_ref->fill(ttbar.mass(), weight);
      }

    }

    void finalize() {
      scale(_h_njets, 1/_sumwPassedLepJetMET);
      scale(_h_bjets, 1/_sumwPassedLepJetMET);
      scale(_h_lepton_1_pT, 1/_sumwPassedLepJetMET);
      scale(_h_jet_1_pT, 1/_sumwPassedLepJetMET);
      scale(_h_jet_2_pT, 1/_sumwPassedLepJetMET);
      scale(_h_jet_3_pT, 1/_sumwPassedLepJetMET);
      scale(_h_jet_4_pT, 1/_sumwPassedLepJetMET);
      scale(_h_jet_HT, 1/_sumwPassedLepJetMET);
      //
      scale(_h_bjet_1_pT, 1/_sumwPassedJetID);
      scale(_h_bjet_2_pT, 1/_sumwPassedJetID);
      scale(_h_ljet_1_pT, 1/_sumwPassedJetID);
      scale(_h_ljet_2_pT, 1/_sumwPassedJetID);
      scale(_h_W_mass, 1/_sumwPassedJetID);
      scale(_h_t_mass, 1/_sumwPassedJetID);
      scale(_h_t_mass_W_cut, 1/_sumwPassedWMass);
      scale(_h_ttbar_mass, 1/_sumwPassedJetID);
      scale(_h_ttbar_mass_W_cut, 1/_sumwPassedWMass);
      scale(_h_ttbar_mass_ref, 1/_sumwPassedWMass);
      scale(_hist_met1, 1/_sumwPassedLepJetMET);
      scale(_hist_met2, 1/_sumwPassedLepJetMET);

      cout << "_sumwPassedLepJetMET = " << _sumwPassedLepJetMET << endl;
      cout << "_sumwPassedJetID = " << _sumwPassedJetID << endl;
      cout << "_sumwPassedWMass = " << _sumwPassedWMass <<endl;

    }

    //@}


  private:

    // Passed-cuts counters
    double _sumwPassedLepJetMET, _sumwPassedJetID, _sumwPassedWMass;

    // @name Histogram data members
    //@{

    AIDA::IHistogram1D *_h_njets;
    AIDA::IHistogram1D *_h_bjets;
    AIDA::IHistogram1D *_h_lepton_1_pT;
    AIDA::IHistogram1D *_h_jet_1_pT, *_h_jet_2_pT, *_h_jet_3_pT, *_h_jet_4_pT;
    AIDA::IHistogram1D *_h_jet_HT;
    AIDA::IHistogram1D *_h_bjet_1_pT, *_h_bjet_2_pT;
    AIDA::IHistogram1D *_h_ljet_1_pT, *_h_ljet_2_pT;
    AIDA::IHistogram1D *_h_W_mass;
    AIDA::IHistogram1D *_h_t_mass, *_h_t_mass_W_cut;
    AIDA::IHistogram1D *_h_ttbar_mass, *_h_ttbar_mass_W_cut;
    AIDA::IHistogram1D *_h_ttbar_mass_ref;
    AIDA::IHistogram1D *_hist_met1;
    AIDA::IHistogram1D *_hist_met2;

    //@}

  };

  // The hook for the plugin system
  //DECLARE_RIVET_PLUGIN(CMS_SKK_11_013);
  AnalysisBuilder<CMS_SKK_11_013> plugin_CMS_SKK_11_013;
}
