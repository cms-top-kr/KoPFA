import FWCore.ParameterSet.Config as cms
 
muonSelectorPSet = cms.PSet(

    # turn me to True to see the results of the muon selection:
    verbose = cms.untracked.bool( False ),

    # keep these set to one, can test the VBTF or QTF cuts
    VBTF = cms.int32( 1 ),
    QTF = cms.int32( 1 ),
    TOP = cms.int32( 1 ),

    # Note setting to zero, does not turn these boolean cuts off, but rather requires it to be false
    # Use ignoreCut to turn it off
    isGlobalMuon = cms.int32( 1 ),
    isTrackerMuon = cms.int32( 1 ),

    # To use the VBTF cuts, set the values as follows

    # Number of matches
    nMatches = cms.int32(2), #nMatches >= 2
    
    # Matching for tracker muons (dummy)
    tmLastStationAngTight = cms.int32(1),

    # chi2/Dof from the global fit
    globalNormChi2 = cms.double(10.),
    # of valid muons hits in the global track
    muonHits = cms.int32(0),

    # of tracker track hits
    trackerHits = cms.int32(11),
    # of valid pixel hits
    pixelHits = cms.int32(0),  #pixelHits >= 0
    # of pixel layers with valid hits
    pixelLayersWithHits = cms.int32(-1),
    # chi2/Dof from the global fit
    trackNormChi2 = cms.double(9999.),
    #transverse impact parameter
    dxy = cms.double(0.02),
    # zed impact parameter 
    dz = cms.double(9999.),

    # To use the TOP cuts, set the values as follows

    # Matching for tracker muons (dummy)
    globalMuonPromptTight = cms.int32(1),
    # chi2/Dof from the global fit
    #globalNormChi2 = cms.double(10.),
    # of tracker track hits
    #trackerHits = cms.int32(10),
    #transverse impact parameter
    #dxy = cms.double(0.02),
    # zed impact parameter 
    #dz = cms.double(9999.),


    # isolation, kinematic cuts
    

    # relative isolation
    relIso = cms.double(999),

    eta = cms.double(2.5),
    pt = cms.double(20.),

    )

