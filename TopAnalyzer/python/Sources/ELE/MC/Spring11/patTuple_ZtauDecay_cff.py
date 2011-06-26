import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_1_1_s70.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_2_1_koD.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_3_1_ofT.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_4_1_k0D.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_5_1_i7j.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_6_1_ye0.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_7_1_Vgl.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_8_1_KHm.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_9_1_Tag.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_10_1_gRu.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_11_1_baw.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_12_1_DwN.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_13_1_ere.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_14_1_LcV.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_15_1_8lQ.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_16_1_ycU.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_17_1_baD.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_18_1_wcI.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_19_1_oqh.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/ZJets_1/patTuple_skim_20_1_wPo.root",
])
