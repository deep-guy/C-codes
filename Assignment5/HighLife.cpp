#include "HighLife.h"

void HighLife::generate_next_gen()
{
    update_neighborhood();
    Gridcell** gridcells = get_grid();
    int X = get_x();
    int Y = get_y();

    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            if (gridcells[i][j].count_live_neighbors() == 2)
            {
                gridcells[i][j].set_state(gridcells[i][j].get_state());
            }
            else if (gridcells[i][j].get_state() == '0' && (gridcells[i][j].count_live_neighbors() == 3 || gridcells[i][j].count_live_neighbors() == 6))
            {
                gridcells[i][j].set_state('1');
            }
            else
            {
                gridcells[i][j].set_state('0');
            }
        }
    }
    set_gridcells(gridcells);
}