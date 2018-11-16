#include "Grid.h"

#ifndef MAZE_H_
#define MAZE_H_

class Maze : public Grid
{
    public: 
        Maze(int x, int y, char* inp) : Grid(x, y, inp) {}
        void generate_next_gen();
        void generate_k_gens(int);
};

#endif
