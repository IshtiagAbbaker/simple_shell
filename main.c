#include "inshell.h"

/**
 * main - Entry point.
 * @count: Argument count.
 * @vector: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int count, char **vector)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (count == 2)
	{
		fd = open(vector[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				ineputs(vector[0]);
				ineputs(": 0: Can't open ");
				ineputs(vector[1]);
				inputchar('\n');
				inputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->inreadfd = fd;
	}
	populateEnv_list(info);
	readHistory(info);
	inhsh(info, vector);
	return (EXIT_SUCCESS);
}
