import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_1_1_uTK.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_2_1_92q.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_3_1_0zl.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_4_1_bKp.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_5_1_Uqq.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_6_1_ndp.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_7_1_JPE.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_8_1_ciw.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_9_1_7hL.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_10_1_Wi6.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_11_1_poq.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_12_1_019.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_13_1_HXP.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_14_1_r1y.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_15_1_Wco.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_16_1_kBI.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_17_1_dp4.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_18_1_I83.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_19_1_c2S.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/ZJets_1/patTuple_skim_20_1_pgT.root",
])
