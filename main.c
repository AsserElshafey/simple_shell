#include "main.h"

/**
 * main - entry point
 * Return: 0 for success
 * @ac: number of args
 * @av: array of args
 */

int main(int ac, char **av)
{
	char *buff;

	if (isatty(0) == 0)
	{
		buff = prompt();

                av = split_string(buff);
                execute(av);
                free(buff);
	}
	
	(void)ac;
	while (1)
	{
		if (isatty(0) == 1)
		{
			buff = prompt();

			av = split_string(buff);
			execute(av);
			free(buff);
			fflush(stdout);
		}
		/*buff = prompt();

		av = split_string(buff);
		execute(av);
		free(buff);*/
#if 0
		for (i = 0; av[i]; i++)
		{
			free(av[i]);
		}
		free(av);
#endif
	}
	free(buff);
	return (0);
}
