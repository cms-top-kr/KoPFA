#!/usr/bin/env python

import sys, os

maxFiles = 200
triggerMode = "SingleElectron"
samples = [
    "ZJets-Summer12", 
    "%s-Run2012A" % triggerMode, 
    "%s-Run2012B" % triggerMode, 
    "%s-Run2012C" % triggerMode, 
    "%s-Run2012D" % triggerMode,
]
sourceBase = "/afs/cern.ch/user/j/jhgoh/public/sources/CMG/V5_13_0"

## Prepare run environment
if not os.path.exists("ntuple/unmerged"): os.makedirs("ntuple/unmerged")
if not os.path.exists("log/prod"): os.makedirs("log/prod")
os.system("echo > log/prod_finish.log")
os.system("echo > log/prod_error.log")
submitLog = open("log/prod_submit.log", "w")

runscript = open("run_prod.sh", "w")
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
    echo run_prod $MODE $STEP $CATEGORY >> log/prod_finish.log
else
    echo run_prod $MODE $STEP $CATEGORY >> log/prod_error.log
fi

exit $RETVAL
""" % os.environ["PWD"])
runscript.close()
os.system("chmod +x %s/run_prod.sh" % os.environ["PWD"])

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

    print "Submitting jobs for %s, spliting %d files by %d sections" % (sample, nFiles, nSection)

    for section in range(nSection):
      begin = section*maxFiles
      end = (section+1)*maxFiles

      if end > nFiles+1: end = nFiles

      os.system("bsub -oo log/prod/%s_%s_%03d.log -q 8nh run_prod.sh %s %d %d %d %s" % (sample, triggerMode, section, sample, section, begin, end, triggerMode))
      print>>submitLog, sample, section, begin, end, triggerMode

