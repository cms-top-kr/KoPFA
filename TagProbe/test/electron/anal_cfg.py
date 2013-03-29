import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

import os
mode = os.environ['MODE']
step = os.environ['STEP']
category = os.environ['CATEGORY']

from KoPFA.TagProbe.common_PDFs_cff import *

def tnpEffPSet(category):
    effSet = cms.PSet()

    if 'DZ' in category:
        setattr(effSet, category+"_pair_dz", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass", "weight"),
            BinnedVariables = cms.PSet(
                pair_dz = cms.vdouble(0.00, 0.05, 0.10, 0.15, 0.20, 0.30),
            ),
            BinToPDFmap = cms.vstring("bwResCBTurnOn")
        ))

    setattr(effSet, category+"_pt", cms.PSet(
        EfficiencyCategoryAndState = cms.vstring(category, "pass"),
        UnbinnedVariables = cms.vstring("mass", "weight"),
        BinnedVariables = cms.PSet(
            #pt = cms.vdouble(20, 25, 30, 35, 40, 50, 150),
            pt = cms.vdouble(5, 7, 10, 15, 20, 30, 40, 50, 200),
        ),
        #BinToPDFmap = cms.vstring("bwResCBTurnOn", "*pt_bin7*", "bwResCBPoly")
        BinToPDFmap = cms.vstring("bwResCBTurnOn")
    ))

    setattr(effSet, category+"_abseta", cms.PSet(
        EfficiencyCategoryAndState = cms.vstring(category, "pass"),
        UnbinnedVariables = cms.vstring("mass", "weight"),
        BinnedVariables = cms.PSet(
            abseta = cms.vdouble(0.0, 0.8, 1.478, 2.5)
        ),
        BinToPDFmap = cms.vstring("bwResCBTurnOn")
    ))

    setattr(effSet, category+"_pt_abseta", cms.PSet(
        EfficiencyCategoryAndState = cms.vstring(category, "pass"),
        UnbinnedVariables = cms.vstring("mass", "weight"),
        BinnedVariables = cms.PSet(
            #pt = cms.vdouble(20, 25, 30, 35, 40, 50, 150),
            pt = cms.vdouble(5, 7, 10, 15, 20, 30, 40, 50, 200),
            abseta = cms.vdouble(0.0, 0.8, 1.478, 2.5)
            #abseta = cms.vdouble(0.0, 1.5, 2.4)
        ),
        BinToPDFmap = cms.vstring("bwResCBTurnOn")
    ))

    setattr(effSet, category+"_event_nPV", cms.PSet(
        EfficiencyCategoryAndState = cms.vstring(category, "pass"),
        UnbinnedVariables = cms.vstring("mass", "weight"),
        BinnedVariables = cms.PSet(
            event_nPV = cms.vdouble(*[i-0.5 for i in range(0, 31, 5)])
        ),
        BinToPDFmap = cms.vstring("bwResCBTurnOn")
    ))

    setattr(effSet, category+"_event_nJet", cms.PSet(
        EfficiencyCategoryAndState = cms.vstring(category, "pass"),
        UnbinnedVariables = cms.vstring("mass", "weight"),
        BinnedVariables = cms.PSet(
            event_nJet = cms.vdouble(*[i-0.5 for i in range(0, 6)])
        ),
        BinToPDFmap = cms.vstring("bwResCBTurnOn")
    ))

    return effSet

def makeTnPFitter(process, suffix, category):
    fitter = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
        #InputFileNames = cms.vstring("ntuple/0j/tnpTree_%s.root" % mode),
        InputFileNames = cms.vstring("ntuple/ntuple_%s.root" % mode),
        InputDirectoryName = cms.string("tnp"+suffix),
        InputTreeName = cms.string("fitter_tree"),
        OutputFileName = cms.string("result/unmerged/result_%s_%s_%s.root" % (suffix, category, mode)),
        NumCPU = cms.uint32(1),
        SaveWorkspace = cms.bool(False),
        floatShapeParameters = cms.bool(True),
        WeightVariable = cms.string("weight"),
        Variables = cms.PSet(
            mass = cms.vstring("Tag-Probe mass", "60.0", "120.0", "GeV/c^{2}"),
            pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
            abseta = cms.vstring("Probe |#eta|", "0", "2.5", ""),
            event_nPV = cms.vstring("Number of vertex", "0", "30", ""),
            event_nJet = cms.vstring("Jet multiplicity", "0", "5", ""),
            pair_dz = cms.vstring("#Delta z", "0", "0.3", "cm"),
            weight = cms.vstring("Weight", "0.0", "2.0", ""),
        ),
        Categories = cms.PSet(),
        PDFs = basicPDFs,
        binnedFit = cms.bool(True),
        binsForFit = cms.uint32(100),
        Quiet = cms.untracked.bool(True),
    )

    setattr(fitter, 'Efficiencies', tnpEffPSet(category))
    setattr(fitter.Categories, category, cms.vstring(category, "dummy[pass=1,fail=0]"))

    setattr(process, 'fit'+suffix, fitter)
    process.p += getattr(process, 'fit'+suffix)

process.p = cms.Path()

#makeTnPFitter(process, step, categoryMap[step])
makeTnPFitter(process, step, category)
