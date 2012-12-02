#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# Filename: analysis.py
# How to run: ./copy.py status mc ElEl 
import os
import re
import sys
import time
import commands

#os.system("voms-proxy-init -voms cms")

pfnBaseURLs = {}
pfnBaseURLs['T2_BE_IIHE'] = 'srm://maite.iihe.ac.be:8443/srm/managerv2?SFN=/pnfs/iihe/cms/ph/sc4'
pfnBaseURLs['T2_UK_London_IC'] = 'srm://gfe02.grid.hep.ph.ic.ac.uk/pnfs/hep.ph.ic.ac.uk/data/cms'
pfnBaseURLs['T2_IT_Roma'] = 'srm://cmsrm-se01.roma1.infn.it/pnfs/roma1.infn.it/data/cms'
pfnBaseURLs['T2_US_Florida'] = 'srm://srmb.ihepa.ufl.edu/cms/data'
pfnBaseURLs['T2_DE_DESY'] = 'srm://dcache-se-cms.desy.de:8443/srm/managerv2?SFN=/pnfs/desy.de/cms/tier2'

location = pfnBaseURLs['T2_DE_DESY']
fileNames = [
               '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v2/00000/0010005A-421A-E211-9E3C-E41F13181DA4.root'
               '/store/mc/Summer12_DR53X/TTJets_FullLeptMGDecays_8TeV-madgraph/AODSIM/PU_S10_START53_V7A-v2/00000/000C5D15-AB1A-E211-8BDE-00215E22053A.root'

  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/70EA5873-5AD2-E111-AE4F-003048D462C4.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/70CC5B25-C3D2-E111-85A7-001E6739751C.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/70B638CE-C6D2-E111-8430-003048673F0A.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/7041870B-D3D2-E111-8CFE-001E67397008.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/70300E2E-27D2-E111-92BD-001E67397AE4.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6ECBC437-E6D2-E111-9BC1-001E67397B25.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6EC5EF9D-E7D2-E111-98D0-003048D477B2.root'
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6EC4C520-C8D1-E111-8D4E-001E673972DD.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6E9EB30E-C1D2-E111-9479-001E673974EA.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6E4A8852-8ED2-E111-850B-003048D47A18.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6E2DFFE6-0ED2-E111-9085-001E67397CCE.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6E2B06E0-F6D2-E111-A725-001E67397E90.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6E225AE7-FFD1-E111-947B-003048D4773E.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6E0A64F3-A7D1-E111-8AD5-003048D460A8.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6CD59D99-A3D2-E111-963F-001E67398C1E.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6CD32FE1-E0D1-E111-9220-001E67398DE5.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6CC9C7E1-CED2-E111-8335-003048D45F2E.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6C9E5E58-A6D2-E111-84F6-001E673970C1.root',
  #      '/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/6C86B4A6-74D2-E111-8C53-003048D462C6.root'

]

i = 0
for file in fileNames:
  prefix = file.split("/")
  #outname = prefix[3]+"_"+prefix[4]+"_"+ str(i) +".root"
  outname = prefix[8]
  destination = "/eos/cms/store/caf/user/tjkim/mc/" + prefix[3] + "/" + prefix[4] + "/" + prefix[5] + "/" + prefix[6] + "/" + prefix[7] + "/"
  #need to create destination manually 
  print "copying... " + outname
  print "to... " + destination
  
  os.system("lcg-cp -b -D srmv2 --vo cms \""+location+file+"\" "+"/tmp/tjkim/"+outname)
  cmd = "xrdcp /tmp/tjkim/"+outname+" root://eoscms/" + destination
  commands.getoutput(cmd)
  #os.system("rfcp /tmp/tjkim/"+outname+" /castor/cern.ch/user/t/tjkim/MC/Fall11/test") # castor is not supported anylonger
  os.system("rm -rf /tmp/tjkim/"+outname)

  i = i + 1;



