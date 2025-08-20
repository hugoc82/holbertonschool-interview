#include <stdlib.h>
#include "binary_trees.h"

/**
 * binary_tree_size - Calcule le nombre de noeuds d'un arbre binaire.
 * @tree: Pointeur vers la racine.
 * Return: Taille de l'arbre.
 */
static size_t binary_tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);
	return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * node_at_index - Retourne le noeud à l'index 1-based donné (parcours niveau).
 * Utilise la représentation tableau d'un tas complet : on lit les bits de
 * l'index (sans le MSB) du plus grand au plus petit jusqu'au bit 1 inclus.
 * 0 => gauche, 1 => droite.
 * @root: Racine du tas.
 * @index: Index 1-based du noeud désiré.
 * Return: Pointeur vers le noeud ou NULL si un maillon manque.
 */
static heap_t *node_at_index(heap_t *root, size_t index)
{
	size_t msb, mask;

	if (!root || index == 0)
		return (NULL);

	/* Trouver le MSB (plus grande puissance de 2 <= index) */
	msb = 1;
	while ((msb << 1) <= index)
		msb <<= 1;

	/* Parcourir tous les bits en dessous du MSB, jusqu'à mask == 1 inclus */
	for (mask = msb >> 1; mask >= 1; mask >>= 1)
	{
		if (index & mask)
		{
			if (!root->right)
				return (NULL);
			root = root->right;
		}
		else
		{
			if (!root->left)
				return (NULL);
			root = root->left;
		}
		if (mask == 1) /* éviter boucle infinie sur size_t */
			break;
	}
	return (root);
}

/**
 * heapify_down - Restaure la propriété max-heap à partir de node vers le bas.
 * @node: Noeud de départ.
 */
static void heapify_down(heap_t *node)
{
	heap_t *big;
	int tmp;

	if (!node)
		return;

	for (;;)
	{
		big = node;
		if (node->left && node->left->n > big->n)
			big = node->left;
		if (node->right && node->right->n > big->n)
			big = node->right;

		if (big == node)
			break;

		tmp = node->n;
		node->n = big->n;
		big->n = tmp;
		node = big;
	}
}

/**
 * heap_extract - Extrait la racine d'un tas binaire max.
 * Remplace la racine par le dernier noeud en parcours niveau, libère ce dernier,
 * puis réorganise le tas si nécessaire.
 * @root: Double pointeur vers la racine du tas.
 * Return: Valeur extraite, ou 0 en cas d'échec.
 */
int heap_extract(heap_t **root)
{
	size_t size;
	int value;
	heap_t *last, *parent;

	if (!root || !*root)
		return (0);

	value = (*root)->n;
	size = binary_tree_size(*root);

	/* Cas 1: un seul noeud */
	if (size == 1)
	{
		free(*root);
		*root = NULL;
		return (value);
	}

	/* Récupérer le dernier noeud (index == size) */
	last = node_at_index(*root, size);
	if (!last)
		return (0); /* sécurité: arbre non complet/incohérent */

	/* Copier la valeur du dernier noeud à la racine, puis détacher/ free last */
	(*root)->n = last->n;

	parent = last->parent;
	if (parent->left == last)
		parent->left = NULL;
	else
		parent->right = NULL;

	free(last);

	/* Rétablir la propriété de tas */
	heapify_down(*root);

	return (value);
}

