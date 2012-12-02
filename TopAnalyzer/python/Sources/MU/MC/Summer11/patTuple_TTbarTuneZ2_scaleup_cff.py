import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_scaleup_1/patTuple_skim_1_1_Nwa.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_scaleup_1/patTuple_skim_2_3_Lyq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_scaleup_1/patTuple_skim_3_1_7RQ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_scaleup_1/patTuple_skim_4_2_86A.root",
])
