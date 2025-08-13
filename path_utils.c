#include "shell.h"


char *find_env_value(char **env, const char *name)
{
    size_t nlen = strlen(name);
    int i;

    if (!env || !name)
        return NULL;

    for (i = 0; env[i]; i++)
    {
        if (!strncmp(env[i], name, nlen) && env[i][nlen] == '=')
            return env[i] + nlen + 1;
    }
    return NULL;
}


static char *join_path(const char *dir, const char *cmd)
{
    size_t len = strlen(dir) + 1 + strlen(cmd) + 1;
    char *out = malloc(len);
    if (!out) return NULL;

    strcpy(out, dir);
    strcat(out, "/");
    strcat(out, cmd);
    return out;
}

/*
 * resolve_command:
 *  - Nëse cmd ka '/', thjesht kontrollo access(X_OK).
 *  - Përndryshe, kërko në PATH. Nëse PATH mungon ose bosh → NULL.
 *  - Kthen string të ri me malloc (rrugë të plotë) ose NULL.
 */
char *resolve_command(char *cmd, char **env)
{
    char *path, *dup, *dir, *full;

    if (!cmd || !*cmd)
        return NULL;


    if (strchr(cmd, '/'))
        return (access(cmd, X_OK) == 0) ? strdup(cmd) : NULL;

    path = find_env_value(env, "PATH");
    if (!path || !*path)
        return NULL;

    dup = strdup(path);
    if (!dup)
        return NULL;

    dir = strtok(dup, ":");
    while (dir)
    {
        full = join_path(dir, cmd);
        if (full && access(full, X_OK) == 0)
        {
            free(dup);
            return full;
        }
        free(full);
        dir = strtok(NULL, ":");
    }
    free(dup);
    return NULL;
}
