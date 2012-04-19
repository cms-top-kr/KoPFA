#include "KoPFA/DataFormats/interface/TTbarCandidate.h"
#include "CommonTools/Utils/interface/PtComparator.h"
#include "DataFormats/Math/interface/deltaR.h"
#include <map>
#include <vector>
 
using namespace std;
using namespace reco;
using namespace Ko;

void TTbarCandidate::setMatchedBJets(const reco::GenJetCollection* genJets){

  math::XYZTLorentzVector null(0,0,0,0);

  bJets_.push_back(null);
  bJets_.push_back(null);


  std::map<int, vector<const reco::Candidate*> > mapJetToBHadrons;
  std::map<int, int> mapJetToBMatched;
  std::map<const reco::Candidate*, vector<int> > mapBHadronToJets;

  std::vector<math::XYZTLorentzVector> bJets;

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
        double dR = deltaR( *BHadron, bjet ) ; 
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

  std::sort(bJets.begin(), bJets.end(), GreaterByPt<reco::Candidate::LorentzVector>());
 
  for( unsigned int i = 0 ; i < bJets.size() ; i++){
    std::cout << "debug =  " <<bJets[i].pt() << std::endl;
    bJets_[i] = bJets[i];
    if(i == 1) break;
  }
}

void TTbarCandidate::building( const reco::GenParticleCollection* genParticles  ){


  math::XYZTLorentzVector null(0,0,0,0); 

  leptons_.push_back(null);
  leptons_.push_back(null);

  std::vector<bool> electronic(2,static_cast<bool>(false));
  std::vector<bool> muonic(2,static_cast<bool>(false));
  std::vector<bool> taunic(2,static_cast<bool>(false));
  std::vector<bool> hadronic(2,static_cast<bool>(false));


  unsigned int nParticles = genParticles->size();
  int ntop = 0;
  reco::Candidate::LorentzVector ttbarGen;

  for ( unsigned int ip=0; ip<nParticles; ++ip ) { 

    if ( ntop == 2 ) break;

    const reco::GenParticle& p = (*genParticles)[ip];

    if ( abs(p.pdgId()) != 6 ) continue;

    ttbarGen += p.p4();
    mass_ = ttbarGen.M();

    unsigned int nDaughters = p.numberOfDaughters();
    int nW = 0;
    for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
      const reco::Candidate* daugh = p.daughter(iDaughter);
      if ( nW == 1 ) break;
      if ( abs(daugh->pdgId()) == 5 ) {
         bquarks_.push_back( daugh->p4() );
      }

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


  taunic_ = false; 
  if( taunic[1] == true || taunic[0] == true){ 
    taunic_ = true;
  }

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



