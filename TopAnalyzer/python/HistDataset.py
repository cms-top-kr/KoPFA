#import FWCore.ParameterSet.Config as cms
#!/usr/bin/env python

#from PhysicsTools.PatAlgos.tools.pfTools import *

import sys, os
import re
from ROOT import *
from numpy import array

gROOT.SetStyle("Plain")
gStyle.SetOptTitle(0)
gStyle.SetOptStat(0)

class HistDataset:
    def __init__(self, name):
        self.name = name

        self.lumi = 0.0

        ## Data format : a JSON like dict
        ## setup_XX = {
        ##     LABEL1: {
        ##         "color" : INTEGER
        ##         "samples" : {
        ##             NAME : {
        ##                 "xsec" : DOUBLE
        ##                 "files" : [FILE1, FILE2, FILE3...]
        ##             }
        ##         }
        ##     }
        ## }
        self.setup_rd = {}
        self.setup_mc = {}

        self.labels_sig = []
        self.labels_bkg = []

        self.canvases = []
        self.hStacks = []
        self.legends = []

    def addData(self, label, files, color, lumi):
        if label not in self.setup_rd:
            #self.labels_rd.append(label)
            self.setup_rd[label] = {}
            self.setup_rd[label]["files"] = []
        self.setup_rd[label]["color"] = color
        if type(files) == str:
            files = [files]
        self.setup_rd[label]["files"].extend(files)

        self.lumi += lumi

    def addSignal(self, name, label, files, color, xsec):
        if label not in self.labels_sig:
            self.labels_sig.append(label)
            self.setup_mc[label] = {'type':'Signal'}
        setup = self.setup_mc[label]
        setup["color"] = color
        self.__addMCFiles__(name, files, xsec, setup)

    def addBackground(self, name, label, files, color, xsec):
        if label not in self.labels_bkg:
            self.labels_bkg.append(label)
            self.setup_mc[label] = {'type':'Background'}
        setup = self.setup_mc[label]
        setup["color"] = color
        self.__addMCFiles__(name, files, xsec, setup)

    def __addMCFiles__(self, name, files, xsec, setup):
        if "samples" not in setup:
            setup["samples"] = {}
        if name not in setup["samples"]:
            setup["samples"][name] = {}
        setup["samples"][name]["xsec"] = xsec
        if "files" not in setup["samples"][name]:
            setup["samples"][name]["files"] = []

        if type(files) == str:
            files = [files]
        for file in files:
            if not re.match("^.*\.root$", file): continue
            if not os.path.exists(file): 
                print "Cannot find file", file
                continue
            setup["samples"][name]["files"].append(file)

    def listSamples(self):
        ## Get width of name field for pretty printing
        w = len("Data")
        for label in self.setup_mc:
            for name in self.setup_mc[label]["samples"]:
                w = max(w, len(name))
        labelForm = "%" + ("%ds" % (w+2)) + " % 10.3f pb"

        ## Print real data info
        print "="*(19+w/2), "Real data", "="*(18+w/2)
        print " "*(w-9), "Total lumi % 10.3f pb^{-1}" % self.lumi
        print

        ## Print MC signal info
        print "="*(20+w/2), "Signal", "="*(20+w/2)
        print " "*(w-5), "SAMPLE |     XSEC   |   nEvents | Sample lumi"
        for label in self.labels_sig:
            for name in self.setup_mc[label]["samples"]:
                sampleInfo = self.setup_mc[label]["samples"][name]
                xsec = sampleInfo["xsec"]
                nEvent = 0
                for file in sampleInfo["files"]:
                    f = TFile(file)
                    if f == None or not f.IsOpen(): continue
                    h = f.Get("%s/EventSummary" % self.name)
                    if h == None: continue
                    nEvent += h.GetBinContent(1)
                print labelForm % (name, xsec), "% 10d" % nEvent, "% 13.2f /pb" % (nEvent/xsec)
        print

        ## Print MC background info
        print "="*(18+w/2), "Background", "="*(18+w/2)
        print " "*(w-5), "SAMPLE |     XSEC   |   nEvents | Sample lumi"
        for label in self.labels_bkg:
            for name in self.setup_mc[label]["samples"]:
                sampleInfo = self.setup_mc[label]["samples"][name]
                xsec = sampleInfo["xsec"]
                nEvent = 0
                for file in sampleInfo["files"]:
                    f = TFile(file)
                    if f == None or not f.IsOpen(): continue
                    h = f.Get("%s/EventSummary" % self.name)
                    if h == None: continue
                    nEvent += h.GetBinContent(1)
                print labelForm % (name, xsec), "% 10d" % nEvent, "% 13.2f /pb" % (nEvent/xsec)
            print

        print "-"*(47+w)

    def printCutSteps(self):
        cutFlowTable = {}
        for label in self.labels_sig+self.labels_bkg:
            for name in self.setup_mc[label]["samples"]:
                sampleInfo = self.setup_mc[label]["samples"][name]
                xsec = sampleInfo["xsec"]
                cutFlowCount = {}
                for file in sampleInfo["files"]:
                    f = TFile(file)

                    nEvent = f.Get("%s/EventSummary" % self.name).GetBinContent(1)

                    dir = f.GetDirectory(self.name)
                    keys = dir.GetListOfKeys()
                    for i in range(0, keys.GetEntries()):
                        key = keys.At(i).GetName()
                        if "Step" not in key: continue

                        cutStepDir = dir.GetDirectory(key)
                        if key not in cutFlowCount:
                            cutFlowCount[key] = 0

                        cutFlowCount[key] += cutStepDir.Get("hNEvents").GetBinContent(2)/nEvent*xsec*self.lumi
            cutFlowTable[label] = cutFlowCount

        w = 0
        for label in self.labels_sig+self.labels_bkg:
            w = max(w, len(label))

        cutFlowTableContent = []
        cutFlowTableHeader = []
        labelForm = " % "+("%d" % w)+"s "
        for label in self.labels_sig+self.labels_bkg:
            line = labelForm % label
            keys = cutFlowTable[label].keys()
            keys.sort()
            if cutFlowTableHeader == []:
                cutFlowTableHeader = keys
            for key in keys:
                line += "%12.2f" % cutFlowTable[label][key]
            cutFlowTableContent.append(line+" ")
        print "="*((len(cutFlowTableContent[0])-len(self.name)-1)/2), self.name, "="*((len(cutFlowTableContent[0])-len(self.name)-1)/2)
        print (" "*(w+2)), 
        for item in cutFlowTableHeader:
            print "%11s" % item,
        print
        print "\n".join(cutFlowTableContent)
        print "="*(len(cutFlowTableContent[0]))

    def findHistograms(self, rootDir, hists):
        basePath = rootDir.GetPath().split(":")[-1]
        keys = rootDir.GetListOfKeys()
        for i in range(0, keys.GetEntries()):
            key = keys.At(i).GetName()
            obj = rootDir.Get(key)
            if obj.IsA().InheritsFrom("TH1"):
                hists.add(os.path.join(basePath, key))
            elif obj.IsA().InheritsFrom("TDirectory"):
                self.findHistograms(obj, hists)

    def draw(self, histSetups):
        ## Make list of histograms (without duplication)
        allHists = set()
        for label in self.setup_rd:
            for file in self.setup_rd[label]["files"]:
                self.findHistograms(TFile(file), allHists)
        for label in self.setup_mc:
            for name in self.setup_mc[label]["samples"]:
                for file in self.setup_mc[label]["samples"][name]["files"]:
                    self.findHistograms(TFile(file), allHists)

        ## Pick up histograms matching to the given histogram sets
        hists = {}
        for hist in allHists:
            for pattern in histSetups.keys():
                if not re.match("^/%s/%s$" % (self.name, pattern), hist): continue
                hists[hist] = histSetups[pattern]

        ## Draw all
        for hist in hists:
            gROOT.cd()
            c = TCanvas("c"+hist.replace("/", "_"), hist, 500, 500)
            self.__draw__(hist, hists[hist], c)
            self.canvases.append(c)

    def __draw__(self, hist, histSetup, canvas):
        gROOT.cd()

        if 'logy' in histSetup:
            canvas.SetLogy(histSetup['logy'])

        hStack = THStack("hs"+hist.replace("/", "_"), hist)
        if "y" in histSetup and len(histSetup["y"]) == 2:
            hStack.SetMinimum(histSetup["y"][0])
            hStack.SetMaximum(histSetup["y"][1])

        legend = TLegend(0.72, 0.67, 0.97, 0.97)
        legend.SetFillColor(kWhite)

        hSums = []

        for label in self.labels_sig+self.labels_bkg:
            color = self.setup_mc[label]["color"]

            ## Make scaled histogram
            hSum = None
            if "x" in histSetup and len(histSetup["x"]) > 2:
                bins = array(histSetup["x"], 'd')
                hSum = TH1F("hSumMC_"+hist.replace("/", "_")+"%d"%(self.labels_sig+self.labels_bkg).index(label), "hTemp", len(bins)-1, bins)

            for name in self.setup_mc[label]["samples"]:
                sampleInfo = self.setup_mc[label]["samples"][name]
                hSum = self.__accumulateHistograms__(sampleInfo, hist, hSum)
            if hSum == None: continue

            hSum.SetLineColor(color)
            hSum.SetFillColor(color)
            hStack.Add(hSum)
            hSums.append((hSum, label))

        hStack.Draw("hist")

        hSums.reverse()
        for h, label in hSums:
            legend.AddEntry(h, label, "LF")

        for label in self.setup_rd:
            color = self.setup_rd[label]["color"]
            hSum = None
            if "x" in histSetup and len(histSetup["x"]) > 2:
                bins = array(histSetup["x"], 'd')
                hSum = TH1F("hSumRD_"+hist.replace("/", "_")+"%d"%self.setup_rd.keys().index(label), "hTemp", len(bins)-1, bins)

            for file in self.setup_rd[label]["files"]:
                f = TFile(file)
                h = f.Get(hist)
                if hSum == None:
                    gROOT.cd()
                    hSum = h.Clone("hSumRD_"+hist.replace("/", "_"))
                    hSum.Sumw2()
                    hSum.Reset()
                elif hSum.GetTitle() == "hTemp":
                    hSum.SetTitle(h.GetTitle())
                    hSum.GetXaxis().SetTitle(h.GetXaxis().GetTitle())
                    hSum.GetYaxis().SetTitle(h.GetYaxis().GetTitle())
                    if ( hSum.GetXaxis().GetBinLabel(1) != ""):
                        for bin in range(1, hSum.GetNbinsX()+1):
                            hSum.GetXaxis().SetBinLabel(bin, h.GetXaxis().GetBinLabel(bin))
                self.__addHist__(hSum, h)
            if hSum == None: continue

            hSum.SetLineColor(color)
            hSums.append((hSum, label))
            legend.AddEntry(hSum, label, "LP")
            hSum.Draw("same")

        legend.Draw()
        self.hStacks.append(hStack)
        self.hStacks.append(hSums)
        self.legends.append(legend)

    def __accumulateHistograms__(self, info, hist, hSum):
        xsec = info["xsec"]
        for file in info["files"]:
            f = TFile(file)
            nEvent = f.Get("%s/EventSummary" % self.name).GetBinContent(1)
            h = f.Get(hist)

            if hSum == None:
                gROOT.cd()
                hSum = h.Clone("hSum_"+hist.replace("/", "_"))
                hSum.Reset()
            elif hSum.GetTitle() == "hTemp":
                hSum.SetTitle(h.GetTitle())
                hSum.GetXaxis().SetTitle(h.GetXaxis().GetTitle())
                hSum.GetYaxis().SetTitle(h.GetYaxis().GetTitle())
                if ( hSum.GetXaxis().GetBinLabel(1) != ""):
                    for bin in range(1, hSum.GetNbinsX()+1):
                        hSum.GetXaxis().SetBinLabel(bin, h.GetXaxis().GetBinLabel(bin))

            h.Scale(xsec*self.lumi/nEvent)
            self.__addHist__(hSum, h)

        return hSum

    def __addHist__(self, h1, h2):
        nBins1 = h1.GetNbinsX()
        nBins2 = h2.GetNbinsX()
        isSameBin = (nBins1 == nBins2)
        if isSameBin:
            for bin in range(1, nBins1+1):
                xlo1 = h1.GetXaxis().GetBinLowEdge(bin)
                xlo2 = h2.GetXaxis().GetBinLowEdge(bin)
                xup1 = h1.GetXaxis().GetBinUpEdge(bin)
                xup2 = h2.GetXaxis().GetBinUpEdge(bin)
                if xlo1 != xlo2 or xup1 != xup2:
                    isSameBin = False
                    break

        if isSameBin:
            h1.Add(h2)
            return

        ## Do only for nBins2 > nBins1
        for bin1 in range(1, nBins1+1):
            lowerBin = h2.FindBin(h1.GetXaxis().GetBinLowEdge(bin1))
            upperBin = h2.FindBin(h1.GetXaxis().GetBinLowEdge(bin1+1))

            add = h1.GetBinContent(bin1)
            err2 = h1.GetBinError(bin1)**2
            for bin2 in range(lowerBin, upperBin):
                add += h2.GetBinContent(bin2)
                err2 += h2.GetBinError(bin2)

            h1.SetBinContent(bin1, add)
            h1.SetBinError(bin1, sqrt(err2))
