#include "binary_trees.h"
#include <limits.h>

/**
 * is_avl_rec - Vérifie récursivement qu'un sous-arbre est un AVL valide,
 *              en contrôlant la propriété BST via des bornes [min, max)
 *              et en calculant la hauteur.
 * @tree: pointeur vers le nœud racine du sous-arbre
 * @min: borne inférieure exclusive autorisée pour tree->n (large pour éviter
 *       les débordements de int ; on utilise long)
 * @max: borne supérieure exclusive autorisée pour tree->n
 * @height: sortie - hauteur du sous-arbre (en nombre de nœuds)
 *
 * Return: 1 si le sous-arbre est AVL, 0 sinon.
 */
static int is_avl_rec(const binary_tree_t *tree, long min, long max,
		      size_t *height)
{
	size_t hl = 0, hr = 0;
	int left_ok, right_ok;
	size_t diff;

	if (!tree)
	{
		*height = 0;
		return (1);
	}

	/* Propriété BST stricte : min < n < max */
	if ((long)tree->n <= min || (long)tree->n >= max)
		return (0);

	/* Vérifier récursivement gauche et droite avec bornes mises à jour */
	left_ok = is_avl_rec(tree->left, min, (long)tree->n, &hl);
	if (!left_ok)
		return (0);

	right_ok = is_avl_rec(tree->right, (long)tree->n, max, &hr);
	if (!right_ok)
		return (0);

	/* Vérifier l'équilibre AVL (écart de hauteur <= 1) */
	diff = (hl > hr) ? (hl - hr) : (hr - hl);
	if (diff > 1)
		return (0);

	/* Hauteur du sous-arbre courant */
	*height = (hl > hr ? hl : hr) + 1;
	return (1);
}

/**
 * binary_tree_is_avl - Vérifie si un arbre binaire est un AVL valide.
 * @tree: pointeur vers la racine de l'arbre à vérifier
 *
 * Return: 1 si l'arbre est un AVL valide, 0 sinon. Si tree est NULL, 0.
 *
 * Notes:
 * - BST stricte: toutes les valeurs du sous-arbre gauche < n,
 *   toutes les valeurs du sous-arbre droit > n (pas de doublons).
 * - Hauteur comptée en nombre de nœuds.
 * - Complexité: O(n) temps, O(h) espace (pile d'appels).
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	size_t h;

	if (!tree)
		return (0);

	return (is_avl_rec(tree, LONG_MIN, LONG_MAX, &h));
}

