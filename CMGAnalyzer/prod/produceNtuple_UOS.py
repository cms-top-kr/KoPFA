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

#mclist = ["ZJets","ZJets10To50","WJetsToLNu", "WW", "WZ", "ZZ","TTbarTuneZ2"]
#mclist = ["TTbarFullLepMGDecays"] #TTbarTuneZ2"]
#mclist = ["WJetsToLNu","WZ"]
mclist = ["ZJets","ZJets10To50"]
mclist += ["WJetsToLNu", "WW", "WZ", "ZZ"]
mclist += ["SingleToptW","SingleTopBartW"]#,"TTH"]
mclist += ["TTbarFullLepMGDecays","TTbarSemiLeptMGDecays","TTbarHadronicMGDecays"]
#mclist = ["TTbarFullLeptP11","TTbarSemiLeptP11","TTbarHadronicP11"]
#mclist = ["SingleTopBartW","TTbarHadronicMGDecays"]
#mclist += ["TTbar161_5","TTbar184_5"]

#rdlist = ["Run2012Av1_MuMu","Run2012Av2_MuMu","Run2012B_MuMu","Run2012Cv1_MuMu","Run2012Cv2_MuMu","Run2012Cv3_MuMu","Run2012Dv1_MuMu"] #,"Run2012Dv2_MuMu"]
#rdlist += ["Run2012Av1_MuEl","Run2012Av2_MuEl","Run2012B_MuEl","Run2012Cv1_MuEl","Run2012Cv2_MuEl","Run2012Cv3_MuEl","Run2012Dv1_MuEl"] #,"Run2012Dv2_MuEl"]
#rdlist += ["Run2012Av1_ElEl","Run2012Av2_ElEl","Run2012B_ElEl","Run2012Cv1_ElEl","Run2012Cv2_ElEl","Run2012Cv3_ElEl","Run2012Dv1_ElEl"] #,"Run2012Dv2_ElEl"]
#rdlist = ["Run2012Cv1_MuMu","Run2012Cv1_MuEl"]
rdlist = ["Run2012A-22Jan2013-v1_MuMu","Run2012B-22Jan2013-v1_MuMu","Run2012C-22Jan2013-v1_MuMu","Run2012D-22Jan2013-v1_MuMu"]
rdlist += ["Run2012A-22Jan2013-v1_MuEl","Run2012B-22Jan2013-v1_MuEl","Run2012C-22Jan2013-v1_MuEl","Run2012D-22Jan2013-v1_MuEl"]
rdlist += ["Run2012A-22Jan2013-v1_ElEl","Run2012B-22Jan2013-v1_ElEl","Run2012C-22Jan2013-v1_ElEl","Run2012D-22Jan2013-v1_ElEl"]

samplePath = {}
samplePath["ZJets"]           ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_ZJets_cff"
samplePath["ZJets10To50"]     ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_ZJets10To50_cff"
#samplePath["ZtauDecay"]       ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_ZJets_cff"
#samplePath["ZtauDecay10To50"] ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_ZJets10To50_cff"
samplePath["WJetsToLNu"]      ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_WJets_cff"
samplePath["WW"]              ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_WW_cff"
samplePath["WZ"]              ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_WZ_cff"
samplePath["ZZ"]              ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_ZZ_cff"
samplePath["TTbarTuneZ2"]     ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTbarTuneZ2_cff"
samplePath["SingleToptW"]     ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TtW_cff"
samplePath["SingleTopBartW"]  ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TbartW_cff"
samplePath["TTH"]             ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTH_HToBB_M125_cff"
samplePath["TTbarFullLepMGDecays"] ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTbarFullLepMGDecays_cff"
samplePath["TTbarSemiLeptMGDecays"]="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTbarSemiLeptMGDecays_cff"
samplePath["TTbarHadronicMGDecays"]="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTbarHadronicMGDecays_cff"
samplePath["TTbarFullLeptP11"] ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTbarFullLeptP11_cff"
samplePath["TTbarSemiLeptP11"] ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTbarSemiLeptP11_cff"
samplePath["TTbarHadronicP11"] ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTbarHadronicP11_cff"
samplePath["TTbar161_5"]      = "KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTJets_mass161_5_TuneZ2star_cff"
samplePath["TTbar184_5"]      = "KoPFA.CommonTools.Sources.CMG.V5_13_0.Summer12.cmgTuple_TTJets_mass184_5_TuneZ2star_cff"

### DATA ####
samplePath["Run2012Av1_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Av1_MuMu_cff"
samplePath["Run2012Av1_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Av1_ElEl_cff"
samplePath["Run2012Av1_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Av1_MuEl_cff"
samplePath["Run2012Av2_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Av2_MuMu_cff"
samplePath["Run2012Av2_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Av2_ElEl_cff"
samplePath["Run2012Av2_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Av2_MuEl_cff"

samplePath["Run2012B_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012B_MuMu_cff"
samplePath["Run2012B_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012B_ElEl_cff"
samplePath["Run2012B_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012B_MuEl_cff"

samplePath["Run2012Cv1_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Cv1_MuMu_cff"
samplePath["Run2012Cv1_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Cv1_ElEl_cff"
samplePath["Run2012Cv1_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Cv1_MuEl_cff"

samplePath["Run2012Cv2_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Cv2_MuMu_cff"
samplePath["Run2012Cv2_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Cv2_ElEl_cff"
samplePath["Run2012Cv2_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Cv2_MuEl_cff"

samplePath["Run2012Cv3_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Cv3_MuMu_cff"
samplePath["Run2012Cv3_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Cv3_ElEl_cff"
samplePath["Run2012Cv3_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Cv3_MuEl_cff"

samplePath["Run2012Dv1_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Dv1_MuMu_cff"
samplePath["Run2012Dv1_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Dv1_ElEl_cff"
samplePath["Run2012Dv1_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Dv1_MuEl_cff"

samplePath["Run2012Dv2_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Dv2_MuMu_cff"
samplePath["Run2012Dv2_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Dv2_ElEl_cff"
samplePath["Run2012Dv2_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_13_0.Run2012.cmgTuple_Run2012Dv2_MuEl_cff"

#Data Rereco
samplePath["Run2012A-22Jan2013-v1_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012A-22Jan2013-v1_MuMu_cff"
samplePath["Run2012B-22Jan2013-v1_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012B-22Jan2013-v1_MuMu_cff"
samplePath["Run2012C-22Jan2013-v1_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012C-22Jan2013-v1_MuMu_cff"
samplePath["Run2012D-22Jan2013-v1_MuMu"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012D-22Jan2013-v1_MuMu_cff"

samplePath["Run2012A-22Jan2013-v1_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012A-22Jan2013-v1_MuEl_cff"
samplePath["Run2012B-22Jan2013-v1_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012B-22Jan2013-v1_MuEl_cff"
samplePath["Run2012C-22Jan2013-v1_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012C-22Jan2013-v1_MuEl_cff"
samplePath["Run2012D-22Jan2013-v1_MuEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012D-22Jan2013-v1_MuEl_cff"

samplePath["Run2012A-22Jan2013-v1_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012A-22Jan2013-v1_ElEl_cff"
samplePath["Run2012B-22Jan2013-v1_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012B-22Jan2013-v1_ElEl_cff"
samplePath["Run2012C-22Jan2013-v1_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012C-22Jan2013-v1_ElEl_cff"
samplePath["Run2012D-22Jan2013-v1_ElEl"]    ="KoPFA.CommonTools.Sources.CMG.V5_15_0.Run2012.cmgTuple_Run2012D-22Jan2013-v1_ElEl_cff"

def applyFilter(sample, process):

  #process.GenZmassFilterMuMu.applyFilter = False
  #process.GenZmassFilterMuEl.applyFilter = False
  #process.GenZmassFilterElEl.applyFilter = False

  if sample.find("Run") != -1:
    applyJSON(process, json )

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
    os.system("cmsBatch0.py 1 "+dir+'/cmg2kcms_'+sample+'_cfg.py'+" -o "+dir+"/"+sample+"/Log -r "+dir+"/"+sample+"/Res -b 'bsub -q 1nh < batchScript.sh'")
    #os.system("cmsBatch0.py 3 "+dir+'/cmg2kcms_'+sample+'_cfg.py'+" -o "+dir+"/"+sample+"/Log -r "+dir+"/"+sample+"/Res -b 'bsub -q 1nh -oo "+dir+"/"+"log < batchScript.sh'")
    #os.system("cmsBatch0.py 1 "+dir+'/cmg2kcms_'+sample+'_cfg.py'+" -o "+dir+"/"+sample+"/Log -r "+dir+"/"+sample+"/Res -b 'bsub -G u_zh -q 1nh < batchScript.sh'")

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


