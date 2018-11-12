// Example for operator overloading for assignment, index and binary operators
//
// Modified source code from C++ Annotations by Jaya Sreevalsan Nair
// Oct-24-2018 
//


#include <iostream>
#include <sstream>

class IntArray {
public:
  IntArray(size_t size = 1) ;
  IntArray(IntArray const &other) ;
  ~IntArray() ;
  
  // operator overloading //
  IntArray const &operator=(IntArray const &other) ;
  int &operator[] (size_t index) ; // for non-const objects
  int const &operator[](size_t index) const ; // for const objects
  IntArray &operator+=(IntArray const &rhs) ;
  
private:
  int *_data ;
  size_t _size ;

  void boundary(size_t index) const ;
  int &operatorIndex(size_t index) const;
} ;
//===
IntArray :: IntArray(size_t l_size) : _size(l_size) {
  _data = new int[_size] ;
}

IntArray :: IntArray(IntArray const &other):_size(other._size) {
   _data = new int[_size] ;
  for (int i = 0 ; i < _size ; i++)
    _data[i] = other._data[i] ;
}

IntArray :: ~IntArray() {
  // Note: non-empty destructor -- "new" has to be "delete"d here.
  delete [] _data ;
}

// private members //
void IntArray::boundary(size_t index) const {
  if (index < _size) return ;

  std :: ostringstream out ;
  out << "IntArray:: boundary overflow, index = " << index
      << ", should be < " << _size << std :: endl ;
  throw out.str() ;
  
}

int &IntArray::operatorIndex(size_t index) const {
  boundary(index);
  return _data[index];
}

// operator overloading //
IntArray const &IntArray::operator=(IntArray const &other) {
  delete [] _data ;

  _size = other._size ;
  _data = new int[_size] ;
  for (int i = 0 ; i < _size ; i++)
    _data[i] = other._data[i] ;

  return (*this) ;
}

int &IntArray::operator[](size_t index) {
  //std :: cout << "calling non-const index op" << std :: endl ;
  return operatorIndex(index);
}

int const &IntArray::operator[](size_t index) const {
  //std :: cout << "calling const index op" << std :: endl ;
  return operatorIndex(index); 
}

IntArray &IntArray::operator+=(IntArray const &rhs) {
  if (rhs._size != _size) {
    std :: cerr << "Size mismatch -- addition not done" << std :: endl;
    return *this ;
  }
  for (int i = 0 ; i < _size ; i++)
    (*this)[i] += rhs[i] ;
  return *this ;  
}


int main() {
  IntArray x(20), y(10) ; // 20 ints

  for (int i = 0 ; i < 20 ; i++)
    x[i] = i*2 ;

  // Testing copy constructor
  IntArray z(y) ;
  for (int i = 0 ; i < 10 ; i++) 
    std :: cout << "z[" << i << "] = " << z[i] << std :: endl ;
  std :: cout << std :: endl ;
  
  // Testing index operator
  for (int i = 0 ; i < 20 ; i++) 
    std :: cout << "x[" << i << "] = " << x[i] << std :: endl ;
  std :: cout << std :: endl ;
  
  // Testing assignment operator
  std :: cin.ignore() ;
    std :: cout << "Before assignment of x to y:" << std :: endl ;
  for (int i = 0 ; i < 10 ; i++) 
    std :: cout << "y[" << i << "] = " << y[i] << std :: endl ;
  std :: cout << std :: endl ;

  std :: cin.ignore() ;
  y = x ;
  std :: cout << "After assignment of x to y:" << std :: endl ;
  for (int i = 0 ; i < 20 ; i++) 
    std :: cout << "y[" << i << "] = " << y[i] << std :: endl ;
  std :: cout << std :: endl ;
  
  // Testing addition operator
  std :: cin.ignore() ;
  x += y ;
  std :: cout << "Sum of x and y: "<< std :: endl ;
  for (int i = 0 ; i < 20 ; i++) 
    std :: cout << "x[" << i << "] = " << x[i] << std :: endl ;
  std :: cout << std :: endl ;
  
  std :: cin.ignore() ;
  std :: cout << "Sum of x and z:" << std :: endl ;
  x += z ;
  std :: cout << std :: endl ;

  return 0 ;    
}
