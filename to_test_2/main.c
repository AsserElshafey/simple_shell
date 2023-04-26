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

char *prompt(void)
{
	char *buf = NULL;
	size_t n = 0;
	ssize_t len;

	len = getline(&buf, &n, stdin);

	if (len == -1)
	{
		_putchar('\n');
		free(buf);
		exit(-1);
	}

	return (buf);
}

char **split_string(char *buff)
{
	char *buf_cpy = _strdup(buff);
	char *token = NULL;
	char *delim = " \n";
	char **av;
	unsigned int num_tokens = 0, i = 0;

	token = strtok(buff, delim);

	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	num_tokens++;

	av = malloc(sizeof(char *) * num_tokens);

	if (av == NULL)
	{
		perror("Memory allocation failed");
		exit(-1);
	}

	token = strtok(buf_cpy, delim);
	for (i = 0; token != NULL; i++)
	{
		av[i] = _strdup(token);
		token = strtok(NULL, delim);
	}
	free(buf_cpy);
	av[i] = NULL;
	return (av);
}

int execute(char **argv)
{
	char *cmd = NULL;
	pid_t pid;
	unsigned int i = 0;

	if (argv == NULL)
		return (-1);

	cmd = get_cmd_path(argv[0]);

	if (_strcmp(argv[0], "env") == 0)
	{
		char **env = environ;

		while (env[i])
		{
			write(STDOUT_FILENO, env[i], _strlen(env[i]));
			_putchar('\n');
			i++;
		}

                free(cmd);

                return (0);
        }

        pid = fork();

        switch (pid)
        {
        case (-1):
                free(cmd);

                return (-1);

        case (0):
                if (cmd == NULL || execve(cmd, argv, NULL) == -1)
                {
                        free(cmd);

                        perror(argv[0]);

                        exit(EXIT_FAILURE);
                }

                exit(EXIT_SUCCESS);

        default:
                if (wait(NULL) == -1)
                {
                        free(cmd);

                        perror("wait");

                        return (-1);
                }

                break;
        }

        free(cmd);

        return (0);
}

char *get_cmd_path(char *cmd)
{
	char *path = NULL, *token = NULL, *path_cpy = NULL, *path_array = NULL;
	int cmd_len, dir_len;
	struct stat buffer;

	if (_strcmp(cmd, "exit") == 0)
	        exit(0);

	path = _getenv("PATH");

	if (path == NULL)
	        return (NULL);

	path_cpy = _strdup(path);

	if (path_cpy == NULL)
	        return (NULL);

	cmd_len = _strlen(cmd);

	token = strtok(path_cpy, ":");

	while (token != NULL)
        {
	        dir_len = _strlen(token);

	        path_array = malloc(dir_len + cmd_len + 2);

	        if (path_array == NULL)
	        {
	                free(path_cpy);

	                return (NULL);
	        }

	        _strcpy(path_array, token);

	        _strcat(path_array, "/");

	        _strcat(path_array, cmd);

	        if (!stat(path_array, &buffer))
	        {
	                free(path_cpy);

	                return (path_array);
	        }

	        free(path_array);

	        token = strtok(NULL, ":");
        }

        free(path_cpy);

        if (!stat(cmd, &buffer))
                return (cmd);

        return (NULL);
}
