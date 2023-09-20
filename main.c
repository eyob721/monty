#include "lib.h"
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
	queue_t *front = NULL, *rear = NULL;

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
		build_queue(&front, &rear, file_buf);
		print_queue(front);
	}
	close(fd);
	free(file_buf);
	return (EXIT_SUCCESS);
}

/**
 * build_queue - builds a queue of instructions from the file buffer.
 * @front: double pointer to the front of the queue
 * @rear: double pointer to the rear of the queue
 * @file_buf: pointer to the file buffer
 *
 * Return: void
 */
void build_queue(queue_t **front, queue_t **rear, char *file_buf)
{
	char *line = NULL, *opcode = NULL, *oparg = NULL;
	char *line_save = NULL, *op_save = NULL;

	if (file_buf == NULL)
		return;
	line = _strtok_r(file_buf, "\n", &line_save);
	while (line != NULL)
	{
		opcode = _strtok_r(line, " ", &op_save);
		oparg = _strtok_r(NULL, " ", &op_save);
		enqueue(front, rear, opcode, oparg);
		line = _strtok_r(NULL, "\n", &line_save);
	}
}
