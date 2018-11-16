#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <sstream>
#include <fstream>
#include <string>
#ifndef GRIDCELL_H_
#define GRIDCELL_H_
class Gridcell {
    private:
        int _x; 
        int _y;
        unsigned char _state;
        unsigned char* _neighborhood;
    public:
        //Constructors 
        Gridcell(void) {_neighborhood = new unsigned char[8];} 
        ~Gridcell() {delete[] _neighborhood;}
        Gridcell(const Gridcell& obj);

        //Getters
        unsigned char get_state() {return _state;} 
        int get_x() {return _x;}
        int get_y() {return _y;}
        unsigned char* get_neighborhood() {return _neighborhood;}

        //Setters
        void set_state(unsigned char ch) {_state = ch;}
        void set_x(int X) {_x = X;}
        void set_y(int Y) {_y = Y;}
        void set_neighborhood(unsigned char*);
        void operator() (int x, int y);

        //Overloaded assignment
        Gridcell operator = (const Gridcell&);

        //Other functions
        int count_live_neighbors();  
        friend std::ostream& operator << (std::ostream& os, Gridcell& cell);

};
#endif