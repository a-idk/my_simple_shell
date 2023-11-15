#include "main.h"

/**
 * main - main entry point of the code
 * @ar_c: arguments count
 * @ar_v: argument vectors
 *
 * Return: 0 on success!
 */

int main(int ar_c, char *ar_v[])
{
	char *pmt = "$ ", *c_cache = NULL; /* declaring variable */
	size_t c_bytes = 0;
	ssize_t command;
	int result;

	setenv("PATH", "/bin:/usr/bin:/usr/local/bin", 1); /* setting the path env */
	if (ar_c > 1)
		return (exe_command(ar_v[1]));
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, pmt, 2), command = read_comm(&c_cache, &c_bytes);
		} else
		{
			if (getline(&c_cache, &c_bytes, stdin) == -1)
				break;
			command = _strlen(c_cache);
		}
		if (command == (ssize_t)-1)
		{
			perror("Read command failed"), free_up(c_cache);
			return (-1);
		}
		if (c_cache[command - 1] == '\n')
			c_cache[command - 1] = '\0';
		if (_strcmp(c_cache, "exit") == 0)
		{
			free_up(c_cache);
			return (0);
		}
		result = exe_command(c_cache);
		if (result == -1)
		{
			free_up(c_cache);
			return (0);
		}}
	free_up(c_cache);
	return (0);
}
