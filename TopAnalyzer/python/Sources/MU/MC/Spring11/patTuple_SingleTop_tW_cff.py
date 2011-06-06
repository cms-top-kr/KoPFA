import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/SingleTop_tW/patTuple_skim_1_1_LYR.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/SingleTop_tW/patTuple_skim_2_1_QtN.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/SingleTop_tW/patTuple_skim_3_1_KmZ.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/SingleTop_tW/patTuple_skim_4_1_4Uz.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/SingleTop_tW/patTuple_skim_5_1_dUI.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/SingleTop_tW/patTuple_skim_6_1_R2O.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/SingleTop_tW/patTuple_skim_7_1_g4w.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/SingleTop_tW/patTuple_skim_8_1_bwA.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/SingleTop_tW/patTuple_skim_9_1_PHy.root',
])
