#ifndef MAIN_H
#define MAIN_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;

/* input.c */
ssize_t read_line(char **line, size_t *n, int interactive);
char **tokenize_line(char *line, int *argc);
void free_tokens(char **tokens);
int is_empty_line(const char *s);

/* builtins.c */
int is_builtin(const char *cmd);
int handle_builtin(char **argv);

/* path.c */
char *get_env_value(const char *name);
char *find_in_path(const char *cmd);
int is_executable(const char *path);

/* execute.c */
int execute(char **argv, const char *progname, int cmd_no);

/* string_utils.c */
char *strdup_safe(const char *s);
void strip_newline(char *s);

/* errors.c */
void print_not_found(const char *prog, int cmd_no, const char *cmd);


ssize_t read_line(char **line, size_t *n, int interactive);
int is_empty_line(const char *s);
char **tokenize_line(char *line, int *argc);
void free_tokens(char **tokens);


#endif /* MAIN_H */
