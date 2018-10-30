#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Gridcell.h"
#include "Grid.h"
using namespace std;

// use 'X' to denote the neighborhood state of the cells that do not exist


// Function definitions of all methods of gridcell class
gridcell::gridcell()
{
    neighborhood = new unsigned char[8];
}

gridcell::~gridcell()
{
    delete[] neighborhood;
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
}

grid::~grid()
{
    int i = 0;
    for (i = 0; i < X; i++)
    {
        delete[] gridcells[i];
    }
    delete[] gridcells;
}

gridcell grid::get_cell(int i, int j)
{
    return gridcells[i][j];
}

void grid::generate_initial_state(int L)
{
    srand(time(0));
    int i, j = 0;

    gridcells[0][0].set_x(0);
    gridcells[0][0].set_y(0);
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



void grid::print_grid()
{
    int i, j;
    for(i = 0; i < X; i++)
    {
        for(j = 0; j < Y; j++)
        {
            if(gridcells[i][j].get_state() == '0')
            {
                cout << "0 ";
            }
            else if(gridcells[i][j].get_state() == '1')
            {
                cout << "+ ";
            }
        }
        cout << "" << endl;
    }
}


int grid::calculate_output()
{
    int i, j, output = 0;
    for(i = 0; i < X; i++)
    {
        for(j = 0; j < Y; j++)
        {
            output += gridcells[i][j].count_live_neighbors();
        }
    }
    return output;
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


int main()
{
    int row_count, col_count, live_cell_count;
    cin >> row_count;
    cin >> col_count;
    cin >> live_cell_count;
    grid myGrid(row_count, col_count);

    if (row_count > 0 && col_count > 0 && live_cell_count >= 0)
    {
        if (live_cell_count <= (row_count-2) * (col_count-2))
        {
            myGrid.generate_initial_state(live_cell_count);
            myGrid.update_neighborhood();
            int output = myGrid.calculate_output();
            cout << output << endl;
           // myGrid.print_grid();
            // cout << myGrid;
        }
        else
            cout << "0" << endl;
            
    }
    else
        cout << "0" << endl;
    return 0;
}