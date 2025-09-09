#include "lists.h"

/**
 * find_listint_loop - Finds the start node of a loop in a linked list.
 * @head: Pointer to the head of the list.
 *
 * Return: Address of the node where the loop starts, or NULL if no loop.
 */
listint_t *find_listint_loop(listint_t *head)
{
	listint_t *slow, *fast;

	if (head == NULL || head->next == NULL)
		return (NULL);

	slow = head;
	fast = head;

	/* Phase 1: Detect loop */
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast)
			break;
	}

	/* No loop found */
	if (fast == NULL || fast->next == NULL)
		return (NULL);

	/* Phase 2: Find start of loop */
	slow = head;
	while (slow != fast)
	{
		slow = slow->next;
		fast = fast->next;
	}

	return (slow);
}

