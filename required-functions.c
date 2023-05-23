#include "shell.h"
#include <stdbool.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
/**
 * our_strlen - function to return the length of a string
 * @str: string to check
 * Return: size of the string
 */
int our_strlen(char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;
	return (len);
}
/**
 * print_env - function to print the environment
 * @env: environment variables
 * Return: void
 */
void print_env(char **env)
{
	int len;

	while (*env != NULL)
	{
		char *myenv = *env;
		len = our_strlen(myenv);
		env++;
		write(1, myenv, len);
		write(1, "\n",1);
	}
}
/**
 * our_getline - a function that immitates getline
 * @lineptr: linepointer
 * @n: the size of our linepointer
 * @stream: file/ where we are reading
 * Return: the linepointer
 */
ssize_t our_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[BUFFER_SIZE];
	/*size_t bytes_to_read;*/
	size_t total_bytes_to_read = 0;
	static size_t b_pos = 0;
	static size_t b_size = 0;
	char ccp;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	if ((*lineptr == NULL) || (*n == 0))
	{
		*n = BUFFER_SIZE;
		*lineptr = (char *)malloc(*n);
		if (lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (b_pos >= b_size)
		{
			b_size = read(fileno(stream), buffer, BUFFER_SIZE);
			if (b_size == (size_t)-1 || b_size == 0)
				break;
			b_pos = 0;
		}
		ccp = buffer[b_pos++];
		(*lineptr)[total_bytes_to_read++] = ccp;

		if (total_bytes_to_read >= *n)
		{
			b_size += BUFFER_SIZE;
			char *new_lineptr = (char *)realloc(*lineptr, b_size);
			if (new_lineptr == NULL)
				return (-1);
			*lineptr = new_lineptr;
			*n = b_size;
		}
		if (ccp == '\n')
			break;
	}
	if (total_bytes_to_read == 0)
		return (-1);
	(*lineptr)[total_bytes_to_read] = '\0';

	return (total_bytes_to_read);
}
/**
 * our_stktok - a function that immitates stktok
 * @str: a string to breake to tokens
 * @delim: delimeters
 * Return: token
 */
char *our_strtok(char *str, const char *delim)
{
	static char* token = NULL;
	static char* n_token = NULL;
	size_t i;

	if (str != NULL)
		token = str;
	else if (n_token == NULL)
		return (NULL);
	else
		token = n_token;
	if (*token == '\0')
		return (NULL);

	char *res = token;
	bool is_delim = false;

	while (*token != '\0')
	{
		is_delim = false;
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*token == delim[i])
			{
				is_delim = true;
				break;
			}
		}
		if (is_delim)
		{
			*token = '\0';
			token++;
			break;
		}
		token++;
	}
	n_token = token;
	return (res);
}
/*
 * change_dir - a function to change directory
 * @directory: directory name
 * Return: 0 if success otherwise -1
 */
int change_dir(char *directory)
{
	return (0);
}

