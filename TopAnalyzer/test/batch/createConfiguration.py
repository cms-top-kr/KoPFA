#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# How to run: ./createConfiguration MuMu
import os
import re
import sys
import time
import commands

decay = sys.argv[1]

mclist = ["ZJets", "ZtauDecay", "DYmm20to50", "DYee20to50", "DYtt20to50", "DYmm10to20", "DYee10to20", "DYtt10to20", "WJetsToLNu", "VVJets", "TTbarTuneZ2","SingleTop_tW","QCD"]
datalist = ["Run2011A_PromptReco_v1", "Run2011A_PromptReco_v2"]

def common():
  script = """import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("KoPFA.TopAnalyzer.topAnalysis_cff")
"""
  return script

def mcsample(src):
  dir = ""
  if( decay == "MuEl"):
    dir = "EMU"
  elif( decay == "MuMu"):
    dir = "MU"
  elif( decay == "ElEl"):
    dir = "ELE"
  script = """
process.load("KoPFA.TopAnalyzer.Sources.%s.MC.Spring11.patTuple_%s_cff")
""" % (dir,src)
  return script

def mcpath():
  script = """
process.p = cms.Path(
    process.top%sAnalysisMCSequence
) 
""" % decay
  return script

def rdsample(src):
  dir = ""
  if( decay == "MuEl"):
    dir = "EMU"
  elif( decay == "MuMu"):
    dir = "MU"
  elif( decay == "ElEl"):
    dir = "ELE"
  script = """
process.load("KoPFA.TopAnalyzer.Sources.%s.RD.patTuple_%s_cff")
""" % (dir,src)
  return script


def rdpath():
  script = """
process.p = cms.Path(
    process.top%sAnalysisRealDataSequence
) 
""" % decay
  return script

def outfile(src):
  script = """
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_%s.root')
)
""" % src
  return script

def ttbarfilter():
  script = """
process.topWLeptonGenFilter.applyFilter = True
"""
  return script

def genzmassfilter():
  script = """
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.decayMode = [11, 13]
"""
  return script

def genzmasstaudecayfilter():
  script = """
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.decayMode = [15]
"""
  return script

def genzlowmassfilter():
  script = """
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.max = 50
"""
  return script

#os.system("mkdir "+decay)
 
for src in mclist:
    out = open(decay+'/top'+decay+'Analyzer_'+src+'_cfg.py','w')
    out.write(common())
    out.write(mcpath())
    out.write(outfile(src))
    if src.find("ZtauDecay") != -1:
      out.write(mcsample("ZJets"))
    else:
      out.write(mcsample(src))
    if src.find("TTbar") != -1:
      out.write(ttbarfilter())
    if src.find("ZJets") != -1:
      out.write(genzmassfilter())
    if src.find("ZtauDecay") != -1:
      out.write(genzmasstaudecayfilter())
    if src.find("20to50") != -1:
      out.write(genzlowmassfilter())
    out.close()

for src in datalist:
    out = open(decay+'/top'+decay+'Analyzer_'+src+'_cfg.py','w')
    out.write(common())
    out.write(rdpath())
    out.write(outfile(src))
    out.write(rdsample(src))
    out.close()
