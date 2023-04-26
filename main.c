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

	if (signal(SIGINT, my_handler) == SIG_ERR)
	{
		write(STDERR_FILENO, "Error: failed to register signal handler.\n", 42);
		return (1);
	}
	if (isatty(0) == 0)
	{
		buff = prompt();

                av = split_string(buff);
                execute(av);
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

			av = split_string(buff);
			execute(av);
			free(buff);
			fflush(stdout);
		}
	}
	free(buff);
	return (0);
}
