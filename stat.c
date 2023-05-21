#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
/**
 * _stat - a function that checks the status of the file
 * @argc: number of arguments
 * @argv: arguments
 * Return: value
 */

int _stat(int argc, char **argv)
{
	unsigned int i = 1;
	struct stat status;

	if (argc < 2)
	{
		return (-1);
	}
	while (argv[i])
	{
		if (stat(argv[i], &status) == 0)
		{
			return (i);
		}
		else
		{
			return (-99);
		}
		i++;
	}
	return (0);
}
