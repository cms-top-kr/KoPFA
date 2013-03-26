// -*- C++ -*-
//
// Package:    CMGMuonFilter
// Class:      CMGMuonFilter
//
/**\class CMGMuonFilter CMGMuonFilter.cc UserCode/CMGMuonFilter/src/CMGMuonFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: CMGMuonFilter.cc,v 1.3 2012/10/30 15:50:17 tjkim Exp $
//
//

// system include files
#include <memory>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/CompositePtrCandidate.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"

#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
//#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "CommonTools/Utils/interface/PtComparator.h"

//
// class declaration
//
using namespace edm;
using namespace std;
using namespace reco;
using namespace isodeposit;

class CMGMuonFilter : public edm::EDFilter {
   public:
      explicit CMGMuonFilter(const edm::ParameterSet&);
      ~CMGMuonFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      // ----------member data ---------------------------

      bool applyFilter_;
      edm::InputTag muonLabel_;
      edm::InputTag vertexLabel_;
      double ptcut_;
      double etacut_;
      double relIso_;

      bool isRealData_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
CMGMuonFilter::CMGMuonFilter(const edm::ParameterSet& cfg)
{
   //now do what ever initialization is needed
  applyFilter_=cfg.getUntrackedParameter<bool>("applyFilter",false);
  muonLabel_ = cfg.getParameter<edm::InputTag>("muonLabel");
  vertexLabel_ =  cfg.getUntrackedParameter<edm::InputTag>("vertexLabel");
  ptcut_ = cfg.getUntrackedParameter<double>("ptcut",20);
  etacut_ = cfg.getUntrackedParameter<double>("etacut",2.5);
  relIso_ = cfg.getUntrackedParameter<double>("relIso",9999);

  produces<std::vector<cmg::Muon> >("");

}


CMGMuonFilter::~CMGMuonFilter()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
CMGMuonFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  isRealData_ = iEvent.isRealData();

  bool accepted = false;

  edm::Handle<vector<cmg::Muon> > muons_;
  iEvent.getByLabel(muonLabel_, muons_);

  std::auto_ptr<std::vector<cmg::Muon> > pos(new std::vector<cmg::Muon>());
  
  edm::Handle<reco::VertexCollection> recVtxs_;
  iEvent.getByLabel(vertexLabel_,recVtxs_);

  int nvertex = 0;
  std::auto_ptr<std::vector<reco::Vertex> > goodOfflinePrimaryVertices(new std::vector<reco::Vertex>());
  for(unsigned int i=0; i < recVtxs_->size();  ++i){
    reco::Vertex v = recVtxs_->at(i);
    if (!(v.isFake()) && (v.ndof()>4) && (fabs(v.z())<=24.0) && (v.position().Rho()<=2.0) ) {
      goodOfflinePrimaryVertices->push_back((*recVtxs_)[i]);
      nvertex++;
    }
  }
    
  if( nvertex == 0 ) return false;
  reco::Vertex pv = goodOfflinePrimaryVertices->at(0);

  for (unsigned int i=0; i < muons_->size();++i){
    cmg::Muon muon = muons_->at(i);

    bool passPre = muon.pt() > ptcut_ && fabs(muon.eta()) < etacut_ && fabs(muon.dxy(pv.position())) < 0.04;

    if( !passPre ) continue;
 
    bool passId = muon.sourcePtr()->get()->isPFMuon() && ( muon.sourcePtr()->get()->isGlobalMuon() ||  muon.sourcePtr()->get()->isTrackerMuon() );
    
    if( !passId) continue;

    reco::isodeposit::Direction Dir = Direction(muon.eta(),muon.phi());

    reco::isodeposit::AbsVetos vetos_ch;
    reco::isodeposit::AbsVetos vetos_nh;
    reco::isodeposit::AbsVetos vetos_ph;

    vetos_nh.push_back(new ThresholdVeto( 0.5 ));
    vetos_ph.push_back(new ThresholdVeto( 0.5 ));

    double chIso03 = muon.sourcePtr()->get()->isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
    double puChIso03 = muon.sourcePtr()->get()->isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
    double nhIso03 = muon.sourcePtr()->get()->isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
    double phIso03 = muon.sourcePtr()->get()->isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph).first;
    double relIso03 = (chIso03+max(0.0, nhIso03+phIso03 - 0.5*puChIso03))/muon.pt();

    bool passIso =  relIso03 < relIso_;

    if( !passIso ) continue;

    pos->push_back((*muons_)[i]);

  }

  iEvent.put(pos);

  if( applyFilter_ ) return accepted;
  else return true;

}

// ------------ method called once each job just before starting event loop  ------------
void
CMGMuonFilter::beginJob()
{

}

// ------------ method called once each job just after ending the event loop  ------------
void
CMGMuonFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(CMGMuonFilter);



