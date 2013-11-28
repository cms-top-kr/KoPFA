#include "KoPFA/CMGDataFormats/interface/CMGTTbarJPsiCandidate.h"
#include "CommonTools/Utils/interface/PtComparator.h"
#include "DataFormats/Math/interface/deltaR.h"
#include <map>
#include <vector>
 
using namespace std;
using namespace reco;
using namespace vallot;

void CMGTTbarJPsiCandidate::building( const std::vector<cmg::GenJet>* genJets, const reco::GenParticleCollection* genParticles  ){

  math::XYZTLorentzVector null(0,0,0,0); 

  tquarks_.push_back(null);
  tquarks_.push_back(null);
  bquarks_.push_back(null);
  bquarks_.push_back(null);
  ///bquarks_.push_back(null);
  ///bquarks_.push_back(null);

  leptons_.push_back(null);
  leptons_.push_back(null);
  /*JPsiB_.push_back(null);
  JPsiB_.push_back(null);*/
  priJPsi_.push_back(null);
  secJPsi_.push_back(null);
  tbJPsi_.push_back(null);
  tbJPsilp_.push_back(null);
  tbJPsilm_.push_back(null);
  tbbJPsi_.push_back(null);
  tbbJPsilp_.push_back(null);
  tbbJPsilm_.push_back(null);
  /*JPsi_.push_back(null);
  JPsi_.push_back(null);
  lepJPsi_.push_back(null);
  lepJPsi_.push_back(null);
  JPsileptonP_.push_back(null);
  JPsileptonP_.push_back(null);
  JPsileptonM_.push_back(null);
  JPsileptonM_.push_back(null);*/
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
  int topKind = 0;
  reco::Candidate::LorentzVector ttbarGen;

  ///std::vector<math::XYZTLorentzVector> bquarksfromnotop;
  std::vector<math::XYZTLorentzVector> bquarksfromtop;
  std::vector<math::XYZTLorentzVector> bquarksfromtopbar;
  std::vector<math::XYZTLorentzVector> bquarks;
  std::vector<math::XYZTLorentzVector> priJPsi;
  std::vector<math::XYZTLorentzVector> secJPsi;
  std::vector<math::XYZTLorentzVector> tbJPsi;
  std::vector<math::XYZTLorentzVector> tbJPsilp;
  std::vector<math::XYZTLorentzVector> tbJPsilm;
  std::vector<math::XYZTLorentzVector> tbbJPsi;
  std::vector<math::XYZTLorentzVector> tbbJPsilp;
  std::vector<math::XYZTLorentzVector> tbbJPsilm;
  std::vector<double> priJPsi3DlTrue;
  std::vector<double> secJPsi3DlTrue;
  std::vector<double> tbJPsi3DlTrue;
  std::vector<double> tbbJPsi3DlTrue;
  std::vector<double> priJPsippdlTrue;  
  std::vector<double> secJPsippdlTrue;  
  std::vector<double> tbJPsippdlTrue;  
  std::vector<double> tbbJPsippdlTrue;  
  std::vector<double> tbJPsidthetaTrue;
  std::vector<double> tbbJPsidthetaTrue;

  mass_ = 0;
  ////cout << "EVENT= " << endl;
  for ( unsigned int ip=0; ip<nParticles; ++ip ) { 

    const reco::GenParticle& p = (*genParticles)[ip];

    if ( abs(p.pdgId()) == 5 ) { //If p is b,
      bool isLast = isLastbottom(p); //If p(==b)'s daughter is b again, return false.
      if (isLast == true) {
        bool isfromtop = isFromtop(p); //If p(==b) is from top, return true.
        if(isfromtop) {
          if(p.pdgId() > 0)bquarksfromtop.push_back( p.p4() );
          if(p.pdgId() < 0)bquarksfromtopbar.push_back( p.p4() );
        ///}else{
          ///bquarksfromnotop.push_back( p.p4() );
        }
        bquarks.push_back( p.p4() );
      } 
    }
   
    if ( abs(p.pdgId()) == 443 ) { //If p is JPsi,
      ////cout<<"JPsi---------------------"<<endl;
      bool isLast = isLastParton(p); //If p(==JPsi)'s daughter is JPsi again, return false.
      if (isLast == true) {
        bool isfromb = isFrombottom(p); //If p(==JPsi) is from bquark, return true.
        bool isfromtop = isFromtop(p); //If p(==JPsi) is from top, return true.
        bool isfromt = isFromt(p); //If p(==JPsi) is from top, return true.
        bool isfromtbar = isFromtbar(p); //If p(==JPsi) is from top, return true.i
        int nDau = p.numberOfDaughters();

        if(isfromb && isfromtop) {
          ////cout<<"b->JPsi"<<endl;
          secJPsi.push_back( p.p4() );
          std::pair<double, double> dlTrue = getJPsidlTrue(p,6);
          secJPsi3DlTrue.push_back(dlTrue.first);
          secJPsippdlTrue.push_back(dlTrue.second);
          //cout<<"(t->)b->JPsi dlTrue : "<<dlTrue.first<<"/"<<dlTrue.second<<endl;
        }
       
        if(!isfromb && !isfromtop) {
          ////cout<<"prim. JPsi"<<endl;
          priJPsi.push_back( p.p4() );
          std::pair<double, double> dlTrue = getJPsidlTrue(p,-999);
          priJPsi3DlTrue.push_back(dlTrue.first);
          priJPsippdlTrue.push_back(dlTrue.second);
          //cout<<"prim. JPsi dlTrue : "<<dlTrue.first<<"/"<<dlTrue.second<<endl;

        }
  
        if(isfromb && isfromt) {
          ////cout<<"t->b->JPsi"<<endl;
          if(nDau==2){
            ////cout<<"2 Dau"<<endl;  
            const reco::Candidate* decay0 = p.daughter(0);
            const reco::Candidate* decay1 = p.daughter(1);
            if((decay0->pdgId() == 13) && (decay1->pdgId() == -13)){
              tbJPsi.push_back( p.p4() );
              std::pair<double, double> dlTrue = getJPsidlTrue(p,6);
              tbJPsi3DlTrue.push_back(dlTrue.first);
              tbJPsippdlTrue.push_back(dlTrue.second);
              tbJPsidthetaTrue.push_back(getdthetaTrue(p));
              tbJPsilp.push_back( decay0->p4() );
              tbJPsilm.push_back( decay1->p4() );
              //cout<<"t->b->JPsi dlTrue : "<<dlTrue.first<<"/"<<dlTrue.second<<endl;
            }
            if((decay0->pdgId() == -13) && (decay1->pdgId() == 13)){
              tbJPsi.push_back( p.p4() );
              std::pair<double, double> dlTrue = getJPsidlTrue(p,6);
              tbJPsi3DlTrue.push_back(dlTrue.first);
              tbJPsippdlTrue.push_back(dlTrue.second);
              tbJPsidthetaTrue.push_back(getdthetaTrue(p));
              tbJPsilp.push_back( decay1->p4() );
              tbJPsilm.push_back( decay0->p4() );
              //cout<<"t->b->JPsi dlTrue : "<<dlTrue.first<<"/"<<dlTrue.second<<endl;
            }
          }else{
             //cout<<"t->b->JPsi->not mumu"<<endl;
            //tbJPsinotmumu.push_back( p.p4() );
          }
        }

        if(isfromb && isfromtbar) {
          ////cout<<"tbar->b->JPsi"<<endl;
          if(nDau==2){
            ////cout<<"2 Dau"<<endl; 
            const reco::Candidate* decay0 = p.daughter(0);
            const reco::Candidate* decay1 = p.daughter(1);
            if((decay0->pdgId() == 13) && (decay1->pdgId() == -13)){
              tbbJPsi.push_back( p.p4() );
              std::pair<double, double> dlTrue = getJPsidlTrue(p,6);
              tbbJPsi3DlTrue.push_back(dlTrue.first);
              tbbJPsippdlTrue.push_back(dlTrue.second);
              tbbJPsidthetaTrue.push_back(getdthetaTrue(p));
              tbbJPsilp.push_back( decay0->p4() );
              tbbJPsilm.push_back( decay1->p4() );
              //cout<<"tbar->b->JPsi dlTrue : "<<dlTrue.first<<"/"<<dlTrue.second<<endl;
            }
            if((decay0->pdgId() == -13) && (decay1->pdgId() == 13)){
              tbbJPsi.push_back( p.p4() );
              std::pair<double, double> dlTrue = getJPsidlTrue(p,6);
              tbbJPsi3DlTrue.push_back(dlTrue.first);
              tbbJPsippdlTrue.push_back(dlTrue.second);
              tbbJPsidthetaTrue.push_back(getdthetaTrue(p));
              tbbJPsilp.push_back( decay1->p4() );
              tbbJPsilm.push_back( decay0->p4() );
              //cout<<"tbar->b->JPsi dlTrue : "<<dlTrue.first<<"/"<<dlTrue.second<<endl;
            }
          }else{
             //cout<<"tbar->b->JPsi->not mumu"<<endl;
            //tbbJPsinotmumu.push_back( p.p4() );
          }
        }
    
      }
      //cout<<"------------------"<<endl;
    }
    
    /*if ( abs(p.pdgId()) == 4 ) {
      bool isLast = isLastcharm(p);
      if(isLast == true){
        bool isfromtop = isFromtop(p);
        if( isfromtop == false ) cquarks.push_back( p.p4() );
      }
    }*/

    if ( ntop == 2 ) continue; //ntop0, ntop1
    if ( abs(p.pdgId()) != 6 ) continue; //If p == top quark, go through.
    if ( p.pdgId() == 6 ) topKind = 0;
    if ( p.pdgId() == -6 ) topKind = 1;
    ////cout<<"topKind = " << topKind << endl;

    bool isLast = isLastParton(p); //If p's daughter's id == p's, return false.
    if(isLast != true) continue; //If p is not last top, finish.
    //debug
    ////cout << "ntop = " << ntop << endl;
 
    ttbarGen += p.p4();  //LorentzVector 
    if( ntop == 1 ) { //ntop0 + ntop1 = ttbar
      mass_ = ttbarGen.M();
    }
    
    tquarks_[topKind] = p.p4();
   
    unsigned int nDaughters = p.numberOfDaughters(); // p == top
    int nW = 0;
    for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
      const reco::Candidate* daughTemp = p.daughter(iDaughter);
      if ( nW == 1 ) break; //if p has 2nd W, just get out daughter loop. 
      if ( abs(daughTemp->pdgId()) != 24 ) continue;
      const reco::Candidate* daugh = getLast( *daughTemp ); //last W
      unsigned int nWDaughters = daugh->numberOfDaughters();
      //debug
      ////cout << "nW daughters= " << nWDaughters << endl;
      int nWleptonDaughters = 0;
      for ( unsigned iWDaughter=0; iWDaughter<nWDaughters; ++iWDaughter ) {
        const reco::Candidate* decay = daugh->daughter(iWDaughter); //last W's daughter
        int decayId = abs(decay->pdgId());
        //debug
        ////cout << "W decay Id = " << decayId << endl;
        if ( decayId == 11 || decayId == 12 ) {  //el, nuel
          if( nWleptonDaughters == 2 ) break;
          if( decayId == 11 ) {
            electronic[topKind] = true;
            leptons_[topKind] = decay->p4() ;
            nWleptonDaughters++;
          }
          if( decayId == 12 ) {
            nus_[topKind] = decay->p4() ;
            nWleptonDaughters++;
          }
        } else if ( decayId == 13 || decayId == 14 ) {  //mu, numu
          if( nWleptonDaughters == 2 ) break;
          if( decayId == 13 ) {
            muonic[topKind] = true;
            leptons_[topKind] = decay->p4() ;
            nWleptonDaughters++;
          }
          if( decayId == 14 ) {
            nus_[topKind] = decay->p4() ;
            nWleptonDaughters++;
          }
        } else if ( decayId == 15 || decayId == 16 ) {  //tau, nutau
          if( decayId == 15 ) taunic[topKind] = true;
          if( decayId == 16 ) taunus_[topKind] = decay->p4() ;
          unsigned int nTauDaughters = decay->numberOfDaughters();
          for ( unsigned iTauDaughter=0; iTauDaughter<nTauDaughters; ++iTauDaughter ) {
            const reco::Candidate* tauDecay = decay->daughter(iTauDaughter);
            int tauDecayId = abs(tauDecay->pdgId());
            if ( tauDecayId == 11 || tauDecayId == 12 ) {
            if( nWleptonDaughters == 2 ) break;
            if( tauDecayId == 11) {
              electronic[topKind] = true;
              leptons_[topKind] = tauDecay->p4() ;
              nWleptonDaughters++;
            }
            if( tauDecayId == 12) {
              nus_[topKind] = tauDecay->p4() ;
              nWleptonDaughters++;
            }
          } else if ( tauDecayId == 13 || tauDecayId == 14 ) {
            if( nWleptonDaughters == 2 ) break;
            if( tauDecayId == 13) {
              muonic[topKind] = true;
              leptons_[topKind] = tauDecay->p4() ;
              nWleptonDaughters++;
            }
            if( tauDecayId == 14) {
              nus_[topKind] = tauDecay->p4() ;
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
                    electronic[topKind] = true;
                    leptons_[topKind] = tauGrandDecay->p4() ;
                    nWleptonDaughters++;
                  }
                  if( tauGrandDecayId == 12 ) {
                    nus_[topKind] = tauGrandDecay->p4() ;
                    nWleptonDaughters++;
                  }
                } else if ( tauGrandDecayId == 13 || tauGrandDecayId == 14 ) {
                  if( nWleptonDaughters == 2 ) break;
                  if( tauGrandDecayId == 13 ){
                    muonic[topKind] = true;
                    leptons_[topKind] = tauGrandDecay->p4() ;
                    nWleptonDaughters++;
                  }
                  if( tauGrandDecayId == 12 ) {
                    nus_[topKind] = tauGrandDecay->p4() ;
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
        } else if( decayId < 6 ){ //decayId is less than 6, d(1), u(2), s(3), c(4), b(5)
          hadronic[topKind] = true;
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
  ////cout << "diLeptonic= " << diLeptonic_ << endl;
  ////cout << "diLeptonicMuoMuo= " << diLeptonicMuoMuo_ << endl;
  ////cout << "diLeptonicMuoEle= " << diLeptonicMuoEle_ << endl;
  ////cout << "diLeptonicEleEle= " << diLeptonicEleEle_ << endl;
  ////cout << "diLeptonicTauMuo= " << diLeptonicTauMuo_ << endl;
  ////cout << "diLeptonicTauEle= " << diLeptonicTauEle_ << endl;
  ////cout << "diLeptonicTauTau= " << diLeptonicTauTau_ << endl;

  taunic1_ = taunic[0]; //boolean
  taunic2_ = taunic[1]; //boolean

  //sort b-quarks from top since the leading two quarks must be from top.
  std::sort(bquarksfromtop.begin(), bquarksfromtop.end(), GreaterByPt<reco::Candidate::LorentzVector>());
  std::sort(bquarksfromtopbar.begin(), bquarksfromtopbar.end(), GreaterByPt<reco::Candidate::LorentzVector>());
  ///std::sort(bquarksfromnotop.begin(), bquarksfromnotop.end(), GreaterByPt<reco::Candidate::LorentzVector>());

  ///NbQuarksNoTop_ = (int) bquarksfromnotop.size();
  NbQuarksTop_ = (int) bquarksfromtop.size() + (int) bquarksfromtopbar.size();
  ///NcQuarks_ = (int) cquarks.size();

  //inseart b-quarks from top to the b-quarks from non-top.
  //bquarks.insert( bquarks.begin(), bquarksfromtop.begin(), bquarksfromtop.end());

  NbQuarks_ = (int) bquarks.size(); 

  int nbQuark20 = 0;
  for( unsigned int i = 0 ; i < bquarksfromtop.size() ; i++){
    if( i < 1){
      bquarks_[i] = bquarksfromtop[i];
    }
    if( bquarksfromtop[i].pt() > 20 && fabs(bquarksfromtop[i].eta()) < 2.5) nbQuark20++;
  }

  for( unsigned int i = 0 ; i < bquarksfromtopbar.size() ; i++){
    if( i < 1){
      bquarks_[i+1] = bquarksfromtopbar[i];
    }
    if( bquarksfromtopbar[i].pt() > 20 && fabs(bquarksfromtopbar[i].eta()) < 2.5) nbQuark20++;
  }

  /*for( unsigned int i = 0 ; i < bquarksfromnotop.size() ; i++){
    if( i < 2){
      bquarks_[2+i] = bquarksfromnotop[i];
    }
    if( bquarksfromnotop[i].pt() > 20 && fabs(bquarksfromnotop[i].eta()) < 2.5) nbQuark20++;
  }*/
  NbQuarks20_ = nbQuark20;

  NpJPsi_ = (int) priJPsi.size();
  for( unsigned int i = 0 ; i < priJPsi.size() ; i++){
    if( i < 1){
      priJPsi_[i] = priJPsi[i];
      priJPsi3DlTrue_ = priJPsi3DlTrue[i];
      priJPsippdlTrue_ = priJPsippdlTrue[i];
    }
  }

  NbJPsi_ = (int) secJPsi.size();
  for( unsigned int i = 0 ; i < secJPsi.size() ; i++){
    if( i < 1){
      secJPsi_[i] = secJPsi[i];
      secJPsi3DlTrue_ = secJPsi3DlTrue[i];
      secJPsippdlTrue_ = secJPsippdlTrue[i];
    }
  }

  NtbJPsi_ = (int) tbJPsi.size();
  NtbJPsilp_ = (int) tbJPsilp.size();
  NtbJPsilm_ = (int) tbJPsilm.size();
  for( unsigned int i = 0 ; i < tbJPsi.size() ; i++){
    if( i < 1 && NtbJPsilp_>0 && NtbJPsilm_>0){
      tbJPsi_[i] = tbJPsi[i];
      tbJPsi3DlTrue_ = tbJPsi3DlTrue[i];
      tbJPsippdlTrue_ = tbJPsippdlTrue[i];
      tbJPsidthetaTrue_ = tbJPsidthetaTrue[i];
      tbJPsilp_[i] = tbJPsilp[i];
      tbJPsilm_[i] = tbJPsilm[i];
    }
  }

  NtbbJPsi_ = (int) tbbJPsi.size();
  NtbbJPsilp_ = (int) tbbJPsilp.size();
  NtbbJPsilm_ = (int) tbbJPsilm.size();
  for( unsigned int i = 0 ; i < tbbJPsi.size() ; i++){
    if( i < 1 && NtbbJPsilp_>0 && NtbbJPsilm_>0){
      tbbJPsi_[i] = tbbJPsi[i];
      tbbJPsi3DlTrue_ = tbbJPsi3DlTrue[i];
      tbbJPsippdlTrue_ = tbbJPsippdlTrue[i];
      tbbJPsidthetaTrue_ = tbbJPsidthetaTrue[i];
      tbbJPsilp_[i] = tbbJPsilp[i];
      tbbJPsilm_[i] = tbbJPsilm[i];
    }
  }

//////
  bJets_.push_back(null);
  bJets_.push_back(null);
  ///bJets_.push_back(null);
  ///bJets_.push_back(null);

  std::map<int, vector<const reco::Candidate*> > mapJetToBHadrons;
  std::map<int, int> mapJetToBMatched;
  std::map<const reco::Candidate*, vector<int> > mapBHadronToJets;

  ///std::map<int, vector<const reco::Candidate*> > mapJetToCHadrons;
  ///std::map<int, int> mapJetToCMatched;
  ///std::map<const reco::Candidate*, vector<int> > mapCHadronToJets;

  std::vector<math::XYZTLorentzVector> bJets;
  std::vector<math::XYZTLorentzVector> bJetsBHad;
  std::vector<math::XYZTLorentzVector> nobJetsBHad;
  ///std::vector<math::XYZTLorentzVector> bJetsfromnotop;
  ///std::vector<math::XYZTLorentzVector> cJets;
  ///std::vector<math::XYZTLorentzVector> cJetsCHad;

  int idx = 0; //genJet's index

  NJets_ = 0;
  NJets30_ = 0;
  NJets25_ = 0;
  NJets20_ = 0;
  NJets15_ = 0;
  NJets10_ = 0;

  //JPsiBID_ = 0;
  //NbJetJPsi_ = 0;

  for (std::vector<cmg::GenJet>::const_iterator genJet=genJets->begin();genJet!=genJets->end();++genJet, ++idx){ //genJet loop
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
    if( minDR < 0.5 ) bJets.push_back(gJet.p4()); //bJets is mached gJet with bquarks

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
        //int Bmoid = -99;
        //int topkind = -99;
        const GenParticle* mcpart = mcparts[i];
        //int PDG = std::abs( mcpart->pdgId());
        ////cout << "mcpart ID : " << PDG <<endl;
        bool isB = decayFromBHadron(*mcpart); //If genJet's one of constituents's ancestors is B, return true.
        if(isB){
           const reco::Candidate* lastB = lastBHadron(*mcpart); // mcpart's mother B is returned.
           //topkind = fromWhichTopKind(lastB);
           //topkind = fromWhichTopKind(*mcpart);
           ////cout << "topkind = " << topkind << endl;       
           vector<const reco::Candidate*>::iterator it = find ( mapJetToBHadrons[idx].begin(), mapJetToBHadrons[idx].begin(), lastB );
           if( it == mapJetToBHadrons[idx].end() ){ //Find current B is in mapJetToBHadrons, if not, push_back into it.
             mapJetToBHadrons[idx].push_back(lastB);
             mapJetToBMatched[idx] = 1;
             mapBHadronToJets[lastB].push_back( idx );
             
           /*  const reco::Candidate* daugh = getLast( *lastB );
             unsigned int nBDaughters = daugh->numberOfDaughters(); //b's daughter
             ////cout << "n B daughters = " << nBDaughters << endl;
             for ( unsigned iBDaughter=0; iBDaughter<nBDaughters; ++iBDaughter ) {
               const reco::Candidate* BDaughTemp = daugh->daughter(iBDaughter);
               if ( NbJetJPsi_ == 1 ) break; //if p has 2nd JPsi, just get out daughter loop.
               if ( BDaughTemp->pdgId() != 443 ) continue;
               if ( topkind < 0 ) continue;
               ////cout << "n B daughters = " << nBDaughters << endl;
               ////cout<< "B JPsi ID = " << BDaughTemp->pdgId() << endl; 
               const reco::Candidate* JPsiCand = getLast( *BDaughTemp ); //last JPsi
               ////cout<< "B mother/daughter ID = " << topkind <<"/"<< JPsiCand->pdgId() << endl;
               unsigned int nJPsiDaughters = JPsiCand->numberOfDaughters();
               //debug
               ////cout << "nJPsi daughters= " << nJPsiDaughters << endl;
               if( nJPsiDaughters != 2) continue;
               //int nJPsileptonDaughters = 0;
               for ( unsigned iJPsiDaughter=0; iJPsiDaughter<nJPsiDaughters; ++iJPsiDaughter ) {
                 const reco::Candidate* decay = JPsiCand->daughter(iJPsiDaughter); //last JPsi's daughter  
                 int decayId = decay->pdgId();
                 //debug
                 ////cout << "JPsi decay Id = " << decayId << endl;
                 if ( abs(decayId) == 13 ) {  //mu
                  // if( nJPsileptonDaughters == 2 ) break;
                   if( decayId > 0){
                     ////cout<<decayId<<endl;
                     JPsiB_[topkind] = daugh->p4() ;
                     JPsiBID_ = daugh->pdgId();
                     JPsi_[topkind] = JPsiCand->p4() ;
                     lepJPsi_[topkind] = JPsi_[topkind]+leptons_[topkind];
                     NbJetJPsi_++;
                     ////cout<<"NbJetJPsi : " <<NbJetJPsi_<<endl;

                     JPsileptonP_[topkind] = decay->p4() ;
                     //nJPsileptonDaughters++;
                   }
                   if( decayId < 0){
                     ////cout<<decayId<<endl;
                     JPsileptonM_[topkind] = decay->p4() ;
                     //nJPsileptonDaughters++;
                   }
                 }
               }
             }*/

             
           }
        }
        /*bool isC = decayFromCHadron(*mcpart);
        if(isC){
          const reco::Candidate* lastC = lastCHadron(*mcpart);
          vector<const reco::Candidate*>::iterator it = find ( mapJetToCHadrons[idx].begin(), mapJetToCHadrons[idx].begin(), lastC );
          if( it == mapJetToCHadrons[idx].end() ){
            mapJetToCHadrons[idx].push_back(lastC);
            mapJetToCMatched[idx] = 1;
            mapCHadronToJets[lastC].push_back( idx );
          }
        }*/
      }
    }

  } //genJet loop

  ////cout << "idx : " << idx << endl;

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

/*  for( std::map<const reco::Candidate*, vector<int> >::iterator it = mapCHadronToJets.begin() ; it != mapCHadronToJets.end(); it++){

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

  }*/


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
    if( i < 2 ){
      bJets_[i] = bJetsBHad[i];
    }
    NbJetsBHad_++;
    if( bJetsBHad[i].pt() > 10 && fabs(bJetsBHad[i].eta()) < 2.5) NbJets10BHad_++;
    if( bJetsBHad[i].pt() > 15 && fabs(bJetsBHad[i].eta()) < 2.5) NbJets15BHad_++;
    if( bJetsBHad[i].pt() > 20 && fabs(bJetsBHad[i].eta()) < 2.5) NbJets20BHad_++;
    if( bJetsBHad[i].pt() > 25 && fabs(bJetsBHad[i].eta()) < 2.5) NbJets25BHad_++;
    if( bJetsBHad[i].pt() > 30 && fabs(bJetsBHad[i].eta()) < 2.5) NbJets30BHad_++;
  }
/*  for( std::map<int, vector<const reco::Candidate*> >::iterator it = mapJetToCHadrons.begin() ; it != mapJetToCHadrons.end(); it++){
    if( (*it).second.size() > 1) //cout << "!!! This jet matches with more than 1 hadron !!!" << endl;
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
  }*/

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

/*  NbJetsNoTop_ = 0;
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
  }*/
}


std::vector<const reco::Candidate *> CMGTTbarJPsiCandidate::getAncestors(const reco::Candidate &c)
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

bool CMGTTbarJPsiCandidate::hasBottom(const reco::Candidate &c)
{
  int code1;
  int code2;
  bool tmpHasBottom = false;
  // B0 511,B0bar, B+ 521, B-, Bc+ 541, Bc-, Bs0 531, Bs0bar 
  // lamdab0 5122, sigmab0 5232, sigmab- 5132, sigmab+, omegab- 5332 
  code1 = (int)( ( abs(c.pdgId() ) / 100)%10 );
  code2 = (int)( ( abs(c.pdgId() ) /1000)%10 );
  if ( code1 == 5 || code2 == 5) tmpHasBottom = true;
  return tmpHasBottom;
}

bool CMGTTbarJPsiCandidate::hasCharm(const reco::Candidate &c) 
{
  int code1;
  int code2;
  bool tmpHasCharm = false;
  code1 = (int)( ( abs(c.pdgId() ) / 100)%10 );
  code2 = (int)( ( abs(c.pdgId() ) /1000)%10 );
  if ( code1 == 4 || code2 == 4) tmpHasCharm = true;
  return tmpHasCharm;
}

bool CMGTTbarJPsiCandidate::decayFromBHadron(const Candidate & c)
{
   bool isFromB = false;
   vector<const Candidate *> allParents = getAncestors( c );
   for( vector<const Candidate *>::const_iterator aParent  = allParents.begin();
                                                  aParent != allParents.end(); 
                                                  aParent ++ ) 
     {
         if( hasBottom(**aParent) ) isFromB = true;
        /* if(isFromB == true){
              //cout << "     particle Parent is " << (*aParent)->status()
              << " type " << (*aParent)->pdgId()
              << " pt= " << (*aParent)->pt()
              << " isB = " << isFromB
              << endl;
         }*/
     }
   return isFromB;
}

bool CMGTTbarJPsiCandidate::decayFromCHadron(const Candidate & c)
{
  bool isFromC = false;
  vector<const Candidate *> allParents = getAncestors( c );
  for( vector<const Candidate *>::const_iterator aParent  = allParents.begin();
                                                 aParent != allParents.end();
                                                 aParent ++ )
  {
    if( hasCharm(**aParent) ) isFromC = true;
/*
         //cout << "     particle Parent is " << (*aParent)->status()
              << " type " << (*aParent)->pdgId()
              << " pt=" << (*aParent)->pt()
              << " isC = " << isFromC
              << endl;
*/
   }
   return isFromC;
}

const Candidate* CMGTTbarJPsiCandidate::lastBHadron(const Candidate & c)
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

/*const Candidate* CMGTTbarJPsiCandidate::lastCHadron(const Candidate & c)
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
}*/

bool CMGTTbarJPsiCandidate::isLastbottom( const reco::GenParticle& p ){
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


/*bool CMGTTbarJPsiCandidate::isLastcharm( const reco::GenParticle& p ){
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
}*/

bool CMGTTbarJPsiCandidate::isLastParton( const reco::GenParticle& p){

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

const reco::Candidate* CMGTTbarJPsiCandidate::getLast( const reco::Candidate& p ){

   const reco::Candidate* last = 0;
   int id = abs( p.pdgId() );
   unsigned int nDaughters =p.numberOfDaughters();
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

bool CMGTTbarJPsiCandidate::isFromtop( const reco::GenParticle& p){
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

bool CMGTTbarJPsiCandidate::isFrombottom( const reco::GenParticle& p){
  bool out = false;

  string pt = Form("%f", p.pt());
  string pdgid = Form("%i",p.pdgId());
  const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
  while( mother != 0 ){
    string id = Form("%i", mother->pdgId());
    string mopt = Form("%f", mother->pt());
    //cout<<"moid : " <<id<<endl;
    if( abs(mother->pdgId()) == 5 || abs(mother->pdgId()) == 511 || abs(mother->pdgId()) == 521 
        || abs(mother->pdgId()) == 531 || abs(mother->pdgId()) == 541 || abs(mother->pdgId()) == 5122
        || abs(mother->pdgId()) == 5132 || abs(mother->pdgId()) == 5232 || abs(mother->pdgId()) == 5332) {
      out = true;
    }
    mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
  }

  return out;
}

bool CMGTTbarJPsiCandidate::isFromt( const reco::GenParticle& p){
  bool out = false;

  string pt = Form("%f", p.pt());
  string pdgid = Form("%i",p.pdgId());
  const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
  while( mother != 0 ){
    string id = Form("%i", mother->pdgId());
    string mopt = Form("%f", mother->pt());
    if( mother->pdgId() == 6 ) {
      out = true;
    }
    mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
  }

  return out;
}

bool CMGTTbarJPsiCandidate::isFromtbar( const reco::GenParticle& p){
  bool out = false;

  string pt = Form("%f", p.pt());
  string pdgid = Form("%i",p.pdgId());
  const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
  while( mother != 0 ){
    string id = Form("%i", mother->pdgId());
    string mopt = Form("%f", mother->pt());
    if( mother->pdgId() == -6 ) {
      out = true;
    }
    mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
  }

  return out;
}

int CMGTTbarJPsiCandidate::fromWhichTopKind(const reco::GenParticle& p){
  int out = -99;

  //string pt = Form("%f", p.pt());
  //string pdgid = Form("%i",p.pdgId());
  const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
  while( mother != 0 ){
    //string id = Form("%i", mother->pdgId());
    //string mopt = Form("%f", mother->pt());
    if( mother->pdgId() == 6 ) {
      out = 0;
    }
    if( mother->pdgId() == -6 ) {
      out = 1;
    }

    mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
  }

  return out;

}

double CMGTTbarJPsiCandidate::getdthetaTrue( const reco::GenParticle& p){
  double out = 0.0;

  double Jpsitheta = p.theta();
  const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
  while( mother != 0 ){
    if( abs(mother->pdgId()) == 6 ) {
      out = abs(mother->theta()-Jpsitheta);
    }
    mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
  }

  return out;
}

std::pair<double, double> CMGTTbarJPsiCandidate::getJPsidlTrue(const reco::GenParticle& p, const int momID ) {

  double true3Dl = -999.;
  double trueLife = -999.;
 
  if (p.numberOfMothers()>0) {

    TVector3 trueVtx(0.0,0.0,0.0);
    TVector3 trueP(0.0,0.0,0.0);
    TVector3 trueVtxMom(0.0,0.0,0.0);
  
    trueVtx.SetXYZ(p.vertex().x(),p.vertex().y(),p.vertex().z());
    trueP.SetXYZ(p.momentum().x(),p.momentum().y(),p.momentum().z());

    const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
    while( mother != 0 ){
      string id = Form("%i", mother->pdgId());
      if( abs(mother->pdgId()) == momID ) {
        //cout<<"momID : "<<id<<" / "<<momID<<endl;
        trueVtxMom.SetXYZ(mother->vertex().x(),mother->vertex().y(),mother->vertex().z());
        //cout<<"p vx : "<<Form("%f",mother->vertex().x())<<" vy : "<<Form("%f",mother->vertex().y())<<" vz : "<<Form("%f",mother->vertex().z())<<endl;
        break;
      }
      if(abs(mother->pdgId()) == 2212 ) break;
      trueVtxMom.SetXYZ(mother->vertex().x(),mother->vertex().y(),mother->vertex().z());
      mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
    }

    TVector3 vdiff = trueVtx - trueVtxMom;
    //trueLife = vdiff.Perp()*3.09688/trueP.Perp();
    trueLife = vdiff.Perp()*p.mass()/trueP.Perp();
    true3Dl = vdiff.Mag();
    //cout<<"p vx : "<<Form("%f",trueVtxMom.x())<<" vy : "<<Form("%f",trueVtxMom.y())<<" vz : "<<Form("%f",trueVtxMom.z())<<endl;
    //cout<<"JPsi vx : "<<Form("%f",trueVtx.x())<<" vy : "<<Form("%f",trueVtx.y())<<" vz : "<<Form("%f",trueVtx.z())<<endl;
    //cout<<true3Dl<<" / "<<trueLife<<endl;

  }
 
  std::pair<double, double> result = std::make_pair(true3Dl,trueLife);
  return result;

}

double CMGTTbarJPsiCandidate::deltaR( const Candidate& pasObj, const Candidate& proObj ) {

  double pasEta = pasObj.eta();
  double pasPhi = pasObj.phi();

  double proEta = proObj.eta();
  double proPhi = proObj.phi();

  double dRval = reco::deltaR(proEta, proPhi, pasEta, pasPhi);

  return dRval;

}




