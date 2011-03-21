void ROCTnP(){
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();


  TFile * fbkg3 = new TFile("/home/tjkim/ntuple/iso/data/QCD_new/vallot.root");
  TTree * tbkg3 = (TTree *) fbkg3->Get("MuonAna/tree");

  TCut cutbkg3 = "pt > 20 && pt < 50 && multiplicity == 1 && @jetspt30.size() >= 1 && delphi < 1.5 && mt < 20"; 
  
  TH1* h_bkg3 = new TH1F("h_bkg3","h_bkg",50,0,0.5);
  tbkg3->Project("h_bkg3","(chIsoOpt04+phIsoOpt04+nhIsoOpt04)/pt", cutbkg3);

  //Data vs PU
  plot(h_bkg3, "Data", "MC (PU)" , "QCD_MC_pt20_50_PU" , "p_{T}=20-50 GeV" );
  
}

void plot(TH1* h_bkg, const TString& leg1, const TString& leg2, const TString& name, const TString &header){
  //Disable NoPileUp pt > 20 && pt <50
  //double eff_sig_mc[] = { 0.777097, 0.817503, 0.848577, 0.874898, 0.895996, 0.91393, 0.925849, 0.936758, 0.945159, 0.952213, 0.959501, 0.964424, 0.967803, 0.970706, 0.973994, 0.976333, 0.978711, 0.980532, 0.981996, 0.983742, 0.985043, 0.986117, 0.987224};
  //double mc_errY_high[] = { 0.00296416, 0.00279095, 0.00261571, 0.00244458, 0.0022896, 0.00211358, 0.00198766, 0.0018811, 0.00177614, 0.00167537, 0.00157868, 0.00148989, 0.00143445, 0.00137324, 0.00131343, 0.00124855, 0.00119739, 0.00115326, 0.00111317, 0.00107009, 0.00104057, 0.00100481, 0.000971194  };
  //double mc_errY_low[] = { 0.0029893, 0.00280266, 0.00263175, 0.00246867, 0.00229444, 0.0021617, 0.00203377, 0.00190559, 0.00179992, 0.00171237, 0.00159944, 0.00151928, 0.00145079, 0.00138794, 0.00133022, 0.00127416, 0.00122056, 0.00117508, 0.00113644, 0.00109011, 0.00105959, 0.00102594, 0.000997564 };


  // pt > 20 && pt <50 with tight muon
  //double eff_sig_data[] = {0.854924, 0.882504,  0.904535,  0.921796,   0.934912,  0.945304, 0.95352, 0.960589 ,  0.965924, 0.969319,  0.97278,  0.975907, 0.978318, 0.980017, 0.982006, 0.983305,  0.984726, 0.986045, 0.987406, 0.988623, 0.989513, 0.990199, 0.991073};
  //double data_errY_high[] = { 0.00272733, 0.00253665, 0.00234661, 0.00218691, 0.00203661, 0.00191659, 0.00179405, 0.00169531, 0.00160113, 0.00153607, 0.001469, 0.00140937, 0.00135369, 0.00131713, 0.00126881, 0.0012321, 0.00119582, 0.00115973, 0.00112235, 0.0010931, 0.00106187, 0.00103808, 0.00101155};
  //double data_errY_low[] = {  0.00274547, 0.00255775, 0.00237854, 0.00220984, 0.00207029, 0.001942, 0.00183573, 0.0017302, 0.0016308, 0.00156618, 0.00149596, 0.00143587, 0.00138969, 0.00133985, 0.00129132, 0.00125429, 0.00121867, 0.00118433, 0.00114815, 0.00111449, 0.00109479, 0.00107199, 0.00104858};
  //double eff_sig_mc[] = {  0.88329, 0.905857,  0.923565, 0.936937, 0.947608, 0.955828,0.962467, 0.967751, 0.972362, 0.975395,  0.978247, 0.980247,  0.982426,
  //                   , 0.983757, 0.985424, 0.986361, 0.987075, 0.987813, 0.988767, 0.989528, 0.990471, 0.990881,  0.990998};
  //double mc_errY_high[] ={  0.00281113, 0.00257327, 0.00235248, 0.00217405, 0.00201008, 0.00186546, 0.0017571, 0.00162143, 0.00152733, 0.00144247, 0.0013649, 0.00129975, 0.00123287, 0.00118607, 0.00111774, 0.00106578, 0.00102949, 0.00100854, 0.000960115, 0.000922256, 0.000886947, 0.000856076, 0.000839435}; 
  //double mc_errY_low[] ={  0.00283226, 0.00260319, 0.00240016, 0.00220971, 0.00205239, 0.00191512, 0.0017878, 0.0016642, 0.00156019, 0.001473, 0.00139423, 0.00133572, 0.00126687, 0.00121723, 0.00114754, 0.00110279, 0.00107542, 0.00103819, 0.000998335, 0.000961736, 0.000918542, 0.000891498, 0.000878688};

  //pfmuon pt > 20 && pt <50
  
//  double eff_sig_data[] = {0.852906, 0.882518, 0.904202, 0.921838, 0.935377, 0.945283, 0.952924, 0.959412, 0.96536, 0.968942, 0.972033, 0.975294, 0.977692, 0.979146, 0.981267, 0.982567, 0.98409, 0.985574, 0.986709, 0.988002, 0.989097, 0.989922, 0.990782}; 
//  double data_errY_high[] = {0.00303023, 0.00280279, 0.00260926, 0.00239772, 0.00222697, 0.00209268, 0.00196042, 0.00184747, 0.00172756, 0.00164882, 0.0015734, 0.00149994, 0.00144179, 0.00139572, 0.00133252, 0.00129119, 0.00124975, 0.00120267, 0.0011662, 0.00112349, 0.00108148, 0.00104925, 0.00101346}; 
//  double data_errY_low[] = { 0.00305564, 0.00282421, 0.00260647, 0.00243107, 0.0022605, 0.00212408, 0.00200424, 0.00188964, 0.00176292, 0.00168155, 0.00160969, 0.00153518, 0.00147538, 0.00142713, 0.00136821, 0.00132521, 0.00128328, 0.00123444, 0.00119643, 0.00115899, 0.00113148, 0.00109593, 0.00107}; 
  //new
  double eff_sig_data[] = { 0.854278, 0.882006, 0.904698, 0.921771, 0.934692, 0.945063, 0.952763, 0.959916, 0.965438, 0.969068, 0.972388, 0.975373, 0.977695, 0.979406, 0.981525, 0.98277, 0.984248, 0.985752, 0.986893, 0.988057, 0.988947, 0.98956, 0.990327 };
  double data_errY_high[] = { 0.00258889, 0.00239578, 0.00221409, 0.00228838, 0.00191174, 0.00179234, 0.00168477, 0.00158011, 0.00148129, 0.00141319, 0.00138971, 0.00128441, 0.00123691, 0.00119217, 0.00113906, 0.00110401, 0.00106734, 0.00102511, 0.000991171, 0.000955544, 0.000933315, 0.000914105, 0.000885432 };
  double data_errY_low[] = { 0.00259572, 0.00241887, 0.00223474, 0.00242084, 0.00193662, 0.00181665, 0.00171027, 0.00161287, 0.00151149, 0.00144113, 0.00143174, 0.0013114, 0.00125811, 0.00121253, 0.00116, 0.00112402, 0.00108772, 0.00104577, 0.00101604, 0.000988753, 0.000960771, 0.000933588, 0.000916392 };


  //double eff_sig_mc[] = { 0.888736, 0.912009, 0.928784, 0.941291, 0.951524, 0.958932, 0.964167, 0.969483, 0.97429, 0.977268, 0.980329, 0.982977, 0.984729, 0.986083, 0.987417, 0.988749, 0.989564, 0.990163, 0.991052, 0.991405, 0.991851, 0.992188, 0.99277};
  //double mc_errY_high[] ={0.00231037, 0.00210617, 0.00193263, 0.00178263, 0.00164766, 0.00151176, 0.00144318, 0.0013445, 0.00125087, 0.0011825, 0.00111634, 0.00104354, 0.000989734, 0.00094588, 0.000904283, 0.000863275, 0.000830599, 0.00082247, 0.000768234, 0.000754605, 0.000735804, 0.000708555, 0.000683636};
 
  //double mc_errY_low[] ={ 0.00232636, 0.00211623, 0.00195119, 0.00180292, 0.00166338, 0.00156111, 0.00146925, 0.00137134, 0.00127559, 0.00120994, 0.00113344, 0.00106846, 0.00101436, 0.000973547, 0.000931645, 0.000889717, 0.000854591, 0.000840649, 0.00079682, 0.000781843, 0.000761704, 0.000734842, 0.000707864};
 
  //PU
  //double eff_sig_data[] = { 0.863671, 0.891931, 0.912327, 0.92809, 0.941113, 0.950261, 0.957942, 0.964278, 0.968983, 0.973555, 0.976774, 0.979176, 0.981454, 0.98226, 0.984897, 0.986644, 0.988112, 0.989, 0.989802, 0.990395, 0.991323, 0.991785, 0.992222 }; 
  //double data_errY_high[] ={ 0.00244652, 0.00223015, 0.00206387, 0.0019187, 0.0017636, 0.00163899, 0.00153817, 0.0014449, 0.00136296, 0.00126888, 0.00119982, 0.0011426, 0.00108433, 0.00570291, 0.000983534, 0.000932786, 0.000883148, 0.000846843, 0.000816589, 0.000794136, 0.000756715, 0.000727642, 0.00070662 }; 
  //double data_errY_low[] ={ 0.00245753, 0.00227668, 0.00208199, 0.00193148, 0.00180322, 0.00167872, 0.00155891, 0.00146565, 0.00138626, 0.00129328, 0.00122968, 0.00117314, 0.00111699, 0.00483786, 0.001009, 0.000955494, 0.000911435, 0.000871955, 0.000842384, 0.000812678, 0.000781107, 0.000756909, 0.000729905 }; 

  //PU reweighting
  double eff_sig_mc[] = { 0.867079, 0.89499, 0.915219, 0.930813, 0.943367, 0.951977, 0.959214, 0.965226, 0.969838, 0.974225, 0.977315, 0.979737, 0.981951, 0.983382, 0.985175, 0.986739, 0.988274, 0.989187, 0.989997, 0.990575, 0.99152, 0.991946, 0.992353  };
  double mc_errY_high[] ={ 0.00238169, 0.00217114, 0.00200748, 0.0018516, 0.00172672, 0.0015856, 0.00149472, 0.00140433, 0.00132614, 0.00123435, 0.00116539, 0.00110722, 0.00105557, 0.00101728, 0.000957019, 0.000910408, 0.000862843, 0.000825312, 0.000795245, 0.000770742, 0.000736819, 0.000708125, 0.000687902,  };
  double mc_errY_low[] ={ 0.00239742, 0.00220975, 0.00201958, 0.00188083, 0.00172641, 0.00163287, 0.0015143, 0.00142623, 0.00134865, 0.0012591, 0.00119689, 0.00113576, 0.00107585, 0.00103235, 0.000981741, 0.000935602, 0.000889717, 0.000850958, 0.000820614, 0.000795305, 0.00076066, 0.000736873, 0.000715087};

  // 20 GeV - 150 GeV
  //double eff_sig_data[] = { 0.864175, 0.891814, 0.912088, 0.928322, 0.940793, 0.949959, 0.957069, 0.963421, 0.968617, 0.971816, 0.974627, 0.977661, 0.979937, 0.981356, 0.983201, 0.984349, 0.985683, 0.986977, 0.98805, 0.989248, 0.990211, 0.990946, 0.991755  };
 //double data_errY_high[] = { 0.0027439, 0.0025327, 0.00234663, 0.00216908, 0.00201482, 0.00188478, 0.00176371, 0.00165946, 0.00155791, 0.00148256, 0.00142545, 0.0013601, 0.00130282, 0.0012605, 0.00120428, 0.00116604, 0.00112897, 0.00108672, 0.00105313, 0.0010191, 0.000986022, 0.000954859, 0.000928344  };
 //double data_errY_low[] = { 0.00275908, 0.00255678, 0.00236719, 0.00219589, 0.00204067, 0.0019225, 0.00181801, 0.00170346, 0.00159158, 0.00152477, 0.00145161, 0.00137939, 0.0013278, 0.00128448, 0.00123372, 0.00119962, 0.0011647, 0.0011227, 0.0010868, 0.00104816, 0.00102167, 0.000992145, 0.000961869  };
 //mc
 //double eff_sig_mc[] = { 0.897581, 0.919634, 0.935253, 0.946748, 0.956239, 0.963076, 0.967943, 0.972637, 0.976995, 0.979646, 0.982517, 0.984933, 0.98648, 0.987782, 0.988956, 0.990113, 0.990823, 0.991354, 0.992166, 0.992477, 0.992868, 0.993167, 0.993672 };
 //double mc_errY_high[] ={ 0.00207214, 0.0018793, 0.00171757, 0.00158495, 0.00146258, 0.00135368, 0.00127701, 0.00118764, 0.00110352, 0.00105137, 0.00098227, 0.000923675, 0.000877636, 0.000835143, 0.00079842, 0.000761686, 0.000733266, 0.000711171, 0.000678676, 0.000665729, 0.000649476, 0.00062594, 0.000602485  };
 //double mc_errY_low[] ={ 0.00208434, 0.00189142, 0.00174217, 0.00160739, 0.0014825, 0.00137205, 0.00130236, 0.00122133, 0.00113812, 0.00106893, 0.00100975, 0.000943909, 0.00089468, 0.000857823, 0.00081936, 0.000783544, 0.000752868, 0.000735472, 0.000700937, 0.000689381, 0.000672055, 0.000647758, 0.000625914};
  //PU
 //double eff_sig_mc[] = { 0.875163, 0.90094, 0.919921, 0.934467, 0.946478, 0.954888, 0.961751, 0.967489, 0.971783, 0.975909, 0.978927, 0.981109, 0.983213, 0.984571, 0.986317, 0.987881, 0.989152, 0.989931, 0.990629, 0.991236, 0.992042, 0.992494, 0.992925};
 //double mc_errY_high[] ={ 0.00219511, 0.00200216, 0.00183731, 0.00171106, 0.00157793, 0.00146816, 0.00137091, 0.00128601, 0.00121174, 0.00112389, 0.00106935, 0.00101732, 0.000964859, 0.000927103, 0.000872063, 0.000826511, 0.00078551, 0.00074961, 0.000724737, 0.00069992, 0.000670512, 0.000646625, 0.000625464 };
  //double mc_errY_low[] ={ 0.00217668, 0.00201282, 0.00185182, 0.00171296, 0.00159428, 0.00148409, 0.00138782, 0.00130462, 0.00123476, 0.00115524, 0.00109163, 0.00103876, 0.000984866, 0.000946727, 0.000896514, 0.000851046, 0.000807476, 0.000771965, 0.000746157, 0.000721521, 0.00069229, 0.000667671, 0.000645184 };

  TGraphAsymmErrors *gr_data = new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_mc = new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_opt_data = new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_opt_mc = new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_data_sigeff = new TGraphAsymmErrors();
  TGraphAsymmErrors *gr_mc_sigeff = new TGraphAsymmErrors();

  double optsoverb_data = 0;
  double optval_data = 0;
  double opteff_data = 0;
  double optsoverb_mc = 0;
  double optval_mc = 0;
  double opteff_mc = 0;
  cout << "QCD=" << h_bkg->GetEntries() << endl;
  for(int i=0 ; i < 23 ; i++  ){
    double bin = i*1+6;
    double point = h_bkg->GetBinLowEdge(bin)+h_bkg->GetBinWidth(bin);
    double eff_bkg = h_bkg->Integral(1,bin)/h_bkg->GetEntries();
    double soverb_data = eff_sig_data[i]/sqrt(eff_sig_data[i]+eff_bkg);
    double soverb_mc = eff_sig_mc[i]/sqrt(eff_sig_mc[i]+eff_bkg);
   
//    double soverb_data = eff_sig_data[i]*200000/sqrt(eff_sig_data[i]*200000+eff_bkg*h_bkg->GetEntries());
//    double soverb_mc = eff_sig_mc[i]*200000/sqrt(eff_sig_mc[i]*200000+eff_bkg*h_bkg->GetEntries());
   
    cout << "[" << point << "]:" << "bkg eff= " << eff_bkg << " sig eff (data)= " << eff_sig_data[i] << " sig eff (mc)= " << eff_sig_mc[i] << endl;
    gr_opt_data->SetPoint(i, point, soverb_data);
    gr_opt_mc->SetPoint(i, point, soverb_mc);


    if( soverb_data > optsoverb_data){
      optsoverb_data = soverb_data;
      optval_data = point;
      opteff_data = eff_sig_data[i];
    }

    if( soverb_mc > optsoverb_mc){
      optsoverb_mc = soverb_mc;
      optval_mc = point;
      opteff_mc = eff_sig_data[i];
    }

    gr_data->SetPoint(i, eff_bkg, eff_sig_data[i]);
    gr_data->SetPointEYhigh(i, data_errY_high[i]);    
    gr_data->SetPointEYlow(i, data_errY_low[i]);    
    gr_data->SetPointEXhigh(i, sqrt(h_bkg->Integral(1,bin))/h_bkg->GetEntries());
    gr_data->SetPointEXlow(i, sqrt(h_bkg->Integral(1,bin))/h_bkg->GetEntries());

    gr_mc->SetPoint(i, eff_bkg, eff_sig_mc[i]);
    gr_mc->SetPointEYhigh(i, mc_errY_high[i]);
    gr_mc->SetPointEYlow(i, mc_errY_low[i]);
    gr_mc->SetPointEXhigh(i, sqrt(h_bkg->Integral(1,bin))/h_bkg->GetEntries());
    gr_mc->SetPointEXlow(i, sqrt(h_bkg->Integral(1,bin))/h_bkg->GetEntries());

    gr_data_sigeff->SetPoint(i, point, eff_sig_data[i]);
    gr_data_sigeff->SetPointEYhigh(i, data_errY_high[i]);
    gr_data_sigeff->SetPointEYlow(i, data_errY_low[i]);

    gr_mc_sigeff->SetPoint(i, point, eff_sig_mc[i]);
    gr_mc_sigeff->SetPointEYhigh(i, mc_errY_high[i]);
    gr_mc_sigeff->SetPointEYlow(i, mc_errY_low[i]);
    
  }

  TCanvas* c_eff= new TCanvas(Form("c_eff_%s",name.Data()),Form("c_eff_%s",name.Data()),1);
  gr_data_sigeff->GetYaxis()->SetTitle("Isolation Efficiency");
  gr_data_sigeff->GetXaxis()->SetTitle("RelIso");
  gr_data_sigeff->SetLineColor(1);
  gr_data_sigeff->SetLineWidth(2);
  gr_data_sigeff->SetMarkerColor(1);
  gr_data_sigeff->SetMarkerSize(1.1);
  gr_data_sigeff->SetMarkerStyle(20);
  gr_data_sigeff->Draw("ACP");
  gr_data_sigeff->SetFillColor(30);
  gr_data_sigeff->SetFillStyle(3001);

  gr_mc_sigeff->SetLineColor(2);
  gr_mc_sigeff->SetLineWidth(2);
  gr_mc_sigeff->SetMarkerColor(2);
  gr_mc_sigeff->SetMarkerSize(1.1);
  gr_mc_sigeff->SetMarkerStyle(21);
  gr_mc_sigeff->Draw("CPSame");
  gr_mc_sigeff->SetFillColor(5);
  gr_mc_sigeff->SetFillStyle(3001);

  TLegend *l_eff= new TLegend(0.6,0.3,0.9,0.45);
  l_eff->SetHeader(Form("%s",header.Data()));
  l_eff->AddEntry(gr_data_sigeff,Form("%s",leg1.Data()),"PL");
  l_eff->AddEntry(gr_mc_sigeff,Form("%s",leg2.Data()),"PL");
  l_eff->SetTextSize(0.04);
  l_eff->SetFillColor(0);
  l_eff->SetLineColor(0);
  l_eff->Draw();
  c_eff->Print(Form("c_eff_%s.eps",name.Data()));
  c_eff->Print(Form("c_eff_%s.C",name.Data()));
  c_eff->Print(Form("c_eff_%s.png",name.Data()));

  TCanvas* c= new TCanvas(Form("c_%s",name.Data()),Form("c_%s",name.Data()),1);
  gr_data->GetYaxis()->SetTitle("Signal Efficiency");
  gr_data->GetXaxis()->SetTitle("QCD Efficiency");
  gr_data->SetLineColor(1);
  gr_data->SetLineWidth(2);
  gr_data->SetMarkerColor(1);
  gr_data->SetMarkerSize(1.1);
  gr_data->SetMarkerStyle(20);
  gr_data->Draw("ACP");
  gr_data->SetFillColor(30);
  gr_data->SetFillStyle(1001);


  gr_mc->SetLineColor(2);
  gr_mc->SetLineWidth(2);
  gr_mc->SetMarkerColor(2);
  gr_mc->SetMarkerSize(1.1);
  gr_mc->SetMarkerStyle(21);
  gr_mc->Draw("CPSame");
  gr_mc->SetFillColor(5);
  gr_mc->SetFillStyle(3001);
 
  TLegend *l= new TLegend(0.6,0.3,0.9,0.45);
  l->SetHeader(Form("%s",header.Data()));
  l->AddEntry(gr_data,Form("%s",leg1.Data()),"PL");
  l->AddEntry(gr_mc,Form("%s",leg2.Data()),"PL");
  l->SetTextSize(0.04);
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->Draw();
  c->Print(Form("c_ROCtnp_%s.eps",name.Data()));
  c->Print(Form("c_ROCtnp_%s.C",name.Data()));
  c->Print(Form("c_ROCtnp_%s.png",name.Data()));

  //TCanvas *c_opt = new TCanvas(Form("c_opt_%s",name.Data()),Form("c_opt_%s",name.Data()),1);
  //gr_opt_mc->Draw("ACP");
  gr_opt_mc->GetYaxis()->SetTitle("s / #sqrt{(s+b)}");
  gr_opt_mc->SetMarkerColor(2);
  gr_opt_mc->SetLineColor(2);
  //gr_opt_data->Draw("CPSame");
  gr_opt_data->SetLineColor(1);
  gr_opt_data->SetMarkerColor(1);
  //TLatex *label= new TLatex;
  //label->SetNDC();
  //label->SetTextSize(0.04);
  //label->DrawLatex(0.4,0.3.5,  Form("%5.2f at %5.2f for Data",opteff_data,optval_data));
  //label->DrawLatex(0.4,0.2.9,Form("%5.2f at %5.2f for MC",opteff_mc,optval_mc));
  TLegend *lopt= new TLegend(0.4,0.2,0.7,0.45);
  lopt->SetHeader("p_{T}=20-50 GeV");
  lopt->AddEntry(gr_data,Form("Data %5.2f at %5.2f",opteff_data,optval_data),"PL");
  lopt->AddEntry(gr_mc,Form("MC %5.2f at %5.2f",opteff_mc,optval_mc),"PL");
  lopt->SetTextSize(0.04);
  lopt->SetFillColor(0);
  lopt->SetLineColor(0);
  //lopt->Draw();

  //c_opt->Print(Form("c_opt_%s.eps",name.Data()));
}


