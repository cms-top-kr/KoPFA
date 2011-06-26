import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_1_1_qFb.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_2_1_XDi.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_3_1_jUV.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_4_1_lhD.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_5_1_kqK.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_6_1_Lmo.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_7_1_WTa.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_8_1_skV.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_9_1_IoD.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_10_1_ZWi.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_11_1_XjA.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_12_2_k7i.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_13_1_O7S.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_14_1_Kbz.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_15_1_0IR.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_16_1_Bjm.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_17_1_hAe.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_18_1_7mO.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_19_1_pim.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_20_1_1Rl.root",
])
