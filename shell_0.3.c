#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
/**
 * check_pid - a function to run execve function if all checks are passed
 * @pid: pid
 * @inputline: memory to free
 * @argv: arguments
 * @env: environment
 * Return: int
 */
int check_pid(int pid, char *inputline, char **argv char **env)
{
	if (pid == -1)
	{
		free(inputline);
		perror("Failed to create a process");
	}
	if (pid == 0)
	{
		our_execve(argv[0], argv, env);
		free(inputline);
	}
}
/**
 * main -main function
 * @argc: no of arguments
 * @argv: arguments
 * @env: environment
 * Return: 0
 */
int main(int argc, char **argv, char **env)
{

	char *inputline = NULL;
	size_t len = 0;
	ssize_t bytes;
	char *token;
	int i = 0;
	int our_pid;

	if (argc < 1)
		return (-1);
	while (1)
	{
		printf(":) ");

		bytes = getline(&inputline, &len, stdin);
		if (bytes == -1)
		{
			perror("Error: (getline)");
			free(inputline);
			exit(EXIT_FAILURE);
		}
		printf("%s\n", inputline);

		token = strtok(inputline, " ");

		printf("Before looping\n");
		while (token != NULL)
		{
			argv[i] = token;
			printf("loop %d\n", i);
			printf("%s\n", argv[i]);
			i++;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;
		printf("%s\n", argv[0]);
		/* create a child process and let the child run execve function*/
		our_pid = fork();
		check_pid(our_pid, inputline, argv, env);
	}
	return (0);
}
