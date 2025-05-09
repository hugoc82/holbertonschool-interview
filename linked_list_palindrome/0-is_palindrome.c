#include "lists.h"

/**
 * is_palindrome - checks if a singly linked list is a palindrome
 * @head: double pointer to head of the list
 * Return: 1 if palindrome, 0 otherwise
 */
int is_palindrome(listint_t **head)
{
    listint_t *slow = *head, *fast = *head;
    listint_t *prev = NULL, *next, *left, *right;

    if (*head == NULL || (*head)->next == NULL)
        return (1);

    while (fast && fast->next)
    {
        fast = fast->next->next;

        next = slow->next;
        slow->next = prev;
        prev = slow;
        slow = next;
    }

    if (fast)
        slow = slow->next;

    left = prev;
    right = slow;
    while (left && right)
    {
        if (left->n != right->n)
            return (0);
        left = left->next;
        right = right->next;
    }

    return (1);
}
