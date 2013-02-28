import FWCore.ParameterSet.Config as cms

from KoPFA.CommonTools.PileUpWeight_cff import *

PUweight = cms.EDProducer("EventWeightProducer",
  PileUpRD = PileUpRD2011,
  PileUpRDup = PileUpRD2011UP,
  PileUpRDdn = PileUpRD2011DN,
  PileUpMC = Fall11,
  #PileUpRD = PileUpRD2012,
  #PileUpRDPUup = PileUpRD2012UP,
  #PileUpRDPUdn = PileUpRD2012DN,
  #PileUpMC = Summer12,
)
