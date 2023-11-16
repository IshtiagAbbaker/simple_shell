#include "inshell.h"

/**
 * pfree - Frees a pointer and NULLs the address.
 * @ptrtf: Address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */
int pfree(void **ptrtf)
{
	if (ptrtf && *ptrtf)
	{
		free(*ptrtf);
		*ptrtf = NULL;
		return (1);
	}
	return (0);
}
