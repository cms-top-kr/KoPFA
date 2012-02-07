import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_3_1_66p.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_9_0_vP3.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_12_0_YF4.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_21_0_7G6.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_26_0_lDf.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_30_0_Qfn.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_78_0_smR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_84_0_94o.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_86_1_UwB.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_91_1_Zzy.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_108_0_Gxh.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_110_0_kxm.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_122_0_KON.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_129_0_sA1.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_131_1_2l2.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_132_0_aTR.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_135_0_vva.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_141_0_KKu.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_150_0_Rew.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_160_0_gYw.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_161_1_wb3.root",
#"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_162_0_5ZK.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_164_0_jwJ.root",
"rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MC/20120127_2/TTbarTuneZ2_2/patTuple_skim_158_0_RJh.root",
])
