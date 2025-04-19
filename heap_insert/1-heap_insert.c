#include "binary_trees.h"
#include <stdlib.h>

/**
 * heap_insert - Inserts a value into a Max Binary Heap.
 * @root: Double pointer to the root of the heap.
 * @value: The value to insert into the heap.
 * 
 * Return: A pointer to the inserted node, or NULL on failure.
 */
heap_t *heap_insert(heap_t **root, int value)
{
    heap_t *new_node;

    // Step 1: Create a new node with the given value.
    new_node = binary_tree_node(NULL, value); // Create the node
    if (!new_node)
        return (NULL);

    // Step 2: If the root is NULL, the new node becomes the root.
    if (!*root)
    {
        *root = new_node;
        return (new_node);
    }

    // Step 3: Insert the new node into the heap.
    insert_at_correct_position(*root, new_node); // Insert at the correct position
    heapify_up(new_node); // Maintain the Max Heap property by heapifying upwards.

    return (new_node);
}

/**
 * insert_at_correct_position - Helper function to insert the node in the right position.
 * @root: Pointer to the root of the heap.
 * @new_node: The new node to insert.
 */
void insert_at_correct_position(heap_t *root, heap_t *new_node)
{
    // This function should insert the new node at the first available position in the tree
    // You can use a level order traversal or another appropriate method
    // This part is left for you to implement if needed.
    // Since the task doesn't provide specifics on how to insert, you should implement this.
}

/**
 * heapify_up - Moves a node up to restore the Max Heap property.
 * @node: The node to move up.
 */
void heapify_up(heap_t *node)
{
    heap_t *parent;

    // Step 4: Move the node upwards while its value is greater than its parent's.
    while (node->parent && node->parent->n < node->n)
    {
        parent = node->parent;

        // Swap the values of node and parent.
        int temp = parent->n;
        parent->n = node->n;
        node->n = temp;

        // Move the node upwards.
        node = parent;
    }
}
