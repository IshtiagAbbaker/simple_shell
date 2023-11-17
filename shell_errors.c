#include "inshell.h"

/**
 * ineputs - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void ineputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		inputchar(str[index]);
		index++;
	}
}

/**
 * inputchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int inputchar(char c)
{
	static int buffer_index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(2, buf, buffer_index);
		buffer_index = 0;
	}
	if (c != BUF_FLUSH)
		buf[buffer_index++] = c;
	return (1);
}

/**
 * niputfd - Writes the character c to given fd.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int niputfd(char c, int fd)
{
	static int buffer_index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(fd, buf, buffer_index);
		buffer_index = 0;
	}
	if (c != BUF_FLUSH)
		buf[buffer_index++] = c;
	return (1);
}

/**
 * inputsfd - Prints an input string.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int inputsfd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += niputfd(*str++, fd);
	}
	return (count);
}
