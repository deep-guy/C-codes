// Example for operator overloading for assignment, IO, index and
// binary operators
//
// Modified source code from C++ Annotations by Jaya Sreevalsan Nair
// Oct-24-2018
//


#include "IntArray.h"

int main() {
  IntArray x(20), y(10) ; // 20 ints

  for (int i = 0 ; i < 20 ; i++)
    x[i] = i*2 ;

  // Testing copy constructor
  IntArray z(y) ;
  
  // Testing index operator
  for (int i = 0 ; i < 20 ; i++) 
    std :: cout << "x[" << i << "] = " << x[i] << std :: endl ;
  std :: cout << std :: endl ;

  // Testing assignment operator
  std :: cin.ignore() ;
    std :: cout << "Initial y:" << std :: endl ;
  for (int i = 0 ; i < 10 ; i++) 
    std :: cout << "y[" << i << "] = " << y[i] << std :: endl ;
  std :: cout << std :: endl ;

  std :: cin.ignore() ;
  y = x ;
  std :: cout << "After assignment of x to y:" << std :: endl ;
  for (int i = 0 ; i < 20 ; i++) 
    std :: cout << "y[" << i << "] = " << y[i] << std :: endl ;
  std :: cout << std :: endl ;

  // Testing addition operator
  std :: cin.ignore() ;
  x += y ;
  std :: cout << "Addition of y to x "<< std :: endl ;
  for (int i = 0 ; i < 20 ; i++) 
    std :: cout << "x[" << i << "] = " << x[i] << std :: endl ;
  std :: cout << std :: endl ;

  std :: cin.ignore() ;
  x += z ;

  // Testing ostream operator
  std :: cin.ignore() ;
  std :: cout << "OStream" << std :: endl ;
  std :: cout << x << std :: endl << y ;

  // Testing istream operator
  std :: cin.ignore() ;
  IntArray w(5) ;
  
  std :: cin >> w ;
  
  std :: cout << "Checking entries: " << std :: endl
	      << w << std :: endl ;
  return 0 ;    
}
