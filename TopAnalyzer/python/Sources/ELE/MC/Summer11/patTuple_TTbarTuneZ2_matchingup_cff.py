import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_matchingup_4/patTuple_skim_1_3_Kjg.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_matchingup_4/patTuple_skim_2_1_RIF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_matchingup_4/patTuple_skim_3_1_zgY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_matchingup_4/patTuple_skim_4_1_rBC.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_matchingup_4/patTuple_skim_5_1_Dy3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_matchingup_4/patTuple_skim_6_1_tVS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111124_1/TTbarTuneZ2_matchingup_4/patTuple_skim_7_1_GDr.root",
])
