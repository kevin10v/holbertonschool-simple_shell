#include "main.h"

/**
 * path_is_exec - Checks if a path exists and is executable
 * @p: File path
 *
 * Return: 1 if executable, 0 otherwise
 */
static int path_is_exec(const char *p)
{
	struct stat st;

	if (p == NULL || *p == '\0')
		return (0);
	if (stat(p, &st) == -1)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (0);
	if (access(p, X_OK) == -1)
		return (0);
	return (1);
}

/**
 * build_path - Builds "<dir>/<cmd>" into a new string
 * @dir: Directory (may be empty)
 * @cmd: Command (no '/')
 *
 * Return: Newly allocated path (or "./cmd" when dir is empty), or NULL
 */
static char *build_path(const char *dir, const char *cmd)
{
	size_t dlen = strlen(dir), clen = strlen(cmd), total;
	char *full;

	if (dlen == 0)
	{
		total = 2 + 1 + clen + 1; /* "." + "/" + cmd + '\0' */
		full = malloc(total);
		if (!full)
			return (NULL);
		full[0] = '.';
		full[1] = '/';
		memcpy(full + 2, cmd, clen);
		full[total - 1] = '\0';
		return (full);
	}
	if (dir[dlen - 1] == '/')
	{
		total = dlen + clen + 1;
		full = malloc(total);
		if (!full)
			return (NULL);
		memcpy(full, dir, dlen);
		memcpy(full + dlen, cmd, clen);
		full[total - 1] = '\0';
		return (full);
	}
	total = dlen + 1 + clen + 1;
	full = malloc(total);
	if (!full)
		return (NULL);
	memcpy(full, dir, dlen);
	full[dlen] = '/';
	memcpy(full + dlen + 1, cmd, clen);
	full[total - 1] = '\0';
	return (full);
}

/**
 * search_in_path - Searches PATH for cmd (no slash in cmd)
 * @cmd: Command name (no '/')
 * @path: PATH value (colon-separated). If NULL/empty, returns NULL.
 *
 * Return: Newly allocated absolute path if found, else NULL
 */
static char *search_in_path(const char *cmd, const char *path)
{
	char *dup, *tok, *full;

	if (!path || path[0] == '\0')
		return (NULL);

	dup = strdup_safe(path);
	if (!dup)
		return (NULL);

	for (tok = strtok(dup, ":"); tok != NULL; tok = strtok(NULL, ":"))
	{
		full = build_path(tok, cmd);
		if (!full)
		{
			free(dup);
			return (NULL);
		}
		if (path_is_exec(full))
		{
			free(dup);
			return (full);
		}
		free(full);
	}
	free(dup);
	return (NULL);
}

/**
 * command_path - Resolve a command to an executable path
 * @cmd: Command (may contain '/')
 *
 * Return: Newly allocated resolved path (caller frees), or NULL if not found
 */
char *command_path(char *cmd)
{
	char *path, *resolved;

	if (cmd == NULL || *cmd == '\0')
		return (NULL);

	/* If contains '/', try directly (works even when PATH is unset) */
	if (strchr(cmd, '/') != NULL)
		return (path_is_exec(cmd) ? strdup_safe(cmd) : NULL);

	/* Otherwise search PATH */
	path = _getenv("PATH");
	resolved = search_in_path(cmd, path);
	return (resolved);
}
