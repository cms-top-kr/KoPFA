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

location = pfnBaseURLs['T2_BE_IIHE']
fileNames = [
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0005/36D94209-ADE3-DF11-9040-00145E551385.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/DC31018F-06E3-DF11-9F4F-001D09675288.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0004/AA58573A-FCE2-DF11-B0F9-00145E551FF1.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0002/EA149FB1-1EE2-DF11-9ADD-00145E551805.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0002/DE88D0EE-65E2-DF11-BF62-00D0680BF984.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0002/D001EAAC-64E2-DF11-8C97-00D0680B8821.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0002/AE7BF2DF-53E2-DF11-BAD0-00145E5523CC.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0002/9E37B266-48E2-DF11-9215-00145E551FC4.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0002/86A4CE5B-64E2-DF11-84D1-00144F45F56E.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0002/42D1D8E0-1EE2-DF11-899E-00145E551A9B.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0002/264D2AFB-70E2-DF11-90FA-001D096766B0.root',
        '/store/mc/Fall10/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0001/B8FEF9BF-FDE1-DF11-A4F4-00D0680BF8E8.root'
]

i = 0
for file in fileNames:
  prefix = file.split("/",5)
  outname = prefix[3]+"_"+prefix[4]+"_"+ str(i) +".root"
  print "copying... " + outname 
  os.system("lcg-cp -b -D srmv2 --vo cms \""+location+file+"\" "+"/tmp/tjkim/"+outname)
  os.system("rfcp /tmp/tjkim/"+outname+" /castor/cern.ch/user/t/tjkim/MC/Fall10/test")
  i = i + 1;



