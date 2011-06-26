import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_1_1_OhX.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_2_1_1kV.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_3_1_kAk.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_4_1_uuq.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_5_1_cdK.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_6_1_d3X.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_7_1_3lC.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_8_1_hse.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_9_1_Rub.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_10_1_9Uv.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_11_1_krT.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_12_1_B5W.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_13_1_dmT.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_14_3_0us.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_15_1_0OQ.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_16_1_iDy.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_17_1_TF6.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_18_1_LL0.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_19_1_w6b.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/ZJets_3/patTuple_skim_20_1_6WP.root",
])
