#include <iostream>
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TFile.h"
#include <iostream>
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
//using namespace std;
void efficiency()
{
    gROOT->ProcessLine(".L tdrstyle.C");
    defaultStyle();
	TFile* f1 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/MuMu/v0/vallot_TTbarTuneZ2.root");
	TFile* f2 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/ElEl/v0/vallot_TTbarTuneZ2.root");
	TFile* f3 = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/MuEl/v0/vallot_TTbarTuneZ2.root");
	
	TTree* treeMuMu = (TTree*)f1->Get("MuMu/tree");
	TTree* treeMuEl = (TTree*)f2->Get("ElEl/tree");
	TTree* treeElEl = (TTree*)f3->Get("MuEl/tree");
	
	float binspt[] = {0,10,20,30,40,50,60,70,80,100,120,160,210,260,320,400,500};
	int nBinpt = sizeof(binspt)/sizeof(float) - 1;
	float binseta[] = {0.,0.4,0.8,1.2,1.6,2.0,2.4};
	int nBineta = sizeof(binseta)/sizeof(float) - 1;
	
	TH1F* hmmptdeno = new TH1F("hmmptdeno","hmmptdeno",nBinpt,binspt);
	TH1F* hmmptdenottbb = new TH1F("hmmptdenottbb","hmmptdenottbb",nBinpt,binspt);
	TH1F* hmmptdenottll = new TH1F("hmmptdenottll","hmmptdenottll",nBinpt,binspt);
	
	TH1F* hmmptnumel = new TH1F("hmmptnumel","hmmptnumel",nBinpt,binspt);
	TH1F* hmmptnumem = new TH1F("hmmptnumem","hmmptnumem",nBinpt,binspt);	
	TH1F* hmmptnumemttbb = new TH1F("hmmptnumemttbb","hmmptnumemttbb",nBinpt,binspt);	
	TH1F* hmmptnumemttll = new TH1F("hmmptnumemttll","hmmptnumemttll",nBinpt,binspt);	
	TH1F* hmmptnumet = new TH1F("hmmptnumet","hmmptnumet",nBinpt,binspt);
	TH1F* hmmptnumetttbb = new TH1F("hmmptnumetttbb","hmmptnumetttbb",nBinpt,binspt);
	TH1F* hmmptnumetttll = new TH1F("hmmptnumetttll","hmmptnumetttll",nBinpt,binspt);

	TH1F* heeptdeno = new TH1F("heeptdeno","heeptdeno",nBinpt,binspt);
	TH1F* heeptdenottbb = new TH1F("heeptdenottbb","heeptdenottbb",nBinpt,binspt);
	TH1F* heeptdenottll = new TH1F("heeptdenottll","heeptdenottll",nBinpt,binspt);
	
	TH1F* heeptnumel = new TH1F("heeptnumel","heeptnumel",nBinpt,binspt);
	TH1F* heeptnumem = new TH1F("heeptnumem","heeptnumem",nBinpt,binspt);
	TH1F* heeptnumemttbb = new TH1F("heeptnumemttbb","heeptnumemttbb",nBinpt,binspt);
	TH1F* heeptnumemttll = new TH1F("heeptnumemttll","heeptnumemttll",nBinpt,binspt);
	TH1F* heeptnumet = new TH1F("heeptnumet","heeptnumet",nBinpt,binspt);
	TH1F* heeptnumetttbb = new TH1F("heeptnumetttbb","heeptnumetttbb",nBinpt,binspt);
	TH1F* heeptnumetttll = new TH1F("heeptnumetttll","heeptnumetttll",nBinpt,binspt);
	
	TH1F* hemptdeno = new TH1F("hemptdeno","hemptdeno",nBinpt,binspt);
	TH1F* hemptdenottbb = new TH1F("hemptdenottbb","hemptdenottbb",nBinpt,binspt);
	TH1F* hemptdenottll = new TH1F("hemptdenottll","hemptdenottll",nBinpt,binspt);
	
	TH1F* hemptnumel = new TH1F("hemptnumel","hemptnumel",nBinpt,binspt);
	TH1F* hemptnumem = new TH1F("hemptnumem","hemptnumem",nBinpt,binspt);
	TH1F* hemptnumemttbb = new TH1F("hemptnumemttbb","hemptnumemttbb",nBinpt,binspt);
	TH1F* hemptnumemttll = new TH1F("hemptnumemttll","hemptnumemttll",nBinpt,binspt);
	TH1F* hemptnumet = new TH1F("hemptnumet","hemptnumet",nBinpt,binspt);
	TH1F* hemptnumetttbb = new TH1F("hemptnumetttbb","hemptnumetttbb",nBinpt,binspt);
	TH1F* hemptnumetttll = new TH1F("hemptnumetttll","hemptnumetttll",nBinpt,binspt);
	
	TH1F* hmmetadeno = new TH1F("hmmetadeno","hmmetadeno",nBineta,binseta);
	
	TH1F* hmmetanumel = new TH1F("hmmetanumel","hmmetanumel",nBineta,binseta);	
	TH1F* hmmetanumem = new TH1F("hmmetanumem","hmmetanumem",nBineta,binseta);
	TH1F* hmmetanumet = new TH1F("hmmetanumet","hmmetanumet",nBineta,binseta);
	
	TH1F* heeetadeno = new TH1F("heeetadeno","heeetadeno",nBineta,binseta);
	
	TH1F* heeetanumel = new TH1F("heeetanumel","heeetanumel",nBineta,binseta);
	TH1F* heeetanumem = new TH1F("heeetanumem","heeetanumem",nBineta,binseta);
	TH1F* heeetanumet = new TH1F("heeetanumet","heeetanumet",nBineta,binseta);
	
	TH1F* hemetadeno = new TH1F("hemetadeno","hemetadeno",nBineta,binseta);
	
	TH1F* hemetanumel = new TH1F("hemetanumel","hemetanumel",nBineta,binseta);
	TH1F* hemetanumem = new TH1F("hemetanumem","hemetanumem",nBineta,binseta);
	TH1F* hemetanumet = new TH1F("hemetanumet","hemetanumet",nBineta,binseta);

	TH2F* hmmdeno = new TH2F("hmmdeno","hmmdeno",nBinpt,binspt,nBineta,binseta);
	
	TH2F* hmmnumel = new TH2F("hmmnumel","hmmnumel",nBinpt,binspt,nBineta,binseta);	
	TH2F* hmmnumem = new TH2F("hmmnumem","hmmnumem",nBinpt,binspt,nBineta,binseta);
	TH2F* hmmnumet = new TH2F("hmmnumet","hmmnumet",nBinpt,binspt,nBineta,binseta);
	
	TH2F* heedeno = new TH2F("heedeno","heedeno",nBinpt,binspt,nBineta,binseta);
	
	TH2F* heenumel = new TH2F("heenumel","heenumel",nBinpt,binspt,nBineta,binseta);
	TH2F* heenumem = new TH2F("heenumem","heenumem",nBinpt,binspt,nBineta,binseta);
	TH2F* heenumet = new TH2F("heenumet","heenumet",nBinpt,binspt,nBineta,binseta);
	
	TH2F* heedeno = new TH2F("hemdeno","hemdeno",nBinpt,binspt,nBineta,binseta);
	
	TH2F* hemnumel = new TH2F("hemnumel","hemnumel",nBinpt,binspt,nBineta,binseta);
	TH2F* hemnumem = new TH2F("hemnumem","hemnumem",nBinpt,binspt,nBineta,binseta);
	TH2F* hemnumet = new TH2F("hemnumet","hemnumet",nBinpt,binspt,nBineta,binseta);
	
	TCut mmdeno = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5)";
	TCut mmdenottbb = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5)  && ttbarGen.NbJets15() >= 4";
	TCut mmdenottll = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5)  && ttbarGen.NbJets15() >= 2 && !(ttbarGen.NbJets15() >= 4)";
	TCut mmnumel = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.244";
	TCut mmnumem = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.679";
	TCut mmnumemttbb = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.679  && ttbarGen.NbJets15() >= 4";
	TCut mmnumemttll = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.679  && ttbarGen.NbJets15() >= 2 && !(ttbarGen.NbJets15() >= 4)";
	TCut mmnumet = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.898";
	TCut mmnumetttbb = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.898  && ttbarGen.NbJets15() >= 4";
	TCut mmnumetttll = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.20 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.898  && ttbarGen.NbJets15() >= 2 && !(ttbarGen.NbJets15() >= 4)";
	
	TCut eedeno = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5)";	
	TCut eedenottbb = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5)  && ttbarGen.NbJets15() >= 4";
	TCut eedenottll = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5)  && ttbarGen.NbJets15() >= 2 && !(ttbarGen.NbJets15() >= 4)";
	TCut eenumel = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.244";
	TCut eenumem = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.679";
	TCut eenumemttbb = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.679  && ttbarGen.NbJets15() >= 4";
	TCut eenumemttll = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.679  && ttbarGen.NbJets15() >= 2 && !(ttbarGen.NbJets15() >= 4)";
	TCut eenumet = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.898";
	TCut eenumetttbb = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.898  && ttbarGen.NbJets15() >= 4";
	TCut eenumetttll = "ZMass > 12 && relIso1 < 0.17 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > 15 && @jetspt30.size() >= 4 && MET > 30 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.898  && ttbarGen.NbJets15() >= 2 && !(ttbarGen.NbJets15() >= 4)";
	
	TCut emdeno = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > -1 && @jetspt30.size() >= 4 && MET > -999 && (jetspt30flavor == 5 || jetspt30flavor == -5)";
	TCut emdenottbb = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > -1 && @jetspt30.size() >= 4 && MET > -999 && (jetspt30flavor == 5 || jetspt30flavor == -5)  && ttbarGen.NbJets15() >= 4";
	TCut emdenottll = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > -1 && @jetspt30.size() >= 4 && MET >-999 && (jetspt30flavor == 5 || jetspt30flavor == -5)  && ttbarGen.NbJets15() >= 2 && !(ttbarGen.NbJets15() >= 4)";
	TCut emnumel = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > -1 && @jetspt30.size() >= 4 && MET > -999 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.244";
	TCut emnumem = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > -1 && @jetspt30.size() >= 4 && MET > -999 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.679";
	TCut emnumemttbb = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > -1 && @jetspt30.size() >= 4 && MET > -999 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.679  && ttbarGen.NbJets15() >= 4";
	TCut emnumemttll = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > -1 && @jetspt30.size() >= 4 && MET > -999 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.679  && ttbarGen.NbJets15() >= 2 && !(ttbarGen.NbJets15() >= 4)";
	TCut emnumet = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > -1 && @jetspt30.size() >= 4 && MET > -999 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.898";
	TCut emnumetttbb = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > -1 && @jetspt30.size() >= 4 && MET > -999 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.898  && ttbarGen.NbJets15() >= 4";
	TCut emnumetttll = "ZMass > 12 && relIso1 < 0.20 && relIso2 < 0.17 && PairSign < 0 && abs(ZMass - 91.2) > -1 && @jetspt30.size() >= 4 && MET > -999 && (jetspt30flavor == 5 || jetspt30flavor == -5) && jetspt30bDiscriminator > 0.898  && ttbarGen.NbJets15() >= 2 && !(ttbarGen.NbJets15() >= 4)";
	
	treeMuMu->Draw("jetspt30.pt() >> hmmptdeno",mmdeno,"");
	treeMuMu->Draw("jetspt30.pt() >> hmmptdenottbb",mmdenottbb,"");
	treeMuMu->Draw("jetspt30.pt() >> hmmptdenottll",mmdenottll,"");
	treeMuMu->Draw("jetspt30.pt() >> hmmptnumel",mmnumel,"");
	treeMuMu->Draw("jetspt30.pt() >> hmmptnumem",mmnumem,"");
	treeMuMu->Draw("jetspt30.pt() >> hmmptnumemttbb",mmnumemttbb,"");
	treeMuMu->Draw("jetspt30.pt() >> hmmptnumemttll",mmnumemttll,"");
	treeMuMu->Draw("jetspt30.pt() >> hmmptnumet",mmnumet,"");
	treeMuMu->Draw("jetspt30.pt() >> hmmptnumetttbb",mmnumetttbb,"");
	treeMuMu->Draw("jetspt30.pt() >> hmmptnumetttll",mmnumetttll,"");
	treeElEl->Draw("jetspt30.pt() >> heeptdeno",eedeno,"");
	treeElEl->Draw("jetspt30.pt() >> heeptdenottbb",eedenottbb,"");
	treeElEl->Draw("jetspt30.pt() >> heeptdenottll",eedenottll,"");
	treeElEl->Draw("jetspt30.pt() >> heeptnumel",eenumel,"");
	treeElEl->Draw("jetspt30.pt() >> heeptnumem",eenumem,"");
	treeElEl->Draw("jetspt30.pt() >> heeptnumemttbb",eenumemttbb,"");
	treeElEl->Draw("jetspt30.pt() >> heeptnumemttll",eenumemttll,"");
	treeElEl->Draw("jetspt30.pt() >> heeptnumet",eenumet,"");
	treeElEl->Draw("jetspt30.pt() >> heeptnumetttbb",eenumetttbb,"");
	treeElEl->Draw("jetspt30.pt() >> heeptnumetttll",eenumetttll,"");
	treeMuEl->Draw("jetspt30.pt() >> hemptdeno",emdeno,"");
	treeMuEl->Draw("jetspt30.pt() >> hemptdenottbb",emdenottbb,"");
	treeMuEl->Draw("jetspt30.pt() >> hemptdenottll",emdenottll,"");
	treeMuEl->Draw("jetspt30.pt() >> hemptnumel",emnumel,"");
	treeMuEl->Draw("jetspt30.pt() >> hemptnumem",emnumem,"");
	treeMuEl->Draw("jetspt30.pt() >> hemptnumemttbb",emnumemttbb,"");
	treeMuEl->Draw("jetspt30.pt() >> hemptnumemttll",emnumemttll,"");
	treeMuEl->Draw("jetspt30.pt() >> hemptnumet",emnumet,"");
	treeMuEl->Draw("jetspt30.pt() >> hemptnumetttbb",emnumetttbb,"");
	treeMuEl->Draw("jetspt30.pt() >> hemptnumetttll",emnumetttll,"");
	
	treeMuMu->Draw("TMath::Abs(jetspt30.eta()) >> hmmetadeno",mmdeno,"");
	treeMuMu->Draw("TMath::Abs(jetspt30.eta()) >> hmmetanumel",mmnumel,"");
	treeMuMu->Draw("TMath::Abs(jetspt30.eta()) >> hmmetanumem",mmnumem,"");
	treeMuMu->Draw("TMath::Abs(jetspt30.eta()) >> hmmetanumet",mmnumet,"");
	treeElEl->Draw("TMath::Abs(jetspt30.eta()) >> heeetadeno",eedeno,"");
	treeElEl->Draw("TMath::Abs(jetspt30.eta()) >> heeetanumel",eenumel,"");
	treeElEl->Draw("TMath::Abs(jetspt30.eta()) >> heeetanumem",eenumem,"");
	treeElEl->Draw("TMath::Abs(jetspt30.eta()) >> heeetanumet",eenumet,"");
	treeMuEl->Draw("TMath::Abs(jetspt30.eta()) >> hemetadeno",emdeno,"");
	treeMuEl->Draw("TMath::Abs(jetspt30.eta()) >> hemetanumel",emnumel,"");
	treeMuEl->Draw("TMath::Abs(jetspt30.eta()) >> hemetanumem",emnumem,"");
	treeMuEl->Draw("TMath::Abs(jetspt30.eta()) >> hemetanumet",emnumet,"");
	
	treeMuMu->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> hmmdeno",mmdeno,"");
	treeMuMu->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> hmmnumel",mmnumel,"");
	treeMuMu->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> hmmnumem",mmnumem,"");
	treeMuMu->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> hmmnumet",mmnumet,"");
	treeElEl->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> heedeno",eedeno,"");
	treeElEl->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> heenumel",eenumel,"");
	treeElEl->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> heenumem",eenumem,"");
	treeElEl->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> heenumet",eenumet,"");
	treeMuEl->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> hemdeno",emdeno,"");
	treeMuEl->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> hemnumel",emnumel,"");
	treeMuEl->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> hemnumem",emnumem,"");
	treeMuEl->Draw("TMath::Abs(jetspt30.eta()):jetspt30.pt() >> hemnumet",emnumet,"");
	
	TCanvas*  tageff1 = new TCanvas("tageff1","tagging efficiency",1200,1200);
	TCanvas*  tageff2 = new TCanvas("tageff2","tagging efficiency",1200,1200);
	TCanvas*  tageff3 = new TCanvas("tageff3","tagging efficiency",1200,1200);
	TCanvas*  tageff4 = new TCanvas("tageff4","tagging efficiency",1200,1200);
	TCanvas*  tageff5 = new TCanvas("tageff5","tagging efficiency",1200,1200);
	TCanvas*  tageff6 = new TCanvas("tageff6","tagging efficiency",1200,1200);
	TCanvas*  tageff7 = new TCanvas("tageff7","tagging efficiency",1200,1200);
	TCanvas*  tageff8 = new TCanvas("tageff8","tagging efficiency",1200,1200);
	TCanvas*  tageff9 = new TCanvas("tageff9","tagging efficiency",1200,1200);
	TCanvas*  tageff10 = new TCanvas("tageff10","tagging efficiency",1200,1200);
	TCanvas*  tageff11 = new TCanvas("tageff11","tagging efficiency",1200,1200);
	TCanvas*  tageff12 = new TCanvas("tageff12","tagging efficiency",1200,1200);
	TCanvas*  tageff13 = new TCanvas("tageff13","tagging efficiency",1200,1200);
	
	TCanvas*  tageff14 = new TCanvas("tageff14","tagging efficiency",1200,1200);

	tageff1->cd();
	hmmptdeno->Add(heeptdeno);
	hmmptdeno->Add(hemptdeno);
	hmmptnumel->Add(heeptnumel);
	hmmptnumel->Add(hemptnumel);
	TH1F* hptl = hmmptdeno->Clone("hptl");
	hptl->Sumw2();
	hptl->SetStats(0);
	hptl->SetTitle("tagging efficiency(CSVL)");
	hptl->Divide(hmmptnumel,hmmptdeno,1,1,"B");
	hptl->Fit("pol4");
	hptl->SetMinimum(0.0);
	hptl->SetMaximum(1.0);
	hptl->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hptl->GetYaxis()->SetTitle("efficiency");
	hptl->SetStats(0);
	hptl->Draw("");
	TH1F *hptlint = hptl->Clone("hptlint");
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hptlint,0.68);
	hptlint->SetFillColor(2);
	hptlint->SetStats(0);
	hptlint->Draw("e3 same");
	TH1F * hptlcopy = hptl->Clone("hptlcopy");
	TH1F * hptlintcopy = hptlint->Clone("hptlintcopy");
	hptl->Reset();
	
	tageff2->cd();
	hmmptnumem->Add(heeptnumem);
	hmmptnumem->Add(hemptnumem);
	TH1F* hptm = hmmptdeno->Clone("hptm");
	hptm->Sumw2();
	hptm->SetTitle("tagging efficiency(CSVM)");
	hptm->Divide(hmmptnumem,hmmptdeno,1,1,"B");
	hptm->Fit("pol4");
	hptm->SetMinimum(0.0);
	hptm->SetMaximum(1.0);
	hptm->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hptm->GetYaxis()->SetTitle("efficiency");
	hptm->SetStats(0);
	hptm->Draw("");
	TH1F *hptmint = hptm->Clone("hptmint");
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hptmint,0.68);
	hptmint->SetFillColor(2);
	hptmint->SetStats(0);
	hptmint->Draw("e3 same");
	TH1F * hptmcopy = hptm->Clone("hptmcopy");
	TH1F * hptmintcopy = hptmint->Clone("hptmintcopy");
	hptm->Reset();
	
	tageff3->cd();
	hmmptnumet->Add(heeptnumet);
	hmmptnumet->Add(hemptnumet);
	TH1F* hptt = hmmptdeno->Clone("hptt");
	hptt->Sumw2();
	hptt->SetTitle("tagging efficiency(CSVT)");
	hptt->Divide(hmmptnumet,hmmptdeno,1,1,"B");
	hptt->Fit("pol4");
	hptt->SetMinimum(0.0);
	hptt->SetMaximum(1.0);
	hptt->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hptt->GetYaxis()->SetTitle("efficiency");
	hptt->SetStats(0);
	hptt->Draw("");
	TH1F *hpttint = hptt->Clone("hpttint");
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hpttint,0.68);
	hpttint->SetFillColor(2);
	hpttint->SetStats(0);
	hpttint->Draw("e3 same");
	TH1F * hpttcopy = hptt->Clone("hpttcopy");
	TH1F * hpttintcopy = hpttint->Clone("hpttintcopy");
	hptt->Reset();
	
	tageff4->cd();
	hmmetadeno->Add(heeetadeno);
	hmmetadeno->Add(hemetadeno);
	hmmetanumel->Add(heeetanumel);
	hmmetanumel->Add(hemetanumel);
	TH1F* hetal = hmmetadeno->Clone("hetal");
	hetal->Sumw2();
	hetal->SetTitle("tagging efficiency(CSVL)");
	hetal->Divide(hmmetanumel,hmmetadeno,1,1,"B");
	hetal->Fit("pol4");
	hetal->SetMinimum(0.0);
	hetal->SetMaximum(1.0);
	hetal->GetXaxis()->SetTitle("#void8#eta#void8");
	hetal->GetYaxis()->SetTitle("efficiency");
	hetal->SetStats(0);
	hetal->Draw("");
	TH1F *hetalint = hetal->Clone("hetalint");
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hetalint,0.68);
	hetalint->SetFillColor(2);
	hetalint->SetStats(0);
	hetalint->Draw("e3 same");
	hetal->Reset();
	
	tageff5->cd();
	hmmetanumem->Add(heeetanumem);
	hmmetanumem->Add(hemetanumem);
	TH1F* hetam = hmmetadeno->Clone("hetam");
	hetam->Sumw2();
	hetam->SetTitle("tagging efficiency(CSVM)");
	hetam->Divide(hmmetanumem,hmmetadeno,1,1,"B");
	hetam->Fit("pol4");
	hetam->SetMinimum(0.0);
	hetam->SetMaximum(1.0);
	hetam->GetXaxis()->SetTitle("#void8#eta#void8");
	hetam->GetYaxis()->SetTitle("efficiency");
	hetam->SetStats(0);
	hetam->Draw("");
	TH1F *hetamint = hetam->Clone("hetamint");
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hetamint,0.68);
	hetamint->SetFillColor(2);
	hetamint->SetStats(0);
	hetamint->Draw("e3 same");
	hetam->Reset();
	
	tageff6->cd();
	hmmetanumet->Add(heeetanumet);
	hmmetanumet->Add(hemetanumet);
	TH1F* hetat = hmmetadeno->Clone("hetat");
	hetat->Sumw2();
	hetat->SetTitle("tagging efficiency(CSVT)");
	hetat->Divide(hmmetanumet,hmmetadeno,1,1,"B");
	hetat->Fit("pol4");
	hetat->SetMinimum(0.0);
	hetat->SetMaximum(1.0);
	hetat->GetXaxis()->SetTitle("#void8#eta#void8");
	hetat->GetYaxis()->SetTitle("efficiency");
	hetat->SetStats(0);
	hetat->Draw("");
	TH1F *hetatint = hetat->Clone("hetatint");
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hetatint,0.68);
	hetatint->SetFillColor(2);
	hetatint->SetStats(0);
	hetatint->Draw("e3 same");
	hetat->Reset();
	
	tageff7->cd();
	hmmdeno->Add(heedeno);
	hmmdeno->Add(hemdeno);
	hmmnumel->Add(heenumel);
	hmmnumel->Add(hemnumel);
	TH2F* hl = hmmdeno->Clone("hl");
	hl->Sumw2();
	hl->SetTitle("tagging efficiency(CSVL)");
	hl->Divide(hmmnumel,hmmdeno,1,1,"B");
	hl->Fit("pol4");
	hl->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hl->GetYaxis()->SetTitle("#void8#eta#void8");
	hl->SetStats(0);
	hl->Draw("SURF4");
	
	tageff8->cd();
	hmmnumem->Add(heenumem);
	hmmnumem->Add(hemnumem);
	TH2F* hm = hmmdeno->Clone("hm");
	hm->Sumw2();
	hm->SetTitle("tagging efficiency(CSVM)");
	hm->Divide(hmmnumem,hmmdeno,1,1,"B");
	hm->Fit("pol4");
	hm->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hm->GetYaxis()->SetTitle("#void8#eta#void8");
	hm->SetStats(0);
	hm->Draw("SURF4");
	
	tageff9->cd();
	hmmnumet->Add(heenumet);
	hmmnumet->Add(hemnumet);
	TH2F* ht = hmmdeno->Clone("ht");
	ht->Sumw2();
	ht->SetTitle("tagging efficiency(CSVT)");
	ht->Divide(hmmnumet,hmmdeno,1,1,"B");
	ht->Fit("pol4");
	ht->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	ht->GetYaxis()->SetTitle("#void8#eta#void8");
	ht->SetStats(0);
	ht->Draw("SURF4");
	
	tageff10->cd();
	hmmptdenottbb->Add(heeptdenottbb);
	hmmptdenottbb->Add(hemptdenottbb);
	hmmptnumemttbb->Add(heeptnumemttbb);
	hmmptnumemttbb->Add(hemptnumemttbb);
	TH1F* hptmttbb = hmmptdeno->Clone("hptmttbb");
	hptmttbb->Sumw2();
	hptmttbb->SetTitle("tagging efficiency(CSVM)");
	hptmttbb->Divide(hmmptnumemttbb,hmmptdenottbb,1,1,"B");
	hptmttbb->Fit("pol4");
	hptmttbb->SetMinimum(0.0);
	hptmttbb->SetMaximum(1.0);
	hptmttbb->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hptmttbb->GetYaxis()->SetTitle("efficiency");
	hptmttbb->SetStats(0);
	hptmttbb->Draw("");
	TH1F *hptmttbbint = hptmttbb->Clone("hptmttbbint");
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hptmttbbint,0.68);
	hptmttbbint->SetFillColor(2);
	hptmttbbint->SetStats(0);
	hptmttbbint->Draw("e3 same");
	TH1F * hptmttbbcopy = hptmttbb->Clone("hptmttbbcopy");
	TH1F * hptmttbbintcopy = hptmttbbint->Clone("hptmttbbintcopy");
	hptmttbb->Reset();
	
	tageff11->cd();
	hmmptdenottll->Add(heeptdenottll);
	hmmptdenottll->Add(hemptdenottll);
	hmmptnumemttll->Add(heeptnumemttll);
	hmmptnumemttll->Add(hemptnumemttll);
	TH1F* hptmttll = hmmptdeno->Clone("hptmttll");
	hptmttll->Sumw2();
	hptmttll->SetTitle("tagging efficiency(CSVM)");
	hptmttll->Divide(hmmptnumemttll,hmmptdenottll,1,1,"B");
	hptmttll->Fit("pol4");
	hptmttll->SetMinimum(0.0);
	hptmttll->SetMaximum(1.0);
	hptmttll->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hptmttll->GetYaxis()->SetTitle("efficiency");
	hptmttll->SetStats(0);
	hptmttll->Draw("");
	TH1F *hptmttllint = hptmttll->Clone("hptmttllint");
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hptmttllint,0.68);
	hptmttllint->SetFillColor(2);
	hptmttllint->SetStats(0);
	hptmttllint->Draw("e3 same");
	TH1F * hptmttllcopy = hptmttll->Clone("hptmttllcopy");
	TH1F * hptmttllintcopy = hptmttllint->Clone("hptmttllintcopy");
	hptmttll->Reset();
	
	tageff12->cd();
	hmmptnumetttbb->Add(heeptnumetttbb);
	hmmptnumetttbb->Add(hemptnumetttbb);
	TH1F* hpttttbb = hmmptdeno->Clone("hpttttbb");
	hpttttbb->Sumw2();
	hpttttbb->SetTitle("tagging efficiency(CSVT)");
	hpttttbb->Divide(hmmptnumetttbb,hmmptdenottbb,1,1,"B");
	hpttttbb->Fit("pol4");
	hpttttbb->SetMinimum(0.0);
	hpttttbb->SetMaximum(1.0);
	hpttttbb->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hpttttbb->GetYaxis()->SetTitle("efficiency");
	hpttttbb->SetStats(0);
	hpttttbb->Draw("");
	TH1F *hpttttbbint = hpttttbb->Clone("hpttttbbint");
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hpttttbbint,0.68);
	hpttttbbint->SetFillColor(2);
	hpttttbbint->SetStats(0);
	hpttttbbint->Draw("e3 same");
	TH1F * hpttttbbcopy = hpttttbb->Clone("hpttttbbcopy");
	TH1F * hpttttbbintcopy = hptlint->Clone("hpttttbbintcopy");
	hpttttbb->Reset();
	
	tageff13->cd();
	hmmptnumetttll->Add(heeptnumetttll);
	hmmptnumetttll->Add(hemptnumetttll);
	TH1F* hpttttll = hmmptdeno->Clone("hpttttll");
	hpttttll->Sumw2();
	hpttttll->SetTitle("tagging efficiency(CSVT)");
	hpttttll->Divide(hmmptnumetttll,hmmptdenottll,1,1,"B");
	hpttttll->Fit("pol4");
	hpttttll->SetMinimum(0.0);
	hpttttll->SetMaximum(1.0);
	hpttttll->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hpttttll->GetYaxis()->SetTitle("efficiency");
	hpttttll->SetStats(0);
	hpttttll->Draw("");
	TH1F *hpttttllint = hpttttll->Clone("hpttttllint");
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hpttttllint,0.68);
	hpttttllint->SetFillColor(2);
	hpttttllint->SetStats(0);
	hpttttllint->Draw("e3 same");
	TH1F * hpttttllcopy = hpttttll->Clone("hpttttllcopy");
	TH1F * hpttttllintcopy = hpttttllint->Clone("hpttttllintcopy");
	hpttttll->Reset();
	
	tageff14->cd();
	hptmcopy->SetLineColor(1);
	hptmcopy->Draw("");
	hptmintcopy->SetLineColor(1);
	hptmintcopy->SetFillStyle(3004);
	hptmintcopy->SetFillColor(1);
	hptmintcopy->Draw("e3 same");
	hptmttbbcopy->SetLineColor(2);
	hptmttbbintcopy->SetLineColor(2);
	hptmttbbintcopy->SetFillStyle(3005);
	hptmttbbintcopy->SetFillColor(2);
	hptmttbbcopy->Draw("same");
	hptmttbbintcopy->Draw("e3 same");
	hptmttllcopy->SetLineColor(3);
	hptmttllintcopy->SetLineColor(3);
	hptmttllintcopy->SetFillStyle(3006);
	hptmttllintcopy->SetFillColor(3);
	hptmttllcopy->Draw("same");
	hptmttllintcopy->Draw("e3 same");
	
	TLegend *l = new TLegend(0.75,0.62,0.92,0.88);
	l->AddEntry(hptmintcopy,"tt + jj","L");
	l->AddEntry(hptmttbbintcopy,"tt + bb","L");
	l->AddEntry(hptmttllintcopy,"tt + ll","L");
	l->SetTextSize(0.04);
	l->SetFillColor(0);
	l->SetLineColor(0);	
	l->Draw();
	
	hptmcopy->Reset();
	hptmttbbcopy->Reset();
	hptmttllcopy->Reset();

	TFile* result = new TFile("taggingefficiency.root","RECREATE");
	tageff1->Write();
	tageff2->Write();
	tageff3->Write();
	tageff4->Write();
	tageff5->Write();
	tageff6->Write();
	tageff7->Write();
	tageff8->Write();
	tageff9->Write();
	tageff10->Write();
	tageff11->Write();
	tageff12->Write();
	tageff13->Write();
	tageff14->Write();
	result->Close();
}
