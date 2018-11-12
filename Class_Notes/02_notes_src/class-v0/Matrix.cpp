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
