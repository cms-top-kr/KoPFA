import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_Pythia_1/patTuple_skim_1_2_kgr.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_Pythia_1/patTuple_skim_2_2_Uqw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_Pythia_1/patTuple_skim_3_2_7IB.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_Pythia_1/patTuple_skim_4_2_Xt0.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_Pythia_1/patTuple_skim_5_2_6vA.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_Pythia_1/patTuple_skim_6_2_szK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_Pythia_1/patTuple_skim_7_2_ats.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_Pythia_1/patTuple_skim_8_2_fXf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_Pythia_1/patTuple_skim_9_2_w3V.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110712_1/EE_TTbar_Pythia_1/patTuple_skim_10_2_uZ7.root",
])
