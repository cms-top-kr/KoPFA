import FWCore.ParameterSet.Config as cms
import sys, os

#suffix = "FullLeptMGDecays"
suffix = "MassiveBinDECAY"
dataCatalogue = "TTJets_%s.txt" % suffix

process = cms.Process("RIVET")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000000))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(),
)

if os.path.exists(dataCatalogue):
    for line in open(dataCatalogue).readlines():
        line = line.strip()
        if line == "" or line[0] == '#': continue
        process.source.fileNames.append(line)
else:
    cmgBaseDir = '/store/cmst3/user/cmgtools/CMG'
    sampleName = '/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/AODSIM'
    cmgFullVer = 'V5_B/PAT_CMG_V5_13_0'
    for i in range(1,1184):
        process.source.fileNames.append("%s%s/%s/patTuple_%d.root" % (cmgBaseDir, sampleName, cmgFullVer, i))

### Select dilepton decay only
process.topDecayGenFilter = cms.EDFilter('TopDecayGenFilter',
  applyFilter =  cms.untracked.bool(True),
  genParticlesLabel = cms.InputTag('genParticles'),
  allHadronic = cms.bool(False),
  semiLeptonic = cms.bool(False),
  semiLeptonicMuon = cms.bool(False),
  semiLeptonicElectron = cms.bool(False),
  semiLeptonicTau = cms.bool(False),
  diLeptonic = cms.bool(True),
  diLeptonicMuoMuo = cms.bool(True),
  diLeptonicEleEle = cms.bool(True),
  diLeptonicMuoEle = cms.bool(True),
  diLeptonicTauMuo = cms.bool(False),
  diLeptonicTauEle = cms.bool(False),
  diLeptonicTauTau = cms.bool(False),
)

### Add ghost B hadron
process.load('KoPFA.CommonTools.genJetsWithGhostBHadrons_cff')
process.genParticlesWithGhostB.userPdgId = 7

### Rebuild HepMC
#process.load('Configuration.GenProduction.EightTeV.Hadronizer_MgmMatchTuneZ2star_8TeV_madgraph_tauola_cff')
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load('KoPFA.RivetAnalyzer.GenParticles2HepMC_cfi')
process.generator.genParticles = 'genParticlesWithGhostB'

## Setup RIVET analyzer
process.load("GeneratorInterface.RivetInterface.rivetAnalyzer_cfi")

process.p = cms.Path(process.rivetAnalyzer)
process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_TOP_12_028')
process.rivetAnalyzer.CrossSection = cms.double(13.43)
#process.rivetAnalyzer.CrossSection = cms.double(165)
process.rivetAnalyzer.OutputFile = '%s.aida' % suffix

process.p = cms.Path(process.topDecayGenFilter + process.genParticlesWithGhostB * process.generator * process.rivetAnalyzer)
#process.p = cms.Path(process.generator * process.rivetAnalyzer)

