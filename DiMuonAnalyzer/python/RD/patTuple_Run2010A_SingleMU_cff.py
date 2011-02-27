
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend([
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_10_1_qMa.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_11_1_Mm3.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_12_1_YNs.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_13_1_Onw.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_14_1_CBu.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_15_1_tL7.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_16_1_K18.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_17_1_GC6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_18_1_OHF.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_19_1_2sI.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_1_1_0aj.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_20_1_p0V.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_21_1_6Ut.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_2_1_7Os.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_3_1_eA6.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_4_1_syn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_5_1_PuO.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_6_1_Akn.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_7_1_9s8.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_8_1_cZp.root',
	'rfio:///castor/cern.ch/user/t/tjkim/MUSKIM/Nov22_jetfixed/Run2010A-Nov4ReReco_v1_V2/patTuple_skim_9_1_lKs.root',
]
        )
