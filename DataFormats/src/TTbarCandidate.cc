#include "KoPFA/DataFormats/interface/TTbarCandidate.h"
#include "CommonTools/Utils/interface/PtComparator.h"
#include "DataFormats/Math/interface/deltaR.h"
#include <map>
#include <vector>
 
using namespace std;
using namespace reco;
using namespace Ko;

void TTbarCandidate::building( const reco::GenJetCollection* genJets, const reco::GenParticleCollection* genParticles  ){

  math::XYZTLorentzVector null(0,0,0,0); 

  bquarks_.push_back(null);
  bquarks_.push_back(null);
  bquarks_.push_back(null);
  bquarks_.push_back(null);

  leptons_.push_back(null);
  leptons_.push_back(null);

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

    ttbarGen += p.p4();
    mass_ = ttbarGen.M();

    unsigned int nDaughters = p.numberOfDaughters();
    int nW = 0;
    for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
      const reco::Candidate* daugh = p.daughter(iDaughter);
      if ( nW == 1 ) break;
      if ( abs(daugh->pdgId()) != 24 ) continue; 
      unsigned int nWDaughters = daugh->numberOfDaughters();
      for ( unsigned iWDaughter=0; iWDaughter<nWDaughters; ++iWDaughter ) {
	const reco::Candidate* decay = daugh->daughter(iWDaughter);
	int decayId = abs(decay->pdgId());
	if ( decayId == 11  ) {  
          leptons_[ntop] = decay->p4() ;
	  electronic[ntop] = true;
	  break; 
	} else if ( decayId == 13 ) {  
	  muonic[ntop] = true;
          leptons_[ntop] = decay->p4() ;
	  break;
	} else if ( decayId == 15  ) {  
          taunic[ntop] = true;
          unsigned int nTauDaughters = decay->numberOfDaughters();
          for ( unsigned iTauDaughter=0; iTauDaughter<nTauDaughters; ++iTauDaughter ) {
            const reco::Candidate* tauDecay = decay->daughter(iTauDaughter);
            int tauDecayId = abs(tauDecay->pdgId());
            if ( tauDecayId == 11  ) {
              electronic[ntop] = true;
              leptons_[ntop] = tauDecay->p4() ;
              break;
            } else if ( tauDecayId == 13 ) {
              muonic[ntop] = true;
              leptons_[ntop] = tauDecay->p4() ;
              break;
            } else if (  tauDecayId == 15 ) {
              unsigned int nTauGrandDaughters = tauDecay->numberOfDaughters();
              for ( unsigned iTauGrandDaughter=0; iTauGrandDaughter<nTauGrandDaughters; ++iTauGrandDaughter ) {
                const reco::Candidate* tauGrandDecay = tauDecay->daughter(iTauGrandDaughter);
                int tauGrandDecayId = abs(tauGrandDecay->pdgId());
                if ( tauGrandDecayId == 11 ) {
                  electronic[ntop] = true;
                  leptons_[ntop] = tauGrandDecay->p4() ;
                  break;
                } else if ( tauGrandDecayId == 13 ) {
                  muonic[ntop] = true;
                  leptons_[ntop] = tauGrandDecay->p4() ;
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
    if( bquarksfromtop[i].pt() > 20 && abs(bquarksfromtop[i].eta()) < 2.5) nbQuark20++;
  }
  for( unsigned int i = 0 ; i < bquarksfromnotop.size() ; i++){
    if( i < 2){
      bquarks_[i] = bquarksfromnotop[i];
    }
    if( bquarksfromnotop[i].pt() > 20 && abs(bquarksfromnotop[i].eta()) < 2.5) nbQuark20++;
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

  std::vector<math::XYZTLorentzVector> bJets;
  std::vector<math::XYZTLorentzVector> bJetsBHad;
  std::vector<math::XYZTLorentzVector> bJetsfromnotop;
  std::vector<math::XYZTLorentzVector> cJets;

  int nJet30 = 0;
  int nJet25 = 0;
  int nJet20 = 0;
  int nJet15 = 0;
  int nJet10 = 0;
  int idx = 0;

  int nbJets15NoTop = 0;
  int nbJets20NoTop = 0;
  int ncJets = 0;
  int ncJets10 = 0;
  int ncJets15 = 0;
  int ncJets20 = 0;

  for (reco::GenJetCollection::const_iterator genJet=genJets->begin();genJet!=genJets->end();++genJet){
    const reco::GenJet& gJet = *genJet;

    double minDR = 999;
    for(unsigned int i=0 ; i < bquarks.size() ; i++){
      double deta = gJet.eta()-bquarks[i].eta();
      double dphi = gJet.phi()-bquarks[i].phi();
      double dR = sqrt( deta*deta + dphi*dphi );
      if( dR < minDR ) minDR = dR;
    }
    if( minDR < 0.5 ) bJets.push_back(gJet.p4());

    double minDR2b = 999;
    for(unsigned int i=0 ; i < bquarksfromnotop.size() ; i++){
      double deta = gJet.eta()-bquarksfromnotop[i].eta();
      double dphi = gJet.phi()-bquarksfromnotop[i].phi();
      double dR = sqrt( deta*deta + dphi*dphi ); 
      if( dR < minDR2b ) minDR2b = dR;
    }
    if( minDR2b < 0.5 ) bJetsfromnotop.push_back(gJet.p4());

    double minDR2c = 999;
    for(unsigned int i=0 ; i < cquarks.size() ; i++){
      double deta = gJet.eta()-cquarks[i].eta();
      double dphi = gJet.phi()-cquarks[i].phi();
      double dR = sqrt( deta*deta + dphi*dphi );
      if( dR < minDR2c ) minDR2c = dR;
    }
    if( minDR2c < 0.5 ) cJets.push_back(gJet.p4());

    if( gJet.pt() > 30 && abs(gJet.eta()) < 2.5 ) nJet30++;
    if( gJet.pt() > 25 && abs(gJet.eta()) < 2.5 ) nJet25++;
    if( gJet.pt() > 20 && abs(gJet.eta()) < 2.5 ) nJet20++;
    if( gJet.pt() > 15 && abs(gJet.eta()) < 2.5 ) nJet15++;
    if( gJet.pt() > 10 && abs(gJet.eta()) < 2.5 ) nJet10++;

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

  NJets_ = (int) genJets->size();
  NJets30_ = nJet30;
  NJets25_ = nJet25;
  NJets20_ = nJet20;
  NJets15_ = nJet15;
  NJets10_ = nJet10;

  for( std::map<const reco::Candidate*, vector<int> >::iterator it = mapBHadronToJets.begin() ; it != mapBHadronToJets.end(); it++){

    const reco::Candidate* BHadron = (*it).first;

    if( (*it).second.size() > 1) {
      double minDR = 999;
      int selectedJet = -1;
      for( std::vector<int>::iterator bjet = (*it).second.begin(); bjet != (*it).second.end(); bjet++){
        int idx = *bjet;
        mapJetToBMatched[idx] = 0; // set it to 0 again 
        const reco::GenJet& bjet = genJets->at(idx);
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

  for( std::map<int, vector<const reco::Candidate*> >::iterator it = mapJetToBHadrons.begin() ; it != mapJetToBHadrons.end(); it++){
    if( (*it).second.size() > 1) cout << "!!! This jet matches with more than 1 hadron !!!" << endl;
    int idx = (*it).first;
    const reco::GenJet& genJet = genJets->at(idx);
    // is It unique b-jet?  
    if( mapJetToBMatched[idx]  == 0 ) continue;
    bJetsBHad.push_back( genJet.p4() );
  }

  std::sort(bJetsBHad.begin(), bJetsBHad.end(), GreaterByPt<reco::Candidate::LorentzVector>());

  int nbJet15BHad = 0;
  int nbJet20BHad = 0;
  for( unsigned int i = 0 ; i < bJets.size() ; i++){
    if( i < 4 ){
      bJets_[i] = bJetsBHad[i];
    }
    if( bJetsBHad[i].pt() > 20 && abs(bJetsBHad[i].eta()) < 2.5) nbJet20BHad++;
    if( bJetsBHad[i].pt() > 15 && abs(bJetsBHad[i].eta()) < 2.5) nbJet15BHad++;
  }

  NbJetsBHad_ = (int) bJetsBHad.size();
  NbJets15BHad_ = nbJet15BHad;
  NbJets20BHad_ = nbJet20BHad;

  int nbJets15 = 0;
  int nbJets20 = 0;

  for( unsigned int i = 0 ; i < bJets.size() ; i++){
    if( bJets[i].pt() > 15 && abs(bJets[i].eta()) < 2.5) nbJets15++;
    if( bJets[i].pt() > 20 && abs(bJets[i].eta()) < 2.5) nbJets20++;
  }

  NbJets_ = (int) bJets.size();
  NbJets15_ = nbJets15;
  NbJets20_ = nbJets20;

  for( unsigned int i = 0 ; i < bJetsfromnotop.size() ; i++){
    if( bJetsfromnotop[i].pt() > 15 && abs(bJetsfromnotop[i].eta()) < 2.5) nbJets15NoTop++;
    if( bJetsfromnotop[i].pt() > 20 && abs(bJetsfromnotop[i].eta()) < 2.5) nbJets20NoTop++;
  }

  NbJetsNoTop_ = (int) bJetsfromnotop.size();
  NbJets15NoTop_ = nbJets15NoTop;
  NbJets20NoTop_ = nbJets20NoTop;

  for( unsigned int i = 0 ; i < cJets.size() ; i++){
    if( cJets[i].pt() > 10 && abs(cJets[i].eta()) < 2.5) ncJets10++;
    if( cJets[i].pt() > 15 && abs(cJets[i].eta()) < 2.5) ncJets15++;
    if( cJets[i].pt() > 20 && abs(cJets[i].eta()) < 2.5) ncJets20++;
  }

  NcJets_ = (int) cJets.size();
  NcJets10_ = ncJets10;
  NcJets15_ = ncJets15;
  NcJets20_ = ncJets20;

}

std::vector<const reco::Candidate *> TTbarCandidate::getAncestors(const reco::Candidate &c)
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


bool TTbarCandidate::hasBottom(const reco::Candidate &c) 
{
  int code1;
  int code2;
  bool tmpHasBottom = false;
  code1 = (int)( ( abs(c.pdgId() ) / 100)%10 );
  code2 = (int)( ( abs(c.pdgId() ) /1000)%10 );
  if ( code1 == 5 || code2 == 5) tmpHasBottom = true;
  return tmpHasBottom;
}

bool TTbarCandidate::decayFromBHadron(const Candidate & c)
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

const Candidate* TTbarCandidate::lastBHadron(const Candidate & c)
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

bool TTbarCandidate::isLastbottom( const reco::GenParticle& p ){
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

bool TTbarCandidate::isLastcharm( const reco::GenParticle& p ){
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

bool TTbarCandidate::isFromtop( const reco::GenParticle& p){
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

double TTbarCandidate::deltaR( const Candidate& pasObj, const GenJet& proObj ) {
    
  double pasEta = pasObj.eta();
  double pasPhi = pasObj.phi();

  double proEta = proObj.eta();
  double proPhi = proObj.phi();

  double dRval = reco::deltaR(proEta, proPhi, pasEta, pasPhi);

  return dRval;

}



