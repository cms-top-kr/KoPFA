#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "KoPFA/TTbarMassAlgos/interface/TTbarEventTopology.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TMath.h"

#include <memory>
#include <vector>

using namespace std;
using namespace edm;
using namespace reco;

class TTbarMassAnalyzer : public edm::EDAnalyzer
{
public:
  TTbarMassAnalyzer(const edm::ParameterSet& pset);
  ~TTbarMassAnalyzer() {};

  virtual void beginJob();
  virtual void endJob() {};
  virtual void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);

private:
  edm::InputTag lepton1Label_;
  edm::InputTag lepton2Label_;
  edm::InputTag jetLabel_;
  edm::InputTag metLabel_;
  std::string genTTbarName_;

  TTbarEventTopology eventTopology_;
  bool isSameCollection_;

private:
  TH1F* hmTT_vsum_;
  TH1F* hmTT_symb_;
  TH1F* hmTT_maos_;
  TH1F* hmTT_nwt_;
  TH1F* hmTT_kin_;

  // MC matched
  TH1F* hmTT_true_;
  TH1F* hmTopA_true_;
  TH1F* hmTopB_true_;
  TH1F* hmTopA_ljnu_;
  TH1F* hmTopB_ljnu_;
  TH1F* hmTopA_lbnu_;
  TH1F* hmTopB_lbnu_;
  TH1F* hmWA_lnu_;
  TH1F* hmWB_lnu_;

  TH1F* hmTopA_ljnuMaos_;
  TH1F* hmTopB_ljnuMaos_;

  // Top mass from reconstruction methods
  TH1F* hmt2_maos_;
  TH1F* hmTop_nwt_;
  TH1F* hmTop_kin_;

  // Wrong association
  TH1F* hmTopA_lbnuWrong_;
  TH1F* hmTopB_lbnuWrong_;
  TH1F* hmTopA_ljnuWrong_;
  TH1F* hmTopB_ljnuWrong_;

  TH1F* hmTopA_ljnuMaosWrong_;
  TH1F* hmTopB_ljnuMaosWrong_;

  // Response matrix
  TH2F* hmTTRVsT_vsum_;
  TH2F* hmTTRVsT_symb_;
  TH2F* hmTTRVsT_maos_;
  TH2F* hmTTRVsT_nwt_;
  TH2F* hmTTRVsT_kin_;

  // Error
  TH1F* hmTTRes_vsum_;
  TH1F* hmTTRes_symb_;
  TH1F* hmTTRes_maos_;
  TH1F* hmTTRes_nwt_;
  TH1F* hmTTRes_kin_;
};

TTbarMassAnalyzer::TTbarMassAnalyzer(const edm::ParameterSet& pset)
{
  lepton1Label_ = pset.getParameter<edm::InputTag>("lepton1");
  lepton2Label_ = pset.getParameter<edm::InputTag>("lepton2");
  jetLabel_ = pset.getParameter<edm::InputTag>("jet");
  metLabel_ = pset.getParameter<edm::InputTag>("met");

  genTTbarName_ = pset.getUntrackedParameter<std::string>("genTTbar", "");

  isSameCollection_ = (lepton1Label_.encode() == lepton2Label_.encode());

}

void TTbarMassAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;

  hmTT_vsum_ = fs->make<TH1F>("hmTT_vsum", "Vector sum;Mass [GeV/c^{2}];Events per 1GeV", 1000, 0, 1000);
  hmTT_symb_ = fs->make<TH1F>("hmTT_symb", "Symbolic algebra;Mass [GeV/c^{2}];Events per 1GeV", 1000, 0, 1000);
  hmTT_maos_ = fs->make<TH1F>("hmTT_maos", "MAOS;Mass [GeV/c^{2}];Events per 1GeV", 1000, 0, 1000);
  hmTT_nwt_ = fs->make<TH1F>("hmTT_nwt", "NWT;Mass [GeV/c^{2}];Events per 1GeV", 1000, 0, 1000);
  hmTT_kin_ = fs->make<TH1F>("hmTT_kin", "KIN;Mass [GeV/c^{2}];Events per 1GeV", 1000, 0, 1000);

  hmt2_maos_ = fs->make<TH1F>("hmt2_maos", "MAOS M_{T2};Stransverse mass [GeV/c^{2}];Events per 1GeV", 300, 0, 300);
  hmTop_nwt_ = fs->make<TH1F>("hmTop_nwt", "NWT top mass;Mass [GeV/c^{2}];Events per 1GeV", 300, 0, 300);
  hmTop_kin_ = fs->make<TH1F>("hmTop_kin", "KIN top mass;Mass [GeV/c^{2}];Events per 1GeV", 300, 0, 300);

  hmTT_true_ = fs->make<TH1F>("hmTT_true", "MC truth;Mass [GeV/c^{2}];Events per 1GeV", 1000, 0, 1000);
  hmTopA_true_ = fs->make<TH1F>("hmTopA_true", "MC truth top mass;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  hmTopB_true_ = fs->make<TH1F>("hmTopB_true", "MC truth anti-top mass;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  hmTopA_lbnu_ = fs->make<TH1F>("hmTopA_lbnu", "MC matched top mass;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  hmTopB_lbnu_ = fs->make<TH1F>("hmTopB_lbnu", "MC matched anti-top mass;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  hmTopA_ljnu_ = fs->make<TH1F>("hmTopA_ljnu", "MC matched top mass with Jet;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  hmTopB_ljnu_ = fs->make<TH1F>("hmTopB_ljnu", "MC matched anti-top mass with Jet;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  
  hmTopA_ljnuMaos_ = fs->make<TH1F>("hmTopA_ljnuMaos", "MC matched Maos top mass with Jet;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  hmTopB_ljnuMaos_ = fs->make<TH1F>("hmTopB_ljnuMaos", "MC matched Maos anti-top mass with Jet;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);

  hmWA_lnu_ = fs->make<TH1F>("hmWA_lnu", "MC matched l^{+}+#nu mass;Mass [GeV/c^{2}];Events per 1GeV", 80, 40, 120);
  hmWB_lnu_ = fs->make<TH1F>("hmWB_lnu", "MC matched l^{-}+#nu mass;Mass [GeV/c^{2}];Events per 1GeV", 80, 40, 120);

  hmTopA_lbnuWrong_ = fs->make<TH1F>("hmTopA_lbnuWrong", "Wrong pairing of l^{+}#nub mass;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  hmTopB_lbnuWrong_ = fs->make<TH1F>("hmTopB_lbnuWrong", "Wrong pairing of l^{-}#nub mass;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  hmTopA_ljnuWrong_ = fs->make<TH1F>("hmTopA_ljnuWrong", "Wrong pairing of l^{+}#nujet mass;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  hmTopB_ljnuWrong_ = fs->make<TH1F>("hmTopB_ljnuWrong", "Wrong pairing of l^{-}#nujet mass;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);

  hmTopA_ljnuMaosWrong_ = fs->make<TH1F>("hmTopA_ljnuMaosWrong", "Wrong pairing of l^{+}#nujet maos mass;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);
  hmTopB_ljnuMaosWrong_ = fs->make<TH1F>("hmTopB_ljnuMaosWrong", "Wrong pairing of l^{-}#nujet maos mass;Mass [GeV/c^{2}];Events per 1GeV", 120, 100, 240);

  hmTTRVsT_vsum_ = fs->make<TH2F>("hmTTRVsT_vsum", "Reco vs MC truth m(t#bar{t}) : Vector sum;MC truth mass [GeV/c^{2}];Reco mass [GeV/c^{2}]", 80, 200, 1000, 80, 200, 1000);
  hmTTRVsT_symb_ = fs->make<TH2F>("hmTTRVsT_symb", "Reco vs MC truth m(t#bar{t}) : Symbolic algebra;MC truth mass [GeV/c^{2}];Reco mass [GeV/c^{2}]", 80, 200, 1000, 80, 200, 1000);
  hmTTRVsT_maos_ = fs->make<TH2F>("hmTTRVsT_maos", "Reco vs MC truth m(t#bar{t}) : MAOS;MC truth mass [GeV/c^{2}];Reco mass [GeV/c^{2}]", 80, 200, 1000, 80, 200, 1000);
  hmTTRVsT_nwt_ = fs->make<TH2F>("hmTTRVsT_nwt", "Reco vs MC truth m(t#bar{t}) : NWT;MC truth mass [GeV/c^{2}];Reco mass [GeV/c^{2}]", 80, 200, 1000, 80, 200, 1000);
  hmTTRVsT_kin_ = fs->make<TH2F>("hmTTRVsT_kin", "Reco vs MC truth m(t#bar{t}) : Kin;MC truth mass [GeV/c^{2}];Reco mass [GeV/c^{2}]", 80, 200, 1000, 80, 200, 1000);

  hmTTRes_vsum_ = fs->make<TH1F>("hmTTRes_vsum", "Reco-MC truth m(t#bar{t}) : Vector sum;Mass difference [GeV/c^{2}];Events per 1GeV", 600, -300, 300);
  hmTTRes_symb_ = fs->make<TH1F>("hmTTRes_symb", "Reco-MC truth m(t#bar{t}) : Symbolic algebra;Mass difference [GeV/c^{2}];Events per 1GeV", 600, -300, 300);
  hmTTRes_maos_ = fs->make<TH1F>("hmTTRes_maos", "Reco-MC truth m(t#bar{t}) : MAOS;Mass difference [GeV/c^{2}];Events per 1GeV", 600, -300, 300);
  hmTTRes_nwt_ = fs->make<TH1F>("hmTTRes_nwt", "Reco-MC truth m(t#bar{t}) : NWT;Mass difference [GeV/c^{2}];Events per 1GeV", 600, -300, 300);
  hmTTRes_kin_ = fs->make<TH1F>("hmTTRes_kin", "Reco-MC truth m(t#bar{t}) : Kin;Mass difference [GeV/c^{2}];Events per 1GeV", 600, -300, 300);

  hmTTRVsT_vsum_->SetOption("COLZ");
  hmTTRVsT_symb_->SetOption("COLZ");
  hmTTRVsT_maos_->SetOption("COLZ");
  hmTTRVsT_nwt_->SetOption("COLZ");
  hmTTRVsT_kin_->SetOption("COLZ");

}

void TTbarMassAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  // Pick leading leptons
  // Manual sorting is necessary in case of genParticles
  const reco::Candidate* lepton1 = 0;
  const reco::Candidate* lepton2 = 0;
  if ( !isSameCollection_ )
  {
    edm::Handle<edm::View<reco::Candidate> > lepton1Handle;
    edm::Handle<edm::View<reco::Candidate> > lepton2Handle;

    event.getByLabel(lepton1Label_, lepton1Handle);
    event.getByLabel(lepton2Label_, lepton2Handle);

    for ( int i=0, n=lepton1Handle->size(); i<n; ++i )
    {
      const reco::Candidate* l = &lepton1Handle->at(i);
      if ( !lepton1 or lepton1->pt() < l->pt() ) lepton1 = l;
    }
    for ( int i=0, n=lepton2Handle->size(); i<n; ++i )
    {
      const reco::Candidate* l = &lepton2Handle->at(i);
      if ( !lepton2 or lepton2->pt() < l->pt() ) lepton2 = l;
    }
  }
  else
  {
    edm::Handle<edm::View<reco::Candidate> > lepton1Handle;

    event.getByLabel(lepton1Label_, lepton1Handle);

    for ( int i=0, n=lepton1Handle->size(); i<n; ++i )
    {
      const reco::Candidate* l = &lepton1Handle->at(i);
      if ( !lepton2 or lepton2->pt() < l->pt() ) lepton2 = l;
      if ( !lepton1 or lepton1->pt() < lepton2->pt() ) std::swap(lepton1, lepton2);
    }
  }
  if ( !lepton1 or !lepton2 ) return;

  edm::Handle<edm::View<reco::MET> > metHandle;
  event.getByLabel(metLabel_, metHandle);
  const reco::MET* met = &metHandle->at(0);

  // Pick leading dijets
  const reco::Jet* jet1 = 0;
  const reco::Jet* jet2 = 0;
  edm::Handle<edm::View<reco::Jet> > jetHandle;
  event.getByLabel(jetLabel_, jetHandle);
  if ( jetHandle->size() < 2 ) return;

  jet1 = &jetHandle->at(0);
  jet2 = &jetHandle->at(1);

  eventTopology_.set(lepton1, lepton2, jet1, jet2, met);
  eventTopology_.setMetErr(8.7);
  eventTopology_.solve();

  const double m_vsum = eventTopology_.vsum().mass();
  const double m_symb = eventTopology_.symb();
  const double m_maos = eventTopology_.maos().mass();
  const double m_nwt = eventTopology_.nwt().mass();
  const double m_kin = eventTopology_.kin().mass();

  hmTT_vsum_->Fill(m_vsum);
  hmTT_symb_->Fill(m_symb);

  if ( eventTopology_.mt2_maos() > 3 )
  {
    hmTT_maos_->Fill(m_maos);
    hmt2_maos_->Fill(eventTopology_.mt2_maos());
  }

  if ( eventTopology_.combination_nwt_ != 0 )
  {
    hmTT_nwt_->Fill(m_nwt);
    //hweight_nwt_->Fill(eventTopology_.weight_nwt_);
    if ( eventTopology_.combination_nwt_ == 1 )
    {
      hmTop_nwt_->Fill((eventTopology_.vis11_+eventTopology_.nu1_nwt_).mass());
      hmTop_nwt_->Fill((eventTopology_.vis22_+eventTopology_.nu2_nwt_).mass());
    }
    else if ( eventTopology_.combination_nwt_ == -1 )
    {
      hmTop_nwt_->Fill((eventTopology_.vis12_+eventTopology_.nu1_nwt_).mass());
      hmTop_nwt_->Fill((eventTopology_.vis21_+eventTopology_.nu2_nwt_).mass());
    }
  }

  if ( eventTopology_.combination_kin_ != 0 )
  {
    hmTT_kin_->Fill(m_kin);
    //hweight_kin_->Fill(eventTopology_.weight_kin_);
    if ( eventTopology_.combination_kin_ == 1 )
    {
      hmTop_kin_->Fill((eventTopology_.vis11_+eventTopology_.nu1_kin_).mass());
      hmTop_kin_->Fill((eventTopology_.vis22_+eventTopology_.nu2_kin_).mass());
    }
    else if ( eventTopology_.combination_kin_ == -1 )
    {
      hmTop_kin_->Fill((eventTopology_.vis12_+eventTopology_.nu1_kin_).mass());
      hmTop_kin_->Fill((eventTopology_.vis21_+eventTopology_.nu2_kin_).mass());
    }
  }

  // Generator level truth
  if ( lepton1 and lepton2 and jet1 and jet2 and ! genTTbarName_.empty() )
  {
    edm::Handle<reco::GenParticleCollection> lAHandle;
    edm::Handle<reco::GenParticleCollection> lBHandle;
    edm::Handle<reco::GenParticleCollection> vAHandle;
    edm::Handle<reco::GenParticleCollection> vBHandle;
    edm::Handle<reco::GenParticleCollection> bAHandle;
    edm::Handle<reco::GenParticleCollection> bBHandle;

    event.getByLabel(edm::InputTag(genTTbarName_ , "lA"), lAHandle);
    event.getByLabel(edm::InputTag(genTTbarName_ , "lB"), lBHandle);
    event.getByLabel(edm::InputTag(genTTbarName_ , "vA"), vAHandle);
    event.getByLabel(edm::InputTag(genTTbarName_ , "vB"), vBHandle);
    event.getByLabel(edm::InputTag(genTTbarName_ , "bA"), bAHandle);
    event.getByLabel(edm::InputTag(genTTbarName_ , "bB"), bBHandle);

    if ( ! lAHandle->empty() and ! lBHandle->empty() and
         ! vAHandle->empty() and ! vBHandle->empty() and
         ! bAHandle->empty() and ! bBHandle->empty() )
    {
      const reco::Candidate::LorentzVector lALVec = lAHandle->at(0).p4();
      const reco::Candidate::LorentzVector lBLVec = lBHandle->at(0).p4();
      const reco::Candidate::LorentzVector vALVec = vAHandle->at(0).p4();
      const reco::Candidate::LorentzVector vBLVec = vBHandle->at(0).p4();
      const reco::Candidate::LorentzVector bALVec = bAHandle->at(0).p4();
      const reco::Candidate::LorentzVector bBLVec = bBHandle->at(0).p4();

      const double m_true = (lALVec+lBLVec+vALVec+vBLVec+bALVec+bBLVec).mass();
      hmTT_true_->Fill(m_true);
      hmTopA_true_->Fill((lALVec+vALVec+bALVec).mass());
      hmTopB_true_->Fill((lBLVec+vBLVec+bBLVec).mass());

      // Truth matching : leptons
      const double dRl_A1 = deltaR(lALVec, lepton1->p4());
      const double dRl_A2 = deltaR(lALVec, lepton2->p4());
      const double dRl_B1 = deltaR(lBLVec, lepton1->p4());
      const double dRl_B2 = deltaR(lBLVec, lepton2->p4());

      reco::Candidate::LorentzVector leptonA, leptonB;
      if ( TMath::Hypot(dRl_A1, dRl_B2) < TMath::Hypot(dRl_A2, dRl_B1) )
      {
        leptonA = lepton1->p4();
        leptonB = lepton2->p4();
      }
      else
      {
        leptonA = lepton2->p4();
        leptonB = lepton1->p4();
      }

      // Truth matching : jets
      const double dRj_A1 = deltaR(bALVec, jet1->p4());
      const double dRj_A2 = deltaR(bALVec, jet2->p4());
      const double dRj_B1 = deltaR(bBLVec, jet1->p4());
      const double dRj_B2 = deltaR(bBLVec, jet2->p4());

      reco::Candidate::LorentzVector jetA, jetB;
      if ( TMath::Hypot(dRj_A1, dRj_B2) < TMath::Hypot(dRj_A2, dRj_B1) )
      {
        jetA = jet1->p4();
        jetB = jet2->p4();
      }
      else
      {
        jetA = jet2->p4();
        jetB = jet1->p4();
      }

      hmTopA_lbnu_->Fill((leptonA+bALVec+vALVec).mass());
      hmTopB_lbnu_->Fill((leptonB+bBLVec+vBLVec).mass());

      hmTopA_ljnu_->Fill((leptonA+jetA+vALVec).mass());
      hmTopB_ljnu_->Fill((leptonB+jetB+vBLVec).mass());

      hmWA_lnu_->Fill((leptonA+vALVec).mass());
      hmWB_lnu_->Fill((leptonB+vBLVec).mass());

      hmTopA_lbnuWrong_->Fill((leptonA+bBLVec+vALVec).mass());
      hmTopB_lbnuWrong_->Fill((leptonB+bALVec+vBLVec).mass());
      hmTopA_ljnuWrong_->Fill((leptonA+jetB+vALVec).mass());
      hmTopB_ljnuWrong_->Fill((leptonB+jetA+vBLVec).mass());

      hmTTRVsT_vsum_->Fill(m_true, m_vsum);
      hmTTRVsT_symb_->Fill(m_true, m_symb);

      hmTTRes_vsum_->Fill(m_vsum-m_true);
      hmTTRes_symb_->Fill(m_symb-m_true);

      if ( eventTopology_.mt2_maos() > 3 )
      {
        hmTTRVsT_maos_->Fill(m_true, m_maos);
        hmTopA_ljnuMaos_->Fill((leptonA+jetA+eventTopology_.nu1_maos_).mass());
        hmTopB_ljnuMaos_->Fill((leptonB+jetB+eventTopology_.nu2_maos_).mass());

        hmTopA_ljnuMaosWrong_->Fill((leptonA+jetB+eventTopology_.nu1_maos_).mass());
        hmTopB_ljnuMaosWrong_->Fill((leptonB+jetA+eventTopology_.nu2_maos_).mass());

        hmTTRes_maos_->Fill(m_maos-m_true);
      }

      if ( eventTopology_.combination_nwt_ != 0 )
      {
        hmTTRVsT_nwt_->Fill(m_true, m_nwt);
        hmTTRes_nwt_->Fill(m_nwt-m_true);
      }

      if ( eventTopology_.combination_kin_ != 0 )
      {
        hmTTRVsT_kin_->Fill(m_true, m_kin);
        hmTTRes_kin_->Fill(m_kin-m_true);
      }
    }
  }

}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TTbarMassAnalyzer);
