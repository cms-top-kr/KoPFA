import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

import os
if 'MODE' not in os.environ:
    mode = 'MC'
else:
    mode = os.environ['MODE']

from KoPFA.TagProbe.common_PDFs_cff import *

def tnpEffPSet(categories):
    effSet = cms.PSet()

    for category in categories:
        setattr(effSet, category+"_pt", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass","weight"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(20, 25, 30, 35, 40, 50, 150),
                pt = cms.vdouble(20, 30, 40, 50, 150),
            ),
            BinToPDFmap = cms.vstring("vpvPlusQuadratic") #vpvPlusExpo")
        ))

        setattr(effSet, category+"_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass","weight"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.0, 0.5, 1.0, 1.4, 1.6, 2.0, 2.4)
                #abseta = cms.vdouble(0.0, 1.5, 2.4)
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo")
        ))

        setattr(effSet, category+"_pt_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass","weight"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(20, 25, 30, 35, 40, 50, 150),
                pt = cms.vdouble(20, 30, 40, 50, 150),
                abseta = cms.vdouble(0.0, 1.4, 1.6, 2.4)
                #abseta = cms.vdouble(0.0, 1.5, 2.4)
            ),
            BinToPDFmap = cms.vstring("vpvPlusQuadratic") #vpvPlusExpo")
        ))

        setattr(effSet, category+"_event_nPV", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass","weight"),
            BinnedVariables = cms.PSet(
                event_nPV = cms.vdouble(0, 4, 7, 10, 13, 16, 30),
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo")
        ))

    return effSet

process.tnpFit = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    InputFileNames = cms.vstring("rfio:/castor/cern.ch/user/j/jkim/TopAna/TnpTree/Fall11/DYJetsToLL_IsoMu24_relIsoTag_wmass/tagprob_MC_tightmu_relIsoTag_12files.root"),
    InputDirectoryName = cms.string("tnpTreeIso"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("result_Iso_all_%s.root" % mode),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
    WeightVariable = cms.string("weight"),
    Variables = cms.PSet(
        #mass = cms.vstring("Tag-Probe mass", "50.0", "130.0", "GeV/c^{2}"),
        mass = cms.vstring("Tag-Probe mass", "60.0", "140.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        eta = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
        weight = cms.vstring("Weight", "0.0","2.0", ""),
        event_nPV = cms.vstring("event_nPV", "0", "30", "")
    ),

    Categories = cms.PSet(
        Iso20 = cms.vstring("Iso20", "dummy[pass=1,fail=0]"),
        Iso20dbeta = cms.vstring("Iso20dbeta", "dummy[pass=1,fail=0]"),
    ),

    PDFs = basicPDFs,

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),

    Efficiencies = tnpEffPSet(["Iso20","Iso20dbeta"]),
)

process.fit = cms.Path(
  process.tnpFit
)

