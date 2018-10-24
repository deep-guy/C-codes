#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct gridcell
{
    int x;
    int y;
    unsigned char state;
    unsigned char* neighborhood;
};

// use 'X' to denote the neighborhood state of the cells that do not exist

typedef struct gridcell gridcell;

gridcell** generate_initial_state(int X, int Y, int L, gridcell** grid)
{
    srand(time(0));
    grid = (gridcell**)malloc((X+1) * sizeof(gridcell*));
    int i = 0;
    for (i = 0; i < X; i++)
    {
        grid[i] = (gridcell*)malloc((Y+1) * sizeof(gridcell));
    }

    int j = 0;

    grid[0][0].x = 0;
    grid[0][0].y = 0;
    grid[0][0].state = '0';

    // Assigining all the side rows and columns as 0
    for (i = 1; i < X; i++)
    {
        grid[i][0].x = i;
        grid[i][0].y = 0;
        grid[i][0].state = '0';
    }
    for (i = 1; i < Y; i++)
    {
        grid[0][i].x = 0;
        grid[0][i].y = i;
        grid[0][i].state = '0';
    }

    //assigning all the values of the remaining cells
    for(i = 1; i < X; i++)
    {
        for(j = 1; j < Y; j++)
        {
            grid[i][j].x = i;
            grid[i][j].y = j;
            grid[i][j].state = '0';
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
                else if(rdm%16 == 0)
                {
                    if(grid[i][j].state != '1')
                    {
                        st = '1';
                        L--;
                        grid[i][j].state = st;
                    }
                }
            }
        }
    }
    return grid;
}


void update_neighborhood(gridcell** grid, int X, int Y)
// {
//     unsigned char i0, i1, i2, i3, i4, i5, i6, i7;
//     int i, j, k;
// //     for(i = 0; i < X; i++)
// //     {
// //         for(j = 0; j < Y; j++)
// //         {
// //             grid[i][j].neighborhood = (unsigned char*)malloc(8*sizeof(unsigned char));
// //             for (k = 0; k < 8; k++)
// //             {
// //                 grid[i][j].neighborhood[k] = 'X';
// //             }        
// //         }
// //     }
// //     for (i = 1; i < X-1; i++)
// //     {
// //         for(j = 1; j < Y-1; j++)
// //         {
// //             printf("%c ", grid[i][j].state);
// //         }
// //         printf("\n");
// //     }
// // }
{
    unsigned char i0, i1, i2, i3, i4, i5, i6, i7;
    // There will be 8 seperate cases in this, maybe more
    //Each corner cell is a seperate case, and has to be updates individually

    //updating the top-left corner
    i0 = grid[1][0].state;
    i7 = grid[1][1].state;
    i6 = grid[0][1].state;
    int i, j, k;
    for(i = 0; i < X; i++)
    {
        for(j = 0; j < Y; j++)
        {
            grid[i][j].neighborhood = (unsigned char*)malloc(8*sizeof(unsigned char));
        }
    }
    for (i = 0; i < 8; i++)
    {
        grid[0][0].neighborhood[i] = 'X';
    }
    grid[0][0].neighborhood[0] = i0;
    grid[0][0].neighborhood[7] = i7;
    grid[0][0].neighborhood[6] = i6;


    //updating top-right corner
    i4 = grid[X-2][0].state;
    i6 = grid[X-1][1].state;
    i5 = grid[X-2][1].state;
    for (i = 0; i < 8; i++)
    {
        grid[X-1][0].neighborhood[i] = 'X';
    }
    grid[X-1][0].neighborhood[4] = i4;
    grid[X-1][0].neighborhood[5] = i5;
    grid[X-1][0].neighborhood[6] = i6;

    //Updating bottom-left corner
    i0 = grid[1][Y-1].state;
    i1 = grid[1][Y-2].state;
    i2 = grid[0][Y-2].state;
    for (i = 0; i < 8; i++)
    {
        grid[0][Y-1].neighborhood[i] = 'X';
    }
    grid[0][Y-1].neighborhood[0] = i0;
    grid[0][Y-1].neighborhood[1] = i1;
    grid[0][Y-1].neighborhood[2] = i2;

    //Updating bottom-right corner
    i2 = grid[X-1][Y-2].state;
    i3 = grid[X-2][Y-2].state;
    i4 = grid[X-2][Y-1].state;
    for (i = 0; i < 8; i++)
    {
        grid[X-1][Y-1].neighborhood[i] = 'X';
    }
    grid[X-1][Y-1].neighborhood[2] = i2;
    grid[X-1][Y-1].neighborhood[3] = i3;
    grid[X-1][Y-1].neighborhood[4] = i4;

    //Updating top-edge cells
    for(i = 1; i < X-1; i++)
    {
        i0 = grid[i+1][0].state;
        i4 = grid[i-1][0].state;
        i5 = grid[i-1][1].state;
        i6 = grid[i][1].state;
        i7 = grid[i+1][1].state;
        for (j = 0; j < 8; j++)
        {
            grid[i][0].neighborhood[j] = 'X';
        }
        grid[i][0].neighborhood[0] = i0;
        grid[i][0].neighborhood[4] = i4;
        grid[i][0].neighborhood[5] = i5;
        grid[i][0].neighborhood[6] = i6;
        grid[i][0].neighborhood[7] = i7;
    }


    //Updating bottom-edge cells
    for(i = 1; i < X-1; i++)
    {
        i0 = grid[i+1][Y-1].state;
        i1 = grid[i+1][Y-2].state;
        i2 = grid[i][Y-2].state;
        i3 = grid[i-1][Y-2].state;
        i4 = grid[i-1][Y-1].state;
        for (j = 0; j < 8; j++)
        {
            grid[i][Y-1].neighborhood[j] = 'X';
        }
        grid[i][Y-1].neighborhood[0] = i0;
        grid[i][Y-1].neighborhood[1] = i1;
        grid[i][Y-1].neighborhood[2] = i2;
        grid[i][Y-1].neighborhood[3] = i3;
        grid[i][Y-1].neighborhood[4] = i4;
    }


    //Updating left-edge cells
    for(i = 1; i < Y-1; i++)
    {
        i0 = grid[1][i].state;
        i1 = grid[1][i-1].state;
        i2 = grid[0][i-1].state;
        i6 = grid[0][i+1].state;
        i7 = grid[1][i+1].state;
        for (j = 0; j < 8; j++)
        {
            grid[0][i].neighborhood[j] = 'X';
        }
        grid[0][i].neighborhood[0] = i0;
        grid[0][i].neighborhood[1] = i1;
        grid[0][i].neighborhood[2] = i2;
        grid[0][i].neighborhood[6] = i6;
        grid[0][i].neighborhood[7] = i7;
    }
    


    //Updating right-edge cells
    for(i = 1; i < Y-1; i++)
    {
        i2 = grid[X-1][i-1].state;
        i3 = grid[X-2][i-1].state;
        i4 = grid[X-2][i].state;
        i5 = grid[X-2][i+1].state;
        i6 = grid[X-1][i+1].state;
        for (j = 0; j < 8; j++)
        {
            grid[X-1][i].neighborhood[j] = 'X';
        }
        grid[X-1][i].neighborhood[2] = i2;
        grid[X-1][i].neighborhood[3] = i3;
        grid[X-1][i].neighborhood[4] = i4;
        grid[X-1][i].neighborhood[5] = i5;
        grid[X-1][i].neighborhood[6] = i6;
    }



    //Updating all remaining center cells
    for(i = 1; i < X-1; i++)
    {
        for(j = 1; j < Y-1; j++)
        {
            grid[i][j].neighborhood[0] = grid[i+1][j].state;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
            grid[i][j].neighborhood[1] = grid[i+1][j-1].state;
            grid[i][j].neighborhood[2] = grid[i][j-1].state;
            grid[i][j].neighborhood[3] = grid[i-1][j-1].state;
            grid[i][j].neighborhood[4] = grid[i-1][j].state;
            grid[i][j].neighborhood[5] = grid[i-1][j+1].state;
            grid[i][j].neighborhood[6] = grid[i][j+1].state;
            grid[i][j].neighborhood[7] = grid[i+1][j+1].state;
            
        }
    }

}



int count_live_neighbors(gridcell gcell)
{
    int i, count = 0;
    for(i = 0; i < 8; i++)
    {
        if(gcell.neighborhood[i] == '1')
            count++;
            // int loop = 0;
            // for(loop = 0; loop < 8; loop++)
            //     printf("%c ", gcell.neighborhood[loop]);
            // printf("\n");
    }

    return count;
}


void print_grid(gridcell** grid, int X, int Y)
{
    // printf("%c\n", grid[9][9].state);
    int i, j;
    // for(i = 0; i < X; i++)
    // {
    //     for(j = 0; j < Y; j++)
    //     {
    //         int k = 0;
    //         for(k = 0; k < 8; k++)
    //         {
    //             printf("%c ", grid[i][j].neighborhood[k]);
    //         }
    //         printf("\n");
    //     }
    // }
    for(i = 0; i < X; i++)
    {
        for(j = 0; j < Y; j++)
        {
            // printf("i = %d\n", i);
            // printf("j = %d\n", j);
            // printf("%c ", grid[i][j].state);
            if(grid[i][j].state == '0')
            {
                printf("0 ");
            }
            else if(grid[i][j].state == '1')
            {
                printf("+ ");
            }
        }
        printf("\n");
    }
}


int calculate_output(gridcell** grid, int X, int Y)
{
    int i, j, output = 0;
    for(i = 0; i < X; i++)
    {
        for(j = 0; j < Y; j++)
        {
            output += count_live_neighbors(grid[i][j]);
            
        }
    }
    // printf("%d ++++++\n", count_live_neighbors(grid[5][5]));
    return output;
}




int main()
{
    gridcell** grid;
    int row_count, col_count, live_cell_count;
    scanf("%d", &row_count);
    scanf("%d", &col_count);
    scanf("%d", &live_cell_count);

    if (row_count > 0 && col_count > 0 && live_cell_count >= 0)
    {
        if (live_cell_count <= (row_count-2) * (col_count-2))
        {
            grid = generate_initial_state(row_count, col_count, live_cell_count, grid);
            update_neighborhood(grid, row_count, col_count);
            int output = calculate_output(grid, row_count, col_count);
            printf("%d\n", output);
            print_grid(grid, row_count, col_count);
        }
        else
            printf("0\n");
            
    }
    else
        printf("0\n");
    return 0;
}