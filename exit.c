#include "main.h"

/**
 * free_up - cleans up the memory allocated
 * @comm_cache: the memory to free
 * Return: nothing
 */

void free_up(char *comm_cache)
{
	free(comm_cache);
}

/* exit.c */

/**
 * my_exit - exit a process
 * @com_cache: the command entered
 * @status: stores the command
 *
 * Return: nothing
 */

void my_exit(char *com_cache, int status)
{
	char error_msg[20];

	free_up(com_cache);

	if (com_cache != NULL && com_cache[0] != '\0')
	{
		status = _atoi(com_cache);

		if (status == 0 && com_cache[0] != '0')
		{
			_strcpy(error_msg, "Exit with error: ");
			write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
			write(STDERR_FILENO, com_cache, _strlen(com_cache));
			write(STDERR_FILENO, "\n", 1);
			exit(1);
		}
		exit(status);
	}
	exit(0);
}

/**
 * checks_builtin - checks for builtin command
 * @args: the argument count
 * @com_cache: the command entered
 *
 * Return: 1 if it's built-in, 0 otherwise
 */

int checks_builtin(char *args[], char *com_cache)
{
	/* declaring variable */
	int status;

	if (_strcmp(args[0], "exit") == 0)
	{
		status = (args[1] != NULL && args[1][0] != '\0');
		my_exit(com_cache, status);
		return (1);
	}
	return (0);
}

/**
 * _atoi - Convert a string to an integer.
 * @s: The pointer to convert
 * Return: A integer
 */

int _atoi(char *s)
{
	unsigned int ni = 0;
	int min = 1, isi = 0, c = 0;

	while (s[c])
	{
		if (s[c] == 45)
			min *= -1;
		while (s[c] >= 48 && s[c] <= 57)
			isi = 1, ni = (ni * 10) + (s[c] - '0'), c += 1;
		if (isi == 1)
			break;
		c += 1;
	}
	ni *= min;
	return (ni);
}
