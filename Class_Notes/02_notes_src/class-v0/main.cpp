#include "Matrix.h"
#include <iostream>

int main() {

  Matrix m;
  int r = m.numRows() ;
  int c = m.numCols() ;

  std :: cout << "Matrix size: " << r << " x " << c
	      << std :: endl ;
  for (int i = 0 ; i < r ; i++)
    for (int j = 0 ; j < c ; j++) {
      std :: cout << "Matrix[" << i << "][" << j << "] = "
	<< m.data(i,j)
	//<< m._data[i][j]
		  << std :: endl ;
    }
  return 0 ; // return success
}
