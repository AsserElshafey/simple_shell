#include "main.h"

/**
 * prompt - function that shows new line for command to be entered
 * Return: String read from the shell
 */

char *prompt(void)
{
	char *buf;
	size_t n = 0;

	printf("$ ");
	if (getline(&buf, &n, stdin) != -1)
		return (buf);
	exit(-1);
}
