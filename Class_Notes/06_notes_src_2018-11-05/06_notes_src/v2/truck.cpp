#include "truck.h"


// Truck implementation //
Truck :: Truck() {}

Truck :: Truck(size_t tractor_mass, size_t trailer_mass,
	       size_t speed, std :: string brand):
  Four_wheeler(tractor_mass,speed,brand),_mass(tractor_mass) {
  
  _mass += trailer_mass ;
}

Truck :: ~Truck() {
  std :: cout << "Truck destructor called" << std :: endl ;
}

size_t Truck :: mass() const {
  return _mass ;
}

void Truck :: setMass(size_t new_tractor_mass,
		   size_t new_trailer_mass) {
  _mass = new_tractor_mass+new_trailer_mass ;
  std :: cout << "Truck mass changed: new_tractor_mass: " << new_tractor_mass
	      << " new_trailer_mass: " << new_trailer_mass
	      << " total: " << _mass << std :: endl ;
  Four_wheeler::setMass(new_tractor_mass) ;
  std :: cout << "Check: " << Four_wheeler::mass() << std :: endl ;
  return ;
}

