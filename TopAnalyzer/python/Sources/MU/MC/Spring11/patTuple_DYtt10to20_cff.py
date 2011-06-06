import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_1_1_GQz.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_2_1_8Ta.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_3_1_vgS.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_4_1_gd2.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_5_1_jUr.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_6_1_HE9.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_7_1_f7e.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_8_1_9rw.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_9_1_rZM.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_10_1_Gnv.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_11_1_IvE.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_12_1_u2B.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_13_1_lTx.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_14_1_jI7.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_15_1_eap.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_16_1_qXE.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_17_1_FiK.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_18_1_6WS.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_19_1_dhn.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/MuMu/MC/20110603/DYtt10to20/patTuple_skim_20_1_RVg.root',
])
