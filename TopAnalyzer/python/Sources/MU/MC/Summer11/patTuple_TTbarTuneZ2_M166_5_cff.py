import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M166_5_1/patTuple_skim_1_3_SaB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M166_5_1/patTuple_skim_2_2_lH2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M166_5_1/patTuple_skim_3_1_g7h.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M166_5_1/patTuple_skim_4_4_Qd1.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M166_5_1/patTuple_skim_5_1_88Q.root",
])
