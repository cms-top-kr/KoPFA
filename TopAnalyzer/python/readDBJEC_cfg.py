import FWCore.ParameterSet.Config as cms

process = cms.Process("JEC")

#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = cms.string( 'GR_R_42_V12::All' )

process.load("CondCore.DBCommon.CondDBCommon_cfi")
process.jec = cms.ESSource("PoolDBESSource",
      DBParameters = cms.PSet(
        messageLevel = cms.untracked.int32(0)
        ),
      timetype = cms.string('runnumber'),
      toGet = cms.VPSet(
      cms.PSet(
            record = cms.string('JetCorrectionsRecord'),
            tag    = cms.string('JetCorrectorParametersCollection_Jec11V2_AK5PF'),
            label  = cms.untracked.string('AK5PF')
            )
      ),
      ## here you add as many jet types as you need (AK5Calo, AK5JPT, AK7PF, AK7Calo, KT4PF, KT4Calo)
      connect = cms.string('sqlite:Jec11V2.db')
)
# Add an es_prefer statement to get your new JEC constants from the sqlite file, rather than from the global tag
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')

##-------------------- Import the JEC services -----------------------
#process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
##-------------------- Import the Jet RECO modules -----------------------
#process.load('RecoJets.Configuration.RecoPFJets_cff')
##-------------------- Turn-on the FastJet density calculation -----------------------
#process.kt6PFJets.doRhoFastjet = True
##-------------------- Turn-on the FastJet jet area calculation for your favorite algorithm -----------------------
#process.ak5PFJets.doAreaFastjet = True
##-------------------- Include in the path the jet reconstruction  --------------------------------
#process.p = cms.Path(process.kt6PFJets * process.ak5PFJets)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
    )


process.source = cms.Source("EmptySource")

process.readAK5PF = cms.EDAnalyzer('JetCorrectorDBReader', 
        payloadName    = cms.untracked.string('AK5PF'),
        printScreen    = cms.untracked.bool(False),
        createTextFile = cms.untracked.bool(True),
        globalTag      = cms.untracked.string('Jec11_V2') 
  )

process.p = cms.Path(process.readAK5PF)

