#include "Grid.h"

#ifndef MULTIVERSE_H_
#define MULTIVERSE_H_
class multiverse
{
    // Learn to generate a copy constructor
    private:grid** supergrid;
            int NR;
            int NC;
            int R;
            int C;
            // int age;
    public: multiverse(int nr, int nc, int r, int c);
            multiverse(const multiverse& obj);
            void generate_initial_state();
            void set_characters(int nr, int nc, int r, int c);
            // ~multiverse();
            // void copy_to_proxy();
            void update_state();
            void update_neighborhood();
            void generate_next_gen();
            int count_live_cells();
            void synchronize_multiverse(int k);
            void set_grids(grid** sgrid);
            grid** get_supergrid();
            bool is_valid();
            void print_grid_row(int rn);
            void print_multiverse();

};
#endif