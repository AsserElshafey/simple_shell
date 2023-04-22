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

	while (env[i])
	{
		if (_strncmp(name, env[i], strlen(name)) == 0)
		{
			return (&env[i][strlen(name) + 1]);
		}
		i++;
	}
	return (NULL);
}

/**
 * execute - executes a command using fork and execve
 * @argv: array of arguments for the command
 * Return: 0 on success, -1 on failure
 */

int execute(char **argv)
{
	char *cmd = NULL;
	pid_t pid;
	unsigned int i = 0;

	cmd = get_cmd_path(argv[0]);
	if (strcmp(argv[0], "env") == 0)
	{
		char **env = environ;

		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
		return (0);
	}
	pid = fork();
	switch (pid)
	{
	case (-1):
		return (-1);
	case (0):
		if (execve(cmd, argv, NULL) == -1)
		{
			perror("Error");
		}
		break;
	default:
		wait(NULL);
		break;
	}
	return (0);
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

	path = _getenv("PATH");
	if (path)
	{
		path_cpy = _strdup(path);
		cmd_len = _strlen(cmd);
		token = strtok(path_cpy, ":");
		while (token != NULL)
		{
			dir_len = _strlen(token);
			path_array = malloc(dir_len + cmd_len + 2);
			_strcpy(path_array, token);
			_strcat(path_array, "/");
			_strcat(path_array, cmd);
			_strcat(path_array, "\0");
			if (!stat(path_array, &buffer))
			{
				free(path_cpy);
				return (path_array);
			}
			else
			{
				free(path_array);
				token = strtok(NULL, ":");
			}
		}
		free(path_cpy);
		if (!stat(cmd, &buffer))
			return (cmd);
		return (NULL);
	}
	return (NULL);
}

/**
 * prompt - function that shows new line for command to be entered
 * Return: String read from the shell
 */

char *prompt(void)
{
	char *buf;
	size_t n = 0;

	printf("$ ");
	if (getline(&buf, &n, stdin) != -1)
		return (buf);
	exit(-1);
}

/**
 * split_string - splits a string into an array of tokens
 * @buff: the string to split
 * Return: an array of tokens, or NULL on failure
 */
char **split_string(char *buff)
{
	char *buf_cpy = strdup(buff);
	char *token;
	char *delim = " \n";
	char **av;
	unsigned int num_tokens = 0, i = 0;

	token = strtok(buff, delim);
	/* Number of tokens*/
	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	num_tokens++;
	/* Allocating memory for new array */
	av = malloc(sizeof(char *) * num_tokens);
	/* NULL error handling */
	if (av == NULL)
	{
		perror("Memory allocation failed");
		exit(-1);
	}
	/* Storing string in new array */
	token = strtok(buf_cpy, delim);
	for (i = 0; token != NULL; i++)
	{
		av[i] = malloc(sizeof(char) * strlen(token));
		_strcpy(av[i], token);
		token = strtok(NULL, delim);
	}
	free(buf_cpy);
	av[i] = NULL;
	return (av);
}