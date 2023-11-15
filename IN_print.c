#include "shell_prompt.h"
/**
 * IN_print - Prints a message to the standard output.
 * @input: The input string to be printed.
 *
 * This function writes the specified input string to the standard output.
 *
 * @input: The input string to be printed.
 */
void IN_print(const char *input)
{
write(STDOUT_FILENO, message, strlen(input));
}

