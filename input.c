#include "main.h"

/**
 * read_line - Prints prompt (if tty) and reads a line with getline
 * @line: Buffer pointer (managed by getline)
 * @n: Size of the buffer (in/out)
 * @interactive: 1 if stdin is a tty, 0 otherwise
 *
 * Return: Number of bytes read, or -1 on EOF/error
 */
ssize_t read_line(char **line, size_t *n, int interactive)
{
	ssize_t r;

	if (interactive)
		write(STDOUT_FILENO, "$ ", 2);

	r = getline(line, n, stdin);
	if (r == -1)
	{
		if (interactive)
			write(STDOUT_FILENO, "\n", 1);
		return (-1);
	}

	strip_newline(*line);
	return (r);
}

/**
 * is_empty_line - Checks if a string is empty or only whitespace
 * @s: String to check
 *
 * Return: 1 if empty/whitespace-only, 0 otherwise
 */
int is_empty_line(const char *s)
{
	const char *p = s;

	if (s == NULL)
		return (1);

	while (*p != '\0')
	{
		if (*p != ' ' && *p != '\t' && *p != '\n')
			return (0);
		p++;
	}
	return (1);
}

/**
 * append_token - Appends a token to argv (grows with malloc+memcpy)
 * @argvp: Address of argv pointer
 * @cap: Address of current capacity (pointer count)
 * @idx: Address of next insert position
 * @tok: Token to duplicate and append
 *
 * Return: 0 on success, -1 on allocation failure
 */
static int append_token(char ***argvp, size_t *cap, size_t *idx,
			const char *tok)
{
	char **arr = *argvp, **newp;
	size_t need = *idx + 2, ncap;
	char *dup;

	if (*cap < need)
	{
		ncap = (*cap == 0) ? 8 : *cap;
		while (ncap < need)
			ncap *= 2;

		newp = malloc(sizeof(char *) * ncap);
		if (newp == NULL)
			return (-1);

		if (arr != NULL && *cap > 0)
		{
			size_t copy = (*idx + 1 <= *cap) ? (*idx + 1) : *cap;

			memcpy(newp, arr, sizeof(char *) * copy);
		}
		else
		{
			newp[0] = NULL;
		}

		free(arr);
		arr = newp;
		*argvp = arr;
		*cap = ncap;
	}

	dup = strdup_safe(tok);
	if (dup == NULL)
		return (-1);

	arr[*idx] = dup;
	(*idx)++;
	arr[*idx] = NULL;
	return (0);
}

/**
 * tokenize_line - Splits a line into argv by whitespace
 * @line: Input line (not modified)
 * @argc: Output number of arguments
 *
 * Return: NULL-terminated argv (caller frees), or NULL on failure
 */
char **tokenize_line(char *line, int *argc)
{
	char *copy, *tok;
	char **argv = NULL;
	size_t cap = 0, i = 0;

	if (argc)
		*argc = 0;

	copy = strdup_safe(line);
	if (copy == NULL)
		return (NULL);

	for (tok = strtok(copy, " \t"); tok; tok = strtok(NULL, " \t"))
	{
		if (append_token(&argv, &cap, &i, tok) == -1)
		{
			free(copy);
			free_tokens(argv);
			return (NULL);
		}
	}

	if (argc)
		*argc = (int)i;

	free(copy);
	return (argv);
}

/**
 * free_tokens - Frees an argv array produced by tokenize_line
 * @tokens: The argv array (NULL-terminated)
 */
void free_tokens(char **tokens)
{
	size_t i;

	if (tokens == NULL)
		return;

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);

	free(tokens);
}
