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
  bool isLastbottom(const reco::GenParticle&);
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

}

bool TTbar2bGenFilter::filter(edm::Event& iEvent, const edm::EventSetup& eventSetup)
{

  bool accepted = false;

  using namespace std;
  using namespace edm;
  using namespace reco;
  debug = "";
  debug += "---------EVENT start---------\n" ;
  const reco::GenParticleCollection* myGenParticles = 0;

  Handle<reco::GenParticleCollection> genEvt;
  bool genPart = iEvent.getByLabel("genParticles",genEvt);
  if ( genPart ) myGenParticles = &(*genEvt);
  if ( !myGenParticles ) return false;

  unsigned int nParticles = myGenParticles->size();

  int nb_from_top = 0;
  int nb_from_nontop = 0;

  for ( unsigned int ip=0; ip<nParticles; ++ip ) { 

    const reco::GenParticle& p = (*myGenParticles)[ip];
   
    if ( abs(p.pdgId()) != 5 ) continue;
    bool isLast = isLastbottom(p);
    if (isLast != true) continue;
 
    int status = p.status();

    const reco::GenParticle* mother = dynamic_cast<const reco::GenParticle*>(p.mother());
    int motherAbsPdgId = abs(mother->pdgId());

    bool isfromtop = isFromtop(p);

    if( !isfromtop ) {  
      accepted = true;
      b_from_nontop_status->Fill(status);
      b_from_nontop_motherid->Fill(motherAbsPdgId);
      b_from_nontop_pt->Fill(p.pt());
      nb_from_nontop++ ;
    }else{
      accepted = false;
      b_from_top_status->Fill(status);
      b_from_top_motherid->Fill(motherAbsPdgId);
      b_from_top_pt->Fill(p.pt());
      nb_from_top++  ;
    }
  }

  if( nb_from_top  > 2 ) {
    //cout << debug << endl;
  }
  b_from_top_multi->Fill(nb_from_top);
  b_from_nontop_multi->Fill(nb_from_nontop);

  if (!applyFilter_)
    return true;

  return accepted;
}

bool TTbar2bGenFilter::isLastbottom( const reco::GenParticle& p ){
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

