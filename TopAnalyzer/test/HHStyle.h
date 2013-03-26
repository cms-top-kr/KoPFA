#ifndef HHStyle_h
#define HHStyle_h

// ========================================================
//
//  Common style for HH analysis, based on PTDR style
//
//  Change log: 
//  (1) Added standard configuration for text
//  (2) Made fontstyle global variable
//  (3) Unified fontsize for title and axis
//
// ========================================================

#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"

const int fontstyle=42;

void setHHStyle(TStyle& HHStyle)
{
  HHStyle.SetPalette(1);
    
  // ==============
  //  Canvas
  // ==============
	
  HHStyle.SetCanvasBorderMode(0);
  HHStyle.SetCanvasColor(kWhite);
  HHStyle.SetCanvasDefH(600); //Height of canvas
  HHStyle.SetCanvasDefW(600); //Width of canvas
  HHStyle.SetCanvasDefX(0);   //Position on screen
  HHStyle.SetCanvasDefY(0);
	
  // ==============
  //  Pad
  // ==============
	
  HHStyle.SetPadBorderMode(0);
  // HHStyle.SetPadBorderSize(Width_t size = 1);
  HHStyle.SetPadColor(kWhite);
  HHStyle.SetPadGridX(false);
  HHStyle.SetPadGridY(false);
  HHStyle.SetGridColor(0);
  HHStyle.SetGridStyle(3);
  HHStyle.SetGridWidth(1);
	
  // ==============
  //  Frame
  // ==============
	
  HHStyle.SetFrameBorderMode(0);
  HHStyle.SetFrameBorderSize(1);
  HHStyle.SetFrameFillColor(0);
  HHStyle.SetFrameFillStyle(0);
  HHStyle.SetFrameLineColor(1);
  HHStyle.SetFrameLineStyle(1);
  HHStyle.SetFrameLineWidth(1);
	
  // ==============
  //  Histo
  // ==============

  HHStyle.SetErrorX(0.0);
  HHStyle.SetEndErrorSize(8);
	
  // HHStyle.SetHistFillColor(1);
  // HHStyle.SetHistFillStyle(0);
  // HHStyle.SetHistLineColor(1);
  HHStyle.SetHistLineStyle(0);
  HHStyle.SetHistLineWidth(1);
  // HHStyle.SetLegoInnerR(Float_t rad = 0.5);
  // HHStyle.SetNumberContours(Int_t number = 20);

  // HHStyle.SetErrorMarker(20);
	
  HHStyle.SetMarkerStyle(20);
	
  // ==============
  //  Fit/function
  // ==============
	
  HHStyle.SetOptFit(1);
  HHStyle.SetFitFormat("5.4g");
  HHStyle.SetFuncColor(2);
  HHStyle.SetFuncStyle(1);
  HHStyle.SetFuncWidth(1);
	
  // ==============
  //  Date
  // ============== 
	
  HHStyle.SetOptDate(0);
  // HHStyle.SetDateX(Float_t x = 0.01);
  // HHStyle.SetDateY(Float_t y = 0.01);
	
  // =====================
  //  Statistics Box
  // =====================
	
  HHStyle.SetOptFile(0);
  HHStyle.SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  HHStyle.SetStatColor(kWhite);
  HHStyle.SetStatFont(fontstyle);
  HHStyle.SetStatFontSize(0.025);
  HHStyle.SetStatTextColor(1);
  HHStyle.SetStatFormat("6.4g");
  HHStyle.SetStatBorderSize(1);
  HHStyle.SetStatH(0.1);
  HHStyle.SetStatW(0.15);
  // HHStyle.SetStatStyle(Style_t style = 1001);
  // HHStyle.SetStatX(Float_t x = 0);
  // HHStyle.SetStatY(Float_t y = 0);
	
  // ==============
  //  Margins
  // ==============

  HHStyle.SetPadTopMargin(0.1);
  HHStyle.SetPadBottomMargin(0.15);
  HHStyle.SetPadLeftMargin(0.20);
  HHStyle.SetPadRightMargin(0.05);
	
  // ==============
  //  Global Title
  // ==============
	
  HHStyle.SetOptTitle(0);
  HHStyle.SetTitleFont(fontstyle);
  HHStyle.SetTitleColor(1);
  HHStyle.SetTitleTextColor(1);
  HHStyle.SetTitleFillColor(10);
  HHStyle.SetTitleFontSize(0.05);
  // HHStyle.SetTitleH(0); // Set the height of the title box
  // HHStyle.SetTitleW(0); // Set the width of the title box
  // HHStyle.SetTitleX(0); // Set the position of the title box
  // HHStyle.SetTitleY(0.985); // Set the position of the title box
  // HHStyle.SetTitleStyle(Style_t style = 1001);
  // HHStyle.SetTitleBorderSize(2);
	
  // ==============
  //  Axis titles
  // ==============
	
  HHStyle.SetTitleColor(1, "XYZ");
  HHStyle.SetTitleFont(fontstyle, "XYZ");
  HHStyle.SetTitleSize(0.04, "XYZ");
  // HHStyle.SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // HHStyle.SetTitleYSize(Float_t size = 0.02);
  HHStyle.SetTitleXOffset(1.25);
  HHStyle.SetTitleYOffset(1.6);
  // HHStyle.SetTitleOffset(1.1, "Y"); // Another way to set the Offset
	
  // ==============
  //  Axis Label
  // ==============
	
  //HHStyle.SetLabelColor(1, "XYZ");
  HHStyle.SetLabelFont(fontstyle, "XYZ");
  HHStyle.SetLabelOffset(0.007, "XYZ");
  HHStyle.SetLabelSize(0.04, "XYZ");
	
  // ==============
  //  Axis
  // ==============
	
  HHStyle.SetAxisColor(1, "XYZ");
  HHStyle.SetStripDecimals(kTRUE);
  HHStyle.SetTickLength(0.03, "XYZ");
  HHStyle.SetNdivisions(510, "XYZ");
  HHStyle.SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  HHStyle.SetPadTickY(1);
	
  // Change for log plots:
  HHStyle.SetOptLogx(0);
  HHStyle.SetOptLogy(0);
  HHStyle.SetOptLogz(0);
	
  // ==============
  //  Text
  // ==============
	
  HHStyle.SetTextAlign(11);
  HHStyle.SetTextAngle(0);
  HHStyle.SetTextColor(1);
  HHStyle.SetTextFont(fontstyle);
  HHStyle.SetTextSize(0.05);
	
  // =====================
  //  Postscript options:
  // =====================
	
  HHStyle.SetPaperSize(20.,20.);
  // HHStyle.SetLineScalePS(Float_t scale = 3);
  // HHStyle.SetLineStyleString(Int_t i, const char* text);
  // HHStyle.SetHeaderPS(const char* header);
  // HHStyle.SetTitlePS(const char* pstitle);
	
  // HHStyle.SetBarOffset(Float_t baroff = 0.5);
  // HHStyle.SetBarWidth(Float_t barwidth = 0.5);
  // HHStyle.SetPaintTextFormat(const char* format = "g");
  // HHStyle.SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // HHStyle.SetTimeOffset(Double_t toffset);
  // HHStyle.SetHistMinimumZero(kTRUE);
}

#endif
