import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt10to20_1/patTuple_skim_1_5_3zS.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt10to20_1/patTuple_skim_3_5_J2e.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt10to20_1/patTuple_skim_4_5_S9L.root",
"rfio:/castor/cern.ch/user/b/bhlee/2011mc/Summer11/MU/Jul14/DYtt10to20_1/patTuple_skim_5_0_KwT.root",
])
