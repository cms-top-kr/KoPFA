#!/usr/bin/env python

import sys, os

datasets = [
#    'DoubleElectron_MC',
#    'DoubleElectron_RD',
    'MC',
    'RD',
]

categoryMap = {}
categoryMap['Nh'                ] = ['nh0', 'nh1', 'allIdIso09', 'allIdIso05', 'allIdIso00',]
categoryMap['Nh0Mva'            ] = ['mvam01', 'mva00', 'mva03', 'mva05', 'mva07', 'mva09']
categoryMap['Nh0Mva05Iso'       ] = ['iso15' , 'diso15', 'riso15',]
categoryMap['Nh0Mva05Riso15Pf'  ] = ['pf']

categoryMap['Nh0Mva05Riso15PfCharge'] = ['chargeConsistency']
categoryMap['Nh0Mva00Iso'       ] = ['iso15' , 'diso15', 'riso15',]
categoryMap['Nh0Mva00Riso15Pf'  ] = ['pf']

categoryMap['Nh0Mva05Riso15PfHL'] = ['TS', 'HL']
categoryMap['Nh0Mva05Riso15PfSL'] = ['SL']
categoryMap['Nh0Mva05Riso15PfDZ'] = ['DZ']

categoryMap['Nh0Mva00Riso15PfHL'] = ['TS', 'HL']
categoryMap['Nh0Mva00Riso15PfSL'] = ['SL']
categoryMap['Nh0Mva00Riso15PfDZ'] = ['DZ']

categoryMap['Nh0Mva09Riso15PfHL'] = ['TS', 'HL']
categoryMap['Nh0Mva09Riso15PfSL'] = ['SL']
categoryMap['Nh0Mva09Riso15PfDZ'] = ['DZ']

categoryMap['S'] = ['idIso']
categoryMap['STrg'] = ['TS']

submitLog = open("log/submit.log", "w")
finishLog = open("log/finish.log", "w")

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
    echo run_anal $MODE $STEP $CATEGORY >> log/finish.log
else
    echo run_anal $MODE $STEP $CATEGORY >> log/error.log
fi

exit $RETVAL
""" % os.environ["PWD"])
os.system("chmod +x %s/run_anal.sh" % os.environ["PWD"])

for dataset in datasets:
    for step in categoryMap.keys():
        for category in categoryMap[step]:
            #print 'bsub -q 8nh -oo log/fit_%s_%s_%s.log run_anal.sh %s %s %s' % (dataset, step, category, dataset, step, category)
            #print 'bsub -q 8nh -oo log/fit_%s_%s_%s.log run_anal.sh %s %s %s' % (dataset, step, category, dataset, step, category)
            os.system('echo bsub -q 8nh -oo log/fit_%s_%s_%s.log run_anal.sh %s %s %s' % (dataset, step, category, dataset, step, category))
            print>>submitLog, dataset, step, category
