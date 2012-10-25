#ifndef CMGTtFullLepMaosSolutionProducer_h
#define CMGTtFullLepMaosSolutionProducer_h

//
// $Id: CMGTtFullLepMaosSolutionProducer.h,v 1.1 2012/10/25 15:43:38 youngjo Exp $
//
#include <memory>
#include <string>
#include <vector>
#include "TLorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Candidate/interface/LeafCandidate.h"

//#include "TopQuarkAnalysis/TopKinFitter/interface/TtFullLepKinSolver.h"
#include "KoPFA/DataFormats/interface/Maos.h"

#include "AnalysisDataFormats/CMGTools/interface/BaseMET.h"
#include "AnalysisDataFormats/CMGTools/interface/BaseJet.h"
#include "AnalysisDataFormats/CMGTools/interface/PFJet.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"
#include "KoPFA/DataFormats/interface/TTbarDILEvent.h"
#include "Math/LorentzVector.h"

class CMGTtFullLepMaosSolutionProducer : public edm::EDProducer {

  public:

    explicit CMGTtFullLepMaosSolutionProducer(const edm::ParameterSet & iConfig);
    ~CMGTtFullLepMaosSolutionProducer();
    
    virtual void beginJob();
    virtual void produce(edm::Event & evt, const edm::EventSetup & iSetup);
    virtual void endJob();

  private:  

    // next methods are avoidable but they make the code legible
    inline bool PTComp(const reco::Candidate*, const reco::Candidate*) const;
    inline bool LepDiffCharge(const reco::Candidate* , const reco::Candidate*) const;
    inline bool HasPositiveCharge(const reco::Candidate*) const;
    
    struct Compare{
      bool operator()(std::pair<double, int> a, std::pair<double, int> b){
        return a.first > b.first;
      } 
    };
    
    edm::InputTag jets_;
    edm::InputTag electrons_;
    edm::InputTag muons_;
    edm::InputTag mets_;

    std::string jetCorrLevel_;
    int maxNJets_, maxNComb_;
    bool eeChannel_, emuChannel_, mumuChannel_, searchWrongCharge_;
    double tmassbegin_, tmassend_, tmassstep_;
    std::vector<double> nupars_;

    vallot::Maos* solver; 
    //TtFullLepKinSolver* solver;
};

inline bool CMGTtFullLepMaosSolutionProducer::PTComp(const reco::Candidate* l1, const reco::Candidate* l2) const 
{
  return (l1->pt() > l2->pt());
}

inline bool CMGTtFullLepMaosSolutionProducer::LepDiffCharge(const reco::Candidate* l1, const reco::Candidate* l2) const 
{
  return (l1->charge() != l2->charge());
}

inline bool CMGTtFullLepMaosSolutionProducer::HasPositiveCharge(const reco::Candidate* l) const 
{
  return (l->charge() > 0);
}

CMGTtFullLepMaosSolutionProducer::CMGTtFullLepMaosSolutionProducer(const edm::ParameterSet & iConfig) 
{
  // configurables
  jets_        = iConfig.getParameter<edm::InputTag>("jets");
  electrons_   = iConfig.getParameter<edm::InputTag>("electrons");
  muons_       = iConfig.getParameter<edm::InputTag>("muons");
  mets_        = iConfig.getParameter<edm::InputTag>("mets");
  jetCorrLevel_= iConfig.getParameter<std::string>  ("jetCorrectionLevel");  
  maxNJets_       = iConfig.getParameter<int> ("maxNJets");
  maxNComb_       = iConfig.getParameter<int> ("maxNComb");  
  eeChannel_      = iConfig.getParameter<bool>("eeChannel"); 
  emuChannel_     = iConfig.getParameter<bool>("emuChannel");
  mumuChannel_    = iConfig.getParameter<bool>("mumuChannel");
  searchWrongCharge_ = iConfig.getParameter<bool> ("searchWrongCharge");  
  tmassbegin_       = iConfig.getParameter<double>("tmassbegin");
  tmassend_         = iConfig.getParameter<double>("tmassend");
  tmassstep_        = iConfig.getParameter<double>("tmassstep");
  nupars_           = iConfig.getParameter<std::vector<double> >("neutrino_parameters");
  
  // define what will be produced
  produces<std::vector<std::vector<int> > >  (); // vector of the particle inices (b, bbar, e1, e2, mu1, mu2)
  produces<std::vector<reco::LeafCandidate> >("fullLepNeutrinos");
  produces<std::vector<reco::LeafCandidate> >("fullLepNeutrinoBars");
  produces<std::vector<double> >("solWeight");          //weight for a specific kin solution 
  produces<bool>("isWrongCharge");                      //true if leptons have the same charge    
  produces<std::vector<vallot::TTbarDILEvent> >("ttbars");
}

CMGTtFullLepMaosSolutionProducer::~CMGTtFullLepMaosSolutionProducer() 
{
}

void CMGTtFullLepMaosSolutionProducer::beginJob()
{
    solver = new vallot::Maos();
  //solver = new TtFullLepKinSolver(tmassbegin_, tmassend_, tmassstep_, nupars_);
}

void CMGTtFullLepMaosSolutionProducer::endJob()
{
  delete solver;
}

void CMGTtFullLepMaosSolutionProducer::produce(edm::Event & evt, const edm::EventSetup & iSetup) 
{    
  //create vectors fo runsorted output
  std::vector<std::vector<int> > idcsV;
  std::vector<reco::LeafCandidate> nusV;
  std::vector<reco::LeafCandidate> nuBarsV;
  std::vector<std::pair<double, int> > weightsV;

  //create pointer for products
  std::auto_ptr<std::vector<std::vector<int> > >   pIdcs(new std::vector<std::vector<int> >);
  std::auto_ptr<std::vector<reco::LeafCandidate> > pNus(new std::vector<reco::LeafCandidate>);
  std::auto_ptr<std::vector<reco::LeafCandidate> > pNuBars(new std::vector<reco::LeafCandidate>);
  std::auto_ptr<std::vector<double> >              pWeight(new std::vector<double>);  
  std::auto_ptr<bool> pWrongCharge(new bool);  
  std::auto_ptr<std::vector<vallot::TTbarDILEvent> >    ttbarMaosSolutions(new std::vector<vallot::TTbarDILEvent>());  
 
  edm::Handle<std::vector<cmg::PFJet> > jets;
  evt.getByLabel(jets_, jets);
  edm::Handle<std::vector<cmg::Electron> > electrons;
  evt.getByLabel(electrons_, electrons);
  edm::Handle<std::vector<cmg::Muon> > muons;
  evt.getByLabel(muons_, muons);
  edm::Handle<std::vector<cmg::BaseMET> > mets;
  evt.getByLabel(mets_, mets);
  
  int selMuon1 = -1, selMuon2 = -1;
  int selElectron1 = -1, selElectron2 = -1;
  bool ee = false;
  bool emu = false;
  bool mumu = false;
  bool isWrongCharge = false;
  bool jetsFound = false;
  bool METFound = false;
  bool electronsFound = false;
  bool electronMuonFound = false;
  bool muonsFound = false;
  TLorentzVector metV(0,0,0,0); 
 
  //select Jets (TopJet vector is sorted on ET)
  if(jets->size()>=2) { jetsFound = true; }  
  
  //select MET (TopMET vector is sorted on ET)
  if(mets->size()>=1) { 
     METFound = true; 
     metV.SetPxPyPzE((*mets)[0].px(),(*mets)[0].py(),0,(*mets)[0].pt());
  }
  
  // If we have electrons and muons available, 
  // build a solutions with electrons and muons.
  if(muons->size() + electrons->size() >=2) {     
    // select leptons
    if(electrons->size() == 0) mumu = true;
    else if(muons->size() == 0) ee = true;
    else if(electrons->size() == 1) {
      if(muons->size() == 1) emu = true;
      else if(PTComp(&(*electrons)[0], &(*muons)[1])) emu = true;
      else mumu = true;
    }
    else if(electrons->size() > 1) {
      if(PTComp(&(*electrons)[1], &(*muons)[0])) ee = true;
      else if(muons->size() == 1) emu = true;
      else if(PTComp(&(*electrons)[0], &(*muons)[1])) emu = true;
      else mumu = true;
    }
    if(ee && eeChannel_) {          
      if(LepDiffCharge(&(*electrons)[0], &(*electrons)[1]) || searchWrongCharge_) {
        if(HasPositiveCharge(&(*electrons)[0]) || !LepDiffCharge(&(*electrons)[0], &(*electrons)[1])) {
          selElectron1 = 0;
          selElectron2 = 1;
        } 
	else{
          selElectron1 = 1;
          selElectron2 = 0;
	}
	electronsFound = true;
	if(!LepDiffCharge(&(*electrons)[0], &(*electrons)[1])) isWrongCharge = true;
      }
    }
    else if(emu && emuChannel_) {    
      if(LepDiffCharge(&(*electrons)[0], &(*muons)[0]) || searchWrongCharge_) {
	selElectron1 = 0;
        selMuon1 = 0;
	electronMuonFound = true;
	if(!LepDiffCharge(&(*electrons)[0], &(*muons)[0])) isWrongCharge = true;
      }
    }
    else if(mumu && mumuChannel_) {  
      if(LepDiffCharge(&(*muons)[0], &(*muons)[1]) || searchWrongCharge_) {
        if(HasPositiveCharge(&(*muons)[0]) || !LepDiffCharge(&(*muons)[0], &(*muons)[1])) {
          selMuon1 = 0;
          selMuon2 = 1;
        } 
	else {
          selMuon1 = 1;
          selMuon2 = 0;
        }
	muonsFound = true;
	if(!LepDiffCharge(&(*muons)[0], &(*muons)[1])) isWrongCharge = true;
      }
    }
  }
  
  *pWrongCharge = isWrongCharge;
   
  // Check that the above work makes sense
  if(int(ee)+int(emu)+int(mumu)>1) {
    edm::LogWarning("CMGTtFullLepMaosSolutionProducer") << "Lepton selection criteria uncorrectly defined";
  }
    
  // Check if the leptons for the required Channel are available
  bool correctLeptons = ((electronsFound && eeChannel_) || (muonsFound && mumuChannel_) || (electronMuonFound && emuChannel_) );
  // Check for equally charged leptons if for wrong charge combinations is searched
  if(isWrongCharge) correctLeptons *= searchWrongCharge_;       
                                          
  if(correctLeptons && METFound && jetsFound) { 
            
    // run over all jets if input parameter maxNJets is -1 or
    // adapt maxNJets if number of present jets is smaller than selected
    // number of jets    
    int stop=maxNJets_;
    if(jets->size()<static_cast<unsigned int>(stop) || stop<0) stop=jets->size();
       
    // counter for number of found kinematic solutions
    int nSol=0;
    // consider all permutations
    for (int ib = 0; ib<stop; ib++) {
      // second loop of the permutations
      for (int ibbar = 0; ibbar<stop; ibbar++) {
        // avoid the diagonal: b and bbar must be distinct jets
        if(ib==ibbar) continue;
		
	std::vector<int> idcs;
	
	// push back the indices of the jets
	idcs.push_back(ib);
	idcs.push_back(ibbar);

        TLorentzVector LV_l1;
        TLorentzVector LV_l2;		
	TLorentzVector LV_b    = TLorentzVector((*jets)[ib].px(), 
	                                        (*jets)[ib].py(), 
						(*jets)[ib].pz(), 
						(*jets)[ib].energy() );
        TLorentzVector LV_bbar = TLorentzVector((*jets)[ibbar].px(), 
	                                        (*jets)[ibbar].py(), 
						(*jets)[ibbar].pz(), 
						(*jets)[ibbar].energy());  
			
	if (ee) {
          idcs.push_back(selElectron1);	  
	  LV_l1.SetXYZT((*electrons)[selElectron1].px(), 
	                (*electrons)[selElectron1].py(), 
		        (*electrons)[selElectron1].pz(), 
		        (*electrons)[selElectron1].energy());	  
	
          idcs.push_back(selElectron2);	  
	  LV_l2.SetXYZT((*electrons)[selElectron2].px(), 
	                (*electrons)[selElectron2].py(), 
		        (*electrons)[selElectron2].pz(), 
		        (*electrons)[selElectron2].energy());	  

	  idcs.push_back(-1);
	  idcs.push_back(-1);
	} 
				
	else if (emu) {
	  if(!isWrongCharge){
	    if(HasPositiveCharge(&(*electrons)[selElectron1])){	  
              idcs.push_back(selElectron1);	  
	      LV_l1.SetXYZT((*electrons)[selElectron1].px(), 
	                    (*electrons)[selElectron1].py(), 
		            (*electrons)[selElectron1].pz(), 
		            (*electrons)[selElectron1].energy());	  

	      idcs.push_back(-1);
	      idcs.push_back(-1);	    

              idcs.push_back(selMuon1);	  
	      LV_l2.SetXYZT((*muons)[selMuon1].px(), 
	                    (*muons)[selMuon1].py(), 
		            (*muons)[selMuon1].pz(), 
		            (*muons)[selMuon1].energy());	  
	    }
	    else{
	      idcs.push_back(-1);	    
	        
              idcs.push_back(selMuon1);	  
	      LV_l1.SetXYZT((*muons)[selMuon1].px(), 
	                    (*muons)[selMuon1].py(), 
		            (*muons)[selMuon1].pz(), 
		            (*muons)[selMuon1].energy());	  
	      
              idcs.push_back(selElectron1);	  
	      LV_l2.SetXYZT((*electrons)[selElectron1].px(), 
	                    (*electrons)[selElectron1].py(), 
		            (*electrons)[selElectron1].pz(), 
		            (*electrons)[selElectron1].energy());	  
	      	  
	      idcs.push_back(-1);			    
	    }	    	    
	  }
	  else{  // means "if wrong charge"
	    if(HasPositiveCharge(&(*electrons)[selElectron1])){	// both leps positive    	    
              idcs.push_back(selElectron1);	  
	      LV_l1.SetXYZT((*electrons)[selElectron1].px(), 
	                    (*electrons)[selElectron1].py(), 
		            (*electrons)[selElectron1].pz(), 
		            (*electrons)[selElectron1].energy());	  
	      
              idcs.push_back(-1);
    
              idcs.push_back(selMuon1);	  
	      LV_l2.SetXYZT((*muons)[selMuon1].px(), 
	                    (*muons)[selMuon1].py(), 
		            (*muons)[selMuon1].pz(), 
		            (*muons)[selMuon1].energy());	  
	      	  
	      idcs.push_back(-1);	    
	    }
	    else{ // both leps negative
	      idcs.push_back(-1);	    
	    
              idcs.push_back(selElectron1);	  
	      LV_l2.SetXYZT((*electrons)[selElectron1].px(), 
	                    (*electrons)[selElectron1].py(), 
		            (*electrons)[selElectron1].pz(), 
		            (*electrons)[selElectron1].energy());	  
	      
	      idcs.push_back(-1);
    
              idcs.push_back(selMuon1);	  
	      LV_l1.SetXYZT((*muons)[selMuon1].px(), 
	                    (*muons)[selMuon1].py(), 
		            (*muons)[selMuon1].pz(), 
		            (*muons)[selMuon1].energy());	  
	    }
	  }	  
        }
	        	
	else if (mumu) {
	  idcs.push_back(-1);
	  idcs.push_back(-1);
	
          idcs.push_back(selMuon1);	  
	  LV_l1.SetXYZT((*muons)[selMuon1].px(), 
	                (*muons)[selMuon1].py(), 
		        (*muons)[selMuon1].pz(), 
		        (*muons)[selMuon1].energy());	  
	
          idcs.push_back(selMuon2);	  
	  LV_l2.SetXYZT((*muons)[selMuon2].px(), 
	                (*muons)[selMuon2].py(), 
		        (*muons)[selMuon2].pz(), 
		        (*muons)[selMuon2].energy());	  
        }
	 		
        // calculate neutrino momenta and eventweight
        //vallot::Maos* solver = new vallot::Maos();
        double mt2 = solver->MAOS(metV,LV_l1+LV_b,LV_l2+LV_bbar, 0.0, 0.0, false );
	// add solution to the vectors of solutions if solution exists 
	if(mt2>0){
	  // add the leptons and jets indices to the vector of combinations
	  idcsV.push_back(idcs);

          reco::LeafCandidate nu1;
          reco::LeafCandidate nu2;

          ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > nu1p4;
          ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > nu2p4;

          nu1p4.SetPxPyPzE( solver->nu1().Px(),solver->nu1().Py(),solver->nu1().Pz(),solver->nu1().Pt() );
          nu2p4.SetPxPyPzE( solver->nu2().Px(),solver->nu2().Py(),solver->nu2().Pz(),solver->nu2().Pt() );
 
          nu1.setP4( nu1p4 );
          nu2.setP4( nu2p4 );

	  // add the neutrinos
	  nusV.push_back( nu1);	
	  nuBarsV.push_back( nu2);

          double weight = 1/((pow(solver->leg1().M()-174.,2) + pow(solver->leg2().M()-174.,2))/pow(9.5,2)+
                             (pow((solver->nu1()+LV_l1).M()-80.4,2) + pow((solver->nu2()+LV_l2).M()-80.4,2))/pow(7.5,2) +
                              pow(solver->leg1().M()-solver->leg2().M(),2)/pow(9.5,2)+
                              pow((solver->nu1()+LV_l1).M()-(solver->nu2()+LV_l2).M(),2)/pow(7.5,2) 
                            );	
	  // add the solution weight
	  weightsV.push_back(std::make_pair(weight, nSol));
	  
	  nSol++;
	}
      }
    }           
  }
  
  if(weightsV.size()==0){      
    //create dmummy vector 
    std::vector<int> idcs;
    for(int i=0; i<6; ++i)
      idcs.push_back(-1);

    idcsV.push_back(idcs);
    weightsV.push_back(std::make_pair(-1,0));
    reco::LeafCandidate nu;
    nusV.push_back(nu);
    reco::LeafCandidate nuBar;
    nuBarsV.push_back(nuBar);
  }

  // check if all vectors have correct length
  int weightL = weightsV.size();
  int nuL     = nusV.size();  
  int nuBarL  = nuBarsV.size();  
  int idxL    = idcsV.size();   
      
  if(weightL!=nuL || weightL!=nuBarL || weightL!=idxL){
    edm::LogWarning("CMGTtFullLepMaosSolutionProducer") << "Output vectors are of different length:"
    << "\n weight: " << weightL    
    << "\n     nu: " << nuL
    << "\n  nubar: " << nuBarL
    << "\n   idcs: " << idxL;
  } 
    
  // sort vectors by weight in decreasing order
  if(weightsV.size()>1){
    sort(weightsV.begin(), weightsV.end(), Compare());
  }
  
  // determine the number of solutions which is written in the event
  int stop=weightL;
  if(maxNComb_>0 && maxNComb_<stop) stop=maxNComb_;
  for(int i=0; i<stop; ++i){
    pWeight->push_back(weightsV[i].first);
    pNus   ->push_back(nusV[weightsV[i].second]);
    pNuBars->push_back(nuBarsV[weightsV[i].second]);    
    pIdcs  ->push_back(idcsV[weightsV[i].second]);    
  }

  ///// Set the combination for top quark four-momentum
  for(int i=0; i<stop; ++i){
    double weight = pWeight->at(i);
    std::vector<int> match = pIdcs->at(i);
    //debug
    //for(unsigned int k = 0; k < match.size() ; k++){
    //  std::cout << match[k] << " " ; 
    //}
    //std::cout << std::endl;
    if( weight < 0 ) continue;
    int ib = match[0];
    int ibbar = match[1];
    TLorentzVector nu( pNus->at(i).px(), pNus->at(i).py(), pNus->at(i).pz(), pNus->at(i).energy() );
    TLorentzVector nuBar( pNuBars->at(i).px(), pNuBars->at(i).py(), pNuBars->at(i).pz(), pNuBars->at(i).energy() );
    TLorentzVector b( (*jets)[ib].px(), (*jets)[ib].py(), (*jets)[ib].pz(), (*jets)[ib].energy() );
    TLorentzVector bBar( (*jets)[ibbar].px(), (*jets)[ibbar].py(), (*jets)[ibbar].pz(), (*jets)[ibbar].energy() );

    TLorentzVector LepBar(0,0,0,0);  
    TLorentzVector Lep(0,0,0,0);  
    
    if( !electrons->empty() && match[2]>=0) {
      //std::cout << "LepBar= " ;
      LepBar.SetPxPyPzE( (*electrons)[match[2]].px(), (*electrons)[match[2]].py(), (*electrons)[match[2]].pz(), (*electrons)[match[2]].energy() );
      //std::cout << LepBar.Pt();
    }

    if( !electrons->empty() && match[3]>=0){
      //std::cout << "Lep= " ;
      Lep.SetPxPyPzE( (*electrons)[match[3]].px(), (*electrons)[match[3]].py(), (*electrons)[match[3]].pz(), (*electrons)[match[3]].energy() );
      //std::cout << Lep.Pt();
    }

    if( !muons->empty() && match[4]>=0 && match[2]<0){
      //std::cout << "LepBar= " ;
      LepBar.SetPxPyPzE( (*muons)[match[4]].px(), (*muons)[match[4]].py(), (*muons)[match[4]].pz(), (*muons)[match[4]].energy() );
      //std::cout << LepBar.Pt();
    }
    // this 'else' happens if you have a wrong charge electron-muon-
    // solution so the indices are (b-idx, bbar-idx, 0, -1, 0, -1)
    // so the mu^+ is stored as l^-
    else if( !muons->empty() && match[4]>=0){
      //std::cout << "Lep= " ;
      Lep.SetPxPyPzE( (*muons)[match[4]].px(), (*muons)[match[4]].py(), (*muons)[match[4]].pz(), (*muons)[match[4]].energy() );
      //std::cout << Lep.Pt();
    }
    if( !muons->empty()  && match[5]>=0 && match[3]<0){ 
      //std::cout << "Lep= " ;
      Lep.SetPxPyPzE( (*muons)[match[5]].px(), (*muons)[match[5]].py(), (*muons)[match[5]].pz(), (*muons)[match[5]].energy() );
      //std::cout << Lep.Pt();
    }
    // this 'else' happens if you have a wrong charge electron-muon-
    // solution so the indices are (b-idx, bbar-idx, -1, 0, -1, 0)  
    // so the mu^- is stored as l^+
    else if( !muons->empty()  && match[5]>=0){ 
      //std::cout << "LepBar= " ;
      LepBar.SetPxPyPzE( (*muons)[match[5]].px(), (*muons)[match[5]].py(), (*muons)[match[5]].pz(), (*muons)[match[5]].energy() );
      //std::cout << LepBar.Pt();
    }
    TLorentzVector top = LepBar + nu + b;
    TLorentzVector topBar = Lep + nuBar + bBar;

    TLorentzVector ttbar = top + topBar;

    vallot::TTbarDILEvent ttbarMaosSolution;

    ttbarMaosSolution.SetLeg1( top );
    ttbarMaosSolution.SetLeg2( topBar );

    ttbarMaosSolution.SetNu1( nu );
    ttbarMaosSolution.SetNu2( nuBar );

    ttbarMaosSolution.SetM( ttbar.M() );
    ttbarMaosSolution.SetBId( ib, ibbar );  
    
    int j1 = -1; 
    int j2 = -1;
    double Mbb = -1;
    std::vector<int> add;
    if( jets->size() >= 4){  
      for( int n =0 ; n < (int) jets->size(); n++){
        if( !( n == ib || n == ibbar) ) add.push_back(n);
      }
 
      j1 = add[0];
      j2 = add[1];
 
      TLorentzVector j1p4( (*jets)[j1].px(), (*jets)[j1].py(), (*jets)[j1].pz(), (*jets)[j1].energy() );
      TLorentzVector j2p4( (*jets)[j2].px(), (*jets)[j2].py(), (*jets)[j2].pz(), (*jets)[j2].energy() );
      TLorentzVector Mbbp4 = j1p4 + j2p4;
      Mbb = Mbbp4.M();
    }

    ttbarMaosSolution.SetJId( j1, j2);
    ttbarMaosSolution.SetMbb( Mbb );

    ttbarMaosSolutions->push_back(ttbarMaosSolution); 
  }
  /////

  // put the results in the event
  evt.put(pIdcs);     
  //evt.put(pNus,         "fullLepNeutrinos");  
  //evt.put(pNuBars,      "fullLepNeutrinoBars");             
  evt.put(pWeight,      "solWeight");  
  evt.put(pWrongCharge, "isWrongCharge"); 
  evt.put(ttbarMaosSolutions,   "ttbars");
}

#endif
