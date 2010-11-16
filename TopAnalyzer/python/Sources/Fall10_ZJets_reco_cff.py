
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall10/test/Fall10_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_0.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall10/test/Fall10_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall10/test/Fall10_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall10/test/Fall10_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall10/test/Fall10_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_4.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall10/test/Fall10_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_5.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall10/test/Fall10_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall10/test/Fall10_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall10/test/Fall10_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall10/test/Fall10_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_9.root',
]
        )
