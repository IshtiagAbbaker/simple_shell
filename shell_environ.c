#include "inshell.h"

/**
 * inmyenv - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int inmyenv(info_t *info)
{
	printList_str(info->env);
	return (0);
}

/**
 * ingetenv - Gets the value of an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @env_name: Environment variable name.
 *
 * Return: The value of the environment variable.
 */
char *ingetenv(info_t *info, const char *env_name)
{
	inlist *node = info->env;
	char *p;

	while (node)
	{
		p = strt_with(node->str, env_name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * inmysetenv - Initializes a new environment variable,
 *              or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int inmysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		ineputs("Incorrect number of arguments\n");
		return (1);
	}
	if (insetenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * inmyunsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int inmyunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		ineputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		inunsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populateEnv_list - Populates the environment linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int populateEnv_list(info_t *info)
{
	inlist *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nod_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
