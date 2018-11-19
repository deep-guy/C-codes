#include "four_wheeler.h"
#include "truck.h"

int main() {
  // construct Truck as an assignment to Vehicle pointer
  Vehicle *vp =  new Truck(2000, 3000, 500, "Ashok Leyland") ;
  std :: cout << std :: endl << "Test function: " << vp-> mass()
	      << std :: endl ;

  // destructor calls
  std :: cin.ignore() ;
  std :: cout << "Calling destructors: " << std :: endl ;
  delete vp ;
  
  return 0 ;
}
