#include "monty.h"

/**
 * read_line - a function that reads a line from a file descriptor
 * @fd: file descriptor
 * @line_buff: double pointer to the line buffer
 * @line_size: pointer to the line buffer size
 *
 * Return: number of characters read, or -1 if an error occured
 */
int read_line(int fd, char **line_buff, int *line_size)
{
	char ch;
	int bytes_read = READ_EOF, total_read = 0, pos = 0;

	if (fd == OPEN_ERR)
		return (READ_ERR);
	if (*line_buff == NULL)
	{
		*line_size = LINE_BUFF_SIZE;
		*line_buff = _realloc(*line_buff, 0, *line_size);
		if (*line_buff == NULL)
			return (READ_ERR);
	}

	bytes_read = read(fd, &ch, 1);
	while (bytes_read != READ_EOF && bytes_read != READ_ERR)
	{
		if (pos == *line_size - 1)
		{
			*line_buff =
				_realloc(*line_buff, *line_size, *line_size + LINE_BUFF_SIZE);
			*line_size += LINE_BUFF_SIZE;
		}
		(*line_buff)[pos] = ch;
		total_read += bytes_read;
		if ((*line_buff)[pos] == '\n')
			break;
		++pos;
		bytes_read = read(fd, &ch, 1);
	}
	(*line_buff)[pos] = '\0'; /* terminate new line character */
	return (total_read);
}
