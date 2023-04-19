#include "main.h"

/**
 * main - entry point
 * Return: 0 for success
 */

int main(void)
{
	char *buff;
	char **av;

	while (1)
	{
		buff = prompt();
		av = split_string(buff);
		execute(av);
		free(buff);
		free(av);
	}
	return (0);
}
