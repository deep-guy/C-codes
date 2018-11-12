// default_func_parameters.cpp

#include <iostream>

void showints(int a = 0, int b = 1) {
  std :: cout << a << " and " << b << std :: endl ;
  return ;
}

int main() {
  showints(1,0);
  showints();

  return 0 ;
}
