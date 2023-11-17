#include "inshell.h"

/**
 * getHistory_file - Gets the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing history file.
 */
char *getHistory_file(info_t *info)
{
	char *buf, *dir;

	dir = ingetenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (shstrlen(dir) + shstrlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	shstrcpy(buf, dir);
	shstrcat(buf, "/");
	shstrcat(buf, HIST_FILE);
	return (buf);
}

/**
 * writeHistory - Creates a file, or appends to an existing file.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int writeHistory(info_t *info)
{
	ssize_t fd;
	char *filename = getHistory_file(info);
	inlist *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->inhistory; node; node = node->nxt)
	{
		inputsfd(node->strng, fd);
		niputfd('\n', fd);
	}
	niputfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readHistory - Reads history from file.
 * @info: The parameter struct.
 *
 * Return: Histcount on success, 0 otherwise.
 */
int readHistory(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistory_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			buildHistory_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildHistory_list(info, buf + last, linecount++);
	free(buf);
	info->inhistcount = linecount;
	while (info->inhistcount-- >= HIST_MAX)
		delete_nod_at_index(&(info->inhistory), 0);
	renumberHistory(info);
	return (info->inhistcount);
}

/**
 * buildHistory_list - Adds entry to a history linked list.
 * @info: Structure containing potential arguments. Used to maintain.
 * @buf: Buffer.
 * @linecount: The history linecount, histcount.
 *
 * Return: Always 0.
 */
int buildHistory_list(info_t *info, char *buf, int linecount)
{
	inlist *node = NULL;

	if (info->inhistory)
		node = info->inhistory;
	add_nod_end(&node, buf, linecount);

	if (!info->inhistory)
		info->inhistory = node;
	return (0);
}

/**
 * renumberHistory - Renumbers the history linked list after changes.
 * @inf: Structure containing potential arguments. Used to maintain.
 *
 * Return: The new histcount.
 */
int renumberHistory(info_t *inf)
{
	inlist *nod = inf->inhistory;
	int k = 0;

	while (nod)
	{
		nod->number = k++;
		nod = nod->nxt;
	}
	return (inf->inhistcount = k);
}
