#include "Multiverse.h"
using namespace std;

multiverse::multiverse(int nr, int nc, int r, int c)                                
{
    // cout << "In Multiverse constructor" << endl;
    // cout << nr << "++++++" << endl;
    // cout << nc << "++++++" << endl;
    // cout << r << "=====" << endl;
    // cout << c << "=====" << endl;
    NR = nr;
    NC = nc;
    R = r;
    C = c;
    supergrid = new grid*[nr];
    for (int i = 0; i < nr; i++)
    {
        supergrid[i] = new grid[nc];
    }

    for (int i = 0; i < NR; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            supergrid[i][j].set_x(R);
            supergrid[i][j].set_y(C);
            supergrid[i][j].set_state('0');
            supergrid[i][j].initialize_gridcells();
            // cout << "this code has executed" << endl;
            for (int ct = 0; ct < 8; ct++)
            {
                supergrid[i][j].set_neighborhood(ct, '0');
            }
        }
    }
}

multiverse::multiverse(const multiverse& obj)
{
    NR = obj.NR;
    NC = obj.NC;
    R = obj.R;
    C = obj.C;
    // age = obj.age;
    // gen_count = obj.gen_count;

    supergrid = new grid*[NR];
    for (int i = 0; i < NR; i++)
    {
        supergrid[i] = new grid[NC];
    }

    for (int i = 0; i < NR; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            supergrid[i][j] = *(new grid(R, C));
            supergrid[i][j] = obj.supergrid[i][j];
        }
    }
}

void multiverse::generate_initial_state()
{
    // cout << "In multiverse gen initial state" << endl;
    int i, j;
    for (i = 0; i < NC; i++)
    {
        // supergrid[0][i]
        supergrid[0][i].generate_initial_state(false);
        supergrid[NR-1][i].generate_initial_state(false);
    }
    for (i = 0; i < NR; i++)
    {
        supergrid[i][0].generate_initial_state(false);
        supergrid[i][NC-1].generate_initial_state(false);
    }

    for (i = 1; i < NR-1; i++)
    {
        if (i % 2 == 0)
        {
            for (j = 1; j < NC-1; j++)
            {
                if (j % 2 == 1)
                    supergrid[i][j].generate_initial_state(false);
                else
                    supergrid[i][j].generate_initial_state(true);
            }
        }
        else
        {
            for (j = 1; j < NC-1; j++)
            {
                if (j % 2 == 1)
                    supergrid[i][j].generate_initial_state(true);
                else
                    supergrid[i][j].generate_initial_state(false);
            }
        }
    }
    // cout<< count_live_cells()<< "=======" << endl;
}

int multiverse::count_live_cells()
{
    int count = 0;
    for (int i = 0; i < NR; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            count += supergrid[i][j].calculate_output();
        }
    }
    return count;
}

void multiverse::update_neighborhood() 
{

    // cout << "In multiverse update neighborhood" << endl;
    // int i, j;
    // unsigned char state;
    // for (i = 1; i < NR-1; i++)
    // {
    //     for (j = 1; j < NC-1; j++)
    //     {
    //         state = supergrid[i][j].get_state();
    //         supergrid[i-1][j].set_neighborhood(0, state);
    //         supergrid[i-1][j+1].set_neighborhood(1, state);
    //         supergrid[i][j+1].set_neighborhood(2, state);
    //         supergrid[i+1][j+1].set_neighborhood(3, state);
    //         supergrid[i+1][j].set_neighborhood(4, state);
    //         supergrid[i+1][j-1].set_neighborhood(5, state);
    //         supergrid[i][j-1].set_neighborhood(6, state);
    //         supergrid[i-1][j-1].set_neighborhood(7, state);
    //     }
    // }

    for (int i = 0; i < NR; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            if ((j+1) > 0 && (j+1) < NC)
            {
                supergrid[i][j].set_neighborhood(0, supergrid[i][j+1].get_state());
            }
            else 
            {
                supergrid[i][j].set_neighborhood(0, '0');
            }
            if ((j+1) > 0 && (j+1) < NC && (i-1) >= 0 && (i-1) < NR)
            {
                supergrid[i][j].set_neighborhood(1, supergrid[i-1][j+1].get_state());
            }
            else 
            {
                supergrid[i][j].set_neighborhood(1, '0');
            }
            if ((i-1) >= 0 && (i-1) < NR) 
            {
                supergrid[i][j].set_neighborhood(2, supergrid[i-1][j].get_state());
            }
            else 
            {
                supergrid[i][j].set_neighborhood(2, '0');
            }
            if ((j-1) >= 0 && (j-1) < NC && (i-1) >= 0 && (i-1) < NR) 
            {
                supergrid[i][j].set_neighborhood(3, supergrid[i-1][j-1].get_state());
            }
            else 
            {
                supergrid[i][j].set_neighborhood(3, '0');
            }
            if ((j-1) >= 0 && (j-1) < NC) 
            {
                supergrid[i][j].set_neighborhood(4, supergrid[i][j-1].get_state());
            }
            else 
            {
                supergrid[i][j].set_neighborhood(4, '0');
            }
            if ((j-1) >= 0 && (j-1) < NC && (i+1) > 0 && (i+1) < NR) 
            {
                supergrid[i][j].set_neighborhood(5, supergrid[i+1][j-1].get_state());
            }
            else 
            {
                supergrid[i][j].set_neighborhood(5, '0');
            }
            if ((i+1) > 0 && (i+1) < NR) 
            {
                supergrid[i][j].set_neighborhood(6, supergrid[i+1][j].get_state());
            }
            else 
            {
                supergrid[i][j].set_neighborhood(6, '0');
            }
            if ((j+1) > 0 && (j+1) < NC && (i+1) > 0 && (i+1) < NR) 
            {
                supergrid[i][j].set_neighborhood(7, supergrid[i+1][j+1].get_state());
            }
            else 
            {
                supergrid[i][j].set_neighborhood(7, '0');
            }
        }
    }

    // cout << count_live_cells() << "========" << endl;

}

bool multiverse::is_valid()
{
    int i = 0;
    for (i = 0; i < NC; i++)
    {
        if(supergrid[0][i].get_state() != '0')
            return false;
        if(supergrid[NR-1][i].get_state() != '0')
            return false;
    }

    for (i = 0; i < NR; i++)
    {
        if(supergrid[i][0].get_state() != '0')
            return false;
        if(supergrid[i][NC-1].get_state() != '0')
            return false;
    }

    return true;
}

void multiverse::update_state()
{
    // cout << count_live_cells() << "========" << endl;
    // cout << "In Multiverse update state" << endl;
    int i, j;
    for (i = 0; i < NR; i++)
    {
        for (j = 0; j < NC; j++)
        {
            if (supergrid[i][j].is_live())
            {
                supergrid[i][j].set_state('1');
            }
            else
                supergrid[i][j].set_state('0');
        }
    }
    // cout << count_live_cells() << "========" << endl;
}

grid** multiverse::get_supergrid()
{
    return supergrid;
}

            // supergrid[i][j].set_state(sgrid[i][j].get_state());
            // for (int ct = 0; ct < 8; ct++)
            // {
            //     supergrid[i][j].set_neighborhood(ct, sgrid[i][j].get_neighborhood()[ct]);
            // }

            // supergrid[i][j].set_gridcells(sgrid[i][j].get_grid());

void multiverse::set_grids(grid** sgrid)
{
    // cout << "setting grids" << endl;
    for (int i = 0; i < NR; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            for (int k = 0; k < R; k++)
            {
                for (int l = 0; l < C; l++)
                {
                    supergrid[i][j].get_grid()[k][l].set_state(sgrid[i][j].get_grid()[k][l].get_state());
                }
            }
            supergrid[i][j].update_neighborhood();
            supergrid[i][j].set_state(sgrid[i][j].get_state());
        }
    }
    
    update_neighborhood();

    // cout << "done setting grids" << endl;
    // cout << count_live_cells() << "========" << endl;
}

void multiverse::generate_next_gen()
{
    // cout << "generating next gen" << endl;
    for (int i = 0; i < NR; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            if (supergrid[i][j].count_live_neighbors() < 2 || supergrid[i][j].count_live_neighbors() > 3)
            {
                supergrid[i][j].kill_grid();
            }
            else if (supergrid[i][j].get_state() == '0' && supergrid[i][j].count_live_neighbors() == 3)
            {
                supergrid[i][j].revive_grid();
            }
        }
    }
    // cout << "done generating next gen" << endl;
    // cout << count_live_cells() << "========" << endl;
}

void multiverse::synchronize_multiverse(int gen_count)
{

    // cout << "Synchronizing multiverse"<<endl;
    // cout << count_live_cells() << "========" << endl;
    int i, j;
    for (i = 0; i < NR; i++)
    {
        for (j = 0; j < NC; j++)
        {
            // grid proxy = supergrid[i][j];
            // for (int k = 0; k < gen_count; k++)
            // {
            //     proxy.generate_next_gen();
            //     if (proxy.is_valid())
            //     {
            //         supergrid[i][j].set_gridcells(proxy.get_grid());
            //         supergrid[i][j].update_neighborhood();
            //     }
            //     else
            //         break;
            // }
            supergrid[i][j].generate_k_generations(gen_count);
        }
    }
    // cout << count_live_cells() << "========" << endl;

    update_state();
    update_neighborhood();
    // cout << "done synchronizing" << endl;
    // cout << count_live_cells() << "========" << endl;    
}


std::ostream& operator << (std::ostream& os, gridcell& cell)
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

void multiverse::print_grid_row(int rn)
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            supergrid[rn][j].print_row(i);
            cout << " ";
        }
    }
}

void multiverse::print_multiverse()
{
    for (int i = 0; i < NR; i++)
    {
        print_grid_row(i);
        cout << endl;
    }
}

std::ostream& operator << (std::ostream& os, grid& myGrid) {
    int rows = myGrid.X, cols = myGrid.Y;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++) {
            os << myGrid.gridcells[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}
