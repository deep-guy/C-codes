#include "Gridcell.h"
#include "Grid.h"
#include "Multiverse.h"
using namespace std;

// use 'X' to denote the neighborhood state of the cells that do not exist


// Function definitions of all methods of gridcell class



// Function definitions of all methods of grid class


// Multiverse methods 



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