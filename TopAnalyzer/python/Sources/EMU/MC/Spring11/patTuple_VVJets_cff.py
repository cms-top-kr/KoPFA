import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_1_1_WGh.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_2_1_krm.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_3_1_qoK.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_4_1_teg.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_5_1_fqT.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_6_1_ocy.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_7_1_DZ6.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_8_1_IOz.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_9_1_SiU.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_10_1_EFt.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/VVJets_1/patTuple_skim_11_1_TXD.root",
])
