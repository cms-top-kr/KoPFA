#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/AnalysisLoader.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Tools/ParticleIdUtils.hh"
#include "Rivet/RivetAIDA.hh"

namespace Rivet {

  class MC_TTBAR_ME : public Analysis {

  public:

    MC_TTBAR_ME()
      : Analysis("MC_TTBAR_ME")
    {
      _sumwPassedLep = 0;
      _sumwPassedMET = 0;
      _sumwPassedJet = 0;
      _sumwPassedBJetID = 0;
    }

    /// @name Analysis methods
    //@{

    void init() {

      IdentifiedFinalState mufs(-2.5,2.5,20*GeV);
      mufs.acceptIdPair(MUON);
      addProjection(mufs, "Muons");

      IdentifiedFinalState munufs(-5.0,5.0,0*GeV);
      munufs.acceptIdPair(NU_MU);
      addProjection(munufs, "MuonNus");

      IdentifiedFinalState elfs(-2.5,2.5,20*GeV);
      elfs.acceptIdPair(ELECTRON);
      addProjection(elfs, "Electrons");

      IdentifiedFinalState elnufs(-5.0,5.0,0*GeV);
      elnufs.acceptIdPair(NU_MU);
      addProjection(elnufs, "ElectronNus");

      // Final state for jets, mET etc.
      const FinalState fs(-2.5, 2.5);
      addProjection(fs, "FS");
      // Veto neutrinos, and muons with pT above 1.0 GeV
      VetoedFinalState vfs(fs);
      vfs.vetoNeutrinos();
      vfs.addVetoPairDetail(MUON, 20.0*GeV, MAXDOUBLE);
      addProjection(vfs, "VFS");
      addProjection(FastJets(vfs, FastJets::ANTIKT, 0.5), "Jets");
      addProjection(MissingMomentum(vfs), "MissingET");

      addProjection(ChargedLeptons(FinalState(-2.5, 2.5, 20*GeV)), "LFS");

      _h_nleps = bookHistogram1D("lep_multi", 11, -0.5, 10.5);

      _h_lep_1_pT = bookHistogram1D("lep_1_pT", 50, 0, 500);
      _h_lep_2_pT = bookHistogram1D("lep_2_pT", 50, 0, 500);

      _h_chleps = bookHistogram1D("lep_charge", 11, -5.5, 5.5);

      _h_met = bookHistogram1D("met", 50, 0, 1500);

      _h_njets = bookHistogram1D("jet_multi_all", 11, -0.5, 10.5);
      _h_bjets = bookHistogram1D("jet_multi_b", 11, -0.5, 10.5);

      _h_jet_1_pT = bookHistogram1D("jet_1_pT", 50, 0, 500);
      _h_jet_2_pT = bookHistogram1D("jet_2_pT", 50, 0, 500);

      _h_bjet_1_pT = bookHistogram1D("jetb_1_pT", 50, 0, 500);
      _h_bjet_2_pT = bookHistogram1D("jetb_2_pT", 50, 0, 500);

      _h_ttbar1_mass = bookHistogram1D("ttbar1_mass", 75, 0, 1400);
      _h_ttbar2_mass = bookHistogram1D("ttbar2_mass", 22, 200, 1400);
    }


    void analyze(const Event& event) {
      const double weight = event.weight();

      const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(event, "LFS");
      MSG_DEBUG("Charged lepton multiplicity = " << lfs.chargedLeptons().size());
      foreach (Particle lepton, lfs.chargedLeptons()) {
        MSG_DEBUG("Lepton pT = " << lepton.momentum().pT());
      }
      if (lfs.chargedLeptons().size() < 1) {
        MSG_DEBUG("Event failed lepton multiplicity cut");
        vetoEvent;
      }
      const ParticleVector sortedMuons = applyProjection<IdentifiedFinalState>(event, "Muons").particlesByPt();
      const ParticleVector sortedElectrons = applyProjection<IdentifiedFinalState>(event, "Electrons").particlesByPt();
      const ParticleVector sortedMuonNus = applyProjection<IdentifiedFinalState>(event, "MuonNus").particlesByPt();
      const ParticleVector sortedElectronNus = applyProjection<IdentifiedFinalState>(event, "ElectronNus").particlesByPt();

      MSG_DEBUG("Muon multiplicity = " << sortedMuons.size());
      foreach (Particle mu, sortedMuons ) {
        MSG_DEBUG("Muon pT = " << mu.momentum().pT());
      }
      if ( sortedMuons.size() < 1) {
        MSG_DEBUG("Event failed muon multiplicity cut");
        vetoEvent;
      }

      MSG_DEBUG("Electron multiplicity = " << sortedElectrons.size());
      foreach (Particle el, sortedElectrons ) {
        MSG_DEBUG("Electron pT = " << el.momentum().pT());
      }
      if ( sortedElectrons.size() < 1) {
        MSG_DEBUG("Event failed muon multiplicity cut");
        vetoEvent;
      }

      int chlep1 = PID::threeCharge(sortedMuons[0]) ;
      _h_chleps->fill(chlep1, weight);
      int chlep2 = PID::threeCharge(sortedElectrons[0]) ;
      _h_chleps->fill(chlep2, weight);
      int chleps = chlep1*chlep2/9 ;
      _h_chleps->fill(chleps, weight);

      if ( chleps >= 0) {
        MSG_DEBUG("Event failed opposite sign cut");
        vetoEvent;
      }

      _sumwPassedLep += weight;

      int lepsize= sortedMuons.size()+sortedElectrons.size();
      _h_nleps->fill(lepsize, weight);
      _h_lep_1_pT->fill(sortedMuons[0].momentum().pT(), weight);
      _h_lep_2_pT->fill(sortedElectrons[0].momentum().pT(), weight);

      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MissingET");
      MSG_DEBUG("Vector ET  =" << met.visibleMomentum().perp() << " GeV");
/*      if ( met.visibleMomentum().perp() < 30*GeV) {
        MSG_DEBUG("Event failed missing ET cut");
        vetoEvent;
      }*/

      _sumwPassedMET += weight;

      FourMomentum missvec(0.0,0.0,0.0,0.0);
      missvec = -met.visibleMomentum(); 
      missvec.setPz(0.0); // no information about Pz
      missvec.setE(missvec.perp()); // assume neutrinos are massless
      _h_met->fill(missvec.perp(), weight);

      const FastJets& jetpro = applyProjection<FastJets>(event, "Jets");
      const Jets alljets = jetpro.jetsByPt();
      if (alljets.size() < 2) {
        MSG_DEBUG("Event failed jet multiplicity cut");
        vetoEvent;
      }

      _h_jet_1_pT->fill(alljets[0].momentum().pT(), weight);
      _h_jet_2_pT->fill(alljets[1].momentum().pT(), weight);

      const Jets jets = jetpro.jetsByPt(30*GeV);
      _h_njets->fill(jets.size(), weight);
      foreach (const Jet& jet, jets) {
        MSG_DEBUG("Jet pT = " << jet.momentum().pT()/GeV << " GeV");
      }
      if (jets.size() < 2) {
        MSG_DEBUG("Event failed jet pT cut");
        vetoEvent;
      }

      _sumwPassedJet += weight;

      Jets bjets;
      foreach (const Jet& jet, jets) {
        if (jet.containsBottom()) {
          bjets.push_back(jet);
        } 
      }

      _h_bjets->fill(bjets.size(), weight);

      MSG_DEBUG("Number of b-jets = " << bjets.size());
      if (bjets.size() != 2) {
        MSG_DEBUG("Event failed b-tagging cut");
        vetoEvent;
      }

      _sumwPassedBJetID += weight;

      _h_bjet_1_pT->fill(bjets[0].momentum().pT(), weight);
      _h_bjet_2_pT->fill(bjets[1].momentum().pT(), weight);

      const FourMomentum ttbar = bjets[0].momentum() + bjets[1].momentum() + sortedMuons[0].momentum() + sortedElectrons[0].momentum() + missvec ;

      double m_tt=ttbar.mass();
      _h_ttbar1_mass->fill(m_tt, weight);
      _h_ttbar2_mass->fill(m_tt, weight);
    }


    void finalize() {
      // No histos, so nothing to do!
      cout << "_sumwPassedLep = " << _sumwPassedLep << endl;
      cout << "_sumwPassedMET = " << _sumwPassedMET << endl;
      cout << "_sumwPassedJet = " << _sumwPassedJet << endl;
      cout << "_sumwPassedBJetID = " << _sumwPassedBJetID << endl;
    }

    //@}


  private:

    double _sumwPassedLep, _sumwPassedMET, _sumwPassedJet, _sumwPassedBJetID;

    AIDA::IHistogram1D *_h_nleps;
    AIDA::IHistogram1D *_h_lep_1_pT, *_h_lep_2_pT;
    AIDA::IHistogram1D *_h_chleps;
    AIDA::IHistogram1D *_h_met;
    AIDA::IHistogram1D *_h_njets, *_h_bjets;
    AIDA::IHistogram1D *_h_jet_1_pT, *_h_jet_2_pT;
    AIDA::IHistogram1D *_h_bjet_1_pT, *_h_bjet_2_pT;
    AIDA::IHistogram1D *_h_ttbar1_mass, *_h_ttbar2_mass;

  };

  // This global object acts as a hook for the plugin system
  AnalysisBuilder<MC_TTBAR_ME> plugin_MC_TTBAR_ME;

}

