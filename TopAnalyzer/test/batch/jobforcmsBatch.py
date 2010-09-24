#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# Filename: analysis.py
# How to run: ./jobforcmsBatch status ElEl 
import os
import re
import sys
import time

input = sys.argv[1]
type = sys.argv[2]

if type == "MuMu":
  mclist = ["ZJets", "Ztautau", "WJets", "VVJets", "TTbar", "SingleTop", "Zmumu", "DYmumu"]
  #qcdlist =["InclusiveMu15"]
  qcdlist =[""]
elif type == "ElEl":
  mclist = ["ZJets", "Ztautau", "WJets", "VVJets", "TTbar", "SingleTop", "Zee", "DYee"]
  qcdlist =[""]
elif type == "MuEl":
  mclist = ["ZJets", "Ztautau", "WJets", "VVJets", "TTbar", "SingleTop", "Zee", "DYee"]
  qcdlist =[""]

datalist = ["data_1","data_2","data_3","data_4"]

def processSample(sample, dir):
    os.system("rfmkdir "+dir+"/"+sample)
    os.system("rm -rf Out/"+sample)
    os.system("cmsBatch.py 1 top"+type+"Analyzer_"+sample+"_cfg.py -o Out/"+sample+" -r "+dir+"/"+sample+"/vallot.root -b 'bsub -q 8nm < batchScript.sh'")

mcdir = "/castor/cern.ch/user/t/tjkim/ntuple/top/"+type+"/MC/Spring10"
datadir = "/castor/cern.ch/user/t/tjkim/ntuple/top/"+type+"/RD/Sep11"

if input == "status":
  print mcdir
  os.system("rfdir "+mcdir) 
  print datadir
  os.system("rfdir "+datadir) 
elif input =="run":
  for s in mclist:
    processSample(s,mcdir)
#  time.sleep(240)
#  for s in datalist:
#    time.sleep(240)
#    processSample(s,datadir)
#  for s in qcdlist:
#    time.sleep(600)
#    processSample(s,mcdir)
elif input == "removemc":
  for s in mclist:
    os.system("rfrm -r "+ mcdir+"/"+s)
#  for s in qcdlist:
#    os.system("rfrm -r "+ mcdir+"/"+s)
elif input == "removedata":
  for s in datalist:
    os.system("rfrm -r "+ datadir+"/"+s)
else:
  print "ERROR!"
  print "OPTION: 'status' , 'run', 'remove data', 'remove mc'"
