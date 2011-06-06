import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYtt10to20_1/patTuple_skim_1_3_FCz.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYtt10to20_1/patTuple_skim_2_2_1Ea.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYtt10to20_1/patTuple_skim_3_1_ROv.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYtt10to20_1/patTuple_skim_4_2_STS.root',
])
