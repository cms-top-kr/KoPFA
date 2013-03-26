#ifndef KoPFA_CommonTools_interface_LeptonIsoSelector_h
#define KoPFA_CommonTools_interface_LeptonIsoSelector_h


/**
   \class LeptonIsoSelector    
   \brief Selects pat::Electron or pat::Muons, on isolation criteria. 

   LeptonIsoSelector<class T> is a class template. Concrete classes are
   defined at the end of this file for T=pat::Electron and T=pat::Muon. 
   
   A SpecificIsolation is computed for charged hadrons,
   photons, and neutral hadrons. These SpecificIsolation can be arranged in 
   an arbitrary number of combined isolations. 

   Given a pat::Lepton, and for a given combined isolation combIso, 
   the LeptonIsoSelector 
   - computes the absolute isolation value combIsoAbs and the relative 
   isolation value combIsoRel ( = combIsoAbs / lepton pT), through the Isolation class
   - checks if the lepton passes the isolation cut on combIsoAbs, 
   and on combIsoRel. The results are stored in the strbitset, with the strings
   "combIsoAbs" and "combIsoRel"
   - the isolation values can later be accessed using the funcion
   const Isolation& isolation( const char* name )

   An example of use can be found in:
   http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/PFAnalyses/TemplateAnalysis/src/TestAnalyzer.cc?view=markup

   An example configuration can be found in:
   http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/PFAnalyses/TemplateAnalysis/test/Demo_cfg.py?view=markup
*/

#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"

#include "PhysicsTools/SelectorUtils/interface/Selector.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

 
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"

#include "KoPFA/CommonTools/interface/KoSpecificIsolation.h"
#include "KoPFA/CommonTools/interface/KoCombinedIsolation.h"

#include "Math/VectorUtil.h"
#include "TMath.h"



#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <string>



template <class T>
class LeptonIsoSelector : public Selector<T>  {

 public: // interface
  
  LeptonIsoSelector();
    
  virtual ~LeptonIsoSelector() {}
  
  /// initialize all parameters and cuts from a parameter set
  void initialize( const edm::ParameterSet& ps );
  
  /// does the lepton pass the cuts? 
  bool operator()( const T & lepton, pat::strbitset & ret );

  /// data structure to store the CombinedIsolations, as defined in the cfg,
  /// indexed by their name
  typedef std::map< std::string, KoCombinedIsolation> CombinedIsolations; 
  
  /// retrieve the combinedIsolation with a given name. 
  /// the combinedIsolation object can be printed, and can provide the 
  /// absolute and relative isolation values, for histogramming. 
  const KoCombinedIsolation& combinedIsolation( const char* name ) const {
    CombinedIsolations::const_iterator i = combinedIsolations_.find( name );
    if(i!=combinedIsolations_.end() ) 
      return i->second; 
    else {
      std::string err = "cannot find combinedIsolation";
      throw err;
    }
  }

  typedef reco::isodeposit::AbsVetos AbsVetos;

 private: 
  
  /// define an isolation cut from its parameters
  void setIsoCut( const edm::ParameterSet& ps ); 

   /// verbose mode
  bool      verbose_;
  
  /// parameters for charged hadron isolation value
  KoSpecificIsolation chargedIsoPar_;

  /// parameters for neutral hadron isolation value
  KoSpecificIsolation neutralIsoPar_;

  /// parameters for photon isolation value
  KoSpecificIsolation photonsIsoPar_;

  /// this vector will contain an arbitrary number of isolations, 
  /// as defined by the user in the python configuration file
  CombinedIsolations  combinedIsolations_;
     
};

template< class T>
LeptonIsoSelector<T>::LeptonIsoSelector()
  : verbose_(false) {
}


template< class T>
void LeptonIsoSelector<T>::initialize( const edm::ParameterSet& ps ) {
  
  verbose_ = ps.getUntrackedParameter<bool>("verbose", false);

  chargedIsoPar_.initialize( ps.getParameter<edm::ParameterSet>("chargedIsoPar"));
  neutralIsoPar_.initialize( ps.getParameter<edm::ParameterSet>("neutralIsoPar"));
  photonsIsoPar_.initialize( ps.getParameter<edm::ParameterSet>("photonsIsoPar"));

  if(verbose_){
    std::cout<<"*** Charged iso ***"<<std::endl;
    std::cout<<chargedIsoPar_<<std::endl;
    std::cout<<"*** Neutral iso ***"<<std::endl;
    std::cout<<neutralIsoPar_<<std::endl;
    std::cout<<"*** Photons iso ***"<<std::endl;
    std::cout<<photonsIsoPar_<<std::endl;
  }

  const std::vector<edm::ParameterSet>& vps  
    = ps.getParameter< std::vector< edm::ParameterSet > > ("isolationCuts");

  for( unsigned i=0; i<vps.size(); ++i) {

    const edm::ParameterSet& ps = vps[i];
    setIsoCut( ps );
  }
}


template< class T>
void LeptonIsoSelector<T>::setIsoCut( const edm::ParameterSet& ps ) {
  KoCombinedIsolation combinedIsolation;
  combinedIsolation.initialize(ps);
  
  if(verbose_) std::cout<<combinedIsolation<<std::endl;
  
  
  combinedIsolations_.insert( std::make_pair(combinedIsolation.name(), combinedIsolation) );

  std::string relcut = combinedIsolation.name();
  relcut += "Rel";
  Selector<T>::push_back( relcut );
  Selector<T>::set( relcut, combinedIsolation.relativeCut() );
  
  std::string abscut = combinedIsolation.name();
  abscut += "Abs";
  Selector<T>::push_back( abscut );
  Selector<T>::set( abscut, combinedIsolation.absoluteCut() ); 
}


template< class T>
bool LeptonIsoSelector<T>::operator()( const T & lepton, 
				       pat::strbitset & ret ) {

  const double Eta = lepton.p4().Eta();
  const double Phi = lepton.p4().Phi();

  // computing isolation value in cone for each
  // type of particle. 

  // retrieve the AbsVetos from the SpecificIsolation
  AbsVetos chargedVetos = chargedIsoPar_.getAbsVetoes();
  AbsVetos neutralVetos = neutralIsoPar_.getAbsVetoes();
  AbsVetos photonsVetos = photonsIsoPar_.getAbsVetoes();

  // center the deposits around the lepton
  for(unsigned int i = 0; i<chargedVetos.size(); i++){
    chargedVetos[i]->centerOn(Eta,Phi);
  }
  for(unsigned int i = 0; i<neutralVetos.size(); i++){
    neutralVetos[i]->centerOn(Eta,Phi);
  }
  for(unsigned int i = 0; i<photonsVetos.size(); i++){
    photonsVetos[i]->centerOn(Eta,Phi);
  }

  double chIso = (lepton.isoDeposit(pat::PfChargedHadronIso)->depositAndCountWithin( chargedIsoPar_.coneSize(), chargedVetos, false ).first);
  double nhIso = (lepton.isoDeposit(pat::PfNeutralHadronIso)->depositAndCountWithin( neutralIsoPar_.coneSize(), neutralVetos, false ).first);
  double phIso = (lepton.isoDeposit(pat::PfGammaIso)->depositAndCountWithin( photonsIsoPar_.coneSize(), photonsVetos ,false ).first);
      
  if(verbose_) {
    std::cout << "LeptonIsoSelector : lepton pt = "<<lepton.pt() <<std::endl;
    std::cout << "Ch iso = "
	 << chIso
	 << " , Nh iso = "
	 << nhIso
	 << " , Ph iso = "
	 << phIso
	 << std::endl;
  }
 
  // testing all isolation cuts
  typedef CombinedIsolations::iterator II;

  for(II ii=combinedIsolations_.begin(); ii!=combinedIsolations_.end(); ++ii) {
    
    // testing relative combinedIsolation:
    std::string cutName = ii->first;
    cutName += "Rel";
    
    if( Selector<T>::ignoreCut( cutName ) || 
	ii->second.testIsoCut( chIso, nhIso, phIso, lepton.pt(), true ) )
      Selector<T>::passCut( ret, cutName);

    // testing absolute isolation:
    cutName = ii->first;
    cutName += "Abs";
    
    if( Selector<T>::ignoreCut( cutName ) || 
	ii->second.testIsoCut( chIso, nhIso, phIso, lepton.pt(), false ) )
      Selector<T>::passCut( ret, cutName);
  }


  if(verbose_) ret.print(std::cout);

  return (bool) ret;
}





#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

//  class for selecting pat::Muons
typedef LeptonIsoSelector<pat::Muon> MuonIsoSelector;

// class for selecting pat::Electrons
typedef LeptonIsoSelector<pat::Electron> ElectronIsoSelector;


#endif
