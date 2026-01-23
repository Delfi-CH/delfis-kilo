// includes

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "delfi.h"
#include "kilo.h"

extern char **environ;

// runfile

struct runfile R;

char *trim_runfile(char *s) {
    while (isspace((unsigned char)*s)) s++;
    if (*s == 0) return s;

    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return s;
}

void parse_runfile(void) {
    FILE *f = fopen(".dk/run.ini", "r");
    if (!f) return;

    char line[256];

    while (fgets(line, sizeof(line), f))
    {
        char *s = trim_runfile(line);
        if (*s == '\0' || *s == '#' || *s == ';')
            continue;
        
        char *comment = strpbrk(s, "#;");
        if (comment)
            *comment = '\0';

        char *eq = strchr(s, '=');
        if (!eq) continue;

        *eq = '\0';
        char *k = trim_runfile(s);

        char *v = trim_runfile(eq + 1);

        if (strcmp(k, "name") == 0) {
            free(E.R.name);
            E.R.name = strdup(v);
        } else if (strcmp(k, "bin") == 0) {
            free(E.R.bin);
            E.R.bin = strdup(v);
        } else if (strcmp(k, "args") == 0) {
            free(E.R.argv);
            E.R.argv = strdup(v);
        }
    }
    fclose(f);
    return;
}

int exec_runfile(void) {
    posix_spawn_file_actions_t file_actions;
    posix_spawn_file_actions_init(&file_actions);

    int devnull = open("/dev/null", O_RDWR);

    if (devnull == -1) {
        die("open");
    }

    // Redirect stdin
    posix_spawn_file_actions_adddup2(&file_actions, devnull, STDIN_FILENO);
    // Redirect stdout
    posix_spawn_file_actions_adddup2(&file_actions, devnull, STDOUT_FILENO);
    // Redirect stderr
    posix_spawn_file_actions_adddup2(&file_actions, devnull, STDERR_FILENO);


    char *cmd = E.R.argv;
    char *token;
    char *argv[64];
    int i = 0;

    token = strtok(cmd, " ");
    while (token != NULL) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    if (access(E.R.bin, X_OK) != 0) {
        char *tmp = find_bin_in_path(E.R.bin);
        if (!tmp) {
            die("bin not found");
        }
    }

    pid_t pid;
    int status = posix_spawnp(&pid, E.R.bin, &file_actions, NULL, argv, environ);
    if (status != 0) {
        die("posix_spawnp");
    }

    if (waitpid(pid, &status, 0) == -1) {
        die("waitpid");
    }

    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) != 0) {
            return WEXITSTATUS(status);
        } else {
            return 0;
        }
    }
    return 1;
}

char *find_bin_in_path(const char *binname) {
    if (!binname) return NULL;

    char *path = getenv("PATH");
    if (!path) return NULL;

    char *path_dup = strdup(path);
    if (!path_dup) return NULL;

    char *saveptr;
    char *dir = strtok_r(path_dup, ":", &saveptr);
    while (dir != NULL) {
        size_t len = strlen(dir) + 1 + strlen(binname) + 1;
        char *fullpath = malloc(len);
        if (!fullpath) {
            free(path_dup);
            return NULL;
        }
        snprintf(fullpath, len, "%s/%s", dir, binname);

        if (access(fullpath, X_OK) == 0) {
            free(path_dup);
            return fullpath;
        }

        free(fullpath);
        dir = strtok_r(NULL, ":", &saveptr); 
    }

    free(path_dup);
    return NULL;
}