#include "inshell.h"

/**
 * inhsh - main shell loop
 * @ininf: the parameter & return ininf struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int inhsh(info_t *ininf, char **av)
{
	ssize_t inr = 0;
	int builin_rt = 0;

	while (inr != -1 && builin_rt != -2)
	{
		clear_ininfo(ininf);
		if (interact(ininf))
			shputs("$ ");
		inputchar(BUF_FLUSH);
		inr = get_input(ininf);
		if (inr != -1)
		{
			set_ininfo(ininf, av);
			builin_rt = fd_builin(ininf);
			if (builin_rt == -1)
				fd_command(ininf);
		}
		else if (interact(ininf))
			_putchar('\n');
		free_inf(ininf, 0);
	}
	writeHistory(ininf);
	free_inf(ininf, 1);
	if (!interact(ininf) && ininf->instatus)
		exit(ininf->instatus);
	if (builin_rt == -2)
	{
		if (ininf->inerr_num == -1)
			exit(ininf->instatus);
		exit(ininf->inerr_num);
	}
	return (builin_rt);
}

/**
 * fd_builin - finds a builtin command
 * @ininfo: the parameter & return ininfo struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int fd_builin(info_t *ininfo)
{
	int i, built_in_ret = -1;
	builtin_t builtintbl[] = {
		{"exit", inmyexit},
		{"env", inmyenv},
		{"help", inmyhelp},
		{"history", inmyhistory},
		{"setenv", inmysetenv},
		{"unsetenv", inmyunsetenv},
		{"cd", inmycd},
		{"alias", inmyalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].typeo; i++)
		if (shstrcmp(ininfo->inargv[0], builtintbl[i].typeo) == 0)
		{
			ininfo->inline_count++;
			built_in_ret = builtintbl[i].fun(ininfo);
			break;
		}
	return (built_in_ret);
}

/**
 * fd_command - finds a command in PATH
 * @ininfo: the parameter & return ininfo struct
 *
 * Return: void
 */
void fd_command(info_t *ininfo)
{
	char *inpath = NULL;
	int i, k;

	ininfo->inpath = ininfo->inargv[0];
	if (ininfo->inlinecount_flag == 1)
	{
		ininfo->inline_count++;
		ininfo->inlinecount_flag = 0;
	}
	for (i = 0, k = 0; ininfo->inarg[i]; i++)
		if (!ist_delim(ininfo->inarg[i], " \t\n"))
			k++;
	if (!k)
		return;

	inpath = fd_path(ininfo, ingetenv(ininfo, "PATH="), ininfo->inargv[0]);
	if (inpath)
	{
		ininfo->inpath = inpath;
		fork_command(ininfo);
	}
	else
	{
		if ((interact(ininfo) || ingetenv(ininfo, "PATH=")
			|| ininfo->inargv[0][0] == '/') && is_command(ininfo, ininfo->inargv[0]))
			fork_command(ininfo);
		else if (*(ininfo->inarg) != '\n')
		{
			ininfo->instatus = 127;
			printError(ininfo, "not found\n");
		}
	}
}

/**
 * fork_command - forks a an exec thread to run cmd
 * @ininfo: the parameter & return ininfo struct
 *
 * Return: void
 */
void fork_command(info_t *ininfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(ininfo->inpath, ininfo->inargv, getEnviron(ininfo)) == -1)
		{
			free_inf(ininfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(ininfo->instatus));
		if (WIFEXITED(ininfo->instatus))
		{
			ininfo->instatus = WEXITSTATUS(ininfo->instatus);
			if (ininfo->instatus == 126)
			printError(ininfo, "Permission denied\n");
		}
	}
}

