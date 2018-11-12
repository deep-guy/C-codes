// default_func_parameters_variant1.cpp

#include <iostream>

int a = 1;
int b = 0;
extern void showints(int a = 0,int b = 1) ;

int main() {
  showints(a,b);
  showints();

  return 0 ;
}
