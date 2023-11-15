#include "main.h"

/**
 * initialize_buffer - initializes buffer
 * @_ptr: the pointer
 * @_num: pointer to the number
 *
 * Return: 0
 */

int initialize_buffer(char **_ptr, size_t *_num)
{
	if (*_ptr == NULL || *_num == 0)
	{
		*_ptr = (char *)malloc(INIT_BUF_SZ);
		if (*_ptr == NULL)
			return (-1);
		*_num = INIT_BUF_SZ;
	}
	return (0);
}


/**
 * read_line - function that reads the line
 * @_ptr: a pointer
 * @_num: pointer to the number
 *
 * Return: the number
 */

ssize_t read_line(char **_ptr, size_t *_num)
{
	size_t a = 0;
	size_t nwsz;
	int bytrd, i;
	char buf[INIT_BUF_SZ];
	char *nwptr;

	while (1)
	{
		bytrd = read(STDIN_FILENO, buf, INIT_BUF_SZ);
		if (bytrd < 0)
			return (-1);
		if (bytrd == 0)
		{
			if (a == 0)
				return (-1);
		}
	}
	for (i = 0; i < bytrd; i++)
	{
		if (buf[i] == '\n')
		{
			(*_ptr)[a] = '\0';
			return (a);
		}
		if (a == (*_num - 1))
		{
			nwsz = *_num * 2;
			nwptr = (char *)realloc(*_ptr, nwsz);
		}
		if (nwptr == NULL)
			return (-1);
		*_ptr = nwptr;
		*_num = nwsz;
	}
	(*_ptr)[a++] = buf[i];
	return (a);
}


/**
 * _getline - reads the line
 * @lineptr: a pointer
 * @n: pointer to the number
 * @fd: file descriptor
 *
 * Return: the number
 */

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[128];
	static size_t pos;
	static ssize_t bytes_in_buffer;
	ssize_t bytes_read = 0, line_length = 0;
	char *new_lineptr;

	if (fd < 0 || !lineptr || !n)
		return (-1);  /* Invalid input parameters */
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128, *lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
			return (-1); /* failed */
	}
	while (1)
	{
		if (pos >= (size_t)bytes_in_buffer)
		{
			bytes_read = read(fd, buffer, sizeof(buffer));
			if (bytes_read <= 0)
			{
				if (line_length == 0)
					return (-1);
				break;
			}
			bytes_in_buffer = bytes_read, pos = 0;
		}
		if ((size_t)line_length >= *n)
		{
			*n *= 2, new_lineptr = (char *)realloc(*lineptr, *n);
			if (!new_lineptr)
				return (-1);  /* failed */
			*lineptr = new_lineptr;
		}
		(*lineptr)[line_length++] = buffer[pos++];
		if (buffer[pos - 1] == '\n')
			break;
	}
	(*lineptr)[line_length] = '\0';
	return (line_length);
}
