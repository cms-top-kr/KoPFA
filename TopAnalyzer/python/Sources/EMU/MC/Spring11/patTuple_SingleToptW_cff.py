import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_1_3_M9S.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_2_3_jEI.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_3_3_Jta.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_4_3_6OA.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_5_3_uTx.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_6_3_RKa.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_7_3_fej.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_8_3_MpW.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_9_3_Tan.root",
])
