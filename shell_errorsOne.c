#include "inshell.h"

/**
 * inerratoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: 0 if no numbers in the string, converted number otherwise,
 *         -1 on error.
 */
int inerratoi(char *str)
{
	int idx = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (idx = 0; str[idx] != '\0'; idx++)
	{
		if (str[idx] >= '0' && str[idx] <= '9')
		{
			result *= 10;
			result += (str[idx] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printError - Prints an error message.
 * @info: The parameter & return info struct.
 * @errorStr: String containing the specified error type.
 *
 * Return: 0 if no numbers in the string, converted number otherwise,
 *        -1 on error.
 */
void printError(info_t *info, char *errorStr)
{
	ineputs(info->fname);
	ineputs(": ");
	printd(info->line_count, STDERR_FILENO);
	ineputs(": ");
	ineputs(info->argv[0]);
	ineputs(": ");
	ineputs(errorStr);
}

/**
 * printd - Function prints a decimal (integer) number (base 10).
 * @input: The input.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int printd(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absValue, current;

	if (fd == STDERR_FILENO)
		__putchar = ineputchar;
	if (input < 0)
	{
		absValue = -input;
		__putchar('-');
		count++;
	}
	else
		absValue = input;
	current = absValue;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absValue / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convertNumber - Converter function, a clone of itoa.
 * @num: Number.
 * @base: Base.
 * @flags: Argument flags.
 *
 * Return: String.
 */
char *convertNumber(long int num, int base, int flags)
{
	static char *charArray;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	charArray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = charArray[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - Function replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Return: Always 0.
 */
void rm_comments(char *buf)
{
	int idx;

	for (idx = 0; buf[idx] != '\0'; idx++)
		if (buf[idx] == '#' && (!idx || buf[idx - 1] == ' '))
		{
			buf[idx] = '\0';
			break;
		}
}
