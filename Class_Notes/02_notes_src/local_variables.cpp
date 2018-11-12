// local_variables.cpp

#include <iostream>

int main() {
  
  // Instead of defining variable i in the beginning of the function
  // it can be locally defined in-place, as shown here.

  for (int i = 0; i < 20; i++)
    std :: cout << "Printing inside for-loop: " << i << std :: endl ;
  std :: cout << std :: endl ;

  return 0 ;
}
