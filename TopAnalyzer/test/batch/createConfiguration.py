#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# How to run: ./createConfiguration MuMu
import os
import re
import sys
import time
import commands

newSubmit = False

class CreateConfig:
    def __init__(self, dataType, decay):
        ## All things you should set before submit
        self.sourceDir = os.environ['CMSSW_BASE']+'/src/KoPFA/TopAnalyzer/python/Sources'
        self.mcReign = 'Summer11'

        self.outProtocol = 'ssh'
        self.outHost = 'cmskr-top'
        self.outDir = '/data/export/'+os.environ['USER']+'/TopAnalysis/ntuple'
        #self.outProtocol = 'file'
        #self.outDir = '/afs/cern.ch/'+os.environ['USER'][0]+'/'+os.environ['USER']+'YOUR_DIRECTORY'
        #self.outProtocol = 'rfio'
        #self.outDir = '/castor/cern.ch/user/'+os.environ['USER'][0]+'/'+os.environ['USER']+'YOUR_DIRECTORY'

        ## Set decay mode name
        if decay in ('ElEl', 'elel', 'ELEL', 'ee', 'EE', 'ELE', 'ele'):
            decay = 'ElEl'
        elif decay in ('MuMu', 'mumu', 'MUMU', 'mm', 'MM', 'MU', 'mu'):
            decay = 'MuMu'
        elif decay in ('MuEl', 'muel', 'elmu', 'MUEL', 'ELMU', 'em', 'me', 'EM', 'ME', 'EMU', 'emu'):
            decay = 'MuEl'
        else:
            print 'Invalid decay mode :', decay
            return
        self.decay = decay

        ## Set dataset
        if dataType == 'RD':
            self.datasets = [
                'Run2011A', 
            ]

        else:
            self.datasets = [
                'TTbarTuneZ2', 'TTbarOthers',
                'TTbarPowheg', 'TTbarPythia',
                'SingleToptW',
                'WJetsToLNu', 'VVJets',
                'ZJets', 'ZtauDecay', 
                'DYtt20to50', 'DYtt10to20',
            ]

            if 'Mu' in self.decay:
                self.datasets.extend(['DYmm20to50', 'DYmm10to20']) 

            if 'El' in self.decay:
                self.datasets.extend(['DYee20to50', 'DYee10to20']) 

            if self.decay == 'ElEl':
                self.datasets.extend(['QCDPt20to30BCtoE', 'QCDPt30to80BCtoE', 'QCDPt80to170BCtoE'])
            else:
                self.datasets.extend(['QCDPt20MuPt15']) 

        ## Set base directory
        if dataType == 'RD':
            if decay == 'ElEl':
                self.sourceDir += '/ELE'
            elif decay == 'MuMu':
                self.sourceDir += '/MU'
            elif decay == 'MuEl':
                self.sourceDir += '/EMU'

            self.sourceDir += '/RD'
        else:
            if decay == 'ElEl':
                self.sourceDir += '/ELE'
            elif decay == 'MuMu':
                self.sourceDir += '/MU'
            elif decay == 'MuEl':
                self.sourceDir += '/EMU'
            
            self.sourceDir += '/MC/'+self.mcReign

        ## Find data files
        self.datasetFileMap = {}
        for dataset in self.datasets:
            if dataset == 'TTbarOthers':
                datasetFile = self.sourceDir+'/patTuple_%s_cff.py' % 'TTbarTuneZ2'
            else:
                datasetFile = self.sourceDir+'/patTuple_%s_cff.py' % dataset

            if not os.path.exists(datasetFile):
                print 'Cannot find dataset file :', os.path.basename(datasetFile)
                continue

            self.datasetFileMap[dataset] = []
            for line in open(datasetFile).readlines():
                line = line.strip().strip(",").strip("'").strip('"')
                if '.root' not in line:
                    continue

                self.datasetFileMap[dataset].append(line)

        ## Write contents
        self.header = """import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = cms.untracked.vstring(),
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("KoPFA.TopAnalyzer.topAnalysis_cff")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)
"""

        if dataType == 'RD':
            self.footer = """
process.p = cms.Path(
    process.top%sAnalysisRealDataSequence
)
""" % self.decay
        else:
            self.footer = """
process.p = cms.Path(
    process.top%sAnalysisMCSequence
)
""" % self.decay

        if dataType == 'RD':
            self.footer += "process.%s.doResJec = cms.untracked.bool(True)" % (self.decay)

        ## Now we are ready to create configuration files
        cfgDir = os.path.abspath('./%s/%s' % (dataType, self.decay))
        os.makedirs(cfgDir)

        ## Create run script
        runScript = open('%s/run.sh' % cfgDir, 'w')
        os.system('chmod +x %s' % runScript.name)
        runScript.write("""#!/bin/bash
SCRATCHDIR=`pwd`
CFGDIR=%s
CFG=$1
OUTDIR=%s

cd $CFGDIR
eval `scram runtime -sh`

cd $SCRATCHDIR
cmsRun $CFGDIR/$CFG
""" % (cfgDir, self.outDir))
        if 'rfio' == self.outProtocol:
            runScript.write("""
nsmkdir -p $OUTDIR
for FILE in vallot_*.root
    do rfcp $FILE *.root $OUTDIR; 
done
""")
        elif 'ssh' == self.outProtocol:
            runScript.write("""
OUTHOST=%s
ssh $OUTHOST 'mkdir -p $OUTDIR'
scp vallot_*.root $OUTHOST:$OUTDIR
""" % (self.outHost))
        elif 'file' == self.outProtocol:
            runScript.write("""
mv vallot_*.root $OUTDIR/
""")
        runScript.close()

        for dataset in self.datasetFileMap:
            print dataset, len(self.datasetFileMap[dataset])

            ## Decay mode specific configurations
            specificCfg = "\n## Decay mode specific configurations"
            if 'TTbar' in dataset:
                specificCfg += """
process.topWLeptonGenFilter.applyFilter = True
"""
            if 'TTbarOthers' in dataset:
                specificCfg += """
process.top%sAnalysisMCSequence.replace(process.topWLeptonGenFilter,~process.topWLeptonGenFilter)
""" % self.decay
            if dataset in ('ZJets'):
                specificCfg += """
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.decayMode = [11, 13]
"""
            if dataset in ('ZtauDecay'):
                specificCfg += """
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.decayMode = [15]
"""
            if '20to50' in dataset:
                specificCfg += """
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.max = 50
"""
            specificCfg += "\n"

            submitScript = open('%s/submit_%s.sh' % (cfgDir, dataset), 'w')
            os.system('chmod +x %s' % submitScript.name)
            submitScript.write('#!/bin/bash\n')

            for (index, file) in enumerate(self.datasetFileMap[dataset]):
                sectionName = '%s_%03d' % (dataset, index+1)
                cfgOut = open('%s/ntuple_%s_cfg.py' % (cfgDir, sectionName), 'w')

                cfgOut.write(self.header)
                cfgOut.write(specificCfg)
                cfgOut.write('process.source.fileNames.append("%s")\n' % file)
                cfgOut.write('process.TFileService.fileName = "vallot_%s.root"\n' % sectionName)
                cfgOut.write(self.footer)

                submitScript.write('bsub -J %s -q 8nh -oo log_%s.log run.sh %s\n' %  (sectionName, sectionName, os.path.basename(cfgOut.name)))

                cfgOut.close()
                cfgOut = None

            submitScript.close()

if newSubmit == True:
    CreateConfig('RD', 'ElEl')
    CreateConfig('RD', 'MuEl')
    CreateConfig('RD', 'MuMu')

    CreateConfig('MC', 'ElEl')
    CreateConfig('MC', 'MuEl')
    CreateConfig('MC', 'MuMu')

    sys.exit(0)

decay = sys.argv[1]

mcSet = {}
rdSet = {}

mcSet['ElEl'] = [
    'TTbarTuneZ2', 'TTbarOthers',
    'SingleToptW', 'SingleTopt', 'SingleTops',
    'ZJets', 'DYee20to50', 'DYee10to20', 'DYmm20to50', 'DYmm10to20',
    'ZtauDecay', 'DYtt20to50', 'DYtt10to20',
    'WJetsToLNu', 'VVJets',
    'QCDPt20to30BCtoE', 'QCDPt30to80BCtoE', 'QCDPt80to170BCtoE',
    'QCDPt20to30EM', 'QCDPt30to80EM', 'QCDPt80to170EM',
]

mcSet['MuMu'] = [
    'TTbarTuneZ2', 'TTbarOthers',
    'SingleToptW', 'SingleTopt', 'SingleTops',
    'ZJets', 'DYee20to50', 'DYee10to20', 'DYmm20to50', 'DYmm10to20',
    'ZtauDecay', 'DYtt20to50', 'DYtt10to20',
    'WJetsToLNu', 'VVJets',
    'QCDPt20MuPt15',
]

mcSet['MuEl'] = [
    'TTbarTuneZ2', 'TTbarOthers',
    'SingleToptW', 'SingleTopt', 'SingleTops',
    'ZJets', 'DYee20to50', 'DYee10to20', 'DYmm20to50', 'DYmm10to20',
    'ZtauDecay', 'DYtt20to50', 'DYtt10to20',
    'WJetsToLNu', 'VVJets',
    'QCDPt20to30BCtoE', 'QCDPt30to80BCtoE', 'QCDPt80to170BCtoE',
    'QCDPt20to30EM', 'QCDPt30to80EM', 'QCDPt80to170EM',
	'QCDPt20MuPt15',
]

rdSet['ElEl'] = [
    'Run2011A', 
]

rdSet['MuMu'] = [
    'Run2011A', 
]

rdSet['MuEl'] = [
    'Run2011A', 
]

mclist = mcSet[decay]
datalist = rdSet[decay]

def common():
  script = """import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring()
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.load("KoPFA.TopAnalyzer.topAnalysis_cff")
"""
  return script

def mcsample(src):
  dir = ""
  if( decay == "MuEl"):
    dir = "EMU"
  elif( decay == "MuMu"):
    dir = "MU"
  elif( decay == "ElEl"):
    dir = "ELE"
  script = """
process.load("KoPFA.TopAnalyzer.Sources.%s.MC.Spring11.patTuple_%s_cff")
""" % (dir,src)
  return script

def mcpath():
  script = """
process.p = cms.Path(
    process.top%sAnalysisMCSequence
) 
""" % decay
  return script

def rdsample(src):
  dir = ""
  if( decay == "MuEl"):
    dir = "EMU"
  elif( decay == "MuMu"):
    dir = "MU"
  elif( decay == "ElEl"):
    dir = "ELE"
  script = """
process.load("KoPFA.TopAnalyzer.Sources.%s.RD.patTuple_%s_cff")
""" % (dir,src)
  return script


def rdpath():
  script = """
process.%s.doResJec = cms.untracked.bool(True)

process.p = cms.Path(
    process.top%sAnalysisRealDataSequence
) 
""" % (decay, decay)
  return script

def outfile(src):
  script = """
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_%s.root')
)
""" % src
  return script

def ttbarfilter():
  script = """
process.topWLeptonGenFilter.applyFilter = True
"""
  return script

def ttbarothersfilter():
  script = """
process.topWLeptonGenFilter.applyFilter = True
process.top%sAnalysisMCSequence.replace(process.topWLeptonGenFilter,~process.topWLeptonGenFilter)
""" % decay
  return script

def genzmassfilter():
  script = """
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.decayMode = [11, 13]
"""
  return script

def genzmasstaudecayfilter():
  script = """
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.decayMode = [15]
"""
  return script

def genzlowmassfilter():
  script = """
process.GenZmassFilter.applyFilter = True
process.GenZmassFilter.max = 50
"""
  return script

#os.system("mkdir "+decay)
if not os.path.exists(decay):
    os.mkdir(decay)
 
for src in mclist:
    out = open(decay+'/top'+decay+'Analyzer_'+src+'_cfg.py','w')
    out.write(common())
    out.write(mcpath())
    out.write(outfile(src))
    if src.find("ZtauDecay") != -1:
      out.write(mcsample("ZJets"))
    elif src.find("TTbarOthers") != -1:
      out.write(mcsample("TTbarTuneZ2"))
    else:
      out.write(mcsample(src))
    if src.find("TTbarTuneZ2") != -1:
      out.write(ttbarfilter())
    if src.find("TTbarOthers") != -1:
      out.write(ttbarothersfilter())
    if src.find("ZJets") != -1:
      out.write(genzmassfilter())
    if src.find("ZtauDecay") != -1:
      out.write(genzmasstaudecayfilter())
    if src.find("20to50") != -1:
      out.write(genzlowmassfilter())
    out.close()

for src in datalist:
    out = open(decay+'/top'+decay+'Analyzer_'+src+'_cfg.py','w')
    out.write(common())
    out.write(rdpath())
    out.write(outfile(src))
    out.write(rdsample(src))
    out.close()
