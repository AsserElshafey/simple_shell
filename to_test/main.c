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
}

/**
 * main - entry point
 * Return: 0 for success
 */

int main(int ac, char **av)
{
	char *buff = NULL;
	void (*handler)(int);

	/* set up the signal handler for SIGINT */
	handler = signal(SIGINT, sigint_handler);

	/* check for errors */
	if (handler == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	/* check if the input is from a terminal or a file */
	if (isatty(0) == 0)
	{
		/* get a line from the standard input */
		buff = prompt();
		if (buff == NULL)
			return (-1);

		/* split the line by spaces and newlines */
		av = split_string(buff);
		if (av == NULL)
			return (-1);

		/* execute the command with arguments */
		if (execute(av) == -1)
			return (-1);

		free(buff);
		return (0);
	}
	
	(void)ac;
	while (1)
	{
		if (isatty(0) == 1)
		{
			/* print a prompt */
			write(1, "$ ", 2);

			/* get a line from the standard input */
			buff = prompt();
			if (buff == NULL)
				return (-1);

			/* split the line by spaces and newlines */
			av = split_string(buff);
			if (av == NULL)
				return (-1);

			/* execute the command with arguments */
			if (execute(av) == -1)
				return (-1);

			free(buff);

			/* flush the output buffer */
			fflush(stdout);
		}
	}
	free(buff);
	return (0);
}
