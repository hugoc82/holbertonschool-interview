#include <stdio.h>
#include "sandpiles.h"

#define SIZE 3

/**
 * print_grid - Prints a 3x3 grid
 * @grid: The 3x3 grid to print
 */
void print_grid(int grid[3][3])
{
    int i, j;

    printf("=\n");
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (j)
                printf(" ");
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}

/**
 * is_unstable - Checks if the grid is unstable (any value > 3)
 * @grid: 3x3 grid to check
 * Return: 1 if unstable, 0 if stable
 */
int is_unstable(int grid[3][3])
{
    int i, j;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (grid[i][j] > 3)
                return 1;
    return 0;
}

/**
 * topple - Performs one round of toppling on the grid
 * @grid: Grid to update
 */
void topple(int grid[3][3])
{
    int temp[3][3] = {0};
    int i, j;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (grid[i][j] > 3)
            {
                temp[i][j] -= 4;
                if (i > 0)
                    temp[i - 1][j]++;
                if (i < 2)
                    temp[i + 1][j]++;
                if (j > 0)
                    temp[i][j - 1]++;
                if (j < 2)
                    temp[i][j + 1]++;
            }
        }
    }

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            grid[i][j] += temp[i][j];
}

/**
 * sandpiles_sum - Adds two sandpiles and stabilizes the result
 * @grid1: First 3x3 grid (modified in-place to hold result)
 * @grid2: Second 3x3 grid
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
    int i, j;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            grid1[i][j] += grid2[i][j];

    while (is_unstable(grid1))
    {
        print_grid(grid1);
        topple(grid1);
    }
}
