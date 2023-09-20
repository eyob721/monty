#include "monty.h"

/**
 * read_file - a function that reads a file
 * @fd: file discriptor of the file
 * @buf: double pointer to the buffer
 * @size: pointer to the buffer size
 *
 * Return: number of characters read, or -1 if an error occurs
 * Description:
 *		- Use a temporary buffer for reading a file
 *		- When reading from a file, the number of bytes read is the amount of
 *		  bytes specified in the BUF_SIZE macro, minus 1 for a null byte.
 */
int read_file(int fd, char **buf, int *size)
{
	char tmp_buf[FILE_BUF_SIZE] = {0};
	int bytes_read, buf_pos = 0;

	if (*buf == NULL)
	{
		*size = FILE_BUF_SIZE;
		*buf = _realloc(*buf, 0, *size);
		if (*buf == NULL)
			return (READ_ERR);
	}

	bytes_read = read(fd, tmp_buf, FILE_BUF_SIZE - 1);
	while (bytes_read != READ_EOF && bytes_read != READ_ERR)
	{
		if (bytes_read >= (*size - buf_pos))
		{
			*buf = _realloc(*buf, *size, *size + FILE_BUF_SIZE);
			*size += FILE_BUF_SIZE;
		}
		_memcpy(*buf + buf_pos, tmp_buf, bytes_read);
		buf_pos += bytes_read;
		if ((*buf)[buf_pos - 1] == '\n')
		{
			(*buf)[buf_pos - 1] = '\0';
			return (buf_pos);
		}
		bytes_read = read(fd, tmp_buf, FILE_BUF_SIZE - 1);
	}
	return (bytes_read);
}

/**
 * get_file_line - a function that gets the next line token from a file buffer
 * @start: starting point of line token
 * @save_ptr: a double pointer to save the start of the next token
 *
 * Return: a line from the file buffer
 * Description:
 *     - In the case where there is an empty line, then the function
 *       returns an empty token.
 *     - The starting point for the next token (i.e. save_ptr), is determined
 *       in the _strtok_r function.
 */
char *get_file_line(char *start, char **save_ptr)
{
	char *line = NULL;

	if (save_ptr == NULL || (start == NULL && *save_ptr == NULL))
		return (NULL);

	/* Determine starting point */
	start = start != NULL ? start : *save_ptr;

	/* In case of an empty line, return an empty string */
	if (*start == '\n')
	{
		*save_ptr = start + 1;
		*start = '\0';
		return (start);
	}

	line = _strtok_r(start, "\n", save_ptr);
	return (line);
}

/**
 * is_integer - a function that check if a given string is an integer string
 * @str: a string
 *
 * Return: 1 if the string is an integer, 0 otherwise
 */
int is_integer(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (!_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}
