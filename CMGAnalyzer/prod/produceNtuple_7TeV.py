#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# How to run: ./produceNtuple data
import os
import re
import sys
import time
import os,commands

from cmg2kcms_7TeV_cfg import *

input = sys.argv[1]

mclist = ["ZJets","ZJets10To50","TTbarTuneZ2"]
mclist = ["WJetsToLNu", "WW", "WZ", "ZZ"]
mclist += ["SingleToptW","SingleTopBartW"]
mclist += ["TTbarTuneZ2matchingdown","TTbarTuneZ2matchingup","TTbarTuneZ2mcatnlo","TTbarTuneZ2powheg","TTbarTuneZ2scaledown","TTbarTuneZ2scaleup"]

rdlist = ["Run2011A_MuMu","Run2011B_MuMu"]
rdlist += ["Run2011Av1_MuEl","Run2011Av2_MuEl","Run2011Av3_MuEl","Run2011Av4_MuEl","Run2011B_MuEl"]
rdlist += ["Run2011A_ElEl","Run2011B_ElEl"]

samplePath = {}
samplePath["ZJets"]           ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Fall11.cmgTuple_ZJets_cff"
samplePath["ZJets10To50"]     ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Fall11.cmgTuple_ZJets10To50_cff"
samplePath["WJetsToLNu"]      ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Fall11.cmgTuple_WJets_cff"
samplePath["WW"]              ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Fall11.cmgTuple_WW_cff"
samplePath["WZ"]              ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Fall11.cmgTuple_WZ_cff"
samplePath["ZZ"]              ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Fall11.cmgTuple_ZZ_cff"
samplePath["TTbarTuneZ2"]     ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Fall11.patTuple_TTbarTuneZ2_cff"
samplePath["SingleToptW"]     ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Fall11.cmgTuple_TtW_cff"
samplePath["SingleTopBartW"]  ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Fall11.cmgTuple_TbartW_cff"
samplePath["TTH"]              ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Fall11.cmgTuple_TTH_HToBB_M125_cff"
### DATA ####
samplePath["Run2011A_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Run2011.cmgTuple_MuMu_Run2011A16Jan2012v1_cff"
samplePath["Run2011B_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Run2011.cmgTuple_MuMu_Run2011B16Jan2012v1_cff"
samplePath["Run2011A_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Run2011.cmgTuple_ElEl_Run2011A16Jan2012v1_cff"
samplePath["Run2011B_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Run2011.cmgTuple_ElEl_Run2011B16Jan2012v1_cff"
samplePath["Run2011Av1_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Run2011.cmgTuple_MuEl_Run2011A05Aug2011v1_cff"
samplePath["Run2011Av2_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Run2011.cmgTuple_MuEl_Run2011AMay10ReRecov1_cff"
samplePath["Run2011Av3_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Run2011.cmgTuple_MuEl_Run2011APromptRecov4_cff"
samplePath["Run2011Av4_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Run2011.cmgTuple_MuEl_Run2011APromptRecov6_cff"
samplePath["Run2011B_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_12_0_44X.Run2011.cmgTuple_MuEl_Run2011BPromptRecov1_cff"

def applyFilter(sample, process):

  #process.GenZmassFilterMuMu.applyFilter = False
  #process.GenZmassFilterMuEl.applyFilter = False
  #process.GenZmassFilterElEl.applyFilter = False

  if sample.find("Run") != -1:
    applyJSON(process, json )
    process.hltHighLevelMuMu = process.hltHighLevelMuMuRD.clone()
    process.hltHighLevelMuEl = process.hltHighLevelMuElRD.clone()
    process.hltHighLevelElEl = process.hltHighLevelElElRD.clone()
  else:
    process.hltHighLevelMuMu = process.hltHighLevelMuMuMC.clone()
    process.hltHighLevelMuEl = process.hltHighLevelMuElMC.clone()
    process.hltHighLevelElEl = process.hltHighLevelElElMC.clone()

  #if sample.find("ZJets") != -1 or sample.find("ZtauDecay") != -1:
  #  process.GenZmassFilterMuMu.applyFilter = True
  #  process.GenZmassFilterMuEl.applyFilter = True
  #  process.GenZmassFilterElEl.applyFilter = True

  #  if sample.find("tau") != -1:
  #    process.GenZmassFilterMuMu.decayMode = [15]
  #    process.GenZmassFilterMuEl.decayMode = [15]
  #    process.GenZmassFilterElEl.decayMode = [15]
  #  else:
  #    process.GenZmassFilterMuMu.decayMode = [11,13]
  #    process.GenZmassFilterMuEl.decayMode = [11,13]
  #    process.GenZmassFilterElEl.decayMode = [11,13]

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
    #os.system("cmsBatch0.py 1 "+dir+'/cmg2kcms_'+sample+'_cfg.py'+" -o "+dir+"/"+sample+"/Log -r "+dir+"/"+sample+"/Res -b 'bsub -q 1nh < batchScript.sh'")
    os.system("cmsBatch0.py 1 "+dir+'/cmg2kcms_'+sample+'_cfg.py'+" -o "+dir+"/"+sample+"/Log -r "+dir+"/"+sample+"/Res -b 'bsub -G u_zh -q 1nh < batchScript.sh'")

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
    time.sleep(60)
elif input == "data":
  for s in rdlist:
    processSample(s, outdir)  
    time.sleep(60)
elif input == "all":
  for s in mclist:
    processSample(s, outdir)
    time.sleep(60)
  for s in rdlist:
    processSample(s, outdir)
    time.sleep(60)

