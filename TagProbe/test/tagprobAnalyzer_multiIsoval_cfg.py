import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

from KoPFA.TagProbe.common_PDFs_cff import *

MC = False 
postfix = ""
if(MC): 
  postfix = "_mc"


def tnpEffPSet(categories):
    effSet = cms.PSet()

    for category in categories:
        setattr(effSet, category+"_pt", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 30, 40, 50, 150)
            ),
            BinToPDFmap = cms.vstring("bgaussPlusLinear")
        ))

        setattr(effSet, category+"_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.0, 1.0, 2.1, 2.4)
            ),
            BinToPDFmap = cms.vstring("bgaussPlusLinear")
        ))

        setattr(effSet, category+"_finerabseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.0, 0.3, 0.6 , 0.9, 1.2, 1.5, 1.8 , 2.1, 2.4)
            ),
            BinToPDFmap = cms.vstring("bgaussPlusLinear")
        ))

        setattr(effSet, category+"_pt_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 30, 40, 50, 150),
                abseta = cms.vdouble(0.0, 1.0, 2.1 , 2.4)
            ),
            BinToPDFmap = cms.vstring("bgaussPlusLinear")
        ))

        setattr(effSet, category+"_charge", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                charge = cms.vdouble(-1.0, 0.0, 1.0)
            ),
            BinToPDFmap = cms.vstring("bgaussPlusLinear")
        ))


    return effSet

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("result2/tagprob"+postfix+".root"),
    InputDirectoryName = cms.string("tnpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("Efficiency_ID"+postfix+".root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(1),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
#    fixVars = cms.vstring("mean"),
                                                 
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "70.0", "110.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        abseta = cms.vstring("Probe #eta", "0", "2.5", ""),
        charge = cms.vstring("Probe charge","-1","1","")
    ),

    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
        #mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),
        isIDMuon = cms.vstring("isIDMuon", "dummy[pass=1,fail=0]"),
        isPFMuon = cms.vstring("isPFMuon", "dummy[pass=1,fail=0]")
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
      basicPDFs,
    ),

    Efficiencies = tnpEffPSet(["isIDMuon","isPFMuon"])
)

process.TagProbeFitTreeAnalyzerIso = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    InputFileNames = cms.vstring("result2/tagprob"+postfix+".root"),
    InputDirectoryName = cms.string("tnpTreeIso"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("Efficiency_Iso"+postfix+".root"),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
#    fixVars = cms.vstring("mean"),

    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "70.0", "110.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        abseta = cms.vstring("Probe #eta", "0", "2.5", ""),
        charge = cms.vstring("Probe charge","-1","1","")
    ),

    Categories = cms.PSet(
        #mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),
        isIso = cms.vstring("isIso", "dummy[pass=1,fail=0]"),
        isIso12 = cms.vstring("isIso12", "dummy[pass=1,fail=0]"),
        isIso14 = cms.vstring("isIso14", "dummy[pass=1,fail=0]"),
        isIso16 = cms.vstring("isIso16", "dummy[pass=1,fail=0]"),
        isIso18 = cms.vstring("isIso18", "dummy[pass=1,fail=0]"),
        isIso20 = cms.vstring("isIso20", "dummy[pass=1,fail=0]"),
        isIso22 = cms.vstring("isIso22", "dummy[pass=1,fail=0]"),
        isIso24 = cms.vstring("isIso24", "dummy[pass=1,fail=0]"),
        isIso26 = cms.vstring("isIso26", "dummy[pass=1,fail=0]"),
        isIso28 = cms.vstring("isIso28", "dummy[pass=1,fail=0]"),
    ),

    PDFs = cms.PSet(
      basicPDFs,
    ),

    Efficiencies = tnpEffPSet(["isIso","isIso12","isIso14","isIso16","isIso18","isIso20","isIso22","isIso24","isIso26","isIso28"])

)

process.fit = cms.Path(process.TagProbeFitTreeAnalyzer
                      *process.TagProbeFitTreeAnalyzerIso
                      )

