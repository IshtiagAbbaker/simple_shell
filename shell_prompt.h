#ifndef SHELL_PROMPT_H
#define SHELL_PROMPT_H
/*
 * The macro SHELL_H is typically chosen to be unique to the header file,
 * serving as a marker to check whether the file has been included before.
 * struct Alias - Represents an alias for the simple shell
 * @name: The name of the alias
 * @value: The value associated with the alias
 *
 * This struct defines the structure for storing aliases in the simple shell.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_BUFFER_SIZE 1024
#define ALIASES 64
#define ALIAS_NAME 32
#define ALIAS_VALUE 128
#define VARIABLE_NAME 3
#define COMMAND_LENGTH 256

typedef struct
{
char name[ALIAS_NAME]; /**< The name of the alias */
char val[ALIAS_VALUE]; /**< The value associated with the alias */
} Alias;
void prompt_display(void);
void IN_print(const char *input);
void read_input(char *input, size_t Size);
void exe_command(const char *entered_command, char **arguments);
void execute_builtin(char *input);
int Is_builtin(char *input);
void execute(char *input);
char *IN_getline(void);
void unset_environment_variable(const char *var);
void set_environment_variable(const char *var, const char *val);
void cd(const char *dir);
void logical_op(char *inlin, char *op);
void handle_alias(char *rgs[], int arg_cont);
void defup_aliases(char *name_vals[], int cont);
void print_speci_aliases(char *names[], int cont);
void print_aliases(void);
void replace_vars(char *input);
void rm_comments(char *inlin);

#endif /* SHELL_PROMPT_H */

