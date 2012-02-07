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
// $Id: TopLJAnalyzer.h,v 1.1 2012/02/06 12:38:27 bhlee Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/EDProducer.h"

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
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/WCandidate.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "KoPFA/DataFormats/interface/TTbarMass.h"
#include "KoPFA/DataFormats/interface/METCandidate.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/Core/interface/DQMStore.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
//#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"
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
class TopLJAnalyzer : public edm::EDFilter {
 public:
  explicit TopLJAnalyzer(const edm::ParameterSet& iConfig){
    //now do what ever initialization is needed
    muonLabel_ = iConfig.getParameter<edm::InputTag>("muonLabel");
    metLabel_ = iConfig.getParameter<edm::InputTag>("metLabel");
    jetLabel_ = iConfig.getParameter<edm::InputTag>("jetLabel");
    genParticlesLabel_= iConfig.getParameter<edm::InputTag>("genParticlesLabel");
    vertexLabel_ =  iConfig.getUntrackedParameter<edm::InputTag>("vertexLabel");
    metStudy_ = iConfig.getUntrackedParameter<bool>("metStudy",false);
    useEventCounter_ = iConfig.getParameter<bool>("useEventCounter");
    filters_ = iConfig.getUntrackedParameter<std::vector<std::string> >("filters");
    //pfJetIdParams_ = iConfig.getParameter<edm::ParameterSet> ("looseJetId");
    relIso_ = iConfig.getUntrackedParameter<double>("relIso");
    bTagAlgo_ = iConfig.getUntrackedParameter<std::string>("bTagAlgo");
    minBTagValue_ = iConfig.getUntrackedParameter<double>("minBTagValue");
    
    PileUpRD_ = iConfig.getParameter< std::vector<double> >("PileUpRD");
    PileUpMC_ = iConfig.getParameter< std::vector<double> >("PileUpMC");

    //doJecFly_ = iConfig.getUntrackedParameter<bool>("doJecFly", true);
    //doResJec_ = iConfig.getUntrackedParameter<bool>("doResJec", false);
    //doJecUnc_ = iConfig.getUntrackedParameter<bool>("doJecUnc", false);
    //resolutionFactor_ = iConfig.getUntrackedParameter<double>("resolutionFactor", 1.0);
    //up_ = iConfig.getUntrackedParameter<bool>("up", true); // uncertainty up
    //resJetCorrector_ = 0;
    //jecUnc_ = 0;

    edm::Service<TFileService> fs;
    tree = fs->make<TTree>("tree", "Tree for Top quark study");
    tmp = fs->make<TH1F>("EventSummary","EventSummary",filters_.size(),0,filters_.size());

    h_leadingpt   = fs->make<TH1F>( "h_leadingpt"  , "p_{t}", 50,  0., 100. );
    h_transversemass      = fs->make<TH1F>( "h_transversemass", "transverseMass", 100, 0., 200. );
    h_MET       = fs->make<TH1F>( "h_MET", "MET", 40, 0, 80);
    h_jet_multi = fs->make<TH1F>( "h_jet_multi", "jet_multi", 10, 0, 10);
    h_jetpt30_multi = fs->make<TH1F>( "h_jetpt30_multi", "jet30pt_multi", 10, 0, 10);
    h_bjet_multi = fs->make<TH1F>( "h_bjet_multi", "bjet_multi", 10, 0, 10);
    h_npileupin = fs->make<TH1F>( "h_npileupin", "npileupin", 30, 0, 30);
    h_npileup = fs->make<TH1F>( "h_npileup", "npileup", 30, 0, 30);
    h_nvertex = fs->make<TH1F>( "h_nvertex", "nvertex", 30, 0, 30);

    W = new std::vector<Ko::WCandidate>();
    lepton = new std::vector<Ko::Lepton>();
    pfMet = new std::vector<Ko::METCandidate>();
    ttbar = new std::vector<Ko::TTbarMass>();
    met = new std::vector<math::XYZTLorentzVector>();
    jets = new std::vector<math::XYZTLorentzVector>();
    jetspt30 = new std::vector<math::XYZTLorentzVector>();
    bjets = new std::vector<math::XYZTLorentzVector>();
 
  }


  ~TopLJAnalyzer()
  {
    //if ( resJetCorrector_ ) delete resJetCorrector_;
    //if ( jecUnc_ ) delete jecUnc_;
  }

 private:
  virtual void beginJob() 
  {
  	//cout << "test1" << endl;
    tree->Branch("EVENT",&EVENT,"EVENT/i");
    tree->Branch("RUN",&RUN,"RUN/i");
    tree->Branch("LUMI",&LUMI,"LUMI/i");
    tree->Branch("npileup",&npileup,"npileup/i");
    tree->Branch("nvertex",&nvertex,"nvertex/i");
    tree->Branch("weightin",&weightin, "weightin/d");
    tree->Branch("weight",&weight, "weight/d");
    tree->Branch("weightplus",&weightplus, "weightplus/d");
    tree->Branch("weightminus",&weightminus, "weightminus/d");
    //tree->Branch("weight3D",&weight3D, "weight3D/d");

    //tree->Branch("WtransverseMass",&WtransverseMass,"WtransverMass/d");
    tree->Branch("relIso",&relIso,"relIso/d");
    tree->Branch("pt",&pt,"pt/d");
    tree->Branch("eta",&eta,"eta/d");

    //tree->Branch("W","std::vector<Ko::WCandidate>", &W);
    //tree->Branch("lepton","std::vector<Ko::Lepton>", &lepton);
    //tree->Branch("pfMet","std::vector<Ko::METCandidate>", &pfMet);
    //tree->Branch("ttbar","std::vector<Ko::TTbarMass>", &ttbar);

    //tree->Branch("met","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &met);
    //tree->Branch("jets","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jets);
    tree->Branch("jetspt30","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &jetspt30);
    //tree->Branch("bjets","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &bjets);
    tree->Branch("nbjets",&nbjets,"nbjets/d");

    tree->Branch("MET",&MET,"MET/d");
    //tree->Branch("dphimetlepton",&dphimetlepton,"dphimetlepton/d");
    //tree->Branch("dphimetjet1",&dphimetjet1,"dphimetjet1/d");
    //tree->Branch("dphimetjet2",&dphimetjet2,"dphimetjet2/d");
    //tree->Branch("dphimetjet3",&dphimetjet3,"dphimetjet3/d");
    //tree->Branch("dphimetjet4",&dphimetjet4,"dphimetjet4/d");

    //tree->Branch("genttbarM",&genttbarM,"genttbarM/d");
    //tree->Branch("resmaosM",&resmaosM,"resmaosM/d");
    //tree->Branch("resvsumM",&resvsumM,"resvsumM/d");
    //tree->Branch("resuser1M",&resuser1M,"resuser1M/d");
    //tree->Branch("resuser2M",&resuser2M,"resuser2M/d");

    //tree->Branch("sumEt",&sumEt,"sumEt/d");
    //tree->Branch("photonEt",&photonEt,"photonEt/d");
    //tree->Branch("chargedHadronEt",&chargedHadronEt,"chargedHadronEt/d");
    //tree->Branch("neutralHadronEt",&neutralHadronEt,"neutralHadronEt/d");
	//cout << "test2" << endl;
    // Jet energy correction for 38X
    /*if ( doJecFly_ )
    {
      edm::FileInPath jecL1File("KoPFA/TopAnalyzer/python/JEC/chs/GR_R_42_V19_AK5PFchs_L1FastJet.txt");
      edm::FileInPath jecL2File("KoPFA/TopAnalyzer/python/JEC/chs/GR_R_42_V19_AK5PFchs_L2Relative.txt");
      edm::FileInPath jecL3File("KoPFA/TopAnalyzer/python/JEC/chs/GR_R_42_V19_AK5PFchs_L3Absolute.txt");
      edm::FileInPath jecL2L3File("KoPFA/TopAnalyzer/python/JEC/chs/GR_R_42_V19_AK5PFchs_L2L3Residual.txt");
      std::vector<JetCorrectorParameters> jecParams;
      jecParams.push_back(JetCorrectorParameters(jecL1File.fullPath()));
      jecParams.push_back(JetCorrectorParameters(jecL2File.fullPath()));
      jecParams.push_back(JetCorrectorParameters(jecL3File.fullPath()));
      if( doResJec_ ) {
        jecParams.push_back(JetCorrectorParameters(jecL2L3File.fullPath()));
      }
      resJetCorrector_ = new FactorizedJetCorrector(jecParams);
    }

    if ( doJecUnc_){
        edm::FileInPath jecUncFile("KoPFA/TopAnalyzer/python/JEC/Jec11_V2_AK5PF_Uncertainty.txt");
        jecUnc_ = new JetCorrectionUncertainty(jecUncFile.fullPath());
    }*/

    std::vector< float > Wlumi ;
    std::vector< float > TrueDist2011;

    for( int i=0; i<25; ++i) {
      TrueDist2011.push_back((float)PileUpRD_[i]);
      Wlumi.push_back((float)PileUpMC_[i]);
    }

    LumiWeights_ = edm::LumiReWeighting(Wlumi, TrueDist2011);

    PShiftDown_ = reweight::PoissonMeanShifter(-0.5);
    PShiftUp_ = reweight::PoissonMeanShifter(0.5);//1D reweighting
    
	/*for( int i=0; i<55; ++i) {
      TrueDist2011.push_back((float)PileUpRD_[i]);
      Wlumi.push_back((float)PileUpMC_[i]);
    }
	LumiWeights_ = edm::Lumi3DReWeighting(Wlumi, TrueDist2011);*///3D reweighting

  }


  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {

    bool accept = false;

    clear();

    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.id().luminosityBlock();

    edm::Handle<double>  rho;
    iEvent.getByLabel(edm::InputTag("kt6PFJetsPFlow","rho"), rho);

    edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
    iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);

    std::vector<PileupSummaryInfo>::const_iterator PVI;

    int npv = -1;
    float sum_nvtx = 0;
    float ave_nvtx = 0;
    if( PupInfo.isValid()){
      for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
        int tmpnpv = PVI->getPU_NumInteractions();
        sum_nvtx += float(tmpnpv);

        int BX = PVI->getBunchCrossing();

        if(BX == 0) {
          npv = PVI->getPU_NumInteractions();
          continue;
        }

      } 

      ave_nvtx = sum_nvtx/3.;

      weightin = LumiWeights_.weight( npv );
      weight = LumiWeights_.weight3BX( ave_nvtx );
      weightplus  = weight*PShiftUp_.ShiftWeight( ave_nvtx );
      weightminus = weight*PShiftDown_.ShiftWeight( ave_nvtx );
    }else{
      weightin = 1.0;
      weight = 1.0;
      weightplus = 1.0;
      weightminus = 1.0;
    }

    h_npileupin->Fill(npv);
    h_npileup->Fill(ave_nvtx);

    npileup = npv;//1D reweighting

	/*int npvm1 = -1; int npv0 = -1; int npvp1 = -1;
	if( PupInfo.isValid() ){
		for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI){
			int BX = PVI->getBunchCrossing();

			if(BX == -1){
				npvm1 = PVI->getPU_NumInteractions();
			}
			if(BX == 0){
				npv0 = PVI->getPU_NumInteractions();
			}
			if(BX == 1){
				npvp1 = PVI->getPU_NumInteractions();
			}
		}
		weight3D = LumiWeights_.weight3D( npvm1, npv0, npvp1);
    }
	h_npileup->Fill(npv0);

    npileup = npv0;*///3D reweighting

    edm::Handle<reco::VertexCollection> recVtxs_;
    iEvent.getByLabel(vertexLabel_,recVtxs_);

    int nv = 0 ;

    for(reco::VertexCollection::const_iterator v=recVtxs_->begin();  v!=recVtxs_->end(); ++v){
      if (!(v->isFake()) && (v->ndof()>4) && (fabs(v->z())<=24.0) && (v->position().Rho()<=2.0) ) {
            nv++;
      }
    }

    nvertex = nv;

    h_nvertex->Fill(nv);

    //edm::Handle<double> weight_;
    //iEvent.getByLabel("PUweight", weight_);

    //if(weight_.isValid()){
    //  weight = *weight_;
    //}else{
    //  weight = 1.0;
    //}

    edm::Handle<std::vector<T1> > muons_;
    edm::Handle<pat::METCollection> MET_;
    iEvent.getByLabel(muonLabel_,muons_);
    iEvent.getByLabel(metLabel_,MET_);
	//cout << "test3" << endl;
    pat::METCollection::const_iterator mei = MET_->begin();
	//MET = mei->pt();
    met->push_back(mei->p4());
    //h_MET->Fill(MET);
    edm::Handle< reco::PFCandidateCollection > pfCandidates_;
    typedef reco::PFCandidateCollection::const_iterator CI;
    iEvent.getByLabel("particleFlow",pfCandidates_);

    sumEt = 0;
    photonEt = 0;
    chargedHadronEt = 0;
    neutralHadronEt = 0;

    //for(CI ci = pfCandidates_->begin(); ci!=pfCandidates_->end(); ++ci) {
    //  const reco::PFCandidate& pfc = *ci;
    //  double E = pfc.energy();
    //  double theta = pfc.theta();
    //  double sintheta = sin(theta);
    //  double et = E*sintheta;
    //  sumEt += et;
    //  if( pfc.particleId() == 1 ) chargedHadronEt += et;
    //  if( pfc.particleId() == 5 ) neutralHadronEt += et;
    //  if( pfc.particleId() == 4 ) photonEt += et; 
    //} 

    edm::Handle<pat::JetCollection> Jets;
    iEvent.getByLabel(jetLabel_, Jets);

    edm::Handle<reco::GenParticleCollection> genParticles_;
    iEvent.getByLabel(genParticlesLabel_,genParticles_);

    //PFJetIDSelectionFunctor looseJetIdSelector_(pfJetIdParams_);
	//cout << "test4" << endl;
    for(unsigned i = 0; i != muons_->size(); i++){
        T1 it1 = muons_->at(i);
        it1.setP4(it1.pfCandidateRef()->p4());

        const Ko::Lepton lep(it1.p4(), (int) it1.charge());
        lepton->push_back(lep);

        reco::isodeposit::Direction Dir1 = Direction(it1.eta(),it1.phi());
        reco::isodeposit::AbsVetos vetos_ch;
        reco::isodeposit::AbsVetos vetos_nh;
        vetos_nh.push_back(new ThresholdVeto( 0.5 ));
        reco::isodeposit::AbsVetos vetos_ph;
        vetos_ph.push_back(new ThresholdVeto( 0.5 ));
        //vetos_ph.push_back(new RectangularEtaPhiVeto( Dir1, -0.1, 0.1, -0.2, 0.2));

        //pf isolation setup
        lepton->back().setIsoDeposit( pat::PfChargedHadronIso, it1.isoDeposit(pat::PfChargedHadronIso), vetos_ch );
        lepton->back().setIsoDeposit( pat::PfNeutralHadronIso, it1.isoDeposit(pat::PfNeutralHadronIso), vetos_nh );
        lepton->back().setIsoDeposit( pat::PfGammaIso, it1.isoDeposit(pat::PfGammaIso), vetos_ph );
    
        //detector based isolation
        lepton->back().setIsoDeposit( it1.trackIso(), it1.ecalIso(), it1.hcalIso());

        //explicitly require sign of one isolated lepton
        const Ko::WCandidate muonmet(lepton->back(), met->back());
        if( muonmet.transversemass() <= 12 ) continue;

        bool selected = false;
        if(!selected) {
          selected = true;
          W->push_back(muonmet);
          WtransverseMass = muonmet.transversemass();
          relIso = lepton->back().relpfIso03();
          pt = it1.pt();
          eta = it1.eta();
        }

        accept = true;
        dphimetlepton = fabs(deltaPhi(mei->phi(),it1.phi()));
 
        W->push_back(muonmet);
        WtransverseMass = muonmet.transversemass();
        relIso = lepton->back().relpfIso03();
        pt = it1.pt();
        eta = it1.eta();
        
        h_leadingpt->Fill(it1.pt());
        h_transversemass->Fill(muonmet.transversemass());

        break;
    }
	//cout << "test5" << endl;
    //double met_x = mei->px();
    //double met_y = mei->py();

    //Jet selection by checking overlap with selected leptons
    for (JI jit = Jets->begin(); jit != Jets->end(); ++jit) {

      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrjet;
      corrjet.SetPxPyPzE(jit->px(),jit->py(),jit->pz(),jit->energy());

      /*double scaleF = 1.0;
      if(doJecFly_){
		reco::Candidate::LorentzVector uncorrJet = jit->correctedP4(0);

		corrjet.SetPxPyPzE(uncorrJet.px(),uncorrJet.py(),uncorrJet.pz(),uncorrJet.energy());
		resJetCorrector_->setJetEta( uncorrJet.eta() );
		resJetCorrector_->setJetPt ( uncorrJet.pt() );
		resJetCorrector_->setJetE  ( uncorrJet.energy() );
		resJetCorrector_->setJetA  ( jit->jetArea() );
		resJetCorrector_->setRho   ( *(rho.product()) );
		resJetCorrector_->setNPV   ( nv );

		scaleF = resJetCorrector_->getCorrection();
		corrjet *= scaleF;
      }

      if(doJecUnc_){
		jecUnc_->setJetEta(corrjet.eta());
		jecUnc_->setJetPt(corrjet.pt());
		met_x += corrjet.px();
		met_y += corrjet.py();
		double unc = jecUnc_->getUncertainty(up_);
		//double c_sw = 0.015; //for release differences and calibration changes
		double c_sw = 0.0; //for release differences and calibration changes
		//double c_pu = 0.2*0.8*2.2/(corrjet.pt()); // PU uncertainty
		double c_pu = 0.0; // PU uncertainty
		double c_bjets = 0.03; // bjet uncertainty
		//if(corrjet.pt() > 50 && corrjet.pt() < 200 && fabs(corrjet.eta()) < 2.0) {
		//  c_bjets = 0.02;
		//}else c_bjets = 0.03;

		double cor = sqrt(c_sw*c_sw + c_pu*c_pu+c_bjets*c_bjets);
		unc = sqrt(unc*unc + cor*cor);
		double ptscaleunc = 0;
		if(up_) ptscaleunc = 1 + unc;
		else ptscaleunc = 1 - unc;
		corrjet *= ptscaleunc;
		met_x -= corrjet.px();
		met_y -= corrjet.py();
      }

      //geometric acceptance
      if(fabs(jit->eta()) >= 2.4) continue;

      pat::strbitset looseJetIdSel = looseJetIdSelector_.getBitTemplate();
      bool passId = looseJetIdSelector_( *jit, looseJetIdSel);

      //jet id
      if(passId){
		//const double dRval = deltaR(jit->eta(), jit->phi(), it1.eta(), it1.phi());
		//bool overlap = checkOverlap(jit->eta(),jit->phi(),dRval,lepton->back.relpfIso03());
		//cout << "test6" << endl;
		//jet cleaning
		//if( overlap ) continue;*/

		jets->push_back(corrjet);

		if(corrjet.pt() > 30){
	  		jetspt30->push_back(corrjet);
	  		discr = jit->bDiscriminator(bTagAlgo_);
	  		if(discr > minBTagValue_){
	    		bjets->push_back(corrjet);
	  		}
		}
      //}
    }
	//cout << "test7" << endl;
    if( jetspt30->size() >= 4 ){
      dphimetjet1 = fabs(deltaPhi(mei->phi(),jetspt30->at(0).phi()));
      dphimetjet2 = fabs(deltaPhi(mei->phi(),jetspt30->at(1).phi()));
      dphimetjet3 = fabs(deltaPhi(mei->phi(),jetspt30->at(2).phi()));
      dphimetjet4 = fabs(deltaPhi(mei->phi(),jetspt30->at(3).phi()));
    }
	//cout << "test8" << endl;
    h_jet_multi->Fill(jets->size());
    h_jetpt30_multi->Fill(jetspt30->size());
    h_bjet_multi->Fill(bjets->size());

    nbjets = bjets->size();

    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > corrmet;
    //corrmet.SetPxPyPzE(met_x,met_y,0,sqrt(met_x*met_x + met_y*met_y));
    //MET = sqrt(met_x*met_x + met_y*met_y);
    corrmet.SetPxPyPzE(mei->px(),mei->py(),0,mei->pt());
    MET = mei->pt();
    met->push_back(corrmet);
	//cout << "test9" << endl;
    if(metStudy_){
      const Ko::METCandidate pfmet(MET, mei->sumEt(), mei->NeutralEMFraction(),mei->NeutralHadEtFraction(),mei->ChargedHadEtFraction(),mei->ChargedEMEtFraction(),mei->MuonEtFraction() );
      pfMet->push_back(pfmet);
    }
	//cout << "test10" << endl;
    h_MET->Fill(MET);

    if(jetspt30->size() >= 4 && WtransverseMass > 12){
      ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > lep;
      lep.SetPxPyPzE(W->back().leg1().px(),W->back().leg1().py(),W->back().leg1().pz(),W->back().leg1().energy());

      const Ko::TTbarMass ttbarMass(lep, jetspt30->at(0), jetspt30->at(1), jetspt30->at(2), jetspt30->at(3), met->at(0));
      ttbar->push_back(ttbarMass);

      	/*if(genParticles_.isValid()){

		TLorentzVector ttbarGen(0,0,0,0);
		for (reco::GenParticleCollection::const_iterator mcIter=genParticles_->begin(); mcIter != genParticles_->end(); mcIter++ ) {
	  		int genId = mcIter->pdgId();
	  		if( fabs(genId) == 6){
	    		//double mass = mcIter->p4().M(); 
	    		TLorentzVector top(mcIter->p4().Px(), mcIter->p4().Py(), mcIter->p4().Pz(), mcIter->p4().E());
	    		ttbarGen = ttbarGen+top;
	  		}

		}

		genttbarM = ttbarGen.M();
		//resmaosM = ttbar->back().maosM() - ttbarGen.M();
		resvsumM = ttbar->back().M() - ttbarGen.M();
		//resuser1M = ttbar->back().user1M() - ttbarGen.M();
		//resuser2M = ttbar->back().user2M() - ttbarGen.M();
      }*/
    }
	//cout << "test11" << endl;

    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);
    tree->Fill();

    return accept;

  }

  void clear(){

    W->clear();
    lepton->clear();
    pfMet->clear();
    ttbar->clear();
    met->clear();
    jets->clear();
    jetspt30->clear();
    bjets->clear();

    nbjets = -999;

    weight = 1.0;
    weightplus = 1.0;
    weightminus = 1.0;
	//weight3D = 1.0;

    dphimetlepton = -999;  
    dphimetjet1 = -999;
    dphimetjet2 = -999;
    dphimetjet3 = -999;
    dphimetjet4 = -999;

    WtransverseMass = -999; 
    relIso = -999;
    pt = -999; 
    eta = -999;

    genttbarM = -999;
    //resmaosM = -999; 
    resvsumM = -999;
    //resuser1M = -999;
    //resuser2M = -999;

    sumEt = -1;
    photonEt = -1;
    chargedHadronEt = -1;
    neutralHadronEt = -1;

  }

  virtual bool endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & setup){
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
    return true;
  }

  bool checkOverlap(const double & eta, const double & phi, const double & dRval1, const double & reliso)
  {

    bool overlap = false;
    if( reliso < relIso_ ) {
      overlap = dRval1 < 0.4 ;
      if(overlap) return overlap;
    }

    return overlap;

  }

  bool MatchObjects( const reco::Candidate::LorentzVector& pasObj,
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

  /*double resolutionFactor(const pat::Jet& jet)
  {
    if(!jet.genJet()) { return 1.; }
    double factor = 1. + (resolutionFactor_-1.)*(jet.pt() - jet.genJet()->pt())/jet.pt();
    return (factor<0 ? 0. : factor);
  }*/

  typedef pat::JetCollection::const_iterator JI;

  edm::InputTag muonLabel_;
  edm::InputTag metLabel_;
  edm::InputTag jetLabel_;
  edm::InputTag genParticlesLabel_;
  edm::InputTag vertexLabel_;

  std::vector<std::string> filters_;
  bool metStudy_;
  bool useEventCounter_;
  
  // relIso
  double relIso_;
  // btag Discriminator
  std::string bTagAlgo_;
  double minBTagValue_;

  TTree* tree;

  TH1F * tmp;
  TH1F * h_leadingpt;
  TH1F * h_secondpt;
  TH1F * h_transversemass;
  TH1F * h_MET;
  TH1F * h_jet_multi;
  TH1F * h_jetpt30_multi;
  TH1F * h_bjet_multi;
  TH1F * h_npileupin;
  TH1F * h_npileup;
  TH1F * h_nvertex;

  std::vector<Ko::WCandidate>* W;
  std::vector<Ko::Lepton>* lepton;
  std::vector<Ko::METCandidate>* pfMet;
  std::vector<Ko::TTbarMass>* ttbar;
  std::vector<math::XYZTLorentzVector>* met;
  std::vector<math::XYZTLorentzVector>* jets;
  std::vector<math::XYZTLorentzVector>* jetspt30;
  std::vector<math::XYZTLorentzVector>* bjets;
  
  double MET;
  double dphimetlepton;
  double dphimetjet1;
  double dphimetjet2;
  double dphimetjet3;
  double dphimetjet4;
  double WtransverseMass;
  double relIso;
  double pt;
  double eta;

  double nbjets;

  double discr;

  double genttbarM;
  //double resmaosM;
  double resvsumM;
  //double resuser1M;
  //double resuser2M;

  double sumEt;
  double photonEt;
  double chargedHadronEt;
  double neutralHadronEt;


  // ----------member data ---------------------------

  //add run event data
  unsigned int EVENT;
  unsigned int RUN;
  unsigned int LUMI;
  unsigned int npileup;
  unsigned int nvertex;
  double weightin;
  double weight;
  double weightplus;
  double weightminus;
  //double weight3D;

  edm::LumiReWeighting LumiWeights_;
  //edm::Lumi3DReWeighting LumiWeights_;

  std::vector<double> PileUpRD_;
  std::vector<double> PileUpMC_;

  reweight::PoissonMeanShifter PShiftUp_;
  reweight::PoissonMeanShifter PShiftDown_;

  // Residual Jet energy correction for 38X
  //bool doJecFly_;
  //bool doResJec_;
  //bool doJecUnc_;
  //bool up_;
  //FactorizedJetCorrector* resJetCorrector_;
  //JetCorrectionUncertainty *jecUnc_;
  //double resolutionFactor_;

  //edm::ParameterSet pfJetIdParams_;

};

