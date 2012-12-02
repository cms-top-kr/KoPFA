//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id: RooUnfoldErrors.h 261 2011-01-13 19:00:40Z T.J.Adye $
//
// Description:
//      Graph Drawing Class for use with RooUnfold.
//
// Authors: Tim Adye <T.J.Adye@rl.ac.uk> and Richard Claridge <richard.claridge@stfc.ac.uk>
//
//==============================================================================

#ifndef RooUnfoldErrors_H_
#define RooUnfoldErrors_H_
#include "TNamed.h"
class TH1;
class RooUnfold;
class TNtuple;
#include "TMatrixD.h"

class RooUnfoldErrors : public TNamed {

public:
  
  int toys; // Number of toys 
  RooUnfold* unfold; // Input unfolding object
  const TH1* hTrue;
  RooUnfoldErrors (int NToys,RooUnfold* unfold,const TH1* Truth);
  virtual ~RooUnfoldErrors();
  TNtuple* Chi2(); 

  TH1* RMSResiduals();
  TH1* UnfoldingError();

private:
  void CreatePlots();
  TH1* h_err; // Output plot
  TH1* h_err_res; // Output plot
  TNtuple* hchi2;  // Output plot 
  void GraphParameters(); //
  double xlo; // Minimum x-axis value 
  double xhi; // Maximum x-axis value
  int ntx; // Number of bins in true distribution
  
  
public:

  ClassDef (RooUnfoldErrors, 0)  // Show unfolding errors
};
#endif
