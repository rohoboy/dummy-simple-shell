#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

/**
 * our_execve - a function to execute execve
 * @command: command to execute
 * @argv: array of arguments
 * @env: environment
 * Return: success or failed
 */
int our_execve(char *command, char **argv, char **env)
{
	if (access(command, X_OK) == -1)
	{
		perror("Error accessing file (says our_execve)");
		return (1);
	}
	int argc = 0;

	while (argv[argc] != NULL)
	{
		argc++;
	}

	int envc = 0;

	while (env[envc] != NULL)
		envc++;
	if (execve(command, argv, env) == -1)
	{
		perror("Error: (says our_execve) ");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);

}
