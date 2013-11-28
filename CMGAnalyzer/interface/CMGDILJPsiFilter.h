// -*- C++ -*-
//
// Package:    TopDILJPsiAnalyzer
// Class:      TopDILJPsiAnalyzer
// 
/**\class TopDILJPsiAnalyzer TopDILJPsiAnalyzer.cc UserCode/TopDILJPsiAnalyzer/src/TopDILJPsiAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Tae Jeong Kim,40 R-A32,+41227678602,
//         Created:  Fri Jun  4 17:19:29 CEST 2010
// $Id: CMGDILJPsiFilter.h,v 1.6 2013/02/07 09:53:21 tjkim Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EventSetup.h"
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
#include "KoPFA/DataFormats/interface/Lepton.h"
#include "KoPFA/DataFormats/interface/ZCandidate.h"
#include "KoPFA/DataFormats/interface/JPsiCandidate.h"
#include "KoPFA/DataFormats/interface/LepJPsiCandidate.h"
#include "KoPFA/DataFormats/interface/TTbarGenEvent.h"
#include "KoPFA/DataFormats/interface/TTbarMass.h"
#include "KoPFA/DataFormats/interface/METCandidate.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"

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
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/PatternTools/interface/TwoTrackMinimumDistance.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "TMath.h"
#include "Math/VectorUtil.h"
#include "TVector3.h"

/*#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "TrackingTools/PatternTools/interface/TSCBLBuilderNoMaterial.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
*/

//
// class declaration
//
using namespace edm;
using namespace std;
using namespace reco;
using namespace isodeposit;
typedef Candidate::LorentzVector LorentzVector;

template<typename T1, typename T2, typename T3, typename T4>
class CMGDILJPsiFilter : public edm::EDFilter {
 public:
  explicit CMGDILJPsiFilter(const edm::ParameterSet& iConfig){
    //now do what ever initialization is needed
    applyFilter_ = iConfig.getUntrackedParameter<bool>("applyFilter",true);
    //addMCTruth_ = iConfig.getUntrackedParameter<bool>("addMCTruth",true);
    muonLabel1_ = iConfig.getParameter<edm::InputTag>("muonLabel1"); //Z
    muonLabel2_ = iConfig.getParameter<edm::InputTag>("muonLabel2"); //Z
    muonLabel3_ = iConfig.getParameter<edm::InputTag>("muonLabel3"); //JPsi
    muonLabel4_ = iConfig.getParameter<edm::InputTag>("muonLabel4"); //JPsi
    min_ = iConfig.getParameter<double>("min");  
    max_ = iConfig.getParameter<double>("max");  
    relIso1_ = iConfig.getUntrackedParameter<double>("relIso1");
    relIso2_ = iConfig.getUntrackedParameter<double>("relIso2");
    vertexLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("vertexLabel");//jkim, offlinePrimaryVertices
    //thebeamspot_ = iConfig.getParameter<edm::InputTag>("beamSpotTag");
    rhoIsoLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("rhoIsoLabel");

    produces<std::vector<vallot::ZCandidate> >("DiLepton");
    produces<std::vector<vallot::JPsiCandidate> >("JPsi");
    produces<std::vector<vallot::LepJPsiCandidate> >("LepJPsi1");
    produces<std::vector<vallot::LepJPsiCandidate> >("LepJPsi2");
    produces<std::vector<T1> >("Lepton1");
    produces<std::vector<T2> >("Lepton2");
    produces<std::vector<T3> >("Lepton3");
    produces<std::vector<T4> >("Lepton4");

  }

  // ------------ method called once each job just after ending the event loop  ------------
  void
  endJob() {
  }


  ~CMGDILJPsiFilter(){}

 private:
  //virtual void produce(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    bool accept = false;
    const bool isRealData = iEvent.isRealData();

    std::auto_ptr<std::vector<vallot::ZCandidate> > dilp(new std::vector<vallot::ZCandidate>());
    std::auto_ptr<std::vector<vallot::ZCandidate> > seldilp(new std::vector<vallot::ZCandidate>());
    std::auto_ptr<std::vector<vallot::JPsiCandidate> > JPsi(new std::vector<vallot::JPsiCandidate>());
    std::auto_ptr<std::vector<vallot::JPsiCandidate> > selJPsi(new std::vector<vallot::JPsiCandidate>());
    std::auto_ptr<std::vector<vallot::LepJPsiCandidate> > lpJPsi1(new std::vector<vallot::LepJPsiCandidate>());
    std::auto_ptr<std::vector<vallot::LepJPsiCandidate> > lpJPsi2(new std::vector<vallot::LepJPsiCandidate>());
    std::auto_ptr<std::vector<vallot::LepJPsiCandidate> > sellpJPsi1(new std::vector<vallot::LepJPsiCandidate>());
    std::auto_ptr<std::vector<vallot::LepJPsiCandidate> > sellpJPsi2(new std::vector<vallot::LepJPsiCandidate>());

    std::auto_ptr<std::vector<T1> > lep1(new std::vector<T1>());
    std::auto_ptr<std::vector<T2> > lep2(new std::vector<T2>());
    std::auto_ptr<std::vector<T3> > lep3(new std::vector<T3>());
    std::auto_ptr<std::vector<T4> > lep4(new std::vector<T4>());
    std::auto_ptr<std::vector<T1> > sellep1(new std::vector<T1>());
    std::auto_ptr<std::vector<T2> > sellep2(new std::vector<T2>());
    std::auto_ptr<std::vector<T3> > sellep3(new std::vector<T3>());
    std::auto_ptr<std::vector<T4> > sellep4(new std::vector<T4>());

    edm::Handle<std::vector<T1> > muons1_;
    edm::Handle<std::vector<T2> > muons2_;
    edm::Handle<std::vector<T3> > muons3_;
    edm::Handle<std::vector<T4> > muons4_;
    edm::Handle<reco::VertexCollection> recVtxs_;
    edm::Handle<reco::BeamSpot> theBeamSpot;

    iEvent.getByLabel(muonLabel1_,muons1_);
    iEvent.getByLabel(muonLabel2_,muons2_);
    iEvent.getByLabel(muonLabel3_,muons3_);
    iEvent.getByLabel(muonLabel4_,muons4_);
    iEvent.getByLabel(vertexLabel_,recVtxs_);
    //iEvent.getByLabel(thebeamspot_,theBeamSpot);

    //Vertex theBeamSpotV;
    //BeamSpot bs = *theBeamSpot;
    //theBeamSpotV = Vertex(bs.position(), bs.covariance3D());

    edm::Handle<double>  rho_;
    iEvent.getByLabel(rhoIsoLabel_, rho_);
    double rhoIso = *(rho_.product());

    edm::ESHandle<TransientTrackBuilder> theTTBuilder;
    iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theTTBuilder);

    std::auto_ptr<std::vector<reco::Vertex> > goodOfflinePrimaryVertices(new std::vector<reco::Vertex>());
    int nvertex = 0 ;
    for(unsigned int i=0; i < recVtxs_->size();  ++i){
      reco::Vertex v = recVtxs_->at(i);
      if (!(v.isFake()) && (v.ndof()>4) && (fabs(v.z())<=24.0) && (v.position().Rho()<=2.0) ) {
        goodOfflinePrimaryVertices->push_back((*recVtxs_)[i]);
        nvertex++;
      }
    }

    for(unsigned i = 0; i != muons1_->size(); i++){
      for(unsigned j = 0; j != muons2_->size(); j++){
        for(unsigned k = 0; k != muons3_->size(); k++){
          for(unsigned m = k+1; m != muons4_->size(); m++){
             T1 it1 = muons1_->at(i);
             T2 it2 = muons2_->at(j);
             T3 it3 = muons3_->at(k);
             T4 it4 = muons4_->at(m);

             const bool match = MatchObjects( it1.p4(), it2.p4(), true)
                           || MatchObjects( it1.p4(), it3.p4(), true)
                           || MatchObjects( it1.p4(), it4.p4(), true)
                           || MatchObjects( it2.p4(), it3.p4(), true)
                           || MatchObjects( it2.p4(), it4.p4(), true)
                           || MatchObjects( it3.p4(), it4.p4(), true);

             if(match) continue;

             if( nvertex < 1 ) continue;

             reco::Vertex pv = goodOfflinePrimaryVertices->at(0);
             const bool pass3 = JPsilepSel(it3, pv);
             const bool pass4 = JPsilepSel(it4, pv);

             //if(!pass3 && !pass4) continue;
             if(!(pass3 && pass4)) continue;

             vallot::Lepton lepton1(it1.p4(), (int) it1.charge());
             vallot::Lepton lepton2(it2.p4(), (int) it2.charge());
             vallot::Lepton lepton3(it3.p4(), (int) it3.charge());
             vallot::Lepton lepton4(it4.p4(), (int) it4.charge());

            //pf isolation setup
            lepton1.setPFIsoValues03( it1.chargedHadronIso(0.3), it1.puChargedHadronIso(0.3), it1.neutralHadronIso(0.3), it1.photonIso(0.3) );
            lepton2.setPFIsoValues03( it2.chargedHadronIso(0.3), it2.puChargedHadronIso(0.3), it2.neutralHadronIso(0.3), it2.photonIso(0.3) );
            lepton1.setPFIsoValues04( it1.chargedHadronIso(0.4), it1.puChargedHadronIso(0.4), it1.neutralHadronIso(0.4), it1.photonIso(0.4) );
            lepton2.setPFIsoValues04( it2.chargedHadronIso(0.4), it2.puChargedHadronIso(0.4), it2.neutralHadronIso(0.4), it2.photonIso(0.4) );

            double AEff03Lep1 = 0.00;
            double AEff04Lep1 = 0.00;

            double AEff03Lep2 = 0.00;
            double AEff04Lep2 = 0.00;

            if( !it1.isMuon() ){
              double sceta1 = it1.sourcePtr()->get()->superCluster()->eta(); 
              AEff03Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, sceta1, ElectronEffectiveArea::kEleEAData2012);
              AEff04Lep1 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04, sceta1, ElectronEffectiveArea::kEleEAData2012);
            }

            if( !it2.isMuon() ){ 
              double sceta2 = it2.sourcePtr()->get()->superCluster()->eta(); 
              AEff03Lep2 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, sceta2, ElectronEffectiveArea::kEleEAData2012);
              AEff04Lep2 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso04, sceta2, ElectronEffectiveArea::kEleEAData2012);
            }
   
            lepton1.setRho( rhoIso );
            lepton2.setRho( rhoIso );
            lepton1.setAEff03( AEff03Lep1 );
            lepton2.setAEff03( AEff03Lep2 );
            lepton1.setAEff04( AEff04Lep1 );
            lepton2.setAEff04( AEff04Lep2 );

            //detector based isolation
            double trackIso1 = it1.sourcePtr()->get()->trackIso();
            double ecalIso1 = it1.sourcePtr()->get()->ecalIso();
            double hcalIso1 = it1.sourcePtr()->get()->hcalIso();

            double trackIso2 = it2.sourcePtr()->get()->trackIso();
            double ecalIso2 = it2.sourcePtr()->get()->ecalIso();
            double hcalIso2 = it2.sourcePtr()->get()->hcalIso();

            lepton1.setIsoDeposit( trackIso1, ecalIso1, hcalIso1);
            lepton2.setIsoDeposit( trackIso2, ecalIso2, hcalIso2);
  
            double lepton1_relIso03 = 999;
            double lepton2_relIso03 = 999;

            if( it1.isMuon() ) {
               lepton1.setType(1);
               lepton1_relIso03 = lepton1.relIso03(1);  
            }else{
               lepton1.setType(0);
               lepton1_relIso03 = lepton1.relIso03(2);
            }
 
            if( it2.isMuon() ) {
              lepton2.setType(1);
              lepton2_relIso03 = lepton1.relIso03(1);
            }else{
              lepton2.setType(0);
              lepton2_relIso03 = lepton1.relIso03(2);
            }

            LorentzVector jpsiLV = it3.p4() + it4.p4();

            double vNChi2 =-999;
            double vProb = -999;
            double ctauPV = -999;
            double ctauErrPV = -999;
            double dlPV = -999;
            //double dlErrPV = -999;
            //double ctauBS = -999;
            //double ctauErrBS = -999;
            float genRefJpmomId = 0;
            double DlTrue = -999.;
            double ppdlTrue = -999.;

            if(it3.sourcePtr()->get()->track().isNonnull() && it4.sourcePtr()->get()->track().isNonnull()) {
               vector<TransientTrack> t_tks;
               //TrackRef tk3 = it3.sourcePtr()->get()->track();
               //TrackRef tk4 = it4.sourcePtr()->get()->track();
               //TransientTrack ttkp3 = (*theTTBuilder).build(&tk3);
               //TransientTrack ttkp4 = (*theTTBuilder).build(&tk4);
               //t_tks.push_back(ttkp3);
               //t_tks.push_back(ttkp4);

               t_tks.push_back(theTTBuilder->build(it3.sourcePtr()->get()->track()));
               t_tks.push_back(theTTBuilder->build(it4.sourcePtr()->get()->track()));  

               KalmanVertexFitter vtxFitter;
               TransientVertex myVertex = vtxFitter.vertex(t_tks);
            
               if (myVertex.isValid()) {
                  double vChi2 = myVertex.totalChiSquared();
                  double vNDF  = myVertex.degreesOfFreedom();
                  vNChi2 = vChi2/vNDF;
                  double vprob(TMath::Prob(vChi2,(int)vNDF));
                  vProb = vprob;
   
                  TVector3 vtx;
                  TVector3 vtx3;
                  TVector3 pvtx;
                  TVector3 pvtx3;
                  VertexDistanceXY vdistXY;
   
                  vtx.SetXYZ(myVertex.position().x(),myVertex.position().y(),0);
                  vtx3.SetXYZ(myVertex.position().x(),myVertex.position().y(),myVertex.position().z());
                  TVector3 pperp(jpsiLV.px(), jpsiLV.py(), 0);
                  TVector3 Jpsip(jpsiLV.px(), jpsiLV.py(), jpsiLV.pz());
                  AlgebraicVector3 vpperp(pperp.x(),pperp.y(),0.);
                  AlgebraicVector3 vJpsip(Jpsip.x(),Jpsip.y(),Jpsip.z());
                
                  // lifetime using PV
                  pvtx.SetXYZ(pv.position().x(),pv.position().y(),0);
                  pvtx3.SetXYZ(pv.position().x(),pv.position().y(),pv.position().z());
                  TVector3 vdiff = vtx - pvtx;
                  TVector3 vdiff3 = vtx3 - pvtx3;
                  double cosAlpha = vdiff.Dot(pperp)/(vdiff.Perp()*pperp.Perp());
                  Measurement1D distXY = vdistXY.distance(Vertex(myVertex), pv);
                  ctauPV = distXY.value()*cosAlpha * ((lepton3+lepton4).M())/pperp.Perp();
                  dlPV = vdiff3.Mag(); 
                  GlobalError v1e = (Vertex(myVertex)).error();
                  GlobalError v2e = pv.error();
                  AlgebraicSymMatrix33 vXYe = v1e.matrix()+ v2e.matrix();
                  ctauErrPV = sqrt(ROOT::Math::Similarity(vpperp,vXYe))*((lepton3+lepton4).M())/(pperp.Perp2());
                  //dlErrPV = sqrt(ROOT::Math::Similarity(vJpsip,vXYe));

                  //lifetime using BS
                  /*pvtx.SetXYZ(theBeamSpotV.position().x(),theBeamSpotV.position().y(),0);
                  vdiff = vtx - pvtx;
                  cosAlpha = vdiff.Dot(pperp)/(vdiff.Perp()*pperp.Perp());
                  distXY = vdistXY.distance(Vertex(myVertex), theBeamSpotV);
                  //double ctauBS = distXY.value()*cosAlpha*3.09688/pperp.Perp();
                  ctauBS = distXY.value()*cosAlpha*((lepton3+lepton4).M())/pperp.Perp();
                  GlobalError v1eB = (Vertex(myVertex)).error();
                  GlobalError v2eB = theBeamSpotV.error();
                  AlgebraicSymMatrix33 vXYeB = v1eB.matrix()+ v2eB.matrix();
                  //double ctauErrBS = sqrt(vXYeB.similarity(vpperp))*3.09688/(pperp.Perp2());
                  ctauErrBS = sqrt(ROOT::Math::Similarity(vpperp,vXYeB))*((lepton3+lepton4).M())/(pperp.Perp2());*/

               }
            }
            //cout<<"dlPV : "<<dlPV<<" /dlErrPV : "<<dlErrPV<<"ctauPV : "<<ctauPV<<" /ctauErrPV : "<<ctauErrPV<<" /ctauBS : "<<ctauBS<<" /ctauErrBS : "<<ctauErrBS<<endl;

            // ---- MC Truth, if enabled ----
           if (!isRealData){ //&& genParticles_.isValid()) {
              //float genReflep1moId = 0;
              //float genReflep2moId = 0;
              reco::GenParticleRef genlep1 = it1.sourcePtr()->get()->genParticleRef();
              reco::GenParticleRef genlep2 = it2.sourcePtr()->get()->genParticleRef();
              reco::GenParticleRef genlep3 = it3.sourcePtr()->get()->genParticleRef();
              reco::GenParticleRef genlep4 = it4.sourcePtr()->get()->genParticleRef();
              if (genlep1.isNonnull() && genlep2.isNonnull() 
                  && genlep3.isNonnull() && genlep4.isNonnull()){

               // if (genlep1->numberOfMothers()>0 && genlep2->numberOfMothers()>0){
                 //  reco::GenParticleRef mom1 = genlep1->motherRef();
                 //  reco::GenParticleRef mom2 = genlep2->motherRef();
                 //  if (mom1.isNonnull() && mom2.isNonnull() && (mom1 != mom2)) {
                      /*if (isFromt(genlep1) && isFromtbar(genlep2)){
                         genReflep1moId = 6;
                         genReflep2moId = -6;
                      }
                      if (isFromtbar(genlep1) && isFromt(genlep2)){
                         genReflep1moId = -6;
                         genReflep2moId = 6;
                      }
                      cout<<"grlepmoid : "<<genReflep1moId<<" / "<<genReflep2moId<<endl;*/
                  // }
                //} 
                  /*else {
                  Handle<GenParticleCollection>theGenParticles;
                  iEvent.getByLabel("genParticlesPruned", theGenParticles);
                  if (theGenParticles.isValid()){
                     for(size_t iGenParticle=0; iGenParticle<theGenParticles->size();++iGenParticle){
                       const Candidate & genCand = (*theGenParticles)[iGenParticle];
                       if (fabs(genCand.pdgId()==11) || fabs(genCand.pdgId()==13)){
                          reco::GenParticleRef mom1(theGenParticles,iGenParticle);
                          if (isFromt(mom1)){
                             genReflep1moId = 6;
                             genReflep2moId = -6;
                           }
                           if (isFromtbar(mom1)){
                            genReflep1moId = -6;
                            genReflep2moId = 6;
                           }
                           cout<<"(else)grlepmoid : "<<genReflep1moId<<" / "<<genReflep2moId<<endl;
                       }
                    }
                  }
                }*/

                if (genlep3->numberOfMothers()>0 && genlep4->numberOfMothers()>0){
                   reco::GenParticleRef mom3 = genlep3->motherRef();
                   reco::GenParticleRef mom4 = genlep4->motherRef();
                   if (mom3.isNonnull() && mom4.isNonnull() && (mom3 == mom4) && mom3->pdgId()==443) {
                      
                      std::pair<double, double> dlTrue = getJPsidlTrue(mom3);
                      genRefJpmomId = getMomID(mom3);
                      DlTrue = dlTrue.first;
                      ppdlTrue = dlTrue.second;
                      //cout<<"dlPV : "<<dlPV<<" /dlErrPV : "<<dlErrPV<<endl;
                      cout<<"grJPmoid : "<<genRefJpmomId<<" 3DlTrue : "<<DlTrue<<" /ppdlTrue : "<<ppdlTrue<<endl;
                   }
                   //cout<<"grJPmoid : "<<genRefJpmomId<<" 3DlTrue : "<<DlTrue<<" /ppdlTrue : "<<ppdlTrue<<endl;
                } /*else {
                  Handle<GenParticleCollection>theGenParticles;
                  iEvent.getByLabel("genParticles", theGenParticles);
                  if (theGenParticles.isValid()){
                     for(size_t iGenParticle=0; iGenParticle<theGenParticles->size();++iGenParticle){
                       const Candidate & genCand = (*theGenParticles)[iGenParticle];
                       if (genCand.pdgId()==443 || genCand.pdgId()==100443 ||
                          genCand.pdgId()==553 || genCand.pdgId()==100553 || genCand.pdgId()==200553){
                          reco::GenParticleRef mom3(theGenParticles,iGenParticle);
                          std::pair<double, double> dlTrue = getJPsidlTrue(mom3);
                          genRefJpmomId = genCand.pdgId();
                          DlTrue = dlTrue.first;
                          ppdlTrue = dlTrue.second;
                          cout<<"(else)grJPmoid : "<<genRefJpmomId<<" 3DlTrue : "<<DlTrue<<" /ppdlTrue : "<<ppdlTrue<<endl;
                       }
                    }
                  }
                }*/

              }
            }
          
            bool iso = lepton1_relIso03 < relIso1_ && lepton2_relIso03 < relIso2_;
            bool opp = it1.sourcePtr()->get()->charge() * it2.sourcePtr()->get()->charge() < 0;
            bool oppJPsi = it3.sourcePtr()->get()->charge() * it4.sourcePtr()->get()->charge() < 0;

            vallot::ZCandidate dimuon(lepton1, lepton2);
            vallot::JPsiCandidate jpsi(lepton3, lepton4, vProb, dlPV, ctauPV, ctauErrPV, genRefJpmomId, DlTrue, ppdlTrue);
            vallot::LepJPsiCandidate lJPsi1(lepton1, lepton3, lepton4);
            vallot::LepJPsiCandidate lJPsi2(lepton2, lepton3, lepton4);

            if( iso && opp && oppJPsi){
              seldilp->push_back( dimuon );
              selJPsi->push_back( jpsi );
              sellpJPsi1->push_back(lJPsi1);
              sellpJPsi2->push_back(lJPsi2);
              sellep1->push_back( (*muons1_)[i] );
              sellep2->push_back( (*muons2_)[j] );      
              sellep3->push_back( (*muons3_)[k] );
              sellep4->push_back( (*muons4_)[m] );
            }else{
              dilp->push_back( dimuon );
              //JPsi->push_back( jpsi );
              //lpJPsi1->push_back(lJPsi1);
              //lpJPsi2->push_back(lJPsi2);
              lep1->push_back( (*muons1_)[i] );
              lep2->push_back( (*muons2_)[j] );
              //lep3->push_back( (*muons3_)[k] );
              //lep4->push_back( (*muons4_)[m] );
             
            }
        
          }
        }
      }
    }
   
    double minMassDiff = 999;
    for(int i=0;i<(int)selJPsi->size();i++){
       double massDiff = fabs(selJPsi->at(i).mass()-3.0968799);
       if( massDiff < minMassDiff ){ 
          minMassDiff = massDiff;
          selJPsi->insert(selJPsi->begin(),selJPsi->at(i));
          sellpJPsi1->insert(sellpJPsi1->begin(),sellpJPsi1->at(i));
          sellpJPsi2->insert(sellpJPsi2->begin(),sellpJPsi2->at(i));
          sellep3->insert(sellep3->begin(),sellep3->at(i));
          sellep4->insert(sellep4->begin(),sellep4->at(i));
          //cout<<"************"<<minMassDiff<<"/"<<selJPsi->at(0).mass()<<endl;
       }
    }

    if( seldilp->size() > 0 && selJPsi->size() > 0){
      dilp->insert( dilp->begin(), seldilp->begin(), seldilp->end());
      JPsi->insert( JPsi->begin(), selJPsi->begin(), selJPsi->end());
      lpJPsi1->insert(lpJPsi1->begin(), sellpJPsi1->begin(), sellpJPsi1->end());
      lpJPsi2->insert(lpJPsi2->begin(), sellpJPsi2->begin(), sellpJPsi2->end());
      lep1->insert( lep1->begin(), sellep1->begin(), sellep1->end());
      lep2->insert( lep2->begin(), sellep2->begin(), sellep2->end());
      lep3->insert( lep3->begin(), sellep3->begin(), sellep3->end());
      lep4->insert( lep4->begin(), sellep4->begin(), sellep4->end());
    }
    //ESHandle<SetupData> pSetup;
    //iSetup.get<SetupRecord>().get(pSetup);

    if( dilp->size() > 0 && dilp->at(0).mass() >  min_ ) { 
      accept = true;
    }

    /*if(seldilp->size() > 0 && JPsi->size() > 0){
       cout << "nZ: "<<dilp->size()<<" / nJPsi: " << JPsi->size() <<endl;
       for(int i=0;i<(int)dilp->size();i++){
          cout<<"Z Mass["<<i<<"] : "<<dilp->at(i).mass()<<endl;
       }

       for(int i=0;i<(int)JPsi->size();i++){
          //if((JPsi->at(0).mass())!=(selJPsi->at(0).mass())){ 
            cout<<"JPsi Mass["<<i<<"] : "<<JPsi->at(i).mass(); 
            cout<<"/"<<selJPsi->at(0).mass()<<endl;
          //}
       }
       cout<<"--------------------------------------------------"<<endl;
    }*/

    iEvent.put(dilp,"DiLepton");
    iEvent.put(JPsi,"JPsi");
    iEvent.put(lpJPsi1,"LepJPsi1");
    iEvent.put(lpJPsi2,"LepJPsi2");
    iEvent.put(lep1,"Lepton1");
    iEvent.put(lep2,"Lepton2");
    iEvent.put(lep3,"Lepton3");
    iEvent.put(lep4,"Lepton4");

    if(applyFilter_) return accept;
    else return true;

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

  bool JPsilepSel(const cmg::Muon& cmgMu, const reco::Vertex pv){
     //Tight Muon
     /*bool passPre = cmgMu.pt() > 0.0 && fabs(cmgMu.eta()) < 2.5
                   && cmgMu.sourcePtr()->get()->isPFMuon()
                   && (cmgMu.sourcePtr()->get()->isGlobalMuon() || cmgMu.sourcePtr()->get()->isTrackerMuon())
                   && cmgMu.normalizedChi2() < 10
                   && cmgMu.trackerLayersWithMeasurement() > 5
                   && cmgMu.numberOfValidMuonHits() > 0
                   && fabs((*(cmgMu.sourcePtr()))->innerTrack()->dxy(pv.position())) < 0.2 //jkim?
                   && fabs((*(cmgMu.sourcePtr()))->innerTrack()->dz(pv.position())) < 0.5 //jkim?
                   && cmgMu.pixelLayersWithMeasurement() > 0
                   && cmgMu.numberOfMatchedStations() > 1;*/
      
      //loose+soft Muon 
      bool passPre = cmgMu.pt() > 0.0 && fabs(cmgMu.eta()) < 2.4 //ok
                   && cmgMu.sourcePtr()->get()->isPFMuon();
                   //&& (cmgMu.sourcePtr()->get()->isGlobalMuon() || cmgMu.sourcePtr()->get()->isTrackerMuon())
                   //&& cmgMu.isTMOST() //ok
                   //&& cmgMu.trackerLayersWithMeasurement() > 5 //ok
                   //&& cmgMu.pixelLayersWithMeasurement() > 1 //ok
                   //&& cmgMu.tkNormalizedChi2() < 1.8 //ok
                   //&& fabs((*(cmgMu.sourcePtr()))->innerTrack()->dxy(pv.position())) < 3.
                   //&& fabs((*(cmgMu.sourcePtr()))->innerTrack()->dz(pv.position())) < 30.;

      //Loose Muon
/*      bool passPre = cmgMu.pt() > 0.0 && fabs(cmgMu.eta()) < 2.4 
                   && cmgMu.sourcePtr()->get()->isPFMuon()
                   && (cmgMu.sourcePtr()->get()->isGlobalMuon() || cmgMu.sourcePtr()->get()->isTrackerMuon());*/

      return passPre;

  }

  bool JPsilepSel(const cmg::Electron& cmgEl, const reco::Vertex pv){
        bool passPre = cmgEl.pt() > 0.0 && fabs(cmgEl.eta()) < 2.5
                   && cmgEl.sourcePtr()->get()->isPF()
                   && fabs( cmgEl.sourcePtr()->get()->superCluster()->eta() ) > 1.4442
                   && fabs( cmgEl.sourcePtr()->get()->superCluster()->eta() ) < 1.5660
                   && fabs( cmgEl.sourcePtr()->get()->gsfTrack()->dxy(pv.position()) ) < 0.02;
                   //&& cmgEl.sourcePtr()->get()->passConversionVeto()
                   //&& cmgEl.mvaTrigV0()>0.5
                   //&& cmgEl.sourcePtr()->get()->gsfTrack()->trackerExpectedHitsInner().numberOfHits()<=0;

        return passPre;

  }

  int getMomID(reco::GenParticleRef genJpsi) {
    int moid = 999;
    bool bHadron = false;
    bool top = false;

    if (genJpsi->numberOfMothers()>0) {
      reco::GenParticleRef Jpsimom = genJpsi->motherRef();
      while( Jpsimom.isNonnull() ){
        string id = Form("%i", Jpsimom->pdgId());
        cout<<"Jpsimomid : "<<id<<endl;
        if( abs(Jpsimom->pdgId()) == 511 || abs(Jpsimom->pdgId()) == 521 
            || abs(Jpsimom->pdgId()) == 531 || abs(Jpsimom->pdgId()) == 541 
            || abs(Jpsimom->pdgId()) == 5122 || abs(Jpsimom->pdgId()) == 5132 
            || abs(Jpsimom->pdgId()) == 5232 || abs(Jpsimom->pdgId()) == 5332) {
            //cout<<"momID : "<<id<<endl;
            bHadron = true;
        }
        if(abs(Jpsimom->pdgId()) == 6) top = true;
        if(abs(Jpsimom->pdgId()) == 2212) {
           moid = 0; 
           break;
        }
        Jpsimom = Jpsimom->motherRef();
      }
    }

    if(bHadron && top) moid = 6;
    if(bHadron && !top) moid = 5;
    //if(!bHadron && !top) moid = 2212;
    cout<<"return moid: "<<moid<<endl; 
 
    return moid;
  }

  std::pair<double, double> getJPsidlTrue(reco::GenParticleRef genJpsi) {

    //int momJpsiID = 0;
    double true3Dl = -999.;
    double trueLife = -999.;

    if (genJpsi->numberOfMothers()>0) {
  
      TVector3 trueVtx(0.0,0.0,0.0);
      TVector3 trueP(0.0,0.0,0.0);
      TVector3 trueVtxMom(0.0,0.0,0.0);

      trueVtx.SetXYZ(genJpsi->vertex().x(),genJpsi->vertex().y(),genJpsi->vertex().z());
      trueP.SetXYZ(genJpsi->momentum().x(),genJpsi->momentum().y(),genJpsi->momentum().z());

      reco::GenParticleRef Jpsimom = genJpsi->motherRef();
      while( Jpsimom.isNonnull() ){
        string id = Form("%i", Jpsimom->pdgId());
        //cout<<"Jpsimomid : "<<id<<endl;
        if( abs(Jpsimom->pdgId()) == 6 ) {
          //cout<<"momID : "<<id<<endl;
          trueVtxMom.SetXYZ(Jpsimom->vertex().x(),Jpsimom->vertex().y(),Jpsimom->vertex().z());
          //cout<<"tb vx : "<<Form("%f",Jpsimom->vertex().x())<<" vy : "<<Form("%f",Jpsimom->vertex().y())<<" vz : "<<Form("%f",Jpsimom->vertex().z())<<endl;
          break;
        }
        if(abs(Jpsimom->pdgId()) == 2212 ) break;
        //cout<<"Jpsimomid : "<<id<<endl;
        trueVtxMom.SetXYZ(Jpsimom->vertex().x(),Jpsimom->vertex().y(),Jpsimom->vertex().z());
        Jpsimom = Jpsimom->motherRef();
      }
      //cout<<"while end--------------"<<endl;

      TVector3 vdiff = trueVtx - trueVtxMom;
      //trueLife = vdiff.Perp()*3.09688/trueP.Perp();
      trueLife = vdiff.Perp()*genJpsi->mass()/trueP.Perp();
      true3Dl = vdiff.Mag();
    }

    std::pair<double, double> result = std::make_pair(true3Dl, trueLife);
    return result;
  
  }


  bool applyFilter_;
  edm::InputTag muonLabel1_;
  edm::InputTag muonLabel2_;
  edm::InputTag muonLabel3_;
  edm::InputTag muonLabel4_;
  edm::InputTag vertexLabel_;
  //edm::InputTag thebeamspot_;
  edm::InputTag rhoIsoLabel_;

  double min_;
  double max_;
  double relIso1_;
  double relIso2_;
  
};

