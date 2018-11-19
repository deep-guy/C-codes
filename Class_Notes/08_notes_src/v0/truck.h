#ifndef Truck_h_
#define Truck_h_

#include "four_wheeler.h"

class Truck: public Four_wheeler {
  size_t _mass ;

 public:
  Truck() ;
  Truck(size_t tractor_mass, size_t trailer_mass, size_t speed,
	std :: string brand);
  ~Truck() ;

  size_t mass() const ;
  //virtual size_t mass() const ;
  void setMass(size_t new_tractor_mass,
  	       size_t new_trailer_mass) ;
  void setMass(size_t new_tractor_mass) ;

  Truck const &operator=(Truck const &other) ;
  Truck const &operator=(Vehicle const &other) ;

} ;

inline void Truck :: setMass(size_t new_tractor_mass) {
  std :: cout << "Current mass: " << mass()
	      << " Tractor mass: " << Four_wheeler::mass()
	      << std :: endl ;
  _mass = mass()-Four_wheeler::mass()+new_tractor_mass ;
  std :: cout << "Truck mass changed: new_tractor_mass: " << new_tractor_mass
		<< " total: " << _mass << std :: endl ;
  
  Four_wheeler::setMass(new_tractor_mass) ;
  return ;
}

class MiniTruck: public Truck {
 public:
  MiniTruck() ;
  MiniTruck(size_t tractor_mass, size_t trailer_mass, size_t speed,
	std :: string brand);
  ~MiniTruck() ;

  //size_t mass() const ;
  
} ;


#endif
