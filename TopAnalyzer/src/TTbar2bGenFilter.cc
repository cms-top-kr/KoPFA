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

  void beginJob();
  bool filter(edm::Event& event, const edm::EventSetup& eventSetup);
  void endJob() {};
  bool isLastQuark(const reco::GenParticle&, const int&);
  bool isFromtop(const reco::GenParticle&);

  string debug;

private:
  bool applyFilter_;
  edm::InputTag genJetsLabel_;

  TTree* tree;

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

  TH1F* h_nEvents;
  TH1F* h_nEvents_parton;

  TH1F* h_nEvents_inclusive;
  TH1F* h_nEvents_parton_inclusive;

  std::vector<vallot::TTbarCandidate>* ttbarGen;

};

TTbar2bGenFilter::TTbar2bGenFilter(const edm::ParameterSet& pset)
{
  applyFilter_= pset.getUntrackedParameter<bool>("applyFilter",true);
  genJetsLabel_= pset.getParameter<edm::InputTag>("genJetsLabel");

  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("tree", "Tree for Top quark study");

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

  h_nEvents = fs->make<TH1F>( "h_nEvents"  , "h_nEvents", 6,  0, 6 );
  h_nEvents_parton = fs->make<TH1F>( "h_nEvents_parton"  , "h_nEvents_parton", 6,  0, 6 );

  h_nEvents_inclusive = fs->make<TH1F>( "h_nEvents_inclusive"  , "h_nEvents", 6,  0, 6 );
  h_nEvents_parton_inclusive = fs->make<TH1F>( "h_nEvents_parton_inclusive"  , "h_nEvents_parton", 6,  0, 6 );

  ttbarGen = new std::vector<vallot::TTbarCandidate>();
}

void TTbar2bGenFilter::beginJob(){
  tree->Branch("ttbarGen","std::vector<vallot::TTbarCandidate>", &ttbarGen);
}

bool TTbar2bGenFilter::filter(edm::Event& iEvent, const edm::EventSetup& eventSetup)
{

  const bool isRealData = iEvent.isRealData();

  if (!applyFilter_ || isRealData )
    return true;

  ttbarGen->clear();

  bool accepted = false;

  using namespace std;
  using namespace edm;
  using namespace reco;
  debug = "";
  debug += "---------EVENT start---------\n" ;

  edm::Handle<reco::GenJetCollection> genJets_;
  iEvent.getByLabel( genJetsLabel_, genJets_);

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
  vallot::TTbarCandidate ttbarGenLevel;

  if(genJets_.isValid()){
    const reco::GenJetCollection* myGenJets = 0;
    myGenJets = &(*genJets_);

    ttbarGenLevel.building(myGenJets, myGenParticles);

    ttbarGen->push_back(ttbarGenLevel);

    bool dil = ttbarGenLevel.diLeptonic() == 1 ;
    bool vis = ttbarGenLevel.lepton1().pt() > 20 && abs(ttbarGenLevel.lepton1().eta()) < 2.4 && ttbarGenLevel.lepton2().pt() > 20 && abs(ttbarGenLevel.lepton2().eta()) < 2.4 && ttbarGenLevel.NbJets20() >= 2;
    bool nbjets2 = ttbarGenLevel.NbJets20() >= 2;
    bool njets4 = ttbarGenLevel.NJets20() >= 4;
    bool ttbb = ttbarGenLevel.NbJets20() >= 4;
    bool ttcc = ttbarGenLevel.NcJets20() >= 2;

    bool nbpartons2 = ttbarGenLevel.NbQuarks20() >= 2;
    bool vis_parton = ttbarGenLevel.lepton1().pt() > 20 && abs(ttbarGenLevel.lepton1().eta()) < 2.4 && ttbarGenLevel.lepton2().pt() > 20 && abs(ttbarGenLevel.lepton2().eta()) < 2.4 && ttbarGenLevel.NbQuarks20() >= 2;
    bool ttbb_parton = ttbarGenLevel.NbQuarks20() >= 4;

    h_multiplicity_bQuarks->Fill( ttbarGenLevel.NbQuarks() ) ;
    h_multiplicity_bQuarks20->Fill( ttbarGenLevel.NbQuarks20() ) ;
    if( dil && vis ) h_multiplicity_bQuarks20DILVIS->Fill( ttbarGenLevel.NbQuarks20() );
    if( dil && vis && ttbb) h_multiplicity_bQuarks20DILVISTTBB->Fill( ttbarGenLevel.NbQuarks20() );
    h_multiplicity_bGenJets->Fill( ttbarGenLevel.NbJets() );
    h_multiplicity_bGenJets20->Fill( ttbarGenLevel.NbJets20() );
    if( dil && vis ) h_multiplicity_bGenJets20DILVIS->Fill( ttbarGenLevel.NbJets20() );
    if( dil && vis && ttbb ) h_multiplicity_bGenJets20DILVISTTBB->Fill( ttbarGenLevel.NbJets20() );

    h_nEvents->Fill(0);
    if( dil ) h_nEvents->Fill(1);
    if( dil && vis ) h_nEvents->Fill(2);
    if( dil && vis && njets4  ) h_nEvents->Fill(3);
    if( dil && vis && njets4 && ttbb  ) h_nEvents->Fill(4);
    if( dil && vis && njets4 && !ttbb && ttcc  ) h_nEvents->Fill(5);

    if( njets4 && nbjets2 ) h_nEvents_inclusive->Fill(0);
    if( njets4 && nbjets2 && ttbb  ) h_nEvents_inclusive->Fill(1);
    if( dil && nbjets2 && njets4  ) h_nEvents_inclusive->Fill(2);
    if( dil && nbjets2 && njets4 && ttbb  ) h_nEvents_inclusive->Fill(3);
    if( vis && njets4  ) h_nEvents_inclusive->Fill(4);
    if( vis && njets4 && ttbb  ) h_nEvents_inclusive->Fill(5);

    h_nEvents_parton->Fill(0);
    if( dil ) h_nEvents_parton->Fill(1);
    if( dil && vis_parton ) h_nEvents_parton->Fill(2);
    if( dil && vis_parton && njets4  ) h_nEvents_parton->Fill(3);
    if( dil && vis_parton && njets4 && ttbb_parton  ) h_nEvents_parton->Fill(4);
    if( dil && vis_parton && njets4 && !ttbb_parton && ttcc  ) h_nEvents_parton->Fill(5);    

    if( njets4 && nbpartons2 ) h_nEvents_parton_inclusive->Fill(0);
    if( njets4 && nbpartons2 && ttbb_parton  ) h_nEvents_parton_inclusive->Fill(1);
    if( dil && nbpartons2 && njets4  ) h_nEvents_parton_inclusive->Fill(2);
    if( dil && nbpartons2 && njets4 && ttbb_parton  ) h_nEvents_parton_inclusive->Fill(3);
    if( vis_parton && njets4  ) h_nEvents_parton_inclusive->Fill(4);
    if( vis_parton && njets4 && ttbb_parton  ) h_nEvents_parton_inclusive->Fill(5);
 
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

  tree->Fill();

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

