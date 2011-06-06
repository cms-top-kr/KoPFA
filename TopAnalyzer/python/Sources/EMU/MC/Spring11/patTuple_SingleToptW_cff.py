import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/SingleTop_tW/patTuple_skim_1_1_8mz.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/SingleTop_tW/patTuple_skim_2_1_1Uk.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/SingleTop_tW/patTuple_skim_3_1_LVo.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/SingleTop_tW/patTuple_skim_4_1_Eez.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/SingleTop_tW/patTuple_skim_5_1_uEt.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/SingleTop_tW/patTuple_skim_6_1_bZ1.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/SingleTop_tW/patTuple_skim_7_1_NZA.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/SingleTop_tW/patTuple_skim_8_1_yCO.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/SingleTop_tW/patTuple_skim_9_1_Jpl.root',
])
