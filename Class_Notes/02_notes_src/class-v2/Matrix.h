#ifndef Matrix_H_
#define Matrix_H_

#include <iostream>

class Matrix{
  // Class interface for a _numRowsx_numCols matrix
 public:
  Matrix() ; // constructor //
  ~Matrix() ; // destructor //
  Matrix(const Matrix&) ; // copy constructor //

  // friend functions //
  friend std::ostream& operator<< (std::ostream &, Matrix &) ;

  // get functions //
  int numRows() { return _numRows ; }
  int numCols() { return _numCols ; }
  float data(int r, int c) { return _data[r][c] ; }
  float& operator()(int r, int c) { return _data[r][c] ; }

  // set functions //
  void setData(int r, int c, float f) ;
 protected:
  
 private:
  // Data members //
  float **_data ;
  int _numRows, _numCols ;
} ;


#endif
