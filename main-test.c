#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * main -main function
 * Return: 0
 **/
int main(void)
{
	extern char **environ;
	char **path_var = print_path(environ);
	char **argv = malloc(10 * sizeof(char *));
	ssize_t check_length;
	size_t len = 0;
	char *inputstring = NULL;
	char *token;

	while (1)
	{

		write(1, ":) ", 3);
		check_length = getline(&inputstring, &len, stdin);
		inputstring[check_length - 1] = '\0';
		if (check_length == -1)
		{
			perror("Error: ");
			free(inputstring);
			exit(EXIT_FAILURE);
		}
		else if (check_length > 1)
		{
			inputstring[check_length - 1] = '\0';
			token = strtok(inputstring, " ");

			if (inputstring[check_length - 1] == '\n')
				inputstring[check_length - 1] = '\0';
			int j = 0;

			while (token != NULL)
			{
				argv[j] = token;
				token = strtok(NULL, " ");
				j++;
			}
			argv[j] = NULL;
			char *myexit = "exit";

			if (compare_strings(argv[0], myexit))
			{
				write(1, "Exiting the program....\n", 30);
				sleep(2);
				exit(0);
			}
			char **tmp = path_var;
			char **conc = malloc(50 * sizeof(char *));
			int m = 0;
			char **myargv = malloc(2 * sizeof(char *));
			int myargc = 2;
			int status = -99;
			int c_index = 99;
			char **t_argv = malloc(2 * sizeof(char *));

			if (j < 2)
			{
				t_argv[0] = argv[0];
				t_argv[1] = argv[0];
				status = _stat(myargc, t_argv);
			}
			else if (j >= 2)
			{
				t_argv[0] = argv[0];
				t_argv[1] = argv[0];
				status = _stat(myargc, t_argv);
			}
			if (status > 0)
			{
				fork_and_wait(argv[0], argv, environ);
			}
			else
			{

				while ((*tmp != NULL) && (c_index == 99))
				{
					conc[m] = concat_strings(*tmp, argv[0]);
					myargv[0] = conc[m];
					myargv[1] = conc[m];
					status = _stat(myargc, myargv);
					if (status == 1)
					{
						c_index = m;
						break;
					}
					tmp++;
					m++;
				}
				char *command;

				if ((c_index != 99))
				{
					command = conc[m];
					fork_and_wait(command, argv, environ);
				}
				if (c_index == 99)
				{
					write(1, "command [", 10);
					write(1, argv[0], 20);
					write(1, "] not found\n", 20);
				}
				int i = 0;

				for (i = 0; i < 10; i++)
				argv[i] = NULL;
				token = NULL;
				inputstring = NULL;
				len = 0;
				check_length = 0;
				j = 0;
			}
		}

	}
	return (0);
}
