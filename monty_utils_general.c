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

/**
 * is_integer - checks if a given string is an integer in string format
 * @str: given string
 *
 * Return: 1 if the string is an integer, 0 otherwise
 */
int is_integer(char *str)
{
	int i = 0, minus_sign_flag = 0;

	if (str == NULL)
		return (0);
	for (i = 0; str[i] != '\0'; ++i)
	{
		/* Allow the first minus sign encountered */
		if (str[i] == '-' && !minus_sign_flag)
		{
			minus_sign_flag = 1;
			continue;
		}
		if (!_isdigit(str[i]))
			return (0);
	}
	return (1);
}

/**
 * remove_comment_part - removes parts of the line that are after a comment
 * @line: a line in the file buffer
 *
 * Return: void
 */
void remove_comment_part(char *line)
{
	char *comment_ptr;

	comment_ptr = _strchr(line, '#');
	if (comment_ptr != NULL)
		*comment_ptr = '\0';
}

/**
 * free_stack - frees the stack_t doubly linked list
 * @top: pointer to the top of the stack
 *
 * Return: void
 */
void free_stack(stack_t *top)
{
	stack_t *tmp;

	while (top != NULL)
	{
		tmp = top;
		top = top->prev;
		tmp->prev = tmp->next = NULL;
		free(tmp);
	}
}
