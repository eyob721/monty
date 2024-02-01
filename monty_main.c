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
	int line_buf_size = 0, line_num = 0, fd, bytes_read;
	char *line_buf = NULL;
	stack_t *top = NULL;
	void (*execute_opcode)(stack_t **top, unsigned int line_number);

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
	bytes_read = read_line(fd, &line_buf, &line_buf_size);
	while (bytes_read != READ_EOF)
	{
		++line_num;
		get_opcode_oparg(line_buf);
		if (monty.cur_opcode != NULL) /* Here NULL means an empty line */
		{
			execute_opcode = get_opcode_function(monty.cur_opcode);
			if (execute_opcode == NULL) /* Here NULL means an invalid opcode */
			{
				_dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n",
						 line_num, monty.cur_opcode);
				monty.exit_status = EXIT_FAILURE;
				break;
			}
			execute_opcode(&top, line_num);
		}
		bytes_read = read_line(fd, &line_buf, &line_buf_size);
	}
	close(fd);
	free(line_buf);
	free_stack(top);
	return (monty.exit_status);
}

/**
 * get_opcode_oparg - gets the opcode and oparg from the line buffer
 * @line_buf: pointer to the line buffer
 *
 * Return: void
 */
void get_opcode_oparg(char *line_buf)
{
	char *line_ptr = line_buf, *line_save_ptr = NULL;

	if (line_buf == NULL)
		return;

	remove_comment_part(line_ptr);

	/* Skip initial spaces */
	while (*line_ptr == ' ')
		++line_ptr;

	monty.cur_opcode = _strtok_r(line_ptr, " ", &line_save_ptr);
	monty.cur_oparg = _strtok_r(NULL, " ", &line_save_ptr);
}

/**
 * get_opcode_function - fetches the handler function for an opcode
 * @opcode: given opcode
 *
 * Return: function of the opcode, or NULL if opcode is not supported
 */
void (*get_opcode_function(char *opcode))(stack_t **top, unsigned int line)
{
	instruction_t opcode_fun[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop",	pop },
		{"swap", swap},
		{"add",	_add},
		{"sub",	_sub},
		{"div",	_div},
		{"mul",	_mul},
		{"mod",	_mod},
		{"nop",	nop },
		{"pchar",	pchar },
		{"pstr",	pstr },
		{"rotl",	rotl },
		{NULL,   NULL}
	};
	int i = 0;

	while (opcode_fun[i].opcode != NULL)
	{
		if (_strcmp(opcode_fun[i].opcode, opcode) == 0)
			return (opcode_fun[i].f);
		++i;
	}

	return (NULL);
}
