import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYee_10to20_1/patTuple_skim_1_1_gBH.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYee_10to20_1/patTuple_skim_2_1_cE8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYee_10to20_1/patTuple_skim_3_2_3Of.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYee_10to20_1/patTuple_skim_4_2_nQh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYee_10to20_1/patTuple_skim_5_1_Kcv.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYee_10to20_1/patTuple_skim_6_1_gCD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYee_10to20_1/patTuple_skim_7_1_SEI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYee_10to20_1/patTuple_skim_8_1_bpS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110720_2/DYee_10to20_1/patTuple_skim_9_1_WLJ.root",
])
