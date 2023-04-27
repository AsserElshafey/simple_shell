#include "main.h"

/**
 * _getenv - gets the env
 * @name: name
 * Return: NULL
 */
char *_getenv(char *name, **environ)
{
	int i, j, k;

	k = _strlen(name);
	for (i = 0; environ[i]; i++)
	{
		for (j = 0; environ[i][j] == name[j]; j++)
		{
		}
		if (j == k && environ[i][j] == '=')
			return (environ[i]);

	}
	return (NULL);
}
char *get_cmd_path(char **environ, char *input)
{
	char **path = NULL, *command;
	unsigned int input_len, path_len, i, j, k;
	struct stat st;

	path = split_string(_getenv("PATH", environ), "=:");
	input_len = _strlen(input);

	for (i = 1; path[i]; i++)
	{
		path_len = _strlen(path[i]);
		command = malloc(sizeof(char) * (path_len + input_len + 2));
		if (!command)
		{
			write(2, "Unable to allocate memory", 25);
			exit(1);
		}

		for (j = 0; path[i][j]; j++)
			command[j] = path[i][j];

		command[j++] = '/';

		for (k = 0; input[k]; k++)
			command[j + k] = input[k];

		command[j + k] = '\0';

		if (stat(command, &st) == 0)
		{
			arraycleaner(path);
			return (command);
		}
		free(command);
	}
	arraycleaner(path);

	return (NULL);
}

/**
 * execute - executes a command using fork and execve
 * @argv: array of arguments for the command
 * Return: 0 on success, -1 on failure
 */

int execute(char **argv)
{
	char *cmd = NULL, *err_msg = NULL;
	pid_t pid;
	unsigned int i = 0;

	/* check for invalid input */
	if (argv == NULL || argv[0] == NULL)
		return (-1);

	/* get the full path of the command */
	cmd = get_cmd_path(argv[0]);

	/* handle the special case of 'env' command */
	if (_strcmp(argv[0], "env") == 0)
	{
		char **env = environ;

		/* print each environment variable */
		while (env[i])
		{
			if (write(STDOUT_FILENO, env[i], _strlen(env[i])) == -1)
			{
				free(cmd);
				perror("write");
				return (-1);
			}
			_putchar('\n');
			i++;
		}
		free(cmd);
		return (0);
	}

	/* create a child process */
	pid = fork();

	switch (pid)
	{
	case (-1):
		free(cmd);
		perror("fork");
		return (-1);
	case (0):
		/* execute the command in the child process */
		if (cmd == NULL || execve(cmd, argv, NULL) == -1)
		{
			free(cmd);
			err_msg = _strcat(argv[0], ": not found");
			perror(err_msg);
			free(err_msg);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	default:
		/* wait for the child process to finish */
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

/**
 * prompt - function that shows new line for command to be entered
 * Return: String read from the shell
 */

char *prompt(void)
{
	char *buf = NULL;
	size_t n = 0;
	ssize_t len;

	/* get a line from the standard input */
	len = getline(&buf, &n, stdin);

	/* check for errors or end of file */
	if (len == -1)
	{
		_putchar('\n');
		free(buf);
		exit(-1);
	}

	/* return the input string */
	return (buf);
}

/**
 * split_string - splits a string into an array of tokens
 * @buff: the string to split
 * Return: an array of tokens, or NULL on failure
 */
char **split_string(char *buff)
{
	char *buf_cpy = NULL;
	char *token = NULL;
	char *delim = " \n";
	char **av;
	unsigned int num_tokens = 0, i = 0;

	/* check for invalid input */
	if (buff == NULL || buff[0] == '\0')
		return (NULL);

	/* make a copy of the input string */
	buf_cpy = _strdup(buff);
	if (buf_cpy == NULL)
		return (NULL);

	/* split the input string by the delimiter */
	token = strtok(buff, delim);

	/* count the number of tokens */
	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	num_tokens++;

	/* allocate memory for the array of tokens */
	av = malloc(sizeof(char *) * num_tokens);
	if (av == NULL)
	{
		perror("Memory allocation failed");
		free(buf_cpy);
		exit(-1);
	}

	/* store each token in the array */
	token = strtok(buf_cpy, delim);
	for (i = 0; token != NULL; i++)
	{
		av[i] = _strdup(token);
		if (av[i] == NULL)
		{
			perror("Memory allocation failed");
			free(buf_cpy);
			free(av);
			exit(-1);
		}
		token = strtok(NULL, delim);
	}
	free(buf_cpy);
	av[i] = NULL;
	return (av);
}
