KoPFA
=====

KoPFA


#Initializing
<pre><code>
cmsrel CMSSW_5_3_12_patch1

git init
git remote add origin git@github.com:cbernet/cmg-cmssw.git
git config core.sparsecheckout true

##IF at CERN,
cp /afs/cern.ch/user/c/cbern/public/Git/SparseCheckouts/CMG_PAT_from-CMSSW_5_3_12_patch1 .git/info/sparse-checkout

##OR at other place,
cat > .git/info/sparse-checkout


AnalysisDataFormats/CMGTools/
CMGTools/Common/
CMGTools/External/
CMGTools/H2TauTau/
CMGTools/Production/
CMGTools/RootTools/
CMGTools/Utilities/
CMGTools/GitTests/
CommonTools/ParticleFlow/
EgammaAnalysis/ElectronTools/
FWCore/Version/
Muon/MuonAnalysisTools/
RecoParticleFlow/PFProducer/
RecoParticleFlow/PostProcessing/
TauAnalysis/CandidateTools/
TauAnalysis/SVFitStandAlone/



git fetch origin

git clone https://github.com/geonmo/KoPFA.git .
(Do not missing "." )
</code></pre>
