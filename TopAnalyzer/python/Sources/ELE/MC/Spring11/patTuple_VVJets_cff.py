import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_1_1_K7y.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_2_1_D7G.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_3_1_Caf.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_4_1_rlz.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_5_1_uzn.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_6_1_bEr.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_7_1_7PP.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_8_1_BJs.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_9_1_cvC.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_10_1_ILr.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/VVJets_1/patTuple_skim_11_1_5Kz.root",
])
