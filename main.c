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
	queue_t *front = NULL, *rear = NULL, *node = NULL;

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
		node = dequeue(&front, &rear);
		while (node != NULL)
		{
			print_node(node);
			free(node);
			node = dequeue(&front, &rear);
		}
	}
	close(fd);
	free_queue(front);
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
	int line_no = 1;
	char *line = NULL, *opcode = NULL, *oparg = NULL;
	char *line_save = NULL, *op_save = NULL;

	if (file_buf == NULL)
		return;
	line = get_file_line(file_buf, &line_save);
	while (line != NULL)
	{
		opcode = _strtok_r(line, " ", &op_save);
		oparg = _strtok_r(NULL, " ", &op_save);
		enqueue(front, rear, opcode, oparg, line_no);
		line = get_file_line(NULL, &line_save);
		++line_no;
	}
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
