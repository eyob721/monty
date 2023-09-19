#include "monty.h"

/**
 * main - the monty program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, or 1 on error
 */
int main(int ac, char **av)
{
	int fd, bytes_read = READ_EOF, buf_size = 0;
	char *file_buf = NULL;

	if (ac != 2)
	{
		_dprintf(STDERR_FILENO, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == OPEN_FILE_ERR)
	{
		_dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		return (EXIT_FAILURE);
	}
	bytes_read = read_file(fd, &file_buf, &buf_size);
	if (bytes_read != READ_EOF && bytes_read != READ_ERR)
	{
		_printf("---------------------------------------------------------\n");
		_printf("%s\n", file_buf);
		_printf("---------------------------------------------------------\n");
	}
	close(fd);
	free(file_buf);
	return (EXIT_SUCCESS);
}
