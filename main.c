#include "main.h"

/**
 * main - simple shell loop (interactive & non-interactive)
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int interactive = isatty(STDIN_FILENO);
	char *line = NULL;
	size_t cap = 0;
	ssize_t r;
	int cmd_no = 0;
	(void)ac;

	while (1)
	{
		r = read_line(&line, &cap, interactive);
		if (r == -1) /* EOF */
			break;

		if (!is_empty_line(line))
		{
			int argc = 0;
			char **argv = tokenize_line(line, &argc);

			if (argv && argv[0])
			{
				cmd_no++;
				/* Built-ins first */
				if (!is_builtin(argv[0]) || handle_builtin(argv) == 0)
				{
					/* If not a builtin, run external */
					if (is_builtin(argv[0]) == 0) /* exit handled inside */
					{
						free_tokens(argv);
						continue;
					}
					execute(argv, av[0], cmd_no);
				}
			}
			free_tokens(argv);
		}
	}
	free(line);
	return (0);
}
