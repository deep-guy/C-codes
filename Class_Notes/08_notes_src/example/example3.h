#ifndef Example_H_
#define Example_H_

#include <iostream>

class Base {
 public: 
  void process() { hello() ; return ; }
 protected:
  virtual void hello() { std :: cout << "base hello" << std :: endl ; return ; }
} ;

class Derived : public Base {
 protected:
  void hello() { std :: cout << "derived hello" << std :: endl ; return ; }
} ;

#endif
