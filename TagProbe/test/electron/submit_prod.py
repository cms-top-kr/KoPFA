#!/usr/bin/env python

import sys, os

maxFiles = 200
triggerMode = "SingleElectron"
samples = [
    "ZJets-Summer12", 
    "%s-Run2012A" % triggerMode, "%s-Run2012B" % triggerMode, 
    "%s-Run2012C" % triggerMode, "%s-Run2012D" % triggerMode,
]
sourceBase = "/afs/cern.ch/user/j/jhgoh/public/sources/CMG/V5_13_0"

## Prepare run environment
if not os.path.exists("ntuple/unmerged"): os.makedirs("ntuple/unmerged")
runscript = open("_run_prod.sh", "w")
runscript.write("""#!/bin/bash

cd %s
eval `scram runtime -sh`

export DATASET=$1
export SECTION=$2
export BEGIN=$3
export END=$4
export TRIGGERMODE=$5

#python prod_cfg.py
cmsRun prod_cfg.py
RETVAL=$?

if [ $RETVAL == 0 ]; then
    echo run_prod $MODE $STEP $CATEGORY >> log/finish.log
else
    echo run_prod $MODE $STEP $CATEGORY >> log/error.log
fi

exit $RETVAL""" % os.environ["PWD"])
os.system("chmod +x _run_prod.sh")

## Submit jobs
for sample in samples:
    source = "%s/%s.txt" % (sourceBase, sample)
    files = []
    for line in open(source).readlines():
        line = line.strip()
        if len(line) < 5 or line[0] == '#' or '.root' not in line: continue

        files.append(line)

    nFiles = len(files)
    nSection = nFiles/maxFiles
    if nFiles == nSection*maxFiles: nSection -= 1

    print "Submitting jobs for %s, spliting by %d sections" % (sample, nFiles)

    for section in range(nSection):
      begin = section*maxFiles
      end = (section+1)*maxFiles

      if end > nFiles+1: end = nFiles

      os.system("echo bsub -oo log/prod/%s_%s_%3d.log -q 8nh run_prod.sh %s %d %d %d %s" % (sample, triggerMode, section, sample, section, begin, end, triggerMode))

