import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_1_2_L6e.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_2_1_9Z1.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_3_1_CCI.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_4_2_J0m.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_5_1_hBl.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_6_2_Z7a.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_7_2_20v.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_8_1_g3E.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_9_1_qXW.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_10_1_AUV.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_11_1_6C6.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_12_1_UNd.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_13_1_5Ut.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_14_2_HxD.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuEl/MC/20110603/DYee10to20/patTuple_skim_15_1_9Q2.root',
])
