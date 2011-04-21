import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

import os
mode = os.environ['MODE']

def tnpEffPSet(categories):
    effSet = cms.PSet()

    for category in categories:
        setattr(effSet, category+"_pt", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 30, 40, 50, 150)
            ),
            BinToPDFmap = cms.vstring("bgaussPlusExp")
        ))

        setattr(effSet, category+"_eta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                eta = cms.vdouble(-2.5, -1.5, 0.0, 1.5, 2.5)
            ),
            BinToPDFmap = cms.vstring("bgaussPlusExp")
        ))

        setattr(effSet, category+"_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.0, 1.5, 2.5)
            ),
            BinToPDFmap = cms.vstring("bgaussPlusExp")
        ))

        setattr(effSet, category+"_pt_eta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 30, 40, 50, 150),
                eta = cms.vdouble(-2.5, -1.5, 0.0, 1.5, 2.5)
            ),
            BinToPDFmap = cms.vstring("bgaussPlusExp")
        ))

        setattr(effSet, category+"_pt_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 30, 40, 50, 150),
                abseta = cms.vdouble(0.0, 1.5, 2.5)
            ),
            BinToPDFmap = cms.vstring("bgaussPlusExp")
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
        eta = cms.vstring("Probe #eta", "-2.5", "2.5", "Radian"),
        abseta = cms.vstring("Probe |#eta|", "0", "2.5", "Radian"),
    ),

    Categories = cms.PSet(
        Id = cms.vstring("Id", "dummy[pass=1,fail=0]"),
    ),

    PDFs = cms.PSet(
        gaussPlusExp = cms.vstring(
            "Gaussian::signal(mass, mean[91.2, 89.0, 93.0], sigma[2.5, 0.5, 10.0])",
            "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
            "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        bgaussPlusExp = cms.vstring(
            "RooBifurGauss::signal(mass, mean[91.2, 89.0, 93.0], sigma1[2.5, 0.5, 10.0], sigma2[2.5, 0.5, 10.0])",
            "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
            "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        )
    ),
    Efficiencies = tnpEffPSet(["Id"])
)

process.tnpIdIso = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    InputFileNames = cms.vstring("tnpTree_%s.root" % mode),
    InputDirectoryName = cms.string("tnpIdIso"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("result_IdIso_%s.root" % mode),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe mass", "70.0", "110.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        eta = cms.vstring("Probe #eta", "-2.5", "2.5", "Radian"),
        abseta = cms.vstring("Probe |#eta|", "0", "2.5", "Radian"),
    ),

    Categories = cms.PSet(
        IdIso20 = cms.vstring("IdIso20", "dummy[pass=1,fail=0]"),
        IdIso22 = cms.vstring("IdIso22", "dummy[pass=1,fail=0]"),
        IdIso24 = cms.vstring("IdIso24", "dummy[pass=1,fail=0]"),
        IdIso26 = cms.vstring("IdIso26", "dummy[pass=1,fail=0]"),
        IdIso30 = cms.vstring("IdIso30", "dummy[pass=1,fail=0]"),
        IdIso50 = cms.vstring("IdIso50", "dummy[pass=1,fail=0]"),
    ),

    PDFs = cms.PSet(
        gaussPlusExp = cms.vstring(
            "Gaussian::signal(mass, mean[91.2, 89.0, 93.0], sigma[2.5, 0.5, 10.0])",
            "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
            "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        bgaussPlusExp = cms.vstring(
            "RooBifurGauss::signal(mass, mean[91.2, 89.0, 93.0], sigma1[2.5, 0.5, 10.0], sigma2[2.5, 0.5, 10.0])",
            "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
            "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        )
    ),

    #Efficiencies = tnpEffPSet(["IdIso20", "IdIso22", "IdIso24", "IdIso26", "IdIso30", "IdIso50"]),
    Efficiencies = tnpEffPSet(["IdIso26"]),
)

process.p = cms.Path(
    process.tnpId * 
    process.tnpIdIso
)

