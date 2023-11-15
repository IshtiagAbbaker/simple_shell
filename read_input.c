#include "shell_prompt.h"
/**
 * read_input - Reads input from the standard input.
 * @input: Buffer to store the input string.
 * @Size: Size of the buffer.
 *
 * This function reads a line of input from the standard input and removes
 * the trailing newline character. If an error occurs during reading,
 * an appropriate error message is displayed, and the program exits.
 *
 * @input: Buffer to store the input string.
 * @Size: Size of the buffer.
 */

void read_input(char *input, size_t Size)
{
if (fgets(input, Size, stdin) == NULL)
{
if (feof(stdin))
{
IN_print("\n");
exit(EXIT_SUCCESS);
}
else
{
IN_print("Error while reading input.\n");
exit(EXIT_FAILURE);
}
}
input[strcspn(input, "\n")] = '\0';
}

