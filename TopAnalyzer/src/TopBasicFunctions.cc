#include "KoPFA/TopAnalyzer/interface/TopBasicFunctions.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/LorentzVector.h"

using namespace std;
using namespace reco;
using namespace vallot;

std::vector<const reco::Candidate *> vallot::getAncestors(const reco::Candidate &c)
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


bool vallot::hasBottom(const reco::Candidate &c) 
{
  int code1;
  int code2;
  bool tmpHasBottom = false;
  code1 = (int)( ( abs(c.pdgId() ) / 100)%10 );
  code2 = (int)( ( abs(c.pdgId() ) /1000)%10 );
  if ( code1 == 5 || code2 == 5) tmpHasBottom = true;
  return tmpHasBottom;
}

bool vallot::decayFromBHadron(const Candidate & c)
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

const Candidate* vallot::lastBHadron(const Candidate & c)
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

double vallot::dR( const Candidate& pasObj, const GenJet& proObj ) {
    
  double pasEta = pasObj.eta();
  double pasPhi = pasObj.phi();

  double proEta = proObj.eta();
  double proPhi = proObj.phi();

  double dRval = deltaR(proEta, proPhi, pasEta, pasPhi);

  return dRval;

}

