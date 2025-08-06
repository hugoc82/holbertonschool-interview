#include "search_algos.h"
#include <stdio.h>

/**
 * print_array - Prints the current subarray
 * @array: The array to print
 * @low: Starting index
 * @high: Ending index
 */
void print_array(int *array, size_t low, size_t high)
{
	size_t i;

	printf("Searching in array: ");
	for (i = low; i <= high; i++)
	{
		printf("%d", array[i]);
		if (i < high)
			printf(", ");
	}
	printf("\n");
}

/**
 * recursive_search - Recursive binary search to find first occurrence
 * @array: The array to search
 * @low: The lower bound index
 * @high: The upper bound index
 * @value: The value to find
 *
 * Return: The index of the first occurrence of value or -1
 */
int recursive_search(int *array, size_t low, size_t high, int value)
{
	size_t mid;

	if (low > high)
		return (-1);

	print_array(array, low, high);

	mid = low + (high - low) / 2;

	if (array[mid] == value)
	{
		if (mid == low || array[mid - 1] != value)
			return ((int)mid);
		else
			return (recursive_search(array, low, mid - 1, value));
	}
	else if (array[mid] < value)
		return (recursive_search(array, mid + 1, high, value));
	else
		return (recursive_search(array, low, mid - 1, value));
}

/**
 * advanced_binary - Searches for a value in a sorted array
 * @array: The array to search
 * @size: The size of the array
 * @value: The value to search for
 *
 * Return: The index where value is located or -1
 */
int advanced_binary(int *array, size_t size, int value)
{
	if (!array || size == 0)
		return (-1);

	return (recursive_search(array, 0, size - 1, value));
}
