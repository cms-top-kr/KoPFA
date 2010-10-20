#include "KoPFA/CommonTools/interface/KoElectronSelector.h"
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

KoElectronSelector::KoElectronSelector(const edm::ParameterSet& cfg)
{
  version_ = cfg.getUntrackedParameter<int>("version", 1);
  electronLabel_ = cfg.getParameter<edm::InputTag>("electronLabel");
  electronIdSelector_.initialize( cfg.getParameter<edm::ParameterSet>("electronIdSelector") );
  electronIsoSelector_.initialize( cfg.getParameter<edm::ParameterSet>("electronIsoSelector") );
  beamSpotLabel_ = cfg.getParameter<edm::InputTag>("beamSpotLabel");
  produces<std::vector<pat::Electron> >("");
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for electron study");

  cutNames.push_back("pre");
  cutNames.push_back("dxy");
  cutNames.push_back("isGlobal");
  cutNames.push_back("isTracker");
  cutNames.push_back("trackerHits");
  cutNames.push_back("chi2");

  int nBins = (int) cutNames.size();
  cutflow   = fs->make<TH1F>( "cutflow", "cutflow", nBins,-0.5,nBins-0.5);
  id2mva = fs->make<TH2F>( "id2mva","id2mva", 200, -1,1, 8,0,8);  
  pfMVA2patMVA_ = fs->make<TH2F>("pfMVA2patMVA", "PF based e_pi MVA vs standard MVA;PF based e_pi MVA;Standard MVA", 100, -1, 1, 100, -1, 1);

  pt = new std::vector<double>();
  eta = new std::vector<double>();
  phi = new std::vector<double>();

  chIso = new std::vector<double>();
  nhIso = new std::vector<double>();
  phIso = new std::vector<double>();

  trackIso = new std::vector<double>();
  ecalIso = new std::vector<double>();
  hcalIso = new std::vector<double>();

}

KoElectronSelector::~KoElectronSelector()
{

}

void KoElectronSelector::produce(edm::Event& iEvent, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace isodeposit;

  pt->clear();
  eta->clear();
  phi->clear();

  chIso->clear();
  nhIso->clear();
  phIso->clear();

  trackIso->clear();
  ecalIso->clear();
  hcalIso->clear();

  IsoDeposit::AbsVetos vetos_ch;
  IsoDeposit::AbsVetos vetos_nh;
  IsoDeposit::AbsVetos vetos_ph;

  iEvent.getByLabel(electronLabel_, electrons_);
  iEvent.getByLabel(beamSpotLabel_,beamSpot_); 
  EVENT  = iEvent.id().event();
  RUN    = iEvent.id().run();
  LUMI   = iEvent.id().luminosityBlock();

  std::auto_ptr<std::vector<pat::Electron> > pos(new std::vector<pat::Electron>());

  int cut[6] = {0,0,0,0,0,0};
  for (unsigned int i=0; i < electrons_->size();++i){
    pat::Electron electron = electrons_->at(i);
    electron.setP4(electron.pfCandidateRef()->p4());

    pat::strbitset electronIdSel = electronIdSelector_.getBitTemplate();
    pat::strbitset electronIsoSel = electronIsoSelector_.getBitTemplate();
    electronIdSelector_( electron, beamSpot_->position(), electronIdSel );
    electronIsoSelector_( electron, electronIsoSel );

    //bool C1 = electronIdSel.test("eta") && electronIdSel.test("pt");
    //bool C2 = C1 && electronIdSel.test("dxy");
    //bool C3 = C2 && electronIdSel.test("isGlobalMuon");
    //bool C4 = C3 && electronIdSel.test("isTrackerMuon");
    //bool C5 = C4 && electronIdSel.test("trackerHits");
    //bool C6 = C5 && electronIdSel.test("globalNormChi2");
  
    //if(C1) cut[0]++;
    //if(C2) cut[1]++;
    //if(C3) cut[2]++;
    //if(C4) cut[3]++;
    //if(C5) cut[4]++;
    //if(C6) cut[5]++;    

    //bool passIso = electronIsoSel.test("pfOptimizedRel");

    bool passed = false;

    //bool pfpass = electronIdSel.test("dxy") && electronIdSel.test("eta") && electronIdSel.test("pt");
    //cout << " 90relIso=" << electron.electronID("simpleEleId90relIso") << " 90cIso= " << electron.electronID("simpleEleId90cIso") <<  endl;
    //cout << electron.superCluster()->energy() << endl;
    bool passPre = electron.pt() > 20 && fabs(electron.eta()) < 2.5 && fabs(electron.gsfTrack()->dxy(beamSpot_->position())) < 0.04;
    bool passMVA = electron.mva() > 0.4;
    bool passWP90ID = electron.electronID("simpleEleId90relIso") == version_;
    if(version_ == 10) passed = passPre && passMVA;
    else passed = passPre && passWP90ID;
    //if(version_==0) passed = electronIdSel.test("eta") && electronIdSel.test("pt");
    //else if(version_==1) passed = pfpass;
    //else if(version_==2) passed = electronIdSel.test("VBTF") && pfpass;
    //else if(version_==3) passed = C6;
    //else if(version_==4) passed = pfpass && passIso;  

    id2mva->Fill( electron.mva(), electron.electronID("simpleEleId90relIso"));
    pfMVA2patMVA_->Fill( electron.mva(), electron.pfCandidateRef()->mva_e_pi());

    if(passed){
      cout << "passed " << electron.electronID("simpleEleId90cIso") << electron.electronID("simpleEleId90relIso") << endl;
      pos->push_back((*electrons_)[i]);

      pt->push_back(electron.pt());
      eta->push_back(electron.eta());
      phi->push_back(electron.phi());

      //chIso->push_back(electron.chargedHadronIso());
      //phIso->push_back(electron.photonIso());
      //nhIso->push_back(electron.neutralHadronIso());
      chIso->push_back(electron.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin(0.4, vetos_ch).first);
      nhIso->push_back(electron.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin(0.4, vetos_nh, 0.5).first);
      phIso->push_back(electron.isoDeposit(pat::PfGammaIso)->depositAndCountWithin(0.4, vetos_ph, 0.5).first);

      trackIso->push_back(electron.trackIso());
      ecalIso->push_back(electron.ecalIso());
      hcalIso->push_back(electron.hcalIso());

    }
  }

  for(int i=0; i < (int) cutNames.size() ; i++){
    cutflow->AddBinContent(i+1, cut[i]);
  }


  multiplicity = (int) pos->size();

  iEvent.put(pos);
 
  tree->Fill(); 

}

void 
KoElectronSelector::beginJob(){
   tree->Branch("EVENT",&EVENT,"EVENT/i");
   tree->Branch("RUN",&RUN,"RUN/i");
   tree->Branch("LUMI",&LUMI,"LUMI/i");

   tree->Branch("pt","std::vector<double>",&pt);
   tree->Branch("eta","std::vector<double>",&eta);
   tree->Branch("phi","std::vector<double>",&phi);
   tree->Branch("multiplicity",&multiplicity,"multiplicity/i");

   tree->Branch("chIso","std::vector<double>",&chIso);
   tree->Branch("nhIso","std::vector<double>",&nhIso);
   tree->Branch("phIso","std::vector<double>",&phIso);

   tree->Branch("trackIso","std::vector<double>",&trackIso);
   tree->Branch("ecalIso","std::vector<double>",&ecalIso);
   tree->Branch("hcalIso","std::vector<double>",&hcalIso);
}


void
KoElectronSelector::endJob() {
  for(int i=0 ; i < 6; i++){
    cutflow->GetXaxis()->SetBinLabel(i+1,cutNames[i].c_str());
  }
  id2mva->GetXaxis()->SetTitle("mva");
  id2mva->GetYaxis()->SetTitle("id90");
}


#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(KoElectronSelector);



