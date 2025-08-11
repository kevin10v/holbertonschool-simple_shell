#include "main.h"

/**
 * is_builtin - Checks if a command is a builtin
 * @cmd: Command string
 *
 * Return: 1 if builtin, 0 otherwise
 */
int is_builtin(const char *cmd)
{
	if (cmd == NULL)
		return (0);

	if (strcmp(cmd, "exit") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);

	return (0);
}

/**
 * handle_builtin - Executes a builtin command
 * @argv: Argument vector (argv[0] is the command)
 *
 * Return: 1 if handled and shell should continue,
 *         (does not return for "exit")
 */
int handle_builtin(char **argv)
{
	if (strcmp(argv[0], "exit") == 0)
	{
		/* Task 0.4: no need to handle arguments */
		exit(0);
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		int i;

		for (i = 0; environ[i] != NULL; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}

	return (1);
}
