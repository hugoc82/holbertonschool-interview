#include "sort.h"
#include <stdlib.h>

/**
 * max_value - Get maximum value in array
 * @array: pointer to array
 * @size: size of array
 * Return: max value (>= 0), or 0 if size == 0
 */
static int max_value(const int *array, size_t size)
{
    size_t i;
    int max;

    if (!array || size == 0)
        return (0);

    max = array[0];
    for (i = 1; i < size; i++)
        if (array[i] > max)
            max = array[i];
    return (max);
}

/**
 * counting_sort_exp - Stable counting sort by digit (exp)
 * @array: array to sort (in place)
 * @size: size of array
 * @exp: 10^k (current digit)
 */
static void counting_sort_exp(int *array, size_t size, int exp)
{
    int count[10] = {0};
    int *out;
    size_t i;

    out = malloc(sizeof(*out) * size);
    if (!out)
        return;

    for (i = 0; i < size; i++)
        count[(array[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = size; i > 0; i--)
    {
        int d = (array[i - 1] / exp) % 10;

        out[count[d] - 1] = array[i - 1];
        count[d]--;
    }

    for (i = 0; i < size; i++)
        array[i] = out[i];

    free(out);
}

/**
 * radix_sort - Sort array of non-negative ints with LSD Radix Sort (base 10)
 * @array: pointer to array
 * @size: number of elements
 */
void radix_sort(int *array, size_t size)
{
    int max, exp;

    if (!array || size < 2)
        return;

    max = max_value(array, size);
    for (exp = 1; max / exp > 0; exp *= 10)
    {
        counting_sort_exp(array, size, exp);
        print_array(array, size);
    }
}
