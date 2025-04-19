#include "binary_trees.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * heap_insert - Insert a value into a Max Binary Heap
 *
 * @root: Double pointer to the root node of the Heap
 * @value: Value to insert into the node
 *
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
    heap_t *new_node;

    if (!root)
        return (NULL);

    new_node = binary_tree_node(NULL, value);
    if (!new_node)
        return (NULL);

    if (!*root)
    {
        *root = new_node;
        return (new_node);
    }

    insert_at_correct_position(*root, new_node);
    heapify_up(new_node);

    return (new_node);
}

/**
 * insert_at_correct_position - Insert the new node in the right position
 *
 * @root: Pointer to the root of the heap
 * @new_node: Pointer to the new node to be inserted
 */
void insert_at_correct_position(heap_t *root, heap_t *new_node)
{
    if (root->left == NULL)
        root->left = new_node;
    else if (root->right == NULL)
        root->right = new_node;
    else
    {
        if (root->left->n < root->right->n)
            insert_at_correct_position(root->left, new_node);
        else
            insert_at_correct_position(root->right, new_node);
    }
}

/**
 * heapify_up - Ensure the Max Heap property is maintained
 *
 * @node: The node to start heapifying upwards from
 */
void heapify_up(heap_t *node)
{
    heap_t *parent;

    while (node->parent && node->n > node->parent->n)
    {
        parent = node->parent;

        node->parent = parent->parent;

        if (parent->parent)
        {
            if (parent->parent->left == parent)
                parent->parent->left = node;
            else
                parent->parent->right = node;
        }

        if (parent->left == node)
            parent->left = node->left;
        else
            parent->right = node->right;

        node->left = parent;
        parent->parent = node;
    }
}
