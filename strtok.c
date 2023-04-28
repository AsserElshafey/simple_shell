#include "main.h"
/**
 * _strchr - locates a character in a string
 * @s: string to analyse
 * @c: charater to look for
 *
 * Return: first occurrence if it exits & NULL if not found
 */

char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
		}
	if (c == 0)
		return (s);
	return (0);
}
/**
 * _getdelim - finds the first occurrence of any character in delim in str
 * @str: the string to search
 * @delim: the string containing the delimiters
 *
 * Return: the first matching delimiter, or the first character of delim if none
 */
char _getdelim(char *str, const char *delim)
{
	int i = 0, j;

	while (str[i])
	{
		j = 0;
		while (delim[j])
		{
			if (str[i] == delim[j])
				return (delim[j]);
			j++;
		}
		i++;
	}
	return (delim[0]);
}

/**
 * _strtok_r - splits a string into tokens using a set of delimiters
 * @str: the string to split
 * @delim: the string containing the delimiters
 *
 * Return: a pointer to the next token, or NULL if there are no more tokens
 */
char *_strtok_r(char *str, const char *delim)
{
	static char *tmp;
	char *next = NULL;
	unsigned int dif = 0;
	char *token = NULL;
	char cdel = '\0';

	if (str != NULL)
		tmp = str;

	token = tmp;
	if (token == NULL)
		return (NULL);

	cdel = _getdelim(tmp, delim);
	next = _strchr(tmp, cdel);
	if (next != NULL)
	{
		dif = next - tmp;
		token = tmp;
		next++;
		tmp = next;
		token[dif] = '\0';
	}
	if (next == NULL)
	{
		token = tmp;
		tmp = NULL;
	}
	return (token);
}

/**
 * _strtok - splits a string into tokens using a set of delimiters
 * @str: the string to split
 * @delim: the string containing the delimiters
 *
 * Return: a pointer to the next token, or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	char *token;

	do {
		token = _strtok_r(str, delim);
	} while (token && token[0] == '\0');
	return (token);
}
