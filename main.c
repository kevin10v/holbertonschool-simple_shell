#include "main.h"
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <stddef.h>
/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument values
 * Return: Always 0 (Success)
 */
int main(void)
{

	char *line = NULL;
	size_t buff_size = 0;
	ssize_t characters = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(1, "$ ", 2);
		characters = getline(&line, &buff_size, stdin);

		if (characters == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(1, "\n", 1);
			break;
		}

		if (line[characters - 1] == '\n')
			line[characters - 1] = '\0';
		if (*line == '\0')
			continue;
		if (command_read(line) == 2)
			break;
	}
	free(line);
	line = NULL;
	return (0);
}
