#!/usr/bin/env python
import os
import re
import sys
import time

input = sys.argv[1]

def processSample(sample, dir):
    os.system("rfmkdir "+dir+"/"+sample)
    os.system("rm -rf Out/"+sample)
    os.system("cmsBatch.py 1 topMuMuAnalyzer_"+sample+"_cfg.py -o Out/"+sample+" -r "+dir+"/"+sample+"/vallot.root -b 'bsub -q 8nm < batchScript.sh'")

mcdir = "/castor/cern.ch/user/t/tjkim/ntuple/top/MuMu/MC/Spring10"
datadir = "/castor/cern.ch/user/t/tjkim/ntuple/top/MuMu/RD/Sep11"

if input == "status":
  os.system("rfdir "+mcdir) 
  os.system("rfdir "+datadir) 
elif input =="run":
  processSample("Zmumu",mcdir)
  processSample("TTbar",mcdir)
  processSample("Ztautau",mcdir)
  processSample("ZJets",mcdir)
  processSample("WJets",mcdir)
  processSample("VVJets",mcdir)
  processSample("SingleTop",mcdir)
  time.sleep(480)
  processSample("data_1",datadir)
  processSample("data_2",datadir)
  processSample("data_3",datadir)
  time.sleep(480)
  processSample("data_4",datadir)
  time.sleep(900)
  processSample("InclusiveMu15",mcdir)
elif input =="runmc":
  #processSample("Zmumu",mcdir)
  #processSample("TTbar",mcdir)
  #processSample("Ztautau",mcdir)
  #processSample("ZJets",mcdir)
  #processSample("WJets",mcdir)
  #processSample("VVJets",mcdir)
  #processSample("SingleTop",mcdir)
  #time.sleep(800)
  processSample("InclusiveMu15",mcdir)
elif input =="rundata":
  processSample("data_1",datadir)
  processSample("data_2",datadir)
  processSample("data_3",datadir)
  time.sleep(800)
  processSample("data_4",datadir)
elif input == "removemc":
  os.system("rfrm -r "+ mcdir+"/Zmumu")
  os.system("rfrm -r "+ mcdir+"/TTbar")
  os.system("rfrm -r "+ mcdir+"/Ztautau")
  os.system("rfrm -r "+ mcdir+"/ZJets")
  os.system("rfrm -r "+ mcdir+"/WJets")
  os.system("rfrm -r "+ mcdir+"/VVJets")
  os.system("rfrm -r "+ mcdir+"/SingleTop")
  os.system("rfrm -r "+ mcdir+"/InclusiveMu15")
elif input == "removedata":
  os.system("rfrm -r "+ datadir+"/data_1")
  os.system("rfrm -r "+ datadir+"/data_2")
  os.system("rfrm -r "+ datadir+"/data_3")
  os.system("rfrm -r "+ datadir+"/data_4")
else:
  print "ERROR!"
  print "OPTION: 'status' , 'run data', 'run mc', 'remove data', 'remove mc'"
