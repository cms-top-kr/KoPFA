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

class GenParticles2HepMCConverter : public edm::EDProducer
{
public:
  explicit GenParticles2HepMCConverter(const edm::ParameterSet& pset);
  ~GenParticles2HepMCConverter() {};

  void beginRun(edm::Run& run, const edm::EventSetup& eventSetup);
  void produce(edm::Event& event, const edm::EventSetup& eventSetup);

private:
  edm::InputTag genParticlesLabel_;
  edm::InputTag genRunInfoLabel_;
  edm::InputTag genEventInfoLabel_;
//  edm::ESHandle<ParticleDataTable> pTable_;

private:
  inline HepMC::FourVector FourVector(const reco::Candidate::Point& point)
  {
    return HepMC::FourVector(point.x(), point.y(), point.z(), point.r());
  };

  inline HepMC::FourVector FourVector(const reco::Candidate::LorentzVector& lvec)
  {
    // Avoid negative mass, set minimum m^2 = 0
    return HepMC::FourVector(lvec.px(), lvec.py(), lvec.pz(), std::sqrt(lvec.mag2() + std::max(0., lvec.mass2())));
  };


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

  // Prepare list of HepMC::GenParticles
  std::map<const reco::Candidate*, HepMC::GenParticle*> genCandToHepMCMap;
  std::vector<HepMC::GenParticle*> hepmc_particles;
  for ( unsigned int i=0, n=genParticlesHandle->size(); i<n; ++i )
  {
    const reco::Candidate* p = &genParticlesHandle->at(i);
    HepMC::GenParticle* hepmc_particle = new HepMC::GenParticle(FourVector(p->p4()), p->pdgId(), p->status());
    hepmc_particle->set_generated_mass(p->mass());
    hepmc_particles.push_back(hepmc_particle);
    genCandToHepMCMap[p] = hepmc_particle;
  }

  // Put incident beam particles to null vertex
  hepmc_particles[0]->set_status(4);
  hepmc_particles[1]->set_status(4);
  hepmc_event->set_beam_particles(hepmc_particles[0], hepmc_particles[1]);
  HepMC::GenVertex* firstVertex = new HepMC::GenVertex(FourVector(genParticlesHandle->at(0).vertex()));
  firstVertex->add_particle_out(hepmc_particles[0]);
  firstVertex->add_particle_out(hepmc_particles[1]);
  hepmc_event->add_vertex(firstVertex);

  // Prepare vertex list
  typedef std::map<const reco::Candidate*, HepMC::GenVertex*> ParticleToVertexMap;
  ParticleToVertexMap particleToVertexMap;
  particleToVertexMap[&genParticlesHandle->at(0)] = firstVertex;
  for ( unsigned int i=2, n=genParticlesHandle->size(); i<n; ++i )
  {
    const reco::Candidate* p = &genParticlesHandle->at(i);
    if ( p->numberOfMothers() == 0 )
    {
      std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
      std::cout << "Skipping orphan particle \n";
      std::cout << "  Event " << event.id().event() << " Index = " << i << '\n';
      std::cout << "  pdgId = " << p->pdgId() << " nDaughter = " << p->numberOfDaughters() << "\n";
      std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
      continue;
    }
    const reco::Candidate* elder = p->mother(0)->daughter(0);

    HepMC::GenVertex* vertex = 0;
    if ( particleToVertexMap.find(elder) == particleToVertexMap.end() ) //p == elder )
    {
      vertex = new HepMC::GenVertex(FourVector(elder->vertex()));
      hepmc_event->add_vertex(vertex);
      particleToVertexMap[elder] = vertex;
      for ( unsigned int j=0, m=elder->numberOfMothers(); j<m; ++j )
      {
        const reco::Candidate* mother = elder->mother(j);
        vertex->add_particle_in(genCandToHepMCMap[mother]);
      }
    }
    else
    {
      vertex = particleToVertexMap[elder];
    }

    vertex->add_particle_out(hepmc_particles[i]);
  }

  std::auto_ptr<edm::HepMCProduct> hepmc_product(new edm::HepMCProduct());
  hepmc_product->addHepMCData(hepmc_event);
  event.put(hepmc_product);

}

DEFINE_FWK_MODULE(GenParticles2HepMCConverter);
