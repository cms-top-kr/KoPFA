#!/usr/bin/env python

from ROOT import *
from math import *

gROOT.ProcessLine(".x rootlogon.C")
gStyle.SetPalette(1)
gStyle.SetPaintTextFormat(".3f")
gROOT.ForceStyle()

steps = {
    "Nh":["nh0", "nh1"],
    'Nh0Mva':['mva00', 'mva03', 'mva05', 'mva07', 'mva09'],
    'Nh0Mva05Iso':['iso15', 'diso15', 'riso15'],
    'Nh0Mva05Riso15Pf':['pf'],
    'Nh0Mva05Riso15PfTrg':['trgHL', 'trgPath'],

    'Nh0Mva00Iso':['iso15', 'diso15', 'riso15'],
    'Nh0Mva00Riso15Pf':['pf'],
    'Nh0Mva00Riso15PfTrg':['trgHL', 'trgPath'],
}

yTitle = "Supercluster |#eta|"
xTitle = "Transverse momentum p_{T} (GeV/c^{2})"

def getTH2FromCanvas(canvas):
    return [x for x in canvas.GetListOfPrimitives() if 'TH2' in x.IsA().GetName()]

def getEffMap(directory, fitResultPath, nbinsX, nbinsY):
    binToEffMap = {}

    for i in range(nbinsX):
        for j in range(nbinsY):
            subDirName = fitResultPath % (i, j)
            fitResults = directory.Get(subDirName)
            if not fitResults: continue

            fitValues = fitResults.floatParsFinal()
            effValue = None

            for k in range(fitValues.getSize()):
                var = fitValues.at(k)
                if var.GetName() != 'efficiency': continue

                effValue = var

            if not effValue: continue

            binToEffMap[(i,j)] = (effValue.getVal(), effValue.getErrorLo(), effValue.getErrorHi())

    return binToEffMap

canvases = []
hists = []
fout = open("table.tex", "w")
for step in steps:
    fMC = TFile("result/result_%s_Summer12-ZJets.root" % step)
    fRD = TFile("result/result_%s_Run2012-Run2012ElEl.root" % step)

    categories = steps[step]
    for category in categories:
        dirMC = fMC.Get("tnp%s/%s_pt_abseta" % (step, category))
        dirRD = fRD.Get("tnp%s/%s_pt_abseta" % (step, category))

        histMC = getTH2FromCanvas(dirMC.Get("fit_eff_plots/pt_abseta_PLOT"))[0]
        histRD = getTH2FromCanvas(dirRD.Get("fit_eff_plots/pt_abseta_PLOT"))[0]

        gROOT.cd()
        histMC = histMC.Clone("hMCEff2D_%s_%s_pt_abseta" % (step, category))
        histRD = histRD.Clone("hRDEff2D_%s_%s_pt_abseta" % (step, category))

        if histMC.GetNbinsX() != histRD.GetNbinsX() or histMC.GetNbinsY() != histRD.GetNbinsY(): continue
        nbinsX = histMC.GetNbinsX()
        nbinsY = histMC.GetNbinsY()

        ## Scale factor in 2D
        fitResultPathForm = "abseta_bin%d__pt_bin%d__bwResCBExp/fitresults"
        effResultMC = getEffMap(dirMC, fitResultPathForm, nbinsY, nbinsX)
        effResultRD = getEffMap(dirRD, fitResultPathForm, nbinsY, nbinsX)

        latexTableHeader = ["r"]
        scaleTable = ""
        scaleLine = []
        for xbin in range(nbinsX):
            xmin = histMC.GetXaxis().GetBinLowEdge(xbin+1)
            xmax = histMC.GetXaxis().GetBinUpEdge(xbin+1)
            scaleLine.append("$%.0f < p_{T} < %.0f$" % (xmin, xmax))
            latexTableHeader.append("c")
        scaleTable = ("  \\textbf{Step %s %s} & " % (step, category)) + (" & ".join(scaleLine)) + " \\\\\n"
        scaleTable += "  \\hline\n"
        latexTableHeader = "|".join(latexTableHeader)

        for ybin in range(nbinsY):
            ymin = histMC.GetYaxis().GetBinLowEdge(ybin+1)
            ymax = histMC.GetYaxis().GetBinUpEdge(ybin+1)
            scaleLine = ["$%.2f |\eta| < %.2f$" % (ymin, ymax)]
            for xbin in range(nbinsX):
                binPair = (ybin, xbin)
                if binPair not in effResultMC or binPair not in effResultRD:
                    scaleLine.append("$0$")
                    continue

                effValMC = effResultMC[binPair]
                effValRD = effResultRD[binPair]

                if effValMC[0] == 0 or effValRD[0] == 0:
                    scale, scaleErrHi, scaleErrLo = 0,0,0
                else:
                    scale = effValRD[0]/effValMC[0]
                    scaleErrHi = scale*hypot(effValRD[1]/effValRD[0], effValMC[1]/effValMC[0])
                    scaleErrLo = scale*hypot(effValRD[2]/effValRD[0], effValMC[2]/effValMC[0])

                scaleLine.append("$%.3f^{+%.3f}_{-%.3f}$" % (scale, scaleErrHi, scaleErrLo))

            scaleTable += " " + (" & ".join(scaleLine)) + " \\\\\n"
        print>>fout, """\\begin{table}[hbtp]
\\begin{tabular}{%s}
\hline
%s
\hline
\\end{tabular}
\\caption{Scale factor for %s}
\\end{table}
""" % (latexTableHeader, scaleTable, step+category)

        for hist in (histMC, histRD):
            hist.SetMarkerSize(1.5)
            hist.GetXaxis().SetRangeUser(20, 200)

        c = TCanvas("c_%s_%s_pt_abseta" % (step, category), "%s %s pt_abseta" % (step, category), 1000, 500)
        c.Divide(2,1)
        pad = c.cd(1)
        pad.SetLogx()
        histMC.Draw("COLZtext")
        pad = c.cd(2)
        pad.SetLogx()
        histRD.Draw("COLZtext")

        c.Print("image/"+c.GetName()+".pdf")
        c.Print("image/"+c.GetName()+".png")

        hists.extend((histMC, histRD))
        canvases.append(c)
