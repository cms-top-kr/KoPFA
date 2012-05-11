#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# How to run: ./createNtuple data MuMu 
import os
import re
import sys
import time

sample = sys.argv[1]
decay = sys.argv[2]

mclist = ["ZJets", "WJetsToLNu", "TTbarTuneZ2"]

#datalist = ["Run2011A","Run2011B"]
datalist = ["Run2011_DecoupledIso"]

def processSample(sample, dir):
    os.system("rm -rf "+dir+"/Log/"+sample)
    os.system("rm -rf "+dir+"/Res/"+sample)
    os.system("rfmkdir "+dir+"/Res/"+sample)
    os.system("cmsBatch.py 1 "+"electronOptimizer_"+sample+"_cfg.py -o "+"Out/"+decay+"/Log/"+sample+" -r "+dir+"/Res/"+sample+" -b 'bsub -q 1nh < batchScript.sh'")

import os,commands
currdir = commands.getoutput('pwd') 
print currdir

outdir = currdir+"/Out/"+decay

#if you want to save ntuple in castor
#outdir = "/castor/cern.ch/user/t/tjkim/ntuple/top/Out/"+decay

#to save log information in local
os.system("rfmkdir Out")
os.system("rfmkdir "+outdir)
os.system("rfmkdir "+outdir+"/Log")
os.system("rfmkdir "+outdir+"/Res")

if sample == "all":
  for s in mclist:
    processSample(s,outdir)
  time.sleep(60)
  for s in datalist:
    processSample(s,outdir)
elif sample == "mc":
  for s in mclist:
    processSample(s,outdir)
elif sample == "qcd":
  for s in qcdlist:
    processSample(s,outdir)
elif sample == "data":
  for s in datalist:
    processSample(s,outdir)
else:
  print "ERROR!"
  print "OPTION: 'all MuMu', 'mc MuMu', 'data MuMu', 'qcd MuMu'"
