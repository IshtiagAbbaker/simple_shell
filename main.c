#include "shell.h"

/**
 * main - entry point
 * @arg_count: arg count
 * @arg_vec: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_count, char **arg_vec)
{
	info_t information[] = { INFO_INIT };
	int file_d = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_d)
		: "r" (file_d));

	if (arg_count == 2)
	{
		file_d = open(arg_vec[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				ineputs(arg_vec[0]);
				ineputs(": 0: Can't open ");
				ineputs(arg_vec[1]);
				ineputchar('\n');
				ineputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->readfd = file_d;
	}
	popu_environ_list(information);
	rd_history(information);
	hsh(information, arg_vec);
	return (EXIT_SUCCESS);
}

