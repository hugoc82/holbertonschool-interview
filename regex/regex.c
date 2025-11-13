#include "regex.h"

/**
 * char_matches - Check if a single character matches a pattern character.
 * @s: Character from the string (undefined if string is empty).
 * @p: Character from the pattern (either a literal or '.').
 *
 * Return: 1 if @p matches @s, otherwise 0.
 */
static int char_matches(char s, char p)
{
	if (p == '.')
		return (1);
	return (s == p);
}

/**
 * regex_match - Check if a string matches a simple regex pattern.
 * @str:     The input string to scan (may be empty).
 * @pattern: The pattern, supporting '.' and '*' (may be empty).
 *
 * Description:
 *   Supports:
 *     '.'  -> matches any single character
 *     'x*' -> matches zero or more of the preceding character 'x'
 *
 * Return: 1 if the pattern matches the string, otherwise 0.
 */
int regex_match(char const *str, char const *pattern)
{
	int first_match;

	/* Invalid if pattern begins with '*' (no preceding char to repeat) */
	if (pattern && pattern[0] == '*')
		return (0);

	/* If pattern is empty, it matches only an empty string */
	if (!pattern || pattern[0] == '\0')
		return ((str && str[0] == '\0') ? 1 : 0);

	first_match = (str && str[0] != '\0') && char_matches(str[0], pattern[0]);

	/* Handle 'x*' (zero or more of the preceding character) */
	if (pattern[1] == '*')
	{
		/* Two options:
		 *  1) Skip "x*" entirely (zero occurrences)
		 *  2) If first char matches, consume one char from str and stay on "x*"
		 */
		return (regex_match(str, pattern + 2) ||
			(first_match && regex_match(str + 1, pattern)));
	}

	/* No '*': require current chars to match, then advance both */
	if (first_match)
		return (regex_match(str + 1, pattern + 1));

	return (0);
}

