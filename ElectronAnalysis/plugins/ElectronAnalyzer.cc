#ifndef KoPFA_ElectronAnalysis_ElectronAnalyzer_H
#define KoPFA_ElectronAnalysis_ElectronAnalyzer_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"

#include <memory>

class ElectronAnalyzer : public edm::EDAnalyzer
{
public:
  ElectronAnalyzer(const edm::ParameterSet& pset);
  ~ElectronAnalyzer();

  void beginJob();
  void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);
  void endJob();

private:
  edm::InputTag genParticleLabel_;
  edm::InputTag electronLabel_;
  edm::InputTag pfCandLabel_;

private:
  TTree* tree_;

  int event_, run_, lumi_;

  typedef std::vector<double>* VDP;
  VDP genPt_, genEta_, genPhi_, genE_, genP_;
  VDP gsfPt_, gsfEta_, gsfPhi_, gsfE_, gsfP_;
  VDP pfaPt_, pfaEta_, pfaPhi_, pfaE_, pfaP_;

  // Matched genParticle observables
  VDP gsfGenPt_, gsfGenEta_, gsfGenPhi_, gsfGenE_, gsfGenP_;
  VDP pfaGenPt_, pfaGenEta_, pfaGenPhi_, pfaGenE_, pfaGenP_;

  std::vector<bool>* gsfToPfaMatch_;

  VDP gsfEcalE_, pfaEcalE_;
  VDP gsfMva_, pfaMva_;

  VDP umPfaPt_, umPfaEta_, umPfaPhi_, umPfaE_, umPfaP_;
  VDP umPfaGenPt_, umPfaGenEta_, umPfaGenPhi_, umPfaGenE_, umPfaGenP_;
  VDP umPfaEcalE_;
  VDP umPfaMva_;

private:
  typedef edm::View<reco::GenParticle>::const_iterator GenParIter;
  typedef edm::View<reco::PFCandidate>::const_iterator PFCandIter;
  typedef edm::View<reco::GsfElectron>::const_iterator GsfEleIter;

  template <typename TIter>
  GenParIter findElectron(const TIter recoEle, GenParIter begin, GenParIter end);
  PFCandIter findElectron(const GsfEleIter gsf, PFCandIter begin, PFCandIter end);
  GsfEleIter findElectron(const PFCandIter pfa, GsfEleIter begin, GsfEleIter end);
};

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& pset)
{
  electronLabel_ = pset.getParameter<edm::InputTag>("electron");
  pfCandLabel_ = pset.getParameter<edm::InputTag>("pfCandidate");
  genParticleLabel_ = pset.getParameter<edm::InputTag>("genParticles");

  genPt_  = new std::vector<double>;
  genEta_ = new std::vector<double>;
  genPhi_ = new std::vector<double>;
  genE_   = new std::vector<double>;
  genP_   = new std::vector<double>;

  gsfPt_  = new std::vector<double>;
  gsfEta_ = new std::vector<double>;
  gsfPhi_ = new std::vector<double>;
  gsfE_   = new std::vector<double>;
  gsfP_   = new std::vector<double>;

  pfaPt_  = new std::vector<double>;
  pfaEta_ = new std::vector<double>;
  pfaPhi_ = new std::vector<double>;
  pfaE_   = new std::vector<double>;
  pfaP_   = new std::vector<double>;

  gsfGenPt_  = new std::vector<double>;
  gsfGenEta_ = new std::vector<double>;
  gsfGenPhi_ = new std::vector<double>;
  gsfGenE_   = new std::vector<double>;
  gsfGenP_   = new std::vector<double>;

  pfaGenPt_  = new std::vector<double>;
  pfaGenEta_ = new std::vector<double>;
  pfaGenPhi_ = new std::vector<double>;
  pfaGenE_   = new std::vector<double>;
  pfaGenP_   = new std::vector<double>;

  gsfEcalE_ = new std::vector<double>;
  pfaEcalE_ = new std::vector<double>;

  gsfMva_ = new std::vector<double>;
  pfaMva_ = new std::vector<double>;

  gsfToPfaMatch_ = new std::vector<bool>;

  umPfaPt_  = new std::vector<double>;
  umPfaEta_ = new std::vector<double>;
  umPfaPhi_ = new std::vector<double>;
  umPfaE_   = new std::vector<double>;
  umPfaP_   = new std::vector<double>;

  umPfaGenPt_  = new std::vector<double>;
  umPfaGenEta_ = new std::vector<double>;
  umPfaGenPhi_ = new std::vector<double>;
  umPfaGenE_   = new std::vector<double>;
  umPfaGenP_   = new std::vector<double>;

  umPfaEcalE_ = new std::vector<double>;
  umPfaMva_ = new std::vector<double>;
}

ElectronAnalyzer::~ElectronAnalyzer()
{
}

void ElectronAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("tree", "tree");

  tree_->Branch("event", &event_, "event/i");
  tree_->Branch("run", &run_, "run/i");
  tree_->Branch("lumi", &lumi_, "lumi/i");

  tree_->Branch("genPt" , "std::vector<double>", &genPt_ );
  tree_->Branch("genEta", "std::vector<double>", &genEta_);
  tree_->Branch("genPhi", "std::vector<double>", &genPhi_);
  tree_->Branch("genE"  , "std::vector<double>", &genE_  );
  tree_->Branch("genP"  , "std::vector<double>", &genP_  );

  tree_->Branch("gsfPt" , "std::vector<double>", &gsfPt_ );
  tree_->Branch("gsfEta", "std::vector<double>", &gsfEta_);
  tree_->Branch("gsfPhi", "std::vector<double>", &gsfPhi_);
  tree_->Branch("gsfE"  , "std::vector<double>", &gsfE_  );
  tree_->Branch("gsfP"  , "std::vector<double>", &gsfP_  );

  tree_->Branch("pfaPt" , "std::vector<double>", &pfaPt_ );
  tree_->Branch("pfaEta", "std::vector<double>", &pfaEta_);
  tree_->Branch("pfaPhi", "std::vector<double>", &pfaPhi_);
  tree_->Branch("pfaE"  , "std::vector<double>", &pfaE_  );
  tree_->Branch("pfaP"  , "std::vector<double>", &pfaP_  );

  tree_->Branch("gsfGenPt" , "std::vector<double>", &gsfGenPt_ );
  tree_->Branch("gsfGenEta", "std::vector<double>", &gsfGenEta_);
  tree_->Branch("gsfGenPhi", "std::vector<double>", &gsfGenPhi_);
  tree_->Branch("gsfGenE"  , "std::vector<double>", &gsfGenE_  );
  tree_->Branch("gsfGenP"  , "std::vector<double>", &gsfGenP_  );

  tree_->Branch("pfaGenPt" , "std::vector<double>", &pfaGenPt_ );
  tree_->Branch("pfaGenEta", "std::vector<double>", &pfaGenEta_);
  tree_->Branch("pfaGenPhi", "std::vector<double>", &pfaGenPhi_);
  tree_->Branch("pfaGenE"  , "std::vector<double>", &pfaGenE_  );
  tree_->Branch("pfaGenP"  , "std::vector<double>", &pfaGenP_  );

  tree_->Branch("gsfMva", "std::vector<double>", &gsfMva_);
  tree_->Branch("pfaMva", "std::vector<double>", &pfaMva_);

  tree_->Branch("gsfEcalE", "std::vector<double>", &gsfEcalE_);
  tree_->Branch("pfaEcalE", "std::vector<double>", &pfaEcalE_);

  tree_->Branch("gsfToPfaMatch", "std::vector<bool>", &gsfToPfaMatch_);

  tree_->Branch("umPfaPt" , "std::vector<double>", &umPfaPt_ );
  tree_->Branch("umPfaEta", "std::vector<double>", &umPfaEta_);
  tree_->Branch("umPfaPhi", "std::vector<double>", &umPfaPhi_);
  tree_->Branch("umPfaE"  , "std::vector<double>", &umPfaE_  );
  tree_->Branch("umPfaP"  , "std::vector<double>", &umPfaP_  );

  tree_->Branch("umPfaGenPt" , "std::vector<double>", &umPfaGenPt_ );
  tree_->Branch("umPfaGenEta", "std::vector<double>", &umPfaGenEta_);
  tree_->Branch("umPfaGenPhi", "std::vector<double>", &umPfaGenPhi_);
  tree_->Branch("umPfaGenE"  , "std::vector<double>", &umPfaGenE_  );
  tree_->Branch("umPfaGenP"  , "std::vector<double>", &umPfaGenP_  );

  tree_->Branch("umPfaEcalE", "std::vector<double>", &umPfaEcalE_);
  tree_->Branch("umPfaMva", "std::vector<double>", & umPfaMva_);
}

void ElectronAnalyzer::endJob()
{

}

template <typename TIter>
ElectronAnalyzer::GenParIter ElectronAnalyzer::findElectron(const TIter recoEle,
                                                            ElectronAnalyzer::GenParIter begin,
                                                            ElectronAnalyzer::GenParIter end)
{
  return begin;
}

ElectronAnalyzer::PFCandIter ElectronAnalyzer::findElectron(const GsfEleIter gsf,
                                                            ElectronAnalyzer::PFCandIter begin,
                                                            ElectronAnalyzer::PFCandIter end)
{
  reco::GsfTrackRef refTrk = gsf->gsfTrack();
  if ( refTrk.isNull() ) return end;

  PFCandIter matchedEle = end;
  for ( PFCandIter pfa = begin; pfa != end; ++pfa )
  {
    bool matched = false;

    if ( refTrk == pfa->gsfTrackRef() )
    {
      matched = true;
    }
    else
    {
      for ( reco::GsfTrackRefVector::const_iterator ambTrk = gsf->ambiguousGsfTracksBegin();
            ambTrk != gsf->ambiguousGsfTracksEnd(); ++ambTrk )
      {
        if ( refTrk == *ambTrk )
        {
          matched = true;
          break;
        }
      }
    }

    if ( matched )
    {
      matchedEle = pfa;
      break;
    }
  }

  return matchedEle;
}

ElectronAnalyzer::GsfEleIter ElectronAnalyzer::findElectron(const PFCandIter pfa,
                                                            ElectronAnalyzer::GsfEleIter begin,
                                                            ElectronAnalyzer::GsfEleIter end)
{
  reco::GsfTrackRef refTrk = pfa->gsfTrackRef();
  if ( refTrk.isNull() ) return end;

  GsfEleIter matchedEle = end;
  for ( GsfEleIter gsf = begin; gsf != end; ++gsf )
  {
    bool matched = false;

    if ( refTrk == gsf->gsfTrack() )
    {
      matched = true;
    }
    else
    {
      for ( reco::GsfTrackRefVector::const_iterator ambTrk = gsf->ambiguousGsfTracksBegin();
            ambTrk != gsf->ambiguousGsfTracksEnd(); ++ambTrk )
      {
        if ( refTrk == *ambTrk )
        {
          matched = true;
          break;
        }
      }
    }

    if ( matched )
    {
      matchedEle = gsf;
      break;
    }
  }
  return matchedEle;
}

void ElectronAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  using namespace std;
  using namespace edm;

  event_ = event.id().event();
  run_ = event.id().run();
  lumi_ = event.id().luminosityBlock();

  edm::Handle<edm::View<reco::GenParticle> > genParticleHandle;
  event.getByLabel(genParticleLabel_, genParticleHandle);

  edm::Handle<edm::View<reco::GsfElectron> > electronHandle;
  event.getByLabel(electronLabel_, electronHandle);

  edm::Handle<edm::View<reco::PFCandidate> > pfCandHandle;
  event.getByLabel(pfCandLabel_, pfCandHandle);

  // Set default values
  genPt_ ->clear();
  genEta_->clear();
  genPhi_->clear();
  genE_  ->clear();
  genP_  ->clear();

  gsfPt_ ->clear();
  gsfEta_->clear();
  gsfPhi_->clear();
  gsfE_  ->clear();
  gsfP_  ->clear();

  pfaPt_ ->clear();
  pfaEta_->clear();
  pfaPhi_->clear();
  pfaE_  ->clear();
  pfaP_  ->clear();

  gsfGenPt_ ->clear();
  gsfGenEta_->clear();
  gsfGenPhi_->clear();
  gsfGenE_  ->clear();
  gsfGenP_  ->clear();

  pfaGenPt_ ->clear();
  pfaGenEta_->clear();
  pfaGenPhi_->clear();
  pfaGenE_  ->clear();
  pfaGenP_  ->clear();

  gsfEcalE_->clear();
  pfaEcalE_->clear();

  gsfMva_->clear();
  pfaMva_->clear();

  gsfToPfaMatch_->clear();

  umPfaPt_->clear();
  umPfaEta_->clear();
  umPfaPhi_->clear();
  umPfaE_->clear();
  umPfaP_->clear();

  umPfaEcalE_->clear();
  umPfaMva_->clear();

  if ( genParticleHandle.isValid() )
  {
    for ( GenParIter iGen = genParticleHandle->begin();
          iGen != genParticleHandle->end(); ++iGen )
    {
      if ( abs(iGen->pdgId()) != 11 or iGen->status() != 3 ) continue;

      const reco::Candidate::LorentzVector p4 = iGen->p4();
      genPt_->push_back(p4.pt());
      genEta_->push_back(p4.eta());
      genPhi_->push_back(p4.phi());
      genE_->push_back(p4.e());
      genP_->push_back(p4.P());
    }
  }

  for ( GsfEleIter iEle = electronHandle->begin();
        iEle != electronHandle->end(); ++iEle )
  {
    const reco::Candidate::LorentzVector p4 = iEle->p4();
    gsfPt_->push_back(p4.pt());
    gsfEta_->push_back(p4.eta());
    gsfPhi_->push_back(p4.phi());
    gsfE_->push_back(p4.e());
    gsfP_->push_back(p4.P());

    gsfEcalE_->push_back(iEle->ecalEnergy());
    gsfMva_->push_back(iEle->mva());

    GenParIter gsfGenPar = findElectron(iEle, genParticleHandle->begin(), genParticleHandle->end());
    if ( gsfGenPar != genParticleHandle->end() )
    {
      gsfGenPt_->push_back(gsfGenPar->p4().pt());
      gsfGenEta_->push_back(gsfGenPar->p4().eta());
      gsfGenPhi_->push_back(gsfGenPar->p4().phi());
      gsfGenE_->push_back(gsfGenPar->p4().e());
      gsfGenP_->push_back(gsfGenPar->p4().P());
    }
    else
    {
      gsfGenPt_->push_back(-999);
      gsfGenEta_->push_back(-999);
      gsfGenPhi_->push_back(-999);
      gsfGenE_->push_back(-999);
      gsfGenP_->push_back(-999);
    }

    PFCandIter matched = findElectron(iEle, pfCandHandle->begin(), pfCandHandle->end());
    if ( matched != pfCandHandle->end() )
    {
      pfaPt_->push_back(matched->pt());
      pfaEta_->push_back(matched->eta());
      pfaPhi_->push_back(matched->phi());
      pfaE_->push_back(matched->p4().e());
      pfaP_->push_back(matched->p4().P());

      pfaEcalE_->push_back(matched->ecalEnergy());
      pfaMva_->push_back(matched->mva_e_pi());

      gsfToPfaMatch_->push_back(true);

      GenParIter pfaGenPar = findElectron(matched, genParticleHandle->begin(), genParticleHandle->end());
      if ( pfaGenPar != genParticleHandle->end() )
      {
        pfaGenPt_->push_back(pfaGenPar->p4().pt());
        pfaGenEta_->push_back(pfaGenPar->p4().eta());
        pfaGenPhi_->push_back(pfaGenPar->p4().phi());
        pfaGenE_->push_back(pfaGenPar->p4().e());
        pfaGenP_->push_back(pfaGenPar->p4().P());
      }
      else
      {
        pfaGenPt_->push_back(-999);
        pfaGenEta_->push_back(-999);
        pfaGenPhi_->push_back(-999);
        pfaGenE_->push_back(-999);
        pfaGenP_->push_back(-999);
      }
    }
    else
    {
      pfaPt_->push_back(-999);
      pfaEta_->push_back(-999);
      pfaPhi_->push_back(-999);
      pfaE_->push_back(-999);
      pfaP_->push_back(-999);

      pfaEcalE_->push_back(-999);
      pfaMva_->push_back(-999);

      gsfToPfaMatch_->push_back(false);

      pfaGenPt_->push_back(-999);
      pfaGenEta_->push_back(-999);
      pfaGenPhi_->push_back(-999);
      pfaGenE_->push_back(-999);
      pfaGenP_->push_back(-999);
    }
  }

  for ( PFCandIter iPFCand = pfCandHandle->begin();
      iPFCand != pfCandHandle->end(); ++iPFCand )
  {
    if ( abs(iPFCand->pdgId()) != 11 ) continue;

    const reco::Candidate::LorentzVector p4 = iPFCand->p4();
    GsfEleIter matched = findElectron(iPFCand, electronHandle->begin(), electronHandle->end());
    if ( matched == electronHandle->end() )
    {
      umPfaPt_->push_back(p4.pt());
      umPfaEta_->push_back(p4.eta());
      umPfaPhi_->push_back(p4.phi());
      umPfaE_->push_back(p4.e());
      umPfaP_->push_back(p4.P());

      umPfaEcalE_->push_back(iPFCand->ecalEnergy());
      umPfaMva_->push_back(iPFCand->mva_e_pi());

      GenParIter umPfaGenPar = findElectron(matched, genParticleHandle->begin(), genParticleHandle->end());
      if ( umPfaGenPar != genParticleHandle->end() )
      {
        umPfaGenPt_->push_back(umPfaGenPar->p4().pt());
        umPfaGenEta_->push_back(umPfaGenPar->p4().eta());
        umPfaGenPhi_->push_back(umPfaGenPar->p4().phi());
        umPfaGenE_->push_back(umPfaGenPar->p4().e());
        umPfaGenP_->push_back(umPfaGenPar->p4().P());
      }
      else
      {
        umPfaGenPt_->push_back(-999);
        umPfaGenEta_->push_back(-999);
        umPfaGenPhi_->push_back(-999);
        umPfaGenE_->push_back(-999);
        umPfaGenP_->push_back(-999);
      }
    }
  }

  tree_->Fill();
}

DEFINE_FWK_MODULE(ElectronAnalyzer);

#endif

