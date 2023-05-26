#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: info struct
 * Return: void
 */
void clear_info(info_t *info)
{
	info->path = NULL;
	info->argc = 0;
	info->arg = NULL;
	info->argv = NULL;
}

/**
 * set_info - a function that initializes info_t struct
 * @info: struct address
 * @av: arguments
 * Return: void
 */
void set_info(info_t *info, char **av)
{
	info->fname = av[0];
	int i = 0;

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		while (info->argv && info->argv[i])
			i++;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - a function that frees info_t struct fields
 * @info: info struct
 * @all: number of fields
 * Return: void
 */
void free_info(info_t *info, int all)
{
	info->argv = NULL;
	info->path = NULL;
	ffree(info->argv);
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

