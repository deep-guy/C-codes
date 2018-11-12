#include "Grid.h"
using namespace std;

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
