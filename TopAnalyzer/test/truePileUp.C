void truePileUp(){

  vector<string> file;
  file.push_back("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON_v3.pileupTruth.root");
  file.push_back("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/Cert_165088-167913_7TeV_PromptReco_JSON.pileupTruth.root");
  file.push_back("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/Cert_170249-172619_7TeV_ReReco5Aug_Collisions11_JSON_v2.pileupTruth.root");
  file.push_back("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/Cert_172620-173692_PromptReco_JSON.pileupTruth.root");
  file.push_back("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/Cert_175832-177515_PromptReco_JSON.pileupTruth.root");
  file.push_back("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/Cert_177718_178078_7TeV_PromptReco_Collisons11_JSON.pileupTruth.root");
  file.push_back("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp/Cert_178098-180252_7TeV_PromptReco_Collisions11_JSON.pileupTruth.root");

  cout << "adding... " << file[0] << endl;
  TFile* f = new TFile(file[0].c_str());
  TH1 * hData = (TH1*)  f->Get("pileup") ;

  //if it is more than one file
  for(int i=1; i < file.size(); i++){
   cout << "adding... " << file[i] << endl;
   TFile* ftmp = new TFile(file[i].c_str());
   TH1 * tmp = (TH1*) ftmp->Get("pileup") ;
   hData->Add(tmp);
  }
   
  int bins = hData->GetNbinsX();
  cout << "number of bins from data= " << bins << endl;
  for(int i=1; i <= 50 ; i++){
    if( hData->GetBinContent(i) ) cout << "    " << hData->GetBinContent(i) << "," << endl;
    else cout << "    " << "0.0" << "," << endl;
  } 
 
  hData->Draw();
  
}
