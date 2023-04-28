#include "main.h"

/**
 * exit_shell - exits the shell with a given status
 * @argv: the arguments array
 *
 * Return: nothing
 */
void exit_shell(char **argv)
{
	int status = 0;

	/* check if the argument is a valid integer */
	if (argv[1] != NULL && is_integer(argv[1]))
	{
		/* convert the argument to an integer */
		status = _atoi(argv[1]);
	}

	/* free the arguments array */
	free(argv);

	/* exit the shell with the given status */
	exit(status);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to convert
 *
 * Return: the integer value of the string
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	unsigned int num = 0;

	/* skip any non-digit characters */
	while (s[i] != '\0' && (s[i] < '0' || s[i] > '9'))
	{
		/* change the sign if there is a minus sign */
		if (s[i] == '-')
			sign *= -1;
		i++;
	}

	/* convert the digits to an integer */
	while (s[i] != '\0' && (s[i] >= '0' && s[i] <= '9'))
	{
		num = num * 10 + (s[i] - '0');
		i++;
	}

	/* return the integer with the sign */
	return (sign * num);
}

/**
 * is_integer - checks if a string is a valid integer
 * @s: the string to check
 *
 * Return: 1 if the string is a valid integer, 0 otherwise
 */
int is_integer(char *s)
{
	int i = 0;

	/* check if the string is empty */
	if (s == NULL || s[0] == '\0')
		return (0);

	/* skip any leading signs */
	if (s[0] == '+' || s[0] == '-')
		i++;

	/* check if there is at least one digit */
	if (s[i] == '\0' || (s[i] < '0' || s[i] > '9'))
		return (0);

	/* check if the rest of the string is digits */
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}

	/* return 1 if the string is a valid integer */
	return (1);
}
