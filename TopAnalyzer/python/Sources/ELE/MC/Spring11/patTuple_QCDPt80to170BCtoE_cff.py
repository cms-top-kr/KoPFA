import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)

readFiles.extend([
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_1_1_g2m.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_2_1_cdb.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_3_1_zWg.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_4_1_CNR.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_5_2_QCc.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_6_0_Jy1.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_7_1_e84.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_8_2_NTm.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_9_0_Hus.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_10_0_DJh.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_11_2_Aur.root',
    'rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl_/MC/20110601_1/QCDPt80to170BCtoE/patTuple_skim_12_0_LBf.root',
])
