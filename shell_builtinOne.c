#include "inshell.h"

/**
 * inmyhistory - Displays the history list, one command per line, preceded
 *               with line numbers, starting at 0.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 * Return: Always 0
 */
int inmyhistory(info_t *shell_info)
{
	printList(shell_info->inhistory);
	return (0);
}

/**
 * unset_alias - Sets alias to string.
 * @shell_info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *shell_info, char *str)
{
	char *p, c;
	int ret;

	p = shstrchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_nod_at_index(&(shell_info->inalias),
			get_nod_index(shell_info->inalias, nod_strt_with(shell_info->inalias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Sets alias to string.
 * @shell_info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *shell_info, char *str)
{
	char *p;

	p = shstrchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(shell_info, str));

	unset_alias(shell_info, str);
	return (add_nod_end(&(shell_info->inalias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(inlist *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = shstrchr(node->strng, '=');
		for (a = node->strng; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		shputs(p + 1);
		shputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * inmyalias - Mimics the alias builtin (man alias).
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 * Return: Always 0.
 */
int inmyalias(info_t *shell_info)
{
	int i = 0;
	char *p = NULL;
	inlist *node = NULL;

	if (shell_info->inargc == 1)
	{
		node = shell_info->inalias;
		while (node)
		{
			print_alias(node);
			node = node->nxt;
		}
		return (0);
	}
	for (i = 1; shell_info->inargv[i]; i++)
	{
		p = shstrchr(shell_info->inargv[i], '=');
		if (p)
			set_alias(shell_info, shell_info->inargv[i]);
		else
			print_alias(nod_strt_with(shell_info->inalias, shell_info->inargv[i], '='));
	}

	return (0);
}
