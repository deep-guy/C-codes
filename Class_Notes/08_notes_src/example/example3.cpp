#include "example3.h"

int main() {
  Derived derived ;
  // derived.hello() ; // compiler error since it is a protected function //
  derived.process() ;

  // in case of invoking base.process //
  Base &base = derived ;
  base.process() ;

  return 0 ;
}
