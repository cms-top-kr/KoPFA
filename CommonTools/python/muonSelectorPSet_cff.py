import FWCore.ParameterSet.Config as cms
 
muonSelectorPSet = cms.PSet(

    # turn me to True to see the results of the muon selection:
    verbose = cms.untracked.bool( False ),

    #turn on to always calculate dxy and dz from global track
    calcDispFromGlobalTrack = cms.untracked.bool( False ),

    # keep these set to one, can test the VBTF or QTF cuts
    VBTF = cms.int32( 1 ),
    QTF = cms.int32( 1 ),
    TOPDIL = cms.int32( 1 ),
    
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



    # To use the QTF cuts, set the values as follows

    # Number of matches
    #nMatches = cms.int32(-1), #dummy

    # Matching for tracker muons
#    tmLastStationAngTight = cms.int32(1),
#
#    # chi2/Dof from the global fit (dummy)
#    globalNormChi2 = cms.double(20.),
#    # of valid muons hits in the global track (dummy)
#    muonHits = cms.int32(0),
#    
#
#    # of tracker track hits (uses >=)
#    trackerHits = cms.int32(12),
    # of valid pixel hits
    #pixelHits = cms.int32(-),  #dummy
#    # of pixed layers with valid hits
#    pixelLayersWithHits = cms.int32(1),
#    # chi2/Dof from the global fit
#    trackNormChi2 = cms.double(4.),
#
#    #transverse impact parameter
#    dxy = cms.double(3.),
#    # zed impact parameter 
#    dz = cms.double(30.),




    # isolation, kinematic cuts
    

    # relative isolation
    relIso = cms.double(999),

    eta = cms.double(2.4),
    pt = cms.double(20.),

 

    )


