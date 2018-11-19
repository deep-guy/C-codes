#include "four_wheeler.h"
#include "truck.h"

int main() {
  // construct Truck as an assignment to Vehicle pointer
  Four_wheeler *vp =  new Truck(2000, 3000, 500, "Ashok Leyland") ;
  std :: cout << std :: endl << "Test function: " << vp-> brand()
	      << std :: endl ;

  // destructor calls
  std :: cin.ignore() ;
  std :: cout << "Calling destructors: " << std :: endl ;
  delete vp ;

  return 0 ;
}
