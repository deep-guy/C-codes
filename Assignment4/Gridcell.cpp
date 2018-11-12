#include "Gridcell.h"
using namespace std;

gridcell::gridcell()
{
    neighborhood = new unsigned char[8];
}

// gridcell::~gridcell()
// {
//     delete[] neighborhood;
// }

gridcell::gridcell(const gridcell& obj)
{
    x = obj.x;
    y = obj.y;
    state = obj.state;
    neighborhood = new unsigned char[8];
    for (int i = 0; i < 8; i++)
    {
        neighborhood[i] = obj.neighborhood[i];
    }
}

int gridcell::get_x()
{
    return x;
}

int gridcell::get_y()
{
    return y;
}

void gridcell::set_state(unsigned char ch)
{
    state = ch;
}

void gridcell::set_x(int X)
{
    x = X;
}

void gridcell::set_y(int Y)
{
    y = Y;
}

void gridcell::set_neighborhood(unsigned char* n_in)
{
    for(int i = 0;i < 8;i++) 
    {
        neighborhood[i] = n_in[i];
    }
}

unsigned char gridcell::get_state()
{
    return state;
}

unsigned char* gridcell::get_neighborhood()
{
    return neighborhood;
}

int gridcell::count_live_neighbors() 
{
    int count = 0;
    for(int i = 0;i < 8;i++) 
    {
        if(neighborhood[i] == '1')
            count++;
    }
    return count;        
} 
