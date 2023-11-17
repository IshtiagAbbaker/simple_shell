#include "inshell.h"

/**
 * inmyexit - Exits the shell.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 * Return: Exits with a given exit status (0) if shell_info.inargv[0] != "exit".
 */
int inmyexit(info_t *shell_info)
{
	int exit_check;

	if (shell_info->inargv[1])
	{
		exit_check = inerratoi(shell_info->inargv[1]);
		if (exit_check == -1)
		{
			shell_info->instatus = 2;
			printError(shell_info, "Illegal number:");
			ineputs(shell_info->inargv[1]);
			inputchar('\n');
			return (1);
		}
		shell_info->inerr_num = inerratoi(shell_info->inargv[1]);
		return (-2);
	}
	shell_info->inerr_num = -1;
	return (-2);
}

/**
 * inmycd - Changes the current directory of the process.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 * Return: Always 0.
 */
int inmycd(info_t *shell_info)
{
	char *current_directory, *dir, buffer[1024];
	int chdir_ret;

	current_directory = getcwd(buffer, 1024);
	if (!current_directory)
		shputs("TODO: >>getcwd failure emsg here<<\n");

	if (!shell_info->inargv[1])
	{
		dir = ingetenv(shell_info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = ingetenv(shell_info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (shstrcmp(shell_info->inargv[1], "-") == 0)
	{
		if (!ingetenv(shell_info, "OLDPWD="))
		{
			shputs(current_directory);
			_putchar('\n');
			return (1);
		}
		shputs(ingetenv(shell_info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = ingetenv(shell_info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(shell_info->inargv[1]);

	if (chdir_ret == -1)
	{
		printError(shell_info, "can't cd to ");
		ineputs(shell_info->inargv[1]), inputchar('\n');
	}
	else
	{
		insetenv(shell_info, "OLDPWD", ingetenv(shell_info, "PWD="));
		insetenv(shell_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * inmyhelp - Displays help message. Function not yet implemented.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 * Return: Always 0.
 */
int inmyhelp(info_t *shell_info)
{
	char **arg_array;

	arg_array = shell_info->inargv;
	shputs("help call works. Function not yet implemented \n");
	if (0)
		shputs(*arg_array);
	return (0);
}
