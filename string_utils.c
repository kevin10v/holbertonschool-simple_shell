#include "main.h"
#include <string.h>
#include <stdlib.h>

/**
 * strdup_safe - duplicates a string safely
 * @s: input string
 * Return: newly allocated copy or NULL
 */
char *strdup_safe(const char *s)
{
	char *dup;
	size_t len;

	if (s == NULL)
		return (NULL);

	len = strlen(s);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);

	memcpy(dup, s, len + 1);
	return (dup);
}
