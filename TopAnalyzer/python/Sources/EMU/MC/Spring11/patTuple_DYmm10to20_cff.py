import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYmm10to20_1/patTuple_skim_1_1_78Y.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYmm10to20_1/patTuple_skim_2_1_qYM.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYmm10to20_1/patTuple_skim_3_1_1Cl.root",
])
