import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M161_5_1/patTuple_skim_1_2_1pY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M161_5_1/patTuple_skim_2_0_dTb.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M161_5_1/patTuple_skim_3_1_W0Q.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M161_5_1/patTuple_skim_4_2_7TT.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M161_5_1/patTuple_skim_5_2_U3d.root",
])
