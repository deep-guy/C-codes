#include "Gridcell.h"

#ifndef GRID_H_
#define GRID_H_
class Grid 
{
    protected:
        Gridcell **_gridcells;
        int _X;
        int _Y;

    public: 
        //Constructors
        Grid(int, int, char*);
        Grid(){}
        ~Grid();
        Grid(const Grid&);

        //Setters
        void set_x(int x) {_X = x;}
        void set_y(int y) {_Y = y;}
        void set_gridcells(Gridcell** gcells);

        //Getters
        Gridcell** get_grid() {return _gridcells;}
        int get_x() {return _X;}
        int get_y() {return _Y;}
        Gridcell get_cell(int i, int j) {return _gridcells[i][j];}

        //Overloaded operators
        Gridcell operator()(int i, int j) {return _gridcells[i][j];}
        Grid operator=(const Grid&);

        //Other functions
        void update_neighborhood();        
        void print_grid();
        bool is_valid();
        void output_to_file(int gen_count);
        int calculate_output();
        friend std::ostream& operator << (std::ostream& os, Grid& myGrid);
};
#endif