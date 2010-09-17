#!/usr/bin/env python
import os
import re
import sys
import time

input = sys.argv[1]

def processSample(sample, dir):
    os.system("rfmkdir "+dir+"/"+sample)
    os.system("rm -rf Out/"+sample)
    os.system("cmsBatch.py 1 topElElAnalyzer_"+sample+"_cfg.py -o Out/"+sample+" -r "+dir+"/"+sample+"/vallot.root -b 'bsub -q 8nm < batchScript.sh'")

mcdir = "/castor/cern.ch/user/t/tjkim/ntuple/top/ElEl/MC/Spring10"
datadir = "/castor/cern.ch/user/t/tjkim/ntuple/top/ElEl/RD/Sep11"

if input == "status":
  os.system("rfdir "+mcdir) 
  os.system("rfdir "+datadir) 
elif input =="runmc":
  processSample("Zee",mcdir)
  processSample("TTbar",mcdir)
  processSample("Ztautau",mcdir)
  processSample("ZJets",mcdir)
  processSample("WJets",mcdir)
  processSample("VVJets",mcdir)
  processSample("SingleTop",mcdir)
  processSample("QCD_BCtoE_Pt2030",mcdir)
  processSample("QCD_BCtoE_Pt3080",mcdir)
elif input =="rundata":
  #processSample("data_1",datadir)
  #processSample("data_2",datadir)
  #processSample("data_3",datadir)
  #time.sleep(100)
  processSample("data_4",datadir)
elif input == "removemc":
  os.system("rfrm -r "+ mcdir)
elif input == "removedata":
  os.system("rfrm -r "+ datadir)
else:
  print "ERROR!"
  print "OPTION: 'status' , 'run data', 'run mc', 'remove data', 'remove mc'"
