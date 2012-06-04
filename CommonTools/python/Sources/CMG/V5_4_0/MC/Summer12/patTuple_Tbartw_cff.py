
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",
	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring()
)
source.fileNames.extend([
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_0.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_1.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_10.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_11.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_12.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_13.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_14.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_15.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_16.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_17.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_18.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_19.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_2.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_20.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_21.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_22.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_23.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_24.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_25.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_26.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_27.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_28.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_29.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_3.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_30.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_31.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_32.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_33.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_34.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_35.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_36.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_37.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_38.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_39.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_4.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_40.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_41.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_42.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_43.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_44.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_45.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_46.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_47.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_48.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_49.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_5.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_50.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_51.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_52.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_53.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_54.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_55.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_56.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_57.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_58.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_59.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_6.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_60.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_61.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_62.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_63.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_64.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_7.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_8.root',
		'/store/cmst3/user/cmgtools/CMG/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/Summer12-PU_S7_START52_V9-v1/AODSIM/V5/PAT_CMG_V5_4_0/patTuple_9.root',
])
