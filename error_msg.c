#include "main.h"

/**
 * print_error - prints an error message to the standard error
 * @prog_name: the name of the program
 * @len: the number of commands entered
 * @cmd: the command that caused the error
 *
 * Return: nothing
 */
void print_error(char **argv, int len, char **av)
{
	char *len_str;

	len_str = _itoa(len);
	write(2, av[0], _strlen(av[0]));
	write(2, ": ", 2);
	write(2, len_str, _strlen(len_str));
	write(2, ": ", 2);
	write(2, argv[0], _strlen(argv[0]));
	write(2, ": ", 2);
	write(2, ": not found\n", 12);
	free(len_str);
}

/**
 * _itoa - converts an integer to a string
 * @n: the integer to convert
 *
 * Return: a pointer to the string or NULL if memory allocation fails
 */
char *_itoa(int n)
{
	char *str;
	int len, i, sign;

	len = 0;
	sign = 1;
	if (n < 0)
	{
		len++;
		sign = -1;
		n = -n;
	}
	while (n / 10 > 0)
	{
		len++;
		n /= 10;
	}
	len++;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	n = n * sign;
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	i = len - 1;
	while (n / 10 > 0)
	{
		str[i] = (n % 10) + '0';
		i--;
		n /= 10;
	}
	str[i] = n + '0';
	return (str);
}
