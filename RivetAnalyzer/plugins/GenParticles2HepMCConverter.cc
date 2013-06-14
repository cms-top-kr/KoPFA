#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
//#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

#include <iostream>
#include <map>
using namespace std;

class GenParticles2HepMCConverter : public edm::EDProducer
{
public:
  explicit GenParticles2HepMCConverter(const edm::ParameterSet& pset);
  ~GenParticles2HepMCConverter() {};

  void beginRun(edm::Run& run, const edm::EventSetup& eventSetup);
  void produce(edm::Event& event, const edm::EventSetup& eventSetup);

private:
  template<typename TIter, typename T>
  int findIndex(TIter begin, TIter end, T obj);

  edm::InputTag genParticlesLabel_;
  edm::InputTag genRunInfoLabel_;
  edm::InputTag genEventInfoLabel_;
//  edm::ESHandle<ParticleDataTable> pTable_;

};

GenParticles2HepMCConverter::GenParticles2HepMCConverter(const edm::ParameterSet& pset)
{
  genParticlesLabel_ = pset.getParameter<edm::InputTag>("genParticles");
  genRunInfoLabel_ = pset.getParameter<edm::InputTag>("genRunInfo");
  genEventInfoLabel_ = pset.getParameter<edm::InputTag>("genEventInfo");

  produces<edm::HepMCProduct>();
}

void GenParticles2HepMCConverter::beginRun(edm::Run& run, const edm::EventSetup& eventSetup)
{
  //edm::Handle<GenRunInfoProduct> genRunInfoHandle;
  //event.getByLabel(genRunInfoLabel_, genRunInfoHandle);
  // const double xsecIn = genRunInfoHandle->internalXSec().value();
  // const double xsecInErr = genRunInfoHandle->internalXSec().error();
  // const double xsecLO = genRunInfoHandle->externalXSecLO().value();
  // const double xsecLOErr = genRunInfoHandle->externalXSecLO().error();
  // const double xsecNLO = genRunInfoHandle->externalXSecNLO().value();
  // const double xsecNLOErr = genRunInfoHandle->externalXSecNLO().error();
  
  //eventSetup.getData(pTable_);
}

template<typename TIter, typename T>
int GenParticles2HepMCConverter::findIndex(TIter begin, TIter end, T obj)
{
  for ( TIter p = begin; p != end; ++p )
  {
    if ( &(*p) == obj ) return p-begin;
  }
  return -1;
}

void GenParticles2HepMCConverter::produce(edm::Event& event, const edm::EventSetup& eventSetup)
{
  edm::Handle<reco::CandidateView> genParticlesHandle;
  event.getByLabel(genParticlesLabel_, genParticlesHandle);

  edm::Handle<GenEventInfoProduct> genEventInfoHandle;
  event.getByLabel(genEventInfoLabel_, genEventInfoHandle);

  //const int id1 = pdfInfo.id1;
  //const int id2 = pdfInfo.id2;
  //const float x1 = pdfInfo.x1, x2 = pdfInfo.x2;
  //const float scalePDF = pdfInfo.scalePDF;
  //const float pdf1 = pdfInfo.pdf1, pdf2 = pdfInfo.pdf2;
  HepMC::GenEvent* hepmc_event = new HepMC::GenEvent();
  hepmc_event->set_signal_process_id(genEventInfoHandle->signalProcessID());
  hepmc_event->set_event_scale(genEventInfoHandle->qScale());
  hepmc_event->set_alphaQED(genEventInfoHandle->alphaQED());
  hepmc_event->set_alphaQCD(genEventInfoHandle->alphaQCD());

  //std::vector<HepMC::GenParticle*> hepmc_particles;
  std::map<const reco::Candidate*, HepMC::GenParticle*> genCandToHepMCMap;
  //std::map<HepMC::GenParticle*, reco::Candidate*> hepmcToGenCandMap;
  for ( unsigned int i=0, n=genParticlesHandle->size(); i<n; ++i )
  {
    const reco::Candidate* p = &genParticlesHandle->at(i);
    const math::XYZTLorentzVector& pLVec = p->p4();

    HepMC::FourVector hepmc_p4(pLVec.px(), pLVec.py(), pLVec.pz(), pLVec.e());
    HepMC::GenParticle* hepmc_particle = new HepMC::GenParticle(hepmc_p4, p->pdgId(), p->status());
    hepmc_particle->set_generated_mass(p->mass());

    //hepmc_particles.push_back(hepmc_particle);
    genCandToHepMCMap[p] = hepmc_particle;
    //hepmcToGenCandMap[hepmc_particle] = p;
  }

  // Loop once more to associate particles to vertices
  typedef std::map<HepMC::GenParticle*, HepMC::GenVertex*> ParticleToVertexMap;
  ParticleToVertexMap particleToVertexMap;
  // Special care for incident beam particles - associate to the null vertex
  HepMC::GenVertex* firstVertex = 0;
  //for ( unsigned int i=0, n=genParticlesHandle->size(); i<n; ++i )
  for ( unsigned int i=0, n=2; i<n; ++i )
  {
    const reco::Candidate* p = &genParticlesHandle->at(i);
    if ( p->numberOfMothers() != 0 ) continue;

    if ( !firstVertex )
    {
      const reco::Candidate::Point& vertexPos = p->vertex();
      HepMC::FourVector hepmc_vertexPos(vertexPos.x(), vertexPos.y(), vertexPos.z(), vertexPos.r());
      firstVertex = new HepMC::GenVertex(hepmc_vertexPos);
      hepmc_event->add_vertex(firstVertex);
    }

    HepMC::GenParticle* hepmc_particle = genCandToHepMCMap[p];
    firstVertex->add_particle_out(hepmc_particle);
    particleToVertexMap[hepmc_particle] = firstVertex;
  }

  for ( unsigned int i=2, n=genParticlesHandle->size(); i<n; ++i )
  {
    const reco::Candidate* p = &genParticlesHandle->at(i);
    //if ( p->numberOfMothers() == 0 ) continue;

    HepMC::GenVertex* hepmc_vertex = 0;
    HepMC::GenParticle* hepmc_particle = genCandToHepMCMap[p];

    ParticleToVertexMap::const_iterator particleToVertex = particleToVertexMap.find(hepmc_particle);
    if ( particleToVertex == particleToVertexMap.end() )
    {
      // This particle is not associated to any vertex. Create new one
      const reco::Candidate::Point& vertexPos = p->vertex();
      HepMC::FourVector hepmc_vertexPos(vertexPos.x(), vertexPos.y(), vertexPos.z(), vertexPos.r());
      hepmc_vertex = new HepMC::GenVertex(hepmc_vertexPos);
      hepmc_event->add_vertex(hepmc_vertex);
    }
    else
    {
      hepmc_vertex = particleToVertex->second;
    }

    // Associate mother (incoming) particles
    for ( int j=0, m=p->numberOfMothers(); j<m; ++j )
    {
      const reco::Candidate* mother = p->mother(j);
      HepMC::GenParticle* hepmc_mother = genCandToHepMCMap[mother];
      hepmc_vertex->add_particle_in(hepmc_mother);

      // Associate sister (outgoing) particles, including itself
      for ( int k=0, l=mother->numberOfDaughters(); k<l; ++k )
      {
        const reco::Candidate* sister = mother->daughter(k);
        HepMC::GenParticle* hepmc_sister = genCandToHepMCMap[sister];
        if ( particleToVertexMap.find(hepmc_sister) != particleToVertexMap.end() ) continue;

        particleToVertexMap[hepmc_sister] = hepmc_vertex;
        hepmc_vertex->add_particle_out(hepmc_sister);
      }
    }
  }

  std::auto_ptr<edm::HepMCProduct> hepmc_product(new edm::HepMCProduct(hepmc_event));
  event.put(hepmc_product);

}

DEFINE_FWK_MODULE(GenParticles2HepMCConverter);
