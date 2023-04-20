#include "main.h"

/**
 * _getenv - gets the env
 * @name: name
 * Return: NULL
 */

char *_getenv(const char *name)
{
	unsigned int i = 0;
	char **env = environ;

	while (env[i])
	{
		if (strncmp(name, env[i], strlen(name)) == 0)
		{
			return (&env[i][strlen(name) + 1]);
		}
		i++;
	}
	return (NULL);
}
