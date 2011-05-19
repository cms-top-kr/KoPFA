
"""
The default muon isolation selection for the PatMuonIsolationSelector

Note that for each IsoSelector two types of
isolation are available: Rel (divided by pt of isolated object)
and Abs, so the full labels are: combinedRel,
combinedAbs and so on.
"""
import FWCore.ParameterSet.Config as cms
 
muonIsoSelectorPSet =  cms.PSet(
    verbose=cms.untracked.bool( False ),
    isolationCuts=cms.VPSet(
    cms.PSet(
      name=cms.string("combined"),
      absoluteCut=cms.double(5),
      relativeCut=cms.double(0.15),
      chargedWeight=cms.double(1),
      photonWeight=cms.double(1),
      neutralWeight=cms.double(0.33)
      ),
    cms.PSet(
      name=cms.string("looseHigh"),
      absoluteCut=cms.double(5),
      relativeCut=cms.double(0.3),
      chargedWeight=cms.double(1),
      photonWeight=cms.double(1),
      neutralWeight=cms.double(0.33)
      ),
    cms.PSet(
      name=cms.string("looseLow"),
      absoluteCut=cms.double(5),
      relativeCut=cms.double(0.2),
      chargedWeight=cms.double(1),
      photonWeight=cms.double(1),
      neutralWeight=cms.double(0.33)
      ),
    #this is the optimized PF Isolation from Mike Bachtis. See Task:15012   
    cms.PSet(
      name=cms.string("pfOptimized"),
      absoluteCut=cms.double(9999.),#ignore the absolute cut
      relativeCut=cms.double(0.21),
      chargedWeight=cms.double(1.),
      photonWeight=cms.double(1.),
      neutralWeight=cms.double(1.)
      )
             ),
    ## each IsoPar has a coneSize parameter (radius of the cone inside which
    ## the isolation is computed) plus a VPSet called vetoes, made of any of the following
    ## vetoes: ThresholdVeto, ConeVeto, RectangularEtaPhiVeto (more vetoes can be implemented if needed)
    ## look at DataFormats/RecoCandidate/src/IsoDepositVetos.cc for their meaning.
    chargedIsoPar=cms.PSet(
      coneSize=cms.double(0.4),
      vetoes=cms.VPSet()#no veto
      ),

    neutralIsoPar=cms.PSet(
      coneSize=cms.double(0.4),
      vetoes=cms.VPSet(
        cms.PSet(
           type = cms.string("ThresholdVeto"),
           threshold = cms.double(0.5)
        ),
      )
    ),

    photonsIsoPar=cms.PSet(
      coneSize=cms.double(0.4),
      vetoes=cms.VPSet(
        cms.PSet(
           type = cms.string("ThresholdVeto"),
           threshold = cms.double(0.5)
        )
      )
    ) 
 )
