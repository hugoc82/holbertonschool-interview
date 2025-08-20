#include <stdlib.h>
#include "binary_trees.h"

/**
 * binary_tree_size - Measures the size of a binary tree.
 * @tree: Pointer to the root node of the tree to measure.
 *
 * Return: Size (number of nodes) in the tree.
 */
static size_t binary_tree_size(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * node_at_index - Returns the node at a given 1-based index if the tree
 *                 is viewed as a complete binary tree in level order.
 * @root: Pointer to root of the heap.
 * @index: 1-based index of the target node.
 *
 * Return: Pointer to the node at @index, or NULL on failure.
 */
static heap_t *node_at_index(heap_t *root, size_t index)
{
	size_t mask;

	if (root == NULL || index == 0)
		return (NULL);

	/* Find highest power of two >= index, then step down ignoring MSB */
	for (mask = 1; mask <= index; mask <<= 1)
		;
	/* mask is now first power of two strictly greater than index */
	for (mask >>= 1; mask > 1; mask >>= 1)
	{
		if (index & mask)
		{
			if (root->right == NULL)
				return (NULL);
			root = root->right;
		}
		else
		{
			if (root->left == NULL)
				return (NULL);
			root = root->left;
		}
	}
	return (root);
}

/**
 * heapify_down - Restores the Max Heap property by sifting a node down.
 * @node: Pointer to the node to sift down from.
 */
static void heapify_down(heap_t *node)
{
	heap_t *largest;
	int tmp;

	if (node == NULL)
		return;

	while (1)
	{
		largest = node;

		if (node->left && node->left->n > largest->n)
			largest = node->left;
		if (node->right && node->right->n > largest->n)
			largest = node->right;

		if (largest == node)
			break;

		tmp = node->n;
		node->n = largest->n;
		largest->n = tmp;

		node = largest;
	}
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap.
 * @root: Double pointer to the root node of the heap.
 *
 * Return: The value stored in the root node; 0 on failure.
 */
int heap_extract(heap_t **root)
{
	size_t size;
	int value;
	heap_t *last, *parent;

	if (root == NULL || *root == NULL)
		return (0);

	value = (*root)->n;
	size = binary_tree_size(*root);

	/* If only one node, free it and clear root */
	if (size == 1)
	{
		free(*root);
		*root = NULL;
		return (value);
	}

	/* Find last node in level-order (index == size) */
	last = node_at_index(*root, size);
	if (last == NULL)
		return (0);

	/* Move last node's value to root */
	(*root)->n = last->n;

	/* Unlink last from its parent */
	parent = last->parent;
	if (parent->left == last)
		parent->left = NULL;
	else
		parent->right = NULL;

	free(last);

	/* Restore heap property */
	heapify_down(*root);

	return (value);
}

