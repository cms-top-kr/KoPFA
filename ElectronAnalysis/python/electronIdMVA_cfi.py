import FWCore.ParameterSet.Config as cms

mvaElectrons = cms.EDFilter("ElectronIdMVA",
                            vertexTag = cms.InputTag('goodOfflinePrimaryVertices'),
                            electronTag = cms.InputTag('acceptedElectrons'),
                            HZZmvaWeightFile = cms.string('RecoEgamma/ElectronIdentification/data/TMVA_BDTSimpleCat_17Feb2011.weights.xml'),
                            )
