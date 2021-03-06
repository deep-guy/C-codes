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
  std :: string get_name() { return _name ; }
  
private:
  std::string _name ;
} ;

class Person {
public:
  Person(std::string p_name, int p_age):
    _name(p_name),_age(p_age) {}
  Person(int p_age, std::string p_name):_age(p_age),_name(p_name) {} // Works!
  
  ~Person() {}
  friend std::ostream& operator<<(std::ostream &,
				  Person &) ;
  void set_name(std :: string p_name) {
    _name = p_name ; return ; }
  std::string get_name() { return _name ; }
  
private:
  std :: string _name ;
  int _age ;
} ;
 
class Car {
public:
  //Car(std::string b_name, Person &p):
  // _brand(b_name), _driver(p) {}
  Car(Person &p, std::string b_name): _driver(p),_brand(b_name) {}
  //Car(std::string b_name):_driver(_brand.get_name(),26),_brand(b_name) {} // Works!
  Car(std::string d_name):_brand(_driver.get_name()),_driver(d_name,26) {} // Gives segmentation fault.
  ~Car() {}
  friend std::ostream& operator<<(std::ostream &,
				  Car &) ;
private:
  Brand _brand ;
  Person _driver ;
} ;

class Car_mod {
public:
  Car_mod(std :: string b_name, Person *p):
    _brand(b_name), _driver(p) {}
  ~Car_mod() {}
  friend std::ostream& operator<<(std::ostream &,
				  Car_mod &) ;

private:
  Brand _brand ;
  Person *_driver ;
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
      << c._driver // << &(c._driver)
      << std :: endl ;
}

// Car_mod member definitions //
std :: ostream& operator<< (std :: ostream &out,
			    Car_mod &c) {
  out << "Car: " << c._brand << "Driver: "
      << *(c._driver) //<< (c._driver)
      << std :: endl ;
}

int main() {
  Brand l_brand("Hyundai") ;
  std :: cout << l_brand ;
  Person l_person("Jane Doe", 25) ;
  Person l2_person(35, "John Doe") ;

  
  std :: cout << l_person //<< &(l_person)
	      << std :: endl ;
  std :: cout << l2_person // << &(l2_person)
	      << std :: endl ;
  
  //Car l_car1("Toyota", l_person) ;
  Car l_car1(l_person, "Toyota") ;
  std :: cout << l_car1 ;
  Car l_car1test("Maruti") ;
  std :: cout << l_car1test ;
  Car_mod l_car2("Honda", &l_person) ;
  std :: cout << l_car2 ;
  
  l_person.set_name("Jane C. Doe") ;

  std :: cout << std :: endl << "Change in cars:"
	      << std :: endl ;
  std :: cout << l_car1 << l_car2 ;
  std :: cout << l_person //<< &(l_person)
	      << std :: endl ;
  
  return 0 ;
}

  
