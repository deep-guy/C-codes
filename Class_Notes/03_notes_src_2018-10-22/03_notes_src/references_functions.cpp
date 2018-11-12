#include <iostream>

int int_value = 5 ;
int &ref = int_value ;
int *ptr_int_value = &int_value ;

// int &ref2 ; // This will cause an error.

int int_value2 = 100 ;
int &ref2 = int_value2 ;

// Function types:
// pass by value using pointer
void call_by_value(int *p) {
  *p = 22 ;
  p = NULL ;
  return ;
}

// pass by value using variable
void call_by_value(int p) {
  p = 42 ;
  return ; 
}

// pass by reference
void call_by_reference(int &p) {
  p = 32 ;
  return ;
}

// special pass by value function
void call_by_value_new(int *p) {
  *p = 1000 ; // C-style for pass by reference
  p = NULL ; // pointer does not get updated; only the value gets updated.
  return ;
}

int main() {
  std :: cout << "Integer value: \t\t\t" << int_value << "; " << std :: endl
	      << "Value through reference: \t" << ref << "; " << std :: endl 
	      << "Value through pointer: \t\t" << *ptr_int_value << std :: endl
	      << "Address through int_value: \t" << &int_value << "; " << std :: endl
	      << "Address through reference: \t" << &ref << "; " << std :: endl 
	      << "Address through pointer: \t" << ptr_int_value << std :: endl
	      << std :: endl ;

  // Testing functions:
  std :: cin.ignore() ; // press enter to continue
  call_by_value(ptr_int_value) ;
  std :: cout << "Value (call_by_value(int*)): " << std :: endl 
	      << "Address through pointer: \t" << ptr_int_value << "; " << std :: endl
	      << "Address through reference: \t" << &ref << "; " << std :: endl
	      << "Address through int_value: \t" << &int_value << std :: endl
	      << "Current value: \t\t\t" << int_value << std :: endl << std :: endl ;

  std :: cin.ignore() ; // press enter to continue
  call_by_value(int_value) ;
  std :: cout << "Value (call_by_value(int)): " << std :: endl 
	      << "Address through pointer: \t" << ptr_int_value << "; " << std :: endl  
	      << "Address through reference: \t" << &ref << "; "  << std :: endl 
	      << "Address through int_value: \t" << &int_value << std :: endl
	      << "Current value: \t\t\t" << int_value << std :: endl << std :: endl ;

  std :: cin.ignore() ; // press enter to continue
  call_by_reference(int_value) ;
  std :: cout << "Value (call_by_reference(int&)): " << std :: endl 
	      << "Address through pointer: \t" << ptr_int_value << "; " << std :: endl
	      << "Address through reference: \t" << &ref << "; " << std :: endl 
	      << "Address through int_value: \t" << &int_value << std :: endl
	      << "Current value: \t\t\t" << int_value << std :: endl << std :: endl ;

  std :: cin.ignore() ; // press enter to continue
  call_by_value_new(ptr_int_value) ;
  std :: cout << "Value (call_by_value(int*)): " << std :: endl 
	      << "Address through pointer: \t" << ptr_int_value << "; " << std :: endl
	      << "Address through reference: \t" << &ref << "; " << std :: endl 
	      << "Address through int_value: \t" << &int_value << std :: endl
	      << "Current value: \t\t\t" << int_value << std :: endl << std :: endl ;

  // Address of pointer variable vs address contained in the pointer variable
  std :: cin.ignore() ; // press enter to continue
  std :: cout << "Pointer variable ptr_int_value: \t" << ptr_int_value << "; " << std :: endl
	      << "Its address &ptr_int_value: \t\t" << &ptr_int_value << " ; " << std :: endl
	      << "Its value *ptr_int_value: \t\t" << *ptr_int_value
	      << std :: endl;

  // Pointer reassignment
  std :: cin.ignore() ; // press enter to continue
  //ptr_int_value = NULL ; // this will cause segmentation fault
  ptr_int_value = &ref2 ; // this will work

  std :: cout << "Reassigned pointer variable ptr_int_value: \t" << ptr_int_value << "; " << std :: endl
	      << "Its address &ptr_int_value: \t\t\t" << &ptr_int_value << "; " << std :: endl ;
  std :: cin.ignore() ; // press enter to continue
  std :: cout << "Its value *ptr_int_value: \t\t\t" << *ptr_int_value << std :: endl;

  return 0 ;
}
