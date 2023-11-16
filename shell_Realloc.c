#include "inshell.h"

/**
 * mset - Fills memory with a constant byte.
 * @s: The pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The amount of bytes to be filled.
 *
 * Return: (s) a pointer to the memory area s.
 */
char *mset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * fffree - Frees a string of strings.
 * @pp: String of strings.
 */
void fffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * reloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @oldsize: Byte size of the previous block.
 * @newsize: Byte size of the new block.
 *
 * Return: Pointer to da ol'block nameen.
 */
void *reloc(void *ptr, unsigned int oldsize, unsigned int newsize)
{
	char *p;

	if (!ptr)
		return (malloc(newsize));
	if (!newsize)
		return (free(ptr), NULL);
	if (newsize == oldsize)
		return (ptr);

	p = malloc(newsize);
	if (!p)
		return (NULL);

	oldsize = oldsize < newsize ? oldsize : newsize;
	while (oldsize--)
		p[oldsize] = ((char *)ptr)[oldsize];
	free(ptr);
	return (p);
}
