#include "TF1.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "SFlightFuncs2012.C"

void GetSFlightPlot2012(){

  TCanvas * c_m = new TCanvas("c_m","c_m",1);

  TF1* SFlight_m = GetSFlmean("CSV","M",0.0, 0.8, "ABCD");
  TF1* SFlightmin_m = GetSFlmin("CSV","M",0.0, 0.8, "ABCD");
  TF1* SFlightmax_m = GetSFlmax("CSV","M",0.0, 0.8, "ABCD");

  SFlight_m->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  SFlight_m->GetYaxis()->SetTitle("Scale Factor (light flavor)");
  SFlight_m->SetTitle("");

  SFlight_m->SetMaximum(1.6);
  SFlight_m->SetMinimum(0.6);
  SFlight_m->Draw();
  SFlightmin_m->Draw("same");
  SFlightmax_m->Draw("same");
  SFlightmin_m->SetLineColor(3);
  SFlightmax_m->SetLineColor(3);
 
  c_m->Print("SFlight2012_CSVM.eps");
 

  TCanvas * c_t = new TCanvas("c_t","c_t",1);

  TF1* SFlight_t = GetSFlmean("CSV","T",0.0, 2.4, "ABCD");
  TF1* SFlightmin_t = GetSFlmin("CSV","T",0.0, 2.4, "ABCD");
  TF1* SFlightmax_t = GetSFlmax("CSV","T",0.0, 2.4, "ABCD");

  SFlight_t->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
  SFlight_t->GetYaxis()->SetTitle("Scale Factor (light flavor)");
  SFlight_t->SetTitle("");

  SFlight_t->SetMaximum(1.6);
  SFlight_t->SetMinimum(0.6);
  SFlight_t->Draw();
  SFlightmin_t->Draw("same");
  SFlightmax_t->Draw("same");
  SFlightmin_t->SetLineColor(3);
  SFlightmax_t->SetLineColor(3);

  c_t->Print("SFlight2012_CSVT.eps");


}
