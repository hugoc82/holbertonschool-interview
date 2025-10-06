#include "list.h"
#include <stdlib.h>
#include <string.h>

/**
 * create_node - Allocate and initialize a new list node
 * @str: String to duplicate into the node
 *
 * Return: Pointer to the new node on success, or NULL on failure
 */
static List *create_node(const char *str)
{
    List *node;
    char *dup;

    if (str == NULL)
        return (NULL);

    node = malloc(sizeof(*node));
    if (node == NULL)
        return (NULL);

    dup = strdup(str);
    if (dup == NULL)
    {
        free(node);
        return (NULL);
    }

    node->str = dup;
    node->prev = NULL;
    node->next = NULL;

    return (node);
}

/**
 * add_node_end - Add a new node at the end of a double circular linked list
 * @list: Address of the pointer to the head node
 * @str:  String to duplicate into the new node
 *
 * Return: Address of the new node, or NULL on failure
 */
List *add_node_end(List **list, char *str)
{
    List *node, *tail;

    if (list == NULL)
        return (NULL);

    node = create_node(str);
    if (node == NULL)
        return (NULL);

    if (*list == NULL)
    {
        /* First element: points to itself (circular) */
        node->next = node;
        node->prev = node;
        *list = node;
        return (node);
    }

    /* Existing circular list: insert before head, after tail */
    tail = (*list)->prev;
    node->next = *list;
    node->prev = tail;
    tail->next = node;
    (*list)->prev = node;

    return (node);
}

/**
 * add_node_begin - Add a new node at the beginning of a double circular list
 * @list: Address of the pointer to the head node
 * @str:  String to duplicate into the new node
 *
 * Return: Address of the new node, or NULL on failure
 */
List *add_node_begin(List **list, char *str)
{
    List *node, *tail;

    if (list == NULL)
        return (NULL);

    node = create_node(str);
    if (node == NULL)
        return (NULL);

    if (*list == NULL)
    {
        /* First element: points to itself (circular) */
        node->next = node;
        node->prev = node;
        *list = node;
        return (node);
    }

    /* Insert before current head and update head */
    tail = (*list)->prev;
    node->next = *list;
    node->prev = tail;
    tail->next = node;
    (*list)->prev = node;
    *list = node;

    return (node);
}
