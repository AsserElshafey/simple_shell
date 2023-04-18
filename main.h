#ifndef simple_shell
#define simple_shell

/* Includes */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Helper functions */
int _putchar(char c);
char *_strdup(char *str);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);

/* Shell functions */
int execute(char *cmd);
char *get_cmd_path(char *command);
char *prompt(void);

#endif /* simple_shell */
