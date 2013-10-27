#!/usr/bin/env python

from ROOT import *
gROOT.ProcessLine(".x rootlogon.C")

frivet = TFile("rivet.root")
fcmssw = TFile("tree.root")
tree = fcmssw.Get("genAnalysis/tree")

leg = TLegend(0.75, 0.75, 0.95, 0.95)
leg.SetBorderSize(0)
leg.SetFillStyle(0)

hists = []
canvases = []
def drawHistFromRivet(hName, varexp):
    hrivet = frivet.Get(hName)
    hcmssw = hrivet.Clone()
    hrivet.SetName(hName+"_RIVET")
    hcmssw.SetName(hName+"_CMSSW")

    tree.Draw("%s>>%s" % (varexp, hName+"_CMSSW"), "", "goff")
    for i in range(hcmssw.GetNbinsX()):
        w = hcmssw.GetXaxis().GetBinWidth(i+1)
        h = hcmssw.GetBinContent(i+1)
        hcmssw.SetBinContent(i+1, h/w)
    hcmssw.Scale(hrivet.Integral()/hcmssw.Integral())

    c = TCanvas("c%s" % hName, hName, 500, 500)
    hrivet.SetLineColor(kRed)
    hcmssw.SetLineColor(kBlue)
    hrivet.Draw("hist")
    hcmssw.Draw("samehist")

    if len(hists) == 0:
        leg.AddEntry(hcmssw, "CMSSW", "l")
        leg.AddEntry(hrivet, "RIVET", "l")
    leg.Draw()

    canvases.append(c)
    hists.append( (hrivet, hcmssw) )

drawHistFromRivet("lepton1_pT", "leptons[0].pt()")
drawHistFromRivet("lepton2_pT", "leptons[1].pt()")
#drawHistFromRivet("dilepton_mass", "dileptons.mass()")
#drawHistFromRivet("leptonJet_mass", "lbCands.mass()")
#drawHistFromRivet("bjet1_pT", "bjets[0].pt()")
#drawHistFromRivet("bjet2_pT", "bjets[1].pt()")
#drawHistFromRivet("top1_pT", "tCands[0].pt()")
#drawHistFromRivet("top2_pT", "tCands[1].pt()")
#drawHistFromRivet("top_pT", "tCands.pt()")
drawHistFromRivet("w_mass", "wCands.mass()")
drawHistFromRivet("top1_mass", "tCands[0].mass()")
drawHistFromRivet("top2_mass", "tCands[1].mass()")
drawHistFromRivet("neutrino1_pT", "neutrinos[0].pt()")
drawHistFromRivet("neutrino2_pT", "neutrinos[1].pt()")
#drawHistFromRivet("ttbar_pT", "ttCands.pt()")
