#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
# How to run: ./createConfiguration MuMu
import os
import re
import sys
import time
import commands
import datetime

newSubmit = False
#newSubmit = True 

class CreateConfig:
    def __init__(self, dataType, decay):
        ## All things you should set before submit
        self.sourceDir = os.environ['CMSSW_BASE']+'/src/KoPFA/TopAnalyzer/python/Sources'
        self.mcReign = 'Summer11'
        self.ntupleVersion = datetime.date.today().strftime('%Y%m%d')+'_v1'

        #self.maxFileSize = 0 # Set 0 not to do merging
        GB = 1000000000
        self.maxFileSize = 5*GB

        self.outProtocol = 'ssh'
        self.outHost = 'cmskr-top'
        self.outDir = '/data/export/'+os.environ['USER']+'/TopAnalysis/ntuple/'+dataType+'/'+decay
        self.outDir += '/'+self.ntupleVersion
        #self.outProtocol = 'file'
        #self.outDir = '/afs/cern.ch/'+os.environ['USER'][0]+'/'+os.environ['USER']+'YOUR_DIRECTORY'
        #self.outProtocol = 'rfio'
        #self.outDir = '/castor/cern.ch/user/'+os.environ['USER'][0]+'/'+os.environ['USER']+'YOUR_DIRECTORY'
        #self.outDir = '/castor/cern.ch/cms/store/user/'+os.environ['USER']+'/TopAnalysis/ntuple/'+dataType+'/'+decay
        #self.outDir += '/'+self.ntupleVersion

        print "=== Creating", dataType, decay, "jobs ==="

        ## Set decay mode name
        if decay in ('ElEl', 'elel', 'ELEL', 'ee', 'EE', 'ELE', 'ele'):
            decay = 'ElEl'
        elif decay in ('MuMu', 'mumu', 'MUMU', 'mm', 'MM', 'MU', 'mu'):
            decay = 'MuMu'
        elif decay in ('MuEl', 'muel', 'elmu', 'MUEL', 'ELMU', 'em', 'me', 'EM', 'ME', 'EMU', 'emu'):
            decay = 'MuEl'
        elif decay in ('MuJet', 'mj'):
            decay = 'MuJet'
        elif decay in ('ElJet', 'ej'):
            decay = 'ElJet'
        else:
            print 'Invalid decay mode :', decay
            return
        self.decay = decay

        ## Set GlobalTag
        if dataType == 'RD':
            self.globalTag = 'GR_R_42_V23'
        else:
            self.globalTag = 'START42_V17' 

        ## Set dataset
        if dataType == 'RD':
            self.datasets = [
                'Run2011A', 
                'Run2011B', 
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

            #if self.decay == 'ElEl':
            #    self.datasets.extend(['QCDPt20to30BCtoE', 'QCDPt30to80BCtoE', 'QCDPt80to170BCtoE'])
            #else:
            #    self.datasets.extend(['QCDPt20MuPt15']) 

        ## Set base directory
        if dataType == 'RD':
            if decay == 'ElEl':
                self.sourceDir += '/ELE'
            elif decay == 'MuMu':
                self.sourceDir += '/MU'
            elif decay == 'MuEl':
                self.sourceDir += '/EMU'
            elif decay == 'MuJet':
                self.sourceDir += '/MUJET'
            elif decay == 'ElJet':
                self.sourceDir += '/ELEJET'

            self.sourceDir += '/RD'
        else:
            if decay == 'ElEl':
                self.sourceDir += '/ELE'
            elif decay == 'MuMu':
                self.sourceDir += '/MU'
            elif decay == 'MuEl':
                self.sourceDir += '/EMU'
            elif decay == 'MuJet':
                self.sourceDir += '/MUJET'
            elif decay == 'ElJet':
                self.sourceDir += '/ELEJET'
            
            self.sourceDir += '/MC/'+self.mcReign

        ## Find data files
        self.datasetFileMap = {}
        for dataset in self.datasets:
            if dataset == 'TTbarOthers':
                datasetFile = self.sourceDir+'/patTuple_%s_cff.py' % 'TTbarTuneZ2'
            elif dataset == 'ZtauDecay':
                datasetFile = self.sourceDir+'/patTuple_%s_cff.py' % 'ZJets'
            else:
                datasetFile = self.sourceDir+'/patTuple_%s_cff.py' % dataset

            if not os.path.exists(datasetFile):
                print 'Cannot find dataset file :', os.path.basename(datasetFile)
                continue

            self.datasetFileMap[dataset] = [[],]
            sumFileSize = 0
            for line in open(datasetFile).readlines():
                line = line.strip().strip(",").strip("'").strip('"')
                if '.root' not in line:
                    continue
                if '#' == line[0]:
                    continue

                if self.maxFileSize > 0:
                    fileSize = self.getFileSize(line)
                    if fileSize == 0:
                        continue

                    self.datasetFileMap[dataset][-1].append(line)
                    sumFileSize += fileSize

                    if sumFileSize > self.maxFileSize:
                        self.datasetFileMap[dataset].append([])
                        sumFileSize = 0
                else:
                    self.datasetFileMap[dataset].append([line])

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

#process.load("KoPFA.TopAnalyzer.topAnalysis_Syst_cff")
process.load("KoPFA.TopAnalyzer.topAnalysis_cff")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)
"""

        self.header += """
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string("%s::All")
""" % self.globalTag

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
        cfgDir = os.path.abspath('./%s/%s/%s' % (self.ntupleVersion, dataType, self.decay))
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
RETVAL=$?

if [ $RETVAL != 0 ]; then
  exit $RETVAL
fi

""" % (cfgDir, self.outDir))
        if 'rfio' == self.outProtocol:
            runScript.write("""
rfmkdir -p $OUTDIR
for FILE in vallot_*.root
    do rfcp $FILE $OUTDIR; 
done
""")
        elif 'ssh' == self.outProtocol:
            runScript.write("""
OUTHOST=%s
ssh $OUTHOST "mkdir -p $OUTDIR"
scp vallot_*.root $OUTHOST:$OUTDIR
""" % (self.outHost))
        elif 'file' == self.outProtocol:
            runScript.write("""
mkdir -p $OUTDIR
mv vallot_*.root $OUTDIR/
""")
        runScript.close()

        for dataset in self.datasetFileMap:
            print 'Dataset =', dataset, 'Number of jobs =', len(self.datasetFileMap[dataset])

            ## Decay mode specific configurations
            specificCfg = "\n## Decay mode specific configurations"
            if 'TTbar' in dataset:
				if decay in ('MuMu','ElEl','MuEl'):
					specificCfg += """
process.topWLeptonGenFilter.applyFilter = True
"""
				elif decay in ('MuJet','ElJet'):
					specificCfg += """
process.topWLeptonGenFilterForLJ.applyFilter = True
"""
            if 'TTbarOthers' in dataset:
				if decay in ('MuMu','ElEl','MuEl'):
					specificCfg += """
process.top%sAnalysisMCSequence.replace(process.topWLeptonGenFilter,~process.topWLeptonGenFilter)
""" % self.decay
				elif decay in ('MuJet','ElJet'):
					specificCfg += """
process.top%sAnalysisMCSequence.replace(process.topWLeptonGenFilterForLJ,~process.topWLeptonGenFilterForLJ)
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

            for (index, files) in enumerate(self.datasetFileMap[dataset]):
                sectionName = '%s_%03d' % (dataset, index+1)
                cfgOut = open('%s/ntuple_%s_cfg.py' % (cfgDir, sectionName), 'w')

                cfgOut.write(self.header)
                cfgOut.write(specificCfg)
                for file in files:
                    cfgOut.write('process.source.fileNames.append("%s")\n' % file)
                cfgOut.write('process.TFileService.fileName = "vallot_%s.root"\n' % sectionName)
                cfgOut.write(self.footer)

                submitScript.write('bsub -J %s -q 8nh -oo log_%s.log run.sh %s\n' %  (sectionName, sectionName, os.path.basename(cfgOut.name)))

                cfgOut.close()
                cfgOut = None

            submitScript.close()

    def getFileSize(self, file):
        file = file.replace('///', '/')
        file = file.replace('//', '/')
        file = file.replace('"', '').replace("'", '')
        if 'rfio:' == file[:5]:
            fileQuery = 'rfdir %s' % file[5:]
        elif 'file:' == file[:5]:
            fileQuery = 'ls -l %s' % file[5:]
        else:
            fileQuery = 'rfdir /castor/cern.ch/cms/%s' % file

        fileQuery += ' | grep %s | awk \'{print $5}\'' % os.path.basename(file)

        fileInfo = commands.getoutput(fileQuery)
        if not fileInfo or len(fileInfo) == 0:
            return 0

        fileSize = int(fileInfo)
        return fileSize


if newSubmit == True:
    CreateConfig('RD', 'ElEl')
    CreateConfig('RD', 'MuEl')
    CreateConfig('RD', 'MuMu')
    CreateConfig('RD', 'MuJet')
    CreateConfig('RD', 'ElJet')

    CreateConfig('MC', 'ElEl')
    CreateConfig('MC', 'MuEl')
    CreateConfig('MC', 'MuMu')
    CreateConfig('RD', 'MuJet')
    CreateConfig('RD', 'ElJet')

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
#    'QCDPt20to30BCtoE', 'QCDPt30to80BCtoE', 'QCDPt80to170BCtoE',
#    'QCDPt20to30EM', 'QCDPt30to80EM', 'QCDPt80to170EM',
]

mcSet['MuMu'] = [
    'TTbarTuneZ2', 'TTbarOthers',
    'SingleToptW', 'SingleTopt', 'SingleTops',
    'ZJets', 'DYee20to50', 'DYee10to20', 'DYmm20to50', 'DYmm10to20',
    'ZtauDecay', 'DYtt20to50', 'DYtt10to20',
    'WJetsToLNu', 'VVJets',
#    'QCDPt20MuPt15',
]

mcSet['MuEl'] = [
    'TTbarTuneZ2', 'TTbarOthers',
    'SingleToptW', 'SingleTopt', 'SingleTops',
    'ZJets', 'DYee20to50', 'DYee10to20', 'DYmm20to50', 'DYmm10to20',
    'ZtauDecay', 'DYtt20to50', 'DYtt10to20',
    'WJetsToLNu', 'VVJets',
#    'QCDPt20to30BCtoE', 'QCDPt30to80BCtoE', 'QCDPt80to170BCtoE',
#    'QCDPt20to30EM', 'QCDPt30to80EM', 'QCDPt80to170EM',
#	'QCDPt20MuPt15',
]

mcSet['MuJet'] = [
    'TTbarTuneZ2', 'TTbarOthers',
    'SingleToptW', 'SingleTopt', 'SingleTops',
    'ZJets', 'DYee20to50', 'DYee10to20', 'DYmm20to50', 'DYmm10to20',
    'ZtauDecay', 'DYtt20to50', 'DYtt10to20',
    'WJetsToLNu', 'VVJets',
    'QCDPt20to30BCtoE', 'QCDPt30to80BCtoE', 'QCDPt80to170BCtoE',
    'QCDPt20to30EM', 'QCDPt30to80EM', 'QCDPt80to170EM',
	'QCDPt20MuPt15',
]

mcSet['ElJet'] = [
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
    'Run2011B', 
]

rdSet['MuMu'] = [
    'Run2011A', 
    'Run2011B', 
]

rdSet['MuEl'] = [
    'Run2011A', 
    'Run2011B', 
]

rdSet['MuJet'] = [
    'Run2011A', 
    'Run2011B', 
]

rdSet['ElJet'] = [
    'Run2011A', 
    'Run2011B', 
]

mclist = mcSet[decay]
datalist = rdSet[decay]

mcGlobalTag = "START42_V17"
rdGlobalTag = "GR_R_42_V23"

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

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
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
  elif( decay == "MuJet"):
    dir = "MUJET"
  elif( decay == "ElJet"):
    dir = "ELEJET"
  script = """
process.load("KoPFA.TopAnalyzer.Sources.%s.MC.Fall11.patTuple_%s_cff")
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
  elif( decay == "MuJet"):
    dir = "MUJET"
  elif( decay == "ElJet"):
    dir = "ELEJET"
  script = """
process.load("KoPFA.TopAnalyzer.Sources.%s.RD.patTuple_%s_cff")
""" % (dir,src)
  return script


def rdpath():
  script = """
process.JetEnergyScale.doResJec = cms.untracked.bool(True)

process.p = cms.Path(
    process.top%sAnalysisRealDataSequence
) 
""" % decay
  return script

def outfile(src):
  script = """
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot_%s.root')
)
""" % src
  return script

def ttbardileptonfilter():
  script = """
process.topWLeptonGenFilter.applyFilter = True
"""
  return script

def ttbarleptonjetfilter():
  script = """
process.topWLeptonGenFilterForLJ.applyFilter = True
"""
  return script

def ttbardileptonothersfilter():
  script = """
process.topWLeptonGenFilter.applyFilter = True
process.top%sAnalysisMCSequence.replace(process.topWLeptonGenFilter,~process.topWLeptonGenFilter)
""" % decay
  return script

def ttbarleptonjetothersfilter():
  script = """
process.topWLeptonGenFilterForLJ.applyFilter = True
process.top%sAnalysisMCSequence.replace(process.topWLeptonGenFilterForLJ,~process.topWLeptonGenFilterForLJ)
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
    out.write("process.GlobalTag.globaltag = cms.string('%s::All')\n" % mcGlobalTag)
    out.write("process.JetEnergyScale.globalTag = cms.untracked.string('%s')" % mcGlobalTag)
    out.write(mcpath())
    out.write(outfile(src))
    if src.find("ZtauDecay") != -1:
      out.write(mcsample("ZJets"))
    elif src.find("TTbarOthers") != -1:
      out.write(mcsample("TTbarTuneZ2"))
    else:
      out.write(mcsample(src))
    if src.find("TTbarTuneZ2") != -1:
		if decay in ('MuMu','ElEl','MuEl'):
			out.write(ttbardileptonfilter())
		if decay in ('MuJet','ElJet'):
			out.write(ttbarleptonjetfilter())
    if src.find("TTbarOthers") != -1:
		if decay in ('MuMu','ElEl','MuEl'):
			out.write(ttbardileptonothersfilter())
		if decay in ('MuJet','ElJet'):
			out.write(ttbarleptonjetothersfilter())
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
    out.write("process.GlobalTag.globaltag = cms.string('%s::All')\n" % rdGlobalTag)
    out.write("process.JetEnergyScale.globalTag = cms.untracked.string('%s')" % rdGlobalTag)
    out.write(rdpath())
    out.write(outfile(src))
    out.write(rdsample(src))
    out.close()
