import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/SingleTop_tW/patTuple_skim_1_1_7U1.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/SingleTop_tW/patTuple_skim_2_1_AXB.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/SingleTop_tW/patTuple_skim_3_1_w5U.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/SingleTop_tW/patTuple_skim_4_1_7Uu.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/SingleTop_tW/patTuple_skim_5_1_hra.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/SingleTop_tW/patTuple_skim_6_1_CjY.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/SingleTop_tW/patTuple_skim_7_1_iZ4.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/SingleTop_tW/patTuple_skim_8_1_F3J.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/SingleTop_tW/patTuple_skim_9_1_gDY.root',
])
