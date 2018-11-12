#include "four_wheeler.h"

// Vehicle implementation //
Vehicle :: Vehicle() {}

Vehicle :: Vehicle(size_t mass):_mass(mass)  {}

Vehicle :: ~Vehicle() {
  std :: cout << "Vehicle destructor called" << std :: endl << std :: endl ;
}

size_t Vehicle :: mass() const {
  return _mass;
}

void Vehicle :: setMass(size_t new_mass) {
  _mass = new_mass ;
  return ;
}

// Land_derv implementation //

Land_derv :: Land_derv() {}

Land_derv :: Land_derv(size_t mass, size_t speed):Vehicle(mass),_speed(speed)
{}

Land_derv :: ~Land_derv() {
  std :: cout << "Land_derv destructor called" << std :: endl ;
}

size_t Land_derv :: speed() const {
  return _speed;
}

void Land_derv :: setSpeed(size_t new_speed) {
  _speed = new_speed ;
  return ;
}

// Four_wheeler implementation //
Four_wheeler :: Four_wheeler() {}

Four_wheeler :: Four_wheeler(size_t mass, size_t speed, std :: string brand):
  Land_derv(mass,speed),_brand(brand)
{}

Four_wheeler :: ~Four_wheeler() {
  std :: cout << "Four_wheeler destructor called" << std :: endl ;
}

std :: string Four_wheeler :: brand() const {
  return _brand ;
}

void Four_wheeler :: setBrand(std :: string new_brand) {
  _brand = new_brand ;
  return ;
}

