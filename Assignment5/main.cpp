#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "Gridcell.h"
#include "Grid.h"
#include "Maze.h"
#include "HighLife.h"
#include "Mazectric.h"
using namespace std;


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


int main(int argc, char** argv)
{
    int row_count = 0, col_count = 0, generation_count = 0, input_gen;
    stringstream geek(argv[2]);
    geek >> generation_count;
    cout << generation_count << endl;
    char* in_file_name = argv[1];
    ifstream in_file;
    in_file.open(in_file_name);
    string line;
    getline (in_file, line);
    int counter = line.size();
    int i, sp1 = 0, sp2 = 0;
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

    cout << "Space: " << sp1 << "  Space: " << sp2 << endl;


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

    cout << "Row: " << row_count << "  Col: " << col_count << "  Gen: " << input_gen << endl;
    in_file.close();

    if (!is_valid_input_file(in_file_name, row_count, col_count, input_gen))
    {
        output_invalid_file();
        return 0;
    }
    
    stringstream geek1(argv[3]);
    int type = 0;
    geek1 >> type;
    Grid myGrid;
    if (type == 3)
    {
        Maze myGrid(row_count, col_count, in_file_name);
        myGrid.generate_k_gens(generation_count);
        myGrid.output_to_file(generation_count);
    }
    
    else if (type == 2)
    {
        
    }
    return 0;
}