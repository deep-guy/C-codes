#include "Matrix.h"

// Implementation of Matrix Class

// Public member functions //
Matrix::Matrix(): _numRows(2), _numCols(2) {
  _data = new float*[_numRows] ;
  for (int i = 0 ; i < _numRows ; i++) {
    _data[i] = new float[_numCols] ;

    // data initialization
    for (int j = 0 ; j < _numCols ; j++) 
      _data[i][j] = 0 ;
    }
}

Matrix::~Matrix() {
  for (int i = 0 ; i < _numRows ; i++)
    delete[] _data[i] ;
  delete[] _data ;
  _numRows = 0 ; _numCols = 0 ;
}

Matrix::Matrix(const Matrix& m) :
  _numRows(m._numRows), _numCols(m._numCols){
  _data = new float*[_numRows] ;
  for (int i = 0 ; i < _numRows ; i++) 
    _data[i] = new float[_numCols] ;
    
  for (int i = 0; i < _numRows; i++) 
        for (int j = 0; j < _numCols; j++) 
	  _data[i][j] = m._data[i][j];
        
}

// set functions //
void Matrix::setData(int r, int c, float f) {
  _data[r][c] = f ;
  return ;
}

// Functions (outside the class //
std::ostream& operator<<(std::ostream& os, Matrix& m) {

  int nr = m.numRows() ;
  int nc = m.numCols() ;
  
  for (int i = 0; i < nr; i++) {
    for (int j = 0; j < nc; j++) 
      os << m(i,j) << " " ;
    
    os << std::endl;
  }
  return os;
}
