import FWCore.ParameterSet.Config as cms

process = cms.Process("Iso")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(
   'file:/afs/cern.ch/user/t/tjkim/public/forColin/pf2pat_iso.root',
    )
)

#process.load("PFAnalyses.Z.RD.Wenu_highpt_Mt50_latest_cff")
#process.load("PFAnalyses.Z.MC.Wenu_patTuple_pythia_cff")

#process.load("PFAnalyses.Z.RD.Wmunu_PFIso_cff")
#process.load("PFAnalyses.Z.MC.Wmunu_MuonFilter_cff")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('isoNtuple.root')
)

process.load("PFAnalyses.CommonTools.RandomCone_cfi")
process.load("KoPFA.IsoAnalyzer.PATLeptonSelector_cfi")
process.load("KoPFA.IsoAnalyzer.IsoAnalysis_cfi")
process.load("KoPFA.IsoAnalyzer.Isolation_cfi")
process.load("KoPFA.IsoAnalyzer.WFilter_cff")
process.load("KoPFA.CommonTools.VertexFilter_cfi")
process.WenuMtCut.minMt = 50 
#process.WenuMtCut.minMt = 0
process.WenuMtCut.mindphi = 0.0
process.WenuMtCut.maxdphi = 0.0 
process.WmunuMtCut.minMt = 0.0
process.WmunuMtCut.mindphi = 0.0
process.WmunuMtCut.maxdphi = 0.0

#process.p = cms.Path(process.RandomIso)
process.pMuon = cms.Path(
                         process.PatMuonsPFlowIso*
                         process.selectedPatMuonsPFlowIso*
                         process.patMuonFilter*
                         process.WmunuMtCut*
                         process.VertexFilter*
                         process.randomCones*
                         process.MuonIso*
                         process.RandomIsoForMuon*
                         process.MuonIsoAnal
                        )
process.pElec = cms.Path(
                         process.PatElectronsPFlowIso*
                         process.selectedPatElectronsPFlowIso*
                         process.patElectronFilter*
                         process.WenuMtCut*
                         process.VertexFilter*
                         process.randomCones*
                         process.ElecIso*
                         process.RandomIsoForElec*
                         process.ElecIsoAnal
                        )

process.schedule = cms.Schedule(
                        # process.p, 
                        # process.pMuon, 
                         process.pElec
                        )

