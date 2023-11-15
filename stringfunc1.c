#include "main.h"


/**
 * _strncmp - compare string values
 * @str1: input value
 * @str2: input value
 * @n: byte
 *
 * Return: str1[i] - str2[i]
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		if (*str1 == '\0')
			break;
		str1 += 1, str2 += 1, n -= 1;
	}
	return (0);
}


/**
 * _strcmp - compare string values
 * @str1: input value
 * @str2: input value
 *
 * Return: str1[i] - str2[i]
 */

int _strcmp(char *str1, char *str2)
{
	int indx = 0;

	while ((str1[indx] != '\0') && (str2[indx] != '\0'))
	{
		if (str1[indx] != str2[indx])
			return (str1[indx] - str2[indx]);
		indx += 1;
	}
	return (0);
}



/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, const char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _strcpy - Copy a string
 * @dest: Destination value
 * @src: Source value
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, const char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i++] = '\0';
	return (dest);
}


/**
 * _strdup - function that returns pointer to a newly allocate
 * @st: input string
 *
 * Return: pointer to a newly allocated space in memory
 */

char *_strdup(char *st)
{
	/* initializing variables */
	int index = 0, x = 0;
	char *s;

	if (st == NULL)
		return (NULL);
	while (st[index] != '\0')
		index += 1;
	s = malloc(sizeof(char) * (index + 1));
	/* check for null return by malloc */
	if (s == NULL)
		return (NULL);
	for (x = 0; st[x]; x += 1)
		s[x] = st[x];
	return (s);
}
