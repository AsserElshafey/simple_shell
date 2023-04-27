#include "main.h"
/**
 * sigint_handler - handles the SIGINT signal
 * @signum: the signal number
 */
void sigint_handler(int signum)
{
	(void)signum;
	/* print a newline character */
	write(1, "\n", 1);
	write(1, "$ ", 2);
}
/**
 * is_empty - checks for empty str
 * @str: the string
 * Return: bool value
 */
bool is_empty(char *str)
{
	unsigned int i = 0;

	/* loop through each character of the string */
	while (str[i])
	{
		/* if the character is not whitespace, return false */
		if (!is_whitespace(str[i]))
			return (false);

		i++;
	}

	/* if all characters are whitespace or the string is empty, return true */
	return (true);
}
/**
 * is_whitespace - checks for white space
 * @c: the character
 * Return: 1 or 0
 */
bool is_whitespace(char c)
{
	/* compare the character with the ASCII values of space, tab, and newline */
	if (c == 32 || c == 9 || c == 10)
		/* return true if it matches */
		return (true);
		/* return false otherwise */
	return (false);
}

/**
 * main - entry point
 * Return: 0 for success
 * @ac: num of args
 * @av: args
 */

int main(int ac, char **av)
{
	char *buff = NULL;
	char **argv;
	int len = 0;
	void (*handler)(int);

	handler = signal(SIGINT, sigint_handler);
	if (handler == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	(void)ac;
	while (1)
	{
		if (isatty(0) == 1)
		{
			write(1, "$ ", 2);
		}
		buff = prompt();
		if (handler)
			continue;
		if (is_empty(buff))
			continue;
		if (buff == NULL)
			return (-1);
		len++;
		argv = split_string(buff);
		if (argv == NULL)
			return (-1);
		if (_strcmp(argv[0], "exit") == 0)
		{
			free(buff);
			free(argv);
			return (0);
		}
		if (execute(argv, av, len) == -1)
			return (-1);
		free(buff);
		free(argv);
		fflush(stdout);
	}
	return (0);
}
