#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>

/**
 * struct skiplist_s - Singly linked list with express lane
 *
 * @n: Integer stored at the node
 * @index: Index of the node in the list
 * @next: Pointer to the next node
 * @express: Pointer to the next node in the express lane
 */
typedef struct skiplist_s
{
	int n;
	size_t index;
	struct skiplist_s *next;
	struct skiplist_s *express;
} skiplist_t;

/* ==== Prototypes ==== */

/* Fonction principale */
skiplist_t *linear_skip(skiplist_t *list, int value);

/* Fonctions utilitaires (ex: skiplist/create_skiplist.c, etc.) */
skiplist_t *create_skiplist(int *array, size_t size);
void free_skiplist(skiplist_t *list);
void print_skiplist(const skiplist_t *list);

#endif /* SEARCH_H */
