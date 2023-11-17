#ifndef IN_SHELL_H_
#define IN_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_his"
#define HIST_MAX	4096

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


extern char **envi;

/**
 * struct liststr - singly linked list
 * @number: the number field
 * @strng: a string
 * @nxt: points to the next node
 */
typedef struct liststr
{
	int number;
	char *strng;
	struct liststr *nxt;
} inlist;

/**
 *struct passinformation - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@inarg: a string generated from getline containing arguements
 *@inargv: an array of strings generated from arg
 *@inpath: a string path for the current command
 *@inargc: the argument count
 *@inline_count: the error count
 *@inerr_num: the error code for exit()s
 *@inlinecount_flag: if on count this line of input
 *@infname: the program filename
 *@inenv: linked list local copy of environ
 *@inenviron: custom modified copy of environ from LL env
 *@inhistory: the history node
 *@inalias: the alias node
 *@inenv_changed: on if environ was changed
 *@instatus: the return status of the last exec'd command
 *@incmd_buf: address of pointer to cmd_buf, on if chaining
 *@incmd_buf_type: CMD_type ||, &&, ;
 *@inreadfd: the fd from which to read line input
 *@inhistcount: the history line number count
 */
typedef struct passinformation
{
	char *inarg;
	char **inargv;
	char *inpath;
	int inargc;
	unsigned int inline_count;
	int inerr_num;
	int inlinecount_flag;
	char *infname;
	inlist *inenv;
	inlist *inhistory;
	inlist *inalias;
	char **inenviron;
	int inenv_changed;
	int instatus;

	char **incmd_buf; /* pointer to cmd ; for memory mangement */
	int incmd_buf_type; /* CMD_type ||, &&, ; */
	int inreadfd;
	int inhistcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@typeo: the builtin command flag
 *@fun: the function
 */
typedef struct builtin
{
	char *typeo;
	int (*fun)(info_t *);
} builtin_t;

int inhsh(info_t *, char **);
int fd_builin(info_t *);
void fd_command(info_t *);
void fork_command(info_t *);
int is_command(info_t *, char *);
char *dup_chrs(char *, int, int);
char *fd_path(info_t *, char *, char *);
int loophshell(char **);
void ineputs(char *);
int inputchar(char);
int niputfd(char c, int fd);
int inputsfd(char *str, int fd);
int shstrlen(char *);
int shstrcmp(char *, char *);
char *strt_with(const char *, const char *);
char *shstrcat(char *, char *);
char *shstrcpy(char *, char *);
char *shstrdup(const char *);
void shputs(char *);

int _putchar(char);

char *shstrncpy(char *, char *, int);
char *shstrncat(char *, char *, int);
char *shstrchr(char *, char);
char **str_tow(char *, char *);
char **str_towtow(char *, char);
char *mset(char *, char, unsigned int);
void fffree(char **);
void *reloc(void *, unsigned int, unsigned int);
int pfree(void **);
int interact(info_t *);
int ist_delim(char, char *);
int inisalpha(int);
int inatoi(char *);
int inerratoi(char *);
void printError(info_t *, char *);
int printd(int, int);
char *convertNumber(long int, int, int);
void rm_comments(char *);
int inmyexit(info_t *);
int inmycd(info_t *);
int inmyhelp(info_t *);
int inmyhistory(info_t *);
int inmyalias(info_t *);

ssize_t get_input(info_t *);

int mygetline(info_t *, char **, size_t *);

void sigintHandler(int);

void clear_ininfo(info_t *);
void set_ininfo(info_t *, char **);
void free_inf(info_t *, int);

char *ingetenv(info_t *, const char *);
int inmyenv(info_t *);
int inmysetenv(info_t *);
int inmyunsetenv(info_t *);
int populateEnv_list(info_t *);

char **getEnviron(info_t *);
int inunsetenv(info_t *, char *);
int insetenv(info_t *, char *, char *);

char *getHistory_file(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistory_list(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

inlist *add_nod(inlist **, const char *, int);
inlist *add_nod_end(inlist **, const char *, int);
int delete_nod_at_index(inlist **, unsigned int);
void free_list(inlist **);
size_t printList_str(const inlist *);

size_t list_len(const inlist *);
char **list_to_strings(inlist *);
size_t printList(const inlist *);
inlist *nod_strt_with(inlist *, char *, char);
ssize_t get_nod_index(inlist *, inlist *);
int inis_chain(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVars(info_t *);
int replaceString(char **, char *);

#endif

