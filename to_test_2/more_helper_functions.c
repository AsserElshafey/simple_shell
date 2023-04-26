#include "main.h"

/**
 * _strcmp - comparing two strings
 * Return: int
 * @s1: first string
 * @s2: second string
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 * _strncpy - copies a string
 * Return: char
 * @dest: destination string
 * @src: source string
 * @n: size
 */

char *_strncpy(char *dest, char *src, int n)

{
	int i = 0, srclen = 0;

	while (src[i++])
	{
		srclen++;
	}
	for (i = 0; src[i] && i < n; i++)
	{
		dest[i] = src[i];
	}
	for (i = srclen; i < n; i++)
	{
		dest[i] = '\0';
	}

	return (dest);
}

/**
 * _strncmp - compares between n numbers of characters in two srrings
 * @s1: first string
 * @s2: second string
 * @n: number of characters to compare
 * Return: 0 for similarity
 */

int _strncmp(char *s1, char *s2, int n)
{
	char *arr1 = malloc(sizeof(char) * (n + 1));
	char *arr2 = malloc(sizeof(char) * (n + 1));

	_strncpy(arr1, s1, n);
	_strncpy(arr2, s2, n);
	_strcat(arr1, "\0");
	_strcat(arr2, "\0");
	return (_strcmp(arr1, arr2));
}
/**
 * _getenv - gets the value of an environment variable
 * @name: the name of the variable
 * Return: a pointer to the value of the variable, or NULL if not found
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
