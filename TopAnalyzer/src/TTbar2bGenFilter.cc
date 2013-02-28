#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "KoPFA/DataFormats/interface/TTbarCandidate.h"

#include "TTree.h"
#include "TFile.h"
#include <vector>

using namespace edm;
using namespace std;

class TTbar2bGenFilter : public edm::EDFilter
{
public:
  TTbar2bGenFilter(const edm::ParameterSet& pset);
  ~TTbar2bGenFilter() {};

  void beginJob() {};
  bool filter(edm::Event& event, const edm::EventSetup& eventSetup);
  void endJob() {};
  bool isLastQuark(const reco::GenParticle&, const int&);
  bool isFromtop(const reco::GenParticle&);

  string debug;

private:
  bool applyFilter_;

  TH1F* b_status3_daughterid;

  TH1F* b_from_top_pt;
  TH1F* b_from_top_multi;
  TH1F* b_from_top_motherid;
  TH1F* b_from_top_status;

  TH1F* b_from_nontop_pt;
  TH1F* b_from_nontop_multi;
  TH1F* b_from_nontop_motherid;
  TH1F* b_from_nontop_status;

  TH1F* b_multiplicity;

  TH1F* h_multiplicity_bQuarks;
  TH1F* h_multiplicity_bGenJets;

  TH1F* h_multiplicity_bQuarks20;
  TH1F* h_multiplicity_bQuarks20DILVIS;
  TH1F* h_multiplicity_bQuarks20DILVISTTBB;

  TH1F* h_multiplicity_bGenJets20;
  TH1F* h_multiplicity_bGenJets20DILVIS;
  TH1F* h_multiplicity_bGenJets20DILVISTTBB;

  TH1F* h_multiplicity_GenJets;
  TH1F* h_multiplicity_GenJets10;
  TH1F* h_multiplicity_GenJets15;
  TH1F* h_multiplicity_GenJets20;
  TH1F* h_multiplicity_GenJets25;
  TH1F* h_multiplicity_GenJets30;

  TH1F* h_multiplicity_GenJetsDIL;
  TH1F* h_multiplicity_GenJets10DIL;
  TH1F* h_multiplicity_GenJets15DIL;
  TH1F* h_multiplicity_GenJets20DIL;
  TH1F* h_multiplicity_GenJets25DIL;
  TH1F* h_multiplicity_GenJets30DIL;

  TH1F* h_multiplicity_GenJetsDILVIS;
  TH1F* h_multiplicity_GenJets10DILVIS;
  TH1F* h_multiplicity_GenJets15DILVIS;
  TH1F* h_multiplicity_GenJets20DILVIS;
  TH1F* h_multiplicity_GenJets25DILVIS;
  TH1F* h_multiplicity_GenJets30DILVIS;

  TH1F* h_multiplicity_GenJetsDILVISTTBB;
  TH1F* h_multiplicity_GenJets10DILVISTTBB;
  TH1F* h_multiplicity_GenJets15DILVISTTBB;
  TH1F* h_multiplicity_GenJets20DILVISTTBB;
  TH1F* h_multiplicity_GenJets25DILVISTTBB;
  TH1F* h_multiplicity_GenJets30DILVISTTBB;

  TH1F* h_multiplicity_GenJetsDILVISTTCC;
  TH1F* h_multiplicity_GenJets10DILVISTTCC;
  TH1F* h_multiplicity_GenJets15DILVISTTCC;
  TH1F* h_multiplicity_GenJets20DILVISTTCC;
  TH1F* h_multiplicity_GenJets25DILVISTTCC;
  TH1F* h_multiplicity_GenJets30DILVISTTCC;


};

TTbar2bGenFilter::TTbar2bGenFilter(const edm::ParameterSet& pset)
{
  applyFilter_= pset.getUntrackedParameter<bool>("applyFilter",true);

  edm::Service<TFileService> fs;

  b_from_top_pt  = fs->make<TH1F>( "b_from_top_pt"  , "p_{T}", 100,  0., 150. );
  b_from_top_multi  = fs->make<TH1F>( "b_from_top_multi"  , "Multiplicity", 10,  0, 10 );
  b_from_top_motherid  = fs->make<TH1F>( "b_from_top_motherid"  , "Mother PdgId", 3000,  0, 3000 );
  b_from_top_status  = fs->make<TH1F>( "b_from_top_status"  , "status", 10,  0, 10 );

  b_from_nontop_pt  = fs->make<TH1F>( "b_from_nontop_pt"  , "p_{T}", 100,  0., 150. );
  b_from_nontop_multi  = fs->make<TH1F>( "b_from_nontop_multi"  , "Multiplicity", 10,  0, 10 );
  b_from_nontop_motherid  = fs->make<TH1F>( "b_from_nontop_motherid"  , "Mother PdgId", 3000,  0, 3000 );
  b_from_nontop_status  = fs->make<TH1F>( "b_from_nontop_status"  , "status", 10,  0, 10 );

  b_multiplicity  = fs->make<TH1F>( "b_multiplicity"  , "Multiplicity", 10,  0, 10 );
  
  h_multiplicity_bQuarks  = fs->make<TH1F>( "h_multiplicity_bQuarks"  , "Multiplicity", 10,  0, 10 );
  h_multiplicity_bGenJets  = fs->make<TH1F>( "h_multiplicity_bGenJets"  , "Multiplicity", 10,  0, 10 );

  h_multiplicity_bQuarks20  = fs->make<TH1F>( "h_multiplicity_bQuarks20"  , "Multiplicity", 10,  0, 10 );
  h_multiplicity_bQuarks20DILVIS  = fs->make<TH1F>( "h_multiplicity_bQuarks20DILVIS"  , "Multiplicity", 10,  0, 10 );
  h_multiplicity_bQuarks20DILVISTTBB  = fs->make<TH1F>( "h_multiplicity_bQuarks20DILVISTTBB"  , "Multiplicity", 10,  0, 10 );

  h_multiplicity_bGenJets20  = fs->make<TH1F>( "h_multiplicity_bGenJets20"  , "Multiplicity", 10,  0, 10 );
  h_multiplicity_bGenJets20DILVIS  = fs->make<TH1F>( "h_multiplicity_bGenJets20DILVIS"  , "Multiplicity", 10,  0, 10 );
  h_multiplicity_bGenJets20DILVISTTBB  = fs->make<TH1F>( "h_multiplicity_bGenJets20DILVISTTBB"  , "Multiplicity", 10,  0, 10 );

  h_multiplicity_GenJets  = fs->make<TH1F>( "h_multiplicity_GenJets"  , "Multiplicity", 30,  0, 30 );
  h_multiplicity_GenJets10  = fs->make<TH1F>( "h_multiplicity_GenJets10"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets15  = fs->make<TH1F>( "h_multiplicity_GenJets15"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets20  = fs->make<TH1F>( "h_multiplicity_GenJets20"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets25  = fs->make<TH1F>( "h_multiplicity_GenJets25"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets30  = fs->make<TH1F>( "h_multiplicity_GenJets30"  , "Multiplicity", 12,  0, 12 );
  
  h_multiplicity_GenJetsDIL  = fs->make<TH1F>( "h_multiplicity_GenJetsDIL"  , "Multiplicity", 30,  0, 30 );
  h_multiplicity_GenJets10DIL  = fs->make<TH1F>( "h_multiplicity_GenJets10DIL"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets15DIL  = fs->make<TH1F>( "h_multiplicity_GenJets15DIL"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets20DIL  = fs->make<TH1F>( "h_multiplicity_GenJets20DIL"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets25DIL  = fs->make<TH1F>( "h_multiplicity_GenJets25DIL"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets30DIL  = fs->make<TH1F>( "h_multiplicity_GenJets30DIL"  , "Multiplicity", 12,  0, 12 );

  h_multiplicity_GenJetsDILVIS  = fs->make<TH1F>( "h_multiplicity_GenJetsDILVIS"  , "Multiplicity", 30,  0, 30 );
  h_multiplicity_GenJets10DILVIS  = fs->make<TH1F>( "h_multiplicity_GenJets10DILVIS"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets15DILVIS  = fs->make<TH1F>( "h_multiplicity_GenJets15DILVIS"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets20DILVIS  = fs->make<TH1F>( "h_multiplicity_GenJets20DILVIS"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets25DILVIS  = fs->make<TH1F>( "h_multiplicity_GenJets25DILVIS"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets30DILVIS  = fs->make<TH1F>( "h_multiplicity_GenJets30DILVIS"  , "Multiplicity", 12,  0, 12 );

  h_multiplicity_GenJetsDILVISTTBB  = fs->make<TH1F>( "h_multiplicity_GenJetsDILVISTTBB"  , "Multiplicity", 30,  0, 30 );
  h_multiplicity_GenJets10DILVISTTBB  = fs->make<TH1F>( "h_multiplicity_GenJets10DILVISTTBB"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets15DILVISTTBB  = fs->make<TH1F>( "h_multiplicity_GenJets15DILVISTTBB"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets20DILVISTTBB  = fs->make<TH1F>( "h_multiplicity_GenJets20DILVISTTBB"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets25DILVISTTBB  = fs->make<TH1F>( "h_multiplicity_GenJets25DILVISTTBB"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets30DILVISTTBB  = fs->make<TH1F>( "h_multiplicity_GenJets30DILVISTTBB"  , "Multiplicity", 12,  0, 12 );

  h_multiplicity_GenJetsDILVISTTCC  = fs->make<TH1F>( "h_multiplicity_GenJetsDILVISTTCC"  , "Multiplicity", 30,  0, 30 );
  h_multiplicity_GenJets10DILVISTTCC  = fs->make<TH1F>( "h_multiplicity_GenJets10DILVISTTCC"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets15DILVISTTCC  = fs->make<TH1F>( "h_multiplicity_GenJets15DILVISTTCC"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets20DILVISTTCC  = fs->make<TH1F>( "h_multiplicity_GenJets20DILVISTTCC"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets25DILVISTTCC  = fs->make<TH1F>( "h_multiplicity_GenJets25DILVISTTCC"  , "Multiplicity", 12,  0, 12 );
  h_multiplicity_GenJets30DILVISTTCC  = fs->make<TH1F>( "h_multiplicity_GenJets30DILVISTTCC"  , "Multiplicity", 12,  0, 12 );

}

bool TTbar2bGenFilter::filter(edm::Event& iEvent, const edm::EventSetup& eventSetup)
{

  const bool isRealData = iEvent.isRealData();

  if (!applyFilter_ || isRealData )
    return true;

  bool accepted = false;

  using namespace std;
  using namespace edm;
  using namespace reco;
  debug = "";
  debug += "---------EVENT start---------\n" ;

  edm::Handle<reco::GenJetCollection> genJets_;
  iEvent.getByLabel("ak5GenJets",genJets_);

  const reco::GenParticleCollection* myGenParticles = 0;

  Handle<reco::GenParticleCollection> genEvt;
  bool genPart = iEvent.getByLabel("genParticles",genEvt);
  if ( genPart ) myGenParticles = &(*genEvt);
  if ( !myGenParticles ) return false;

  unsigned int nParticles = myGenParticles->size();

  int nb_from_top = 0;
  int nb_from_nontop = 0;
  int nb = 0;

  for ( unsigned int ip=0; ip<nParticles; ++ip ) { 

    const reco::GenParticle& p = (*myGenParticles)[ip];
   
    if ( abs(p.pdgId()) != 5 ) continue;
    bool isLast = isLastQuark(p, 5);
    if (isLast != true) continue;
 
    int status = p.status();

    const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
    int motherAbsPdgId = abs(mother->pdgId());

    bool isfromtop = isFromtop(p);

    if( !isfromtop ) {  
      b_from_nontop_status->Fill(status);
      b_from_nontop_motherid->Fill(motherAbsPdgId);
      b_from_nontop_pt->Fill(p.pt());
      nb_from_nontop++ ;
    }else{
      b_from_top_status->Fill(status);
      b_from_top_motherid->Fill(motherAbsPdgId);
      b_from_top_pt->Fill(p.pt());
      nb_from_top++  ;
    }

    nb++;
  }

  b_multiplicity->Fill(nb);


  //gen information
  Ko::TTbarCandidate ttbarGenLevel;

  if(genJets_.isValid()){
    const reco::GenJetCollection* myGenJets = 0;
    myGenJets = &(*genJets_);

    ttbarGenLevel.building(myGenJets, myGenParticles);

    int nGenJet = 0;
    int nGenJet10 = 0;
    int nGenJet15 = 0;
    int nGenJet20 = 0;
    int nGenJet25 = 0;
    int nGenJet30 = 0;

    int nGenJetDIL = 0;
    int nGenJet10DIL = 0;
    int nGenJet15DIL = 0;
    int nGenJet20DIL = 0;
    int nGenJet25DIL = 0;
    int nGenJet30DIL = 0;

    int nGenJetDILVIS = 0;
    int nGenJet10DILVIS = 0;
    int nGenJet15DILVIS = 0;
    int nGenJet20DILVIS = 0;
    int nGenJet25DILVIS = 0;
    int nGenJet30DILVIS = 0;

    int nGenJetDILVISTTBB = 0;
    int nGenJet10DILVISTTBB = 0;
    int nGenJet15DILVISTTBB = 0;
    int nGenJet20DILVISTTBB = 0;
    int nGenJet25DILVISTTBB = 0;
    int nGenJet30DILVISTTBB = 0;

    bool dil = ttbarGenLevel.diLeptonic(1) == 1 ;
    bool vis = ttbarGenLevel.lepton1().pt() > 20 && abs(ttbarGenLevel.lepton1().eta()) < 2.4 && ttbarGenLevel.lepton2().pt() > 20 && abs(ttbarGenLevel.lepton2().eta()) < 2.4 ;
    bool ttbb = ttbarGenLevel.NbJets15NoTop() >= 2;
    bool ttcc = ttbarGenLevel.NcJets15() >= 2;

    h_multiplicity_bQuarks->Fill( ttbarGenLevel.NbQuarks() ) ;
    h_multiplicity_bQuarks20->Fill( ttbarGenLevel.NbQuarks20() ) ;
    if( dil + vis ) h_multiplicity_bQuarks20DILVIS->Fill( ttbarGenLevel.NbQuarks20() );
    if( dil + vis && ttbb) h_multiplicity_bQuarks20DILVISTTBB->Fill( ttbarGenLevel.NbQuarks20() );
    h_multiplicity_bGenJets->Fill( ttbarGenLevel.NbJets() );
    h_multiplicity_bGenJets20->Fill( ttbarGenLevel.NbJets20() );
    if( dil + vis ) h_multiplicity_bGenJets20DILVIS->Fill( ttbarGenLevel.NbJets20() );
    if( dil + vis && ttbb ) h_multiplicity_bGenJets20DILVISTTBB->Fill( ttbarGenLevel.NbJets20() );


/*
    for ( size_t i = 0;  i < genJets_->size() ; i++ ){
      const reco::GenJet& genJet = genJets_->at(i);
  
      nGenJet++;
      if(dil) nGenJetDIL++;
      if(dil && vis) nGenJetDILVIS++;
      if(dil && vis && ttbb) nGenJetDILVISTTBB++;
       
      if( genJet.pt() > 10 && abs(genJet.eta()) < 2.5 ) nGenJet10++ ;
      if( genJet.pt() > 15 && abs(genJet.eta()) < 2.5 ) nGenJet15++ ;
      if( genJet.pt() > 20 && abs(genJet.eta()) < 2.5 ) nGenJet20++ ;
      if( genJet.pt() > 25 && abs(genJet.eta()) < 2.5 ) nGenJet25++ ;
      if( genJet.pt() > 30 && abs(genJet.eta()) < 2.5 ) nGenJet30++ ;

      if( genJet.pt() > 10 && abs(genJet.eta()) < 2.5 && dil ) nGenJet10DIL++ ;
      if( genJet.pt() > 15 && abs(genJet.eta()) < 2.5 && dil ) nGenJet15DIL++ ;
      if( genJet.pt() > 20 && abs(genJet.eta()) < 2.5 && dil ) nGenJet20DIL++ ;
      if( genJet.pt() > 25 && abs(genJet.eta()) < 2.5 && dil ) nGenJet25DIL++ ;
      if( genJet.pt() > 30 && abs(genJet.eta()) < 2.5 && dil ) nGenJet30DIL++ ;
   
      if( genJet.pt() > 10 && abs(genJet.eta()) < 2.5 && dil && vis ) nGenJet10DILVIS++ ;
      if( genJet.pt() > 15 && abs(genJet.eta()) < 2.5 && dil && vis ) nGenJet15DILVIS++ ;
      if( genJet.pt() > 20 && abs(genJet.eta()) < 2.5 && dil && vis ) nGenJet20DILVIS++ ;
      if( genJet.pt() > 25 && abs(genJet.eta()) < 2.5 && dil && vis ) nGenJet25DILVIS++ ;
      if( genJet.pt() > 30 && abs(genJet.eta()) < 2.5 && dil && vis ) nGenJet30DILVIS++ ;

      if( genJet.pt() > 10 && abs(genJet.eta()) < 2.5 && dil && vis && ttbb) nGenJet10DILVISTTBB++ ;
      if( genJet.pt() > 15 && abs(genJet.eta()) < 2.5 && dil && vis && ttbb) nGenJet15DILVISTTBB++ ;
      if( genJet.pt() > 20 && abs(genJet.eta()) < 2.5 && dil && vis && ttbb) nGenJet20DILVISTTBB++ ;
      if( genJet.pt() > 25 && abs(genJet.eta()) < 2.5 && dil && vis && ttbb) nGenJet25DILVISTTBB++ ;
      if( genJet.pt() > 30 && abs(genJet.eta()) < 2.5 && dil && vis && ttbb) nGenJet30DILVISTTBB++ ;

    }
*/

    h_multiplicity_GenJets->Fill( ttbarGenLevel.NJets() );
    h_multiplicity_GenJets10->Fill( ttbarGenLevel.NJets10() );
    h_multiplicity_GenJets15->Fill( ttbarGenLevel.NJets15() );
    h_multiplicity_GenJets20->Fill( ttbarGenLevel.NJets20() );
    h_multiplicity_GenJets25->Fill( ttbarGenLevel.NJets25() );
    h_multiplicity_GenJets30->Fill( ttbarGenLevel.NJets30() );

    if( dil ){
      h_multiplicity_GenJetsDIL->Fill( ttbarGenLevel.NJets() );
      h_multiplicity_GenJets10DIL->Fill( ttbarGenLevel.NJets10() );
      h_multiplicity_GenJets15DIL->Fill( ttbarGenLevel.NJets15() );
      h_multiplicity_GenJets20DIL->Fill( ttbarGenLevel.NJets20() );
      h_multiplicity_GenJets25DIL->Fill( ttbarGenLevel.NJets25() );
      h_multiplicity_GenJets30DIL->Fill( ttbarGenLevel.NJets30() );
    }

   if( dil && vis ){
      h_multiplicity_GenJetsDILVIS->Fill( ttbarGenLevel.NJets() );
      h_multiplicity_GenJets10DILVIS->Fill( ttbarGenLevel.NJets10() );
      h_multiplicity_GenJets15DILVIS->Fill( ttbarGenLevel.NJets15() );
      h_multiplicity_GenJets20DILVIS->Fill( ttbarGenLevel.NJets20() );
      h_multiplicity_GenJets25DILVIS->Fill( ttbarGenLevel.NJets25() );
      h_multiplicity_GenJets30DILVIS->Fill( ttbarGenLevel.NJets30() );
    }

    if( dil && vis && ttbb ){
      h_multiplicity_GenJetsDILVISTTBB->Fill( ttbarGenLevel.NJets() );
      h_multiplicity_GenJets10DILVISTTBB->Fill( ttbarGenLevel.NJets10() );
      h_multiplicity_GenJets15DILVISTTBB->Fill( ttbarGenLevel.NJets15() );
      h_multiplicity_GenJets20DILVISTTBB->Fill( ttbarGenLevel.NJets20() );
      h_multiplicity_GenJets25DILVISTTBB->Fill( ttbarGenLevel.NJets25() );
      h_multiplicity_GenJets30DILVISTTBB->Fill( ttbarGenLevel.NJets30() );
    }

    if( dil && vis && ttcc ){
      h_multiplicity_GenJetsDILVISTTCC->Fill( ttbarGenLevel.NJets() );
      h_multiplicity_GenJets10DILVISTTCC->Fill( ttbarGenLevel.NJets10() );
      h_multiplicity_GenJets15DILVISTTCC->Fill( ttbarGenLevel.NJets15() );
      h_multiplicity_GenJets20DILVISTTCC->Fill( ttbarGenLevel.NJets20() );
      h_multiplicity_GenJets25DILVISTTCC->Fill( ttbarGenLevel.NJets25() );
      h_multiplicity_GenJets30DILVISTTCC->Fill( ttbarGenLevel.NJets30() );
    }

  }

  if( nb_from_top <=2 && nb_from_nontop <=0){
    accepted = false;
  }
  else {
    //more than 2 b-quarks are from top. But it will be considered as tt+bb.
    accepted = true;
  }

  b_from_top_multi->Fill(nb_from_top);
  b_from_nontop_multi->Fill(nb_from_nontop);

  return accepted;
}

bool TTbar2bGenFilter::isLastQuark( const reco::GenParticle& p, const int & pdgId ){
   bool out = true;

   unsigned int nDaughters = p.numberOfDaughters();
   for ( unsigned iDaughter=0; iDaughter<nDaughters; ++iDaughter ) {
     const reco::Candidate* daugh = p.daughter(iDaughter);
     if( abs(daugh->pdgId()) == pdgId) {
       out = false;
       break;
     }
   }

   return out;
}

bool TTbar2bGenFilter::isFromtop( const reco::GenParticle& p){
  bool out = false;
  string tmp = "";
  tmp += "Let's study this b quark \n";
  string pt = Form("%f", p.pt());
  string pdgid = Form("%i",p.pdgId());
  tmp += "pt = " + pt + " id= " + pdgid + "\n";
  const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
  while( mother != 0 ){
    string id = Form("%i", mother->pdgId());
    string mopt = Form("%f", mother->pt());
    tmp += "mother pdgid= " + id + " pt= " + mopt +"\n";
    if( abs(mother->pdgId()) == 6 ) { 
      out = true;
    }
    mother = dynamic_cast<const reco::GenParticle*>(mother->mother());
  }
 
  if(out) debug += tmp; 
  return out;
}

DEFINE_FWK_MODULE(TTbar2bGenFilter);

