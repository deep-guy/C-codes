#include <iostream>
#include <string>

class Brand {
public:
  Brand(std :: string b_name):_name(b_name) {}
  ~Brand() {}
  friend std::ostream& operator<<(std :: ostream &,
				  Brand &) ;
  void set_name(std :: string b_name) {
    _name = b_name ; return ; }
  
private:
  std::string _name ;
} ;

class Person {
public:
  Person(std::string p_name, int p_age):
    _name(p_name),_age(p_age) {}
  ~Person() {}
  friend std::ostream& operator<<(std::ostream &,
				  Person &) ;
  void set_name(std :: string p_name) {
    _name = p_name ; return ; }
  
private:
  std :: string _name ;
  int _age ;
} ;
 
class Car {
public:
  Car(std::string b_name, Person &p):
    _brand(b_name), _driver(p) {} 
  ~Car() {}
  friend std::ostream& operator<<(std::ostream &,
				  Car &) ;
private:
  Brand _brand ;
  Person _driver ;
} ;
  
// Brand member definitions //
std :: ostream& operator<< (std :: ostream &out,
			    Brand &b) {
  out << "Brand Name: " << b._name << std :: endl ;
}

// Person member definitions //
std :: ostream& operator<< (std :: ostream &out,
			    Person &p) {
  out << p._name << " of age " << p._age
      << std :: endl ;
}

// Car member definitions //
std :: ostream& operator<< (std :: ostream &out,
			    Car &c) {
  out << "Car: " << c._brand << "Driver: "
      << c._driver << &(c._driver)
      << std :: endl ;
}

int main() {
  Brand l_brand("Hyundai") ;
  std :: cout << l_brand ;
  Person l_person("Jane Doe", 25) ;
  std :: cout << l_person << &(l_person)
	      << std :: endl ;
  
  Car l_car1("Toyota", l_person) ;
  std :: cout << l_car1 ;
  l_person.set_name("Jane C. Doe") ;

  std :: cout << std :: endl << "Change in car:"
	      << std :: endl ;
  std :: cout << l_car1 ;
  std :: cout << l_person << &(l_person)
	      << std :: endl ;
  
  return 0 ;
}

  
