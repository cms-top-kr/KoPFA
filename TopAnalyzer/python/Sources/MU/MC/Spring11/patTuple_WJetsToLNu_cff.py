import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_1_3_NeE.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_2_2_uuT.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_3_2_0eh.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_4_3_XWD.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_5_1_FHV.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_6_1_FmD.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_7_0_KaU.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_8_0_PZo.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_9_0_Gwc.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_10_0_fDb.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_11_0_YCx.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_12_0_Hkd.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_13_0_JM8.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_14_0_cQl.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_15_0_jUZ.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_16_0_1Cm.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_16_1_0Ve.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/WJetsToLNu_1/patTuple_skim_17_0_hdw.root',
])
