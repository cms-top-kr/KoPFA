import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
#    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/',
])
