#ifndef REGEX_H
#define REGEX_H

/**
 * regex_match - Check if a string matches a simple regex pattern.
 * @str:     The input string to scan (may be empty).
 * @pattern: The pattern, supporting '.' and '*' (may be empty).
 *
 * Return: 1 if the pattern matches the string, otherwise 0.
 */
int regex_match(char const *str, char const *pattern);

#endif /* REGEX_H */

