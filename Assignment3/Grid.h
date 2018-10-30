#include "Gridcell.h"
#include <iostream>

#ifndef GRID_H_
#define GRID_H_
class grid 
{
    private:gridcell **gridcells;
            int X;
            int Y;
    public: grid(int x, int y);
            ~grid();
            void generate_initial_state(int L);
            void update_neighborhood();
            void print_grid();
            int calculate_output();
            gridcell get_cell(int i, int j);
            friend std::ostream& operator << (std::ostream& os, grid& myGrid);
};
#endif