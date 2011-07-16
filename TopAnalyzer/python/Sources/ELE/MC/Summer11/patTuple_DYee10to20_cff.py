################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_DYee_10to20_2
### File index = 5
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_DYee_10to20_2/patTuple_skim_1_1_7A8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_DYee_10to20_2/patTuple_skim_2_1_OOz.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_DYee_10to20_2/patTuple_skim_3_1_FK3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_DYee_10to20_2/patTuple_skim_4_1_yZF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_DYee_10to20_2/patTuple_skim_5_1_KyF.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_DYee_10to20_2/patTuple_skim_6_1_jSI.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_DYee_10to20_2/patTuple_skim_7_1_Frr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_DYee_10to20_2/patTuple_skim_8_1_61C.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_DYee_10to20_2/patTuple_skim_9_1_8rg.root",
])
