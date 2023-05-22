#include "shell.h"
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
