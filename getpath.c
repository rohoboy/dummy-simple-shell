#include <stdio.h>
#include "shell.h"
#include <stdlib.h>
/**
 * compare_strings - a function to compare strings
 * @str1: first string
 * @str2: second string
 * Return: 1 if true or 0 if false
 */
int compare_strings(const char *str1, const char *str2)
{
	while (*str2)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	return (1);
}
/**
 * concat_strings -function to concatenate strings
 * @str1: first string
 * @str2: second string
 * Return: concatenated strings
 */
char *concat_strings(char *str1, char *str2)
{
	int l1 = 0, l2 = 0, i, j;
	char *res;

	while (str1[l1] != '\0')
		l1++;
	while (str2[l2] != '\0')
		l2++;

	res = (char *) malloc((l1 + l2 + 1) * sizeof(char));

	for (i = 0; i < l1; i++)
		res[i] = str1[i];
	for (j = 0; j < l2; j++)
		res[l1 + j] = str2[j];
	res[l1 + l2] = '\0';
	return (res);
}
/**
 * print_path - a function that returns the path
 * @env: environment
 * Return: the path
 */
char **print_path(char **env)
{
	char **cenv = env;
	int i = 0;
	const char *path = NULL;
	char *token;
	/*char **arrstr = malloc(1024 * sizeof(char));*/

	while (*cenv)
	{
		if (compare_strings(*cenv, "PATH="))
		{
			path = *cenv + 5;
			break;
		}
		cenv++;
	}
	char **arrstr = (char **)malloc(1024 * sizeof(char *));

	if (path)
	{
		const char *delimiter = ":";

		token = strtok((char *)path, delimiter);
		while (token != NULL)
		{
			arrstr[i] = token;
			i++;
			token = strtok(NULL, delimiter);
		}
	}
	arrstr[i] = NULL;
	return (arrstr);
}

