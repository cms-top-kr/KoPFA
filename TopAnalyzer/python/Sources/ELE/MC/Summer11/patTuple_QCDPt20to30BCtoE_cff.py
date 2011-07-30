import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt20to30BCtoE_1/patTuple_skim_1_2_WpD.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt20to30BCtoE_1/patTuple_skim_2_2_LyS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt20to30BCtoE_1/patTuple_skim_3_0_dgY.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt20to30BCtoE_1/patTuple_skim_4_0_PCZ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt20to30BCtoE_1/patTuple_skim_5_0_4Ud.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt20to30BCtoE_1/patTuple_skim_6_0_2gy.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20110726_1/QCD_Pt20to30BCtoE_1/patTuple_skim_7_1_E8J.root",
])
