 //unit pb
 double scale = 1.0;

 //luminosity
 double lumi_e=0.078;

 //cross section at D0 
 //double Zmm = 242 ;
 //double Ztt = 242 ;
 //double tt = 0.7 ;
 //double WW = 1.08 ;
 //double WZ = 0.1104 ;
 //double ZZ = 0.071;
 //double Wm = 2583 ;
 //double ZZ4mu = 0.001278;
 //cross section at CMS at 7 TeV 
 double Zmm     = 1300 ;
 double Ztautau = 1300 ;
 double Wmunu   = 7899;
 double Wtautau = 7899;
 double tt      = 94.3;
 double tt2l    = 17.3;
 double QCD     = 296900000;

 //total number of events
 double N_Zmm     = 100000 ; //2076806
 double N_Ztautau = 100000 ; //1265250
 double N_Wmunu   = 50000; 
 double N_Wtautau = 100000;
  
 double N_tt   = 100000 ; //103500
 double N_tt2l = 100000 ; //103500

 double N_QCD = 6000000;
 //luminosity for MC
 double L_Zmm     = N_Zmm/Zmm;
 double L_Ztautau = N_Ztautau/Ztautau;
 double L_Wmunu   = N_Wmunu/Wmunu;
 double L_Wtautau = N_Wtautau/Wtautau;
 double L_tt      = N_tt/tt;
 double L_tt2l    = N_tt2l/tt2l;
 double L_QCD     = N_QCD/QCD;
 
 //normalization factor 
 double norm_Zmm      =   lumi_e / L_Zmm ;
 double norm_Ztautau  =   lumi_e / L_Ztautau ;
 double norm_Wmunu    =   lumi_e / L_Wmunu ;
 double norm_Wtautau  =   lumi_e / L_Wtautau ;
 double norm_tt       =   lumi_e / L_tt;
 double norm_tt2l     =   lumi_e / L_tt2l;
 double norm_QCD      =   lumi_e / L_QCD;
