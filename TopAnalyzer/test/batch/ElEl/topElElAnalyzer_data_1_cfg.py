from KoPFA.TopAnalyzer.topElElAnalyzer_cff import process

import FWCore.ParameterSet.Config as cms

process.load("PFAnalyses.TTbarDIL.Sources.ELE.RD.patTuple_Run2010A_Sep17ReReco_cff")
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )
#process.hltHighLevel.HLTPaths = cms.vstring("HLT_Ele10_LW_L1R")
#process.source = cms.Source("PoolSource",
  # replace 'myfile.root' with the source file you want to use
#  noEventSort = cms.untracked.bool(True),
#  duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
#  fileNames = cms.untracked.vstring(
#      'file:/afs/cern.ch/user/t/tjkim/scratch0/CMSSW_3_8_4_patch2/src/PFAnalyses/TTbarDIL/prod/ELE/RD/patTuple_skim.root'
#       'rfio:///castor/cern.ch/user/t/tjkim/SDMUONFILTER/July19th_v4/Run2010A-PromptReco-v4/patTuple_muon_22_0_Qie.root'
#    'rfio:/castor/cern.ch/user/t/tjkim/MUSKIM/Oct6/Run2010A-Sep17ReReco_v2/patTuple_skim_73_1_PoI.root',
#    'rfio:/castor/cern.ch/user/t/tjkim/MUSKIM/Oct6/Run2010A-Sep17ReReco_v2/patTuple_skim_73_1_PoI.root'
#  )
#)

