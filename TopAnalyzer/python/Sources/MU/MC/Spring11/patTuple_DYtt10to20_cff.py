import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYtt10to20_1/patTuple_skim_1_1_Sdi.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYtt10to20_1/patTuple_skim_2_1_Zgp.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYtt10to20_1/patTuple_skim_3_1_GUa.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/DYtt10to20_1/patTuple_skim_4_1_Tik.root",
])
