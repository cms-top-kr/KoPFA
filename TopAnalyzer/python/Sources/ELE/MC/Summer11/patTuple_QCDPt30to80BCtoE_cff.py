import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt30to80BCtoE_1/patTuple_skim_1_1_kgL.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt30to80BCtoE_1/patTuple_skim_2_0_GW8.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt30to80BCtoE_1/patTuple_skim_3_0_z8W.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt30to80BCtoE_1/patTuple_skim_4_0_LmZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt30to80BCtoE_1/patTuple_skim_5_1_A3v.root",
])
