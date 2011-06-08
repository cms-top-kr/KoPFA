#include "KoPFA/CommonTools/interface/pfElectronAnalyzer.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "PhysicsTools/SelectorUtils/interface/SimpleCutBasedElectronIDSelectionFunctor.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

// #include "TauAnalysis/CandidateTools/interface/FetchCollection.h"
using namespace std;

pfElectronAnalyzer::pfElectronAnalyzer(const edm::ParameterSet& cfg)
{
  ptcut_ = cfg.getUntrackedParameter<double>("ptcut",20);
  etacut_ = cfg.getUntrackedParameter<double>("etacut",2.5);
  electronLabel_ = cfg.getParameter<edm::InputTag>("electronLabel");
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");

  edm::Service<TFileService> fs;

  cutNames.push_back("eidVeryLooseMC");
  cutNames.push_back("eidLooseMC");
  cutNames.push_back("eidMediumMC");
  cutNames.push_back("eidTightMC");
  cutNames.push_back("eidSuperTightMC");
  cutNames.push_back("eidHyperTight1MC");
  //cutNames.push_back("eidHyperTight2MC");
  //cutNames.push_back("eidHyperTight3MC");
  //cutNames.push_back("eidHyperTight4MC");
  int nBins = (int) cutNames.size();

  id2iso = fs->make<TH2F>("id2iso","id2iso", 40, 0, 0.4, nBins, -0.5 , nBins-0.5);  
  id2isoQCD = fs->make<TH2F>("id2isoQCD","id2isoQCD", 40, 0, 0.4, nBins, -0.5,nBins-0.5);
    
  id = fs->make<TH1F>( "id", "id", nBins, -0.5, nBins-0.5);
  idQCD = fs->make<TH1F>( "idQCD", "idQCD", nBins, -0.5, nBins-0.5);
  idLike = fs->make<TH1F>( "idLike", "idLike", nBins, -0.5, nBins-0.5);
  idQCDLike = fs->make<TH1F>( "idQCDLike", "idQCDLike", nBins, -0.5, nBins-0.5);


}

pfElectronAnalyzer::~pfElectronAnalyzer()
{

}

void pfElectronAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;

  //EVENT  = iEvent.id().event();
  //RUN    = iEvent.id().run();
  //LUMI   = iEvent.id().luminosityBlock();

  iEvent.getByLabel(electronLabel_, electrons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 

  int cut[6];
  for(int i =0 ; i < (int)cutNames.size() ; i++){
    cut[i] = 0;
  }

  bool find = false;

  for (unsigned int i=0; i < electrons_->size()-1;++i){
    if(find) break;
    for (unsigned int j=i+1; j < electrons_->size();++j){
      if(find) break;
      pat::Electron it1 = electrons_->at(i);
      pat::Electron it2 = electrons_->at(j);
  
      reco::isodeposit::Direction Dir1 = Direction(it1.eta(),it1.phi());
      reco::isodeposit::Direction Dir2 = Direction(it2.eta(),it2.phi());
      reco::isodeposit::AbsVetos vetos_ch;
      reco::isodeposit::AbsVetos vetos_nh;
      vetos_nh.push_back(new ThresholdVeto( 0.5 ));
      reco::isodeposit::AbsVetos vetos_ph1;
      vetos_ph1.push_back(new ThresholdVeto( 0.5 ));
      //vetos_ph1.push_back(new RectangularEtaPhiVeto( Dir1, -0.1, 0.1, -0.2, 0.2));
      reco::isodeposit::AbsVetos vetos_ph2;
      vetos_ph2.push_back(new ThresholdVeto( 0.5 ));
      //vetos_ph2.push_back(new RectangularEtaPhiVeto( Dir2, -0.1, 0.1, -0.2, 0.2));

      double chIso1 = it1.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
      double nhIso1 = it1.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
      double phIso1 = it1.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph1).first;

      double chIso2 = it2.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.3, vetos_ch).first;
      double nhIso2 = it2.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.3, vetos_nh).first;
      double phIso2 = it2.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.3, vetos_ph2).first;

      double relIso1 = (chIso1 + nhIso1+ phIso1)/it1.pt();
      double relIso2 = (chIso2 + nhIso2+ phIso2)/it2.pt();

      bool passPre1 = it1.pt() > ptcut_ && fabs(it1.eta()) < etacut_ && fabs(it1.gsfTrack()->dxy(beamSpot_->position())) < 0.04;
      bool passPre2 = it2.pt() > ptcut_ && fabs(it2.eta()) < etacut_ && fabs(it2.gsfTrack()->dxy(beamSpot_->position())) < 0.04;
      
      if( !passPre1 || !passPre2) continue;

      double dimass = (it1.p4()+it2.p4()).M();
      if( dimass < 12) continue;
      bool qcd = relIso2 > 0.5 && fabs( dimass - 91) > 30 ;

      for(int i = 0 ; i < (int)cutNames.size() ; i++){
        int eidBit1 = (int)it1.electronID(cutNames[i]);
        int eidBit2 = (int)it2.electronID(cutNames[i]);
        bool passID1 = (eidBit1 & 5) == 5; // eidMask = 5 : 1(id)+4(con) 
        bool passID2 = (eidBit2 & 5) == 5; // eidMask = 5 : 1(id)+4(con) 

        if(passID1 && passID2) { 
          id->Fill(i); 
          id2iso->Fill(relIso1, i);
          if(it1.charge()*it2.charge() > 0) idLike->Fill(i);
          if(qcd){
            idQCD->Fill(i);
            id2isoQCD->Fill(relIso1,i);
            if(it1.charge()*it2.charge() > 0) idQCDLike->Fill(i);
          }
          find = true;
        }
      } //ID loop

    }
  }

}

void 
pfElectronAnalyzer::beginJob(){

}

void
pfElectronAnalyzer::endJob() {
  id2iso->GetXaxis()->SetTitle("RelIso");
  id2iso->GetYaxis()->SetTitle("ID");
  id->GetXaxis()->SetTitle("ID");
  id->GetYaxis()->SetTitle("Entries");

  id2isoQCD->GetXaxis()->SetTitle("RelIso");
  id2isoQCD->GetYaxis()->SetTitle("ID");
  idQCD->GetXaxis()->SetTitle("ID");
  idQCD->GetYaxis()->SetTitle("Entries");

  for(int i=0 ; i < (int) cutNames.size(); i++){
    id2iso->GetYaxis()->SetBinLabel(i+1,cutNames[i].c_str());
    id->GetXaxis()->SetBinLabel(i+1,cutNames[i].c_str());
    id2isoQCD->GetYaxis()->SetBinLabel(i+1,cutNames[i].c_str());
    idQCD->GetXaxis()->SetBinLabel(i+1,cutNames[i].c_str());
  }

}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(pfElectronAnalyzer);



