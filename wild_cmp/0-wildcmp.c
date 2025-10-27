#include "holberton.h"

/**
 * skip - saute les '*' successifs.
 * @p: index dans s2.
 * Return: adresse du premier caractere autre que '*'.
 */
char *skip(char *p)
{
	if (*p == '*')
		return (skip(p + 1));
	return (p);
}

/**
 * wildcmp - compare s1 avec s2 (seul '*' dans s2 a un sens special).
 * @s1: texte.
 * @s2: motif (avec '*', qui remplace toute suite, meme vide).
 * Return: 1 si equivalentes selon la regle, sinon 0.
 */
int wildcmp(char *s1, char *s2)
{
	if (*s2 == '\0')
		return (*s1 == '\0');

	if (*s2 == '*')
		return (mstar(s1, s2 + 1));

	if (*s1 != '\0' && *s1 == *s2)
		return (wildcmp(s1 + 1, s2 + 1));

	return (0);
}

/**
 * mstar - gere le cas apres un '*'.
 * @s1: position courante dans s1.
 * @s2: position juste apres '*'.
 * Return: 1 si une concordance existe, sinon 0.
 */
int mstar(char *s1, char *s2)
{
	s2 = skip(s2);

	if (*s2 == '\0')
		return (1);

	if (*s1 == '\0')
		return (0);

	if (wildcmp(s1, s2))
		return (1);

	return (mstar(s1 + 1, s2));
}
