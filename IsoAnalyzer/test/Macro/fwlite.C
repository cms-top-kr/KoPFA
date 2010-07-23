#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TMath.h"

void fwlite(){

  gSystem->Load("libFWCoreFWLite.so"); 
  AutoLibraryLoader::enable();
  gSystem->Load("libDataFormatsFWLite.so");

  vector<string> fileNames1;
  fileNames1.push_back("/tmp/tjkim/pf2pat/DataMt70Wenu/pf2pat_iso_0.root");

  vector<string> fileNames2;
  fileNames2.push_back("/tmp/tjkim/pf2pat/Wenu/pf2pat_iso_0.root");

  //fwlite::ChainEvent ev1(fileNames1);

  fwlite::ChainEvent ev(fileNames2);

  for( ev.toBegin(); ! ev.atEnd(); ++ev) {
    //std::cout << "run= " << ev.id().run() << " event= " << ev.id().event() ; 
    fwlite::Handle<std::vector<pat::Electron> > elec;
    fwlite::Handle<std::vector<pat::MET> > met;
    elec.getByLabel(ev,"selectedPatElectronsPFlowIso");
    met.getByLabel(ev,"patMETsPFlow");
    pat::MET mi = met->at(0);
    //now can access data

    for(unsigned i = 0; i != elec->size(); i++){
      pat::Electron it = elec->at(i);

      double dphi = mi.p4().phi() - it.phi();
      while(dphi >=  TMath::Pi() ) dphi -= 2*TMath::Pi();
      while(dphi < -TMath::Pi() ) dphi += 2*TMath::Pi();
      if( abs(dphi) < 2.0){
        std::cout << "run= " << ev.id().run() << " event= " << ev.id().event() ;
        std::cout <<" pt= " << it.pt() << " delphi= "<< dphi <<std::endl;
      }
    }  
     
  }



}
