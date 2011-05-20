import FWCore.ParameterSet.Config as cms
import os

from PhysicsTools.PatAlgos.tools.pfTools import *

def addLooseLeptons(process):
        #set isolation for muon to be usef for jet clustering    
        process.pfIsolatedMuonsPFlow.combinedIsolationCut = cms.double(0.25)
        process.pfIsolatedElectronsPFlow.combinedIsolationCut = cms.double(0.25)

        #remove isolation for muon  
	process.pfIsolatedMuonsLoosePFlow = process.pfIsolatedMuonsPFlow.clone(
	    combinedIsolationCut = cms.double(999.0) 
	    )

	process.patMuonsLoosePFlow = process.patMuonsPFlow.clone(
	    pfMuonSource = cms.InputTag("pfIsolatedMuonsLoosePFlow")
	    )
	adaptPFMuons( process, process.patMuonsLoosePFlow, "PFlow")

        process.muonMatchLoosePFlow = process.muonMatchPFlow.clone(
            src = cms.InputTag("pfIsolatedMuonsLoosePFlow")
            )
        process.muonMatchPFlow.src = "pfIsolatedMuonsPFlow"

	process.selectedPatMuonsLoosePFlow = process.selectedPatMuonsPFlow.clone(
	    src = cms.InputTag("patMuonsLoosePFlow")
	    )

	process.pfIsolatedElectronsLoosePFlow = process.pfIsolatedElectronsPFlow.clone(
	    combinedIsolationCut = cms.double(999.0) 
	    )

	process.patElectronsLoosePFlow = process.patElectronsPFlow.clone(
	    pfElectronSource = cms.InputTag("pfIsolatedElectronsLoosePFlow")
	    )
	adaptPFElectrons( process, process.patElectronsLoosePFlow, "PFlow")

	process.selectedPatElectronsLoosePFlow = process.selectedPatElectronsPFlow.clone(
	    src = cms.InputTag("patElectronsLoosePFlow")
	    )

	process.looseLeptonSequence = cms.Sequence(
	    process.pfIsolatedMuonsLoosePFlow +
	    process.patMuonsLoosePFlow +
	    process.selectedPatMuonsLoosePFlow +    
	    process.pfIsolatedElectronsLoosePFlow +
	    process.patElectronsLoosePFlow +
	    process.selectedPatElectronsLoosePFlow
	    )

def topProjection(process, postfix=""):
	# top projections in PF2PAT:
	getattr(process,"pfNoPileUp"+postfix).enable = True
	getattr(process,"pfNoMuon"+postfix).enable = True
	getattr(process,"pfNoElectron"+postfix).enable = True
	getattr(process,"pfNoTau"+postfix).enable = False # to use tau-cleaned jet collection : True
	getattr(process,"pfNoJet"+postfix).enable = True


