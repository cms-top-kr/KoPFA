## Recipe from TopDileptonRefAnalysis2010Pass6
# HBHE Filter Producer
addpkg CommonTools/RecoAlgos
cvs update -A -r V00-02-15 CommonTools/RecoAlgos/plugins/HBHENoiseFilterResultProducer.cc
cvs update -r V00-02-15 CommonTools/RecoAlgos/python/HBHENoiseFilterResultProducer_cfi.py
cvs update -r V00-02-15 CommonTools/RecoAlgos/BuildFile

#ID on AOD
cvs co -rV00-03-14-02 RecoEgamma/ElectronIdentification

## PF tags
cvs co -r Jeroen_Sep28 -d AnalysisDataFormats/PFAnalyses UserCode/PFAnalyses/AnalysisDataFormats/PFAnalyses
cvs co -r TJ_Nov9 -d PFAnalyses/CommonTools UserCode/PFAnalyses/CommonTools
cvs co -r Colin_Sept28_newSamplesInterface -d PFAnalyses/RootTools UserCode/PFAnalyses/RootTools
cvs co -r Jeroen_Sep29 -d PFAnalyses/TemplateAnalysis UserCode/PFAnalyses/TemplateAnalysis

cvs co -r michal_V06-01-02_mod DataFormats/PatCandidates
cvs co -r Colin_384_noMoreJetPtCutInPF2PAT_Sept30 PhysicsTools/PFCandProducer
cvs co -r Colin_384_noMoreJetPtCutInPF2PAT_Sept30 PhysicsTools/PatAlgos

# TTbar-dilepton packages and its dependences
cvs co -d PFAnalyses/TTbarDIL UserCode/PFAnalyses/TTbarDIL
cvs co -d KoPFA UserCode/KoPFA
cvs co -r V00-02-01 ElectroWeakAnalysis/WENu

# dont forget this
checkdeps -a

## We don't need to compile everything. remove them to save time and disk space
rm -rf ISpy Fireworks

## Build'em all
#scram build

