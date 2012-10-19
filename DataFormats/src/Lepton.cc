#include "KoPFA/DataFormats/interface/Lepton.h"

using namespace vallot; 
using namespace std;

Lepton::Lepton( const reco::Candidate::LorentzVector& p4, const int& charge  ) : LorentzVector(p4){

  charge_ = charge;
  pt_ = p4.pt();
}

void Lepton::setIsoDeposit( pat::IsolationKeys key, const pat::IsoDeposit *dep, reco::isodeposit::AbsVetos vetos) {
  assert( key == pat::PfChargedHadronIso ||
	  key == pat::PfNeutralHadronIso ||
	  key == pat::PfGammaIso );

  if( key == pat::PfChargedHadronIso ) {
    chIso03_ = dep->depositAndCountWithin(0.3, vetos).first;
    chIso04_ = dep->depositAndCountWithin(0.4, vetos).first;
  }
  if( key == pat::PfNeutralHadronIso ) {
    nhIso03_ = dep->depositAndCountWithin(0.3, vetos).first;
    nhIso04_ = dep->depositAndCountWithin(0.4, vetos).first;
  }
  if( key == pat::PfGammaIso ) {
    phIso03_ = dep->depositAndCountWithin(0.3, vetos).first;
    phIso04_ = dep->depositAndCountWithin(0.4, vetos).first;
  }

}



