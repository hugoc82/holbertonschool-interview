#include "sort.h"

/**
 * swap - échange deux entiers
 * @a: pointeur vers le premier entier
 * @b: pointeur vers le second entier
 */
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * sift_down - réorganise le tas à partir d'un nœud donné
 * @array: tableau à trier
 * @size: taille totale du tableau
 * @n: taille actuelle du tas
 * @i: index du nœud courant
 */
void sift_down(int *array, size_t size, size_t n, size_t i)
{
	size_t largest = i;
	size_t left = 2 * i + 1;
	size_t right = 2 * i + 2;

	if (left < n && array[left] > array[largest])
		largest = left;
	if (right < n && array[right] > array[largest])
		largest = right;
	if (largest != i)
	{
		swap(&array[i], &array[largest]);
		print_array(array, size);
		sift_down(array, size, n, largest);
	}
}

/**
 * heap_sort - trie un tableau d'entiers par ordre croissant en utilisant
 * l'algorithme du tri par tas (heap sort)
 * @array: tableau d'entiers à trier
 * @size: taille du tableau
 */
void heap_sort(int *array, size_t size)
{
	int i;

	if (!array || size < 2)
		return;

	/* Construire un tas max (heapify) */
	for (i = (int)(size / 2) - 1; i >= 0; i--)
		sift_down(array, size, size, (size_t)i);

	/* Extraire les éléments un par un du tas */
	for (i = (int)size - 1; i > 0; i--)
	{
		swap(&array[0], &array[i]);
		print_array(array, size);
		sift_down(array, size, (size_t)i, 0);
	}
}
