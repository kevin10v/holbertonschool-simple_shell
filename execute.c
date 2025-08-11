#include "main.h"

/**
 * resolve_command - Builds an executable path for a command
 * @cmd: Command name (may contain '/')
 * @progname: Program name for error messages
 * @cmd_no: Command counter for error messages
 *
 * Return: Newly allocated full path on success (caller frees),
 *         NULL if not found or on allocation error (prints error if not found)
 */
static char *resolve_command(const char *cmd, const char *progname, int cmd_no)
{
	char *full;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);

	if (strchr(cmd, '/') != NULL)
	{
		if (!is_executable(cmd))
		{
			print_not_found(progname, cmd_no, cmd);
			return (NULL);
		}

		full = strdup_safe(cmd);
		return (full);
	}

	full = find_in_path(cmd);
	if (full == NULL)
	{
		print_not_found(progname, cmd_no, cmd);
		return (NULL);
	}

	return (full);
}

/**
 * spawn_and_wait - Forks and execs the resolved command, then waits
 * @full: Resolved executable full path
 * @argv: Argument vector (NULL-terminated)
 * @progname: Program name for perror on failures
 *
 * Return: Child exit status; 1 on fork error
 */
static int spawn_and_wait(const char *full, char **argv, const char *progname)
{
	pid_t pid;
	int status = 0;

	pid = fork();
	if (pid == -1)
	{
		perror(progname);
		return (1);
	}

	if (pid == 0)
	{
		execve((char *)full, argv, environ);
		perror(progname);
		_exit(126);
	}

	waitpid(pid, &status, 0);
	return (status);
}

/**
 * execute - Executes a command, searching in PATH when needed
 * @argv: Argument vector (argv[0] is the command)
 * @progname: Program name (used in error messages)
 * @cmd_no: Command counter (used in error messages)
 *
 * Return: Child exit status, 127 when not found, 1 on fork error
 */
int execute(char **argv, const char *progname, int cmd_no)
{
	char *full;
	int status;

	if (argv == NULL || argv[0] == NULL || argv[0][0] == '\0')
		return (0);

	full = resolve_command(argv[0], progname, cmd_no);
	if (full == NULL)
		return (127);

	status = spawn_and_wait(full, argv, progname);
	free(full);

	return (status);
}
