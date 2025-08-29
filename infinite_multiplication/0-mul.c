#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * is_digit - check if string contains only digits
 * @s: string
 * Return: 1 if all digits, 0 otherwise
 */
int is_digit(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

/**
 * errors - handle errors and exit
 */
void errors(void)
{
    printf("Error\n");
    exit(98);
}

/**
 * main - multiplies two positive numbers
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: always 0
 */
int main(int argc, char *argv[])
{
    char *num1, *num2;
    int len1, len2, len, i, j, carry, n1, n2, *result;
    int start = 0;

    if (argc != 3)
        errors();
    num1 = argv[1], num2 = argv[2];
    if (!is_digit(num1) || !is_digit(num2))
        errors();
    len1 = strlen(num1);
    len2 = strlen(num2);
    len = len1 + len2;
    result = calloc(len, sizeof(int));
    if (!result)
        return (1);
    for (i = len1 - 1; i >= 0; i--)
    {
        n1 = num1[i] - '0';
        carry = 0;
        for (j = len2 - 1; j >= 0; j--)
        {
            n2 = num2[j] - '0';
            carry += result[i + j + 1] + (n1 * n2);
            result[i + j + 1] = carry % 10;
            carry /= 10;
        }
        result[i + j + 1] += carry;
    }
    while (start < len && result[start] == 0)
        start++;
    if (start == len)
        _putchar('0');
    for (i = start; i < len; i++)
        _putchar(result[i] + '0');
    _putchar('\n');
    free(result);
    return (0);
}

