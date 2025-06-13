#include "slide_line.h"

/**
 * merge_left - Merges values to the left, 2048-style
 * @line: The array to modify
 * @size: Number of elements in array
 */
void merge_left(int *line, size_t size)
{
	size_t i, j;
	int temp[size];
	size_t index = 0;

	/* Step 1: Compress non-zero elements to the left */
	for (i = 0; i < size; i++)
	{
		if (line[i] != 0)
			temp[index++] = line[i];
	}
	while (index < size)
		temp[index++] = 0;

	/* Step 2: Merge and compress again */
	for (i = 0; i < size - 1; i++)
	{
		if (temp[i] != 0 && temp[i] == temp[i + 1])
		{
			temp[i] *= 2;
			temp[i + 1] = 0;
		}
	}

	/* Final compress */
	index = 0;
	for (i = 0; i < size; i++)
	{
		if (temp[i] != 0)
			line[index++] = temp[i];
	}
	while (index < size)
		line[index++] = 0;
}

/**
 * merge_right - Merges values to the right, 2048-style
 * @line: The array to modify
 * @size: Number of elements in array
 */
void merge_right(int *line, size_t size)
{
	size_t i, j;
	int temp[size];
	size_t index = size;

	/* Step 1: Compress non-zero elements to the right */
	for (i = size; i-- > 0;)
	{
		if (line[i] != 0)
			temp[--index] = line[i];
	}
	while (index > 0)
		temp[--index] = 0;

	/* Step 2: Merge and compress again */
	for (i = size - 1; i > 0; i--)
	{
		if (temp[i] != 0 && temp[i] == temp[i - 1])
		{
			temp[i] *= 2;
			temp[i - 1] = 0;
		}
	}

	/* Final compress */
	index = size;
	for (i = size; i-- > 0;)
	{
		if (temp[i] != 0)
			line[--index] = temp[i];
	}
	while (index > 0)
		line[--index] = 0;
}

/**
 * slide_line - Slides and merges a line like the 2048 game
 * @line: Pointer to array of integers
 * @size: Size of the array
 * @direction: SLIDE_LEFT or SLIDE_RIGHT
 *
 * Return: 1 on success, 0 on failure
 */
int slide_line(int *line, size_t size, int direction)
{
	if (!line || size == 0)
		return (0);

	if (direction == SLIDE_LEFT)
		merge_left(line, size);
	else if (direction == SLIDE_RIGHT)
		merge_right(line, size);
	else
		return (0);

	return (1);
}
