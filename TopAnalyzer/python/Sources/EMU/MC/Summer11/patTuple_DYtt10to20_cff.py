import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_10to20_1/patTuple_skim_1_1_KU6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_10to20_1/patTuple_skim_2_1_i96.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_10to20_1/patTuple_skim_3_1_MPu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_10to20_1/patTuple_skim_4_1_KQM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYtt_10to20_1/patTuple_skim_5_2_ELx.root",
])
