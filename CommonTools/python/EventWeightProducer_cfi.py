import FWCore.ParameterSet.Config as cms

from KoPFA.CommonTools.PileUpWeight_cff import *

PUweight = cms.EDProducer("EventWeightProducer",
  PileUpRD = PileUpRD2011,
  PileUpMC = Fall11,
)
