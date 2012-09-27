#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# How to run: ./createNtuple data MuMu 
import os
import re
import sys
import time
import os,commands

sample = sys.argv[1]
decay = sys.argv[2]

mclist = ["ZJets","ZtauDecay", "ZJets10To50", "ZtauDecay10To50", "WJetsToLNu", "WW", "WZ", "ZZ", "TTbarTuneZ2","TTbarOthers","SingleToptW"]
mclist += ["TTbarMatchingUp","TTbarMatchingDw","TTbarScaleUp","TTbarScaleDw"]

#qcdlist = ["QCDPt20to30PCtoE","QCDPt30to80BCtoE","QCDPt80to170BCtoE","QCDPt20to30EM","QCDPt30to80EM","QCDPt80to170EM"]
qcdlist = ["QCD"]

datalist = ["Run2011"]

def processSample(ch, sample, dir):
    os.system("rm -rf "+dir+"/"+sample)
    os.system("rfmkdir "+dir+"/"+sample)
    os.system("rfmkdir "+dir+"/"+sample+"/Res")
    os.system("cmsBatch.py 1 "+ch+"/top"+ch+"Analyzer_"+sample+"_cfg.py -o "+dir+"/"+sample+"/Log -r "+dir+"/"+sample+"/Res -b 'bsub -G u_zh -q 1nh < batchScript.sh'")
    #os.system("cmsBatch.py 1 "+ch+"/top"+ch+"Analyzer_"+sample+"_cfg.py -o "+dir+"/"+sample+"/Log -r "+dir+"/"+sample+"/Res -b 'bsub -q 1nh < batchScript.sh'")

currdir = commands.getoutput('pwd') 
print currdir

outdir = currdir+"/Out/"+decay
#if you want to save ntuple in castor
#outdir = "/castor/cern.ch/user/t/tjkim/ntuple/top/Out/"+decay
#to save log information in local
os.system("rfmkdir Out")
os.system("rfmkdir "+outdir)

if sample == "all":
  for s in mclist:
    processSample(decay, s, outdir)
    time.sleep(60)
  for s in datalist:
    processSample(decay, s, outdir)
elif sample == "mc":
  for s in mclist:
    processSample(decay, s, outdir)
    time.sleep(15)
elif sample == "qcd":
  for s in qcdlist:
    processSample(decay, s, outdir)
elif sample == "data":
  for s in datalist:
    processSample(decay, s, outdir)
else:
  print "ERROR!"
  print "OPTION: 'all MuMu', 'mc MuMu', 'data MuMu', 'qcd MuMu'"

