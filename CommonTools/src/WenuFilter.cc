// -*- C++ -*-
//
// Package:    WenuFilter
// Class:      WenuFilter
// 
/**\class WenuFilter WenuFilter.cc UserCode/WenuFilter/src/WenuFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: WenuFilter.cc,v 1.1 2010/06/22 14:44:25 tjkim Exp $
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
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include <TTree.h>

//
// class declaration
//
using namespace edm;
using namespace std;

class WenuFilter : public edm::EDFilter {
   public:
      explicit WenuFilter(const edm::ParameterSet&);
      ~WenuFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      double transverseMass( const reco::Candidate::LorentzVector& lepton, const reco::Candidate::LorentzVector& met);
      edm::InputTag eleLabel_;
      edm::InputTag metLabel_;
      edm::InputTag pfCandidateLabel_;
      double minMt_;
      double mindphi_;
      double maxdphi_;
    
      double mt;
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
WenuFilter::WenuFilter(const edm::ParameterSet& ps)
{
   //now do what ever initialization is needed
   eleLabel_ = ps.getParameter<edm::InputTag>("eleLabel");
   metLabel_ = ps.getParameter<edm::InputTag>("metLabel");
   pfCandidateLabel_= ps.getParameter<edm::InputTag>("pfCandidateLabel");
   minMt_ =   ps.getParameter<double>("minMt"); 
   mindphi_ = ps.getParameter<double>("mindphi");
   maxdphi_ = ps.getParameter<double>("maxdphi");

   edm::Service<TFileService> fs;
   tree = fs->make<TTree>("tree", "Tree for Wenu Event Selection");

}


WenuFilter::~WenuFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
WenuFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  bool accepted = false;
  edm::Handle<pat::ElectronCollection> pfEles;
  edm::Handle<pat::METCollection> pfMET;
  edm::Handle< reco::PFCandidateCollection > pfCandidates_;
  iEvent.getByLabel(eleLabel_,pfEles);     
  iEvent.getByLabel(metLabel_,pfMET);
  iEvent.getByLabel(pfCandidateLabel_,pfCandidates_);
  typedef pat::ElectronCollection::const_iterator EI; 
  

  pat::METCollection::const_iterator mi = pfMET->begin();

  typedef map< double, EI, greater<double> > PtMap;
  typedef PtMap::const_iterator IM;
  PtMap sortedEles; 
  // electrons passing identification criteria are sorted by decreasing pT
  for(EI ei = pfEles->begin(); ei!=pfEles->end(); ++ei)  {    
    sortedEles.insert( make_pair(ei->pt(), ei) );
  }

  const pat::Electron& leading = *(sortedEles.begin()->second);
  mt = transverseMass( leading.p4(), mi->p4() );
  delphi = deltaPhi(leading.phi(), mi->p4().phi());
  
  chargedhadron_size = 0;
  for(reco::PFCandidateCollection::const_iterator ci  = pfCandidates_->begin(); ci!=pfCandidates_->end(); ++ci) {
    const reco::PFCandidate& pfc = *ci;
    if( pfc.particleId() ==  1) chargedhadron_size++;
  } 
 
  //cout << "mt= " << mt << " delphi= " << delphi << "chargedhadron size= " << chargedhadron_size << endl;
 
  if (mt > minMt_ && (delphi > maxdphi_ || delphi < mindphi_) ) {
    accepted = true;
  }

  tree->Fill();
  return accepted;
}

// ------------ method called once each job just before starting event loop  ------------
void 
WenuFilter::beginJob()
{
  tree->Branch("mt",&mt,"mt/D");
  tree->Branch("delphi",&delphi,"delphi/D");
  tree->Branch("chargedhadron_size",&chargedhadron_size,"chargedhadron_size/i");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
WenuFilter::endJob() {
}

double WenuFilter::transverseMass( const reco::Candidate::LorentzVector& lepton, 
				     const reco::Candidate::LorentzVector& met) {
  
  reco::Candidate::LorentzVector leptonT(lepton.Px(),lepton.Py(),0.,lepton.E()*sin(lepton.Theta()));
  reco::Candidate::LorentzVector sumT=leptonT+met;
  return std::sqrt(sumT.M2());
}

//define this as a plug-in
//DEFINE_FWK_MODULE(WenuFilter);



