#include "Grid.h"

#ifndef HIGHLIFE_H_
#define HIGHLIFE_H_

class HighLife : public Grid
{
    public: 
        HighLife(int x, int y, char* inp) : Grid(x, y, inp) {}
        ~HighLife();
        void generate_next_gen();
        void generate_k_gens(int);
};

#endif