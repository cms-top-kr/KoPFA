
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",

	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring(
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_100_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_101_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_102_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_103_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_104_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_105_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_106_2.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_107_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_107_2.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_108_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_109_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_10_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_110_2.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_111_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_112_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_113_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_114_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_115_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_116_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_117_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_118_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_119_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_11_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_120_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_121_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_122_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_123_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_124_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_125_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_126_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_127_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_128_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_129_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_12_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_130_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_131_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_132_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_133_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_134_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_135_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_136_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_137_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_138_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_139_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_13_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_140_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_141_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_142_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_143_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_144_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_145_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_146_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_147_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_148_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_149_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_14_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_150_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_151_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_152_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_153_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_154_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_155_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_156_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_157_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_158_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_159_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_15_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_160_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_161_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_162_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_163_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_164_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_165_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_166_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_167_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_168_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_169_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_16_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_170_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_171_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_172_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_173_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_174_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_175_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_176_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_177_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_178_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_179_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_17_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_180_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_181_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_182_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_183_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_184_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_185_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_186_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_187_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_188_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_189_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_18_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_190_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_191_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_192_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_193_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_194_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_195_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_196_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_197_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_198_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_199_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_19_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_1_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_200_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_201_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_202_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_203_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_204_2.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_205_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_206_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_206_2.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_207_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_208_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_209_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_20_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_210_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_211_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_212_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_213_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_214_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_215_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_216_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_21_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_22_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_23_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_24_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_25_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_26_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_27_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_28_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_29_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_2_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_30_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_31_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_32_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_33_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_34_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_35_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_36_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_37_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_38_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_38_2.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_39_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_3_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_40_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_41_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_42_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_43_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_44_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_45_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_46_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_47_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_48_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_49_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_4_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_50_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_51_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_52_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_53_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_54_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_55_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_56_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_57_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_58_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_59_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_5_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_60_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_61_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_62_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_63_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_64_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_65_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_66_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_67_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_68_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_69_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_6_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_70_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_71_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_72_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_73_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_74_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_75_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_76_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_77_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_78_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_79_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_7_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_80_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_81_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_82_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_83_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_84_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_85_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_86_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_87_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_88_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_89_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_8_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_90_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_91_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_92_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_93_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_94_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_95_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_96_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_97_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_98_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_99_1.root',
		'rfio:/castor/cern.ch/user/g/gennai/SDMUONFILTER/CMSSW_361p2/Run_131511-135802/PF2PAT_SDMUON_GOODCOLL_MuonFilter_v9_9_1.root',
	)
)
