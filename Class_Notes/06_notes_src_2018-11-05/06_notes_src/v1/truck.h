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
  void setMass(size_t new_tractor_mass,
	       size_t new_trailer_mass) ;
} ;



#endif
