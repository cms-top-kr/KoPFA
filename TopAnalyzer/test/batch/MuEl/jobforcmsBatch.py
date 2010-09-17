#!/usr/bin/env python
import os
import re
import sys
import time

input = sys.argv[1]

def processSample(sample, dir):
    os.system("rfmkdir "+dir+"/"+sample)
    os.system("rm -rf Out/"+sample)
    os.system("cmsBatch.py 1 topMuElAnalyzer_"+sample+"_cfg.py -o Out/"+sample+" -r "+dir+"/"+sample+"/vallot.root -b 'bsub -q 1nh < batchScript.sh'")

mcdir = "/castor/cern.ch/user/t/tjkim/ntuple/top/MuEl/MC/Spring10"
datadir = "/castor/cern.ch/user/t/tjkim/ntuple/top/MuEl/RD/Sep11"

if input == "status":
  os.system("rfdir "+mcdir) 
  os.system("rfdir "+datadir) 
elif input =="runmc":
  processSample("TTbar",mcdir)
  processSample("Ztautau",mcdir)
  processSample("ZJets",mcdir)
  processSample("WJets",mcdir)
  processSample("VVJets",mcdir)
  processSample("SingleTop",mcdir)
elif input =="rundata":
  processSample("data_1",datadir)
  processSample("data_2",datadir)
  processSample("data_3",datadir)
  time.sleep(120)
  processSample("data_4",datadir)
elif input == "removemc":
  os.system("rfrm -r "+ mcdir)
elif input == "removedata":
  os.system("rfrm -r "+ datadir)
else:
  print "ERROR!"
  print "OPTION: 'status' , 'rundata', 'runmc', 'removedata', 'removemc'"
