import FWCore.ParameterSet.Config as cms

basicPDFs = cms.PSet(
        gaussPlusLinear = cms.vstring(
            "Gaussian::signal(mass, mean[91.2, 89.0, 93.0], sigma[5.0, 0.5, 10.0])",
            "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
            "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        bgaussPlusLinear = cms.vstring(
            "RooBifurGauss::signal(mass, mean[91.2, 89.0, 93.0], sigma1[5.0, 0.5, 10.0],sigma2[5.0, 0.5, 10.0])",
            "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
            "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        CBPlusLinear = cms.vstring(
           "RooCBShape::signal(mass,m1[91.2,89.0,93.0],sigma[5.0,0.3,8.5],alfa[1.8,0.,10.],n[1,1.,10.])",
           "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
           "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
           "efficiency[0.9,0,1]",
           "signalFractionInPassing[0.9]"
        ),
        gaussPlusQuadratic = cms.vstring(
           "Gaussian::signal(mass, mean[91.2,89.0,93.0], sigma[5,0.3,8.5])",
           "Chebychev::backgroundPass(mass, {cPass1[0,-1,1], cPass2[0,-1,1]})",
           "Chebychev::backgroundFail(mass, {cFail1[0,-1,1], cFail2[0,-1,1]})",
           "efficiency[0.9,0,1]",
           "signalFractionInPassing[0.9]",
        ),
)
