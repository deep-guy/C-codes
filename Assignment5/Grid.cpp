#include "Grid.h"
using namespace std;

Grid::Grid(int x, int y, char* in_file_name)
{
    _X = x;
    _Y = y;
    _gridcells = new Gridcell*[_X+1];
    for(int i = 0; i < _X; i++)
    {
        _gridcells[i] = new Gridcell[_Y+1];
    }

    for (int i = 0; i < _X; i++)
    {
        for (int j = 0; j < _Y; j++)
        {
            _gridcells[i][j](i, j);
            _gridcells[i][j].set_state('0');
            unsigned char nhood[8] = {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'};
            _gridcells[i][j].set_neighborhood(nhood);
        }
    }

    ifstream in_file;
    in_file.open(in_file_name);
    string line;
    getline (in_file, line);
    getline (in_file, line);
    int counter = 0;
    while (line != "eof")
    {
        for(int i = 0; i < line.size(); i++)
        {
            if(line[i] != ' ')
            {
                
                if (line[i] == 'o')
                {
                    _gridcells[counter][i/2].set_state('0');
                }
                else if (line[i] == '+')
                {
                    _gridcells[counter][i/2].set_state('1');                    
                }
            }
        }
        counter ++;
        getline (in_file, line);
    }
}

Grid::~Grid()
{
    int i = 0;
    for (i = 0; i < _X; i++)
    {
        cout << _gridcells[i];
        delete[] _gridcells[i];
    }
    delete[] _gridcells;
}

Grid::Grid(const Grid& obj)
{
    _X = obj._X;
    _Y = obj._Y;
    _gridcells = new Gridcell*[obj._X];
    for (int i = 0; i < _X; i++)
    {
        _gridcells[i] = new Gridcell[obj._Y];
    }

    for (int i = 0; i < _X; i++)
    {
        for (int j = 0; j < _Y; j++)
        {
            _gridcells[i][j] = obj._gridcells[i][j];
        }
    }
    update_neighborhood();
}


void Grid::set_gridcells(Gridcell** gcells)
{
    for (int i = 0; i < _X; i++)
    {
        for (int j = 0; j < _Y; j++)
        {
            _gridcells[i][j].set_x(i);
            _gridcells[i][j].set_y(j);
            _gridcells[i][j].set_state(gcells[i][j].get_state());
        }
    }
}


Grid Grid::operator = (const Grid& obj)
{
    _X = obj._X;
    _Y = obj._Y;
    for (int i = 0; i < _X; i++)
    {
        for (int j = 0; j < _Y; j++)
        {
            _gridcells[i][j] = obj._gridcells[i][j];
        }
    }
    return *this;
}


void Grid::update_neighborhood()
{
    unsigned char i0, i1, i2, i3, i4, i5, i6, i7;
    // There will be 9 seperate cases in this.
    //Each corner cell is a seperate case, and has to be updates individually
    unsigned char* stateList;
    stateList = new unsigned char[8];


    //(1) updating the top-left corner
    i0 = _gridcells[1][0].get_state();
    i7 = _gridcells[1][1].get_state();
    i6 = _gridcells[0][1].get_state();
    int i, j, k;
    for (i = 0; i < 8; i++)
    {
        stateList[i] = 'X';
    }
    stateList[0] = i0;
    stateList[7] = i7;
    stateList[6] = i6;
    _gridcells[0][0].set_neighborhood(stateList);


    //(2) updating top-right corner
    i4 = _gridcells[_X-2][0].get_state();
    i6 = _gridcells[_X-1][1].get_state();
    i5 = _gridcells[_X-2][1].get_state();
    for (i = 0; i < 8; i++)
    {
        stateList[i] = 'X';
    }
    stateList[4] = i4;
    stateList[5] = i5;
    stateList[6] = i6;
    _gridcells[_X-1][0].set_neighborhood(stateList);

    //(3)Updating bottom-left corner
    i0 = _gridcells[1][_Y-1].get_state();
    i1 = _gridcells[1][_Y-2].get_state();
    i2 = _gridcells[0][_Y-2].get_state();
    for (i = 0; i < 8; i++)
    {
        stateList[i] = 'X';
    }
    stateList[0] = i0;
    stateList[1] = i1;
    stateList[2] = i2;
    _gridcells[0][_Y-1].set_neighborhood(stateList);


    //(4) Updating bottom-right corner
    i2 = _gridcells[_X-1][_Y-2].get_state();
    i3 = _gridcells[_X-2][_Y-2].get_state();
    i4 = _gridcells[_X-2][_Y-1].get_state();
    for (i = 0; i < 8; i++)
    {
        stateList[i] = 'X';
    }
    stateList[2] = i2;
    stateList[3] = i3;
    stateList[4] = i4;
    _gridcells[_X-1][_Y-1].set_neighborhood(stateList);

    //(5) Updating top-edge cells
    for(i = 1; i < _X-1; i++)
    {
        i0 = _gridcells[i+1][0].get_state();
        i4 = _gridcells[i-1][0].get_state();
        i5 = _gridcells[i-1][1].get_state();
        i6 = _gridcells[i][1].get_state();
        i7 = _gridcells[i+1][1].get_state();
        for (j = 0; j < 8; j++)
        {
            stateList[j] = 'X';
        }
        stateList[0] = i0;
        stateList[4] = i4;
        stateList[5] = i5;
        stateList[6] = i6;
        stateList[7] = i7;
        _gridcells[i][0].set_neighborhood(stateList);

    }


    //(6) Updating bottom-edge cells
    for(i = 1; i < _X-1; i++)
    {
        i0 = _gridcells[i+1][_Y-1].get_state();
        i1 = _gridcells[i+1][_Y-2].get_state();
        i2 = _gridcells[i][_Y-2].get_state();
        i3 = _gridcells[i-1][_Y-2].get_state();
        i4 = _gridcells[i-1][_Y-1].get_state();
        for (j = 0; j < 8; j++)
        {
            stateList[j] = 'X';
        }
        stateList[0] = i0;
        stateList[1] = i1;
        stateList[2] = i2;
        stateList[3] = i3;
        stateList[4] = i4;
        _gridcells[i][_Y-1].set_neighborhood(stateList);
    }


    //(7) Updating left-edge cells
    for(i = 1; i < _Y-1; i++)
    {
        i0 = _gridcells[1][i].get_state();
        i1 = _gridcells[1][i-1].get_state();
        i2 = _gridcells[0][i-1].get_state();
        i6 = _gridcells[0][i+1].get_state();
        i7 = _gridcells[1][i+1].get_state();
        for (j = 0; j < 8; j++)
        {
            stateList[j] = 'X';
        }
        stateList[0] = i0;
        stateList[1] = i1;
        stateList[2] = i2;
        stateList[6] = i6;
        stateList[7] = i7;
        _gridcells[0][i].set_neighborhood(stateList);
    }
    


    //(8) Updating right-edge cells
    for(i = 1; i < _Y-1; i++)
    {
        i2 = _gridcells[_X-1][i-1].get_state();
        i3 = _gridcells[_X-2][i-1].get_state();
        i4 = _gridcells[_X-2][i].get_state();
        i5 = _gridcells[_X-2][i+1].get_state();
        i6 = _gridcells[_X-1][i+1].get_state();
        for (j = 0; j < 8; j++)
        {
            stateList[j] = 'X';
        }
        stateList[2] = i2;
        stateList[3] = i3;
        stateList[4] = i4;
        stateList[5] = i5;
        stateList[6] = i6;
        _gridcells[_X-1][i].set_neighborhood(stateList);
    }



    //(9) Updating all remaining center cells
    for(i = 1; i < _X-1; i++)
    {
        for(j = 1; j < _Y-1; j++)
        {
            stateList[0] = _gridcells[i+1][j].get_state();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
            stateList[1] = _gridcells[i+1][j-1].get_state();
            stateList[2] = _gridcells[i][j-1].get_state();
            stateList[3] = _gridcells[i-1][j-1].get_state();
            stateList[4] = _gridcells[i-1][j].get_state();
            stateList[5] = _gridcells[i-1][j+1].get_state();
            stateList[6] = _gridcells[i][j+1].get_state();
            stateList[7] = _gridcells[i+1][j+1].get_state();
            _gridcells[i][j].set_neighborhood(stateList);            
        }
    }
}


void Grid::print_grid()
{
    int i, j;
    int counter = 0;
    for(i = 0; i < _X; i++)
    {
        for(j = 0; j < _Y; j++)
        {
            if(_gridcells[i][j].get_state() == '0')
            {
                cout << "o ";
            }
            else if(_gridcells[i][j].get_state() == '1')
            {
                cout << "+ ";
                counter++;
            }
        }
        cout << endl;
    }
    // cout << counter << " : Cell count pf Grid" << endl;
}


bool Grid::is_valid()
{
    int i = 0;
    for (i = 0; i < _Y; i++)
    {
        if(_gridcells[0][i].get_state() != '0')
            return false;
        if(_gridcells[_X-1][i].get_state() != '0')
            return false;
    }

    for (i = 0; i < _X; i++)
    {
        if(_gridcells[i][0].get_state() != '0')
            return false;
        if(_gridcells[i][_Y-1].get_state() != '0')
            return false;
    }

    return true;
}


void Grid::output_to_file(int z)
{
    int i, j;
    ofstream outfile("output.txt");
    // cout << "hello20" << endl;
    // outfile.open("output.txt");
    // outfile.open("output.txt",ios::out);
    outfile<<_X<<" "<<_Y<<" "<<z<<endl;
        for(i=0; i < _X; i++)
        {
            int j;
            for(j = 0; j < _Y; j++)
            {
                outfile << _gridcells[i][j].get_state() << " ";
            }
            //printf("\n");
            outfile<<endl;
        }
        outfile<<"eof";
    outfile.close();
}


int Grid::calculate_output()
{
    int i, j, output = 0;
    for(i = 0; i < _X; i++)
    {
        for(j = 0; j < _Y; j++)
        {
            if (_gridcells[i][j].get_state() == '1')
                output++;
        }
    }
    return output;
}


std::ostream& operator << (std::ostream& os, Grid& myGrid) {
    int rows = myGrid._X, cols = myGrid._Y;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) 
        {
            os << myGrid._gridcells[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}