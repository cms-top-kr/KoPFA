void defstyle()
{

    gROOT->SetStyle("Plain");
    //gStyle->SetOptStat(1110);
    gStyle->SetOptStat(0); //remove statistics box
    gStyle->SetOptFit(1);
    gStyle->SetStatW(0.25);
    gStyle->SetStatH(0.15);

    gStyle->SetCanvasDefH(400);
    gStyle->SetCanvasDefW(400);

    gStyle->SetPaintTextFormat("5.3f");

    // For the axis:
    //gStyle->SetAxisColor(1, "XYZ");
    //gStyle->SetStripDecimals(kTRUE);
    //gStyle->SetTickLength(0.03, "XYZ");
    //gStyle->SetNdivisions(510, "XYZ");
    gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    gStyle->SetPadTickY(1);

    // To make 2D contour colorful
    gStyle->SetPalette(1); 

    //gStyle->SetOptTitle(0);
    // Margins:
    gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadLeftMargin(0.16);
    gStyle->SetPadRightMargin(0.05);

    // For the axis titles:
    gStyle->SetTitleColor(1, "XYZ");
    gStyle->SetTitleFont(42, "XYZ");
    gStyle->SetTitleSize(0.06, "XYZ");
    gStyle->SetTitleXOffset(0.9);
    gStyle->SetTitleYOffset(1.4);

    // For the axis labels:
    gStyle->SetLabelColor(1, "XYZ");
    gStyle->SetLabelFont(42, "XYZ");
    gStyle->SetLabelOffset(0.007, "XYZ");
    gStyle->SetLabelSize(0.05, "XYZ");

    // For title
    gStyle->SetTitle(0);
    /*
    gStyle->SetStatFontSize(0.15);
    gStyle->SetLabelSize(0.06,"X");
    gStyle->SetLabelSize(0.06,"Y");
    gStyle->SetLabelFont(72,"xyz");
    gStyle->SetTitleW(0.50);
    gStyle->SetTitleH(0.10);
    gStyle->SetHistLineStyle(1);
    gStyle->SetHistLineWidth(2);
    gStyle->SetMarkerStyle(20);
    gStyle->SetMarkerSize(0.4);
    gStyle->SetPaperSize(15,15);
    */

    gROOT->ForceStyle();
    //TColor *titlecol= (TColor*) (gROOT->GetListOfColors()->At(38));
    //titlecol->SetRGB(64.0/255.0, 94.0/255.0, 206.0/255.0);
};

void setTDRStyle() {

  gROOT->SetStyle("Plain");
// For the canvas:
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(600); //Height of canvas
  gStyle->SetCanvasDefW(600); //Width of canvas
  gStyle->SetCanvasDefX(0);   //POsition on screen
  gStyle->SetCanvasDefY(0);

// For the Pad:
  gStyle->SetPadBorderMode(0);
  //  gStyle->SetPadBorderSize(Width_t size = 1);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);

// For the frame:
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);

// For the histo:
  // gStyle->SetHistFillColor(1);
  // gStyle->SetHistFillStyle(0);
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(1);
  // gStyle->SetLegoInnerR(Float_t rad = 0.5);
  // gStyle->SetNumberContours(Int_t number = 20);

  gStyle->SetEndErrorSize(2);
  //gStyle->SetErrorMarker(20);
  gStyle->SetErrorX(0.);
  
  gStyle->SetMarkerStyle(20);

//For the fit/function:
  gStyle->SetOptFit(1);
  gStyle->SetFitFormat("5.4g");
  gStyle->SetFuncColor(2);
  gStyle->SetFuncStyle(1);
  gStyle->SetFuncWidth(1);

//For the date:
  gStyle->SetOptDate(0);
  // gStyle->SetDateX(Float_t x = 0.01);
  // gStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  gStyle->SetOptFile(0);
  //  gStyle->SetOptStat("mr"); // To display the mean and RMS:   SetOptStat("mr");
  gStyle->SetStatColor(kWhite);
  gStyle->SetStatFont(42);
  gStyle->SetStatFontSize(0.025);
  gStyle->SetStatTextColor(1);
  gStyle->SetStatFormat("6.4g");
  gStyle->SetStatBorderSize(0);
  gStyle->SetStatH(0.1);
  gStyle->SetStatW(0.15);
  // gStyle->SetStatStyle(Style_t style = 1001);
  // gStyle->SetStatX(Float_t x = 0);
  // gStyle->SetStatY(Float_t y = 0);

// Margins:
  gStyle->SetPadTopMargin(0.5);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);

// For the Global title:

//  gStyle->SetOptTitle(0);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFillColor(10);
  gStyle->SetTitleFontSize(0.05);
  // gStyle->SetTitleH(0); // Set the height of the title box
  // gStyle->SetTitleW(0); // Set the width of the title box
  // gStyle->SetTitleX(0); // Set the position of the title box
  // gStyle->SetTitleY(0.985); // Set the position of the title box
  // gStyle->SetTitleStyle(Style_t style = 1001);
  // gStyle->SetTitleBorderSize(2);

// For the axis titles:

  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.06, "XYZ");
  // gStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // gStyle->SetTitleYSize(Float_t size = 0.02);
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYOffset(1.05);
  // gStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");

// For the axis:

  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);

// Change for log plots:
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);

// Postscript options:
  gStyle->SetPaperSize(15.,15.);
  // gStyle->SetLineScalePS(Float_t scale = 3);
  // gStyle->SetLineStyleString(Int_t i, const char* text);
  // gStyle->SetHeaderPS(const char* header);
  // gStyle->SetTitlePS(const char* pstitle);

  // gStyle->SetBarOffset(Float_t baroff = 0.5);
  // gStyle->SetBarWidth(Float_t barwidth = 0.5);
  // gStyle->SetPaintTextFormat(const char* format = "g");
  // gStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // gStyle->SetTimeOffset(Double_t toffset);
  // gStyle->SetHistMinimumZero(kTRUE);
  // gStyle->cd();

}

void tdrGrid(bool gridOn) {
  gStyle->SetPadGridX(gridOn);
  gStyle->SetPadGridY(gridOn);
}

void rootlogon() {

  gROOT->SetStyle("Plain");
  gStyle->SetHistMinimumZero(kTRUE);

  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);

  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleW(1);
  gStyle->SetTitleH(0.07);
  gStyle->SetTitleFontSize(0.1);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleOffset(1.3,"y");

  gStyle->SetStatColor(0);
  gStyle->SetPalette(1);
  //gStyle->SetOptDate(3);
  gStyle->SetOptFit(0111);
  gStyle->SetOptStat(0000000);
  gStyle->SetStat(0);
  //gStyle->SetTextSize(10);

  gSystem->SetAclicMode(TSystem::kOpt);
  gSystem->Load("libPhysics");
  gSystem->Load("libEG");
  gSystem->Load("libPyROOT");
}




void rootlogon() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gSystem->Load("libPhysics");
  gSystem->Load("libEG");
  gStyle->SetHistMinimumZero(kTRUE);
}

void loadFWLite() {
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();
  gSystem->Load("libCintex.so");
  ROOT::Cintex::Cintex::Enable();
}

void initAOD(const char* process) {

  string verticesAod = "recoVertexs_offlinePrimaryVertices__"; 
  verticesAod += process;

  string pfCandidatesAod = "recoPFCandidates_particleFlow__"; 
  pfCandidatesAod += process;

  string ic5GenJetsAod = "recoGenJets_iterativeCone5GenJets__";  
  ic5GenJetsAod += process;

  string pfJetsAod = "recoPFJets_iterativeCone5PFJets__";  
  pfJetsAod += process;

  Events->SetAlias("verticesAod", verticesAod.c_str()); 
  Events->SetAlias("pfCandidatesAod",  pfCandidatesAod.c_str());
  Events->SetAlias("ic5GenJetsAod",  ic5GenJetsAod.c_str());
  Events->SetAlias("pfJetsAod",  pfJetsAod.c_str());

}

void initPF2PAT(const char* process) {


  string met = "recoMETs_pfMET__"; met += process;
  string pu = "recoPileUpPFCandidates_pfPileUp__";  pu+= process;
  string jetsin = "recoPFJets_pfJets__"; jetsin += process;
  string jetsout = "recoPFJets_pfNoTau__"; jetsout += process;
  string taus = "recoPFTaus_allLayer0Taus__"; taus += process;
  string muons = "recoPFCandidates_pfIsolatedMuons__"; muons += process;
  string electrons = "recoPFCandidates_pfIsolatedElectrons__"; electrons += process;
  string pfcandout = "recoPFCandidates_pfNoJet__"; pfcandout += process;  
  string noPileUp = "recoPFCandidates_pfNoPileUp__"; noPileUp += process;  


  string genMetTrue = "recoGenMETs_genMetTrue__";
  genMetTrue += process;
  string decaysFromZs = "recoGenParticles_decaysFromZs__";
  decaysFromZs += process;

  Events->SetAlias("met", met.c_str() );
  Events->SetAlias("pileUp", pu.c_str() );
  Events->SetAlias("jetsAll", jetsin.c_str() );
  Events->SetAlias("jets", jetsout.c_str() );
  Events->SetAlias("taus", taus.c_str());
  Events->SetAlias("muons", muons.c_str());
  Events->SetAlias("electrons", electrons.c_str());
  Events->SetAlias("pfCandOut", pfcandout.c_str());
  Events->SetAlias("noPileUp", noPileUp.c_str());

  Events->SetAlias("genmet",  genMetTrue.c_str());
  Events->SetAlias("decaysFromZs",  decaysFromZs.c_str());
}


void initPAT(const char* process) {
  string taus = "patTaus_selectedPatTausPFlow__"; taus += process;
  string jets = "patJets_selectedPatJetsPFlow__"; jets += process;
  string met = "patMETs_patMETsPFlow__";  met+= process;
  string mus = "patMuons_selectedPatMuonsPFlow__"; mus += process;
  string eles = "patElectrons_selectedPatElectronsPFlow__"; eles += process;
  
  string patCaloJets = "patJets_selectedPatJets__"; patCaloJets += process;

  Events->SetAlias("patTaus", taus.c_str() );
  Events->SetAlias("patJets", jets.c_str() );
  Events->SetAlias("patCaloJets", patCaloJets.c_str() );
  Events->SetAlias("patMet", met.c_str() );
  Events->SetAlias("patMuons", mus.c_str() );
  Events->SetAlias("patElectrons", eles.c_str() );
}

