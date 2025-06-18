#include <stdio.h>
#include <math.h>
#include "menger.h"

/**
 * is_hole - Determines if the position should be a hole
 * @row: Row index
 * @col: Column index
 *
 * Return: 1 if it's a hole, 0 otherwise
 */
int is_hole(int row, int col)
{
	while (row > 0 || col > 0)
	{
		if (row % 3 == 1 && col % 3 == 1)
			return (1);
		row /= 3;
		col /= 3;
	}
	return (0);
}

/**
 * menger - Draws a 2D Menger Sponge of a given level
 * @level: The level of the sponge
 */
void menger(int level)
{
	int size, row, col;

	if (level < 0)
		return;

	size = pow(3, level);

	for (row = 0; row < size; row++)
	{
		for (col = 0; col < size; col++)
		{
			if (is_hole(row, col))
				printf(" ");
			else
				printf("#");
		}
		printf("\n");
	}
}
