#include "main.h"

/**
 * get_env_value - Returns the value of an environment variable
 * @name: Variable name (e.g. "PATH")
 *
 * Return: Pointer to value within environ, or NULL if not found
 */
char *get_env_value(const char *name)
{
	size_t nlen;
	int i;

	if (name == NULL)
		return (NULL);

	nlen = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, nlen) == 0 && environ[i][nlen] == '=')
			return (environ[i] + nlen + 1);
	}
	return (NULL);
}

/**
 * is_executable - Checks whether a path exists and is executable
 * @path: File path
 *
 * Return: 1 if executable regular file, 0 otherwise
 */
int is_executable(const char *path)
{
	struct stat st;

	if (path == NULL)
		return (0);
	if (stat(path, &st) == -1)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (0);
	if (access(path, X_OK) == -1)
		return (0);
	return (1);
}

/**
 * build_full_path - Builds "<dir>/<cmd>" into a new string
 * @dir: Directory
 * @cmd: Command
 *
 * Return: Newly allocated string or NULL
 */
char *build_full_path(const char *dir, const char *cmd)
{
	size_t len;
	char *full;

	if (dir == NULL || cmd == NULL)
		return (NULL);

	len = strlen(dir) + 1 + strlen(cmd) + 1;
	full = malloc(len);
	if (full == NULL)
		return (NULL);

	sprintf(full, "%s/%s", dir, cmd);
	return (full);
}

/**
 * find_in_path - Searches PATH for a command and returns its absolute path
 * @cmd: Command name (no '/')
 *
 * Return: Newly allocated absolute path (caller must free), or NULL
 */
char *find_in_path(const char *cmd)
{
	char *path, *dup, *tok, *full;

	if (cmd == NULL || strchr(cmd, '/') != NULL)
		return (NULL);

	path = get_env_value("PATH");
	if (path == NULL)
		return (NULL);

	dup = strdup_safe(path);
	if (dup == NULL)
		return (NULL);

	tok = strtok(dup, ":");
	while (tok != NULL)
	{
		full = build_full_path(tok, cmd);
		if (full == NULL)
		{
			free(dup);
			return (NULL);
		}
		if (is_executable(full))
		{
			free(dup);
			return (full);
		}
		free(full);
		tok = strtok(NULL, ":");
	}
	free(dup);
	return (NULL);
}
