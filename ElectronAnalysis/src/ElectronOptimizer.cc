#include "KoPFA/ElectronAnalysis/interface/ElectronOptimizer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "PhysicsTools/SelectorUtils/interface/SimpleCutBasedElectronIDSelectionFunctor.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Common/interface/MergeableCounter.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

using namespace std;

ElectronOptimizer::ElectronOptimizer(const edm::ParameterSet& cfg)
{
  electronLabel_ = cfg.getParameter<edm::InputTag>("electronLabel");
  metLabel_ = cfg.getParameter<edm::InputTag>("metLabel");
  jetLabel_ = cfg.getParameter<edm::InputTag>("jetLabel");
  useEventCounter_ = cfg.getParameter<bool>("useEventCounter");
  filters_ = cfg.getUntrackedParameter<std::vector<std::string> >("filters");

  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for Electron Optimizer");
  tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());
 
  idNames_.push_back("eidVeryLooseMC");
  idNames_.push_back("eidLooseMC");
  idNames_.push_back("eidMediumMC");
  idNames_.push_back("eidTightMC");
  idNames_.push_back("eidSuperTightMC");
  idNames_.push_back("eidHyperTight1MC");
  idNames_.push_back("simpleEleId95relIso");
  idNames_.push_back("simpleEleId90relIso");
  idNames_.push_back("simpleEleId85relIso");
  idNames_.push_back("simpleEleId80relIso");
  idNames_.push_back("simpleEleId70relIso");
  idNames_.push_back("simpleEleId60relIso");

  for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
        idName != idNames_.end(); ++idName )
  {
    ele1_Id[*idName] = 0;
    ele2_Id[*idName] = 0;
  }

}

ElectronOptimizer::~ElectronOptimizer()
{

}

void ElectronOptimizer::analyze(const edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;

  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  iEvent.getByLabel(electronLabel_, electrons_);
  iEvent.getByLabel("offlineBeamSpot",beamSpot_); 
  iEvent.getByLabel(metLabel_,pfMET);
  iEvent.getByLabel(jetLabel_,pfJet);
 
  if( electrons_->size() < 2 ) {
    cout << "ERROR: currently it should bd at least 2" << endl;
  }
 
  njets = 0;
  for (unsigned int i=0; i < pfJet->size(); i++){
    njets++;
  }

  pat::METCollection::const_iterator mi = pfMET->begin();
  MET = mi->pt();
  pat::Electron leading = electrons_->at(0);
  pat::Electron secondleading = electrons_->at(1);
  mt = transverseMass( leading.p4(), mi->p4() );
  dphi = fabs(deltaPhi(leading.phi(), mi->p4().phi()));
  multipliciy = electrons_->size();
  dimass = (leading.p4() + secondleading.p4()).M();

  ele1_mva = leading.mva();
  ele2_mva = secondleading.mva();
  ele1_pt = leading.pt();
  ele2_pt = secondleading.pt();
  ele1_eta = leading.eta();
  ele2_eta = secondleading.eta();
  ele1_chIso = leading.chargedHadronIso();
  ele2_chIso = secondleading.chargedHadronIso();
  ele1_nhIso = leading.neutralHadronIso();
  ele2_nhIso = secondleading.neutralHadronIso();
  ele1_phIso = leading.photonIso();
  ele2_phIso = secondleading.photonIso();
  ele1_relIso = (leading.chargedHadronIso() + leading.neutralHadronIso() + leading.photonIso()) / leading.pt() ;
  ele2_relIso = (secondleading.chargedHadronIso() + secondleading.neutralHadronIso() + secondleading.photonIso()) / secondleading.pt() ;
  ele1_charge = leading.charge();
  ele2_charge = secondleading.charge();

  for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
          idName != idNames_.end(); ++idName ) {
    ele1_Id[*idName] = ((int) leading.electronID(*idName) & 5) == 5;
    ele2_Id[*idName] = ((int) secondleading.electronID(*idName) & 5) == 5;
  }

  tree->Fill();
}

void 
ElectronOptimizer::beginJob(){

  tree->Branch("EVENT",&EVENT,"EVENT/i");
  tree->Branch("RUN",&RUN,"RUN/i");
  tree->Branch("LUMI",&LUMI,"LUMI/i");

  tree->Branch("mt",&mt,"mt/D");
  tree->Branch("dimass",&dimass,"dimass/d");
  tree->Branch("MET",&MET,"MET/d");
  tree->Branch("dphi",&dphi,"dphi/d");
  tree->Branch("multipliciy",&multipliciy,"multipliciy/i");
  tree->Branch("njets",&njets,"njets/i");

  tree->Branch("ele1_mva",&ele1_mva,"ele1_mva/D");
  tree->Branch("ele2_mva",&ele2_mva,"ele2_mva/D");
  tree->Branch("ele1_pt",&ele1_pt,"ele1_pt/D");
  tree->Branch("ele2_pt",&ele2_pt,"ele2_pt/D");
  tree->Branch("ele1_eta",&ele1_eta,"ele1_eta/D");
  tree->Branch("ele2_eta",&ele2_eta,"ele2_eta/D");
  tree->Branch("ele1_charge",&ele1_charge,"ele1_charge/D");
  tree->Branch("ele2_charge",&ele2_charge,"ele2_charge/D");  
 
  tree->Branch("ele1_chIso",&ele1_chIso,"ele1_chIso/D");
  tree->Branch("ele1_nhIso",&ele1_nhIso,"ele1_nhIso/D");
  tree->Branch("ele1_phIso",&ele1_phIso,"ele1_phIso/D");
  tree->Branch("ele1_relIso",&ele1_relIso,"ele1_relIso/D");

  tree->Branch("ele2_chIso",&ele2_chIso,"ele2_chIso/D");
  tree->Branch("ele2_nhIso",&ele2_nhIso,"ele2_nhIso/D");
  tree->Branch("ele2_phIso",&ele2_phIso,"ele2_phIso/D");
  tree->Branch("ele2_relIso",&ele2_relIso,"ele2_relIso/D");

  

  for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
        idName != idNames_.end(); ++idName )
  {
    tree->Branch(("ele1_"+*idName).c_str(), &(ele1_Id[*idName]), ("ele1_"+*idName+"/i").c_str());
    tree->Branch(("ele2_"+*idName).c_str(), &(ele2_Id[*idName]), ("ele2_"+*idName+"/i").c_str());
  }

}

void
ElectronOptimizer::endJob() {

}

double ElectronOptimizer::transverseMass( const reco::Candidate::LorentzVector& lepton,
                                     const reco::Candidate::LorentzVector& met) {

    reco::Candidate::LorentzVector leptonT(lepton.Px(),lepton.Py(),0.,lepton.E()*sin(lepton.Theta()));
    reco::Candidate::LorentzVector sumT=leptonT+met;
    return std::sqrt(sumT.M2());
}

void ElectronOptimizer::endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & setup){

  if(useEventCounter_){
    for(unsigned int i=0;i<filters_.size();++i) {
      std::string name = filters_[i];
      cout << name << endl;
      edm::Handle<edm::MergeableCounter> numEventsCounter;
      lumi.getByLabel(name, numEventsCounter);
      if( numEventsCounter.isValid()){
        tmp->AddBinContent(i+1, numEventsCounter->value);
        tmp->GetXaxis()->SetBinLabel(i+1,filters_[i].c_str());
      }else cout << "not valid" << endl;
    }
  }

}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(ElectronOptimizer);



