#!/bin/bash

SAMPLES="ZJets Run2012SingleMu"
CMGVERSION=V5_10_0

for SAMPLE in $SAMPLES; do
  echo $SAMPLE | grep -q 'Run2012'
  if [ $? -eq 0 ]; then
    PROD=Run2012
  else
    PROD=Summer12
  fi

  NFILES=`cat $CMSSW_BASE/src/KoPFA/CommonTools/python/Sources/CMG/$CMGVERSION/$PROD/cmgTuple_${SAMPLE}_cff.py | grep root | wc -l`
  #NFILES=$(($NFILES-1))
  MAXFILES=100
  NSECTION=$(($NFILES/$MAXFILES))
  [ $NFILES -eq $(($NSECTION*$MAXFILES)) ] && NSECTION=$(($NSECTION-1))
  echo $NFILES

  for SECTION in `seq 0 $NSECTION`; do
    BEGIN=$(($SECTION*$MAXFILES))
    END=$((($SECTION+1)*$MAXFILES))

    [ $END -gt $(($NFILES+1)) ] && END=$NFILES
    #echo bsub -oo log/${SAMPLE}_${SECTION}.log -q 8nh run_prod.sh $SAMPLE $SECTION $BEGIN $END
    bsub -oo log/${SAMPLE}_${SECTION}.log -q 8nh run_prod.sh $SAMPLE $SECTION $BEGIN $END

    #./run.sh $SAMPLE $SECTION $BEGIN $END
  done
done

