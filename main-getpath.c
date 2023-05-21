#include "shell.h"
#include <stdio.h>
extern char **environ;
int main()
{
	/*char *filename = "ls";
	char *str1 = "hello";
	char *str2 = "world";
	concat_strings(str1, str2);*/
	char *filename = "ls";

	char ** path = create_abs_path(filename, environ);
	char **tmp = path;

	printf("Entering while loop ... \n");
	while (*tmp != NULL)
	{
		printf("%s\n", *tmp);
		tmp++;
	}
	/*char **arrstr = print_path(environ);*/


	return (0);
}
