#ifndef simple_shell
#define simple_shell

/* Includes */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdbool.h>

/* Testing */
#include <stdio.h>

/* extern */
extern char **environ;
char *_getenv(char *name);

/* Helper functions */
int _putchar(char c);
char *_strdup(char *str);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
int frarr(char **str);
void sigint_handler(int signum);
bool is_empty(char *str);
bool is_whitespace(char c);
int print_env(char *cmd);

/* error_msg */
void print_error(char **argv, int len, char **av);
char *_itoa(int n);

/* Shell functions */
int execute(char **argv, char **av, int len);
char *get_cmd_path(char *cmd);
char *prompt(void);
char **split_string(char *buff);

/* Advanced */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void exit_shell(char **argv, int status);
int _atoi(char *s);
int is_integer(char *s);


#endif /* simple_shell */
