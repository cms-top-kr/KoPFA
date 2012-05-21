import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("Ana")

process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/users/jhgoh/data/CMS/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola_GenParticles/genskim_0.root',
        'file:/users/jhgoh/data/CMS/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola_GenParticles/genskim_1.root',
        'file:/users/jhgoh/data/CMS/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola_GenParticles/genskim_2.root',
        'file:/users/jhgoh/data/CMS/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola_GenParticles/genskim_3.root',
        'file:/users/jhgoh/data/CMS/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola_GenParticles/genskim_4.root',
        'file:/users/jhgoh/data/CMS/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola_GenParticles/genskim_5.root',
        'file:/users/jhgoh/data/CMS/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola_GenParticles/genskim_6.root',
        'file:/users/jhgoh/data/CMS/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola_GenParticles/genskim_7.root',
        'file:/users/jhgoh/data/CMS/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola_GenParticles/genskim_8.root',
        'file:/users/jhgoh/data/CMS/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola_GenParticles/genskim_9.root',
    ),
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 10000 ) )
process.MessageLogger.cerr.FwkReport.reportEvery = 5000
#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.load("KoPFA.GeneratorTools.genBJetSelector_cfi")
process.genJets = cms.EDFilter("GenJetSelector",
    src = cms.InputTag("ak5GenJets"),
    cut = cms.string("pt >= 30 && abs(eta) <= 2.4"),
)
process.genBJets.genJet = "genJets"

#process.genTopBquarks = cms.EDProducer("GenParticleMerger",
#    src = cms.VInputTag("genTTbar:bA", "genTTbar:bB"),
##)
#process.genTopBJets = process.genBJets.clone()
#process.genTopBJets.genParticle = "genTopBquarks"
#process.genTopBJets.matchAlgos = ["BquarkOverlap"]

process.genTTbar = cms.EDProducer("TopGenParticleProducer",
    src = cms.InputTag("genParticles"),
    doHist = cms.untracked.bool(True),
)

process.genLeptons = cms.EDFilter("GenParticleSelector",
    src = cms.InputTag("genParticles"),
    cut = cms.string("(abs(pdgId) == 11 || abs(pdgId) == 13) && pt > 20 && abs(eta) < 2.4"),
)
process.genHardLepPos = cms.EDFilter("GenParticleSelector",
    src = cms.InputTag("genLeptons"),
    cut = cms.string("status == 3 && charge > 0"),
)
process.genHardLepNeg = process.genHardLepPos.clone(cut = cms.string("status == 3 && charge < 0"))
process.genSoftLepPos = process.genHardLepPos.clone(cut = cms.string("status == 1 && charge > 0"))
process.genSoftLepNeg = process.genHardLepPos.clone(cut = cms.string("status == 1 && charge < 0"))

process.genTopLepPos = process.genLeptons.clone(src = cms.InputTag("genTTbar:lA"))
process.genTopLepNeg = process.genLeptons.clone(src = cms.InputTag("genTTbar:lB"))

process.load("KoPFA.TTbarMassAlgos.ttbarMassAnalyzer_cfi")
process.genMassHardLepJets = process.genMassLLJJMet.clone()
process.genMassHardLepJets.lepton1 = "genHardLepNeg"
process.genMassHardLepJets.lepton2 = "genHardLepPos"
process.genMassHardLepJets.jet = "genJets"

process.genMassHardLepBJets = process.genMassHardLepJets.clone()
process.genMassHardLepBJets.jet = "genBJets"

process.genMassSoftLepJets = process.genMassHardLepJets.clone()
process.genMassSoftLepJets.lepton1 = "genSoftLepNeg"
process.genMassSoftLepJets.lepton2 = "genSoftLepPos"

process.genMassSoftLepBJets = process.genMassSoftLepJets.clone()
process.genMassSoftLepBJets.jet = "genBJets"

process.load("TopQuarkAnalysis.TopKinFitter.TtFullLepKinSolutionProducer_cfi")
process.kinSolutionTtFullLepEvent.jets = "genBJets"
process.kinSolutionTtFullLepEvent.electrons = "genSoftLepPos"
process.kinSolutionTtFullLepEvent.muons = "genSoftLepNeg"
process.kinSolutionTtFullLepEvent.mets = "genMETTrue"
process.kinSolutionTtFullLepEvent.mumuChannel = True
process.kinSolutionTtFullLepEvent.searchWrongCharge = False

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('hMass.root')
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("out.root"),
    outputCommands = cms.untracked.vstring(
        "drop *",
        "keep *_*_*_Ana",
    ),
)

process.p = cms.Path(
    process.genTTbar
  #* process.genTopBquarks
  + process.genLeptons 
  #* process.genHardLepPos + process.genHardLepNeg 
  + process.genSoftLepPos + process.genSoftLepNeg
  #+ process.genTopLepPos + process.genTopLepNeg
  + process.genJets * process.genBJets #+ process.genTopBJets
  #* process.genMassHardLepJets + process.genMassHardLepBJets
  + process.genMassSoftLepJets + process.genMassSoftLepBJets
  #+ process.kinSolutionTtFullLepEvent
)

#process.outPath = cms.EndPath(process.out)

