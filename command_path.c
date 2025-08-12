#include "main.h"

/**
 * command_path - Finds the full path of a command
 * @cmd: The command to find
 * Return: The full path of the command
 */

char *command_path(char *cmd)
{
	char *path, *path_copy, *full_path, *token;
	struct stat buf;

	path = _getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "Path variable not found");
		return (NULL);
	}
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		fprintf(stderr, "Error copying path");
		return (NULL);
	}
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(cmd) + 2);
		if (full_path == NULL)
		{
			fprintf(stderr, "Error allocating full path");
			free(path_copy);
			return (NULL);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (stat(full_path, &buf) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	if (stat(cmd, &buf) == 0)
		return (strdup(cmd));
	return (NULL);
}
