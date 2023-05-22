#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * fork_and_wait - a function to fork, wait and run execve
 * @command: the command to execut
 * @argv: command line arguments
 * @env: environment
 * Return: 0 if success or -1 if failed
 */
int fork_and_wait(char *command, char **argv, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		return (-1);
	}
	else if (pid == 0)
	{
		our_execve(command, argv, env);
	}
	else
	{
		wait(&status);
	}

	return (0);
}
