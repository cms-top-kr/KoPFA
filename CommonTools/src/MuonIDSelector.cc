#include "KoPFA/CommonTools/interface/MuonIDSelector.h"

#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"

#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include <vector>
#include <iostream>

#include "Math/VectorUtil.h"
#include "TMath.h"

using namespace std;
using namespace reco;

MuonIDSelector::MuonIDSelector()
  : verbose_(false){
  push_back("VBTF",0);
  push_back("QTF",0);
  push_back("TOPDIL",0);
  push_back("isGlobalMuon",0);
  push_back("isTrackerMuon",0);
  push_back("nMatches",0);
  push_back("globalNormChi2",0.);
  push_back("muonHits",0);
  push_back("trackerHits",0);
  push_back("pixelHits",0);
  push_back("pixelLayersWithHits",0);
  push_back("trackNormChi2",0.);
  push_back("dxy",0.);
  push_back("dz",0.);
  push_back("relIso",0.); 
  push_back("tmLastStationAngTight",0);
  push_back("pt",0);
  push_back("eta",0);

}


void MuonIDSelector::initialize( const edm::ParameterSet& ps ) {

  initialize(ps.getParameter< int >("VBTF"),  
	     ps.getParameter< int >("QTF"),  
             ps.getParameter< int >("TOPDIL"),
	     ps.getParameter< int >("isGlobalMuon"),
	     ps.getParameter< int >("isTrackerMuon"),
	     ps.getParameter< int >("nMatches"),
	     ps.getParameter< int >("tmLastStationAngTight"),
	     ps.getParameter< int >("muonHits"),
	     ps.getParameter< double >("globalNormChi2"),
	     ps.getParameter< int >("trackerHits"),
	     ps.getParameter< int >("pixelHits"),
	     ps.getParameter< int >("pixelLayersWithHits"),
	     ps.getParameter< double >("trackNormChi2"),
	     ps.getParameter< double >("dxy"),
	     ps.getParameter< double >("dz"),
	     ps.getParameter< double >("relIso"),
	     ps.getParameter< double >("pt") ,
	     ps.getParameter< double >("eta") 
	     );


  verbose_ = ps.getUntrackedParameter<bool>("verbose", false);
  calcDispFromGlobalTrack_ = ps.getUntrackedParameter<bool>("calcDispFromGlobalTrack", false);

  if ( ps.exists("cutsToIgnore") )
    setIgnoredCuts( ps.getParameter<std::vector<std::string> >("cutsToIgnore") );

}

void MuonIDSelector::initialize(int VBTF,
				 int QTF,
                                 int TOPDIL,
				 int isGlobalMuon,
				 int isTrackerMuon,
				 int nMatches,
				 int tmLastStationAngTight,
				 int muonHits,	
				 double globalNormChi2,
				 int trackerHits,
				 int pixelHits,
				 int pixelLayersWithHits,
				 double trackNormChi2,				     
				 double dxy,	
				 double dz,	
				 double relIso,
				 double pt,
				 double eta){
  set("VBTF",VBTF);
  set("QTF",QTF);
  set("TOPDIL",TOPDIL);
  set("isGlobalMuon",isGlobalMuon);
  set("isTrackerMuon",isTrackerMuon);
  set("nMatches",nMatches);
  set("tmLastStationAngTight",tmLastStationAngTight);
  set("muonHits",muonHits);
  set("globalNormChi2",globalNormChi2);
  set("trackerHits",trackerHits);
  set("pixelHits",pixelHits);
  set("pixelLayersWithHits",pixelLayersWithHits);
  set("trackNormChi2",trackNormChi2);
  set("dxy",dxy);	
  set("dz",dz);	
  set("relIso",relIso);
  set("pt",pt);
  set("eta",eta);
}

bool MuonIDSelector::operator()( const pat::Muon & muon, pat::strbitset & ret ) {
  return muIDSelection(muon, ret);
}

bool MuonIDSelector::operator()( const pat::Muon & muon, const edm::Handle<reco::BeamSpot>& beamspot, pat::strbitset & ret ) {
  return operator()(muon,beamspot->position(),ret);
}

bool MuonIDSelector::operator()( const pat::Muon & muon, const Point& position, pat::strbitset & ret ) {

  bool passedBeamSpotSelection = beamSpotSelection( muon, position, ret);
  bool passedMuIDSelection = muIDSelection( muon, ret ); 
  return passedMuIDSelection && passedBeamSpotSelection;
}


bool MuonIDSelector::muIDSelection( const pat::Muon& muon, 
				pat::strbitset & ret)  {    

  if(verbose_) 
    cout<<"Selecting Pat muon : "<<muon.pt()<<endl;
  
  int isGlobal = (int)muon.isGlobalMuon();
  int isTracker = (int)muon.isTrackerMuon();
  int nMatches = (int)muon.numberOfMatches();
  int tmLastStationAngTight = (int)muon::isGoodMuon(muon,muon::TMLastStationAngTight);

  // from global track
  int muonHits = 0.;
  double globalNormChi2 = 9999.;

  // from tracker track
  int trackerHits = 0.;
  int pixelHits = 0;
  int pixelLayersWithHits = 0;
  double trackNormChi2 = 9999.;
  

  


  if(muon.isGlobalMuon()){
    //const reco::TrackRef& combinedMuon = muon.combinedMuon();    
    const reco::TrackRef& combinedMuon = muon.globalTrack();        
    globalNormChi2 = combinedMuon->normalizedChi2();
    muonHits = combinedMuon->hitPattern().numberOfValidMuonHits();
    trackerHits = combinedMuon->hitPattern().numberOfValidTrackerHits();
    pixelHits = combinedMuon->hitPattern().numberOfValidPixelHits();
    pixelLayersWithHits = combinedMuon->hitPattern().pixelLayersWithMeasurement();
    trackNormChi2 = combinedMuon->normalizedChi2();

  }

  // commented out until tracks are embedded into pat muons
  /*
  if(!muon.track()){
  }
  else{
    const reco::TrackRef& track = muon.track();        
    trackerHits = track->hitPattern().numberOfValidTrackerHits();
    pixelHits = track->hitPattern().numberOfValidPixelHits();
    pixelLayersWithHits = track->hitPattern().pixelLayersWithMeasurement();
    trackNormChi2 = track->normalizedChi2();
  }
  */


  if(ignoreCut("isGlobalMuon") || isGlobal == cut("isGlobalMuon", int() ) )  
    passCut( ret, "isGlobalMuon");  
 
  if(ignoreCut("isTrackerMuon") || isTracker == cut("isTrackerMuon", int() ))  
    passCut( ret, "isTrackerMuon");  
 
  if(ignoreCut("nMatches") ||   nMatches >= cut("nMatches", int() )) 
    passCut( ret, "nMatches");  

  if(ignoreCut("tmLastStationAngTight") ||   tmLastStationAngTight == cut("tmLastStationAngTight", int() )) 
    passCut( ret, "tmLastStationAngTight");  

  if(ignoreCut("muonHits") || muonHits > cut("muonHits", int() ))
    passCut( ret, "muonHits");

  if(ignoreCut("globalNormChi2") || globalNormChi2 <= cut("globalNormChi2", double() )) 
    passCut( ret, "globalNormChi2");
  
  if(ignoreCut("trackerHits") || trackerHits >= cut("trackerHits", int() ))
    passCut( ret, "trackerHits");

  if(ignoreCut("pixelHits") || pixelHits > cut("pixelHits", int() ))
    passCut( ret, "pixelHits");

  if(ignoreCut("pixelLayersWithHits") || pixelLayersWithHits > cut("pixelLayersWithHits", int() ))
    passCut( ret, "pixelLayersWithHits");

  if(ignoreCut("trackNormChi2") || trackNormChi2 <= cut("trackNormChi2", double() )) 
    passCut( ret, "trackNormChi2");
  

  double sumPtR03 = muon.isolationR03().sumPt;
  double emEtR03 = muon.isolationR03().emEt;
  double hadEtR03 = muon.isolationR03().hadEt;
  
  double relIso = (sumPtR03 + emEtR03 + hadEtR03)/muon.pt();
  
  if(ignoreCut("relIso") || relIso< cut("relIso", double() ) )
    passCut( ret, "relIso");


  // No isolation included in VBTF cuts
  if(ignoreCut("VBTF") || (
			   isGlobal == cut("isGlobalMuon", int() )  &&
			   isTracker == cut("isTrackerMuon", int() ) &&
			   nMatches >= cut("nMatches", int() ) &&
			   trackerHits >= cut("trackerHits", int() ) &&
			   pixelHits > cut("pixelHits", int() ) &&
			   globalNormChi2 <= cut("globalNormChi2", double() ) &&
			   muonHits > cut("muonHits", int() ) 
			   )
     )
    passCut( ret, "VBTF");

  // To be filled in with the correct QTF cuts
  if(ignoreCut("QTF") 
     || (
	 isTracker == cut("isTrackerMuon", int() ) &&
	 tmLastStationAngTight == cut("tmLastStationAngTight", int() ) &&
	 trackerHits >= cut("trackerHits", int() ) &&
	 pixelLayersWithHits >= cut("pixelLayersWithHits", int() ) &&
	 muonHits > cut("muonHits", int() ) &&
	 globalNormChi2 <= cut("globalNormChi2", double() ) &&
	 trackNormChi2 <= cut("trackNormChi2", double() ) /*&& 


	 // temp look at global only
	 
	 isGlobal == cut("isGlobalMuon", int() )  &&
	 globalNormChi2 <= cut("globalNormChi2", double() ) &&
	 muonHits > cut("muonHits", int() ) 
	 */	 )
     )    
    passCut( ret, "QTF");
  // No isolation included in TOPDIL cuts
  if(ignoreCut("TOPDIL") || (
                           isGlobal == cut("isGlobalMuon", int() )  &&
                           isTracker == cut("isTrackerMuon", int() ) &&
                           trackerHits >= cut("trackerHits", int() ) &&
                           globalNormChi2 <= cut("globalNormChi2", double() ) &&
                           muonHits > cut("muonHits", int() )
                           )
     )
    passCut( ret, "TOPDIL");
 
  
  double pt = muon.pt();
  
  if(ignoreCut("pt") || pt > cut("pt", double() ) )
    passCut( ret, "pt");

  double eta = muon.eta();
  
  if(ignoreCut("eta") || fabs(eta) < cut("eta", double() ) )
    passCut( ret, "eta");


  setIgnored( ret );
  
  if(verbose_) ret.print( cout );
  
  
  // return value not really useful, use strbitset instead
  return (bool)ret;
}


bool MuonIDSelector::beamSpotSelection( const pat::Muon& muon, 
				const Point& position,
				pat::strbitset & ret)  {    

   
  if(verbose_) 
    cout<<"Selecting Pat muon : "<<muon.pt()<<endl;

  double dxy = 9999.;
  double dz = 9999.;



    const reco::TrackRef& track = muon.track();        
    if(!track.isNull() && !calcDispFromGlobalTrack_){
      dxy = track->dxy(position);
      dz = track->dz(position);
    } 
    else{
      if(muon.isGlobalMuon()){
	const reco::TrackRef& combinedMuon = muon.globalTrack();        
	dxy = combinedMuon->dxy(position);
	dz = combinedMuon->dz(position);
      }    
    }


  
  if(ignoreCut("dxy") || fabs(dxy) <= cut("dxy", double() ) )
    passCut( ret, "dxy");

  if(ignoreCut("dz") || fabs(dz) <= cut("dz", double() ) )
    passCut( ret, "dz");

  setIgnored( ret );
  
  //if(verbose_) ret.print( cout );
  return ret.test("dxy");

}

bool MuonIDSelector::beamSpotCut( const reco::Muon& muon, 
				const Point& position)  {  

  double dxy = 9999;
  double dz = 9999;


    const reco::TrackRef& track = muon.track();        
    if(!track.isNull() && !calcDispFromGlobalTrack_){
      dxy = track->dxy(position);
      dz = track->dz(position);
    } 
    else{
      if(muon.isGlobalMuon()){
	const reco::TrackRef& combinedMuon = muon.globalTrack();        
	dxy = combinedMuon->dxy(position);
	dz = combinedMuon->dz(position);
      }    
    }
    /*
    const reco::TrackRef& track = muon.track();        

  if(calcDispFromGlobalTrack_){
    if(muon.isGlobalMuon()){
      const reco::TrackRef& combinedMuon = muon.globalTrack();        
      dxy = combinedMuon->dxy(position);
      dz = combinedMuon->dz(position);
    }    
  }
  else{


    if(!track.isNull()){
      dxy = track->dxy(position);
      dz = track->dz(position);
    }
    else{
      if(muon.isGlobalMuon()){
	const reco::TrackRef& combinedMuon = muon.globalTrack();        
	dxy = combinedMuon->dxy(position);
	dz = combinedMuon->dz(position);
      }    
    }
  }
    */
  if(!ignoreCut("dxy") && fabs(dxy) > cut("dxy", double() ) )
    return false;
  
  if(!ignoreCut("dz") && fabs(dz) > cut("dz", double() ) )
    return false;

  return true;
}

// parallel versions of VBTF, QTF and TOPDIL cuts for reco muons in case you want to compare (without the strbitset)

bool MuonIDSelector::VBTFcuts( const reco::Muon& muon, 
				const Point& position)  {    

   
  if(verbose_) 
    cout<<"Selecting Reco muon with VBTF cuts: "<<muon.pt()<<endl;
  
  if(!ignoreCut("isGlobalMuon") && !muon.isGlobalMuon()  ) 
    return false;
  
  if(!ignoreCut("isTrackerMuon") && !muon.isTrackerMuon() ) 
    return false;
  
  int nMatches = muon.numberOfMatches();
  
  if(!ignoreCut("nMatches") && nMatches < cut("nMatches", int() ))
    return false;
  
  
  //const reco::TrackRef& combinedMuon = muon.combinedMuon();    
  const reco::TrackRef& combinedMuon = muon.globalTrack();    
  
  int trackerHits = combinedMuon->hitPattern().numberOfValidTrackerHits();
  
  if(!ignoreCut("trackerHits") && trackerHits < cut("trackerHits", int() ))
    return false;
  
  int pixelHits = combinedMuon->hitPattern().numberOfValidPixelHits();
  
  if(!ignoreCut("pixelHits") && pixelHits <= cut("pixelHits", int() ))
    return false;
  
  
  double globalNormChi2 = combinedMuon->normalizedChi2();
  if(!ignoreCut("globalNormChi2") && globalNormChi2 >= cut("globalNormChi2", double() ) )
    return false;
  
  


  double dxy = 9999.;

  const reco::TrackRef& track = muon.track();            

  if(!calcDispFromGlobalTrack_ && !track.isNull()){
      dxy = track->dxy(position);
  }
  else{
      dxy = combinedMuon->dxy(position);
  }

  /*
  if(calcDispFromGlobalTrack_){
    dxy = combinedMuon->dxy(position);
  }
  else{
  const reco::TrackRef& track = muon.track();            
    if(!track.isNull()){  
      dxy = track->dxy(position);
    }
    else{    
      dxy = combinedMuon->dxy(position);
    }  
  }
  */
  if(!ignoreCut("dxy") && fabs(dxy) > cut("dxy", double() ) )
    return false;
  
  int muonHits = combinedMuon->hitPattern().numberOfValidMuonHits();
  
  if(!ignoreCut("muonHits") && muonHits <= cut("muonHits", int() ))
    return false;
  
  
  
  double sumPtR03 = muon.isolationR03().sumPt;
  double emEtR03 = muon.isolationR03().emEt;
  double hadEtR03 = muon.isolationR03().hadEt;
  
  double relIso = (sumPtR03 + emEtR03 + hadEtR03)/muon.pt();
  
  if(!ignoreCut("relIso") && relIso > cut("relIso", double() ) )
    return false;


  return true;
}


bool MuonIDSelector::QTFcuts( const reco::Muon& muon, 
			       const Point& position)  {    
  if(verbose_) 
    cout<<"Selecting Reco muon with QTF cuts: "<<muon.pt()<<endl;

  /*  // This is a cut to test whether tracker muons can be brought into closer agreement
  if(!muon.isGlobalMuon() && muon.isTrackerMuon()){ 
    if(muon.numberOfChambers()<=4) return false;
    //cout<<" number of chambers "<<muon.numberOfChambers()<<endl;
  }
  */
  if(!ignoreCut("isTrackerMuon") && !(int)muon.isTrackerMuon() == cut("isTrackerMuon", int() )) 
    return false;

  if(!ignoreCut("tmLastStationAngTight") && !(int)muon::isGoodMuon(muon,muon::TMLastStationAngTight)  == cut("tmLastStationAngTight", int() )) 
    return false;
  
  if(!muon.track()) return false;

  const reco::TrackRef& track = muon.track();        

  if(!ignoreCut("trackerHits") && track->hitPattern().numberOfValidTrackerHits() < cut("trackerHits", int() ))
    return false;

  if(!ignoreCut("pixelLayersWithHits") && track->hitPattern().pixelLayersWithMeasurement() <= cut("pixelLayersWithHits", int() ))
    return false;

  if(!ignoreCut("trackNormChi2") && track->normalizedChi2() > cut("trackNormChi2", double() ) )
    return false;
  
  if(!ignoreCut("dxy") && fabs(track->dxy(position)) >= cut("dxy", double() ) )
    return false;
  
  if(!ignoreCut("dz") && fabs(track->dz(position)) >= cut("dz", double() ) )
    return false;

  int muonHits = 0;
  double globalNormChi2 = 9999.;

 if(muon.isGlobalMuon()){
    const reco::TrackRef& combinedMuon = muon.globalTrack();    
    muonHits = combinedMuon->hitPattern().numberOfValidMuonHits();
    globalNormChi2 = combinedMuon->normalizedChi2();
  }
  else{
    // hack!!!!
    muonHits = 999;
    //muonHits = 0;
    globalNormChi2 = 0.;
  }

  if(!ignoreCut("muonHits") && muonHits <= cut("muonHits", int() ))
    return false;
 
  if(!ignoreCut("globalNormChi2") && globalNormChi2 >= cut("globalNormChi2", double() ) )
    return false;

  /*
  // Also there are more cuts on the global muon, but if it fails it will pass as tracker anyway
  if(!ignoreCut("isGlobalMuon") && !muon.isGlobalMuon()  ) 
    return false;
  
  const reco::TrackRef& combinedMuon = muon.globalTrack();    
  
  double globalNormChi2 = combinedMuon->normalizedChi2();
  if(!ignoreCut("globalNormChi2") && globalNormChi2 >= cut("globalNormChi2", double() ) )
    return false;

  int muonHits = combinedMuon->hitPattern().numberOfValidMuonHits();
  if(!ignoreCut("muonHits") && muonHits <= cut("muonHits", int() ))
    return false;
    
  */


  return true;
}

bool MuonIDSelector::TOPDILcuts( const reco::Muon& muon,
                                const Point& position)  {


  if(verbose_)
    cout<<"Selecting Reco muon with TOPDIL cuts: "<<muon.pt()<<endl;

  if(!ignoreCut("isGlobalMuon") && !muon.isGlobalMuon()  )
    return false;

  if(!ignoreCut("isTrackerMuon") && !muon.isTrackerMuon() )
    return false;

  //const reco::TrackRef& combinedMuon = muon.combinedMuon();    
  const reco::TrackRef& combinedMuon = muon.globalTrack();

  int trackerHits = combinedMuon->hitPattern().numberOfValidTrackerHits();

  if(!ignoreCut("trackerHits") && trackerHits < cut("trackerHits", int() ))
    return false;

  double globalNormChi2 = combinedMuon->normalizedChi2();
  if(!ignoreCut("globalNormChi2") && globalNormChi2 >= cut("globalNormChi2", double() ) )
    return false;

  double dxy = 9999.;

  const reco::TrackRef& track = muon.track();

  if(!calcDispFromGlobalTrack_ && !track.isNull()){
      dxy = track->dxy(position);
  }
  else{
      dxy = combinedMuon->dxy(position);
  }

  if(!ignoreCut("dxy") && fabs(dxy) > cut("dxy", double() ) )
    return false;

  int muonHits = combinedMuon->hitPattern().numberOfValidMuonHits();

  if(!ignoreCut("muonHits") && muonHits <= cut("muonHits", int() ))
    return false;

  double sumPtR03 = muon.isolationR03().sumPt;
  double emEtR03 = muon.isolationR03().emEt;
  double hadEtR03 = muon.isolationR03().hadEt;

  double relIso = (sumPtR03 + emEtR03 + hadEtR03)/muon.pt();

  if(!ignoreCut("relIso") && relIso > cut("relIso", double() ) )
    return false;

  return true;
}
  


