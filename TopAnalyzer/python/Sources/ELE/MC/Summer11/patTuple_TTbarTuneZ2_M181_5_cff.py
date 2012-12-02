import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M181_5_4/patTuple_skim_1_2_ni3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M181_5_4/patTuple_skim_2_0_xgW.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M181_5_4/patTuple_skim_3_0_C4a.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M181_5_4/patTuple_skim_4_0_GkZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M181_5_4/patTuple_skim_5_0_Ke8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M181_5_4/patTuple_skim_6_0_XWK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M181_5_4/patTuple_skim_7_0_2Jo.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M181_5_4/patTuple_skim_8_0_34F.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M181_5_4/patTuple_skim_9_0_tiH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_M181_5_4/patTuple_skim_10_0_Erv.root",
])
