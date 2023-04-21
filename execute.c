#include "main.h"

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
