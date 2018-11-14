// Example for operator overloading for assignment, IO, index and
// binary operators
//
// Modified source code from C++ Annotations by Jaya Sreevalsan Nair
// Oct-23-2017
//

#ifndef IntArray_H_
#define IntArray_H_

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

    // IO operator overloading //
    friend std :: ostream& operator<<
        (std :: ostream &os, IntArray const &current) ;
    friend std :: istream& operator>>
        (std :: istream &is, IntArray  &current) ;
    
    private:
    int *_data ;
    size_t _size ;

    void boundary(size_t index) const ;
    int &operatorIndex(size_t index) const;
} ;

#endif
