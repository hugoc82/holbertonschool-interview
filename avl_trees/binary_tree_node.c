#include "binary_trees.h"
#include <stdlib.h>

/**
 * binary_tree_node - Crée un nouveau nœud d'arbre binaire
 * @parent: pointeur vers le parent
 * @value: valeur à stocker
 * Return: pointeur vers le nouveau nœud ou NULL en cas d'échec
 */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{
	binary_tree_t *node = malloc(sizeof(*node));

	if (!node)
		return (NULL);

	node->n = value;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;

	return (node);
}

