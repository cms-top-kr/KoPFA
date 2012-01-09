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

process.tnpId = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
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
        IdMedium = cms.vstring("IdMedium", "dummy[pass=1,fail=0]"),
        IdTight = cms.vstring("IdTight", "dummy[pass=1,fail=0]"),
    ),

    PDFs = basicPDFs,

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),

    Efficiencies = tnpEffPSet(["IdMedium", "IdTight"])
)

process.tnpPFId = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    InputFileNames = cms.vstring("tnpTree_%s.root" % mode),
    InputDirectoryName = cms.string("tnpPFId"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("result_PFId_%s.root" % mode),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe mass", "70.0", "110.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
    ),

    Categories = cms.PSet(
        PFId = cms.vstring("PFId", "dummy[pass=1,fail=0]"),
    ),

    PDFs = basicPDFs,

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),

    Efficiencies = tnpEffPSet(["PFId"])
)

process.tnpTrigger = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    InputFileNames = cms.vstring("tnpTree_%s.root" % mode),
    InputDirectoryName = cms.string("tnpTrigger"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("result_Trigger_%s.root" % mode),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe mass", "70.0", "110.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
    ),

    Categories = cms.PSet(
        Trigger = cms.vstring("Trigger", "dummy[pass=1,fail=0]"),
    ),

    PDFs = basicPDFs,

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),

    Efficiencies = tnpEffPSet(["Trigger"])
)


process.tnpTightIdIso = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    InputFileNames = cms.vstring("tnpTree_%s.root" % mode),
    InputDirectoryName = cms.string("tnpTightIdIso"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("result_TightIdIso_%s.root" % mode),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe mass", "70.0", "110.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        eta = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
    ),

    Categories = cms.PSet(
        Iso10 = cms.vstring("Iso10", "dummy[pass=1,fail=0]"),
        Iso15 = cms.vstring("Iso15", "dummy[pass=1,fail=0]"),
        Iso17 = cms.vstring("Iso17", "dummy[pass=1,fail=0]"),
        Iso20 = cms.vstring("Iso20", "dummy[pass=1,fail=0]"),
        Iso10dbeta = cms.vstring("Iso10dbeta", "dummy[pass=1,fail=0]"),
        Iso15dbeta = cms.vstring("Iso15dbeta", "dummy[pass=1,fail=0]"),
        Iso17dbeta = cms.vstring("Iso17dbeta", "dummy[pass=1,fail=0]"),
        Iso20dbeta = cms.vstring("Iso20dbeta", "dummy[pass=1,fail=0]"),
    ),

    PDFs = basicPDFs,

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),

    Efficiencies = tnpEffPSet(["Iso10","Iso15", "Iso17", "Iso20","Iso10dbeta","Iso15dbeta", "Iso17dbeta", "Iso20dbeta"]),
)

process.fit = cms.Path(
    process.tnpId
)

