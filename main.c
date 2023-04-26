#include "main.h"

/**
 * main - entry point
 * Return: 0 for success
 */

int main(int ac, char **av)
{
	char *buff;

	(void)ac;
	while (1)
	{
		buff = prompt();

		av = split_string(buff);
		execute(av);
		free(buff);
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
