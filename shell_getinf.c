#include "inshell.h"

/**
 * clear_inf - Initializes info_t struct.
 * @info: Struct address.
 */
void clear_inf(info_t *info)
{
	info->inarg = NULL;
	info->inargv = NULL;
	info->inpath = NULL;
	info->inargc = 0;
}

/**
 * set_inf - Initializes info_t struct.
 * @info: Struct address.
 * @av: Argument vector.
 */
void set_inf(info_t *info, char **av)
{
	int i = 0;

	info->infname = av[0];
	if (info->inarg)
	{
		info->inargv = str_tow(info->inarg, " \t");
		if (!info->inargv)
		{
			info->inargv = malloc(sizeof(char *) * 2);
			if (info->inargv)
			{
				info->inargv[0] = shstrdup(info->inarg);
				info->inargv[1] = NULL;
			}
		}
		for (i = 0; info->inargv && info->inargv[i]; i++)
			;
		info->inargc = i;

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
	fffree(info->inargv);
	info->inargv = NULL;
	info->inpath = NULL;
	if (all)
	{
		if (!info->incmd_buf)
			free(info->inarg);
		if (info->inenv)
			free_list(&(info->inenv));
		if (info->inhistory)
			free_list(&(info->inhistory));
		if (info->inalias)
			free_list(&(info->inalias));
		fffree(info->inenviron);
		info->inenviron = NULL;
		pfree((void **)info->incmd_buf);
		if (info->inreadfd > 2)
			close(info->inreadfd);
		_putchar(BUF_FLUSH);
	}
}
