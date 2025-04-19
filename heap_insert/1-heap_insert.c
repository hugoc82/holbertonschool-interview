#include "binary_trees.h"
#include <stdlib.h>

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * @value: Value to store in the new node
 * 
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
    heap_t *new_node;

    if (root == NULL)
        return (NULL);

    new_node = binary_tree_node(NULL, value);  // Create the new node
    if (new_node == NULL)
        return (NULL);

    // If the heap is empty, the new node becomes the root
    if (*root == NULL)
    {
        *root = new_node;
        return (new_node);
    }

    // Otherwise, insert the new node in the correct position (bottom-left)
    // Note: This part assumes a simple binary tree structure without balancing for now.
    // You'll need to write the logic for heap property (max heap ordering) after insertion.

    return (new_node);
}
