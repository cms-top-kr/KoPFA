//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id: Array2D.h 248 2010-10-04 22:18:19Z T.J.Adye $
//
// Description:
//      A helper class designed to store an 2 dimensional array as a 1-D array.
//
// Authors: Fergus Wilson <fwilson@slac.stanford.edu> and Tim Adye <T.J.Adye@rl.ac.uk>
//
//==============================================================================

#ifndef ARRAY2D_HH
#define ARRAY2D_HH

#include "TObject.h"

class Array2D : public TObject {
private:
  Int_t _dataSize; // number of elements in 1-D array (same as _nRows*_nCols)
  Double_t *_data; //[_dataSize] array to store elements
  Int_t _nRows; // number of rows in 2-D matrix
  Int_t _nCols; // number of columns in 2-D matrix
  Int_t Map(Int_t R, Int_t C) const; // return index of element in row R, column C
  Bool_t ValidRC(Int_t R, Int_t C) const; // return true if row R, column C is valid element

public:
  Array2D(); // default constructor
  Array2D(Int_t R, Int_t C, Double_t initval=0.0); // construct matrix with R rows, C columns
  Array2D(const Array2D& rhs); // copy operator
  Array2D& operator=(const Array2D& rhs); // assignment operator
  Bool_t operator==(const Array2D& rhs); // comparison operator
  ~Array2D();
  Bool_t Set(Int_t R, Int_t C, Double_t value); // set row R, column C to value
  Bool_t Add(Int_t R, Int_t C, Double_t value); // add value to contents of row R, column C
  Double_t Get(Int_t R, Int_t C) const;  // access the element in row R, column C
  inline Int_t GetNrows() const { return(_nRows);}  // return number of rows
  inline Int_t GetNcols() const { return(_nCols);} // return number of columns

  ClassDef(Array2D,1) // Store a 2-D matrix as a 1-D array
};

#endif
