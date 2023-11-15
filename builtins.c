#include "main.h"

/**
 * dir_change - function that changes the directory
 * @ags: arguments
 *
 * Return: 0 on success
 */

int dir_change(char *ags[])
{
	if (ags[1] == NULL)
	{
		write(STDERR_FILENO, "cd: no arguments\n", 17);
		return (1);
	}
	if (chdir(ags[1]) != 0)
	{
		char *error_msg = "cd: ";

		write(STDERR_FILENO, error_msg, _strlen(error_msg));
		write(STDERR_FILENO, ags[1], _strlen(ags[1]));
		write(STDERR_FILENO, ": file does not exist\n", 22);
		return (1);
	}
	return (0);
}


/**
 * env_print - function that prints environment
 *
 * Return: 0 on success
 */

int env_print(void)
{
	size_t ln;
	char **env = environ;

	while (*env)
	{
		ln = _strlen(*env), write(STDOUT_FILENO, *env, ln);
		write(STDOUT_FILENO, "\n", 1), env += 1;
	}
	return (0);
}


/**
 * _setenv - functio that sets the environment variable
 * @n: name of variable
 * @v: value env
 * @ov: what does the overwriting
 *
 * Return: 0 on success!
 */

int _setenv(const char *n, const char *v, int ov)
{
	size_t n_len, v_len, env_len;
	int i = 0;
	char *env_var;

	if (getenv(n) != NULL && ov == 0)
		return (0);
	n_len = _strlen(n), v_len = _strlen(v), env_len = n_len + 1 + v_len + 1;

	env_var = (char *)malloc(env_len);

	if (env_var == NULL)
		return (-1);
	_strcpy(env_var, n), env_var[n_len] = '=', _strcpy(env_var + n_len + 1, v);
	if (environ == NULL)
		return (-1);
	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], n, n_len) == 0 && environ[i][n_len] == '=')
			break;
		i += 1;
	}
	if (environ[i] != NULL)
		free(environ[i]), environ[i] = env_var;
	else
		environ[i] = env_var, environ[i + 1] = NULL;
	return (0);
}

/**
 * _setenv2 - functio that sets the environment variable
 * @n: name of variable
 * @v: value env
 * @ov: what does the overwriting
 *
 * Return: 0 on success!
 */

int _setenv2(const char *n, const char *v, int ov)
{
	int i, env_count;
	char *var, *new_var, **new_environ;
	size_t len;

	if (n == NULL || n[0] == '\0' || v == NULL)
		return (-1);
	for (i = 0; environ[i] != NULL; i++)
	{
		var = environ[i];
		if (_strncmp(var, n, _strlen(n)) == 0 && var[_strlen(n)] == '=')
		{
			if (!ov)
			{
				return (0);
			}
			else
			{
				free(environ[i]);
				break;
			}
		}
	}
	len = _strlen(n) + _strlen(v) + 2, new_var = (char *)malloc(len);
	if (new_var == NULL)
		return (-1);
	_strcpy(new_var, n), _strcat(new_var, "="), _strcat(new_var, v);
	env_count = 0;
	while (environ[env_count] != NULL)
		env_count += 1;
	new_environ = (char **)malloc((env_count + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		free(new_var);
		return (-1);
	}
	for (i = 0; i < env_count; i++)
		new_environ[i] = environ[i];
	new_environ[env_count] = new_var, new_environ[env_count + 1] = NULL;
	environ = new_environ;
	return (0);
}
