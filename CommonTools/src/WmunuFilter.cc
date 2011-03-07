// -*- C++ -*-
//
// Package:    WmunuFilter
// Class:      WmunuFilter
// 
/**\class WmunuFilter WmunuFilter.cc UserCode/WmunuFilter/src/WmunuFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: WmunuFilter.cc,v 1.5 2011/02/26 13:16:46 tjkim Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include <TTree.h>

//
// class declaration
//
using namespace edm;
using namespace std;

class WmunuFilter : public edm::EDFilter {
   public:
      explicit WmunuFilter(const edm::ParameterSet&);
      ~WmunuFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      double transverseMass( const reco::Candidate::LorentzVector& lepton, const reco::Candidate::LorentzVector& met);
      edm::InputTag muonLabel_;
      edm::InputTag metLabel_;
      edm::InputTag pfCandidateLabel_;
      double metMin_;
      double minMt_;
      double maxMt_;
      double mindphi_;
      double maxdphi_;
    
      double mt;
      double MET;
      double delphi;
      unsigned int chargedhadron_size;
      TTree *tree;
      // ----------member data ---------------------------
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
WmunuFilter::WmunuFilter(const edm::ParameterSet& ps)
{
   //now do what ever initialization is needed
   muonLabel_ = ps.getParameter<edm::InputTag>("muonLabel");
   metLabel_ = ps.getParameter<edm::InputTag>("metLabel");
   metMin_ = ps.getUntrackedParameter<double>("metMin",-999);
   pfCandidateLabel_= ps.getParameter<edm::InputTag>("pfCandidateLabel");
   minMt_ =   ps.getParameter<double>("minMt"); 
   maxMt_ =   ps.getParameter<double>("maxMt");
   mindphi_ = ps.getParameter<double>("mindphi");
   maxdphi_ = ps.getParameter<double>("maxdphi");

   edm::Service<TFileService> fs;
   tree = fs->make<TTree>("tree", "Tree for Wmunu Event Selection");

}


WmunuFilter::~WmunuFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
WmunuFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  //clear
  mt = -9;
  MET= -9;
  delphi = -9;
  chargedhadron_size = -9;
 
  bool accepted = false;
  edm::Handle<pat::MuonCollection> pfMuons;
  edm::Handle<pat::METCollection> pfMET;
  edm::Handle< reco::PFCandidateCollection > pfCandidates_;
  iEvent.getByLabel(muonLabel_,pfMuons);     
  iEvent.getByLabel(metLabel_,pfMET);
  iEvent.getByLabel(pfCandidateLabel_,pfCandidates_);
  typedef pat::MuonCollection::const_iterator MI; 
  

  pat::METCollection::const_iterator mi = pfMET->begin();

  typedef map< double, MI, greater<double> > PtMap;
  typedef PtMap::const_iterator IM;
  PtMap sortedMuons; 
  // muons passing identification criteria are sorted by decreasing pT
  for(MI ei = pfMuons->begin(); ei!=pfMuons->end(); ++ei)  {    
    sortedMuons.insert( make_pair(ei->pt(), ei) );
  }

  const pat::Muon& leading = *(sortedMuons.begin()->second);
  mt = transverseMass( leading.p4(), mi->p4() );

  MET = mi->pt();
  if( mi->p4().pt() <= metMin_ ) return false;

  delphi = fabs(deltaPhi(leading.phi(), mi->p4().phi()));

  chargedhadron_size = 0;
  for(reco::PFCandidateCollection::const_iterator ci  = pfCandidates_->begin(); ci!=pfCandidates_->end(); ++ci) {
    const reco::PFCandidate& pfc = *ci;
    if( pfc.particleId() ==  1) chargedhadron_size++;
  } 
 
  //cout << "mt= " << mt << " delphi= " << delphi << "chargedhadron size= " << chargedhadron_size << endl;
 
  if (( mt < maxMt_ && mt > minMt_) && (delphi < maxdphi_ && delphi > mindphi_) ) {
    accepted = true;
  }

  tree->Fill();
  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
WmunuFilter::beginJob()
{
  tree->Branch("mt",&mt,"mt/D");
  tree->Branch("MET",&MET,"MET/d");
  tree->Branch("delphi",&delphi,"delphi/D");
  tree->Branch("chargedhadron_size",&chargedhadron_size,"chargedhadron_size/i");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
WmunuFilter::endJob() {
}

double WmunuFilter::transverseMass( const reco::Candidate::LorentzVector& lepton, 
				     const reco::Candidate::LorentzVector& met) {
  
  reco::Candidate::LorentzVector leptonT(lepton.Px(),lepton.Py(),0.,lepton.E()*sin(lepton.Theta()));
  reco::Candidate::LorentzVector sumT=leptonT+met;
  return std::sqrt(sumT.M2());
}

//define this as a plug-in
DEFINE_FWK_MODULE(WmunuFilter);



