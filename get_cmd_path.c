#include "main.h"

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
