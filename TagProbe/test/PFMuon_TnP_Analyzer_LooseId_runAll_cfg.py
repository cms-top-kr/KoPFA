import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

import os
if 'MODE' not in os.environ:
    mode = 'DATA'
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
            BinToPDFmap = cms.vstring("vpvPlusQuadratic") #vpvPlusExpo")
        ))

        setattr(effSet, category+"_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.0, 0.5, 1.0, 1.4, 1.6, 2.0, 2.4)
                #abseta = cms.vdouble(0.0, 1.5, 2.4)
            ),
            BinToPDFmap = cms.vstring("vpvPlusExpo")
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
            BinToPDFmap = cms.vstring("vpvPlusExpo")
        ))

    return effSet

process.tnpFit = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    #InputFileNames = cms.vstring("rfio:/castor/cern.ch/user/j/jkim/TopAna/TnpTree/ALL/tagprob_Run2011_SingleMu_nPV_all.root"),
    InputFileNames = cms.vstring("rfio:/castor/cern.ch/user/j/jkim/TopAna/TnpTree/ALL/tagprob_Run2011AB_SingleMu_allfiles-2.root"),
    #InputFileNames = cms.vstring("rfio:/castor/cern.ch/user/j/jkim/TopAna/TnpTree/Run2011A/1-May10ReReco-v1_3_relIsoTag/tagprob_Run2011A_SingleMu_May10ReReco-v1_nPV_9files.root"),
    #InputDirectoryName = cms.string("tnpId"),
    InputDirectoryName = cms.string("tnpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("result_Id_loosemu_runAll_%s.root" % mode),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
    Variables = cms.PSet(
        #mass = cms.vstring("Tag-Probe mass", "50.0", "130.0", "GeV/c^{2}"),
        mass = cms.vstring("Tag-Probe mass", "60.0", "140.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
    ),

    Categories = cms.PSet(
        isLooseMuon = cms.vstring("isLooseMuon", "dummy[pass=1,fail=0]")
    ),

    PDFs = basicPDFs,

    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),

    Efficiencies = tnpEffPSet(["isLooseMuon"])
)

process.fit = cms.Path(
    process.tnpFit
)

