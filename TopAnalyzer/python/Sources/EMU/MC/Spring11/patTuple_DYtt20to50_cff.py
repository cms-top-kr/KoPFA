################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYtt20to50_1
### File index = 2
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYtt20to50_1
### File index = 2
################################################################################
################################################################################
### Duplicated file entry found in the directory /castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYtt20to50_1
### File index = 3
################################################################################
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYtt20to50_1/patTuple_skim_1_1_EBO.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYtt20to50_1/patTuple_skim_2_5_Ldd.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYtt20to50_1/patTuple_skim_3_5_Nte.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYtt20to50_1/patTuple_skim_4_2_MiS.root",
    "rfio:/castor/cern.ch/cms/store/user/jhgoh/TopAnalysis/pat/MuEl/MC/20110620_2/DYtt20to50_1/patTuple_skim_5_2_wv8.root",
])
