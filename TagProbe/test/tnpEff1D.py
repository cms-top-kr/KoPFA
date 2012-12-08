#!/usr/bin/env python

from ROOT import *
from math import *

gROOT.ProcessLine(".x rootlogon.C")

steps = {
    "Nh":["nh0", "nh1"],
    'Nh0Mva':['mva00', 'mva03', 'mva05', 'mva07', 'mva09'],
    'Nh0Mva05Iso':['iso15', 'diso15', 'riso15'],
    'Nh0Mva05Riso15Pf':['pf'],
    'Nh0Mva05Riso15PfTrg':['trgHL', 'trgPath'],

    #'Nh0Mva00Iso':['iso15', 'diso15', 'riso15'],
    'Nh0Mva00Iso':['riso15'],
    'Nh0Mva00Riso15Pf':['pf'],
    'Nh0Mva00Riso15PfTrg':['trgHL', 'trgPath'],
}

variables = ["abseta", "pt", "event_nPV"]
xTitle = ["Supercluster |#eta|", "Transverse momentum p_{T} (GeV/c^{2})", "Number of Primary vertex"]

def getRooHistsFromCanvas(canvas):
    return [x for x in canvas.GetListOfPrimitives() if x.IsA().GetName() == 'RooHist']

def copyGraph(srcGrp, threshold = 0):
    grp = TGraphAsymmErrors()

    p = 0
    for i in range(0, srcGrp.GetN()):
        x, y = srcGrp.GetX()[i], srcGrp.GetY()[i]
        ex = srcGrp.GetEXlow()[i], srcGrp.GetEXhigh()[i]
        ey = srcGrp.GetEYlow()[i], srcGrp.GetEYhigh()[i]
        if threshold > 0 and hypot(*ey) > threshold: continue

        if srcGrp.GetN() > 20:
            ex = 0.5, 0.5
            x = i+0.5

        grp.SetPoint(p, x-ex[0]+(ex[0]+ex[1])/2, y)
        grp.SetPointError(p, (ex[0]+ex[1])/2, (ex[0]+ex[1])/2, ey[0], ey[1])
        p += 1

    return grp

def setGrpXRange(grps):
    xmin, xmax = 1e9, -1e9
    for grp in grps:
        for i in range(0, grp.GetN()):
            x, exLo, exHi = grp.GetX()[i], grp.GetEXlow()[i], grp.GetEXhigh()[i]

            xLo = x-exLo
            xHi = x+exHi

            if xLo < xmin: xmin = xLo
            if xHi > xmax: xmax = xHi

    for grp in grps:
        grp.GetXaxis().SetRangeUser(xmin, xmax)
    return grps

def buildCmpCanvas(name, grpA, grpB, grpRatio):
    c = TCanvas("c_%s" % name, name, 500, 600)
    c.Divide(1,2)

    pad1 = c.cd(1)
    pad1.SetPad(0, 0.3, 1, 1)
    pad1.SetBottomMargin(0.00)
    
    grpA.Draw("APZ")
    grpB.Draw("PZ")

    pad2 = c.cd(2)
    pad2.SetPad(0, 0, 1, 0.3)
    pad2.SetTopMargin(0.0)
    pad2.SetBottomMargin(0.25)

    grpRatio.GetYaxis().SetNdivisions(505)
    grpRatio.GetYaxis().SetLabelSize(0.07)
    grpRatio.GetYaxis().SetTitleSize(0.1)
    grpRatio.GetYaxis().SetTitleOffset(0.6)
    grpRatio.GetXaxis().SetLabelSize(0.08)
    grpRatio.GetXaxis().SetTitleSize(0.1)
    grpRatio.GetXaxis().SetTitleOffset(1.1)

    grpRatio.Draw("APZ")

    return c

def checkFitResults(directory, variable):
    binToFit = {}
    for key in [key.GetName() for key in directory.GetListOfKeys()]:
        if "%s_bin" % variable not in key: continue
        binNumber = int(key.replace("%s_bin" % variable, "").split("__")[0])

        fitResult = directory.Get("%s/fitresults" % key)
        fitCanvas = directory.Get("%s/fit_canvas" % key)

        if not fitResult or not fitCanvas: continue

        if fitResult.IsA().GetName() != "RooFitResult": continue
        if fitCanvas.IsA().GetName() != "TCanvas": continue

        if fitResult.covQual() > 1:
            print fitResult.covQual()
            fitResult.Print("v")

        #pads = []
        #for i in range(1,5):
        #    pad = fitCanvas.FindObject("fit_canvas_%d" % i)
        #    pads.append(pad)
        #    for obj in [obj for obj in pad.GetListOfPrimitives() if ]: 
        #        print obj.IsA().GetName()

        #if binNumber not in binToFit: binToFit[binNumber] = []

        #binToFit[binNumber].append( (fitResult, fitCanvas) )

    #for i in binToFit:
    #    result = binToFit[i]
    #    if len(result) != 1:
    #        print "Multiple fit result exists"
    #    fitResult, fitCanvas = result[0]
    #    #if fitResult.prob() < 0.99:
    #    if fitResult.status() != 0:
    #        print "Fit failed : ", variable, i
    #        pars = fitResult.floatParsFinal()
    #        for i in range(pars.getSize()):
    #            par = pars.at(i)
    #            print par.GetName(), par.getVal(), par.getErrorLo(), par.getErrorHi()

objs = []
canvases = []

for step in steps:
    fMC = TFile("result/result_%s_Summer12-ZJets.root" % step)
    fRD = TFile("result/result_%s_Run2012-Run2012ElEl.root" % step)

    categories = steps[step]
    for category in categories:
        for variable in variables:
            dirMC = fMC.Get("tnp%s/%s_%s" % (step, category, variable))
            dirRD = fRD.Get("tnp%s/%s_%s" % (step, category, variable))

            #checkFitResults(dirMC, variable)
            #checkFitResults(dirRD, variable)

            histsMC = getRooHistsFromCanvas(dirMC.Get("fit_eff_plots/%s_PLOT" % variable))
            histsRD = getRooHistsFromCanvas(dirRD.Get("fit_eff_plots/%s_PLOT" % variable))

            histMC = [x for x in histsMC if x.GetName() == 'hxy_fit_eff'][0]
            histRD = [x for x in histsRD if x.GetName() == 'hxy_fit_eff'][0]

            grpMC = copyGraph(histMC)
            grpRD = copyGraph(histRD)
            grpRatio = copyGraph(histRD)
            #grpRatio = grpRD.Clone()
            for i in range(0, grpRatio.GetN()):
                xMC = grpRatio.GetX()[i]
                yMC = grpMC.GetY()[i]
                yRD = grpRD.GetY()[i]
                y, eyUp, eyDn = 1, 0, 0
                if yMC != 0 and yRD != 0:
                    y = yRD/yMC
                    eyUp = y*hypot(grpMC.GetEYhigh()[i]/yMC, grpRD.GetEYhigh()[i]/yRD)
                    eyDn = y*hypot(grpMC.GetEYlow()[i]/yMC, grpRD.GetEYlow()[i]/yRD)

                grpRatio.SetPoint(i, xMC, y)
                grpRatio.SetPointEYhigh(i, eyUp)
                grpRatio.SetPointEYlow(i, eyDn)
            grpMC = copyGraph(grpMC)#, 0.02)
            grpRD = copyGraph(grpRD)#, 0.02)
            grpRatio = copyGraph(grpRatio)#, 0.02)

            grpRD.GetXaxis().SetTitle("")
            grpRD.GetYaxis().SetTitle("Efficiency")
            grpRatio.GetXaxis().SetTitle(xTitle[variables.index(variable)])
            grpRatio.GetYaxis().SetTitle("Data/MC")

            setGrpXRange([grpMC, grpRD, grpRatio])

            grpMC.SetLineColor(kBlue)
            grpRD.SetLineColor(kRed)

            grpMC.SetFillColor(kBlue)
            grpRD.SetFillColor(kRed)

            grpMC.SetFillStyle(3004)
            grpRD.SetFillStyle(3005)

            grpMC.SetMarkerColor(kBlue)
            grpRD.SetMarkerColor(kRed)

            grpMC.SetMarkerSize(0.1)
            grpRD.SetMarkerSize(0.1)

            grpMC.SetLineWidth(2)
            grpRD.SetLineWidth(2)

            grpRD.SetMinimum(0.8)
            grpRD.SetMaximum(1.01)

            grpRatio.SetFillStyle(3005)
            grpRatio.SetLineWidth(2)
            grpRatio.SetMarkerSize(0.1)

            grpRatio.SetMinimum(0.9)
            grpRatio.SetMaximum(1.1)

            c = buildCmpCanvas("%s_%s_%s" % (step, category, variable), grpRD, grpMC, grpRatio)
            leg = TLegend(0.7, 0.1, 0.93, 0.25)
            leg.SetFillColor(kWhite)
            leg.SetBorderSize(0)
            leg.AddEntry(grpMC, "MC", "l")
            leg.AddEntry(grpRD, "Data", "l")
            c.cd(1)
            leg.Draw()

            canvases.append(c)
            objs.extend( (c, grpMC, grpRD, grpRatio, leg) )

for c in canvases:
    c.Print("image/"+c.GetName()+".png")
    c.Print("image/"+c.GetName()+".pdf")
