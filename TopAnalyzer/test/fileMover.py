#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# Filename: analysis.py
# How to run: ./copy.py status mc ElEl 
import os
import re
import sys
import time

#location = "srm://srm.ciemat.es:8443/srm/managerv2?SFN"
location = "srm://maite.iihe.ac.be:8443/srm/managerv2?SFN=/pnfs/iihe/cms/ph/sc4"
#dir = "/store/mc/Fall10/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/AODSIM/START38_V12-v2/0022/D8FAE496-FAE3-DF11-8D1A-842B2B5027EB.root"
#dir = "/store/mc/Spring10/ZJets-madgraph/GEN-SIM-RECO/START3X_V26_S09-v1/0014/F0D822C6-4D47-DF11-9590-0030487E5179.root"
dir = "/store/mc/Spring10/TTbarJets-madgraph/GEN-SIM-RECO/START3X_V26_S09-v1/0016/6E7C4631-9D47-DF11-96CE-003048C69288.root"
filename = "test_Spring10_TTbar.root"

os.system("lcg-cp -b -D srmv2 --vo cms \""+location+dir+"\" /tmp/tjkim/"+filename)
