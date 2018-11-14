// Example for operator overloading for assignment, IO, index and
// binary operators
//
// Modified source code from C++ Annotations by Jaya Sreevalsan Nair
// Oct-23-2017
//


#include "IntArray.h"

IntArray :: IntArray(size_t l_size) : _size(l_size) {
  _data = new int[_size] ;
}

IntArray :: IntArray(IntArray const &other):_size(other._size) {
   _data = new int[_size] ;
  for (int i = 0 ; i < _size ; i++)
    _data[i] = other._data[i] ;
}

IntArray :: ~IntArray() {
  // Note: non-empty destructor -- "new" was to be "delete"d here.
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
  //boundary(index);
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

// Why is she using an ampersand before IntArray here?

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

// IO operator overloading (Friend functions)
std :: ostream& operator<<(std :: ostream &os,
			   IntArray const &current) {
  os << "IntArray size: " << current._size << std :: endl
     << "Values: " ;
  
  for (int i = 0 ; i < current._size ; i++)
    os << current[i] << ", " ;
  os << " end-o-intarray" << std :: endl ;
  return os ;
}

std :: istream& operator>>(std :: istream &is,
			   IntArray &current) {
  int size, value ;
  std :: cout << "Input array size: "
	      << std :: endl ;
  is >> size ;
  std :: cout << "Input " << size << " values:"
	      << std :: endl ;
  if (size != current._size) {
    delete [] current._data ;
    current._size = size ;
    current._data = new int[size] ;
  }
  for (int i = 0 ; i < size ; i++) {
    is >> value ;
    current._data[i] = value ;
  }

  return is ;
}
