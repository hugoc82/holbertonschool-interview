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

skiplist_t *linear_skip(skiplist_t *list, int value);

#endif /* SEARCH_H */

