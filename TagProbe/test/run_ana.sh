#!/bin/bash

cd /afs/cern.ch/user/s/shsong79/workspace/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/TagProbe/test
eval `scram runtime -sh`

export MODE=$1
export STEP=$2

cmsRun PFMuon_TnP_Analyzer_cfg.py

