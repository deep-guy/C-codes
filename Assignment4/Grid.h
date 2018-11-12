#include "Gridcell.h"


#ifndef GRID_H_
#define GRID_H_
class grid 
{
    private:gridcell **gridcells;
            // gridcell ** proxy;
            int X;
            int Y;
            unsigned char state;
            unsigned char* neighborhood;
    public: grid(int x, int y);
            grid();
            // ~grid();
            grid(const grid& obj);
            void set_x(int x);
            void set_y(int x);
            void initialize_gridcells();
            void generate_initial_state(bool isAlive);
            void generate_next_gen();
            int count_live_neighbors();
            gridcell** get_grid();
            void set_gridcells(gridcell** gcells);
            // void copy_to_proxy();
            void update_neighborhood();
            void set_neighborhood(int k, unsigned char n);
            bool is_live();
            void generate_k_generations(int k);
            void set_state(unsigned char ch);
            unsigned char get_state();
            bool is_valid();
            void kill_grid();
            void revive_grid();
            void print_grid();
            void print_row(int row_num);
            unsigned char* get_neighborhood();
            int calculate_output();
            gridcell get_cell(int i, int j);
            friend std::ostream& operator << (std::ostream& os, grid& myGrid);
};
#endif