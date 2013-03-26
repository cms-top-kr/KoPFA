//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id: RooUnfoldSvd.cxx 261 2011-01-13 19:00:40Z T.J.Adye $
//
// Description:
//      SVD unfolding. Just an interface to TSVDUnfold.
//
// Author: Tim Adye <T.J.Adye@rl.ac.uk>
//
//==============================================================================

//____________________________________________________________
/* BEGIN_HTML
<p>Links to TSVDUnfold class which unfolds using Singular Value Decomposition (SVD).</p>
<p>Regularisation parameter defines the level at which values are deemed to be due to statistical fluctuations and are cut out. (Default= number of bins/2)
<p>Returns errors as a full matrix of covariances
<p>Error processing is much the same as with the kCovToy setting with 1000 toys. This is quite slow but can be switched off.
<p>Can only handle 1 dimensional distributions
<p>True and measured distributions must have the same binning
<p>Can account for both smearing and biasing
<p>Returns near singular covariance matrices, again leading to very large chi squared values
END_HTML */

/////////////////////////////////////////////////////////////

#include "RooUnfoldSvd.h"

#include <iostream>
#include <iomanip>

#include "TNamed.h"
#include "TH1.h"
#include "TH2.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TSVDUnfold.h"

#include "RooUnfoldResponse.h"

using std::cout;
using std::cerr;
using std::endl;

ClassImp (RooUnfoldSvd);

RooUnfoldSvd::RooUnfoldSvd (const RooUnfoldSvd& rhs)
  : RooUnfold (rhs)
{
  // Copy constructor.
  Init();
  CopyData (rhs);
}

RooUnfoldSvd::RooUnfoldSvd (const RooUnfoldResponse* res, const TH1* meas, Int_t kreg, Int_t ntoyssvd,
                            const char* name, const char* title)
  : RooUnfold (res, meas, name, title), _kreg(kreg ? kreg : meas->GetNbinsX()/2), _ntoyssvd(ntoyssvd)
{
  // Constructor with response matrix object and measured unfolding input histogram.
  // The regularisation parameter is kreg.
  Init();
}

RooUnfoldSvd*
RooUnfoldSvd::Clone (const char* newname) const
{
  RooUnfoldSvd* unfold= new RooUnfoldSvd(*this);
  if (newname && strlen(newname)) unfold->SetName(newname);
  return unfold;
}

void
RooUnfoldSvd::Reset()
{
  Destroy();
  Init();
  RooUnfold::Reset();
}

void
RooUnfoldSvd::Destroy()
{
  delete _svd;
  delete _meas1d;
  delete _train1d;
  delete _truth1d;
  delete _reshist;
}

void
RooUnfoldSvd::Init()
{
  _svd= 0;
  _meas1d= _train1d= _truth1d= 0;
  _reshist= 0;
  GetSettings();
}

void
RooUnfoldSvd::Assign (const RooUnfoldSvd& rhs)
{
  RooUnfold::Assign (rhs);
  CopyData (rhs);
}

void
RooUnfoldSvd::CopyData (const RooUnfoldSvd& rhs)
{
  _kreg= rhs._kreg;
  _ntoyssvd= rhs._ntoyssvd;
}

TSVDUnfold*
RooUnfoldSvd::Impl()
{
  return _svd;
}

void
RooUnfoldSvd::Unfold()
{
  if (_res->GetDimensionTruth() != 1 || _res->GetDimensionMeasured() != 1) {
    cerr << "RooUnfoldSvd may not work very well for multi-dimensional distributions" << endl;
  }
  if (_nt != _nm) {
    cerr << "RooUnfoldSvd requires the same number of bins in the truth and measured distributions" << endl;
    return;
  }
  if (_kreg < 0) {
    cerr << "RooUnfoldSvd invalid kreg: " << _kreg << endl;
    return;
  }
  Int_t nb= _nm < _nt ? _nm : _nt;
  if (_kreg > nb) {
    cerr << "RooUnfoldSvd invalid kreg=" << _kreg << " with " << nb << " bins" << endl;
    return;
  }

  Bool_t oldstat= TH1::AddDirectoryStatus();
  TH1::AddDirectory (kFALSE);
  _meas1d=  HistNoOverflow (_meas,             _overflow);
  _train1d= HistNoOverflow (_res->Hmeasured(), _overflow);
  _truth1d= HistNoOverflow (_res->Htruth(),    _overflow);
  _reshist= _res->HresponseNoOverflow();

  if (_verbose>=1) cout << "SVD init " << _reshist->GetNbinsX() << " x " << _reshist->GetNbinsY()
                        << " bins, kreg=" << _kreg << endl;
  _svd= new TSVDUnfold (_meas1d, _train1d, _truth1d, _reshist);

  TH1D* rechist= _svd->Unfold (_kreg);

  _rec.ResizeTo (_nt);
  for (Int_t i= 0; i<_nt; i++) {
    _rec[i]= rechist->GetBinContent(i+1);
  }

  delete rechist;
  TH1::AddDirectory (oldstat);

  _unfolded= true;
  _haveCov=  false;
}

void
RooUnfoldSvd::GetCov()
{
  Bool_t oldstat= TH1::AddDirectoryStatus();
  TH1::AddDirectory (kFALSE);
  TH2D* meascov= new TH2D ("meascov", "meascov", _nm, 0.0, 1.0, _nm, 0.0, 1.0);
  Int_t first= _overflow ? 0 : 1;
  for (Int_t i= 0; i<_nm; i++) {
    Double_t err= _meas->GetBinError(i+first);
    meascov->SetBinContent (i+1, i+1, err*err);
  }

  //Get the covariance matrix for statistical uncertainties on the measured distribution
  TH2D* unfoldedCov= _svd->GetUnfoldCovMatrix (meascov, _ntoyssvd);
  //Get the covariance matrix for statistical uncertainties on the response matrix
  TH2D* adetCov=     _svd->GetAdetCovMatrix   (_ntoyssvd);

  _cov.ResizeTo (_nt, _nt);
  for (Int_t i= 0; i<_nt; i++) {
    for (Int_t j= 0; j<_nt; j++) {
      _cov(i,j)= unfoldedCov->GetBinContent(i+1,j+1) + adetCov->GetBinContent(i+1,j+1);
    }
  }

  delete adetCov;
  delete unfoldedCov;
  delete meascov;
  TH1::AddDirectory (oldstat);

  _haveCov= true;
}

void
RooUnfoldSvd::GetSettings(){
    _minparm=0;
    _maxparm=_meas->GetNbinsX();
    _stepsizeparm=1;
    _defaultparm=_meas->GetNbinsX()/2;
}
