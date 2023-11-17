#include "inshell.h"

/**
 * getEnviron - Returns the string array copy of our environ.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
char **getEnviron(info_t *info)
{
	if (!info->inenviron || info->inenv_changed)
	{
		info->inenviron = list_to_strings(info->inenv);
		info->inenv_changed = 0;
	}

	return (info->inenviron);
}

/**
 * inunsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 1 on delete, 0 otherwise.
 * @envVar: The string environment variable property.
 */
int inunsetenv(info_t *info, char *envVar)
{
	inlist *node = info->inenv;
	size_t index = 0;
	char *p;

	if (!node || !envVar)
		return (0);

	while (node)
	{
		p = strt_with(node->strng, envVar);
		if (p && *p == '=')
		{
			info->inenv_changed = delete_nod_at_index(&(info->inenv), index);
			index = 0;
			node = info->inenv;
			continue;
		}
		node = node->nxt;
		index++;
	}
	return (info->inenv_changed);
}

/**
 * insetenv - Initialize a new environment variable,
 *            or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @envVar: The string environment variable property.
 * @value: The string environment variable value.
 * Return: Always 0.
 */
int insetenv(info_t *info, char *envVar, char *value)
{
	char *buf = NULL;
	inlist *node;
	char *p;

	if (!envVar || !value)
		return (0);

	buf = malloc(shstrlen(envVar) + shstrlen(value) + 2);
	if (!buf)
		return (1);
	shstrcpy(buf, envVar);
	shstrcat(buf, "=");
	shstrcat(buf, value);
	node = info->inenv;
	while (node)
	{
		p = strt_with(node->strng, envVar);
		if (p && *p == '=')
		{
			free(node->strng);
			node->strng = buf;
			info->inenv_changed = 1;
			return (0);
		}
		node = node->nxt;
	}
	add_nod_end(&(info->inenv), buf, 0);
	free(buf);
	info->inenv_changed = 1;
	return (0);
}
