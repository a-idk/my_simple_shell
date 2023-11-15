#include "main.h"

/**
 * check_exec - Find the executable part of the command.
 * @com_cache: The command input.
 *
 * Return: Pointer to the executable part of the command.
 */

char *check_exec(char *com_cache)
{
	char *delim = " ";

	return (strtok(com_cache, delim));
}


/**
 * prep_com_args - prepare the command arguments.
 * @com_cache: command entered
 * @args: array to store command arguments.
 *
 * Return: 0 if successful, -1 if an error occurs.
 */

int prep_com_args(char *com_cache, char **args)
{
	char *delim = " ";
	char *token;
	int arg_index = 0;

	token = strtok(com_cache, delim);
	while (token != NULL)
	{
		args[arg_index++] = token;
		token = strtok(NULL, delim);

		if (arg_index >= MAX_ARGUMENTS - 1)
		{
			perror("Too many command arguments.\n");
			return (-1);
		}
	}
	args[arg_index] = NULL;
	return (0);
}

/**
 * read_comm - reads command given
 * @comm_cache: the memory
 * @comm_bytes: the memory size
 * Return: pointer
 */

ssize_t read_comm(char **comm_cache, size_t *comm_bytes)
{
	ssize_t command = getline(comm_cache, comm_bytes, stdin);

	return (command);
}

/**
 * _strlen - A function that counts string lenght
 * @s: string
 * Return: (leng).
 */

int _strlen(const char *s)
{
	int leng = 0;

	while (*s != '\0')
	{
		leng++;
		s++;
	}
	return (leng);
}

/**
 * _strchr - function that searches for char
 * @s: the string to search
 * @ch: the charcter to search
 * Return: a pointer
 */

char *_strchr(const char *s, int ch)
{
	if (s == NULL)
		return (NULL);
	for (; *s != '\0'; s++)
	{
		if (*s == ch)
			return ((char *)s);
	}
	if (ch == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}
