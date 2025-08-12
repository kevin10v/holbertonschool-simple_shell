#include<string.h>
#include "main.h"

/**
 * command_read - function that reads the commands
 * @s: command
 * Return: return int from execute command
 */
int command_read(char *s)
{
	char *token = NULL;
	char *cmd_array[100];
	int i = 0;

	if (strcmp(s, "exit") == 0)
		return (2);
	if (strcmp(s, "env") == 0)
		return (_printenv());

	token = strtok(s, " ");
	while (token)
	{
		cmd_array[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	cmd_array[i] = NULL;

	return (execute(cmd_array));
}
