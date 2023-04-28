#include "main.h"

/**
 * _memcpy - copies memory area.
 * @dest: the memory area to be filled
 * @src: the origin memery area
 * @n: number of bytes to copy
 *
 * Return: a pointer to the memory area dest.
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	char *p = dest;

	if (src == NULL || dest == NULL)
		return (NULL);

	while (n--)
		*p++ = *src++;

	return (dest);
}

/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: old size of pointer
 * @new_size: new size of pointer
 *
 * Return: void *
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *nptr = NULL;

	if (new_size == old_size)
		return (ptr);

	if ((new_size == 0) && ptr)
	{
		free(ptr);
		return (NULL);
	}

	if (!ptr)
	{
		free(ptr);
		nptr = malloc(new_size);
		if (!nptr)
			return (NULL);
		return (nptr);
	}

	if (new_size > old_size)
	{
		nptr = malloc(new_size);
		if (!nptr)
			return (NULL);

		_memcpy(nptr, ptr, old_size);
		free(ptr);
	}
	return (nptr);
}

/**
 * _getline - get line input from user
 * @lptr: buffer where to send input
 * @n: size of buffer to modify
 * @stream: stream where to read
 * Return: number of chars read
 */
ssize_t _getline(char **lptr, size_t *n, __attribute__((unused))FILE * stream)
{
	static char buffer[BUFFER_SIZE];
	static int start, end;
	char *line;
	int len = 0;

	line = malloc(BUFFER_SIZE);
	if (line == NULL)
		return (-1);
	while (1)
	{
		if (start >= end) /* refill the buffer */
		{
			start = 0;
			end = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (end == 0) /* end of file */
			{
				free(line);
				return (-1);
			}
			if (end == -1) /* error */
			{
				free(line);
				return (-1);
			}
		}
		line[len++] = buffer[start];
		start++;
		if (line[len - 1] == '\n') /* end of line */
			break;
		if (start == end) /* expand the line buffer */
		{
			line = _realloc(line, len, len + BUFFER_SIZE);
			if (line == NULL)
				return (-1);
		}
	}
	line[len] = '\0';
	*lptr = line;
	*n = len;
	return (len);
}
