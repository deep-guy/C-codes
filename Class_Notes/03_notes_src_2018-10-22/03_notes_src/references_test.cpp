#include <iostream>

int int_value = 5 ;
int &ref = int_value ;
//int &ref2 ; // This will cause an error.

int main() {
  // checking the "alias" property of references
  int_value++ ;
  std :: cout << "After incrementing int_value: " << int_value
	      << " and referenced value: " << ref << " @address "
	      << &ref << std :: endl ;
  ref++ ;
  std :: cout << "After incrementing ref: " << ref << " @address " << &ref 
	      << " and int_value: " << int_value << std :: endl ;
  
  return 0 ;
}




