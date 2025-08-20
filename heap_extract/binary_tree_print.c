#include <stdio.h>
#include <stdlib.h>
#include "binary_trees.h"

/* Fonction d’affichage d’un arbre binaire (ne pas modifier) */
static int print_t(const binary_tree_t *tree, int offset, int depth, char s[20][255])
{
	char b[6];
	int width, left, right, is_left, i;

	if (!tree)
		return (0);
	is_left = (tree->parent && tree->parent->left == tree);
	width = sprintf(b, "(%03d)", tree->n);
	left = print_t(tree->left, offset, depth + 1, s);
	right = print_t(tree->right, offset + left + width, depth + 1, s);

	for (i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];
	if (depth && is_left)
	{
		for (i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width/2 + i] = '-';
		s[depth - 1][offset + left + width/2] = '.';
	}
	else if (depth && !is_left)
	{
		for (i = 0; i < left + width; i++)
			s[depth - 1][offset - width/2 + i] = '-';
		s[depth - 1][offset + left + width/2] = '.';
	}
	return (left + width + right);
}

void binary_tree_print(const binary_tree_t *tree)
{
	char s[20][255];
	int i;

	for (i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");

	print_t(tree, 0, 0, s);

	for (i = 0; i < 20; i++)
	{
		if (s[i][0] != ' ')
			printf("%s\n", s[i]);
	}
}

