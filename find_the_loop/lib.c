#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/* --- helpers fournis par l'énoncé --- */
/* add_nodeint: ajoute en tête */
listint_t *add_nodeint(listint_t **head, const int n)
{
	listint_t *new;

	new = malloc(sizeof(listint_t));
	if (!new)
		return (NULL);

	new->n = n;
	new->next = *head;
	*head = new;

	return (new);
}

/**
 * print_listint_safe - imprime une liste en sécurité (gère les boucles)
 * @head: tête de liste
 *
 * Return: nombre de nœuds imprimés
 *
 * Stratégie:
 * - On trouve le début de boucle avec find_listint_loop.
 * - S'il n'y a pas de boucle: on parcourt et on imprime jusqu'à NULL.
 * - S'il y a une boucle: on imprime les nœuds avant la boucle,
 *   puis tous les nœuds de la boucle une fois, puis on affiche
 *   "-> [adresse_debut] valeur" et on s'arrête.
 */
size_t print_listint_safe(const listint_t *head)
{
	const listint_t *loop, *cur;
	size_t count = 0;

	if (!head)
		return (0);

	loop = find_listint_loop((listint_t *)head);

	/* Pas de boucle: impression linéaire */
	if (loop == NULL)
	{
		for (cur = head; cur; cur = cur->next)
		{
			printf("[%p] %d\n", (void *)cur, cur->n);
			count++;
		}
		return (count);
	}

	/* Imprimer jusqu'au début de la boucle (exclu) */
	for (cur = head; cur != loop; cur = cur->next)
	{
		printf("[%p] %d\n", (void *)cur, cur->n);
		count++;
	}

	/* Imprimer tous les nœuds de la boucle une fois */
	{
		const listint_t *p = loop;

		printf("[%p] %d\n", (void *)p, p->n);
		count++;

		p = p->next;
		while (p != loop)
		{
			printf("[%p] %d\n", (void *)p, p->n);
			count++;
			p = p->next;
		}
		/* flèche vers le début de boucle */
		printf("-> [%p] %d\n", (void *)loop, loop->n);
	}

	return (count);
}

/**
 * free_listint_safe - libère une liste en sécurité (gère les boucles)
 * @h: adresse du pointeur vers la tête
 *
 * Return: nombre de nœuds libérés
 *
 * Stratégie:
 * - Trouver le début de boucle (si présent).
 * - Libérer tous les nœuds avant la boucle.
 * - Puis libérer chaque nœud de la boucle exactement une fois.
 * - Mettre *h à NULL.
 */
size_t free_listint_safe(listint_t **h)
{
	listint_t *loop, *cur, *tmp;
	size_t count = 0;

	if (h == NULL || *h == NULL)
		return (0);

	loop = find_listint_loop(*h);

	/* Pas de boucle: libération linéaire */
	if (loop == NULL)
	{
		cur = *h;
		while (cur)
		{
			tmp = cur->next;
			free(cur);
			cur = tmp;
			count++;
		}
		*h = NULL;
		return (count);
	}

	/* Libérer les nœuds avant la boucle */
	cur = *h;
	while (cur != loop)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
		count++;
	}

	/* Libérer chaque nœud de la boucle une fois */
	{
		listint_t *p = loop->next;

		free(loop);
		count++;

		while (p != loop)
		{
			tmp = p->next;
			free(p);
			p = tmp;
			count++;
		}
	}

	*h = NULL;
	return (count);
}

