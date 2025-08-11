#include "main.h"

/**
 * strdup_safe - duplikon një string (me check)
 * @s: string
 * Return: kopja ose NULL
 */
char *strdup_safe(const char *s)
{
	char *p;
	size_t len;

	if (!s)
		return (NULL);
	len = strlen(s);
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	memcpy(p, s, len + 1);
	return (p);
}

/**
 * strip_newline - heq '\n' në fund
 * @s: string
 */
void strip_newline(char *s)
{
	size_t l;

	if (!s)
		return;
	l = strlen(s);
	if (l && s[l - 1] == '\n')
		s[l - 1] = '\0';
}
