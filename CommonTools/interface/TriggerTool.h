#ifndef KoPFA_CommonTools_TriggerTool_
#define KoPFA_CommonTools_TriggerTool_

// system include files
#include <vector>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/Candidate/interface/LeafCandidate.h"

#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include <iostream>
#include <cassert>



/**\class TriggerTool 
\brief Produces a collection of LeafCandidate corresponding to a given HLT path. 
       Code follows the HLTEventAnalyzerAOD of Martin Gruenwald.

\author Colin Bernet, Emmanuelle Perez
\date   September 2010
*/




class TriggerTool : public edm::EDProducer {
 public:

  typedef std::vector< reco::Particle> ParticleCollection;
  explicit TriggerTool(const edm::ParameterSet&);
  ~TriggerTool();
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void beginJob();
  virtual void beginRun(edm::Run&, edm::EventSetup const&);

 private:
  
  
  /// PFCandidates to be analyzed
  edm::InputTag   inputTagTriggerEvent_;
  
  /// vertices
  edm::InputTag   inputTagTriggerResults_;

  /// HLT path
  std::string     HLTPath_; 

  /// verbose ?
  bool   verbose_;

  HLTConfigProvider hltConfig_;
  edm::Handle<edm::TriggerResults>   triggerResultsHandle_;
  edm::Handle<trigger::TriggerEvent> triggerEventHandle_;

  std::string processName_;

  

};

#endif

