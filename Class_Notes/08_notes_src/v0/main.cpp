//#include <iostream>
//#include <string>
#include "four_wheeler.h"
#include "truck.h"

int main() {
  // construct Truck
  Truck t(2000, 3000, 500, "Ashok Leyland") ;
  
  // assignment to Vehicle pointer
  Vehicle *vp = &t ;
  std :: cout << std :: endl << "Test function-truck: " << vp-> mass()
	      << std :: endl ;

  // construct MiniTruck and assign to Vehicle pointer
  MiniTruck m(1000, 300, 20, "XYZ") ;
  vp = &m ;
  std :: cout << std :: endl << "Test function-minitruck: " << vp-> mass()
	      << std :: endl ;

  
  // construct Four_wheeler and vehicle pointer
  std :: cin.ignore() ;
  Four_wheeler f(3000, 200, "Toyota") ;
  vp = &f ;
  std :: cout << std :: endl << "Test function-fourwheeler: " << vp-> mass()
	      << std :: endl ;

  //std :: cout << "Test speed function: " << vp->speed() << std :: endl ;

  // destructor calls
  std :: cin.ignore() ;
  std :: cout << "Calling destructors: " << std :: endl ;
  return 0 ;
}
