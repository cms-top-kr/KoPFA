#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/AnalysisLoader.hh"
#include "Rivet/RivetAIDA.hh"


namespace Rivet {

  class MC_TTBAR_DILEPTON : public Analysis {

  public:

    MC_TTBAR_DILEPTON()
      : Analysis("MC_TTBAR_DILEPTON")
    {
      _sumwPassedLepJetMET = 0;
      _sumwPassedJetID = 0;
      _sumwPassedWMass = 0;
    
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

      addProjection(ChargedLeptons(FinalState(-2.5, 2.5, 20*GeV)), "LFS");
      addProjection(FastJets(FinalState(-5.0, 5.0, 0*GeV), FastJets::ANTIKT, 0.5), "Jets");

      _h_njets = bookHistogram1D("mult_alljet", 11, -0.5, 10.5);
      _h_bjets = bookHistogram1D("mult_bjet", 11, -0.5, 10.5);

      _h_jet_1_pT = bookHistogram1D("jet_1_pT", 50, 0, 500);
      _h_jet_2_pT = bookHistogram1D("jet_2_pT", 50, 0, 400);

      _h_bjet_1_pT = bookHistogram1D("jetb_1_pT", 50, 0, 250);
      _h_bjet_2_pT = bookHistogram1D("jetb_2_pT", 50, 0, 250);

      _h_ttbar_mass = bookHistogram1D("ttbar_mass", 75, 0, 1400);
    }


    void analyze(const Event& event) {
      const double weight = event.weight();

      const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(event, "LFS");
      MSG_DEBUG("Charged lepton multiplicity = " << lfs.chargedLeptons().size());
      foreach (Particle lepton, lfs.chargedLeptons()) {
        MSG_DEBUG("Lepton pT = " << lepton.momentum().pT());
      }
      if (lfs.chargedLeptons().size() < 2) {
        MSG_DEBUG("Event failed lepton multiplicity cut");
        vetoEvent;
      }

      const ParticleVector sortedMuons = applyProjection<IdentifiedFinalState>(event, "Muons").particlesByPt();
      const ParticleVector sortedElectrons = applyProjection<IdentifiedFinalState>(event, "Muons").particlesByPt();
      const ParticleVector sortedMuonNus = applyProjection<IdentifiedFinalState>(event, "MuonNus").particlesByPt();
      const ParticleVector sortedElectronNus = applyProjection<IdentifiedFinalState>(event, "MuonNus").particlesByPt();

      MSG_DEBUG("Muon multiplicity = " << sortedMuons.size());
      foreach (Particle mu, sortedMuons ) {
        MSG_DEBUG("Muon pT = " << mu.momentum().pT());
      }
      if ( sortedMuons.size() < 2) {
        MSG_DEBUG("Event failed muon multiplicity cut");
        vetoEvent;
      }
      if ( sortedMuonNus.size() < 2) {
        MSG_DEBUG("Event failed muon neutrino multiplicity cut");
        vetoEvent;
      }

     
      const FastJets& jetpro = applyProjection<FastJets>(event, "Jets");
      const Jets alljets = jetpro.jetsByPt();
      if (alljets.size() < 2) {
        MSG_DEBUG("Event failed jet multiplicity cut");
        vetoEvent;
      }
      _sumwPassedLepJetMET += weight;
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
      _sumwPassedJetID += weight;
      _h_bjet_1_pT->fill(bjets[0].momentum().pT(), weight);
      _h_bjet_2_pT->fill(bjets[1].momentum().pT(), weight);

      const FourMomentum ttbar = bjets[0].momentum() + bjets[1].momentum() + sortedMuons[0].momentum() + sortedMuons[1].momentum() + sortedMuonNus[0].momentum() + sortedMuonNus[1].momentum() ;

      _h_ttbar_mass->fill(ttbar.mass(), weight);

    }


    void finalize() {
      // No histos, so nothing to do!
      cout << "_sumwPassedLepJetMET = " << _sumwPassedLepJetMET << endl;
      cout << "_sumwPassedJetID = " << _sumwPassedJetID << endl;
    }

    //@}


  private:

    double _sumwPassedLepJetMET, _sumwPassedJetID, _sumwPassedWMass;

    AIDA::IHistogram1D *_h_njets, *_h_bjets;
    AIDA::IHistogram1D *_h_jet_1_pT, *_h_jet_2_pT;
    AIDA::IHistogram1D *_h_bjet_1_pT, *_h_bjet_2_pT;
    AIDA::IHistogram1D *_h_ttbar_mass;

  };


  // This global object acts as a hook for the plugin system
  AnalysisBuilder<MC_TTBAR_DILEPTON> plugin_MC_TTBAR_DILEPTON;

}


