#include "FWCore/Framework/interface/MakerMacros.h"
#include "TopQuarkAnalysis/TopKinFitter/plugins/TtSemiLepKinFitProducer.h"
#include "KoPFA/CMGAnalyzer/plugins/CMGTtFullLepKinSolutionProducer.h"

DEFINE_FWK_MODULE(CMGTtFullLepKinSolutionProducer);

#include "KoPFA/CMGAnalyzer/plugins/CMGTtFullLepMaosSolutionProducer.h"

DEFINE_FWK_MODULE(CMGTtFullLepMaosSolutionProducer);
