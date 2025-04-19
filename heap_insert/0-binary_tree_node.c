#include "binary_trees.h"
#include <stdlib.h>

/**
 * binary_tree_node - Create a binary tree node
 *
 * @parent: Pointer to the parent node of the node to create
 * @value: Value to store in the new node
 * 
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{
    binary_tree_t *node = malloc(sizeof(binary_tree_t));

    if (!node)
        return (NULL);

    node->n = value;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;

    return (node);
}
