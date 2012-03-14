
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_102_0_bgd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_105_0_OOi.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_127_0_DSd.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_12_0_8R3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_136_0_8wn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_139_0_iU2.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_15_0_3it.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_17_1_EK1.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_21_0_9Zr.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_29_0_f42.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_33_0_T2I.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_49_1_WJJ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_52_0_lQt.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_53_0_A9z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_65_0_xNG.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_77_0_33Z.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_81_0_7bD.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_8_1_JzQ.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MC/Fall11/SingleElectron/WJetsToLNu/patTuple_skim_93_0_4aV.root',
]
        )
