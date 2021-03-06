#ifndef Four_wheeler_h_
#define Four_wheeler_h_

#include <iostream>
#include <string>

class Vehicle {
  size_t _mass ;
  
 public:
  Vehicle() ;
 Vehicle(size_t mass);
 ~Vehicle() ;
 //virtual ~Vehicle() ;
 
  size_t mass() const ;
  //virtual size_t mass() const ;
  void setMass(size_t new_mass) ;
} ;


class Land_derv: public Vehicle {
  size_t _speed ;
  // Redefinable interface
  virtual std::string v_brand(void) const = 0 ;
  
 public:
  Land_derv() ;
  Land_derv(size_t mass, size_t speed) ;
  ~Land_derv() ;

  size_t speed() const ;
  void setSpeed(size_t new_speed) ;
} ;

class Four_wheeler: public Land_derv {
  std :: string _brand ;
  std :: string v_brand(void) const ;
  
 public:
  Four_wheeler() ;
  Four_wheeler(size_t mass, size_t speed, std :: string brand) ;
  ~Four_wheeler() ;

  std :: string brand() const ;
  void setBrand(std :: string new_brand) ;
} ;

#endif
