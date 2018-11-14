#include "Gridcell.h"


#ifndef GRID_H_
#define GRID_H_
class Grid 
{
    private:
        Gridcell **_gridcells;
        int _X;
        int _Y;

    public: 
        //Constructors
        Grid(int, int);
        Grid(){}
        ~Grid();
        Grid(const Grid&);

        //Setters
        void set_x(int x) {_X = x;}
        void set_y(int y) {_Y = y;}
        void set_gridcells(Gridcell** gcells);

        //Getters
        Gridcell** get_grid() {return _gridcells;}
        Gridcell get_cell(int i, int j) {return _gridcells[i][j];}

        //Overloaded operators
        Gridcell operator()(int i, int j) {return _gridcells[i][j];}
        Grid operator=(const Grid&);

        //Other functions
        void initialize_gridcells();
        void update_neighborhood();
        void generate_next_gen();        
        void print_grid();
        int calculate_output();
        friend std::ostream& operator << (std::ostream& os, Grid& myGrid);
};
#endif