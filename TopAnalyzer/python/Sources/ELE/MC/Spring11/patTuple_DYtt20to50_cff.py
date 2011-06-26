################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/DYtt20to50_1
### File index = 3
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/DYtt20to50_1
### File index = 4
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/DYtt20to50_1
### File index = 5
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/DYtt20to50_1/patTuple_skim_1_1_IHG.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/DYtt20to50_1/patTuple_skim_2_5_0Dv.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/DYtt20to50_1/patTuple_skim_3_5_OIK.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/DYtt20to50_1/patTuple_skim_4_5_dqX.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/ElEl/MC/20110620_2/DYtt20to50_1/patTuple_skim_5_5_qix.root",
])
