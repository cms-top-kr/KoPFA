#include "KoPFA/CMGDataFormats/interface/CMGTTbarCandidate.h"
#include "CommonTools/Utils/interface/PtComparator.h"
#include "DataFormats/Math/interface/deltaR.h"
#include <map>
#include <vector>
 
using namespace std;
using namespace reco;
using namespace vallot;

void CMGTTbarCandidate::building( const std::vector<cmg::GenJet>* genJets, const reco::GenParticleCollection* genParticles  ){

  math::XYZTLorentzVector null(0,0,0,0); 

  bquarks_.push_back(null);
  bquarks_.push_back(null);
  bquarks_.push_back(null);
  bquarks_.push_back(null);

  leptons_.push_back(null);
  leptons_.push_back(null);
  nus_.push_back(null);
  nus_.push_back(null);
  taunus_.push_back(null);
  taunus_.push_back(null);

  std::vector<bool> electronic(2,static_cast<bool>(false));
  std::vector<bool> muonic(2,static_cast<bool>(false));
  std::vector<bool> taunic(2,static_cast<bool>(false));
  std::vector<bool> hadronic(2,static_cast<bool>(false));

  unsigned int nParticles = genParticles->size();
  int ntop = 0;
  reco::Candidate::LorentzVector ttbarGen;

  std::vector<math::XYZTLorentzVector> bquarksfromnotop;
  std::vector<math::XYZTLorentzVector> bquarksfromtop;
  std::vector<math::XYZTLorentzVector> bquarks;
  std::vector<math::XYZTLorentzVector> cquarks;

  mass_ = 0;
  //debug
  //cout << "EVENT= " << endl;
  for ( unsigned int ip=0; ip<nParticles; ++ip ) { 


    const reco::GenParticle& p = (*genParticles)[ip];

    if ( abs(p.pdgId()) == 5 ) {
      bool isLast = isLastbottom(p);
      if (isLast == true) {
        bool isfromtop = isFromtop(p);
        if(isfromtop) {
          bquarksfromtop.push_back( p.p4() );
        }else{
          bquarksfromnotop.push_back( p.p4() );
        }
        bquarks.push_back( p.p4() );
      } 
    }

    if ( abs(p.pdgId()) == 4 ) {
      bool isLast = isLastcharm(p);
      if(isLast == true){
        bool isfromtop = isFromtop(p);
        if( isfromtop == false ) cquarks.push_back( p.p4() );
      }
    }

    if ( ntop == 2 ) continue;
    if ( abs(p.pdgId()) != 6 ) continue;

    bool isLast = isLastParton(p);
    if(isLast != true) continue;
    //debug
    //cout << "ntop = " << ntop << endl;
 
    ttbarGen += p.p4();
    if( ntop == 1 ) {
      mass_ = ttbarGen.M();
    }

    unsigned int nDaughters = p.numberOfDaughters();
    int nW = 0;
    for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
      const reco::Candidate* daughTemp = p.daughter(iDaughter);
      if ( nW == 1 ) break;
      if ( abs(daughTemp->pdgId()) != 24 ) continue;
      const reco::Candidate* daugh = getLast( *daughTemp );
      unsigned int nWDaughters = daugh->numberOfDaughters();
      //debug
      //cout << "nW daughters= " << nWDaughters << endl;
      int nWleptonDaughters = 0;
      for ( unsigned iWDaughter=0; iWDaughter<nWDaughters; ++iWDaughter ) {
	const reco::Candidate* decay = daugh->daughter(iWDaughter);
	int decayId = abs(decay->pdgId());
        //debug
        //cout << "W decay Id = " << decayId << endl;
	if ( decayId == 11 || decayId == 12 ) {  
          if( nWleptonDaughters == 2 ) break;
          if( decayId == 11 ) {
            electronic[ntop] = true;
            leptons_[ntop] = decay->p4() ;
            nWleptonDaughters++;
          }
          if( decayId == 12 ) {
            nus_[ntop] = decay->p4() ;
            nWleptonDaughters++;
          }
	} else if ( decayId == 13 || decayId == 14 ) {  
          if( nWleptonDaughters == 2 ) break;
          if( decayId == 13 ) {
            muonic[ntop] = true;
            leptons_[ntop] = decay->p4() ;
            nWleptonDaughters++;
          }
          if( decayId == 14 ) {
            nus_[ntop] = decay->p4() ;
            nWleptonDaughters++;
          }
	} else if ( decayId == 15 || decayId == 16 ) {  
          if( decayId == 15 ) taunic[ntop] = true;
          if( decayId == 16 ) taunus_[ntop] = decay->p4() ;
          unsigned int nTauDaughters = decay->numberOfDaughters();
          for ( unsigned iTauDaughter=0; iTauDaughter<nTauDaughters; ++iTauDaughter ) {
            const reco::Candidate* tauDecay = decay->daughter(iTauDaughter);
            int tauDecayId = abs(tauDecay->pdgId());
            if ( tauDecayId == 11 || tauDecayId == 12 ) {
              if( nWleptonDaughters == 2 ) break;
              if( tauDecayId == 11) {
                electronic[ntop] = true;
                leptons_[ntop] = tauDecay->p4() ;
                nWleptonDaughters++;
              }
              if( tauDecayId == 12) {
                nus_[ntop] = tauDecay->p4() ;
                nWleptonDaughters++;
              }
            } else if ( tauDecayId == 13 || tauDecayId == 14 ) {
              if( nWleptonDaughters == 2 ) break;
              if( tauDecayId == 13) {
                muonic[ntop] = true;
                leptons_[ntop] = tauDecay->p4() ;
                nWleptonDaughters++;
              }
              if( tauDecayId == 14) {
                nus_[ntop] = tauDecay->p4() ;
                nWleptonDaughters++;
             }
            } else if (  tauDecayId == 15 || tauDecayId == 16) {
              unsigned int nTauGrandDaughters = tauDecay->numberOfDaughters();
              for ( unsigned iTauGrandDaughter=0; iTauGrandDaughter<nTauGrandDaughters; ++iTauGrandDaughter ) {
                const reco::Candidate* tauGrandDecay = tauDecay->daughter(iTauGrandDaughter);
                int tauGrandDecayId = abs(tauGrandDecay->pdgId());
                if ( tauGrandDecayId == 11 || tauGrandDecayId == 12 ) {
                  if( nWleptonDaughters == 2 ) break;
                  if( tauGrandDecayId == 11){
                    electronic[ntop] = true;
                    leptons_[ntop] = tauGrandDecay->p4() ;
                    nWleptonDaughters++;
                  }
                  if( tauGrandDecayId == 12 ) {
                    nus_[ntop] = tauGrandDecay->p4() ;
                    nWleptonDaughters++;
                  }
                } else if ( tauGrandDecayId == 13 || tauGrandDecayId == 14 ) {
                  if( nWleptonDaughters == 2 ) break;
                  if( tauGrandDecayId == 13 ){
                    muonic[ntop] = true;
                    leptons_[ntop] = tauGrandDecay->p4() ;
                    nWleptonDaughters++;
                  }
                  if( tauGrandDecayId == 12 ) {
                    nus_[ntop] = tauGrandDecay->p4() ;
                    nWleptonDaughters++;
                  }
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

  allHadronic_ = false;
  semiLeptonic_ = false;
  semiLeptonicEle_ = false;
  semiLeptonicMuo_ = false;
  semiLeptonicTau_ = false;
  diLeptonic_ = false;
  diLeptonicMuoMuo_ = false;
  diLeptonicMuoEle_ = false;
  diLeptonicEleEle_ = false;
  diLeptonicTauMuo_ = false;
  diLeptonicTauEle_ = false;
  diLeptonicTauTau_ = false;

  if ( hadronic[0] == true && hadronic[1] == true) allHadronic_ = true;

  if ( ( hadronic[0] == true &&  hadronic[1] == false ) ||
          ( hadronic[0] == false &&  hadronic[1] == true) )  {
    // All semi leptonic decays
    semiLeptonic_ = true;
    // Electron
    if ( ( hadronic[0] == true && electronic[1] == true) ||
            ( hadronic[1] == true && electronic[0] == true ) )  semiLeptonicEle_ = true;
    // Muon
    if ( ( hadronic[0] == true && muonic[1] == true ) ||
            ( hadronic[1] == true && muonic[0] == true ) )  semiLeptonicMuo_ = true;
    // Tau
    if ( ( hadronic[0] == true && taunic[1] == true ) ||
            ( hadronic[1] == true && taunic[0] == true ) )  semiLeptonicTau_ = true;
  }

  // Di-Leptonic
  if ( hadronic[0] == false && hadronic[1] == false ) {
    diLeptonic_ = true;
    // All di-leptonic decays
    // Electron-Electron
    if ( electronic[0] == true && electronic[1] == true ) diLeptonicEleEle_ = true;
    // Muon-Muon
    if ( muonic[0] == true && muonic[1] == true ) diLeptonicMuoMuo_ = true;
    // Electron-Muon
    if ( ( muonic[0] == true && electronic[1] == true ) ||
      ( muonic[1] == true && electronic[0] == true ) )  diLeptonicMuoEle_ = true;
    // Tau-Muon
    if ( ( taunic[0] == true && muonic[1] == true ) ||
      ( taunic[1] == true && muonic[0] == true ) )  diLeptonicTauMuo_ = true;
    // Tau-Electron
    if ( ( taunic[0] == true && electronic[1] == true ) ||
      ( taunic[1] == true && electronic[0] == true ) ) diLeptonicTauEle_ = true;
    // Tau-Tau
    if ( taunic[0] == true && taunic[1] == true ) diLeptonicTauTau_ = true;
  }

  // debug
  //cout << "diLeptonic= " << diLeptonic_ << endl;
  //cout << "diLeptonicMuoMuo= " << diLeptonicMuoMuo_ << endl;
  //cout << "diLeptonicMuoEle= " << diLeptonicMuoEle_ << endl;
  //cout << "diLeptonicEleEle= " << diLeptonicEleEle_ << endl;
  //cout << "diLeptonicTauMuo= " << diLeptonicTauMuo_ << endl;
  //cout << "diLeptonicTauEle= " << diLeptonicTauEle_ << endl;
  //cout << "diLeptonicTauTau= " << diLeptonicTauTau_ << endl;

  taunic1_ = taunic[0];
  taunic2_ = taunic[1];

  //sort b-quarks from top since the leading two quarks must be from top.
  std::sort(bquarksfromtop.begin(), bquarksfromtop.end(), GreaterByPt<reco::Candidate::LorentzVector>());
  std::sort(bquarksfromnotop.begin(), bquarksfromnotop.end(), GreaterByPt<reco::Candidate::LorentzVector>());

  NbQuarksNoTop_ = (int) bquarksfromnotop.size();
  NbQuarksTop_ = (int) bquarksfromtop.size();
  NcQuarks_ = (int) cquarks.size();

  //inseart b-quarks from top to the b-quarks from non-top.
  //bquarks.insert( bquarks.begin(), bquarksfromtop.begin(), bquarksfromtop.end());

  NbQuarks_ = (int) bquarks.size(); 

  int nbQuark20 = 0;
  for( unsigned int i = 0 ; i < bquarksfromtop.size() ; i++){
    if( i < 2){
      bquarks_[i] = bquarksfromtop[i];
    }
    if( bquarksfromtop[i].pt() > 20 && fabs(bquarksfromtop[i].eta()) < 2.5) nbQuark20++;
  }
  for( unsigned int i = 0 ; i < bquarksfromnotop.size() ; i++){
    if( i < 2){
      bquarks_[i] = bquarksfromnotop[i];
    }
    if( bquarksfromnotop[i].pt() > 20 && fabs(bquarksfromnotop[i].eta()) < 2.5) nbQuark20++;
  }
  NbQuarks20_ = nbQuark20;

//////
  bJets_.push_back(null);
  bJets_.push_back(null);
  bJets_.push_back(null);
  bJets_.push_back(null);

  std::map<int, vector<const reco::Candidate*> > mapJetToBHadrons;
  std::map<int, int> mapJetToBMatched;
  std::map<const reco::Candidate*, vector<int> > mapBHadronToJets;

  std::map<int, vector<const reco::Candidate*> > mapJetToCHadrons;
  std::map<int, int> mapJetToCMatched;
  std::map<const reco::Candidate*, vector<int> > mapCHadronToJets;

  std::vector<math::XYZTLorentzVector> bJets;
  std::vector<math::XYZTLorentzVector> bJetsBHad;
  std::vector<math::XYZTLorentzVector> nobJetsBHad;
  std::vector<math::XYZTLorentzVector> bJetsfromnotop;
  std::vector<math::XYZTLorentzVector> cJets;
  std::vector<math::XYZTLorentzVector> cJetsCHad;

  int idx = 0;

  NJets_ = 0;
  NJets30_ = 0;
  NJets25_ = 0;
  NJets20_ = 0;
  NJets15_ = 0;
  NJets10_ = 0;

  for (std::vector<cmg::GenJet>::const_iterator genJet=genJets->begin();genJet!=genJets->end();++genJet, ++idx){
    const reco::Candidate& gJet = *genJet;

    double minDRlepton = 999;
    for(unsigned int i=0 ; i < leptons_.size() ; i++){
      if( leptons_[i] == null ) continue;
      double dR = reco::deltaR(gJet.eta(), gJet.phi(), leptons_[i].eta(), leptons_[i].phi());
      if( dR < minDRlepton ) minDRlepton = dR;
    }
    if( minDRlepton < 0.5) continue;

    double minDR = 999;
    for(unsigned int i=0 ; i < bquarks.size() ; i++){
      double dR = reco::deltaR(gJet.eta(), gJet.phi(), bquarks[i].eta(), bquarks[i].phi());
      if( dR < minDR ) minDR = dR;
    }
    if( minDR < 0.5 ) bJets.push_back(gJet.p4());

    double minDR2b = 999;
    for(unsigned int i=0 ; i < bquarksfromnotop.size() ; i++){
      double dR = reco::deltaR(gJet.eta(), gJet.phi(), bquarksfromnotop[i].eta(), bquarksfromnotop[i].phi());
      if( dR < minDR2b ) minDR2b = dR;
    }
    if( minDR2b < 0.5 ) bJetsfromnotop.push_back(gJet.p4());

    double minDR2c = 999;
    for(unsigned int i=0 ; i < cquarks.size() ; i++){
      double dR = reco::deltaR(gJet.eta(), gJet.phi(), cquarks[i].eta(), cquarks[i].phi());
      if( dR < minDR2c ) minDR2c = dR;
    }
    if( minDR2c < 0.5 ) cJets.push_back(gJet.p4());

    NJets_++;
    if( gJet.pt() > 30 && fabs(gJet.eta()) < 2.5 ) NJets30_++;
    if( gJet.pt() > 25 && fabs(gJet.eta()) < 2.5 ) NJets25_++;
    if( gJet.pt() > 20 && fabs(gJet.eta()) < 2.5 ) NJets20_++;
    if( gJet.pt() > 15 && fabs(gJet.eta()) < 2.5 ) NJets15_++;
    if( gJet.pt() > 10 && fabs(gJet.eta()) < 2.5 ) NJets10_++;

    bool isPAT = genJet->sourcePtr()->isAvailable(); 

    if( isPAT ){
      std::vector <const reco::GenParticle*> mcparts = (*(genJet->sourcePtr()))->getGenConstituents();
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
        bool isC = decayFromCHadron(*mcpart);
        if(isC){
          const reco::Candidate* lastC = lastCHadron(*mcpart);
          vector<const reco::Candidate*>::iterator it = find ( mapJetToCHadrons[idx].begin(), mapJetToCHadrons[idx].begin(), lastC );
          if( it == mapJetToCHadrons[idx].end() ){
            mapJetToCHadrons[idx].push_back(lastC);
            mapJetToCMatched[idx] = 1;
            mapCHadronToJets[lastC].push_back( idx );
          }
        }
      }
    }

  }


  for( std::map<const reco::Candidate*, vector<int> >::iterator it = mapBHadronToJets.begin() ; it != mapBHadronToJets.end(); it++){

    const reco::Candidate* BHadron = (*it).first;

    if( (*it).second.size() > 1) {
      double minDR = 999;
      int selectedJet = -1;
      for( std::vector<int>::iterator bjet = (*it).second.begin(); bjet != (*it).second.end(); bjet++){
        int idx = *bjet;
        mapJetToBMatched[idx] = 0; // set it to 0 again 
        const reco::Candidate& bjet = genJets->at(idx);
        double dR = deltaR( *BHadron, bjet ) ;
        if( dR < minDR ) {
          selectedJet = idx;
          minDR = dR;
        }
      }
      //only set it to true for only selected jet 
      mapJetToBMatched[selectedJet] = 1;
    }

  }

  for( std::map<const reco::Candidate*, vector<int> >::iterator it = mapCHadronToJets.begin() ; it != mapCHadronToJets.end(); it++){

    const reco::Candidate* CHadron = (*it).first;

    if( (*it).second.size() > 1) {
      double minDR = 999;
      int selectedJet = -1;
      for( std::vector<int>::iterator bjet = (*it).second.begin(); bjet != (*it).second.end(); bjet++){
        int idx = *bjet;
        mapJetToCMatched[idx] = 0; // set it to 0 again 
        const reco::Candidate& cjet = genJets->at(idx);
        double dR = deltaR( *CHadron, cjet ) ;
        if( dR < minDR ) {
          selectedJet = idx;
          minDR = dR;
        }
      }
      //only set it to true for only selected jet 
      mapJetToCMatched[selectedJet] = 1;
    }

  }

  for( std::map<int, vector<const reco::Candidate*> >::iterator it = mapJetToBHadrons.begin() ; it != mapJetToBHadrons.end(); it++){
    if( (*it).second.size() > 1) cout << "!!! This jet matches with more than 1 hadron !!!" << endl;
    int idx = (*it).first;
    const reco::Candidate& genJet = genJets->at(idx);
    // is It unique b-jet?  
    if( mapJetToBMatched[idx]  == 0 ) continue;
    bJetsBHad.push_back( genJet.p4() );
  }

  std::sort(bJetsBHad.begin(), bJetsBHad.end(), GreaterByPt<reco::Candidate::LorentzVector>());

  NbJetsBHad_ = 0;
  NbJets10BHad_ = 0;
  NbJets15BHad_ = 0;
  NbJets20BHad_ = 0;
  NbJets25BHad_ = 0;
  NbJets30BHad_ = 0;

  for( unsigned int i = 0 ; i < bJetsBHad.size() ; i++){
    if( i < 4 ){
      bJets_[i] = bJetsBHad[i];
    }
    NbJetsBHad_++;
    if( bJetsBHad[i].pt() > 10 && fabs(bJetsBHad[i].eta()) < 2.5) NbJets10BHad_++;
    if( bJetsBHad[i].pt() > 15 && fabs(bJetsBHad[i].eta()) < 2.5) NbJets15BHad_++;
    if( bJetsBHad[i].pt() > 20 && fabs(bJetsBHad[i].eta()) < 2.5) NbJets20BHad_++;
    if( bJetsBHad[i].pt() > 25 && fabs(bJetsBHad[i].eta()) < 2.5) NbJets25BHad_++;
    if( bJetsBHad[i].pt() > 30 && fabs(bJetsBHad[i].eta()) < 2.5) NbJets30BHad_++;
  }

  for( std::map<int, vector<const reco::Candidate*> >::iterator it = mapJetToCHadrons.begin() ; it != mapJetToCHadrons.end(); it++){
    if( (*it).second.size() > 1) cout << "!!! This jet matches with more than 1 hadron !!!" << endl;
    int idx = (*it).first;
    const reco::Candidate& genJet = genJets->at(idx);
    // is It unique c-jet?  
    if( mapJetToCMatched[idx]  == 0 ) continue;
    if( mapJetToBMatched[idx]  == 1 ) continue; //if it is assigned as b-jet, do not count it as c-jet
    cJetsCHad.push_back( genJet.p4() );
  }

  std::sort(cJetsCHad.begin(), cJetsCHad.end(), GreaterByPt<reco::Candidate::LorentzVector>());

  NcJetsCHad_ = 0;
  NcJets10CHad_ = 0;
  NcJets15CHad_ = 0;
  NcJets20CHad_ = 0;
  NcJets25CHad_ = 0;
  NcJets30CHad_ = 0;

  for( unsigned int i = 0 ; i < cJetsCHad.size() ; i++){
    NcJetsCHad_++;
    if( cJetsCHad[i].pt() > 10 && fabs(cJetsCHad[i].eta()) < 2.5) NcJets10CHad_++;
    if( cJetsCHad[i].pt() > 15 && fabs(cJetsCHad[i].eta()) < 2.5) NcJets15CHad_++;
    if( cJetsCHad[i].pt() > 20 && fabs(cJetsCHad[i].eta()) < 2.5) NcJets20CHad_++;
    if( cJetsCHad[i].pt() > 25 && fabs(cJetsCHad[i].eta()) < 2.5) NcJets25CHad_++;
    if( cJetsCHad[i].pt() > 30 && fabs(cJetsCHad[i].eta()) < 2.5) NcJets30CHad_++;
  }

  NbJets_ = 0;
  NbJets10_ = 0;
  NbJets15_ = 0;
  NbJets20_ = 0;
  NbJets25_ = 0;
  NbJets30_ = 0;

  for( unsigned int i = 0 ; i < bJets.size() ; i++){
    NbJets_++;
    if( bJets[i].pt() > 10 && fabs(bJets[i].eta()) < 2.5) NbJets10_++;
    if( bJets[i].pt() > 15 && fabs(bJets[i].eta()) < 2.5) NbJets15_++;
    if( bJets[i].pt() > 20 && fabs(bJets[i].eta()) < 2.5) NbJets20_++;
    if( bJets[i].pt() > 25 && fabs(bJets[i].eta()) < 2.5) NbJets25_++;
    if( bJets[i].pt() > 30 && fabs(bJets[i].eta()) < 2.5) NbJets30_++;
  }

  NbJetsNoTop_ = 0;
  NbJets15NoTop_ = 0;
  NbJets20NoTop_ = 0;

  for( unsigned int i = 0 ; i < bJetsfromnotop.size() ; i++){
    NbJetsNoTop_++;
    if( bJetsfromnotop[i].pt() > 15 && fabs(bJetsfromnotop[i].eta()) < 2.5) NbJets15NoTop_++;
    if( bJetsfromnotop[i].pt() > 20 && fabs(bJetsfromnotop[i].eta()) < 2.5) NbJets20NoTop_++;
  }

  NcJets_ = 0;
  NcJets10_ = 0;
  NcJets15_ = 0;
  NcJets20_ = 0;
  NcJets25_ = 0;
  NcJets30_ = 0;

  for( unsigned int i = 0 ; i < cJets.size() ; i++){
    NcJets_++;
    if( cJets[i].pt() > 10 && fabs(cJets[i].eta()) < 2.5) NcJets10_++;
    if( cJets[i].pt() > 15 && fabs(cJets[i].eta()) < 2.5) NcJets15_++;
    if( cJets[i].pt() > 20 && fabs(cJets[i].eta()) < 2.5) NcJets20_++;
    if( cJets[i].pt() > 25 && fabs(cJets[i].eta()) < 2.5) NcJets25_++;
    if( cJets[i].pt() > 30 && fabs(cJets[i].eta()) < 2.5) NcJets30_++;
  }

}

std::vector<const reco::Candidate *> CMGTTbarCandidate::getAncestors(const reco::Candidate &c)
{
  vector<const reco::Candidate *> moms;
  if( c.numberOfMothers() == 1 ) {
    const Candidate * dau = &c;
    const Candidate * mom = c.mother();
    while ( dau->numberOfMothers() == 1) {
      moms.push_back( dau );
      dau = mom ;
      mom = dau->mother();
    } 
  } 
  return moms;
}

bool CMGTTbarCandidate::hasBottom(const reco::Candidate &c)
{
  int code1;
  int code2;
  bool tmpHasBottom = false;
  code1 = (int)( ( abs(c.pdgId() ) / 100)%10 );
  code2 = (int)( ( abs(c.pdgId() ) /1000)%10 );
  if ( code1 == 5 || code2 == 5) tmpHasBottom = true;
  return tmpHasBottom;
}

bool CMGTTbarCandidate::hasCharm(const reco::Candidate &c) 
{
  int code1;
  int code2;
  bool tmpHasCharm = false;
  code1 = (int)( ( abs(c.pdgId() ) / 100)%10 );
  code2 = (int)( ( abs(c.pdgId() ) /1000)%10 );
  if ( code1 == 4 || code2 == 4) tmpHasCharm = true;
  return tmpHasCharm;
}

bool CMGTTbarCandidate::decayFromBHadron(const Candidate & c)
{
   bool isFromB = false;
   vector<const Candidate *> allParents = getAncestors( c );
   for( vector<const Candidate *>::const_iterator aParent  = allParents.begin();
                                                  aParent != allParents.end(); 
                                                  aParent ++ ) 
     {
         if( hasBottom(**aParent) ) isFromB = true;
//         cout << "     particle Parent is " << (*aParent)->status()
//              << " type " << (*aParent)->pdgId()
//              << " pt= " << (*aParent)->pt()
//              << " isB = " << isFromB
//              << endl;
     }
   return isFromB;
}

bool CMGTTbarCandidate::decayFromCHadron(const Candidate & c)
{
  bool isFromC = false;
  vector<const Candidate *> allParents = getAncestors( c );
  for( vector<const Candidate *>::const_iterator aParent  = allParents.begin();
                                                 aParent != allParents.end();
                                                 aParent ++ )
  {
    if( hasCharm(**aParent) ) isFromC = true;
/*
         cout << "     particle Parent is " << (*aParent)->status()
              << " type " << (*aParent)->pdgId()
              << " pt=" << (*aParent)->pt()
              << " isC = " << isFromC
              << endl;
*/
   }
   return isFromC;
}

const Candidate* CMGTTbarCandidate::lastBHadron(const Candidate & c)
{
   const Candidate * out;
   
   vector<const Candidate *> allParents = getAncestors( c );
   for( vector<const Candidate *>::const_iterator aParent  = allParents.begin();
                                                  aParent != allParents.end();
                                                  aParent ++ )
     {
         if( hasBottom(**aParent) ) out = *aParent;
         
     }
   return out;
}

const Candidate* CMGTTbarCandidate::lastCHadron(const Candidate & c)
{
   const Candidate * out;

   vector<const Candidate *> allParents = getAncestors( c );
   for( vector<const Candidate *>::const_iterator aParent  = allParents.begin();
                                                  aParent != allParents.end();
                                                  aParent ++ )
     {
         if( hasCharm(**aParent) ) out = *aParent;

     }
   return out;
}

bool CMGTTbarCandidate::isLastbottom( const reco::GenParticle& p ){
   bool out = true;

   unsigned int nDaughters = p.numberOfDaughters();
   for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
     const reco::Candidate* daugh = p.daughter(iDaughter);
     if( abs(daugh->pdgId()) == 5) {
       out = false;
       break;
     }
   }

   return out;
}

bool CMGTTbarCandidate::isLastcharm( const reco::GenParticle& p ){
   bool out = true;

   unsigned int nDaughters = p.numberOfDaughters();
   for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
     const reco::Candidate* daugh = p.daughter(iDaughter);
     if( abs(daugh->pdgId()) == 4) {
       out = false;
       break;
     }
   }

   return out;
}

bool CMGTTbarCandidate::isLastParton( const reco::GenParticle& p){

   bool out = true;

   int id = abs( p.pdgId() );

   unsigned int nDaughters = p.numberOfDaughters();
   for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
     const reco::Candidate* daugh = p.daughter(iDaughter);
     if( abs(daugh->pdgId()) == id) {
       out = false;
       break;
     }
   }

   return out;
}

const reco::Candidate* CMGTTbarCandidate::getLast( const reco::Candidate& p ){

   const reco::Candidate* last = 0;
   int id = abs( p.pdgId() );
   unsigned int nDaughters = p.numberOfDaughters();
   if( nDaughters == 1) {
     const reco::Candidate* daugh = p.daughter(0);
     if( abs( daugh->pdgId() ) == id ){ 
       last = getLast( *daugh );
     }else{
       last = &p;
     }
   }else{
     last = &p;
   }

   return last;

}

bool CMGTTbarCandidate::isFromtop( const reco::GenParticle& p){
  bool out = false;

  string pt = Form("%f", p.pt());
  string pdgid = Form("%i",p.pdgId());
  const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
  while( mother != 0 ){
    string id = Form("%i", mother->pdgId());
    string mopt = Form("%f", mother->pt());
    if( abs(mother->pdgId()) == 6 ) {
      out = true;
    }
    mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
  }

  return out;
}

double CMGTTbarCandidate::deltaR( const Candidate& pasObj, const Candidate& proObj ) {

  double pasEta = pasObj.eta();
  double pasPhi = pasObj.phi();

  double proEta = proObj.eta();
  double proPhi = proObj.phi();

  double dRval = reco::deltaR(proEta, proPhi, pasEta, pasPhi);

  return dRval;

}




