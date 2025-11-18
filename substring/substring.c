#include <stdlib.h>
#include <string.h>
#include "substring.h"

/**
 * word_index - return index of word in list, or -1 if not found
 * @word: word to search for
 * @words: array of words
 * @nb_words: number of words in the array
 *
 * Return: index in words, or -1 if not found
 */
static int word_index(const char *word, const char **words, int nb_words)
{
    int i;

    for (i = 0; i < nb_words; i++)
    {
        if (strcmp(word, words[i]) == 0)
            return (i);
    }
    return (-1);
}

/**
 * find_substring - finds all starting indices of substrings in s that are
 *                  concatenation of each word in words exactly once
 * @s: string to scan
 * @words: array of words
 * @nb_words: number of words
 * @n: address where to store number of indices found
 *
 * Return: malloc'd array of indices (size *n), or NULL if no match / error
 */
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
    int len_s, word_len, total_len;
    int *indices = NULL;
    int *word_count = NULL;
    int i, max_start, found = 0;

    if (!s || !words || nb_words <= 0 || !n)
        return (NULL);

    *n = 0;

    word_len = strlen(words[0]);
    if (word_len == 0)
        return (NULL);

    len_s = strlen(s);
    total_len = word_len * nb_words;
    if (len_s < total_len)
        return (NULL);

    /* Count occurrences of each word in the list */
    word_count = malloc(sizeof(int) * nb_words);
    if (!word_count)
        return (NULL);
    for (i = 0; i < nb_words; i++)
        word_count[i] = 0;

    for (i = 0; i < nb_words; i++)
    {
        int j, already = 0;

        /* We must count by index, not by string pointer equality */
        for (j = 0; j < i; j++)
        {
            if (strcmp(words[i], words[j]) == 0)
            {
                word_count[j]++;
                already = 1;
                break;
            }
        }
        if (!already)
            word_count[i]++;
    }

    /* Maximum possible starting positions */
    max_start = len_s - total_len + 1;
    indices = malloc(sizeof(int) * max_start);
    if (!indices)
    {
        free(word_count);
        return (NULL);
    }

    /* Sliding window for each offset modulo word_len */
    for (i = 0; i < word_len; i++)
    {
        int left = i, right = i, count = 0;
        int *seen;
        char *buffer;

        if (i + total_len > len_s)
            break;

        seen = malloc(sizeof(int) * nb_words);
        if (!seen)
        {
            free(indices);
            free(word_count);
            return (NULL);
        }
        for (int k = 0; k < nb_words; k++)
            seen[k] = 0;

        buffer = malloc(sizeof(char) * (word_len + 1));
        if (!buffer)
        {
            free(seen);
            free(indices);
            free(word_count);
            return (NULL);
        }

        while (right + word_len <= len_s)
        {
            int idx, k;

            /* Extract next word from s */
            memcpy(buffer, s + right, word_len);
            buffer[word_len] = '\0';
            idx = word_index(buffer, words, nb_words);

            if (idx == -1 || word_count[idx] == 0)
            {
                /* Not a valid word: reset window */
                for (k = 0; k < nb_words; k++)
                    seen[k] = 0;
                count = 0;
                right += word_len;
                left = right;
                continue;
            }

            /* Add this word to current window */
            seen[idx]++;
            count++;
            right += word_len;

            /* If too many of this word, shrink from the left */
            while (seen[idx] > word_count[idx])
            {
                memcpy(buffer, s + left, word_len);
                buffer[word_len] = '\0';
                k = word_index(buffer, words, nb_words);
                if (k != -1)
                {
                    seen[k]--;
                    count--;
                }
                left += word_len;
            }

            /* If window has all words, record starting index */
            if (count == nb_words)
            {
                indices[found++] = left;

                /* Move left by one word to look for next window */
                memcpy(buffer, s + left, word_len);
                buffer[word_len] = '\0';
                k = word_index(buffer, words, nb_words);
                if (k != -1)
                {
                    seen[k]--;
                    count--;
                }
                left += word_len;
            }
        }

        free(seen);
        free(buffer);
    }

    free(word_count);

    if (found == 0)
    {
        free(indices);
        return (NULL);
    }

    *n = found;
    return (indices);
}

