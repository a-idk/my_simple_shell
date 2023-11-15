#ifndef MAIN_H
#define MAIN_H

/* include libraries and header files */
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stddef.h>

extern char **environ;

/* include prototypes */
int env_print(void);
int _setenv(const char *name, const char *value, int overwrite);
int _setenv2(const char *n, const char *v, int ov);
int dir_change(char *ags[]);
char *_strcpy(char *dest, const char *src);
int _atoi(char *s);
ssize_t read_comm(char **comm_cache, size_t *comm_bytes);
int exe_command(char *comm_cache);
int exe_child(char *av[]);
int exe_parent(pid_t pid);
void free_up(char *comm_cache);
char *find_exec(char *com_cache);
int prep_com_args(char *com_cache, char **args);
int _strlen(const char *s);
ssize_t _getline(char **lineptr, size_t *n, int fd);
char *_strchr(const char *s, int ch);
char *_strtok(char *s, const char *del);
int checks_builtin(char *args[], char *com_cache);
void my_exit(char *com_cache, int status);
int _strcmp(char *s1, char *s2);
int custom_strncmp(const char *str1, const char *str2, size_t n);
int initialize_buffer(char **_ptr, size_t *_num);
ssize_t read_line(char **_ptr, size_t *_num);
char *check_exec(char *com_cache);
char *_getenv(const char *var);
char *find_com(char *command, char *path);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strcat(char *dest, const char *src);
char *_strdup(char *st);

/* Define MACROS */
#define PROMPT_SIZE 2
#define MAX_ARGUMENTS 64
#define INIT_BUF_SZ 128
#define MAX_BUFFER_SIZE 4096

#endif /* main.h */
