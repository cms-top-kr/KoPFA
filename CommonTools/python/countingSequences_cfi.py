import FWCore.ParameterSet.Config as cms
#Create a sequebnce that saves an event counter in the Run Info
#We can use it later to monitor the cut selection and to make
#event weight in MC


from DQMServices.Core.DQM_cfg import *
from DQMServices.Components.DQMEnvironment_cfi import *
from DQMServices.Components.MEtoEDMConverter_cfi import *
from DQMServices.Components.EDMtoMEConverter_cfi import *

saveHistosInRunInfo   = cms.Sequence(MEtoEDMConverter)
loadHistosFromRunInfo = cms.Sequence(EDMtoMEConverter)



startupCounter = cms.EDProducer('EventNumCounter',
                                        name = cms.string("initialEvents")
)

startupSequence = cms.Sequence(startupCounter)

finalCounter = cms.EDProducer('EventNumCounter',
                                        name = cms.string("finalEvents")
)

finalSequence = cms.Sequence(finalCounter)


