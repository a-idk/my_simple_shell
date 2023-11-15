#include "main.h"

/**
 * _getenv - function that takes an environment var and returns
 * string values
 * @var: variable name
 *
 * Return: string value of env
*/

char *_getenv(const char *var)
{
	/* declaring and setting env variable */
	int indx, len;
	char *pos;

	for (indx = 0; environ[indx] != NULL; indx += 1)
	{
		pos = _strchr(environ[indx], '=');
		if (pos != NULL)
		{
			len = pos - environ[indx];
			if (_strncmp(environ[indx], var, len) == 0)
				return (pos + 1);
		}
	}
	return (NULL);
}

/**
 * find_com - function that checks the command line
 * @command: variable name
 * @path: path string
 *
 * Return: string value of env
*/

char *find_com(char *command, char *path)
{
	char *token, *temp, *delim = ":", *executable = NULL;
/*	size_t t_len; */

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0 && !access(command, F_OK))
			return (_strdup(command));
		else
			return (NULL);
	}
	token = strtok(path, delim);
	while (token != NULL)
	{
/*		t_len = strlen(token) + strlen(command) + 2; */
		if (command[0] == '/')
/*			temp = (char *)malloc(strlen(token) + strlen(command) + 1); */
			temp = malloc(_strlen(token) + _strlen(command) + 1);
		else
/*			temp = (char *) malloc(t_len); */
			temp = malloc(_strlen(token) + _strlen(command) + 2);
		if (temp == NULL)
		{
			perror("Memory allocation failed");
			return (NULL);
		}
		if (command[0] == '/')
			_strcpy(temp, token);
		else
			_strcpy(temp, token), _strcat(temp, "/"), _strcat(temp, command);
		if (access(temp, X_OK) == 0 && !access(temp, F_OK))
		{
			executable = temp;
			break;
		}
		free(temp);
		token = strtok(NULL, delim);
	}
	return (executable);
}



/**
 * exe_child - function that executes the child process
 * @av: pointer to the argument count
 * Return: 0 if successful
 */
int exe_child(char *av[])
{
	char *execute;
	int exec;

	execute = check_exec(av[0]);

	if (execute == NULL)
	{
		perror("Executable not found.\n");
		return (-1);
	}
	exec = execve(execute, av, environ);
	if (exec == -1)
	{
		perror("Execve failed");
		return (-1);
	}
	return (0);
}


/**
 * exe_parent - function to keep parent process on hold until child execute
 * @pid: the child process id
 * Return: 0 if successful, -1 otherwise
 */

int exe_parent(pid_t pid)
{
	int status, wait_res = waitpid(pid, &status, 0);

	if (wait_res == -1)
	{
		perror("waitpid failed");
		return (-1);
	}
	return (0);
}


/**
 * exe_command - function to execute the command entered
 * @comm_cache: command entered by users
 * Return: the pid of the calling process
 */

int exe_command(char *comm_cache)
{
	char *args[MAX_ARGUMENTS], *executable;
	pid_t pid;
	int result;

	if (prep_com_args(comm_cache, args) == -1)
		return (-1);
	if (_strcmp(args[0], "env") == 0)
		return (env_print());
	if (_strcmp(args[0], "cd") == 0)
		return (dir_change(args));
	if (checks_builtin(args, comm_cache))
		return (0);

	executable = find_com(args[0], getenv("PATH"));
	if (executable == NULL)
	{
		perror("Command not found.\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed"), free(executable);
		return (-1);
	} else if (pid == 0)
	{
		result = exe_child(args), free(executable);
		return (result);
	}
	else
	{
		free(executable);
		return (exe_parent(pid));
	}
}
