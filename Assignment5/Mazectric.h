#include "Grid.h"

#ifndef MAZECTRIC_H_
#define MAZECTRIC_H_

class Mazectric : public Grid
{
    public: 
        Mazectric(int x, int y, char* inp) : Grid(x, y, inp) {}
        ~Mazectric();
        void generate_next_gen();
        void generate_k_gens(int);
};

#endif