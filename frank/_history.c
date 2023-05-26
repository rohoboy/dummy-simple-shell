#include "shell.h"
/**
 * get_history_file - a function to get history file
 * @info: info struct
 * Return: allocated string that contains history file
 */
char *get_history_file(info_t *info)
{
	char *dir;
	char *buffer;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
* write_history -a function that creates a file or appends to an existing file
 * @info: info struct
 * Return: 1 on success else -1 on failure
 */
int write_history(info_t *info)
{
	list_t *node = NULL;
	ssize_t fd;
	char *filename = get_history_file(info);

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_history - a function reads history from file
 * @info: info struct
 * Return: histcount on success else 0
 */
int read_history(info_t *info)
{
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);

	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - a function that adds entry to a history linked list
 * @info: info tructure that contains potential arguments.
 * @buf: buffer
 * @linecount: the number of lines
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *c_node = NULL;

	if (info->history)
		c_node = info->history;
	add_node_end(&c_node, buf, linecount);

	if (!info->history)
		info->history = c_node;
	return (0);
}
/**
 * renumber_history - re-numbers history linked list after changes
 * @info: info structure
 * Return: the new history count
 */
int renumber_history(info_t *info)
{
	list_t *c_node = info->history;
	int i = 0;

	while (c_node)
	{
		c_node->num = i++;
		c_node = c_node->next;
	}
	return (info->histcount = i);
}

