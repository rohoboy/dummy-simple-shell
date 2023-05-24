#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * main -main function
 * Return: 0
 **/
extern char **environ;
int main(void)
{
	char **environment = environ;
	char **path_var = print_path(environment);
	char **argv = malloc(10 * sizeof(char *));
	ssize_t check_length;
	size_t len = 0;
	char *inputstring = NULL;
	char *sub_token;
	char *token;
	int B_SIZE =1024;
	char cwd[B_SIZE];


	while (1)
	{

		write(1, "geniuses@peter@frank", our_strlen("geniuses@peter@frank"));
		write(1, getcwd(cwd, B_SIZE), our_strlen(getcwd(cwd, B_SIZE)));
		write(1, "# ", 2);

		check_length = our_getline(&inputstring, &len, stdin);
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
			if (inputstring[check_length - 1] == '\n')
				inputstring[check_length - 1] = '\0';
			token = our_strtok(inputstring, ";");
			int j = 0;


			while (token != NULL)
			{
				sub_token = our_strtok(token, " ");
				while (sub_token != NULL)
				{
					argv = malloc((our_strlen(sub_token) + 1) * sizeof(char));
					argv[j] = sub_token;
					sub_token = our_strtok(NULL, " ");
					j++;
				}
				argv[j] = NULL;

				char *myexit = "exit";
				char *myprintenv = "env";
				char *mysetenvironment = "setenv";
				char *myunsetenvironment = "unsetenv";
				char *mychangedir = "cd";

				if (compare_strings(argv[0], myexit))
				{
					write(1, "Exiting the program....\n", 24);
					sleep(2);
					custom_exit(j, argv);
				}
				else if (compare_strings(argv[0], myprintenv))
				{
					print_env(environment);
				}
				else if (compare_strings(argv[0], mysetenvironment))
				{
					if (j != 3)
					{
						write(1, "invalid number of arguments\n", our_strlen("invalid number of arguments\n"));
					}
					else
					{
						int success = our_setenv(argv[1], argv[2], 1);

						if (success == -1)
							write(1, "unsuccessiful\n", our_strlen("unsuccessiful\n"));
					}
				}
				else if (compare_strings(argv[0], myunsetenvironment))
				{
					const char *value = argv[1];

					if (j != 2)
						write(1, "invalid number of arguments\n", our_strlen("invalid number of arguments\n"));
					else
						our_unsetenv(value);
				}
				else if (compare_strings(argv[0], mychangedir))
				{
					change_dir(argv[1], B_SIZE);
				}
				else
				{
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
						fork_and_wait(argv[0], argv, environment);
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
							fork_and_wait(command, argv, environment);
						}
						if (c_index == 99 && *tmp == NULL)
						{
							write(1, "command [", 10);
							write(1, argv[0], our_strlen(argv[0]));
							write(1, "] not found\n", our_strlen("] not found\n"));
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
				printf("%s\n", token);
			}
			token = strtok(NULL, ";");
		}
		int clear = 0;
		for (clear = 0; clear < 10; clear++)
			free(argv[clear]);

	}
	free(argv);
	return (0);
}
