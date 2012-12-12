#!/bin/bash

MODES="RD"
#STEPS="Id looseIdIso looseIddBIso15TrgMu17Mu8 looseIddBIso15TrgMu17Mu8sl"
STEPS="looseIddBIso15TrgMu17Mu8sl"

for MODE in $MODES; do

  for STEP in $STEPS; do

    #echo bsub -oo log/${SAMPLE}_${SECTION}.log -q 8nh run_prod.sh $SAMPLE $SECTION $BEGIN $END
    bsub -oo log/fit_${STEP}_${MODE}.log -q 1nd run_ana.sh $MODE $STEP

  done
done

