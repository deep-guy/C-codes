#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <sstream>
#include "Gridcell.h"
#include "Grid.h"
#include "Multiverse.h"
using namespace std;

// use 'X' to denote the neighborhood state of the cells that do not exist


// Function definitions of all methods of gridcell class
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



// Function definitions of all methods of grid class
grid::grid(int x, int y)
{
    X = x;
    Y = y;
    gridcells = new gridcell*[X+1];
    for(int i = 0; i < X; i++)
    {
        gridcells[i] = new gridcell[Y+1];
    }

    neighborhood = new unsigned char[8];
    for (int i = 0; i < 8; i ++)
    {
        neighborhood[i] = 'X';
    }
}

// grid::~grid()
// {
//     int i = 0;
//     for (i = 0; i < X; i++)
//     {
//         delete[] gridcells[i];
//     }
//     delete[] gridcells;
// }

grid::grid(const grid& obj)
{
    X = obj.X;
    Y = obj.Y;
    state = obj.state;
    neighborhood = new unsigned char[8];
    for (int i = 0; i < 8; i++)
    {
        neighborhood[i] = obj.neighborhood[i];
    }
    gridcells = new gridcell*[X];
    for (int i = 0; i < X; i++)
    {
        gridcells[i] = new gridcell[Y];
    }

    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            gridcells[i][j] = obj.gridcells[i][j];
        }
    }
}

gridcell grid::get_cell(int i, int j)
{
    return gridcells[i][j];
}

void grid::generate_initial_state(bool isAlive)
{
    // cout << "In grid gen initial state" << endl;
    int L = 0;
    // cout << X << "~~~~~~~~" << endl;
    // cout << Y << "~~~~~~~~" << endl;
    
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            gridcells[i][j].set_state('0');
        }
    }

    if (isAlive)
    {
        // cout << "I set the state!!" << endl;
        set_state('1');
        float lcc = 0.55 * X * Y;
        L = ceil(lcc);
    }
    else
    {
        // cout << "I set the state!!" << endl;
        float lcc = 0.20 * X * Y;
        L = floor(lcc);
        set_state('0');        
    }

    srand(time(0));
    int i, j = 0;

    // gridcells[0][0].set_x(0);
    // gridcells[0][0].set_y(0);
    gridcells[0][0].set_state('0');

    // Assigining all the side rows and columns as 0
    for (i = 1; i < X; i++)
    {
        gridcells[i][0].set_x(i);
        gridcells[i][0].set_y(0);
        gridcells[i][0].set_state('0');
    }
    for (i = 1; i < Y; i++)
    {
        gridcells[0][i].set_x(0);
        gridcells[0][i].set_y(i);
        gridcells[0][i].set_state('0');
    }

    //assigning all the values of the remaining cells
    for(i = 1; i < X; i++)
    {
        for(j = 1; j < Y; j++)
        {
            gridcells[i][j].set_x(i);
            gridcells[i][j].set_y(j);
            gridcells[i][j].set_state('0');
        }
    }
    while(L != 0)
    {
        for(i = 1; i < X-1; i++)
        {
            for(j = 1; j < Y-1; j++)
            {
                unsigned char st;
                int rdm = rand();

                // finding the value of the cell randomly
                if (L == 0)
                {
                    st = '0';
                }
                else if(rdm%2 == 0)
                {
                    if(gridcells[i][j].get_state() != '1')
                    {
                        st = '1';
                        L--;
                        gridcells[i][j].set_state(st);
                    }
                }
            }
        }
    }
}


void grid::update_neighborhood()
{
    unsigned char i0, i1, i2, i3, i4, i5, i6, i7;
    // There will be 9 seperate cases in this.
    //Each corner cell is a seperate case, and has to be updates individually
    unsigned char* stateList;
    stateList = new unsigned char[8];


    //(1) updating the top-left corner
    i0 = gridcells[1][0].get_state();
    i7 = gridcells[1][1].get_state();
    i6 = gridcells[0][1].get_state();
    int i, j, k;
    for (i = 0; i < 8; i++)
    {
        stateList[i] = 'X';
    }
    stateList[0] = i0;
    stateList[7] = i7;
    stateList[6] = i6;
    gridcells[0][0].set_neighborhood(stateList);


    //(2) updating top-right corner
    i4 = gridcells[X-2][0].get_state();
    i6 = gridcells[X-1][1].get_state();
    i5 = gridcells[X-2][1].get_state();
    for (i = 0; i < 8; i++)
    {
        stateList[i] = 'X';
    }
    stateList[4] = i4;
    stateList[5] = i5;
    stateList[6] = i6;
    gridcells[X-1][0].set_neighborhood(stateList);

    //(3)Updating bottom-left corner
    i0 = gridcells[1][Y-1].get_state();
    i1 = gridcells[1][Y-2].get_state();
    i2 = gridcells[0][Y-2].get_state();
    for (i = 0; i < 8; i++)
    {
        stateList[i] = 'X';
    }
    stateList[0] = i0;
    stateList[1] = i1;
    stateList[2] = i2;
    gridcells[0][Y-1].set_neighborhood(stateList);


    //(4) Updating bottom-right corner
    i2 = gridcells[X-1][Y-2].get_state();
    i3 = gridcells[X-2][Y-2].get_state();
    i4 = gridcells[X-2][Y-1].get_state();
    for (i = 0; i < 8; i++)
    {
        stateList[i] = 'X';
    }
    stateList[2] = i2;
    stateList[3] = i3;
    stateList[4] = i4;
    gridcells[X-1][Y-1].set_neighborhood(stateList);

    //(5) Updating top-edge cells
    for(i = 1; i < X-1; i++)
    {
        i0 = gridcells[i+1][0].get_state();
        i4 = gridcells[i-1][0].get_state();
        i5 = gridcells[i-1][1].get_state();
        i6 = gridcells[i][1].get_state();
        i7 = gridcells[i+1][1].get_state();
        for (j = 0; j < 8; j++)
        {
            stateList[j] = 'X';
        }
        stateList[0] = i0;
        stateList[4] = i4;
        stateList[5] = i5;
        stateList[6] = i6;
        stateList[7] = i7;
        gridcells[i][0].set_neighborhood(stateList);

    }


    //(6) Updating bottom-edge cells
    for(i = 1; i < X-1; i++)
    {
        i0 = gridcells[i+1][Y-1].get_state();
        i1 = gridcells[i+1][Y-2].get_state();
        i2 = gridcells[i][Y-2].get_state();
        i3 = gridcells[i-1][Y-2].get_state();
        i4 = gridcells[i-1][Y-1].get_state();
        for (j = 0; j < 8; j++)
        {
            stateList[j] = 'X';
        }
        stateList[0] = i0;
        stateList[1] = i1;
        stateList[2] = i2;
        stateList[3] = i3;
        stateList[4] = i4;
        gridcells[i][Y-1].set_neighborhood(stateList);
    }


    //(7) Updating left-edge cells
    for(i = 1; i < Y-1; i++)
    {
        i0 = gridcells[1][i].get_state();
        i1 = gridcells[1][i-1].get_state();
        i2 = gridcells[0][i-1].get_state();
        i6 = gridcells[0][i+1].get_state();
        i7 = gridcells[1][i+1].get_state();
        for (j = 0; j < 8; j++)
        {
            stateList[j] = 'X';
        }
        stateList[0] = i0;
        stateList[1] = i1;
        stateList[2] = i2;
        stateList[6] = i6;
        stateList[7] = i7;
        gridcells[0][i].set_neighborhood(stateList);
    }
    


    //(8) Updating right-edge cells
    for(i = 1; i < Y-1; i++)
    {
        i2 = gridcells[X-1][i-1].get_state();
        i3 = gridcells[X-2][i-1].get_state();
        i4 = gridcells[X-2][i].get_state();
        i5 = gridcells[X-2][i+1].get_state();
        i6 = gridcells[X-1][i+1].get_state();
        for (j = 0; j < 8; j++)
        {
            stateList[j] = 'X';
        }
        stateList[2] = i2;
        stateList[3] = i3;
        stateList[4] = i4;
        stateList[5] = i5;
        stateList[6] = i6;
        gridcells[X-1][i].set_neighborhood(stateList);
    }



    //(9) Updating all remaining center cells
    for(i = 1; i < X-1; i++)
    {
        for(j = 1; j < Y-1; j++)
        {
            stateList[0] = gridcells[i+1][j].get_state();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
            stateList[1] = gridcells[i+1][j-1].get_state();
            stateList[2] = gridcells[i][j-1].get_state();
            stateList[3] = gridcells[i-1][j-1].get_state();
            stateList[4] = gridcells[i-1][j].get_state();
            stateList[5] = gridcells[i-1][j+1].get_state();
            stateList[6] = gridcells[i][j+1].get_state();
            stateList[7] = gridcells[i+1][j+1].get_state();
            gridcells[i][j].set_neighborhood(stateList);            
        }
    }
}

int grid::count_live_neighbors()
{
    int ln = 0;
    for (int i = 0; i < 8; i++)
    {
        if (neighborhood[i] == '1')
            ln++;
    }
    return ln;
}

bool grid::is_valid()
{
    int i = 0;
    for (i = 0; i < Y; i++)
    {
        if(gridcells[0][i].get_state() != '0')
            return false;
        if(gridcells[X-1][i].get_state() != '0')
            return false;
    }

    for (i = 0; i < X; i++)
    {
        if(gridcells[i][0].get_state() != '0')
            return false;
        if(gridcells[i][Y-1].get_state() != '0')
            return false;
    }

    return true;
}

bool grid::is_live()
{
    int i, j;
    int count = 0;

    for(i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            if (gridcells[i][j].get_state() == '1')
            {
                count++;
            }
        }
    }

    if (count >= ceil(0.5*X*Y))
    {
        state = '1';
        return true;
    }
    state = '0';
    return false;
}

gridcell** grid::get_grid()
{
    return gridcells;
}

void grid::set_gridcells(gridcell** gcells)
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            gridcells[i][j].set_x(i);
            gridcells[i][j].set_y(j);
            gridcells[i][j].set_state(gcells[i][j].get_state());
        }
    }
}

unsigned char* grid::get_neighborhood()
{
    return neighborhood;
}

void grid::kill_grid()
{
    state = '0';
    srand(time(0));
    int i, j;
    int live_count = 0;

    for(i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            if (gridcells[i][j].get_state() == '1')
            {
                live_count++;
            }
        }
    }

    int L = live_count - (floor(0.45*X*Y));

    while (L > 0)
    {
        for(i = 1; i < X-1; i++)
        {
            for(j = 1; j < Y-1; j++)
            {
                unsigned char st;
                int rdm = rand();

                // finding the value of the cell randomly
                if (L <= 0)
                {
                    st = '0';
                }
                else if(rdm%13 == 0)
                {
                    if(gridcells[i][j].get_state() == '1')
                    {
                        st = '0';
                        L--;
                        gridcells[i][j].set_state(st);
                    }
                }
            }
        }
    }
}

void grid::revive_grid()
{
    state = '1';
    srand(time(0));
    int i, j;
    int live_count = 0;

    for(i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            if (gridcells[i][j].get_state() == '1')
            {
                live_count++;
            }
        }
    }

    int L = (ceil(0.55*X*Y)) - live_count;

    while (L > 0)
    {
        for(i = 1; i < X-1; i++)
        {
            for(j = 1; j < Y-1; j++)
            {
                unsigned char st;
                int rdm = rand();

                // finding the value of the cell randomly
                if (L <= 0)
                {
                    st = '0';
                }
                else if(rdm%13 == 0)
                {
                    if(gridcells[i][j].get_state() != '1')
                    {
                        st = '1';
                        L--;
                        gridcells[i][j].set_state(st);
                    }
                }
            }
        }
    }
}

void grid::set_x(int x)
{
    X = x;
}

void grid::set_y(int y)
{
    Y = y;
}

void grid::initialize_gridcells()
{
    //  << X << "+++++++" << endl;
    // cout << Y << "+++++++" << endl;cout
    neighborhood = new unsigned char[8];
    gridcells = new gridcell*[X];
    for (int i = 0; i < X; i++)
    {
        gridcells[i] = new gridcell[Y];
    }

    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            gridcells[i][j].set_x(i);
            gridcells[i][j].set_y(j);
            gridcells[i][j].set_state('0');
        }
    }
    // cout << "Done initialize gridcells" << endl;
}

// void grid::copy_to_proxy()
// {
//     int i, j;
//     for (i = 0; i < X; i++)
//     {
//         for (j = 0; j < Y; j++)
//         {
//             proxy[i][j].set_x(i);
//             proxy[i][j].set_y(j);
//             proxy[i][j].set_state(gridcells[i][j].get_state());
//             proxy[i][j].set_neighborhood(gridcells[i][j].get_neighborhood());
//         }
//     }
// }

void grid::generate_next_gen()
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            update_neighborhood();
            // cout << "Live neighbors are " << gridcells[i][j].count_live_neighbors() << endl;
            if (gridcells[i][j].count_live_neighbors() < 2 || gridcells[i][j].count_live_neighbors() > 3)
            {
                gridcells[i][j].set_state('0');
            }
            else if (gridcells[i][j].get_state() == '0' && gridcells[i][j].count_live_neighbors() == 3)
            {
                gridcells[i][j].set_state('1');
            }
        }
    }
    // cout <<"printing grid inside gen_next_gen:   ";
    // print_grid();
    if (count_live_neighbors() > (int)(X*Y)/2.0)
    {
        state = '1';
    }
    else
    {
        state = '0';
    }
    update_neighborhood();
}



void grid::print_grid()
{
    int i, j;
    int counter = 0;
    for(i = 0; i < X; i++)
    {
        for(j = 0; j < Y; j++)
        {
            if(gridcells[i][j].get_state() == '0')
            {
                // cout << "o ";
            }
            else if(gridcells[i][j].get_state() == '1')
            {
                // cout << "+ ";
                counter++;
            }
        }
    }
    cout << counter << " : Cell count pf grid" << endl;
}

void grid::print_row(int rn)
{
    for (int j = 0; j < Y; j++)
    {
        if(gridcells[rn][j].get_state() == '0')
        {
            cout << "o ";
        }
        else if(gridcells[rn][j].get_state() == '1')
        {
            cout << "+ ";
        }
    }
}

unsigned char grid::get_state()
{
    return state;
}

void grid::generate_k_generations(int k)
{
    // cout <<"generate " << k <<  " generations" << endl;
    grid proxy = *this;
    // proxy.print_grid();
    for (int i = 0; i < k; i++)
    {
        // cout << "entering loop" << endl;
        proxy.generate_next_gen();
        // proxy.print_grid();
        if (proxy.is_valid())
        {
            set_gridcells(proxy.get_grid());
            update_neighborhood();
        }
        else
        {
            break;
        }
        // cout << "exiting loop" << endl;
    }
}

int grid::calculate_output()
{
    int i, j, output = 0;
    for(i = 0; i < X; i++)
    {
        for(j = 0; j < Y; j++)
        {
            if (gridcells[i][j].get_state() == '1')
                output++;
        }
    }
    return output;
}

void grid::set_neighborhood(int k, unsigned char n)
{
    neighborhood[k] = n;
}

void grid::set_state(unsigned char ch)
{
    state = ch;
}

grid::grid(){};


// Multiverse methods 

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


int main(int argc, char** argv)
{
    // int row_count, col_count, live_cell_count;
    // cin >> row_count;
    // cin >> col_count;
    // // cin >> live_cell_count;
    // grid myGrid(row_count, col_count);
    // multiverse MyMultiverse = multiverse(10, 10, 10, 10);
    // int i = 0;
    // int generation_count = 5;
    // live_cell_count = 0;
    // if (row_count > 0 && col_count > 0 && live_cell_count >= 0)
    // {
    //     if (live_cell_count <= (row_count-2) * (col_count-2))
    //     {
    //         myGrid.generate_initial_state(false);
    //         myGrid.update_neighborhood();
    //         grid proxy = myGrid;
    //         while (i < generation_count)
    //         {
    //             proxy.generate_next_gen();
    //             if (proxy.is_valid())
    //             {
    //                 myGrid.set_gridcells(proxy.get_grid());
    //                 myGrid.update_neighborhood();
    //             }
    //             myGrid.print_grid();
    //             cout << endl;
    //             i++;
    //         }
    //         myGrid.print_grid();
    //         cout << "ended"<< endl;
    //         // cout << myGrid;
    //     }
    //     else
    //         cout << "0" << endl;
            
    // }
    // else
    //     cout << "0" << endl;
    // return 0;

    int NR, NC, R, C, k, S;
    stringstream geek1(argv[1]);
    geek1 >> NR;
    stringstream geek2(argv[2]);
    geek2 >> NC;
    stringstream geek3(argv[3]);
    geek3 >> R;
    stringstream geek4(argv[4]);
    geek4 >> C;
    stringstream geek5(argv[5]);
    geek5 >> k;
    stringstream geek6(argv[6]);
    geek6 >> S;

    if (2*(R+C-2) < (R*C))
    {
        multiverse myMultiverse(NR, NC, R, C);
        myMultiverse.generate_initial_state();
        myMultiverse.update_state();
        myMultiverse.update_neighborhood();
        // myMultiverse.print_multiverse();
        int age_count = 0;
        multiverse proxyverse = myMultiverse;

        while (age_count < S)
        {    
            // cout << "===================================================================================" << endl;
            // myMultiverse.print_multiverse();
            // cout << proxyverse.count_live_cells() << "++++++++++" << endl;
            proxyverse.synchronize_multiverse(k);
            // cout << "===================================================================================" << endl;
            // myMultiverse.print_multiverse();
            proxyverse.generate_next_gen();
            if (proxyverse.is_valid())
            {
                myMultiverse.set_grids(proxyverse.get_supergrid());
                myMultiverse.update_neighborhood();
                age_count ++;
            }
            else
            {
                age_count++;
                break;
            }
        }

        myMultiverse.print_multiverse();        

    }

    cout << "eof"<< endl;
}