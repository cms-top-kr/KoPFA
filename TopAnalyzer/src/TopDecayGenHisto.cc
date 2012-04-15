#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/PtComparator.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "KoPFA/TopAnalyzer/interface/TopBasicFunctions.h"

#include <vector>
#include "TH1.h"
#include "TH2.h"

using namespace Ko;

class TopDecayGenHisto : public edm::EDFilter
{
public:
  TopDecayGenHisto(const edm::ParameterSet& pset);
  ~TopDecayGenHisto() {};

  void beginJob() {};
  bool filter(edm::Event& event, const edm::EventSetup& eventSetup);
  void endJob() {};

private:
  bool applyFilter_;
  bool semiLeptonic_;
  bool semiLeptonicMuon_;
  bool semiLeptonicElectron_;
  bool diLeptonic_;
  bool diLeptonicMuoMuo_;
  bool diLeptonicEleEle_;
  bool diLeptonicMuoEle_;
  bool diLeptonicTauMuo_;
  bool diLeptonicTauEle_;
  bool diLeptonicTauTau_;

  //parton level
  TH1F* hMtt_Full;
  TH1F* hMtt_LPJ;
  TH1F* hMtt_LPJ_Pton;
  TH1F* hMtt_LPJ_Pton_Status2;
  TH1F* hMtt_DIL;
  TH1F* hMtt_DIL_Pton;
  TH1F* hMtt_DIL_Pton_Status2;

  //particle level
  TH1F* hMtt_DIL_Ptcl;
  TH1F* hMtt_DIL_Ptcl_Status1Lepton;

  //additional histograms
  TH2F* hMtt_bquarkPt;
  TH2F* hMtt_bquarkStatus2Pt;
  TH2F* hMtt_leptonPt;
  TH2F* hMtt_bquarkEta;
  TH2F* hMtt_leptonEta;

};

TopDecayGenHisto::TopDecayGenHisto(const edm::ParameterSet& pset)
{
  applyFilter_= pset.getUntrackedParameter<bool>("applyFilter",false);

  semiLeptonic_ = pset.getParameter<bool>("semiLeptonic"),
  semiLeptonicMuon_ = pset.getParameter<bool>("semiLeptonicMuon"),
  semiLeptonicElectron_ = pset.getParameter<bool>("semiLeptonicElectron"),
  diLeptonic_ = pset.getParameter<bool>("diLeptonic");
  diLeptonicMuoMuo_ = pset.getParameter<bool>("diLeptonicMuoMuo");
  diLeptonicEleEle_ = pset.getParameter<bool>("diLeptonicEleEle");       
  diLeptonicMuoEle_ = pset.getParameter<bool>("diLeptonicMuoEle");
  diLeptonicTauMuo_ = pset.getParameter<bool>("diLeptonicTauMuo");
  diLeptonicTauEle_ = pset.getParameter<bool>("diLeptonicTauEle");
  diLeptonicTauTau_ = pset.getParameter<bool>("diLeptonicTauTau");
  
  edm::Service<TFileService> fs;

  //parton level
  hMtt_Full = fs->make<TH1F>( "hMtt_Full"  , "M_{tt}", 2500,  0., 2500. );
  hMtt_LPJ = fs->make<TH1F>( "hMtt_LPJ"  , "M_{tt}", 2500,  0., 2500. );
  hMtt_LPJ_Pton = fs->make<TH1F>( "hMtt_LPJ_Pton"  , "M_{tt}", 2500,  0., 2500. );
  hMtt_LPJ_Pton_Status2 = fs->make<TH1F>( "hMtt_LPJ_Pton_Status2"  , "M_{tt}", 2500,  0., 2500. );
  hMtt_DIL = fs->make<TH1F>( "hMtt_DIL"  , "M_{tt}", 2500,  0., 2500. );
  hMtt_DIL_Pton = fs->make<TH1F>( "hMtt_DIL_Pton"  , "M_{tt}", 2500,  0., 2500. );
  hMtt_DIL_Pton_Status2 = fs->make<TH1F>( "hMtt_DIL_Pton_Status2"  , "M_{tt}", 2500,  0., 2500. );
 
  //particle level
  hMtt_DIL_Ptcl = fs->make<TH1F>( "hMtt_DIL_Ptcl"  , "M_{tt}", 2500,  0., 2500. );  
  hMtt_DIL_Ptcl_Status1Lepton = fs->make<TH1F>( "hMtt_DIL_Ptcl_Status1Lepton"  , "M_{tt}", 2500,  0., 2500. );  

  /// additional histograms for debugging
  hMtt_bquarkPt = fs->make<TH2F>( "hMtt_bquarkPt", "M_{tt} vs bquarkPt", 500, 0, 500, 2500, 0, 2500);
  hMtt_bquarkStatus2Pt = fs->make<TH2F>( "hMtt_bquarkStatus2Pt", "M_{tt} vs bquarkPt", 500, 0, 500, 2500, 0, 2500);
  hMtt_leptonPt = fs->make<TH2F>( "hMtt_leptonPt", "M_{tt} vs leptonPt", 500, 0, 500, 2500, 0, 2500);
  hMtt_bquarkEta = fs->make<TH2F>( "hMtt_bquarkEta", "M_{tt} vs bquarkEta", 30, 0, 3, 2500, 0, 2500);
  hMtt_leptonEta = fs->make<TH2F>( "hMtt_leptonEta", "M_{tt} vs leptonEta", 30, 0, 3, 2500, 0, 2500);

}

bool TopDecayGenHisto::filter(edm::Event& iEvent, const edm::EventSetup& eventSetup)
{
  if (!applyFilter_)
    return true;

  bool accepted = false;
  std::vector<bool> electronic(2,static_cast<bool>(false));
  std::vector<bool> muonic(2,static_cast<bool>(false));
  std::vector<bool> taunic(2,static_cast<bool>(false));
  std::vector<bool> hadronic(2,static_cast<bool>(false));

  std::vector<double> leptonPt(2,static_cast<double>(-1));
  std::vector<double> bquarkPt(2,static_cast<double>(-1));
  std::vector<double> bquarkStatus2Pt(2,static_cast<double>(-1));
  std::vector<double> leptonEta(2,static_cast<double>(-1));
  std::vector<double> bquarkEta(2,static_cast<double>(-1));
  std::vector<double> bquarkStatus2Eta(2,static_cast<double>(-1));
  

  using namespace std;
  using namespace edm;
  using namespace reco;

  edm::Handle<reco::GenJetCollection> genJets;
  iEvent.getByLabel("ak5GenJets", genJets);

  std::map<int, vector<const reco::Candidate*> > mapJetToBHadrons;
  std::map<int, int> mapJetToBMatched;
  std::map<const reco::Candidate*, vector<int> > mapBHadronToJets;

  std::vector<math::XYZTLorentzVector> bJets;
  std::vector<math::XYZTLorentzVector> stableLeptons;  

  bool debug = false;
 
  if (debug ) cout << "EVENT" << endl;

  int idx = 0;
  for (reco::GenJetCollection::const_iterator genJet=genJets->begin();genJet!=genJets->end();++genJet){
    std::vector <const GenParticle*> mcparts = genJet->getGenConstituents();
    for (unsigned i = 0; i < mcparts.size (); i++) {
      const GenParticle* mcpart = mcparts[i];
      int PDG = std::abs( mcpart->pdgId());
      bool isB = decayFromBHadron(*mcpart);
      if(isB){
         const reco::Candidate* lastB = lastBHadron(*mcpart);
         vector<const reco::Candidate*>::iterator it = find ( mapJetToBHadrons[idx].begin(), mapJetToBHadrons[idx].begin(), lastB );
         if( it == mapJetToBHadrons[idx].end() ){
           mapJetToBHadrons[idx].push_back(lastB);
           mapJetToBMatched[idx] = 1;
           mapBHadronToJets[lastB].push_back( idx );
         }
      }
    }
    idx++;
  }

  for( std::map<const reco::Candidate*, vector<int> >::iterator it = mapBHadronToJets.begin() ; it != mapBHadronToJets.end(); it++){

    if( (*it).second.size() > 1) {
      if(debug){
        cout << "---> This B hadron : " << (*it).first->pdgId() << " has " << (*it).second.size() <<  " jets matched" << endl;
        cout << "---> Will try to identify only one jet matched with this B hadron by looking at dR" << endl;
      }
      const reco::Candidate* BHadron = (*it).first;
   
      double minDR = 999;
      int selectedJet = -1;
      for( std::vector<int>::iterator bjet = (*it).second.begin(); bjet != (*it).second.end(); bjet++){
        int idx = *bjet;
        mapJetToBMatched[idx] = 0; // set it to 0 again 
        const reco::GenJet& bjet = genJets->at(idx);
        double dR = Ko::dR( *BHadron, bjet ) ; 
        if( dR < minDR ) { 
          selectedJet = idx;
          minDR = dR;
        }
      }

      //only set it to true for only selected jet 
      mapJetToBMatched[selectedJet] = 1;

      if(debug) cout << "---> Now one jet is selected with dR " << minDR << endl;
    }

  }

  for( std::map<int, vector<const reco::Candidate*> >::iterator it = mapJetToBHadrons.begin() ; it != mapJetToBHadrons.end(); it++){
    if( (*it).second.size() > 1) cout << "!!! This jet matches with more than 1 hadron !!!" << endl;
    int idx = (*it).first;
    const reco::GenJet& genJet = genJets->at(idx);
    // is It unique b-jet?  
    if( mapJetToBMatched[idx]  == 0 ) continue;
    bJets.push_back( genJet.p4() );
  }

  const reco::GenParticleCollection* myGenParticles = 0;

  Handle<reco::GenParticleCollection> genEvt;
  bool genPart = iEvent.getByLabel("genParticles",genEvt);
  if ( genPart ) myGenParticles = &(*genEvt);
  if ( !myGenParticles ) return false;

  unsigned int nParticles = myGenParticles->size();
  int ntop = 0;
  reco::Candidate::LorentzVector ttbarGen;
  double Mtt = 0;

  for ( unsigned int ip=0; ip<nParticles; ++ip ) {
    const reco::GenParticle& p = (*myGenParticles)[ip];
    //this is just for checking with stauts 1 lepton cut
    bool isLepton = ( ( abs(p.pdgId()) == 11 || abs(p.pdgId()) == 13 ) && p.status() == 1);
    if ( isLepton ){
      stableLeptons.push_back( p.p4() );
    }
  }

  for ( unsigned int ip=0; ip<nParticles; ++ip ) { 

    if ( ntop == 2 ) break;

    const reco::GenParticle& p = (*myGenParticles)[ip];

    if ( abs(p.pdgId()) != 6 ) continue;

    ttbarGen += p.p4();
    if( ntop == 1) Mtt = ttbarGen.M();

    unsigned int nDaughters = p.numberOfDaughters();
    int nW = 0;
    for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
      const reco::Candidate* daugh = p.daughter(iDaughter);
      if ( nW == 1 ) break;
      if ( abs(daugh->pdgId()) == 5 ) {
         bquarkPt[ntop] = daugh->pt();
         bquarkEta[ntop] = fabs( daugh->eta() );
         unsigned int nbDaughters = daugh->numberOfDaughters();
         for ( unsigned ibDaughter=0; ibDaughter<nbDaughters; ++ibDaughter ) {
           const reco::Candidate* decay = daugh->daughter(ibDaughter);
           int decayId = abs(decay->pdgId());
           int decayStatus = decay->status();
           if( decayId == 5 ){
             assert( decayStatus == 2);
              bquarkStatus2Pt[ntop] = decay->pt();
              bquarkStatus2Eta[ntop] = fabs( decay->eta() );
           }
         }
      }
      if ( abs(daugh->pdgId()) != 24 ) continue; 
      unsigned int nWDaughters = daugh->numberOfDaughters();
      for ( unsigned iWDaughter=0; iWDaughter<nWDaughters; ++iWDaughter ) {
	const reco::Candidate* decay = daugh->daughter(iWDaughter);
	int decayId = abs(decay->pdgId());
	if ( decayId == 11  ) {  
	  electronic[ntop] = true;
	  leptonPt[ntop] = decay->pt();
          leptonEta[ntop] = fabs( decay->eta() );
	  break; 
	} else if ( decayId == 13 ) {  
	  muonic[ntop] = true;
	  leptonPt[ntop] = decay->pt();
          leptonEta[ntop] = fabs( decay->eta() );
	  break;
	} else if ( decayId == 15  ) {  
          taunic[ntop] = decay->pt();
          unsigned int nTauDaughters = decay->numberOfDaughters();
          for ( unsigned iTauDaughter=0; iTauDaughter<nTauDaughters; ++iTauDaughter ) {
            const reco::Candidate* tauDecay = decay->daughter(iTauDaughter);
            int tauDecayId = abs(tauDecay->pdgId());
            if ( tauDecayId == 11  ) {
              electronic[ntop] = true;
              leptonPt[ntop] = tauDecay->pt();
              leptonEta[ntop] = fabs( tauDecay->eta() );
              break;
            } else if ( tauDecayId == 13 ) {
              muonic[ntop] = true;
              leptonPt[ntop] = tauDecay->pt();
              leptonEta[ntop] = fabs( tauDecay->eta() );
              break;
            } else if (  tauDecayId == 15 ) {
              unsigned int nTauGrandDaughters = tauDecay->numberOfDaughters();
              for ( unsigned iTauGrandDaughter=0; iTauGrandDaughter<nTauGrandDaughters; ++iTauGrandDaughter ) {
                const reco::Candidate* tauGrandDecay = tauDecay->daughter(iTauGrandDaughter);
                int tauGrandDecayId = abs(tauGrandDecay->pdgId());
                if ( tauGrandDecayId == 11 ) {
                  electronic[ntop] = true;
                  leptonPt[ntop] = tauGrandDecay->pt();
                  leptonEta[ntop] = fabs( tauGrandDecay->eta() );
                  break;
                } else if ( tauGrandDecayId == 13 ) {
                  muonic[ntop] = true;
                  leptonPt[ntop] = tauGrandDecay->pt();
                  leptonEta[ntop] = fabs( tauGrandDecay->eta() );
                  break;
                } else {
                  continue;
                }
              }
            } else{
              continue;
            }
          }
	} else if( decayId < 6 ){
          hadronic[ntop] = true;
        } else {  
	  continue;
	}
      }
      ++nW;
    }
    ++ntop;
  }

  if ( semiLeptonic_ && 
	( ( hadronic[0] == true &&  hadronic[1] == false ) ||  
	  ( hadronic[0] == false &&  hadronic[1] == true) ) ) {
     // All semi leptonic decays
    accepted = true;
    // Reject specific semi-leptonic decays
    // Electron
    if ( !semiLeptonicElectron_ && 
	  ( ( hadronic[0] == true && electronic[1] == true) ||  
	    ( hadronic[1] == true && electronic[0] == true ) ) ) accepted = false; 
     // Muon
    if ( !semiLeptonicMuon_ && 
	  ( ( hadronic[0] == true && muonic[1] == true ) ||  
	    ( hadronic[1] == true && muonic[0] == true ) ) ) accepted = false; 
  }

  // Di-Leptonic
  if ( diLeptonic_ && leptonPt[0] > 0 && leptonPt[1] > 0 ) { 
    accepted = true;
    // All di-leptonic decays
    // Reject specific di-leptonic decays
    // Electron-Electron
    if ( !diLeptonicEleEle_ && 
      electronic[0] == true && electronic[1] == true ) accepted = false; 
    // Muon-Muon
    if ( !diLeptonicMuoMuo_ && 
      muonic[0] == true && muonic[1] == true ) accepted = false;
    // Electron-Muon
    if ( !diLeptonicMuoEle_ && 
      ( ( muonic[0] == true && electronic[1] == true ) || 
      ( muonic[1] == true && electronic[0] == true ) ) ) accepted = false; 
    // Tau-Muon
    if ( !diLeptonicTauMuo_ &&
      ( ( taunic[0] == true && muonic[1] == true ) ||
      ( taunic[1] == true && muonic[0] == true ) ) ) accepted = false;
    // Tau-Electron
    if ( !diLeptonicTauEle_ &&
      ( ( taunic[0] == true && electronic[1] == true ) ||
      ( taunic[1] == true && electronic[0] == true ) ) ) accepted = false;
    // Tau-Tau
    if ( !diLeptonicTauTau_ &&
      taunic[0] == true && taunic[1] == true ) accepted = false;
  
  }


  /// Parton level histograms 
  hMtt_Full->Fill(Mtt);
  bool visibleDIL = leptonPt[0] > 20 && leptonPt[1] > 20 && leptonEta[0] < 2.4 && leptonEta[1] < 2.4 && bquarkPt[0] > 30 && bquarkPt[1] > 30 && bquarkEta[1] < 2.4 && bquarkEta[2] < 2.4;
  bool visibleLPJ = ( ( leptonPt[0] > 30 && leptonEta[0] < 2.1 && leptonPt[1] < 0 ) || ( leptonPt[0] < 0 && leptonPt[1] > 30 && leptonEta[1] < 2.1 ) ) && bquarkPt[0] > 30 && bquarkPt[1] > 30 && bquarkEta[0] < 2.4 && bquarkEta[1] < 2.4;
  bool visibleDILStatus2 = leptonPt[0] > 20 && leptonPt[1] > 20 && leptonEta[0] < 2.4 && leptonEta[1] < 2.4 && bquarkStatus2Pt[0] > 30 && bquarkStatus2Pt[1] > 30 && bquarkStatus2Eta[1] < 2.4 && bquarkStatus2Eta[2] < 2.4;
  bool visibleLPJStatus2 = ( ( leptonPt[0] > 30 && leptonEta[0] < 2.1 && leptonPt[1] < 0 ) || ( leptonPt[0] < 0 && leptonPt[1] > 30 && leptonEta[1] < 2.1 ) ) && bquarkStatus2Pt[0] > 30 && bquarkStatus2Pt[1] > 30 && bquarkStatus2Eta[0] < 2.4 && bquarkStatus2Eta[1] < 2.4;
  

  if( ( hadronic[0] == true &&  hadronic[1] == false ) || ( hadronic[0] == false &&  hadronic[1] == true) ) hMtt_LPJ->Fill(Mtt);
  if( leptonPt[0] > 0  && leptonPt[1] > 0) hMtt_DIL->Fill(Mtt);
  if( visibleLPJ ) hMtt_LPJ_Pton->Fill(Mtt);
  if( visibleDIL ) hMtt_DIL_Pton->Fill(Mtt);
  if( visibleLPJStatus2 ) hMtt_LPJ_Pton_Status2->Fill(Mtt);
  if( visibleDILStatus2 ) hMtt_DIL_Pton_Status2->Fill(Mtt);

  if(leptonPt[0] > 0) hMtt_leptonPt->Fill( leptonPt[0], Mtt);
  if(leptonPt[1] > 0) hMtt_leptonPt->Fill( leptonPt[1], Mtt);
  if(bquarkPt[0] > 0) hMtt_bquarkPt->Fill( bquarkPt[0], Mtt);
  if(bquarkPt[1] > 0) hMtt_bquarkPt->Fill( bquarkPt[1], Mtt);
  if(bquarkStatus2Pt[0] > 0) hMtt_bquarkStatus2Pt->Fill( bquarkStatus2Pt[0], Mtt);
  if(bquarkStatus2Pt[1] > 0) hMtt_bquarkStatus2Pt->Fill( bquarkStatus2Pt[1], Mtt);
  if(leptonEta[0] > 0) hMtt_leptonEta->Fill( leptonEta[0], Mtt);
  if(leptonEta[1] > 0) hMtt_leptonEta->Fill( leptonEta[1], Mtt);
  if(bquarkEta[0] > 0) hMtt_bquarkEta->Fill( bquarkEta[0], Mtt);
  if(bquarkEta[1] > 0) hMtt_bquarkEta->Fill( bquarkEta[1], Mtt);
 
  /// Particle level histograms
  std::sort(stableLeptons.begin(), stableLeptons.end(), GreaterByPt<reco::Candidate::LorentzVector>());
  std::sort(bJets.begin(), bJets.end(), GreaterByPt<reco::Candidate::LorentzVector>());

  bool visibleBJets = false;
  bool visibleStatus1Lepton = false;
  if( bJets.size() >= 2){
    visibleBJets = bJets[0].pt() > 30 && bJets[1].pt() > 30 && fabs( bJets[0].eta() )  <  2.4 && fabs(bJets[1].eta())  <  2.4 ;
  }

  if( stableLeptons.size() >= 2 ){
    visibleStatus1Lepton = stableLeptons[0].pt() > 20 && stableLeptons[1].pt() > 20 && fabs( stableLeptons[0].eta() )  <  2.4 && fabs(stableLeptons[1].eta())  <  2.4 ; 
  }
    
  bool visibleDILParticleLevelStatus1Lepton = visibleStatus1Lepton && visibleBJets; 
  bool visibleDILParticleLevel = leptonPt[0] > 20 && leptonPt[1] > 20 && leptonEta[0] < 2.4 && leptonEta[1] < 2.4 && visibleBJets; 

  if(visibleDILParticleLevelStatus1Lepton) hMtt_DIL_Ptcl_Status1Lepton->Fill(Mtt);
  if(visibleDILParticleLevel) hMtt_DIL_Ptcl->Fill(Mtt);

  return accepted;
}

DEFINE_FWK_MODULE(TopDecayGenHisto);

