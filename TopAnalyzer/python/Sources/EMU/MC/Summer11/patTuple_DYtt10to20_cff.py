import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_10to20_1/patTuple_skim_1_1_1ZS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_10to20_1/patTuple_skim_2_1_bsj.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_10to20_1/patTuple_skim_3_1_ryy.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_10to20_1/patTuple_skim_4_1_fZc.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110712_1/ME_DYtt_10to20_1/patTuple_skim_5_0_i9C.root",
])
