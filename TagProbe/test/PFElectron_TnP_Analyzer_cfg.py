import FWCore.ParameterSet.Config as cms

def getEnv(varName, default):
    import os
    if varName in os.environ:
        return os.environ[varName]
    else:
        return default

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

import os
mode = getEnv('MODE', 'MC')
step = getEnv('STEP', 'all')

from KoPFA.TagProbe.common_PDFs_cff import *

def tnpEffPSet(categories):
    effSet = cms.PSet()

    for category in categories:
        setattr(effSet, category+"_pt", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass", "weight"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(20, 25, 30, 35, 40, 50, 150),
                pt = cms.vdouble(5, 7, 10, 15, 20, 30, 40, 50, 150),
            ),
            BinToPDFmap = cms.vstring("bwResCBExp")
        ))

        setattr(effSet, category+"_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass", "weight"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.0, 0.8, 1.478, 2.5)
            ),
            BinToPDFmap = cms.vstring("bwResCBExp")
        ))

        setattr(effSet, category+"_pt_abseta", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass", "weight"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(20, 25, 30, 35, 40, 50, 150),
                pt = cms.vdouble(5, 7, 10, 15, 20, 30, 40, 50, 150),
                abseta = cms.vdouble(0.0, 0.8, 1.478, 2.5)
                #abseta = cms.vdouble(0.0, 1.5, 2.4)
            ),
            BinToPDFmap = cms.vstring("bwResCBExp")
        ))

        setattr(effSet, category+"_event_nPV", cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(category, "pass"),
            UnbinnedVariables = cms.vstring("mass", "weight"),
            BinnedVariables = cms.PSet(
                event_nPV = cms.vdouble(*[i-0.5 for i in range(0, 32)])
            ),
            BinToPDFmap = cms.vstring("bwResCBExp")
        ))

    return effSet

def makeTnPFitter(process, suffix, categories):
    fitter = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
        #InputFileNames = cms.vstring("ntuple/tnpTree_%s.root" % mode),
        InputFileNames = cms.vstring("tnpTree.root"),
        InputDirectoryName = cms.string("tnp"+suffix),
        InputTreeName = cms.string("fitter_tree"),
        #OutputFileName = cms.string("result/result_%s_%s.root" % (suffix, mode)),
        OutputFileName = cms.string("result.root"),
        NumCPU = cms.uint32(1),
        SaveWorkspace = cms.bool(False),
        floatShapeParameters = cms.bool(True),
        WeightVariable = cms.string("weight"),
        Variables = cms.PSet(
            mass = cms.vstring("Tag-Probe mass", "70.0", "110.0", "GeV/c^{2}"),
            pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
            abseta = cms.vstring("Probe |#eta|", "0", "2.5", ""),
            event_nPV = cms.vstring("Number of vertex", "0", "30", ""),
            weight = cms.vstring("Weight", "0.0", "2.0", ""),
        ),
        Categories = cms.PSet(),
        PDFs = basicPDFs,
        binnedFit = cms.bool(True),
        binsForFit = cms.uint32(50),
    )

    for cat in categories:
        setattr(fitter, 'Efficiencies', tnpEffPSet(categories))
        setattr(fitter.Categories, cat, cms.vstring(cat, "dummy[pass=1,fail=0]"))

    setattr(process, 'fit'+suffix, fitter)
    process.p += getattr(process, 'fit'+suffix)

process.p = cms.Path()

categoryMap = {}
categoryMap['Nh'                 ] = ['nh0', 'nh1']
categoryMap['Nh0Mva'             ] = ['mva00', 'mva03', 'mva05', 'mva07', 'mva09']
categoryMap['Nh0Mva05Iso'        ] = ['iso15' , 'diso15', 'riso15',]
categoryMap['Nh0Mva05Riso15Pf'   ] = ['pf']
categoryMap['Nh0Mva05Riso15PfTrg'] = ['trgSL', 'trgHL', 'trgDZ', 'trgZM', 'trgTH',]
categoryMap['Nh0Mva00Iso'        ] = ['iso15' , 'diso15', 'riso15',]
categoryMap['Nh0Mva00Riso15Pf'   ] = ['pf']
categoryMap['Nh0Mva00Riso15PfTrg'] = ['trgSL', 'trgHL', 'trgDZ', 'trgZM', 'trgTH',]

if step == 'all':
    for i in categoryMap:
        makeTnPFitter(process, i, categoryMap[i])
else:
    makeTnPFitter(process, step, categoryMap[step])
