#include "Gridcell.h"
using namespace std;

Gridcell::Gridcell(const Gridcell& obj)
{
    _x = obj._x;
    _y = obj._y;
    _state = obj._state;
    _neighborhood = new unsigned char[8];
    for (int i = 0; i < 8; i++)
    {
        _neighborhood[i] = obj._neighborhood[i];
    }
}

void Gridcell::set_neighborhood(unsigned char* n_in)
{
    for(int i = 0;i < 8;i++) 
    {
        _neighborhood[i] = n_in[i];
    }
}

Gridcell Gridcell::operator = (const Gridcell& obj)
{
    _x = obj._x;
    _y = obj._y;
    _state = obj._state;
    for (int i = 0; i < 8; i++)
    {
        _neighborhood[i] = obj._neighborhood[i];
    }
    return *this;
}

void Gridcell::operator()(int x, int y)
{
    _x = x;
    _y = y;
}


int Gridcell::count_live_neighbors() 
{
    int count = 0;
    for(int i = 0;i < 8;i++) 
    {
        if(_neighborhood[i] == '1')
            count++;
    }
    return count;        
}

std::ostream& operator << (std::ostream& os, Gridcell& cell)
{
    if (cell.get_state() == '0')
    {
        os << "0";
    }
    else if (cell.get_state() == '1')
    {
        os << "+";
    }
    return os;
}
