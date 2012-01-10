import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

import os
if 'MODE' not in os.environ:
    mode = 'Data'
else:
    mode = os.environ['MODE']

from KoPFA.TagProbe.common_PDFs_cff import *

def tnpEffPSet(categories):
    effSet = cms.PSet()

    for category in categories:
        setattr(effSet, category+"_pt", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(20, 25, 30, 35, 40, 50, 150),
                pt = cms.vdouble(20, 30, 40, 50, 150),
            ),
            BinToPDFmap = cms.vstring("bwResCBExp")
        ))

        setattr(effSet, category+"_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.0, 1.4, 1.6, 2.4)
                #abseta = cms.vdouble(0.0, 1.5, 2.4)
            ),
            BinToPDFmap = cms.vstring("bwResCBExp")
        ))

        setattr(effSet, category+"_pt_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(20, 25, 30, 35, 40, 50, 150),
                pt = cms.vdouble(20, 30, 40, 50, 150),
                abseta = cms.vdouble(0.0, 1.4, 1.6, 2.4)
                #abseta = cms.vdouble(0.0, 1.5, 2.4)
            ),
            BinToPDFmap = cms.vstring("bwResCBExp")
        ))

    return effSet

process.tnpFit = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    InputFileNames = cms.vstring("tnpTree_%s.root" % mode),
    InputDirectoryName = cms.string("tnpId"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("result_Id_%s.root" % mode),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe mass", "70.0", "110.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
    ),

    Categories = cms.PSet(
        IdLoose = cms.vstring("IdLooseMC", "dummy[pass=1,fail=0]"),
        IdMedium = cms.vstring("IdMediumMC", "dummy[pass=1,fail=0]"),
        IdTight = cms.vstring("IdTightMC", "dummy[pass=1,fail=0]"),
        IdSuperTight = cms.vstring("IdSuperTightMC", "dummy[pass=1,fail=0]"),
        IdHyperTight1 = cms.vstring("IdHyperTight1MC", "dummy[pass=1,fail=0]"),
        IdsimpleEleId95relIso = cms.vstring("simpleEleId95relIso", "dummy[pass=1,fail=0]"),
        IdsimpleEleId90relIso = cms.vstring("simpleEleId90relIso", "dummy[pass=1,fail=0]"),
        IdsimpleEleId85relIso = cms.vstring("simpleEleId85relIso", "dummy[pass=1,fail=0]"),
        IdsimpleEleId80relIso = cms.vstring("simpleEleId80relIso", "dummy[pass=1,fail=0]"),
        IdsimpleEleId70relIso = cms.vstring("simpleEleId70relIso", "dummy[pass=1,fail=0]"),
    ),

    PDFs = basicPDFs,

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),

    Efficiencies = tnpEffPSet(["IdLoose","IdMedium", "IdTight","IdSuperTight","IdHyperTight1","IdsimpleEleId95relIso","IdsimpleEleId90relIso","IdsimpleEleId85relIso","IdsimpleEleId80relIso","IdsimpleEleId70relIso"])
)

process.fit = cms.Path(
    process.tnpFit
)

