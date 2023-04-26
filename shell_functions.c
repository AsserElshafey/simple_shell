#include "main.h"

/**
 * _getenv - gets the env
 * @name: name
 * Return: NULL
 */
char *_getenv(char *name)
{
	unsigned int i = 0;
	char **env = environ;

	/* check for invalid input */
	if (name == NULL || name[0] == '\0' || env == NULL)
		return (NULL);

	/* loop through the environment array */
	while (env[i])
	{
		/* compare the name with the current variable */
		if (_strncmp(name, env[i], _strlen(name)) == 0)
		{
			/* return the value after the '=' sign */
			return (&env[i][_strlen(name) + 1]);
		}
		i++;
	}
	/* return NULL if not found */
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
#if 0

	if (pid != 0)
		wait(NULL);

	if (pid== 0 && execve(cmd, argv, NULL) == -1)
	{
		write(2, argv[0], _strlen(argv[0]));
		perror(": ");
		exit(EXIT_FAILURE);
	}
	return (0);
#endif
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
 * get_cmd_path - gets the full path of a command from the PATH environment
 * @cmd: the command to look for
 * Return: the full path of the command, or NULL if not found
 */

char *get_cmd_path(char *cmd)
{
	char *path = NULL, *token = NULL, *path_cpy = NULL, *path_array = NULL;
	int cmd_len, dir_len;
	struct stat buffer;

	/* check for invalid input */
	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);

	/* handle the special case of 'exit' command */
	if (_strcmp(cmd, "exit") == 0)
		exit(0);

	/* get the value of the PATH environment variable */
	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);

	/* make a copy of the path value */
	path_cpy = _strdup(path);
	if (path_cpy == NULL)
		return (NULL);

	/* get the length of the command name */
	cmd_len = _strlen(cmd);

	/* split the path value by ':' delimiter */
	token = strtok(path_cpy, ":");
	while (token != NULL)
	{
		/* get the length of the current directory */
		dir_len = _strlen(token);

		/* allocate memory for the full path of the command */
		path_array = malloc(dir_len + cmd_len + 2);
		if (path_array == NULL)
		{
			free(path_cpy);
			return (NULL);
		}

		/* concatenate the directory, '/', and the command name */
		_strcpy(path_array, token);
		_strcat(path_array, "/");
		_strcat(path_array, cmd);

		/* check if the file exists and is executable */
		if (!stat(path_array, &buffer))
		{
			free(path_cpy);
			return (path_array);
		}

		free(path_array);
		
                /* get the next token */
                token = strtok(NULL, ":");
        }
        free(path_cpy);

        /* check if the command is a relative or absolute path */
        if (!stat(cmd, &buffer))
                return (cmd);

        /* return NULL if not found */
        return (NULL);
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
	unsigned int num_tokens = 1, i = 0;
	int j = 0;

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
		exit(1);
	}

	/* store each token in the array */
	token = strtok(buf_cpy, delim);
	for (i = 0; token != NULL;)
	{
		av[i] = _strdup(token);
		if (av[i] == NULL)
		{
			perror("Memory allocation failed");
			for (; i != 0; i--)
				free(av[i - 1]);
			free(av);
			exit(1);
		}
		for (j = 0; j < _strlen(token); j++)
		{
			av[i][j] = token[j];
		}
		av[i][j] = '\0';
		i++;
		token = strtok(NULL, delim);
	}
	/* free(buf_cpy);*/
	av[i] = NULL;
	free(buf_cpy);
	return (av);
}
