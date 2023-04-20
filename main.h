#ifndef simple_shell
#define simple_shell

/* Includes */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Testing */
#include <stdio.h>

/* extern */
extern char **environ;
char *_getenv(const char *name);

/* Helper functions */
int _putchar(char c);
char *_strdup(char *str);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

/* Shell functions */
int execute(char **argv);
char *get_cmd_path(char *cmd);
char *prompt(void);
char **split_string(char *buff);
int execute(char **argv);

#endif /* simple_shell */
