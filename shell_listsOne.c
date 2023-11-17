#include "inshell.h"

/**
 * list_len - Determines length of linked list.
 * @h: Pointer to first node.
 *
 * Return: Size of list.
 */
size_t list_len(const inlist *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->nxt;
		i++;
	}
	return (i);
}

/**
 * inlist_to_strings - Returns an array of strings of the list->str.
 * @head: Pointer to first node.
 *
 * Return: Array of strings.
 */
char **inlist_to_strings(inlist *head)
{
	inlist *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->nxt, i++)
	{
		str = malloc(shstrlen(node->strng) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = shstrcpy(str, node->strng);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * printList - Prints all elements of an inlist linked list.
 * @h: Pointer to first node.
 *
 * Return: Size of list.
 */
size_t printList(const inlist *h)
{
	size_t i = 0;

	while (h)
	{
		shputs(convertNumber(h->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		shputs(h->strng ? h->strng : "(nil)");
		shputs("\n");
		h = h->nxt;
		i++;
	}
	return (i);
}

/**
 * nod_strt_with - Returns node whose string starts with prefix.
 * @node: Pointer to list head.
 * @prefix: String to match.
 * @c: The next character after prefix to match.
 *
 * Return: Matched node or null.
 */
inlist *nod_strt_with(inlist *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = strt_with(node->strng, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->nxt;
	}
	return (NULL);
}

/**
 * get_nod_index - Gets the index of a node.
 * @head: Pointer to list head.
 * @node: Pointer to the node.
 *
 * Return: Index of node or -1.
 */
ssize_t get_nod_index(inlist *head, inlist *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->nxt;
		i++;
	}
	return (-1);
}
