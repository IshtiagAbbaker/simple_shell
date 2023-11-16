#include "inshell.h"

/**
 * inhsh - main shell loop
 * @ininf: the parameter & return ininf struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int inhsh(ininfo_t *ininf, char **av)
{
	ssize_t inr = 0;
	int builin_rt = 0;

	while (r != -1 && builin_rt != -2)
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
		free_ininfo(ininf, 0);
	}
	writeHistory(ininf);
	free_ininfo(ininf, 1);
	if (!interact(ininf) && ininf->status)
		exit(ininf->status);
	if (builin_rt == -2)
	{
		if (ininf->err_num == -1)
			exit(ininf->status);
		exit(ininf->err_num);
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
int fd_builin(ininfo_t *ininfo)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
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

	for (i = 0; builtintbl[i].type; i++)
		if (shstrcmp(ininfo->argv[0], builtintbl[i].type) == 0)
		{
			ininfo->line_count++;
			built_in_ret = builtintbl[i].func(ininfo);
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
void fd_command(ininfo_t *ininfo)
{
	char *path = NULL;
	int i, k;

	ininfo->path = ininfo->argv[0];
	if (ininfo->linecount_flag == 1)
	{
		ininfo->line_count++;
		ininfo->linecount_flag = 0;
	}
	for (i = 0, k = 0; ininfo->arg[i]; i++)
		if (!ist_delim(ininfo->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = fd_path(ininfo, ingetenv(ininfo, "PATH="), ininfo->argv[0]);
	if (path)
	{
		ininfo->path = path;
		fork_command(ininfo);
	}
	else
	{
		if ((interact(ininfo) || ingetenv(ininfo, "PATH=")
			|| ininfo->argv[0][0] == '/') && is_command(ininfo, ininfo->argv[0]))
			fork_command(ininfo);
		else if (*(ininfo->arg) != '\n')
		{
			ininfo->status = 127;
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
void fork_command(ininfo_t *ininfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(ininfo->path, ininfo->argv, getEnviron(ininfo)) == -1)
		{
			free_ininfo(ininfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(ininfo->status));
		if (WIFEXITED(ininfo->status))
		{
			ininfo->status = WEXITSTATUS(ininfo->status);
			if (ininfo->status == 126)
			printError(ininfo, "Permission denied\n");
		}
	}
}

