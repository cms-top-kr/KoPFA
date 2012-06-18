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
decay = sys.argv[2]

mclist = ["ZJets","ZtauDecay","WJetsToLNu", "WW", "WZ", "ZZ","TTbarTuneZ2","TTbarOthers"]
mclist += ["SingleToptW","SingleTopBartW"]
#mclist += ["ZJets10To50","ZtauDecay10To50"]
rdlist = ["Run2012AMuMu","Run2012BMuMu"]
#rdlist += ["Run2012AElEl","Run2012BElEl"]
#rdlist += ["Run2012AMuEl","Run2012BMuEl"]

samplePath = {}
samplePath["ZJets"]           ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_ZJets_cff"
samplePath["ZtauDecay"]       ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_ZJets_cff"
samplePath["ZJets10To50"]     ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_ZJets10To50_cff"
samplePath["ZtauDecay10To50"] ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_ZJets10To50_cff"
samplePath["WJetsToLNu"]      ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_WJets_cff"
samplePath["WW"]              ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_WW_cff"
samplePath["WZ"]              ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_WZ_cff"
samplePath["ZZ"]              ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_ZZ_cff"
samplePath["TTbarTuneZ2"]     ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_TTbarTuneZ2_cff"
samplePath["TTbarOthers"]     ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_TTbarTuneZ2_cff"
samplePath["SingleToptW"]     ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_Ttw_cff"
samplePath["SingleTopBartW"]  ="KoPFA.CommonTools.Sources.CMG.V5_4_0.MC.Summer12.patTuple_Tbartw_cff"
samplePath["Run2012AMuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.patTuple_Run2012ADoubleMu_cff"
samplePath["Run2012AElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.patTuple_Run2012ADoubleElectron_cff"
samplePath["Run2012BMuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.patTuple_Run2012BDoubleMu_cff"
samplePath["Run2012BElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.patTuple_Run2012BDoubleElectron_cff"
#samplePath["Run2011MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_4_0.RD.Run2012.patTuple_Run2011_cff"

def applyFilter(sample):

  process.GenZmassFilter.applyFilter = False
  process.topWLeptonGenFilter.applyFilter = False

  if sample.find("Run") != -1:
    process.JetEnergyScale.globalTag = cms.untracked.string('GR_R_42_V23')
    process.JetEnergyScale.doResJec = cms.untracked.bool(True)
  else:
    process.JetEnergyScale.globalTag = cms.untracked.string('START42_V17')
    process.JetEnergyScale.doResJec = cms.untracked.bool(False)
    

  if sample.find("ZJets") != -1 or sample.find("ZtauDecay") != -1:
    process.GenZmassFilter.applyFilter = True
    if sample.find("tau") != -1:
      process.GenZmassFilter.decayMode = [15]
    else:
      process.GenZmassFilter.decayMode = [11, 13]

  if sample.find("TTbar") != -1:
    process.topWLeptonGenFilter.applyFilter = True
    if sample.find("Others") != -1:
      process.p.replace(process.topWLeptonGenFilter,~process.topWLeptonGenFilter)
    #else:
    # need to check if there is already ~topWLeptonGenFilter : just to make sure TTbarOthers is called at the end for the time being.
    #  process.p.replace(process.~topWLeptonGenFilter,process.topWLeptonGenFilter)


def processSample( sample, dir):
    os.system("rm -rf "+dir+"/"+sample)
    os.system("rfmkdir "+dir+"/"+sample)
    os.system("rfmkdir "+dir+"/"+sample+"/Res")
    out = open(dir+'/cmg2kcms_'+sample+'_cfg.py','w')
    process.TFileService.fileName = cms.string('vallot_'+sample+'.root')
    process.load(samplePath[sample]) 

    #for z tau decay and ttbar dilepton filter
    applyFilter(sample)

    out.write(process.dumpPython())
    out.close()
    os.system("cmsBatch0.py 1 "+dir+'/cmg2kcms_'+sample+'_cfg.py'+" -o "+dir+"/"+sample+"/Log -r "+dir+"/"+sample+"/Res -b 'bsub -G u_CMS -q 1nh < batchScript.sh'")

currdir = commands.getoutput('pwd') 
print currdir

outdir = currdir+"/Out/"+decay

#if you want to save ntuple in castor
#outdir = "/castor/cern.ch/user/t/tjkim/ntuple/top/Out/"+decay

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


