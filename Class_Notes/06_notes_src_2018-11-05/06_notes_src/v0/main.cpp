//#include <iostream>
//#include <string>
#include "four_wheeler.h"

int main() {
  // construct vehicle
  Vehicle v(5000) ;
  std :: cout << "Vehicle: mass: " << v.mass() << std :: endl ;

  // change vehicle mass
  std :: cin.ignore() ;
  v.setMass(600) ;
  std :: cout << "Vehicle changed: mass: " << v.mass() << std :: endl ;

  // construct Land_derv
  std :: cin.ignore() ;
  Land_derv l(5000, 300) ;
  std :: cout << "Land_derv: mass: " << l.mass()
	      <<  " speed: " << l.speed() << std :: endl ;

  // change Land_derv mass and speed
  std :: cin.ignore() ;
  l.setMass(2000) ;
  l.setSpeed(200) ;
  std :: cout << "Land_derv changed: mass: " << l.mass()
	      <<  " speed: " << l.speed() << std :: endl ;

  // construct Four_wheeler
  std :: cin.ignore() ;
  Four_wheeler f(3000, 200, "Toyota") ;
  std :: cout << "Four_wheeler: mass: " << f.mass()
	      << " speed: " << f.speed()
	      << " brand: " << f.brand() << std :: endl ;

  // change Four_wheeler attributes
  std :: cin.ignore() ;
  f.setMass(7000) ; f.setSpeed(350) ; f.setBrand("Hyundai") ;
  std :: cout << "Four_wheeler changed: mass: " << f.mass()
	      << " speed: " << f.speed()
	      << " brand: " << f.brand() << std :: endl ;

  // destructor calls
  std :: cin.ignore() ;
  std :: cout << "Calling destructors: " << std :: endl ;
  return 0 ;
}
