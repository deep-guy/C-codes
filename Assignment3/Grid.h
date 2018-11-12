#include "Gridcell.h"
#include <iostream>

#ifndef GRID_H_
#define GRID_H_
class grid 
{
    private:gridcell **gridcells;
            gridcell ** proxy;
            int X;
            int Y;
            // int R;
            // int C;
    public: grid(int x, int y);
            ~grid();
            void generate_initial_state();
            void generate_next_gen();
            void update_neighborhood();
            void output_to_file(int generations);
            void set_gridcell_state(int i, int j, unsigned char state);
            bool is_valid();
            void print_grid();
            void copy_to_proxy();
            int calculate_output();
            gridcell get_cell(int i, int j);
            friend std::ostream& operator << (std::ostream& os, grid& myGrid);
};
#endif