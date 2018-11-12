#ifndef Matrix_H_
#define Matrix_H_

class Matrix{
  // Class interface for a _numRowsx_numCols matrix
 public:
  Matrix() ; // constructor //
  ~Matrix() ; // destructor //
  Matrix(const Matrix&) ; // copy constructor //

  // get functions //
  int numRows() { return _numRows ; }
  int numCols() { return _numCols ; }
  int data(int r, int c) { return _data[r][c] ; }
  
 protected:
  
 private:
  // Data members //
  float **_data ;
  int _numRows, _numCols ;
} ;
#endif
