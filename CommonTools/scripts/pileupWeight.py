#!/usr/bin/env python

import sys, os

usage = """Usage : %s name pileup.root
""" % sys.argv[0]

if len(sys.argv) < 3:
    print usage
    sys.exit()

name = sys.argv[1]
fileName = sys.argv[2]
values = []

import FWCore.ParameterSet.Config as cms

import KoPFA.CommonTools.PileUpWeight_cff as puw

from ROOT import *
fPileup = TFile(fileName)
if not fPileup or not fPileup.IsOpen():
    print "Cannot open file, ", fileName
    sys.exit(1)

hPileup = fPileup.Get("pileup")
if not hPileup or hPileup.GetNbinsX() < 10:
    print "Cannot open histogram, pileup from the file ", fileName
    sys.exit(1)

for i in range(1, hPileup.GetNbinsX()+1):
    values.append(hPileup.GetBinContent(i))

setattr(puw, name, cms.vdouble(values))

fOutput = open(os.environ["CMSSW_BASE"]+"/src/KoPFA/CommonTools/python/PileUpWeight_cff.py", "w")
print>>fOutput, "import FWCore.ParameterSet.Config as cms"
print>>fOutput, ""
for i in dir(puw):
    item = getattr(puw, i)
    if cms.vdouble != type(item): continue

    print>>fOutput, i, "=", item
    print>>fOutput, ""

