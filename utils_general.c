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
	char tmp_buf[BUF_SIZE] = {0};
	int bytes_read = READ_EOF, buf_pos = 0;

	if (*buf == NULL)
	{
		*size = BUF_SIZE;
		*buf = _realloc(*buf, 0, *size);
		if (*buf == NULL)
			return (READ_ERR);
	}

	bytes_read = read(fd, tmp_buf, BUF_SIZE - 1);
	while (bytes_read != READ_EOF && bytes_read != READ_ERR)
	{
		if (bytes_read >= (*size - buf_pos))
		{
			*buf = _realloc(*buf, *size, *size + BUF_SIZE);
			*size += BUF_SIZE;
		}
		_memcpy(*buf + buf_pos, tmp_buf, bytes_read);
		buf_pos += bytes_read;
		if ((*buf)[buf_pos - 1] == '\n')
		{
			(*buf)[buf_pos - 1] = '\0';
			return (buf_pos);
		}
		bytes_read = read(STDIN_FILENO, tmp_buf, BUF_SIZE - 1);
	}
	return (bytes_read);
}

