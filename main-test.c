#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
extern char **environ;

int main(int a, char **argv)
{
	ssize_t check_length;
	size_t len = 0;
	char *inputstring = NULL;
	char *token;
/*	int check_fork_and_wait;*/


	while (1)
	{
		printf(":) ");
		check_length = getline(&inputstring, &len, stdin);
		inputstring[check_length - 1] = '\0';
		if (check_length == -1)
                {
                        perror("Error: (getline)");
                        free(inputstring);
                        exit(EXIT_FAILURE);
                }
		else
		{
			token = strtok(inputstring, " ");
		}


		/*fork_and_wait(argv[1], argv, env);*/
		/*char **argv = malloc(i * sizeof(char *));*/
		int j = 0;

		while (token != NULL)
		{
			argv[j] = token;
			token = strtok(NULL, " ");
			j++;

		}

		fork_and_wait(argv[0], argv, environ);
		j = 0;
		token = NULL;

	}
	return (0);
}
