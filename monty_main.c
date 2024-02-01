#include "lib.h"
#include "monty.h"

/**
 * main - the monty program
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, or 1 on failure
 */
int main(int argc, char **argv)
{
	int line_size = 0, line_number = 0, fd, bytes_read;
	char *line_buf = NULL;

	if (argc != 2)
	{
		_dprintf(STDERR_FILENO, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == OPEN_ERR)
	{
		_dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	bytes_read = read_line(fd, &line_buf, &line_size);
	while (bytes_read != READ_EOF)
	{
		++line_number;
		_printf("[%d]: %s\n", line_number, line_buf);
		bytes_read = read_line(fd, &line_buf, &line_size);
	}
	close(fd);
	free(line_buf);
	return (EXIT_SUCCESS);
}
