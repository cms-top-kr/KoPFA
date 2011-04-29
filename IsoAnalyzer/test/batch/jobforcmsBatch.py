#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# Filename: analysis.py
# How to run: ./jobforcmsBatch status ElEl 
import os
import re
import sys
import time

input = sys.argv[1]
#type = sys.argv[2]

#mclist = ["Pt_15to30","Pt_30to50","Pt_50to80","Pt_80to120","Pt_120to170","Pt_170to300","Pt_300to470","Pt_470to600"]
mclist = ["TTbar","Wmunu","ZmmPU"]
#mclist = ["QCD"]
datalist = ["data_1","data_2"]

def processSample(sample, dir):
    os.system("rfmkdir "+dir+"/"+sample)
    os.system("rm -rf Out/"+sample)
    os.system("cmsBatch.py 1 MuonIsoAna_"+sample+"_cfg.py -o Out/"+sample+" -r "+dir+"/"+sample+" -b 'bsub -q 1nh < batchScript.sh'")

import os,commands
currdir = commands.getoutput('pwd') 
print currdir
mcdir = currdir+"/test"
datadir = mcdir
mcdir = "/castor/cern.ch/user/t/tjkim/ntuple/iso/QCD/MC/Fall10_v3"
#datadir = "/castor/cern.ch/user/t/tjkim/ntuple/iso/"+type+"/RD/Nov22_TightMU"

if input == "status":
  print mcdir
  os.system("rfdir "+mcdir) 
  print datadir
  os.system("rfdir "+datadir) 
elif input =="run":
#  for s in mclist:
#    processSample(s,mcdir)
#  time.sleep(480)
  for s in datalist:
    processSample(s,datadir)
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
  print "OPTION: 'status' , 'run', 'removedata', 'removemc'"
