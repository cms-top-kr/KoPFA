#ifndef KoPFA_CommonTools_interface_MuonIDSelector_h
#define KoPFA_CommonTools_interface_MuonIDSelector_h

/**
   \class MuonIDSelector    
   \brief    
*/
#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include <vector>

using namespace std;

class MuonIDSelector : public Selector<pat::Muon>  {

 public: // interface

  typedef pat::Muon ObjectType;
  typedef math::XYZPoint Point;

   
  MuonIDSelector();
  
  /// initialize all parameters and cuts from a parameter set
  void initialize( const edm::ParameterSet& ps );
  
  /// initialize all parameters and cuts 


void initialize(int VBTF,
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
		double eta);
 
  // selector if no beam-spot included
  bool operator()( const pat::Muon & muon, pat::strbitset & ret );
  // selector w/ beam-spot
  bool operator()( const pat::Muon & muon, const edm::Handle<reco::BeamSpot>& beamSpot, pat::strbitset & ret );
  bool operator()( const pat::Muon & muon, const Point& position, pat::strbitset & ret );

  // beam-spot cut
  bool beamSpotSelection( const pat::Muon& muon, const Point& position, pat::strbitset & ret  );
  // muon ID criteria
  bool muIDSelection( const pat::Muon& muon, pat::strbitset & ret );

  bool beamSpotCut( const reco::Muon& muon, const Point& position);

  // For comparisons to reco muons
  bool VBTFcuts( const reco::Muon& muon, const Point& position);
  bool QTFcuts( const reco::Muon& muon, const Point& position);
  bool TOPDILcuts( const reco::Muon& muon, const Point& position);

 private: // member variables
  
  bool      verbose_;
  bool      calcDispFromGlobalTrack_;
  
};

#endif
