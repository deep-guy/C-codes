#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>
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
    proxy = new gridcell*[X+1];
    for(int i = 0; i < X; i++)
    {
        gridcells[i] = new gridcell[Y+1];
        proxy[i] = new gridcell[Y+1];
    }
}

grid::~grid()
{
    int i = 0;
    for (i = 0; i < X; i++)
    {
        delete[] gridcells[i];
        delete[] proxy[i];
    }
    delete[] gridcells;
    delete[] proxy;
}

gridcell grid::get_cell(int i, int j)
{
    return gridcells[i][j];
}


void grid::generate_initial_state()
{
    int i, j;
    for (i = 0; i < X; i ++)
    {
        for (j = 0; j < Y; j++)
        {
            gridcells[i][j].set_x(i);
            gridcells[i][j].set_y(j);
            gridcells[i][j].set_state('0');
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

bool grid::is_valid()
{
    int i = 0;
    for (i = 0; i < Y; i++)
    {
        if(proxy[0][i].get_state() != '0')
            return false;
        if(proxy[X-1][i].get_state() != '0')
            return false;
    }

    for (i = 0; i < X; i++)
    {
        if(proxy[i][0].get_state() != '0')
            return false;
        if(proxy[i][Y-1].get_state() != '0')
            return false;
    }

    return true;
}

void grid::copy_to_proxy()
{
    int i, j;
    for (i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            proxy[i][j].set_x(i);
            proxy[i][j].set_y(j);
            proxy[i][j].set_state(gridcells[i][j].get_state());
            proxy[i][j].set_neighborhood(gridcells[i][j].get_neighborhood());
        }
    }
}


void grid::generate_next_gen()
{
    int i, j;
    copy_to_proxy();

    for (i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            int ln = gridcells[i][j].count_live_neighbors();
            if (gridcells[i][j].get_state() == '1' && ln < 2)
            {
                proxy[i][j].set_state('0');
            }
            else if (gridcells[i][j].get_state() == '1' && ln > 3)
            {
                proxy[i][j].set_state('0');
            }
            else if(gridcells[i][j].get_state() == '0' && ln == 3)
            {
                proxy[i][j].set_state('1');
            }
        }
    }

    if(is_valid())
    {
        for(i = 0; i < X; i++)
        {
            for(j = 0; j < Y; j++)
            {
                gridcells[i][j].set_state(proxy[i][j].get_state());
            }
        }
        update_neighborhood();
    }
}

void grid::set_gridcell_state(int i, int j, unsigned char state)
{
    gridcells[i][j].set_state(state);
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

bool is_valid_input_file(string name, int rc, int cc, int lcc)
{
    ifstream in_file;
    in_file.open(name);
    string line;
    if (rc != 0 && cc != 0 && lcc == 0)
    {
        while( getline (in_file, line))
        {
            if (line == "eof")
            {
                in_file.close();
                return true;
            }
        }
    }
    in_file.close();
    return false;
}


void output_invalid_file()
{
    ofstream myfile ("output.txt");
    if (myfile.is_open())
    {
        myfile << "0 0 0\n";
        myfile << "eof";
        myfile.close();
    }
    myfile.close();
}

void grid::output_to_file(int z)
{
    int i, j;
    ofstream outfile("output.txt");
    // cout << "hello20" << endl;
    // outfile.open("output.txt");
    // outfile.open("output.txt",ios::out);
    outfile<<X<<" "<<Y<<" "<<z<<endl;
        for(i=0; i < X; i++)
        {
            int j;
            for(j = 0; j < Y; j++)
            {
                outfile << gridcells[i][j].get_state() << " ";
            }
            //printf("\n");
            outfile<<endl;
        }
        outfile<<"eof";
    outfile.close();
}



int main(int argc, char** argv)
{
    int row_count, col_count, generation_count, input_gen;
    stringstream geek(argv[2]);
    geek >> generation_count;
    cout << generation_count << endl;
    string in_file_name = argv[1];
    ifstream in_file;
    in_file.open(in_file_name);
    string line;
    getline (in_file, line);
    int counter = line.size();
    int i, sp1, sp2;
    for(i = 0; i < counter; i++)
    {
        if(line[i] == ' ')
        {
            sp1 = i;
            break;
        }
    }

    for(i = sp1+1; i < counter; i++)
    {
        if (line[i] == ' ')
        {
            sp2 = i;
            break;
        }
    }

    for (i = 0; i < sp1; i++)
    {
        row_count = (row_count * 10) + (line[i] - '0');
    }

    for (i = sp1 + 1; i < sp2; i++)
    {
        col_count = (col_count * 10) + (line[i] - '0');
    }

    input_gen = 0;

    for (i = sp2 + 1; i < counter; i++)
    {
        input_gen = (input_gen * 10) + (line[i]-'0');
    }

    in_file.close();

    if (!is_valid_input_file(in_file_name, row_count, col_count, input_gen))
    {
        output_invalid_file();
        return 0;
    }
    
    
    grid myGrid(row_count, col_count);
    in_file.open(in_file_name);
    getline (in_file, line);
    getline (in_file, line);
    counter = 0;
    while (line != "eof")
    {
        for(i = 0; i < line.size(); i++)
        {
            if(line[i] != ' ')
            {
                
                if (line[i] == 'o')
                {
                    myGrid.set_gridcell_state(counter, i/2, '0');
                }
                else if (line[i] == '+')
                {
                    myGrid.set_gridcell_state(counter, i/2, '1');                    
                }
            }
        }
        counter ++;
        getline (in_file, line);
    }
    myGrid.update_neighborhood();
    i = 0;
    while (i < generation_count)
    {
        myGrid.generate_next_gen();
        i++;
    }
    myGrid.output_to_file(generation_count);
    // cout << "hello1" << endl;
    
}