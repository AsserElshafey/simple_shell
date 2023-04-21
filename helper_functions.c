#include "main.h"

/**
 * _strlen - a function that returns the length of a string
 * @s: char input
 * Return: length of the input string
 */

int _strlen(char *s)
{
	int c;

	for (c = 0; s[c] != 0; c++)
	{
	}
	return (c);
}

/**
 * char *_strcpy - a function that copies the string pointed to by src
 * @dest: copy to
 * @src: copy from
 * Return: string
 */

char *_strcpy(char *dest, char *src)
{
	char *ok = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (ok);
}

/**
 * _strdup - duplicate to new memory space location
 * @str: char
 * Return: 0
 */

char *_strdup(char *str)
{
	int i, end;
	char *array;

	if (str == NULL)
		return (NULL);

	for (end = 0; str[end] != '\0'; end++)
	{
	}

	array = malloc(end + 1);

	if (array == NULL)
		return (NULL);

	for (i = 0; i < end; i++)
		array[i] = str[i];

	return (array);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strcat - a function that concatenates two strings
 * @dest: copy to
 * @src: copy from
 * Return: two concat strings
 */

char *_strcat(char *dest, char *src)
{
	int i, n;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}

	for (n = 0; (dest[i + n] = *src++) != '\0'; n++)
	{
	}

	return (dest);
}

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
 * s1: first string
 * s2: second string
 * n: number of characters to compare
 * Return: 0 for similarity
 */

int _strncmp(char* s1, char *s2, int n)
{
	char arr1[n + 1], arr2[n + 1];

	_strncpy(arr1, s1, n);
	_strncpy(arr2, s2, n);
	arr1[n] = '\0';
	arr2[n] = '\0';
	return (_strcmp(arr1, arr2));
}
