#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# Filename: analysis.py
# How to run: ./copy.py status mc ElEl 
import os
import re
import sys
import time

#os.system("voms-proxy-init -voms cms")

pfnBaseURLs = {}
pfnBaseURLs['T2_BE_IIHE'] = 'srm://maite.iihe.ac.be:8443/srm/managerv2?SFN=/pnfs/iihe/cms/ph/sc4'
pfnBaseURLs['T2_UK_London_IC'] = 'srm://gfe02.grid.hep.ph.ic.ac.uk/pnfs/hep.ph.ic.ac.uk/data/cms'
pfnBaseURLs['T2_IT_Roma'] = 'srm://cmsrm-se01.roma1.infn.it/pnfs/roma1.infn.it/data/cms'
pfnBaseURLs['T2_US_Florida'] = 'srm://srmb.ihepa.ufl.edu/cms/data'
pfnBaseURLs['T2_DE_DESY'] = 'srm://dcache-se-cms.desy.de:8443/srm/managerv2?SFN=/pnfs/desy.de/cms/tier2'

location = pfnBaseURLs['T2_DE_DESY']
fileNames = [
               '/store/mc/Fall11/TT_TuneZ2_7TeV-mcatnlo/AODSIM/PU_S6_START42_V14B-v1/0000/56FB9C88-492A-E111-A509-003048FFCB6A.root'
]

i = 0
for file in fileNames:
  prefix = file.split("/",5)
  outname = prefix[3]+"_"+prefix[4]+"_"+ str(i) +".root"
  print "copying... " + outname 
  os.system("lcg-cp -b -D srmv2 --vo cms \""+location+file+"\" "+"/tmp/tjkim/"+outname)
  os.system("rfcp /tmp/tjkim/"+outname+" /castor/cern.ch/user/t/tjkim/MC/Fall11/test")
  i = i + 1;



