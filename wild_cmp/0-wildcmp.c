/* 0-wildcmp.c */
#include "holberton.h"

/**
 * wildcmp - Compare two strings allowing '*' wildcards in s2.
 * @s1: First string (no wildcards).
 * @s2: Second string (may contain '*', matching any string incl. empty).
 *
 * Return: 1 if the strings can be considered identical, otherwise 0.
 */
int wildcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);

	/* If both end at the same time -> match */
	if (*s2 == '\0')
		return (*s1 == '\0');

	/* Collapse consecutive '*' to avoid redundant recursion */
	if (*s2 == '*')
	{
		while (*s2 == '*')
			s2++;

		/* Trailing '*' matches the rest of s1 */
		if (*s2 == '\0')
			return (1);

		/* Try to match s2 (after *) at each position in s1 */
		while (*s1)
		{
			if (wildcmp(s1, s2))
				return (1);
			s1++;
		}
		return (0);
	}

	/* Regular character must match exactly */
	if (*s1 == *s2 && *s1 != '\0')
		return (wildcmp(s1 + 1, s2 + 1));

	return (0);
}

