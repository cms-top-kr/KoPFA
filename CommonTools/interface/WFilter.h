// -*- C++ -*-
//
// Package:    TopLJAnalyzer
// Class:      TopLJAnalyzer
// 
/**\class TopLJAnalyzer TopLJAnalyzer.cc UserCode/TopLJAnalyzer/src/TopLJAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tae Jeong Kim,40 R-A32,+41227678602,
//         Created:  Fri Jun  4 17:19:29 CEST 2010
// $Id: WFilter.h,v 1.1 2011/05/23 09:34:27 tjkim Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Common/interface/MergeableCounter.h"
#include "KoPFA/DataFormats/interface/WCandidate.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "KoPFA/DataFormats/interface/TTbarMass.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/Core/interface/DQMStore.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "KoPFA/DataFormats/interface/Maos.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TLorentzVector.h"

//
// class declaration
//
using namespace edm;
using namespace std;
using namespace reco;
using namespace isodeposit;

template<typename T1>
class WFilter : public edm::EDFilter {
 public:
  explicit WFilter(const edm::ParameterSet& iConfig){
    //now do what ever initialization is needed
    muonLabel_ = iConfig.getParameter<edm::InputTag>("muonLabel");
    metLabel_ = iConfig.getParameter<edm::InputTag>("metLabel");
    min_ = iConfig.getParameter<double>("min");  
    max_ = iConfig.getParameter<double>("max");  
  }

  ~WFilter(){}

 private:
  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {

    bool accept = false;

    edm::Handle<std::vector<T1>  > muons_;
    edm::Handle<pat::METCollection> met_;
    iEvent.getByLabel(muonLabel_,muons_);
    iEvent.getByLabel(metLabel_,met_);
  	pat::METCollection::const_iterator mei;
	for(unsigned i = 0; i != muons_->size(); i++){
        T1 it1 = muons_->at(i);;
        it1.setP4(it1.pfCandidateRef()->p4());

        double transversemass = (it1.p4() + mei->p4()).M2();

        if( transversemass > min_ && transversemass < max_ ){
          accept = true;
        }
   }

    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);

    return accept;
}


  edm::InputTag muonLabel_;
  edm::InputTag metLabel_;
  double min_;
  double max_;
};

