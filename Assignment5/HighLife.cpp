#include "HighLife.h"

void HighLife::generate_next_gen()
{
    update_neighborhood();

    for (int i = 0; i < _X; i++)
    {
        for (int j = 0; j < _Y; j++)
        {
            int ln = _gridcells[i][j].count_live_neighbors();
            if (ln == 2 || ln == 3)
            {
                _gridcells[i][j].set_state(_gridcells[i][j].get_state());
            }
            else if (_gridcells[i][j].get_state() == '0' && (ln == 3 || ln == 6))
            {
                _gridcells[i][j].set_state('1');
            }
            else
            {
                _gridcells[i][j].set_state('0');
            }
        }
    }
    update_neighborhood();
}

HighLife::~HighLife()
{
    int i = 0;
    for (i = 0; i < _X; i++)
    {
        delete[] _gridcells[i];
    }
    delete[] _gridcells;
}

void HighLife::generate_k_gens(int k)
{
    for (int i = 0; i < k; i++)
    {
        HighLife temp = *this;
        temp.generate_next_gen();
        if (temp.is_valid())
        {
            *this = temp;
            // std::cout << "I made it!!" << std::endl;
        }
    }
}