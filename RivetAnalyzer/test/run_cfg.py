import FWCore.ParameterSet.Config as cms
import sys, os

process = cms.Process("RIVET")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_1_1_yAw.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_3_1_ZHd.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_4_1_IeC.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_5_1_R4E.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_6_1_rMz.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_7_1_WQn.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_9_1_Nyk.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_10_1_2FS.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_11_1_VTS.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_12_1_RzC.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_13_1_6Z8.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_14_1_TRO.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_15_1_NDB.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_16_1_ID7.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_17_1_qW0.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_18_1_h0t.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_21_1_SVA.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_22_1_3pr.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_23_1_E8B.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_25_1_6Cv.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_26_1_BoP.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_28_1_uTL.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_29_1_6Gh.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_30_1_vFo.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_32_1_nFf.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_33_1_SxI.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_35_1_Tbw.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_36_1_ewi.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_37_1_yHy.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_38_1_DwR.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_39_1_y0U.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_41_1_yFH.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_42_1_6gm.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_43_1_ZoI.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_44_1_YoT.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_45_1_pur.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_46_1_VtR.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_47_1_KA4.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_48_1_FtT.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_49_1_kn3.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_50_1_qQP.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_51_1_vQi.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_52_1_LPd.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_53_1_kTn.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_54_1_1SF.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_55_1_W6U.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_56_1_ZkL.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_57_1_Z1A.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_58_1_nRT.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_59_1_RMm.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_60_1_o1V.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_61_1_etT.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_62_1_XbN.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_63_1_QvO.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_64_1_PAa.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_65_1_0KJ.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_66_1_4jD.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_67_1_y9p.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_68_1_842.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_69_1_Bdq.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_70_1_txW.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_71_1_PXI.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_73_1_oG4.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_74_1_c17.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_75_1_mPe.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_76_1_jLU.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_77_1_wkC.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_78_1_527.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_79_1_OXZ.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_80_1_aR6.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_81_1_195.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_82_1_lc2.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_83_1_mG0.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_84_1_Iyq.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_85_1_WLJ.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_86_1_nfj.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_87_1_jJb.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_88_1_kXI.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_89_1_4X0.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_90_1_KxB.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_91_1_vTq.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_92_1_vYw.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_93_1_3PP.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_95_1_AGU.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_96_1_jHz.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_97_1_3zL.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_98_1_XKC.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_99_1_udH.root',
        '/store/user/jhgoh/GenParticles/TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/genParticles_100_1_0zm.root',
    ),
)

### Rebuild HepMC
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load('KoPFA.RivetAnalyzer.GenParticles2HepMC_cfi')

## Setup RIVET analyzer
process.load("GeneratorInterface.RivetInterface.rivetAnalyzer_cfi")

process.p = cms.Path(process.rivetAnalyzer)
process.rivetAnalyzer.AnalysisNames = cms.vstring('CMS_TOP_12_028')
process.rivetAnalyzer.CrossSection = cms.double(13.43)
#process.rivetAnalyzer.CrossSection = cms.double(165)
process.rivetAnalyzer.OutputFile = 'rivet.aida'

process.p = cms.Path(process.generator * process.rivetAnalyzer)

