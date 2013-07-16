// -*- C++ -*-
//
// Package:    CMGJetFilter
// Class:      CMGJetFilter
//
/**\class CMGJetFilter CMGJetFilter.cc UserCode/CMGJetFilter/src/CMGJetFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: CMGJetFilter.cc,v 1.9 2013/07/02 07:53:48 tjkim Exp $
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
#include "AnalysisDataFormats/CMGTools/interface/BaseMET.h"
#include "AnalysisDataFormats/CMGTools/interface/BaseJet.h"
#include "AnalysisDataFormats/CMGTools/interface/PFJet.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"

#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
//#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include "CommonTools/Utils/interface/PtComparator.h"

//
// class declaration
//
using namespace edm;
using namespace std;

class CMGJetFilter : public edm::EDFilter {
   public:
      explicit CMGJetFilter(const edm::ParameterSet&);
      ~CMGJetFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      //double resolutionFactor(const cmg::PFJet&);
      bool checkPFJetId(const cmg::PFJet * jet);
      // ----------member data ---------------------------

      typedef vector<cmg::PFJet>::const_iterator JI;

      bool applyFilter_;
      bool bJetFirst_; 
      string bTagAlgo_;
      double bTagValue_;
      edm::InputTag rhoLabel_;
      edm::InputTag jetLabel_;
      edm::InputTag metLabel_;
      edm::InputTag electronLabel_;
      edm::InputTag muonLabel_;

      string outputJetLabel_;
      string outputMETLabel_;
      edm::InputTag vertexLabel_;
      /// loose jet ID.

      unsigned int min_;
      double ptcut_;
      double absetacut_;
      bool doJecFly_;
      bool doResJec_;
      bool isRealData_;
      bool doJecUnc_;
      bool up_;
      bool doJERUnc_;
      double resolutionFactor_;
      string globalTag_;

      FactorizedJetCorrector* resJetCorrector_;
      JetCorrectionUncertainty *jecUnc_;

      edm::ParameterSet pfJetIdParams_;
 
      string debug_;
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
CMGJetFilter::CMGJetFilter(const edm::ParameterSet& ps)
{
   //now do what ever initialization is needed
  applyFilter_=ps.getUntrackedParameter<bool>("applyFilter",false);
  bJetFirst_ = ps.getUntrackedParameter<bool>("bJetFirst",false);
  bTagAlgo_ = ps.getUntrackedParameter<string>("bTagAlgo","combinedSecondaryVertexBJetTags");
  bTagValue_ = ps.getUntrackedParameter<double>("bTagValue",0.244);
  rhoLabel_ =  ps.getParameter<edm::InputTag>("rhoLabel");
  jetLabel_ =  ps.getParameter<edm::InputTag>("jetLabel");
  metLabel_ = ps.getParameter<edm::InputTag>("metLabel");
  vertexLabel_ =  ps.getUntrackedParameter<edm::InputTag>("vertexLabel");
  min_ = ps.getUntrackedParameter<unsigned int>("min",1);
  ptcut_ = ps.getUntrackedParameter<double>("ptcut",30.0);
  absetacut_ = ps.getUntrackedParameter<double>("absetacut",2.5);
  pfJetIdParams_ = ps.getParameter<edm::ParameterSet> ("looseJetId");
  doJecFly_ = ps.getUntrackedParameter<bool>("doJecFly", false);
  doResJec_ = ps.getUntrackedParameter<bool>("doResJec", false);
  doJecUnc_ = ps.getUntrackedParameter<bool>("doJecUnc", false);
  up_ = ps.getUntrackedParameter<bool>("up", true); // uncertainty up
  doJERUnc_ = ps.getUntrackedParameter<bool>("doJERUnc", false);
  resolutionFactor_ = ps.getUntrackedParameter<double>("resolutionFactor", 1.0);
  globalTag_ = ps.getUntrackedParameter<string>("globalTag","GR_R_42_V23");

  electronLabel_ = ps.getParameter<edm::InputTag>("electronLabel");
  muonLabel_ = ps.getParameter<edm::InputTag>("muonLabel");

  resJetCorrector_ = 0;
  jecUnc_ = 0;

  outputJetLabel_ = jetLabel_.label();
  outputMETLabel_ = metLabel_.label();

  produces<std::vector<cmg::PFJet> >("Jets");
  produces<std::vector<cmg::BaseMET> >("MET");

}


CMGJetFilter::~CMGJetFilter()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
CMGJetFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  debug_ = " ";
  isRealData_ = iEvent.isRealData();

  int EVENT  = iEvent.id().event();
  int RUN    = iEvent.id().run();
  int LUMI   = iEvent.id().luminosityBlock();

  bool accepted = false;
  using namespace edm;
  using namespace std;
  using namespace reco;

  std::auto_ptr<std::vector<cmg::PFJet> > corrJets(new std::vector<cmg::PFJet>());
  std::auto_ptr<std::vector<cmg::BaseMET> > corrMETs(new std::vector<cmg::BaseMET>());
  std::auto_ptr<std::vector<cmg::PFJet> > corrbJets(new std::vector<cmg::PFJet>());

  edm::Handle<vector<cmg::PFJet> > Jets;
  iEvent.getByLabel(jetLabel_,Jets);

  edm::Handle<std::vector<cmg::BaseMET> > MET;
  iEvent.getByLabel(metLabel_,MET);
  //std::vector<cmg::BaseMET>::const_iterator met = MET->begin();
  double met_x = MET->begin()->px();
  double met_y = MET->begin()->py();

  edm::Handle<std::vector<cmg::Electron> > electrons_;
  iEvent.getByLabel(electronLabel_, electrons_);

  edm::Handle<std::vector<cmg::Muon> > muons_;
  iEvent.getByLabel(muonLabel_, muons_);

  edm::Handle<double>  rho;
  iEvent.getByLabel(rhoLabel_, rho);

  edm::Handle<reco::VertexCollection> recVtxs_;
  iEvent.getByLabel(vertexLabel_,recVtxs_);

  //const int nv = recVtxs_->size();

  PFJetIDSelectionFunctor looseJetIdSelector_(pfJetIdParams_);
  int njet = 0;
  for (JI it = Jets->begin(); it != Jets->end(); ++it) {
    cmg::PFJet correctedJet = *it;

    if(fabs(it->eta()) >= absetacut_) continue;
    if( it->pt() < 20 ) continue;

    //pat::strbitset looseJetIdSel = looseJetIdSelector_.getBitTemplate();
    //bool passId = looseJetIdSelector_( *it, looseJetIdSel);

    // it is identical : checkPFJetId and using the cut string
    bool passId = false;
    bool passLooseId = false;

    passId  = checkPFJetId( &correctedJet);
    passLooseId = it->getSelection("cuts_looseJetId");

    if(!passId) continue;
    //reco::Candidate::LorentzVector uncorrJet = it->sourcePtr()->get()->correctedP4(0);
    //cout << "jet uncorrected pt = " << uncorrJet.pt() << endl;

    bool overlap = false;
    
    for (unsigned int i=0; i < electrons_->size(); ++i){
      cmg::Electron electron = electrons_->at(i);
      double dR =  deltaR(electron.eta(), electron.phi(), it->eta(), it->phi());
      if( dR < 0.5 ) {
        overlap = true;
        break;
      }
    }
 
    if(overlap) continue;

    for (unsigned int i=0; i < muons_->size(); ++i){
      cmg::Muon muon = muons_->at(i);
      double dR =  deltaR(muon.eta(), muon.phi(), it->eta(), it->phi());
      if( dR < 0.5 ) {
        overlap = true;
        break;
      }
    }

    //cout << "jet pt = " << it->pt() << " eta = " << it->eta() << " pass= " << passId << " looseJetId= " << passLooseId << " overlap= " << overlap << endl;

    if(overlap) continue;

    //double scaleF = 1.0;
    //if(doJecFly_){
    //  correctedJet.scaleEnergy( it->jecFactor(0) ); //set it to uncorrected jet energy
      //debug
      //cout << "uncorrected jet pt= " << correctedJet.pt() << endl;
    //  reco::Candidate::LorentzVector uncorrJet = it->correctedP4(0);

    //  resJetCorrector_->setJetEta( uncorrJet.eta() );
    //  resJetCorrector_->setJetPt ( uncorrJet.pt() );
    //  resJetCorrector_->setJetE  ( uncorrJet.energy() );
    //  resJetCorrector_->setJetA  ( it->jetArea() );
    //  resJetCorrector_->setRho   ( *(rho.product()) );
    //  resJetCorrector_->setNPV   ( nv );

      //scaleF = resJetCorrector_->getCorrection();
    //}

    //correctedJet.scaleEnergy( scaleF );

    if(doJecUnc_){
      //jecUnc_->setJetEta(correctedJet.eta());
      //jecUnc_->setJetPt(correctedJet.pt());
      met_x += correctedJet.px();
      met_y += correctedJet.py();
      //double unc = jecUnc_->getUncertainty(up_);
      double unc = correctedJet.uncOnFourVectorScale();
      double ptscaleunc = 0;
      if(up_) ptscaleunc = 1 + unc;
      else ptscaleunc = 1 - unc;
      //correctedJet.scaleEnergy( ptscaleunc );
      correctedJet.setP4( correctedJet.p4()*ptscaleunc );
      met_x -= correctedJet.px();
      met_y -= correctedJet.py();
    }

    //if(doJERUnc_){
    //  double jetpx = correctedJet.px();
    //  double jetpy = correctedJet.py();
    //  correctedJet.setP4( correctedJet.p4()*resolutionFactor(correctedJet)  );
    //  double dpx = correctedJet.px() - jetpx;
    //  double dpy = correctedJet.py() - jetpy;
    //  met_x -= dpx;
    //  met_y -= dpy;
    //} 

    //debug
    //cout << "corrected= " << correctedJet.pt() << " default= " << it->pt() << endl;
    //cout << "pt cut = " << ptcut_ << endl;
    if ( correctedJet.pt() > ptcut_ ) {
      njet++;
      if( bJetFirst_ ){
        double bTagValue = correctedJet.bDiscriminator(bTagAlgo_.c_str());
        if( bTagValue > bTagValue_ ) {
          corrbJets->push_back(correctedJet);
        }else{
          corrJets->push_back(correctedJet);
        }
      }else{
        corrJets->push_back(correctedJet);
      }
    }

  }

  cmg::BaseMET corrMET(reco::MET ( sqrt(met_x*met_x + met_y*met_y)   , reco::MET::LorentzVector(met_x,met_y,0,sqrt(met_x*met_x + met_y*met_y))  , reco::MET::Point(0,0,0)));
  corrMETs->push_back(corrMET);

  // Jets passing identification criteria are sorted by decreasing pT
  std::sort(corrJets->begin(), corrJets->end(), GreaterByPt<cmg::PFJet>());

  if( bJetFirst_ ){
    std::sort(corrbJets->begin(), corrbJets->end(), GreaterByPt<cmg::PFJet>());
    corrJets->insert( corrJets->begin(), corrbJets->begin(), corrbJets->end());
  }

  if( corrJets->size() >= min_ ) accepted = true;

  if( corrJets->size() > 10 ) { 
    string debug_output = "=================================================== DEBUG ======================================================";
    string e = Form("%i",EVENT);
    string r = Form("%i",RUN);
    string l = Form("%i",LUMI);
    string njetsbefore = Form("%i",njet);
    string njetsafter  = Form("%i",(int)corrJets->size());
    debug_output += "EVENT : " + e + " RUN : " + r + " LUMI : " + l + "\n";
    debug_output += "Number of jets before ID = " + njetsbefore + " Number of jets after ID = " + njetsafter + "\n";
    debug_output += debug_;
    cout << debug_output;
    cout << "DEBUG : END" << endl;
  }

  iEvent.put(corrJets, "Jets");
  iEvent.put(corrMETs, "MET");

  if( applyFilter_ ) return accepted;
  else return true;

}

//double
//CMGJetFilter::resolutionFactor(const cmg::PFJet& jet)
//{
//    if(!jet.genJet()) {
//      return 1.;
//    }
//    double factor = 1. + (resolutionFactor_-1.)*(jet.pt() - jet.genJet()->pt())/jet.pt();
//    return (factor<0 ? 0. : factor);
//}

// ------------ method called once each job just before starting event loop  ------------
void
CMGJetFilter::beginJob()
{

  if ( doJecFly_ ){
    edm::FileInPath jecL1File("KoPFA/CommonTools/python/JEC/chs/"+globalTag_+"_L1FastJet_AK5PFchs.txt");
    edm::FileInPath jecL2File("KoPFA/CommonTools/python/JEC/chs/"+globalTag_+"_L2Relative_AK5PFchs.txt");
    edm::FileInPath jecL3File("KoPFA/CommonTools/python/JEC/chs/"+globalTag_+"_L3Absolute_AK5PFchs.txt");
    edm::FileInPath jecL2L3File("KoPFA/CommonTools/python/JEC/chs/"+globalTag_+"_L2L3Residual_AK5PFchs.txt");
    std::vector<JetCorrectorParameters> jecParams;
    jecParams.push_back(JetCorrectorParameters(jecL1File.fullPath()));
    jecParams.push_back(JetCorrectorParameters(jecL2File.fullPath()));
    jecParams.push_back(JetCorrectorParameters(jecL3File.fullPath()));
    if( doResJec_ ) {
      jecParams.push_back(JetCorrectorParameters(jecL2L3File.fullPath()));
    }
    resJetCorrector_ = new FactorizedJetCorrector(jecParams);
  }

  edm::FileInPath jecUncFile("KoPFA/CommonTools/python/JEC/chs/"+globalTag_+"_Uncertainty_AK5PFchs.txt");
  jecUnc_ = new JetCorrectionUncertainty(jecUncFile.fullPath());

}

// ------------ method called once each job just after ending the event loop  ------------
void
CMGJetFilter::endJob() {
  if ( resJetCorrector_ ) delete resJetCorrector_;
}

bool CMGJetFilter::checkPFJetId(const cmg::PFJet * jet){
    //Loose PF Jet id 
    ///https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID
    //debug
    bool out = false;
    string pt = Form("%f",jet->pt());
    string eta = Form("%f",jet->eta());
    debug_ += "jet pt = " + pt  + " eta = " + eta + "\n";  
    debug_ += "CMG\n";
    string nConstituents = Form("%i",jet->nConstituents());
    debug_ += "number of Daughters : nConstituents() = " + nConstituents + "\n";
    double NHF_cmg = jet->component(5).fraction() + jet->component(6).fraction();
    string NHF2string_cmg = Form("%f",NHF_cmg);
    debug_ += "NHF(<0.99) : component(5).fraction() + component(6).fraction() = " + NHF2string_cmg + "\n";
    string component4fraction = Form("%f",jet->component(4).fraction()); 
    debug_ += "NEF(<0.99) : component(4).fraction() = " + component4fraction + "\n";
    string component2fraction = Form("%f",jet->component(2).fraction());
    debug_ += "CEF(<0.99) : component(2).fraction() = " + component2fraction + "\n";
    string component1fraction = Form("%f",jet->component(1).fraction());
    debug_ += "CHF(>0)    : component(1).fraction() = " + component1fraction + "\n";
    string component1number = Form("%i",jet->component(1).number());
    debug_ += "NCH(>0)    : component(1).number() = " + component1number + "\n";

/*
    debug_ += "PAT\n";
    string numberOfDaughters = Form("%i",(int)jet->sourcePtr()->get()->numberOfDaughters());
    debug_ += "numberOfDaughters= " + numberOfDaughters + "\n";
    double NHF = (jet->sourcePtr()->get()->neutralHadronEnergy() + jet->sourcePtr()->get()->HFHadronEnergy() ) / jet->sourcePtr()->get()->energy();
    string NHF2string = Form("%f",NHF);
    debug_ += "NHF(<0.99) = " + NHF2string +"\n";
    string neutralEmEnergyFraction = Form("%f",jet->sourcePtr()->get()->neutralEmEnergyFraction());
    debug_ += "NEF(<0.99) = " + neutralEmEnergyFraction +"\n";
    string chargedEmEnergyFraction = Form("%f",jet->sourcePtr()->get()->chargedEmEnergyFraction());
    debug_ += "CEF(<0.99) = " + chargedEmEnergyFraction +"\n";
    string chargedHadronEnergyFraction = Form("%f",jet->sourcePtr()->get()->chargedHadronEnergyFraction()) ;
    debug_ += "CHF(>0) = " + chargedHadronEnergyFraction+"\n";
    string chargedMultiplicity = Form("%i",jet->sourcePtr()->get()->chargedMultiplicity());
    debug_ += "NCH(>0) = " + chargedMultiplicity +"\n"; 
*/
    if( (jet->component(5).fraction() + jet->component(6).fraction()) < 0.99
       &&jet->component(4).fraction() < 0.99
       &&jet->nConstituents() > 1
       &&(jet->component(1).fraction() > 0 || abs(jet->eta()) > 2.4)
       &&(jet->component(1).number() > 0 || abs(jet->eta()) > 2.4)
       &&(jet->component(2).fraction() < 0.99 || abs(jet->eta()) > 2.4)        
    ) out = true;

    string tmp = "false";
    if(out) tmp = "true";
    debug_ += "PASS= " + tmp  + "\n";

    return out;
}

//define this as a plug-in
DEFINE_FWK_MODULE(CMGJetFilter);



