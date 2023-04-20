#include "main.h"

/**
 * split_string - splits a string into an array of tokens
 * @buff: the string to split
 * Return: an array of tokens, or NULL on failure
 */
char **split_string(char *buff)
{
	char *buf_cpy = strdup(buff);
	char *token;
	char *delim = " \n";
	char **av;
	unsigned int num_tokens = 0, i = 0;

	token = strtok(buff, delim);
	/* Number of tokens*/
	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	num_tokens++;
	/* Allocating memory for new array */
	av = malloc(sizeof(char *) * num_tokens);
	/* NULL error handling */
	if (av == NULL)
	{
		perror("Memory allocation failed");
		exit(-1);
	}
	/* Storing string in new array */
	token = strtok(buf_cpy, delim);
	for (i = 0; token != NULL; i++)
	{
		av[i] = malloc(sizeof(char) * strlen(token));
		_strcpy(av[i], token);
		token = strtok(NULL, delim);
	}
	free(buf_cpy);
	av[i] = NULL;
	return (av);
}
