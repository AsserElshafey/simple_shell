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

	cmd = get_cmd_path(argv[0]);
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
