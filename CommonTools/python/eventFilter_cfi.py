import FWCore.ParameterSet.Config as cms

from HLTrigger.HLTfilters.hltHighLevel_cfi import *

#EventFilter = cms.EDFilter("EventFilter",
#    filters = cms.vstring("primaryVertexFilterPath",
#                          "HBHENoiseFilterPath",
#                          "noscrapingFilterPath",
#                         )
#)

EventFilter = hltHighLevel.clone()
EventFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","PAT")
EventFilter.HLTPaths = cms.vstring('primaryVertexFilterPath','HBHENoiseFilterPath','noscrapingFilterPath')
EventFilter.andOr = cms.bool(False)
#EventFilter.HLTPaths = cms.vstring('primaryVertexFilterPath','HBHENoiseFilterPath','noscrapingFilterPath','totalKinematicsFilterPath')
#EventFilter.throw = cms.bool(False)
