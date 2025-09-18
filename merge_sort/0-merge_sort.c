#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * merge - Merge two sorted subarrays into one sorted array
 * @array: The original array
 * @temp: Temporary array used for merging
 * @left: Starting index of the left subarray
 * @mid: Middle index (end of left subarray, start of right)
 * @right: Ending index (exclusive)
 *
 * Description: Prints the left and right parts being merged,
 * then the result after merging.
 */
void merge(int *array, int *temp, size_t left, size_t mid, size_t right)
{
	size_t i = left, j = mid, k = left, l;

	printf("Merging...\n[left]: ");
	print_array(array + left, mid - left);

	printf("[right]: ");
	print_array(array + mid, right - mid);

	while (i < mid && j < right)
	{
		if (array[i] <= array[j])
			temp[k++] = array[i++];
		else
			temp[k++] = array[j++];
	}
	while (i < mid)
		temp[k++] = array[i++];
	while (j < right)
		temp[k++] = array[j++];

	for (l = left; l < right; l++)
		array[l] = temp[l];

	printf("[Done]: ");
	print_array(array + left, right - left);
}

/**
 * merge_sort_recursive - Recursively apply merge sort
 * @array: Array to sort
 * @temp: Temporary array used for merging
 * @left: Starting index
 * @right: Ending index (exclusive)
 */
void merge_sort_recursive(int *array, int *temp, size_t left, size_t right)
{
	size_t mid;

	if (right - left < 2)
		return;

	mid = (left + right) / 2;

	merge_sort_recursive(array, temp, left, mid);
	merge_sort_recursive(array, temp, mid, right);

	merge(array, temp, left, mid, right);
}

/**
 * merge_sort - Sorts an array of integers in ascending order using Merge Sort
 * @array: Array to sort
 * @size: Number of elements in @array
 */
void merge_sort(int *array, size_t size)
{
	int *temp;

	if (!array || size < 2)
		return;

	temp = malloc(sizeof(int) * size);
	if (!temp)
		return;

	merge_sort_recursive(array, temp, 0, size);

	free(temp);
}

