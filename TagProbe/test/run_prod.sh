#!/bin/bash

cd /afs/cern.ch/user/s/shsong79/workspace/CMGTools/CMSSW_5_3_3_patch3/src/KoPFA/TagProbe/test
eval `scram runtime -sh`

export DATASET=$1
export SECTION=$2
export BEGIN=$3
export END=$4

cmsRun PFMuon_TnP_Producer_Zmm_cfg.py
