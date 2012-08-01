#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# How to run: ./produceNtuple data
import os
import re
import sys
import time
import os,commands

from cmg2kcms_cfg import *

input = sys.argv[1]

mclist = ["ZJets","ZtauDecay","WJetsToLNu", "WW", "WZ", "ZZ","TTbarTuneZ2"]
mclist += ["SingleToptW","SingleTopBartW"]
mclist += ["ZJets10To50","ZtauDecay10To50"]
rdlist = ["Run2012MuMu"]
rdlist += ["Run2012ElEl"]
rdlist += ["Run2012MuEl"]

samplePath = {}
samplePath["ZJets"]           ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.cmgTuple_ZJets_cff"
samplePath["ZtauDecay"]       ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.cmgTuple_ZJets_cff"
samplePath["ZJets10To50"]     ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.cmgTuple_ZJets10To50_cff"
samplePath["ZtauDecay10To50"] ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.cmgTuple_ZJets10To50_cff"
samplePath["WJetsToLNu"]      ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.cmgTuple_WJets_cff"
samplePath["WW"]              ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.cmgTuple_WW_cff"
samplePath["WZ"]              ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.cmgTuple_WZ_cff"
samplePath["ZZ"]              ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.cmgTuple_ZZ_cff"
samplePath["TTbarTuneZ2"]     ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_TTbarTuneZ2_cff"
samplePath["SingleToptW"]     ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.cmgTuple_Ttw_cff"
samplePath["SingleTopBartW"]  ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.cmgTuple_Tbartw_cff"
samplePath["Run2012MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.cmgTuple_Run2012DoubleMu_cff"
samplePath["Run2012ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.cmgTuple_Run2012DoubleElectron_cff"
samplePath["Run2012MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.cmgTuple_Run2012MuEl_cff"

def applyFilter(sample, process):

  process.GenZmassFilterMuMu.applyFilter = False
  process.GenZmassFilterMuEl.applyFilter = False
  process.GenZmassFilterElEl.applyFilter = False

  process.MuMu.topSample = False
  process.MuEl.topSample = False
  process.ElEl.topSample = False

  process.MuMu.zSample = False
  process.MuEl.zSample = False
  process.ElEl.zSample = False

  if sample.find("Run") != -1:
    process.JetEnergyScaleMuMu.globalTag = cms.untracked.string('GR_R_52_V9')
    process.JetEnergyScaleMuEl.globalTag = cms.untracked.string('GR_R_52_V9')
    process.JetEnergyScaleElEl.globalTag = cms.untracked.string('GR_R_52_V9')
    process.JetEnergyScaleMuMu.doResJec = cms.untracked.bool(True)
    process.JetEnergyScaleMuEl.doResJec = cms.untracked.bool(True)
    process.JetEnergyScaleElEl.doResJec = cms.untracked.bool(True)

    applyJSON(process, json )

  else:
    process.JetEnergyScaleMuMu.globalTag = cms.untracked.string('START52_V11')
    process.JetEnergyScaleMuEl.globalTag = cms.untracked.string('START52_V11')
    process.JetEnergyScaleElEl.globalTag = cms.untracked.string('START52_V11')
    process.JetEnergyScaleMuMu.doResJec = cms.untracked.bool(False)
    process.JetEnergyScaleMuEl.doResJec = cms.untracked.bool(False)
    process.JetEnergyScaleElEl.doResJec = cms.untracked.bool(False)

  if sample.find("ZJets") != -1 or sample.find("ZtauDecay") != -1:
    process.GenZmassFilterMuMu.applyFilter = True
    process.GenZmassFilterMuEl.applyFilter = True
    process.GenZmassFilterElEl.applyFilter = True

    process.MuMu.zSample = True
    process.MuEl.zSample = True
    process.ElEl.zSample = True


    if sample.find("tau") != -1:
      process.GenZmassFilterMuMu.decayMode = [15]
      process.GenZmassFilterMuEl.decayMode = [15]
      process.GenZmassFilterElEl.decayMode = [15]
    else:
      process.GenZmassFilterMuMu.decayMode = [11,13]
      process.GenZmassFilterMuEl.decayMode = [11,13]
      process.GenZmassFilterElEl.decayMode = [11,13]

  if sample.find("TTbar") != -1 :
    process.MuMu.topSample = True
    process.MuEl.topSample = True
    process.ElEl.topSample = True


def processSample( sample, dir):
    os.system("rm -rf "+dir+"/"+sample)
    os.system("rfmkdir "+dir+"/"+sample)
    os.system("rfmkdir "+dir+"/"+sample+"/Res")
    out = open(dir+'/cmg2kcms_'+sample+'_cfg.py','w')
    process.TFileService.fileName = cms.string('vallot_'+sample+'.root')
    process.load(samplePath[sample]) 

    #for z tau decay and data/MC
    applyFilter(sample,process)

    out.write(process.dumpPython())
    out.close()
    #os.system("cmsBatch0.py 3 "+dir+'/cmg2kcms_'+sample+'_cfg.py'+" -o "+dir+"/"+sample+"/Log -r "+dir+"/"+sample+"/Res -b 'bsub -G u_zh -q 1nh < batchScript.sh'")

currdir = commands.getoutput('pwd') 
print currdir

outdir = currdir+"/Out/"

#if you want to save ntuple in castor
#outdir = "/castor/cern.ch/user/t/tjkim/ntuple/top/Out/"

#to save log information in local
os.system("rfmkdir Out")
os.system("rfmkdir "+outdir)

if input == "mc":
  for s in mclist:
    processSample(s, outdir)
elif input == "data":
  for s in rdlist:
    processSample(s, outdir)  
elif input == "all":
  for s in mclist:
    processSample(s, outdir)
  for s in rdlist:
    processSample(s, outdir)


