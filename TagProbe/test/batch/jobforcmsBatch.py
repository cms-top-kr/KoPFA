#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
import os
import re
import sys
import time
import commands

from PFElectron_TnP_Producer_Zee_cfg import *

files = ["Run2011A","Run2011B"]
#files = ["ZJets"]

currdir = commands.getoutput('pwd')
dir = currdir + "/Out"
#dir = "/castor/cern.ch/user/t/tjkim/ntuple/tnp/Dec19"

for sample in files:
    if sample == "Run2011A" or sample == "Run2011B":
      process.load("KoPFA.TagProbe.Sources.ELE.RD.patTuple_"+sample+"_cff")
    else:
      process.load("KoPFA.TagProbe.Sources.ELE.MC.patTuple_"+sample+"_cff")
      process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
    process.TFileService.fileName = cms.string("tnpTree_%s.root" % sample)
    out = open('PFElectron_TnP_Producer_Zee_'+sample+'_cfg.py','w')
    out.write(process.dumpPython())
    out.close()
    os.system("rm -r "+"Out/Log/"+sample)
    os.system("rfrm -r "+dir+"/Res/"+sample)
    os.system("mkdir "+"Out/Log")
    os.system("rfmkdir "+dir+"/Res")
    os.system("mkdir "+"Out/Log/"+sample)
    os.system("rfmkdir "+dir+"/Res/"+sample)
    os.system("cmsBatch.py 1 PFElectron_TnP_Producer_Zee_"+sample+"_cfg.py -o "+"Out/Log/"+sample+" -r "+dir+"/Res/"+sample+" -b 'bsub -q 8nh < batchScript.sh'")



