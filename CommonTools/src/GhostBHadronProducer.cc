#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "TMath.h"

#include <memory>
#include <vector>

using namespace std;
using namespace edm;
using namespace reco;

// Produces ghost B hadron to be entered GenJet clustering
// This method is standard in pseudo-top
class GhostBHadronProducer : public edm::EDProducer
{
public:
  GhostBHadronProducer(const edm::ParameterSet& pset);
  ~GhostBHadronProducer() {};
  void produce(edm::Event& event, const edm::EventSetup& eventSetup);

private:
  bool isBHadron(const reco::Candidate* p); // B hadron without b hadron decendents
  bool isBHadron(const unsigned int absPdgId); // Check |pdgId| to check flavor

private:
  edm::InputTag srcLabel_;
  int userPdgId_;

};

GhostBHadronProducer::GhostBHadronProducer(const edm::ParameterSet& pset)
{
  srcLabel_ = pset.getParameter<edm::InputTag>("src");
  userPdgId_ = pset.getUntrackedParameter<int>("userPdgId", 0);

  produces<reco::GenParticleCollection>();
  produces<std::vector<int> >().setBranchAlias( pset.getParameter<std::string>("@module_label") + "BarCodes" );
}

void GhostBHadronProducer::produce(edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<reco::GenParticleCollection> genParticlesHandle;
  event.getByLabel(srcLabel_, genParticlesHandle);

  // Prepare output collections
  std::auto_ptr<reco::GenParticleCollection> outGenParticles(new reco::GenParticleCollection());
  std::auto_ptr<std::vector<int> > outGenParticleIndices(new std::vector<int>());
  reco::GenParticleRefProd ref = event.getRefBeforePut<reco::GenParticleCollection>();

  // Copy GenParticles and ghost B hadrons to output collection
  const double scale = 1e-20;
  std::map<const reco::Candidate*, int> particleIndexMap;
  std::vector<int> srcParticleIndices;
  const int nParticles = genParticlesHandle->size();
  for ( int i=0, nOutGenParticle=0; i<nParticles; ++i )
  {
    const reco::GenParticle& pSrc = genParticlesHandle->at(i);
    particleIndexMap[&pSrc] = nOutGenParticle;

    reco::GenParticle p = pSrc;
    p.clearMothers();
    p.clearDaughters();
    p.resetMothers(ref.id());
    p.resetDaughters(ref.id());

    outGenParticleIndices->push_back(nOutGenParticle);
    outGenParticles->push_back(p);
    srcParticleIndices.push_back(i);

    ++nOutGenParticle;

    if ( isBHadron(&pSrc) )
    {
      reco::GenParticle b = p;

      // Scale down particle momentum by 1e-20 : neglegible contribution to the jet momentum
      // Algorithm 2 : Particle energy is sqrt((1e-20*p)^2+m^2) rather than simple 1e-20*E to reserve particle mass
      //               this gives wrong eta distribution for some reason...
      //const reco::Candidate::LorentzVector p4(p.px()*scale, p.py()*scale, p.pz()*scale, std::hypot(p.p()*scale, p.mass()));
      //b.setP4(p4);
      b.setP4(p.p4()*scale);
      b.setStatus(1); // This ghost particle will be considered as a stable particle
      if ( userPdgId_ != 0 ) b.setPdgId(userPdgId_); // Set user defined PDG ID if set

      b.clearDaughters();
      outGenParticleIndices->push_back(nOutGenParticle);
      outGenParticles->push_back(b);
      srcParticleIndices.push_back(i);

      ++nOutGenParticle;
    }
  }

  // Make connection between candidate
  for ( int i=0, n=outGenParticles->size(); i<n; ++i )
  {
    reco::GenParticle& p = outGenParticles->at(i);

    const reco::GenParticle& pSrc = genParticlesHandle->at(srcParticleIndices[i]);
    for ( int j=0, m=pSrc.numberOfMothers(); j<m; ++j )
    {
      const reco::Candidate* mother = pSrc.mother(j);
      if ( particleIndexMap.find(mother) == particleIndexMap.end() )
      {
        cout << "Particle index is corrupted\n";
        continue;
      }
      const unsigned int motherIndex = particleIndexMap[mother];
      p.addMother(reco::GenParticleRef(ref, motherIndex));
      reco::GenParticle& outMother = outGenParticles->at(motherIndex);
      outMother.addDaughter(reco::GenParticleRef(ref, i));
    }
  }

  event.put(outGenParticles);
  event.put(outGenParticleIndices);
}

bool GhostBHadronProducer::isBHadron(const reco::Candidate* p)
{
  const unsigned int absPdgId = abs(p->pdgId());
  if ( !isBHadron(absPdgId) ) return false;

  // Do not consider this particle if it has B hadron daughter
  // For example, B* -> B0 + photon; then we drop B* and take B0 only
  for ( int i=0, n=p->numberOfDaughters(); i<n; ++i )
  {
    const reco::Candidate* dau = p->daughter(i);
    if ( isBHadron(abs(dau->pdgId())) ) return false;
  }

  return true;
}

bool GhostBHadronProducer::isBHadron(const unsigned int absPdgId)
{
  if ( absPdgId <= 100 ) return false; // Fundamental particles and MC internals
  if ( absPdgId >= 1000000000 ) return false; // Nuclears, +-10LZZZAAAI

  // General form of PDG ID is 7 digit form
  // +- n nr nL nq1 nq2 nq3 nJ
  //const int nJ = absPdgId % 10; // Spin
  const int nq3 = (absPdgId / 10) % 10;
  const int nq2 = (absPdgId / 100) % 10;
  const int nq1 = (absPdgId / 1000) % 10;

  if ( nq3 == 0 ) return false; // Diquarks
  if ( nq1 == 0 and nq2 == 5 ) return true; // B mesons
  if ( nq1 == 5 ) return true; // B baryons 

  return false;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(GhostBHadronProducer);
