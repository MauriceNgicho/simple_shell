#include "main.h"

/**
 * read_line - this reads the input string.
 *
 * @i_eof: to return value of getline function.
 * Return: the input string.
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
