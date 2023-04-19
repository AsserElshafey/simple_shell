#include "main.h"

char *prompt(void)
{
		ssize_t status;
		char *buf;
		size_t n = 0;
		
		printf("$ ");
		if (getline(&buf, &n, stdin) != -1)
			return (buf);
		else
			exit(-1);
		free(buf);
}
