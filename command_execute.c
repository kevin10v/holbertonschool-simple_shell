#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/**
 * run_child - Execs the resolved binary in the child process
 * @exe_path: Full path to executable
 * @cmd_arr: NULL-terminated argv (argv[0] is the command)
 *
 * Return: Never returns; on failure prints error and _exit(126)
 */
static int run_child(char *exe_path, char **cmd_arr)
{
	execve(exe_path, cmd_arr, environ);
	perror("execve");
	exit(126);
}

/**
 * run_parent - Waits for child to finish and maps status to shell code
 * @pid: Child PID
 *
 * Return: 0 if child exits with 0; 2 if child exits non-zero
 */
static int run_parent(pid_t pid)
{
	int status;

	do {
		if (waitpid(pid, &status, WUNTRACED) == -1)
			break;
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));

	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (2);

	return (0);
}

/**
 * execute - Executes a command by forking and calling execve
 * @cmd_arr: NULL-terminated argv (cmd_arr[0] is the command)
 *
 * Return: 0 on success, 1 if command not found or fork error,
 *         2 if child exited with non-zero status
 */
int execute(char **cmd_arr)
{
	pid_t pid;
	char *exe_path;

	if (cmd_arr == NULL || cmd_arr[0] == NULL)
		return (0);

	exe_path = command_path(cmd_arr[0]);
	if (exe_path == NULL)
	{
		write(STDERR_FILENO, cmd_arr[0], strlen(cmd_arr[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		return (1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(exe_path);
		return (1);
	}

	if (pid == 0)
		run_child(exe_path, cmd_arr);
	else
	{
		int ret = run_parent(pid);

		free(exe_path);
		return (ret);
	}

	free(exe_path);
	return (0);
}
