import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_1_1_WH5.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_2_1_cRY.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_3_1_y0h.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_4_1_i8D.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_5_1_jf2.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_6_1_b7r.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_7_1_Rt2.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_8_1_H0Z.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/SingleTop_tW_1/patTuple_skim_9_1_JP6.root",
])
