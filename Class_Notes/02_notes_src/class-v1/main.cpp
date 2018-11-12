#include "Matrix.h"
#include <iostream>

int main() {

  Matrix m;
  int r = m.numRows() ;
  int c = m.numCols() ;

  // testing set function
  m.setData(1,1,3) ;

  std :: cout << "Matrix size: " << r << " x " << c
	      << std :: endl ;
  for (int i = 0 ; i < r ; i++)
    for (int j = 0 ; j < c ; j++) {
      std :: cout << "Matrix[" << i << "][" << j << "] = "
		  << m(i,j)
		  << std :: endl ;
    }

  // testing outside-class function
  std :: cout << m ;
  return 0 ; // return success
}
