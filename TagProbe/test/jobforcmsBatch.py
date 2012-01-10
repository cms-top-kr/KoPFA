#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
import os
import re
import sys
import time
import commands

from PFElectron_TnP_Producer_Zee_cfg import *

files = ["Run2011A","Run2011B"]

currdir = commands.getoutput('pwd')
dir = currdir + "/batch/Out"

for sample in files:
    process.load("KoPFA.TagProbe.Sources.ELE.RD.patTuple_"+sample+"_cff")
    out = open('batch/PFElectron_TnP_Producer_Zee_'+sample+'_cfg.py','w')
    out.write(process.dumpPython())
    out.close()
    os.system("rm -rf "+dir+"/Log/"+sample)
    os.system("rm -rf "+dir+"/Res/"+sample)
    os.system("rfmkdir "+dir+"/Log")
    os.system("rfmkdir "+dir+"/Res")
    os.system("rfmkdir "+dir+"/Log/"+sample)
    os.system("rfmkdir "+dir+"/Res/"+sample)
    os.system("cmsBatch.py 1 batch/PFElectron_TnP_Producer_Zee_"+sample+"_cfg.py -o "+dir+"/Log/"+sample+" -r "+dir+"/Res/"+sample+" -b 'bsub -q 1nh < batchScript.sh'")



