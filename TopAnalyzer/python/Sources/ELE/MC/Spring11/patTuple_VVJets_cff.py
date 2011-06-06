import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_1_1_bvk.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_2_1_9Nn.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_3_1_C9q.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_4_1_tju.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_5_1_NJP.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_6_1_yKM.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_7_1_ryS.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_8_1_3yL.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_9_1_nPC.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_10_1_77X.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_11_1_kzo.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_12_1_qnM.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_13_1_qxf.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_14_1_XKK.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_15_1_O5M.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_16_1_i73.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_17_1_TTl.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_18_1_3jb.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_19_1_W8C.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_20_1_IMv.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110603/VVJets/patTuple_skim_21_1_etI.root',
])
