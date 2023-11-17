#include "inshell.h"

/**
 * inis_chain - Tests if the current char in the buffer is a chain delimiter.
 * @info: The parameter struct.
 * @buf: The char buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int inis_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->incmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->incmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->incmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkChain - Checks if we should continue chaining based on the last status.
 * @info: The parameter struct.
 * @buf: The char buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->incmd_buf_type == CMD_AND)
	{
		if (info->instatus)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->incmd_buf_type == CMD_OR)
	{
		if (!info->instatus)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replaceAlias - Replaces an alias in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replaceAlias(info_t *info)
{
	int i;
	inlist *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nod_strt_with(info->inalias, info->inargv[0], '=');
		if (!node)
			return (0);
		free(info->inargv[0]);
		p = shstrchr(node->strng, '=');
		if (!p)
			return (0);
		p = shstrdup(p + 1);
		if (!p)
			return (0);
		info->inargv[0] = p;
	}
	return (1);
}

/**
 * replaceVars - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replaceVars(info_t *info)
{
	int i = 0;
	inlist *node;

	for (i = 0; info->inargv[i]; i++)
	{
		if (info->inargv[i][0] != '$' || !info->inargv[i][1])
			continue;

		if (!shstrcmp(info->inargv[i], "$?"))
		{
			replaceString(&(info->inargv[i]),
				shstrdup(convertNumber(info->instatus, 10, 0)));
			continue;
		}
		if (!shstrcmp(info->inargv[i], "$$"))
		{
			replaceString(&(info->inargv[i]),
				shstrdup(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = nod_strt_with(info->inenv, &info->inargv[i][1], '=');
		if (node)
		{
			replaceString(&(info->inargv[i]),
				shstrdup(shstrchr(node->strng, '=') + 1));
			continue;
		}
		replaceString(&info->inargv[i], shstrdup(""));
	}
	return (0);
}

/**
 * replaceString - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
