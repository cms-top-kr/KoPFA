// -*- C++ -*-
//
// Package:    RemoveDuplicate
// Class:      RemoveDuplicate
//
/**\class RemoveDuplicate RemoveDuplicate.cc UserCode/RemoveDuplicate/src/RemoveDuplicate.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Tae Jeong Kim
//         Created:  Mon Dec 14 01:29:35 CET 2009
// $Id: RemoveDuplicate.cc,v 1.2 2010/10/14 15:50:03 jhgoh Exp $
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "KoPFA/DataFormats/interface/Event.h"

#include <set>
//
// class declaration
//
using namespace edm;
using namespace std;

class RemoveDuplicate : public edm::EDFilter
{
  public:
    explicit RemoveDuplicate(const edm::ParameterSet&);
    ~RemoveDuplicate() {};

  private:
    virtual void beginJob() {};
    virtual bool filter(edm::Event&, const edm::EventSetup&);
    virtual void endJob() {};

    // ----------member data ---------------------------
    bool applyFilter_;

    std::set<edm::EventID> eventSet_;
};

RemoveDuplicate::RemoveDuplicate(const edm::ParameterSet& ps)
{
  applyFilter_ = ps.getUntrackedParameter<bool>("applyFilter", true);
}

bool RemoveDuplicate::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if ( !applyFilter_ ) return true;

  if ( eventSet_.find(iEvent.id()) == eventSet_.end() )
  {
    eventSet_.insert(iEvent.id());
    return true;
  }

  return false;
}

DEFINE_FWK_MODULE(RemoveDuplicate);

