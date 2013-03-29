#!/usr/bin/env python

import sys, os

datasets = [
#    'DoubleElectron_MC',
#    'DoubleElectron_RD',
    'MC',
    'RD',
]

categoryMap = {
    'Nh'                :['nh0', 'nh1', 'allIdIso09', 'allIdIso05', 'allIdIso00',],
    'Nh0Mva'            :['mvam01', 'mva00', 'mva03', 'mva05', 'mva07', 'mva09'],
    'Nh0Mva05Iso'       :['iso15' , 'diso15', 'riso15',],
    'Nh0Mva05Riso15Pf'  :['pf'],

    'Nh0Mva05Riso15PfCharge':['chargeConsistency'],
    'Nh0Mva00Iso'       :['iso15' , 'diso15', 'riso15',],
    'Nh0Mva00Riso15Pf'  :['pf'],

    'Nh0Mva05Riso15PfHL':['TS', 'HL'],
    'Nh0Mva05Riso15PfSL':['SL'],
    'Nh0Mva05Riso15PfDZ':['DZ'],

    'Nh0Mva00Riso15PfHL':['TS', 'HL'],
    'Nh0Mva00Riso15PfSL':['SL'],
    'Nh0Mva00Riso15PfDZ':['DZ'],

    'Nh0Mva09Riso15PfHL':['TS', 'HL'],
    'Nh0Mva09Riso15PfSL':['SL'],
    'Nh0Mva09Riso15PfDZ':['DZ'],

    'S'   :['idIso'],
    'STrg':['TS'],
}

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
