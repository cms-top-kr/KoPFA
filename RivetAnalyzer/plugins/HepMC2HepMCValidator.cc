#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "HepMC/SimpleVector.h"
#include "HepMC/GenEvent.h"

#include <iostream>
#include <map>

using namespace std;

class HepMC2HepMCValidator : public edm::EDAnalyzer
{
public:
  HepMC2HepMCValidator(const edm::ParameterSet& pset);
  ~HepMC2HepMCValidator() {};

  void analyze(const edm::Event& event, const edm::EventSetup& eventSetup);
  void endJob();

private:
  edm::InputTag genEventLabel1_;
  edm::InputTag genEventLabel2_;

  int nEvent_;
  int runNumber_, lumiNumber_, eventNumber_;
  bool isDifferent_;
  std::vector<int> differentEvents_;

private:
  void checkDifference(const char* title, const double value1, const double value2)
  {
  // Ignore if relative error is below 1% level.
    if ( std::abs(value1 - value2) <= 2e-2*(std::abs(value1)+std::abs(value2)) ) return;

    cout << "(D) Run:" << runNumber_ << " Lumi:" << lumiNumber_ << " Event:" << eventNumber_
         << " " << title << "    " << value1 << ":" << value2 << endl;
    isDifferent_ = true;
  }

  void checkDifference(const char* title, const int value1, const int value2)
  {
    if ( value1 == value2 ) return;

    cout << "(I) Run:" << runNumber_ << " Lumi:" << lumiNumber_ << " Event:" << eventNumber_
         << " " << title << "    " << value1 << ":" << value2 << endl;
    isDifferent_ = true;
  }
};

HepMC2HepMCValidator::HepMC2HepMCValidator(const edm::ParameterSet& pset)
{
  genEventLabel1_ = pset.getParameter<edm::InputTag>("genEvent1");
  genEventLabel2_ = pset.getParameter<edm::InputTag>("genEvent2");

  nEvent_ = 0;
}

void HepMC2HepMCValidator::analyze(const edm::Event& event, const edm::EventSetup& eventSetup)
{
  ++nEvent_;

  runNumber_   = event.id().run();
  lumiNumber_  = event.id().luminosityBlock();
  eventNumber_ = event.id().event();

  isDifferent_ = false;

  edm::Handle<edm::HepMCProduct> genEventHandle1;
  event.getByLabel(genEventLabel1_, genEventHandle1);
  const HepMC::GenEvent* genEvent1 = genEventHandle1->GetEvent();

  edm::Handle<edm::HepMCProduct> genEventHandle2;
  event.getByLabel(genEventLabel2_, genEventHandle2);
  const HepMC::GenEvent* genEvent2 = genEventHandle2->GetEvent();

  checkDifference("Process Id", genEvent1->signal_process_id(), genEvent2->signal_process_id());
  checkDifference("Event number", genEvent1->event_number(), genEvent2->event_number());
  checkDifference("Multiparton", genEvent1->mpi(), genEvent2->mpi());

  checkDifference("PDF:id1", genEvent1->pdf_info()->id1(), genEvent2->pdf_info()->id1());
  checkDifference("PDF:id2", genEvent1->pdf_info()->id2(), genEvent2->pdf_info()->id2());
  checkDifference("PDF:x1", genEvent1->pdf_info()->x1(), genEvent2->pdf_info()->x1());
  checkDifference("PDF:x2", genEvent1->pdf_info()->x2(), genEvent2->pdf_info()->x2());
  checkDifference("PDF:scalePDF", genEvent1->pdf_info()->scalePDF(), genEvent2->pdf_info()->scalePDF());
  checkDifference("PDF:pdf1", genEvent1->pdf_info()->pdf1(), genEvent2->pdf_info()->pdf1());
  checkDifference("PDF:pdf2", genEvent1->pdf_info()->pdf2(), genEvent2->pdf_info()->pdf2());

  checkDifference("Event scale", genEvent1->event_scale(), genEvent2->event_scale());
  checkDifference("Alpha QCD", genEvent1->alphaQCD(), genEvent2->alphaQCD());
  checkDifference("Alpha QED", genEvent1->alphaQED(), genEvent2->alphaQED());

  checkDifference("nParticle", genEvent1->particles_size(), genEvent2->particles_size());
  HepMC::GenEvent::particle_const_iterator ptclItr1 = genEvent1->particles_begin();
  HepMC::GenEvent::particle_const_iterator ptclItr2 = genEvent2->particles_begin();
  while ( ptclItr1 != genEvent1->particles_end() and ptclItr2 != genEvent2->particles_end() )
  {
    const HepMC::GenParticle* p1 = *ptclItr1;
    const HepMC::GenParticle* p2 = *ptclItr2;

    checkDifference("Particle:pdgId" , p1->pdg_id(), p2->pdg_id());
    checkDifference("Particle:status", p1->status(), p2->status());
    //checkDifference("Particle:flow", p1->flow(), p2->flow());
    //checkDifference("Particle:generatedMass", p1->generated_mass(), p2->generated_mass());
    //checkDifference("Particle:barcode", p1->barcode(), p2->barcode());
    checkDifference("Particle::px", p1->momentum().px(), p2->momentum().px());
    checkDifference("Particle::py", p1->momentum().py(), p2->momentum().py());
    checkDifference("Particle::pz", p1->momentum().pz(), p2->momentum().pz());
    checkDifference("Particle::e" , p1->momentum().e() , p2->momentum().e() );

    ++ptclItr1;
    ++ptclItr2;
  }

  checkDifference("nVertex", genEvent1->vertices_size(), genEvent2->vertices_size());
  HepMC::GenEvent::vertex_const_iterator vtxItr1 = genEvent1->vertices_begin();
  HepMC::GenEvent::vertex_const_iterator vtxItr2 = genEvent2->vertices_begin();
  while ( vtxItr1 != genEvent1->vertices_end() and vtxItr2 != genEvent2->vertices_end() )
  {
    const HepMC::GenVertex* v1 = *vtxItr1;
    const HepMC::GenVertex* v2 = *vtxItr2;

    checkDifference("Vertex:id", v1->id(), v2->id());
    checkDifference("Vertex:barcode", v1->barcode(), v2->barcode());
    checkDifference("Vertex:x", v1->position().x(), v2->position().x());
    checkDifference("Vertex:y", v1->position().y(), v2->position().y());
    checkDifference("Vertex:z", v1->position().z(), v2->position().z());
    //checkDifference("Vertex:t", v1->position().t(), v2->position().t());
    checkDifference("Vertex:nParticlesIn", v1->particles_in_size(), v2->particles_in_size());
    checkDifference("Vertex:nParticlesOut", v1->particles_out_size(), v2->particles_out_size());

    ++vtxItr1;
    ++vtxItr2;
  }

  if ( isDifferent_ ) differentEvents_.push_back(eventNumber_);

}

void HepMC2HepMCValidator::endJob()
{
  cout << "===== HepMC2HepMCValidator =====" << endl;
  cout << " Analyzed  : " << nEvent_ << " events" << endl;
  cout << " Different : " << differentEvents_.size() << " events found" << endl;
  if ( !differentEvents_.empty() )
  {
    cout << " List of events with different contents : " << endl;
    for ( int i=0, n=differentEvents_.size()-1; i<n; ++i )
    {
      cout << differentEvents_[i] << ", ";
    }
    cout << differentEvents_.back() << endl;
  }
  cout << "================================" << endl;
}

DEFINE_FWK_MODULE(HepMC2HepMCValidator);
