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
	if (execve(command, argv, env) == -1)
	{
		perror("Error: (Our_execve) ");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);

}
