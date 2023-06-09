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
	while (n > 0 && *s1 && *s2)
	{
		if (*s1 != *s2)
	{
		return ((int) (*s1 - *s2));
	}
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
	{
		return (0);
	}
	return ((int) (*s1 - *s2));
}

/**
 * frarr - Clears a double pointer
 * @str: Double pointer to clean
 *
 * Return: 1
 */

int frarr(char **str)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		free(str[i]);
	}
	free(str);

	return (1);
}

/**
 * print_env - prints the environment variables
 * @argv: passed argv
 * Return: 0 on success, -1 on failure
 */
int print_env(char **argv)
{
	char **env = environ;
	unsigned int i = 0;

	if (argv[1] == NULL)
	{
		while (env[i])
		{
			write(1, env[i], _strlen(env[i]));
			_putchar('\n');
			i++;
		}
	}
	else
	{
		i = 1;
		while (argv[i])
		{
			write(1, argv[i], _strlen(argv[i]));
			_putchar('\n');
			i++;
		}
	}
	return (1);
}
