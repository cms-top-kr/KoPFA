import FWCore.ParameterSet.Config as cms

#Apply trigger matching
patMuonTrigger = cms.EDProducer( "PATTriggerProducer",
                                    processName    = cms.string('HLT'),
                                    triggerResults = cms.InputTag( "TriggerResults" ),
                                    triggerEvent   = cms.InputTag( "hltTriggerSummaryAOD" ),
                                    onlyStandAlone = cms.bool( False ),
                                    # trigger paths
                                    addPathModuleLabels = cms.bool( False ) # setting this 'True' stores the names of all modules as strings (~8kB/ev.)
                                    )


#Match With The triggers
patMuonTriggerMatch = cms.EDProducer( "PATTriggerMatcherDRDPtLessByR",
                                       src     = cms.InputTag( 'selectedPatMuonsPFlow'),
                                       matched = cms.InputTag( "patMuonTrigger" ),
                                       andOr          = cms.bool( False ),
                                       filterIdsEnum  = cms.vstring( '*' ),
                                       filterIds      = cms.vint32( 0 ),
                                       filterLabels   = cms.vstring( '*' ),
                                       pathNames      = cms.vstring('HLT_DoubleMu6_v1'),
                                       collectionTags = cms.vstring( '*' ),
                                       maxDPtRel = cms.double( 0.5 ),
                                       maxDeltaR = cms.double( 0.2 ),
                                       resolveAmbiguities    = cms.bool( True ),
                                       resolveByMatchQuality = cms.bool( False )
                                       )

triggeredPatMuons = cms.EDProducer("PATTriggerMatchMuonEmbedder",
                                   src     = cms.InputTag('selectedPatMuonsPFlow'),
                                   matches = cms.VInputTag( "patMuonTriggerMatch")
                                   )

triggerMatch  = cms.Sequence(
                           patMuonTrigger*
                           patMuonTriggerMatch*
                           triggeredPatMuons
                          )

