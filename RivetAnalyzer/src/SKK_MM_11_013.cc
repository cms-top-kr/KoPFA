// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Tools/Logging.hh"
#include "Rivet/Tools/ParticleIdUtils.hh"
#include "Rivet/RivetAIDA.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/ChargedFinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/LeadingParticlesFinalState.hh"

namespace Rivet {


  /// @brief MC validation analysis for SUSY events
  /// @author Andy Buckley
  class SKK_MM_11_013 : public Analysis {
  public:

    /// Constructor
    SKK_MM_11_013()
      : Analysis("SKK_MM_11_013")
    {  
      setNeedsCrossSection(true);

      _sumwPassedDiLepton = 0;
      _sumwPassedLepJetMET = 0;
      _sumwPassedJetID = 0;
      _sumwPassedWMass = 0;
      _sumw = 0;
    }


    /// @name Analysis methods
    //@{

    // Book histograms
    void init() {
      // Basic final state
      const FinalState fs(-5.0, 5.0, 0*GeV);

      // Tracks and jets

      addProjection(ChargedFinalState(fs), "Tracks");
      addProjection(FastJets(FinalState(-5.0, 5.0, 0*GeV), FastJets::ANTIKT, 0.5), "Jets");

      IdentifiedFinalState mufs(fs);
      mufs.acceptIdPair(MUON);
      addProjection(mufs, "Muons");

      IdentifiedFinalState munufs(fs);
      munufs.acceptIdPair(NU_MU);
      addProjection(munufs, "MuonNus");

      MissingMomentum missing(fs);
      addProjection(missing, "MET");

      LeadingParticlesFinalState lpfs(fs);
      lpfs.addParticleIdPair(MUON);
      lpfs.addParticleIdPair(NU_MU);
      addProjection(lpfs, "LeadingParticles");

//      VetoedFinalState jetinput;
//      jetinput
//          .addVetoOnThisFinalState(munufs);
//      FastJets jetpro(jetinput, FastJets::KT, 0.5);
//      addProjection(jetpro, "Jets");


      // Tracks and jets
/*
      addProjection(ChargedFinalState(FinalState(-2.4, 2.4, 10*GeV)), "Tracks");
      addProjection(FastJets(FinalState(-2.4, 2.4, 0.*GeV), FastJets::ANTIKT, 0.5), "Jets");

      IdentifiedFinalState mufs(-2.4, 2.4, 10*GeV);
      mufs.acceptIdPair(MUON);
      addProjection(mufs, "Muons");

      IdentifiedFinalState munufs(-5.0, 5.0, 10*GeV);
      munufs.acceptIdPair(NU_MU);
      addProjection(munufs, "MuonNus");

      MissingMomentum missing(FinalState(-5.0, 5.0, 10.*GeV));
      addProjection(missing, "MET");

      LeadingParticlesFinalState lpfs(FinalState(-2.4, 2.4, 10*GeV));
      lpfs.addParticleIdPair(MUON);
      lpfs.addParticleIdPair(NU_MU);
      addProjection(lpfs, "LeadingParticles");

//      VetoedFinalState jetinput;
//      jetinput
//          .addVetoOnThisFinalState(munufs);
//      FastJets jetpro(jetinput, FastJets::KT, 0.5);
//      addProjection(jetpro, "Jets");
*/
      _hist_n_mu_nu   = bookHistogram1D("n-mu_nu", 11, -0.5, 10.5);
      _hist_phi_mu_nu = bookHistogram1D("phi-mu_nu", 50, -PI, PI);
      _hist_eta_mu_nu = bookHistogram1D("eta-mu_nu", 50, -4, 4);
      _hist_pt_mu_nu  = bookHistogram1D("pt-mu_nu", 50, 0.0, 500);

      _hist_n_mu   = bookHistogram1D("n-mu", 11, -0.5, 10.5);
      _hist_phi_mu = bookHistogram1D("phi-mu", 50, -PI, PI);
      _hist_eta_mu = bookHistogram1D("eta-mu", 50, -4, 4);
      _hist_pt_mu  = bookHistogram1D("pt-mu", 50, 0.0, 500);

      _hist_mup_lpt  = bookHistogram1D("mup_lpt", 50, 0.0, 500);
      _hist_mum_lpt  = bookHistogram1D("mum_lpt", 50, 0.0, 500);
      _hist_munup_lpt  = bookHistogram1D("munup_lpt", 50, 0.0, 500);
      _hist_munum_lpt  = bookHistogram1D("munum_lpt", 50, 0.0, 500);

      _hist_met = bookHistogram1D("Etmiss", 75, 0.0, 1500);
      _hist_met2 = bookHistogram1D("Etmiss2", 75, 0.0, 1500);
      _hist_met4v = bookHistogram1D("Etmiss4v", 75, 0.0, 00);

      _hist_mll_ossf_mumu = bookHistogram1D("mll-ossf-mumu", 50, 0.0, 500);
      _hist_mll_all_ossf_mumu = bookHistogram1D("mll-all-ossf-mumu", 50, 0.0, 500);
      _hist_mll_2_ossf_mumu = bookHistogram1D("mll-2-ossf-mumu", 50, 0.0, 500);
      _hist_mll_ossf_mmf   = bookHistogram1D("mll-ossf-mmf", 50, 0.0, 500);

      _h_jet_1_pT = bookHistogram1D("jet_1_pT", 50, 0, 500);
      _h_jet_2_pT = bookHistogram1D("jet_2_pT", 50, 0, 500);
      _h_jet_HT   = bookHistogram1D("jet_HT", logspace(1, 2000, 50));

      _h_bjet_1_pT = bookHistogram1D("bjet_1_pT", 50, 0, 500);
      _h_bjet_2_pT = bookHistogram1D("bjet_2_pT", 50, 0, 500);

      _h_njets = bookHistogram1D("mult_jet", 11, -0.5, 10.5);
      _h_njets_0 = bookHistogram1D("mult_jet_nocut", 11, -0.5, 10.5);
      _h_bjets = bookHistogram1D("mult_bjet", 11, -0.5, 10.5);

      _h_bjet_mass = bookHistogram1D("bjet_mass", 50, 0, 1400);
      _h_WW_mass = bookHistogram1D("mass_WW", 80, 0, 800);
      _h_WW_mass2 = bookHistogram1D("mass_WW2", 80, 0, 800);
      _h_WW_mass3 = bookHistogram1D("mass_WW3", 80, 0, 800);
      _h_WW_pT = bookHistogram1D("WW_pT", 50,0,1000);
      _h_ttbar_pT = bookHistogram1D("pT_ttbar", 50, 0, 700);
      _h_ttbar_mass = bookHistogram1D("mass_ttbar", 50, 0, 1400);
      _h_ttbar_mass2 = bookHistogram1D("mass_ttbar2", 50, 0, 1400);
      _h_ttbar_mass3 = bookHistogram1D("mass_ttbar3", 50, 0, 1400);
      _h_ttbar_mass_ref = bookHistogram1D(1, 1, 1);
      _h_ttbar_mass_ref2 = bookHistogram1D(2, 1, 1);
      _h_ttbar_mass_ref3 = bookHistogram1D(3, 1, 1);

      /// @todo LSP eta, pT, phi, mass: no reliable cross-scenario LSP PID but
      /// maybe plot for all of chi^0_1, gravitino, sneutrino, gluino, ... or
      /// identify the LSP as any PID::isSUSY (?) particle with status = 1?
    }


    // Do the analysis
    void analyze(const Event& evt) {
      const FinalState& tracks = applyProjection<FinalState>(evt, "Tracks");
      if (tracks.particles().empty()) {
        getLog() << Log::DEBUG << "Failed multiplicity cut" << endl;
        vetoEvent;
      }

      // Get event weight
      const double weight = evt.weight();
      _sumw += weight;

      // Fill final state muon_neutrino/anti_muon_neutrino hisos
      const FinalState& munufs = applyProjection<FinalState>(evt, "MuonNus");
      _hist_n_mu_nu->fill(munufs.size(), weight);
      vector<FourMomentum> pmunupes, pmunumes;
      foreach (const Particle& munu, munufs.particles()) {
        const FourMomentum& p = munu.momentum();
        _hist_phi_mu_nu->fill(mapAngleMPiToPi(p.phi()), weight);
        _hist_eta_mu_nu->fill(p.eta(), weight);
        _hist_pt_mu_nu->fill(p.pT()/GeV, weight);
        // Add sufficiently hard leptons to collections for m_ll histo
        if (p.pT()/GeV > 20) {
          if (munu.pdgId() == 14) pmunupes += p; else pmunumes += p;
        }
      }

      // Fill final state muon/antimuon histos
      const FinalState& mufs = applyProjection<FinalState>(evt, "Muons");
      _hist_n_mu->fill(mufs.size(), weight);
      vector<FourMomentum> mupluses, muminuses;
      foreach (const Particle& mu, mufs.particles()) {
        const FourMomentum& p = mu.momentum();
        _hist_phi_mu->fill(mapAngleMPiToPi(p.phi()), weight);
        _hist_eta_mu->fill(p.eta(), weight);
        _hist_pt_mu->fill(p.pT()/GeV, weight);
        // Add sufficiently hard leptons to collections for m_ll histo
        if (p.pT()/GeV > 20) {
          if (PID::threeCharge(mu.pdgId()) > 0) mupluses += p; else muminuses += p;
        }
      }

      // Choose highest-pT leptons of each sign and flavour for dilepton mass edges
      const FinalState& lpfs = applyProjection<FinalState>(evt, "LeadingParticles");
      bool muplus_ok(false), muminus_ok(false), munuplus_ok(false), munuminus_ok(false);
      FourMomentum pmunuplus, pmunuminus, pmuplus, pmuminus;
      foreach (const Particle& p, lpfs.particles()) {
        // Only use leptons above 20 GeV
        if (p.momentum().pT()/GeV < 20) continue;
        // Identify the PID
        const PdgId pid = p.pdgId();
        if (pid == MUON) {
          muminus_ok = true;
          pmuminus = p.momentum();
          _hist_mup_lpt->fill(p.momentum().pT()/GeV, weight);
        } else if (pid == ANTIMUON) {
          muplus_ok = true;
          pmuplus = p.momentum();
          _hist_mum_lpt->fill(p.momentum().pT()/GeV, weight);
        } else if (pid == NU_MUBAR) {
          munuminus_ok = true;
          pmunuminus = p.momentum();
          _hist_munum_lpt->fill(p.momentum().pT()/GeV, weight);
        } else if (pid == NU_MU) {
          munuplus_ok = true;
          pmunuplus = p.momentum();
          _hist_munup_lpt->fill(p.momentum().pT()/GeV, weight);
        } else {
          throw Error("Unexpected particle type in leading particles FS!");
        }
      }

      if (!(muminus_ok && munuminus_ok) || !(muplus_ok && munuplus_ok)) {
        MSG_DEBUG("Event failed di-electron multiplicity cut");
        vetoEvent;
      }

      _sumwPassedDiLepton += weight;

      const double m_mumu = FourMomentum(pmuplus + pmuminus).mass();
      const double m_munumunu = FourMomentum(pmunuplus + pmunuminus).Et();
      _hist_mll_ossf_mumu->fill(m_mumu/GeV, weight);
      _hist_met4v->fill(fabs(m_munumunu));
      if (mupluses.size() == 1 && muminuses.size() == 1)
        _hist_mll_2_ossf_mumu->fill(m_mumu/GeV, weight);

//      _sumwPassedDiLepton += weight;

///////////////////////

      // Calculate and fill missing Et histos
      const MissingMomentum& met = applyProjection<MissingMomentum>(evt, "MET");
      FourMomentum missvec(0.0,0.0,0.0,0.0);
      missvec = -met.visibleMomentum(); 
//      double v4met=fabs(missvec.Et());
      missvec.setE(missvec.vector3().mod()); // assume neutrinos are massless
//      MSG_DEBUG("Vector ET = " << met.vectorET()/GeV << " GeV");
//      if (met.vectorET()/GeV < 30) {
//        MSG_DEBUG("Event failed missing ET cut");
//        vetoEvent;
//      }
      _hist_met->fill(met.vectorET()/GeV);

///////////////////////

      const FastJets& jetpro = applyProjection<FastJets>(evt, "Jets");
      const Jets alljets = jetpro.jetsByPt();
      _h_njets_0->fill(alljets.size(), weight);
      if (alljets.size() < 2) {
        MSG_DEBUG("Event failed jet multiplicity cut");
        vetoEvent;
      }
      
      // Update passed-cuts counter and fill all-jets histograms
      _sumwPassedLepJetMET += weight;

//      _h_jet_1_pT->fill(alljets[0].momentum().pT()/GeV, weight);
//      _h_jet_2_pT->fill(alljets[1].momentum().pT()/GeV, weight);

      // Insist that the hardest 4 jets pass pT hardness cuts. If we don't find
      // at least 4 such jets, we abandon this event.
      const Jets jets = jetpro.jetsByPt(30*GeV);
      _h_njets->fill(jets.size(), weight);
      double ht = 0.0;
      foreach (const Jet& j, jets) { ht += j.momentum().pT(); }
      _h_jet_HT->fill(ht/GeV, weight);

      if (jets.size() < 2) {
//          jets[0].momentum().pT() < 60*GeV ||
//          jets[1].momentum().pT() < 40*GeV) {
//        MSG_DEBUG("Event failed jet cuts");
        vetoEvent;
      }

      _hist_met2->fill(met.vectorET()/GeV);

      // Sort the jets into b-jets and light jets. We expect one hard b-jet from
      // each top decay, so our 4 hardest jets should include two b-jets. The
      // Jet::containsBottom() method is equivalent to perfect experimental
      // b-tagging, in a generator-independent way.
      Jets bjets, ljets;
      foreach (const Jet& jet, jets) {
        // // Don't count jets that overlap with the hard leptons
        bool isolated = true;
            //if (deltaR(jet.momentum(), lepton.momentum()) < 0.3) {
            if (deltaR(jet.momentum(), pmuminus) < 0.3 ||deltaR(jet.momentum(), pmuplus) < 0.3) {
            isolated = false;
            break;   
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

      // Plot the pTs of the identified jets.
      _sumwPassedJetID += weight;
      _h_bjet_1_pT->fill(bjets[0].momentum().pT(), weight);
      _h_bjet_2_pT->fill(bjets[1].momentum().pT(), weight);

      FourMomentum WW(10*sqrtS(), 0, 0, 0), WW2(0., 0., 0., 0.), WW3(0., 0., 0., 0.);
          const FourMomentum WWcand = pmuminus + pmuplus + missvec;
          cout << "WWcand = " << WWcand.mass() << " GeV" << endl; 
          if ((pmuplus + pmuminus).mass() > 12) {
            WW = WWcand;
            WW2= pmuminus + pmuplus + pmunuminus + pmunuplus;
            WW3= pmuminus + pmuplus + pmunumes[0] + pmunupes[0];
          } else {
            cout << " Not Good Event ( " << (pmuplus + pmuminus).mass() << " GeV )" << endl;
            vetoEvent;
          }

      const FourMomentum v4_ee = pmuplus + pmuminus;
        double v4m_mm = FourMomentum(pmuplus + pmuminus).mass();
        _hist_mll_ossf_mmf->fill(v4m_mm/GeV, weight);
        _sumwPassedWMass += weight;
        const FourMomentum ttbar = bjets[0].momentum()+bjets[1].momentum()+WW;
        const FourMomentum ttbar2 = bjets[0].momentum()+bjets[1].momentum()+WW2;
        const FourMomentum ttbar3 = bjets[0].momentum()+bjets[1].momentum()+WW3;
        _h_bjet_mass->fill((bjets[0].momentum()+bjets[1].momentum()).mass(), weight);
        _h_WW_mass->fill(WW.mass(), weight);
        _h_WW_mass2->fill(WW2.mass(), weight);
        _h_WW_mass3->fill(WW3.mass(), weight);
        _h_WW_pT->fill(WW.pT(), weight);
        _h_ttbar_pT->fill(ttbar.pT(), weight);
        _h_ttbar_mass->fill(ttbar.mass(), weight);
        _h_ttbar_mass2->fill(ttbar2.mass(), weight);
        _h_ttbar_mass3->fill(ttbar2.mass(), weight);
        _h_ttbar_mass_ref->fill(ttbar.mass(), weight);
        _h_ttbar_mass_ref2->fill(ttbar2.mass(), weight);
        _h_ttbar_mass_ref3->fill(ttbar3.mass(), weight);

///////////////////////
    }

    void finalize() {

//      double norm=crossSection()/sumOfWeights();

      scale(_h_ttbar_mass_ref, 1/_sumwPassedJetID);
      scale(_h_ttbar_mass_ref2, 1/_sumwPassedJetID);
      scale(_h_ttbar_mass_ref3, 1/_sumwPassedJetID);

      cout << "Event weight = " << _sumw << endl;
      cout << "_sumwPassedDiLepton = " << _sumwPassedDiLepton << endl;
      cout << "_sumwPassedLepJetMET = " << _sumwPassedLepJetMET << endl;
      cout << "_sumwPassedJetID = " << _sumwPassedJetID << endl;
      cout << "_sumwPassedWMass = " << _sumwPassedWMass <<endl;

      /// @todo Normalisations
    }

    //@}


  private:

    double _sumwPassedDiLepton, _sumwPassedLepJetMET, _sumwPassedJetID, _sumwPassedWMass, _sumw;

    AIDA::IHistogram1D *_hist_n_mu_nu, *_hist_phi_mu_nu, *_hist_eta_mu_nu, *_hist_pt_mu_nu;
    AIDA::IHistogram1D *_hist_n_mu, *_hist_phi_mu, *_hist_eta_mu, *_hist_pt_mu;
    AIDA::IHistogram1D *_hist_mup_lpt, *_hist_mum_lpt, *_hist_munup_lpt, *_hist_munum_lpt;

    AIDA::IHistogram1D *_hist_n_ees, *_hist_n_els, *_hist_n_pos; 
    AIDA::IHistogram1D *_hist_met;
    AIDA::IHistogram1D *_hist_met2;
    AIDA::IHistogram1D *_hist_met4v;

    AIDA::IHistogram1D *_hist_mll_2_ossf_mumu;
    AIDA::IHistogram1D *_hist_mll_ossf_mumu;
    AIDA::IHistogram1D *_hist_mll_all_ossf_mumu;
    AIDA::IHistogram1D *_hist_mll_ossf_mmf;

    AIDA::IHistogram1D *_h_jet_1_pT, *_h_jet_2_pT, *_h_jet_3_pT, *_h_jet_4_pT;
    AIDA::IHistogram1D *_h_jet_HT;
    AIDA::IHistogram1D *_h_bjet_1_pT, *_h_bjet_2_pT;

    AIDA::IHistogram1D *_h_njets;
    AIDA::IHistogram1D *_h_njets_0;
    AIDA::IHistogram1D *_h_bjets;
    AIDA::IHistogram1D *_h_bjet_mass ;
    AIDA::IHistogram1D *_h_WW_mass ;
    AIDA::IHistogram1D *_h_WW_mass2 ;
    AIDA::IHistogram1D *_h_WW_mass3 ;
    AIDA::IHistogram1D *_h_WW_pT ;
    AIDA::IHistogram1D *_h_ttbar_pT ;
    AIDA::IHistogram1D *_h_ttbar_mass ;
    AIDA::IHistogram1D *_h_ttbar_mass2 ;
    AIDA::IHistogram1D *_h_ttbar_mass3 ;
    AIDA::IHistogram1D *_h_ttbar_mass_ref ;
    AIDA::IHistogram1D *_h_ttbar_mass_ref2 ;
    AIDA::IHistogram1D *_h_ttbar_mass_ref3 ;

  };

  // This global object acts as a hook for the plugin system
  AnalysisBuilder<SKK_MM_11_013> plugin_SKK_MM_11_013;

}
