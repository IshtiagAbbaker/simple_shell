#include "inshell.h"

/**
 * clear_inf - Initializes info_t struct.
 * @info: Struct address.
 */
void clear_inf(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_inf - Initializes info_t struct.
 * @info: Struct address.
 * @av: Argument vector.
 */
void set_inf(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_tow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = shstrdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAlias(info);
		replaceVars(info);
	}
}

/**
 * free_inf - Frees info_t struct fields.
 * @info: Struct address.
 * @all: True if freeing all fields.
 */
void free_inf(info_t *info, int all)
{
	fffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		fffree(info->environ);
		info->environ = NULL;
		pfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
