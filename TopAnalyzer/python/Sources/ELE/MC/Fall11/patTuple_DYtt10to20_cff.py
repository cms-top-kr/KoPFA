import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_3/patTuple_skim_1_3_Kjq.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_1/patTuple_skim_2_3_Tf6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_3/patTuple_skim_3_1_bfK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_3/patTuple_skim_4_0_lAo.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_1/patTuple_skim_4_0_xwM.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_1/patTuple_skim_6_1_dlV.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_1/patTuple_skim_10_2_h3Z.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_3/patTuple_skim_13_0_NGs.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_1/patTuple_skim_13_1_zlh.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_1/patTuple_skim_16_0_CzO.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_1/patTuple_skim_17_0_eiL.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_3/patTuple_skim_17_0_oOc.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_1/patTuple_skim_18_2_48v.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_3/patTuple_skim_18_1_ztS.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_1/patTuple_skim_20_1_RDF.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_3/patTuple_skim_20_0_Gw6.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_1/patTuple_skim_23_3_aL2.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20111213_1/DYtt10to20_3/patTuple_skim_23_1_eLt.root",
])
