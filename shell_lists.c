#include "inshell.h"

/**
 * add_nod - Adds a node to the start of the list.
 * @head: Address of pointer to head node.
 * @str: str field of node.
 * @number: Node index used by history.
 *
 * Return: Size of list.
 */
inlist *add_nod(inlist **head, const char *str, int number)
{
	inlist *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(inlist));
	if (!new_head)
		return (NULL);
	mset((void *)new_head, 0, sizeof(inlist));
	new_head->number = number;
	if (str)
	{
		new_head->strng = shstrdup(str);
		if (!new_head->strng)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->nxt = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_nod_end - Adds a node to the end of the list.
 * @head: Address of pointer to head node.
 * @str: str field of node.
 * @num: Node index used by history.
 *
 * Return: Size of list.
 */
inlist *add_nod_end(inlist **head, const char *str, int num)
{
	inlist *new_nod, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_nod = malloc(sizeof(inlist));
	if (!new_nod)
		return (NULL);
	mset((void *)new_nod, 0, sizeof(inlist));
	new_nod->number = num;
	if (str)
	{
		new_nod->strng = shstrdup(str);
		if (!new_nod->strng)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->nxt)
			node = node->nxt;
		node->nxt = new_nod;
	}
	else
		*head = new_nod;
	return (new_nod);
}

/**
 * printList_str - Prints only the str element of an inlist linked list.
 * @h: Pointer to first node.
 *
 * Return: Size of list.
 */
size_t printList_str(const inlist *h)
{
	size_t i = 0;

	while (h)
	{
		shputs(h->strng ? h->strng : "(nil)");
		shputs("\n");
		h = h->nxt;
		i++;
	}
	return (i);
}

/**
 * delete_nod_at_index - Deletes node at the given index.
 * @head: Address of pointer to first node.
 * @index: Index of node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_nod_at_index(inlist **head, unsigned int index)
{
	inlist *node, *prev_nod;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->nxt;
		free(node->strng);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_nod->nxt = node->nxt;
			free(node->strng);
			free(node);
			return (1);
		}
		i++;
		prev_nod = node;
		node = node->nxt;
	}
	return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of pointer to head node.
 *
 * Return: void.
 */
void free_list(inlist **head_ptr)
{
	inlist *node, *next_nod, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_nod = node->nxt;
		free(node->strng);
		free(node);
		node = next_nod;
	}
	*head_ptr = NULL;
}
