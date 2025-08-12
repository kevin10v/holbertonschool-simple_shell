#include "main.h"

/**
 * _printenv - Prints the current environment to STDOUT
 *
 * Return: 0 on success, -1 if environ is NULL
 */
int _printenv(void)
{
	int i;

	if (environ == NULL)
		return (-1);

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}

/**
 * _getenv - Returns the value of an environment variable
 * @name: Variable name (e.g. "PATH")
 *
 * Return: Pointer to value inside environ, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i;
	size_t len;

	if (name == NULL || environ == NULL)
		return (NULL);

	len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 &&
		    environ[i][len] == '=')
			return (environ[i] + len + 1);
	}

	return (NULL);
}
