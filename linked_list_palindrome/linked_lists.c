#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * print_listint - prints all elements of a listint_t list
 * @h: pointer to head of list
 * Return: number of nodes
 */
size_t print_listint(const listint_t *h)
{
    unsigned int n = 0;

    while (h != NULL)
    {
        printf("%i\n", h->n);
        h = h->next;
        n++;
    }

    return (n);
}

/**
 * add_nodeint_end - adds a new node at the end of a listint_t list
 * @head: pointer to pointer of first node of list
 * @n: integer to be included in new node
 * Return: address of the new element or NULL if it fails
 */
listint_t *add_nodeint_end(listint_t **head, const int n)
{
    listint_t *new = malloc(sizeof(listint_t));
    listint_t *current;

    if (!new)
        return (NULL);

    new->n = n;
    new->next = NULL;

    if (!*head)
    {
        *head = new;
        return (new);
    }

    current = *head;
    while (current->next)
        current = current->next;

    current->next = new;

    return (new);
}

/**
 * free_listint - frees a listint_t list
 * @head: pointer to list to be freed
 */
void free_listint(listint_t *head)
{
    listint_t *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
