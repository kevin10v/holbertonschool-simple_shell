#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Environment utilities */
int _printenv(void);
char *_getenv(const char *name); /* <-- konstante dhe emri 'name' */

/* Command path / execution */
char *command_path(char *cmd);
int command_read(char *s);
int execute(char **cmd_arr);

/* Helpers */
void trim_whitespace(char *str);
void strip_newline(char *str);
char **split_line(char *line);
void free_tokens(char **tokens);
char *strdup_safe(const char *s);



#endif /* MAIN_H */
