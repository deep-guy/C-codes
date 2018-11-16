#include "Mazectric.h"

void Mazectric::generate_next_gen()
{
    update_neighborhood();
    Gridcell** gridcells = get_grid();
    int X = get_x();
    int Y = get_y();

    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            int ln = gridcells[i][j].count_live_neighbors();
            if (ln == 1 || ln == 2 || ln == 3 || ln == 4)
            {
                gridcells[i][j].set_state(gridcells[i][j].get_state());
            }
            else if (gridcells[i][j].get_state() == '0' && ln == 3)
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