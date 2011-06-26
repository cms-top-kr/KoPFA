import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_1_1_Ob0.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_2_1_LOP.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_3_1_7DM.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_4_1_dzB.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_5_1_k0i.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_6_1_kX4.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_7_1_JHy.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_8_1_4Lr.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_9_1_Nrp.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_10_1_imf.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_11_1_UX1.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_12_1_mBB.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_13_1_Vmr.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_14_1_Emi.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_15_1_sYs.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_16_1_HbD.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_17_1_Yg4.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_18_1_9DK.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_19_1_Vux.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuMu/MC/20110620_2/TTbarTuneZ2_1/patTuple_skim_20_1_bRg.root",
])
