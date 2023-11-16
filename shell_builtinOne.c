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
	printList(shell_info->history);
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
	ret = delete_nod_at_index(&(shell_info->alias),
			get_nod_index(shell_info->alias, nod_strt_with(shell_info->alias, str, -1)));
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
	return (add_nod_end(&(shell_info->alias), str, 0) == NULL);
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
		p = shstrchr(node->str, '=');
		for (a = node->str; a <= p; a++)
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

	if (shell_info->argc == 1)
	{
		node = shell_info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; shell_info->argv[i]; i++)
	{
		p = shstrchr(shell_info->argv[i], '=');
		if (p)
			set_alias(shell_info, shell_info->argv[i]);
		else
			print_alias(nod_strt_with(shell_info->alias, shell_info->argv[i], '='));
	}

	return (0);
}
