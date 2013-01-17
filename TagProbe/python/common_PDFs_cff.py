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
           "signalFractionInPassing[0.9]"
        ),
        voigtianPlusLinear = cms.vstring(
            "RooVoigtian::signal(mass, mean[91.2, 89.0, 93.0], width[2.5,0.5,10.0], sigma[5.0, 0.5, 10.0])",
            "RooExponential::backgroundPass(mass, cPass[0,-10,10])",
            "RooExponential::backgroundFail(mass, cFail[0,-10,10])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        bwResCBExp = cms.vstring(
            "BreitWigner::bw(mass, m0[91.2], width[2.9,0.1,9.0])",
            "RooCBShape::cbResPass(mass, peakPass[0,-5,5], sigmaPass[2,1e-2,10], alphaPass[0.5,0,3], nPass[10,1,10])",
            "RooCBShape::cbResFail(mass, peakFail[0,-5,5], sigmaFail[2,1e-2,10], alphaFail[0.5,0,3], nFail[10,1,10])",
            "FCONV::signalPass(mass, bw, cbResPass)",
            "FCONV::signalFail(mass, bw, cbResFail)",
            "RooExponential::backgroundPass(mass, cPass[-0.02,-10,0])",
            "RooExponential::backgroundFail(mass, cFail[-0.02,-10,0])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]",
        ),
        bwResCBPoly = cms.vstring(
            "BreitWigner::bw(mass, m0[91.2], width[2.9,0.5,5])",
            "RooCBShape::resPass(mass, peakPass[0,-3,3], sigmaPass[2,0.01,10], alphaPass[0.5,0,3], nPass[5,1,10])",
            "RooCBShape::resFail(mass, peakFail[0,-3,3], sigmaFail[2,0.01,10], alphaFail[0.5,0,3], nFail[5,1,10])",
            "FCONV::signalPass(mass, bw, resPass)",
            "FCONV::signalFail(mass, bw, resFail)",
            "Chebychev::backgroundPass(mass, {cPass1[0,-10,10], cPass2[0,-10,10], cPass3[0,-10,10]})",
            "Chebychev::backgroundFail(mass, {cFail1[0,-10,10], cFail2[0,-10,10], cFail3[0,-10,10]})",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]",
        ),
        bwResCBTurnOn = cms.vstring(
            "BreitWigner::bw(mass, m0[91.2], width[2.9,0.5,5])",
            "RooCBShape::resPass(mass, peakPass[0,-3,3], sigmaPass[2,0.01,10], alphaPass[0.5,0,3], nPass[5,1,10])",
            "RooCBShape::resFail(mass, peakFail[0,-3,3], sigmaFail[2,0.01,10], alphaFail[0.5,0,3], nFail[5,1,10])",
            "FCONV::signalPass(mass, bw, resPass)",
            "FCONV::signalFail(mass, bw, resFail)",
            "Exponential::bkgModelPass(mass, p0Pass[0,-5e-1,0])",
            "Exponential::bkgModelFail(mass, p0Fail[0,-5e-1,0])",
            "turnOn[50,50,100]",
            "EXPR::bkgTurnOnPass('TMath::Erf((mass-turnOn)/bkgResPass)/2+0.5', mass, turnOn, bkgResPass[50,5,50])",
            "EXPR::bkgTurnOnFail('TMath::Erf((mass-turnOn)/bkgResPass)/2+0.5', mass, turnOn, bkgResPass)"
            #"EXPR::bkgTurnOnFail('TMath::Erf((mass-turnOn)/bkgResFail)/2+0.5', mass, turnOn, bkgResFail[50,5,50])"
            "PROD::backgroundPass(bkgModelPass, bkgTurnOnPass)",
            "PROD::backgroundFail(bkgModelFail, bkgTurnOnFail)",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]",
        ),
)
