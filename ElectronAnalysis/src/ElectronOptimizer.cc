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
  vertexLabel_ =  cfg.getUntrackedParameter<edm::InputTag>("vertexLabel");
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

  multiplicity = -9;
  nVertex = -9;
  mt = -9;
  MET = -9;
  dphi = -9;
  njets = -9;
  dimass = -9;

  ele1_isFromW = -9;
  ele2_isFromW = -9;

  ele1_mva = -9;
  ele2_mva = -9;
  ele1_pt = -9;
  ele2_pt = -9;
  ele1_eta = -9;
  ele2_eta = -9;

  ele1_charge = -9;
  ele2_charge = -9;

  ele1_chIso = -9;
  ele2_chIso = -9;
  ele1_puChIso = -9;
  ele2_puChIso = -9;
  ele1_nhIso = -9;
  ele2_nhIso = -9;
  ele1_phIso = -9;
  ele2_phIso = -9;
  ele1_relIso = -9;
  ele2_relIso = -9;
  ele1_relIso_dbeta = -9;
  ele2_relIso_dbeta = -9;
 
  ele1_chIsoNoVeto = -9;
  ele2_chIsoNoVeto = -9;
  ele1_puChIsoNoVeto = -9;
  ele2_puChIsoNoVeto = -9;
  ele1_nhIsoNoVeto = -9;
  ele2_nhIsoNoVeto = -9;
  ele1_phIsoNoVeto = -9;
  ele2_phIsoNoVeto = -9;
  ele1_relIsoNoVeto = -9;
  ele2_relIsoNoVeto = -9;
  ele1_relIsoNoVeto_dbeta = -9;
  ele2_relIsoNoVeto_dbeta = -9;

  ele1_reco_chIso = -9;
  ele2_reco_chIso = -9;
  ele1_reco_nhIso = -9;
  ele2_reco_nhIso = -9;
  ele1_reco_phIso = -9;
  ele2_reco_phIso = -9;
  ele1_reco_relIso = -9;
  ele2_reco_relIso = -9;

  for ( std::vector<std::string>::const_iterator idName = idNames_.begin();
          idName != idNames_.end(); ++idName ) {
    ele1_Id[*idName] = -9;
    ele2_Id[*idName] = -9;
  }

  iEvent.getByLabel(vertexLabel_,recVtxs_);
  int nv = (int) recVtxs_->size();
  nVertex = nv;  

  iEvent.getByLabel(electronLabel_, electrons_);
  iEvent.getByLabel("offlineBeamSpot",beamSpot_); 
  iEvent.getByLabel(metLabel_,pfMET);
  iEvent.getByLabel(jetLabel_,pfJet);

  iEvent.getByLabel("genParticles",genParticles_);
 
  if( electrons_->size() < 1 ) {
    cout << "ERROR: currently it should bd at least 1" << endl;
  }
 
  njets = 0;
  for (unsigned int i=0; i < pfJet->size(); i++){
    njets++;
  }

  pat::METCollection::const_iterator mi = pfMET->begin();
  MET = mi->pt();
  pat::Electron leading = electrons_->at(0);
  mt = transverseMass( leading.p4(), mi->p4() );
  dphi = fabs(deltaPhi(leading.phi(), mi->p4().phi()));
  multiplicity = electrons_->size();
  
  if(genParticles_.isValid()){
    bool isMatched = isFromW(leading.p4(), genParticles_);
    double match = -1.0;
    if( isMatched ) match = 1.0;
    ele1_isFromW = match;
  }

  ele1_mva = leading.mva();
  ele1_pt = leading.pt();
  ele1_eta = leading.eta();

  ele1_chIso = leading.chargedHadronIso();
  ele1_puChIso = leading.puChargedHadronIso();
  ele1_nhIso = leading.neutralHadronIso();
  ele1_phIso = leading.photonIso();
  ele1_relIso = (leading.chargedHadronIso() + leading.neutralHadronIso() + leading.photonIso()) / leading.pt() ;
  ele1_relIso_dbeta = (leading.chargedHadronIso() + max(0.0, leading.neutralHadronIso() + leading.photonIso() - leading.puChargedHadronIso()*0.5 )) / leading.pt() ;

  ele1_chIsoNoVeto = leading.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3).first;
  ele1_puChIsoNoVeto = leading.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.3).first;
  ele1_nhIsoNoVeto = leading.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3).first;
  ele1_phIsoNoVeto = leading.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3).first;
  ele1_relIsoNoVeto = ( ele1_chIsoNoVeto + ele1_nhIsoNoVeto + ele1_phIsoNoVeto) / ele1_pt ;
  ele1_relIsoNoVeto_dbeta = ( ele1_chIsoNoVeto + max(0.0, ele1_nhIsoNoVeto + ele1_phIsoNoVeto - ele1_puChIsoNoVeto*0.5 )) / ele1_pt ;

  ele1_reco_chIso = leading.pfIsolationVariables().chargedHadronIso;
  ele1_reco_nhIso = leading.pfIsolationVariables().neutralHadronIso;
  ele1_reco_phIso = leading.pfIsolationVariables().photonIso;
  ele1_reco_relIso = ( ele1_reco_chIso + ele1_reco_nhIso + ele1_reco_phIso ) / leading.pt() ;

  ele1_charge = leading.charge();

  for ( std::vector<std::string>::const_iterator idName = idNames_.begin(); idName != idNames_.end(); ++idName ) {
    ele1_Id[*idName] = ((int) leading.electronID(*idName) & 5) == 5;
  }


  if(multiplicity > 1){
    pat::Electron secondleading = electrons_->at(1);
    if(genParticles_.isValid()){
      bool isMatched = isFromW(secondleading.p4(), genParticles_);
      double match = -1.0;
      if( isMatched ) match = 1.0;
      ele2_isFromW = match;
    }    
    dimass = (leading.p4() + secondleading.p4()).M();
    ele2_mva = secondleading.mva();
    ele2_pt = secondleading.pt();
    ele2_eta = secondleading.eta();

    ele2_chIso = secondleading.chargedHadronIso();
    ele2_puChIso = secondleading.puChargedHadronIso();
    ele2_nhIso = secondleading.neutralHadronIso();
    ele2_phIso = secondleading.photonIso();
    ele2_relIso = (secondleading.chargedHadronIso() + secondleading.neutralHadronIso() + secondleading.photonIso()) / secondleading.pt() ;
    ele2_relIso_dbeta = (secondleading.chargedHadronIso() + max(0.0, secondleading.neutralHadronIso() + secondleading.photonIso() - secondleading.puChargedHadronIso()*0.5) ) / secondleading.pt() ;

    ele2_chIsoNoVeto = secondleading.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3).first;
    ele2_puChIsoNoVeto = secondleading.isoDeposit(pat::PfPUChargedHadronIso)->depositAndCountWithin(0.3).first;
    ele2_nhIsoNoVeto = secondleading.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3).first;
    ele2_phIsoNoVeto = secondleading.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3).first;
    ele2_relIsoNoVeto = ( ele2_chIsoNoVeto + ele2_nhIsoNoVeto + ele2_phIsoNoVeto) / ele2_pt;
    ele2_relIsoNoVeto_dbeta = ( ele2_chIsoNoVeto + max(0.0, ele2_nhIsoNoVeto + ele2_phIsoNoVeto - ele2_puChIsoNoVeto*0.5 )) / ele2_pt ;

    ele2_reco_chIso = secondleading.pfIsolationVariables().chargedHadronIso;
    ele2_reco_nhIso = secondleading.pfIsolationVariables().neutralHadronIso;
    ele2_reco_phIso = secondleading.pfIsolationVariables().photonIso;
    ele2_reco_relIso = ( ele2_reco_chIso + ele2_reco_nhIso + ele2_reco_phIso ) / secondleading.pt() ;

    ele2_charge = secondleading.charge();
    for ( std::vector<std::string>::const_iterator idName = idNames_.begin(); idName != idNames_.end(); ++idName ) {
      ele2_Id[*idName] = ((int) secondleading.electronID(*idName) & 5) == 5;
    }
    
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
  tree->Branch("multiplicity",&multiplicity,"multiplicity/i");
  tree->Branch("nVertex",&nVertex,"nVertex/i");
  tree->Branch("njets",&njets,"njets/i");

  tree->Branch("ele1_isFromW",&ele1_isFromW,"ele1_isFromW/D");
  tree->Branch("ele2_isFromW",&ele2_isFromW,"ele2_isFromW/D");

  tree->Branch("ele1_mva",&ele1_mva,"ele1_mva/D");
  tree->Branch("ele2_mva",&ele2_mva,"ele2_mva/D");
  tree->Branch("ele1_pt",&ele1_pt,"ele1_pt/D");
  tree->Branch("ele2_pt",&ele2_pt,"ele2_pt/D");
  tree->Branch("ele1_eta",&ele1_eta,"ele1_eta/D");
  tree->Branch("ele2_eta",&ele2_eta,"ele2_eta/D");
  tree->Branch("ele1_charge",&ele1_charge,"ele1_charge/D");
  tree->Branch("ele2_charge",&ele2_charge,"ele2_charge/D");  
 
  tree->Branch("ele1_chIso",&ele1_chIso,"ele1_chIso/D");
  tree->Branch("ele1_puChIso",&ele1_puChIso,"ele1_puChIso/D");
  tree->Branch("ele1_nhIso",&ele1_nhIso,"ele1_nhIso/D");
  tree->Branch("ele1_phIso",&ele1_phIso,"ele1_phIso/D");
  tree->Branch("ele1_relIso",&ele1_relIso,"ele1_relIso/D");
  tree->Branch("ele1_relIso_dbeta",&ele1_relIso_dbeta,"ele1_relIso_dbeta/D");

  tree->Branch("ele2_chIso",&ele2_chIso,"ele2_chIso/D");
  tree->Branch("ele2_puChIso",&ele2_puChIso,"ele2_puChIso/D");
  tree->Branch("ele2_nhIso",&ele2_nhIso,"ele2_nhIso/D");
  tree->Branch("ele2_phIso",&ele2_phIso,"ele2_phIso/D");
  tree->Branch("ele2_relIso",&ele2_relIso,"ele2_relIso/D");
  tree->Branch("ele2_relIso_dbeta",&ele2_relIso_dbeta,"ele2_relIso_dbeta/D");

  tree->Branch("ele1_chIsoNoVeto",&ele1_chIsoNoVeto,"ele1_chIsoNoVeto/D");
  tree->Branch("ele1_puChIsoNoVeto",&ele1_puChIsoNoVeto,"ele1_puChIsoNoVeto/D");
  tree->Branch("ele1_nhIsoNoVeto",&ele1_nhIsoNoVeto,"ele1_nhIsoNoVeto/D");
  tree->Branch("ele1_phIsoNoVeto",&ele1_phIsoNoVeto,"ele1_phIsoNoVeto/D");
  tree->Branch("ele1_relIsoNoVeto",&ele1_relIsoNoVeto,"ele1_relIsoNoVeto/D");
  tree->Branch("ele1_relIsoNoVeto_dbeta",&ele1_relIsoNoVeto_dbeta,"ele1_relIsoNoVeto_dbeta/D");

  tree->Branch("ele2_chIsoNoVeto",&ele2_chIsoNoVeto,"ele2_chIsoNoVeto/D");
  tree->Branch("ele2_puChIsoNoVeto",&ele2_puChIsoNoVeto,"ele2_puChIsoNoVeto/D");
  tree->Branch("ele2_nhIsoNoVeto",&ele2_nhIsoNoVeto,"ele2_nhIsoNoVeto/D");
  tree->Branch("ele2_phIsoNoVeto",&ele2_phIsoNoVeto,"ele2_phIsoNoVeto/D");
  tree->Branch("ele2_relIsoNoVeto",&ele2_relIsoNoVeto,"ele2_relIsoNoVeto/D");
  tree->Branch("ele2_relIsoNoVeto_dbeta",&ele2_relIsoNoVeto_dbeta,"ele2_relIsoNoVeto_dbeta/D");

  tree->Branch("ele1_reco_chIso",&ele1_reco_chIso,"ele1_reco_chIso/D");
  tree->Branch("ele1_reco_nhIso",&ele1_reco_nhIso,"ele1_reco_nhIso/D");
  tree->Branch("ele1_reco_phIso",&ele1_reco_phIso,"ele1_reco_phIso/D");
  tree->Branch("ele1_reco_relIso",&ele1_reco_relIso,"ele1_reco_relIso/D");

  tree->Branch("ele2_reco_chIso",&ele2_reco_chIso,"ele2_reco_chIso/D");
  tree->Branch("ele2_reco_nhIso",&ele2_reco_nhIso,"ele2_reco_nhIso/D");
  tree->Branch("ele2_reco_phIso",&ele2_reco_phIso,"ele2_reco_phIso/D");
  tree->Branch("ele2_reco_relIso",&ele2_reco_relIso,"ele2_reco_relIso/D");
 

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

void ElectronOptimizer::endLuminosityBlock(const edm::LuminosityBlock & lumi, const edm::EventSetup & setup){

  if(useEventCounter_){
    for(unsigned int i=0;i<filters_.size();++i) {
      std::string name = filters_[i];
      edm::Handle<edm::MergeableCounter> numEventsCounter;
      lumi.getByLabel(name, numEventsCounter);
      if( numEventsCounter.isValid()){
        tmp->AddBinContent(i+1, numEventsCounter->value);
        tmp->GetXaxis()->SetBinLabel(i+1,filters_[i].c_str());
      }
    }
  }

}

bool ElectronOptimizer::isFromW( const reco::Candidate::LorentzVector& lepton, const edm::Handle<reco::GenParticleCollection> & genParticles_ ){

  bool out = false;

  for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
    int genId = mcIter->pdgId();

    if( abs(genId) != 11 ) continue;

    bool match = MatchObjects(lepton, mcIter->p4(), false);

    if( match != true) continue;
   
    const reco::Candidate* mother = mcIter->mother();
    while( mother != 0 ){
      if( abs(mother->pdgId()) == 24 ) { 
        out = true;
      }
      mother = mother->mother();
    }
  }

  return out;
}

bool ElectronOptimizer::MatchObjects( const reco::Candidate::LorentzVector& pasObj,
      const reco::Candidate::LorentzVector& proObj,
      bool exact ) {
    double proEta = proObj.eta();
    double proPhi = proObj.phi();
    double proPt  = proObj.pt();
    double pasEta = pasObj.eta();
    double pasPhi = pasObj.phi();
    double pasPt  = pasObj.pt();

    double dRval = deltaR(proEta, proPhi, pasEta, pasPhi);
    double dPtRel = 999.0;
    if( proPt > 0.0 ) dPtRel = fabs( pasPt - proPt )/proPt;
    // If we are comparing two objects for which the candidates should
    // be exactly the same, cut hard. Otherwise take cuts from user.
    if( exact ) return ( dRval < 1e-3 && dPtRel < 1e-3 );
    else        return ( dRval < 0.025 && dPtRel < 0.025 );
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(ElectronOptimizer);



