#include "main.h"

/**
 * main - entry point
 * Return: 0 for success
 * @ac: number of args
 * @av: array of args
 */

int main(int ac, char **av)
{
	char *buff = NULL;

	if (isatty(0) == 0)
	{
		buff = prompt();
                printf("%s", prompt);
                free(buff);
		return (0);
	}
	
	(void)ac;
	while (1)
	{
		if (isatty(0) == 1)
		{
			write(1, "$ ", 2);
			buff = prompt();
			printf("%s", buff);
			free(buff);
			fflush(stdout);
		}
	}
	free(buff);
	return (0);
}
