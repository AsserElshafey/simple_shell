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

	if (name == NULL || name[0] == '\0' || env == NULL)
		return (NULL);
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
 * @av: av
 * @length: len from loop
 */

int execute(char **argv, char **av, int length)
{
	char *cmd = NULL;
	pid_t pid;
	int status;

	if (argv == NULL || argv[0] == NULL)
		return (-1);
	cmd = get_cmd_path(argv[0]);
	if (cmd == NULL)
	{
		print_error(argv, length, av);
		return (127);
	}
	if (_strcmp(argv[0], "env") == 0)
		print_env(argv);
	pid = fork();
	switch (pid)
	{
	case (-1):
		perror("fork");
		return (-1);
	case (0):
		if (execve(cmd, argv, environ) == -1)
		{
			perror("Error");
		}
		free(cmd);
		exit(0);
	default:

		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = 2;
		if (cmd != argv[0])
			free(cmd);
		return (status);
	}
	return (1);
}

/**
 * get_cmd_path - gets the full path of a command from the PATH environment
 * @cmd: the command to look for
 * Return: the full path of the command, or NULL if not found
 */

char *get_cmd_path(char *cmd)
{
	char *path, *token, *path_cpy, *path_array;
	int cmd_len, dir_len;
	struct stat buffer;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
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
		_strcat(path_array, "\0");
		if (stat(path_array, &buffer) == 0)
		{
			free(path_cpy);
			return (path_array);
		}
		free(path_array);
		token = strtok(NULL, ":");
	}
	free(path_cpy);
	if (stat(cmd, &buffer) == 0)
		return (cmd);
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
	len = _getline(&buf, &n, stdin);

	/* check for errors or end of file */
	if (len == -1)
	{
		free(buf);
		if (isatty(0))
		{
			_putchar('\n');
			exit(0);
		}
		exit(0);
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
	char *buf_cpy = NULL, *token = NULL;
	char *delim = " \n";
	char **av;
	unsigned int num_tokens = 0, i = 0;

	if (buff == NULL || buff[0] == '\0')
		return (NULL);
	buf_cpy = _strdup(buff);
	if (buf_cpy == NULL)
	{
		perror("alloc failed");
		exit(EXIT_FAILURE);
	}

	token = strtok(buf_cpy, delim);
	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	num_tokens++;
	av = malloc(sizeof(char *) * (num_tokens));
	if (av == NULL)
	{
		free(buf_cpy);
		perror("Memory allocation failed");
		exit(1);
	}
	token = strtok(buff, delim);
	for (i = 0; i  < (num_tokens - 1); i++)
	{
		av[i] = token;
		token = strtok(NULL, delim);
	}
	av[i] = NULL;
	free(buf_cpy);
	return (av);
}
