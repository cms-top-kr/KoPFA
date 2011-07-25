import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/ZPrime_M750W075_1/patTuple_skim_1_1_FkB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/ZPrime_M750W075_1/patTuple_skim_2_1_W1H.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/ZPrime_M750W075_1/patTuple_skim_3_2_KGq.root",
])
