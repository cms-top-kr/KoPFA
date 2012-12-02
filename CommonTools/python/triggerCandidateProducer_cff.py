import FWCore.ParameterSet.Config as cms

from KoPFA.CommonTools.triggerCandidateProducer_cfi import * 

triggerCandidateHLTMu9 = triggerCandidate.clone()
triggerCandidateHLTMu9.HLTPath = cms.string("HLT_Mu9")

# here, define the other trigger candidate producers in the same  way



