import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/SingleTopA_tW_1/patTuple_skim_1_3_Bos.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/SingleTopA_tW_1/patTuple_skim_2_1_CWf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/SingleTopA_tW_1/patTuple_skim_3_0_zXl.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/SingleTopA_tW_1/patTuple_skim_4_0_XK8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/SingleTopA_tW_1/patTuple_skim_5_2_vDJ.root",
])
