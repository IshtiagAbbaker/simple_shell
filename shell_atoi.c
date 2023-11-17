#include "inshell.h"

/**
 * interact - Returns true if the shell is in interactive mode.
 * @shell_info: Struct containing shell information.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interact(info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->inreadfd <= 2);
}

/**
 * ist_delim - Checks if a character is a delimiter.
 * @character: The character to check.
 * @delimiters: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int ist_delim(char character, char *delimiters)
{
	while (*delimiters)
		if (*delimiters++ == character)
			return (1);
	return (0);
}

/**
 * inisalpha - Checks for an alphabetic character.
 * @input_char: The character to check.
 *
 * Return: 1 if input_char is alphabetic, 0 otherwise.
 */
int inisalpha(int input_char)
{
	if ((input_char >= 'a' && input_char <= 'z') || (input_char >= 'A' && input_char <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * inatoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: 0 if no numbers in the string, the converted number otherwise.
 */
int inatoi(char *str)
{
	int index, sign = 1, flag = 0, result = 0;

	for (index = 0; str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;
		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		result = -result;
	return (result);
}
