#include "main.h"

/**
 * main - entry point
 * Return: 0 for success
 */

int main(int ac, char **av)
{
	char *buff = NULL;;
	size_t bufsize = 0;
	ssize_t chars_len  = 0;
	char **avv = NULL;

	(void)av;

	if (ac < 1)
		return (-1);;
	while (1)
	{
		free_buffers(avv);
		prompt();
		chars_len = getline(&buff, &bufsize, stdin);
		if (chars_len = -1)
			break;

		avv = split_string(buff);
		execute(avv);
	}
	if (chars_len == -1)
		write(STDERR_FILENO, "\n", 1);
	free(buff);
	return (0);
}
