import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("result6/tagprob.root"),
    InputDirectoryName = cms.string("tnpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("Efficiency_ID.root"),
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
        abseta = cms.vstring("Probe #eta", "0", "2.5", "")
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
        gaussPlusLinear = cms.vstring(
            "Gaussian::signal(mass, mean[91.2, 89.0, 93.0], sigma[2.5, 0.5, 10.0])",
            "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
            "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
    ),

    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
        #the name of the parameter set becomes the name of the directory
        ID_pt = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isIDMuon","pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 40, 150)
            ),
            BinToPDFmap = cms.vstring("gaussPlusLinear")
        ),

        ID_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isIDMuon","pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.0, 1.5 , 2.5)
            ),
            BinToPDFmap = cms.vstring("gaussPlusLinear")
        ),

        ID_pt_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isIDMuon","pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 40, 150),
                abseta = cms.vdouble(0.0, 1.5, 2.5)
            ),
            BinToPDFmap = cms.vstring("gaussPlusLinear")
        ),
        
        #the name of the parameter set becomes the name of the directory
        PF_pt = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isPFMuon","pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 40, 150)
            ),
            BinToPDFmap = cms.vstring("gaussPlusLinear")
        ),

        PF_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isPFMuon","pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.0, 1.5 , 2.5)
            ),
            BinToPDFmap = cms.vstring("gaussPlusLinear")
        ),

        PF_pt_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isPFMuon","pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 40, 150),
                abseta = cms.vdouble(0.0, 1.5, 2.5)
            ),
            BinToPDFmap = cms.vstring("gaussPlusLinear")
        ),

    )
)

process.TagProbeFitTreeAnalyzerIso = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    InputFileNames = cms.vstring("result6/tagprob.root"),
    InputDirectoryName = cms.string("tnpTreeIso"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("Efficiency_Iso.root"),
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(True),
    floatShapeParameters = cms.bool(True),
#    fixVars = cms.vstring("mean"),

    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "70.0", "110.0", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        abseta = cms.vstring("Probe #eta", "0", "2.5", "")
    ),

    Categories = cms.PSet(
        #mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),
        isIso = cms.vstring("isIso", "dummy[pass=1,fail=0]")
    ),

    PDFs = cms.PSet(
        gaussPlusLinear = cms.vstring(
            "Gaussian::signal(mass, mean[91.2, 89.0, 93.0], sigma[2.5, 0.5, 10.0])",
            "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
            "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
    ),

    Efficiencies = cms.PSet(
        pt = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isIso","pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 40, 150)
            ),
            BinToPDFmap = cms.vstring("gaussPlusLinear")
        ),
        
        abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isIso","pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0.0, 1.5 , 2.5)
            ),
            BinToPDFmap = cms.vstring("gaussPlusLinear")
        ),

        pt_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("isIso","pass"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(20, 40, 150),
                abseta = cms.vdouble(0.0, 1.5, 2.5)
            ),
            BinToPDFmap = cms.vstring("gaussPlusLinear")
        ),

    )
)


process.fit = cms.Path(process.TagProbeFitTreeAnalyzer
                      *process.TagProbeFitTreeAnalyzerIso
                      )



