// -*- C++ -*-
//
// Package:    JetFilter
// Class:      JetFilter
// 
/**\class JetFilter JetFilter.cc UserCode/JetFilter/src/JetFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: JetFilter.cc,v 1.1 2010/07/22 20:10:20 tjkim Exp $
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "PFAnalyses/CommonTools/interface/PatJetIdSelector.h"
#include "PFAnalyses/CommonTools/interface/CandidateSelector.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"

#include "TTree.h"
#include "TFile.h"
#include "TH1.h"



//
// class declaration
//
using namespace edm;
using namespace std;

class JetFilter : public edm::EDFilter {
   public:
      explicit JetFilter(const edm::ParameterSet&);
      ~JetFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      // ----------member data ---------------------------

      typedef pat::JetCollection::const_iterator JI;
      edm::InputTag jetLabel_;
      /// loose jet ID. 
      PatJetIdSelector looseJetIdSelector_;
      unsigned int min_;
      double ptcut_;

      TTree* tree;

      std::vector<math::XYZTLorentzVector>* jets;
      std::vector<math::XYZTLorentzVector>* jetspt30;

      // Residual Jet energy correction for 38X
      FactorizedJetCorrector* resJetCorrector_;
      bool doResJec_;

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
JetFilter::JetFilter(const edm::ParameterSet& ps)
{
   //now do what ever initialization is needed
  jetLabel_ =  ps.getParameter<edm::InputTag>("jetLabel");
  min_ = ps.getUntrackedParameter<unsigned int>("min",1);
  ptcut_ = ps.getUntrackedParameter<double>("ptcut",30.0);
  looseJetIdSelector_.initialize( ps.getParameter<edm::ParameterSet> ("looseJetId") );
   // Residual Jet energy correction for 38X
  doResJec_ = ps.getUntrackedParameter<bool>("doResJec", false);
  resJetCorrector_ = 0;


  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for JetFilter");

  jets = new std::vector<math::XYZTLorentzVector>();
  jetspt30 = new std::vector<math::XYZTLorentzVector>();

}


JetFilter::~JetFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
JetFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  bool accepted = false;
  using namespace edm;
  using namespace std;
  using namespace reco;

  jets->clear();
  jetspt30->clear();

  edm::Handle<pat::JetCollection> Jets;
  iEvent.getByLabel(jetLabel_,Jets);

  for (JI it = Jets->begin(); it != Jets->end(); ++it) {

    if(abs(it->eta()) >= 2.4) continue; 

    pat::strbitset looseJetIdSel = looseJetIdSelector_.getBitTemplate();
    bool passId = looseJetIdSelector_( *it, looseJetIdSel);

    if(passId){

       ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrjet;
       corrjet.SetPxPyPzE(it->px(),it->py(),it->pz(),it->energy());


       if(doResJec_){
         resJetCorrector_->setJetEta(it->eta());
         resJetCorrector_->setJetPt(it->pt());
         const double scaleF = resJetCorrector_->getCorrection();
         corrjet *= scaleF;
        }

      jets->push_back(corrjet);

      if( corrjet.pt() > ptcut_ )
        jetspt30->push_back(corrjet);
     }

   }

  if( jetspt30->size() >= min_ ) accepted = true;

  tree->Fill();
  return accepted;

}
   


// ------------ method called once each job just before starting event loop  ------------
void 
JetFilter::beginJob()
{

  tree->Branch("jets","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jets);
  tree->Branch("jetspt30","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jetspt30);

  // Jet energy correction for 38X
  if ( doResJec_ )
  {
    edm::FileInPath jecFile("CondFormats/JetMETObjects/data/Spring10DataV2_L2L3Residual_AK5PF.txt");
    std::vector<JetCorrectorParameters> jecParams;
    jecParams.push_back(JetCorrectorParameters(jecFile.fullPath()));
    resJetCorrector_ = new FactorizedJetCorrector(jecParams);
  }


}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetFilter::endJob() {
  if ( resJetCorrector_ ) delete resJetCorrector_;
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetFilter);



