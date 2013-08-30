#!/usr/bin/env python

import sys, os

datasets = [
#    'DoubleElectron_MC',
#    'DoubleElectron_RD',
#    'MC',
#    'RD',
    'ZJets', 'Run2012A', 'Run2012B', 'Run2012C', 'Run2012D',
]

## Load list of TnP module configurations from prod configuration file
sys.path.append(".")
from prod_cfg import process
paths = dict(process.paths_())

tnpProducers = []
for key in paths:
    path = paths[key]
    for moduleName in path.moduleNames():
        module = getattr(process, moduleName)
        moduleType = module.type_()
        if moduleType != 'TagProbeFitTreeProducer': continue

        tnpProducers.append(module)

## Now we have full list of TnP producers
categoryMap = {}
for module in tnpProducers:
    moduleLabel = module.label()
    selections = []
    flags = module.flags
    for p in flags.parameterNames_():
        selections.append(p)
    categoryMap[moduleLabel.replace('tnp', '')] = selections
print categoryMap

exit()

## Prepare run environment
if not os.path.exists("result/unmerged"): os.makedirs("result/unmerged")
if not os.path.exists("log/anal"): os.makedirs("log/anal")
os.system("echo > log/anal_finish.log")
os.system("echo > log/anal_error.log")
submitLog = open("log/anal_submit.log", "w")

runscript = open("run_anal.sh", "w")
runscript.write("""#!/bin/bash

cd %s
eval `scram runtime -sh`

export MODE=$1
export STEP=$2
export CATEGORY=$3
cmsRun anal_cfg.py 
#python -i anal_cfg.py 
RETVAL=$?

if [ $RETVAL == 0 ]; then
    echo run_anal $MODE $STEP $CATEGORY >> log/anal_finish.log
else
    echo run_anal $MODE $STEP $CATEGORY >> log/anal_error.log
fi

exit $RETVAL
""" % os.environ["PWD"])
runscript.close()
os.system("chmod +x %s/run_anal.sh" % os.environ["PWD"])

## Submit jobs
for dataset in datasets:
    for step in categoryMap.keys():
        for category in categoryMap[step]:
            os.system('bsub -q 8nh -oo log/anal/%s_%s_%s.log run_anal.sh %s %s %s' % (dataset, step, category, dataset, step, category))
            print>>submitLog, dataset, step, category
