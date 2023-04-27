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

/* Shell functions */
int execute(char **argv, char **av, int len);
char *get_cmd_path(char *cmd);
char *prompt(void);
char **split_string(char *buff);

#endif /* simple_shell */
