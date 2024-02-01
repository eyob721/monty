#include "lib.h"
#include "monty.h"

monty_t monty = {NULL, NULL, EXIT_SUCCESS, NULL};

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
		get_opcode_oparg(line_buf);
		_printf("[%d]: opcode: [%s] oparg: [%s]\n", line_number,
				monty.cur_opcode, monty.cur_oparg);
		bytes_read = read_line(fd, &line_buf, &line_size);
	}
	close(fd);
	free(line_buf);
	return (EXIT_SUCCESS);
}

/**
 * get_opcode_oparg - gets the opcode and oparg from the line buffer.
 * @line_buf: pointer to the line buffer
 *
 * Return: void
 */
void get_opcode_oparg(char *line_buf)
{
	char *line_ptr = line_buf, *line_save = NULL;

	if (line_buf == NULL)
		return;

	/* Skip initial spaces */
	while (*line_ptr == ' ')
		++line_ptr;

	monty.cur_opcode = _strtok_r(line_ptr, " ", &line_save);
	monty.cur_oparg = _strtok_r(NULL, " ", &line_save);
}
