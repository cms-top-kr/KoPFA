import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110513/patTuple_skim_1_1_QfQ.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110513/patTuple_skim_2_1_e0E.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110513/patTuple_skim_3_1_Sa9.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110513/patTuple_skim_4_1_He5.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110513/patTuple_skim_5_1_1dj.root',
])
