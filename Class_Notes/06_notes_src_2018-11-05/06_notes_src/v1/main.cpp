//#include <iostream>
//#include <string>
#include "four_wheeler.h"
#include "truck.h"

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

  // construct Truck
  std :: cin.ignore() ;
  Truck t(2000, 3000, 500, "Ashok Leyland") ;
  std :: cout << "Truck: mass: " << t.mass()
	      << " speed: " << t.speed()
	      << " brand: " << t.brand()
	      << " tractor mass: " << t.Four_wheeler::mass()
	      << std :: endl ;

  // change Truck attributes
  std :: cin.ignore() ;
  t.setMass(4000, 200) ;
  t.setSpeed(300) ;
  t.setBrand("Mahindra") ;
  //t.setMass(6000) ; // will give compiler error //
  t.Four_wheeler::setMass(6000) ;
  std :: cout << "Truck changed: mass: " << t.mass()
	      << " speed: " << t.speed()
	      << " brand: " << t.brand()
	      << " tractor mass: " << t.Four_wheeler::mass()
	      << std :: endl ;

  // destructor calls
  std :: cin.ignore() ;
  std :: cout << "Calling destructors: " << std :: endl ;
  return 0 ;
}
