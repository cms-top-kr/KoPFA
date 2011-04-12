import FWCore.ParameterSet.Config as cms

PUweight = cms.EDProducer("EventWeightProducer",
    PUweight = cms.vdouble(0.24698,0.878399,1.62972,1.74644,1.48563,0.999695,0.740525,0.457214,0.268234,0.184943,0.127889,0.0274048,0.0959167,0.383667),
    PUdefault = cms.double(0.0),
)
