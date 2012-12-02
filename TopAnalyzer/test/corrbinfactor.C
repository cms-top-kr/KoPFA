#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TFile.h"
#include <iostream>
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
using namespace std;
void corrbinfactor()
{
	TFile * f = new TFile("ttbarGen.root");
	gDirectory->cd("ttbarGenAna");
	TH1F * h = new TH1F("h","h",1400,0,1400);
	tree->Draw("ttbarGen.tt_.mass() >> h");
	float detBins[] = {0, 340, 400, 450, 500,  550, 600, 700, 800, 1400};
    int nDet = sizeof(detBins)/sizeof(float) - 1;
	double x1[10],x2[10],x3[10];
	for (int i = 0; i < nDet + 1 ; i++)
	{
		x1[i] = h->Integral(detBins[i],detBins[i+1]);
		x2[i] = h->GetBinContent((detBins[i+1]+detBins[i])/2);
		if (x1[i] == 0)
			x3[i] = 0;
		else
			x3[i] = x2[i]/x1[i];
	}
	cout << x3[0] << endl;
	cout << x3[1] << endl;
	cout << x3[2] << endl;
	cout << x3[3] << endl;
	cout << x3[4] << endl;
	cout << x3[5] << endl;
	cout << x3[6] << endl;
	cout << x3[7] << endl;
	cout << x3[8] << endl;
}
