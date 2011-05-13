import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_1_1_gFj.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_2_1_DPy.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_3_1_go4.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_4_1_mOQ.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_5_1_o1O.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_6_1_U9v.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_7_1_QF8.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_8_1_dPg.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_9_1_Zpa.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_10_1_OWE.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_11_1_EmP.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_12_1_ccs.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_13_1_v9E.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_14_1_iSQ.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_15_1_XhN.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_16_1_kgP.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_17_1_4QH.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_18_1_KML.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_19_1_XOD.root',
    'rfio:/castor/cern.ch/user/j/jhgoh/TopAnalysis/pf2pat/ElEl/MC/20110512/TTbarTuneZ2/patTuple_skim_20_1_UND.root',
])
