#include "monty.h"

monty_t monty = INITIALIZE_MONTY;

/**
 * main - the monty program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, or 1 on failure
 */
int main(int ac, char **av)
{
	int line_size = 0, line_number = 0, fd, bytes_read;
	char *line_buf = NULL;
	stack_t *top = NULL;
	void (*execute_opcode)(stack_t **top, unsigned int line_number);

	if (ac != 2)
	{
		_dprintf(STDERR_FILENO, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == OPEN_ERR)
	{
		_dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		return (EXIT_FAILURE);
	}
	bytes_read = read_line(fd, &line_buf, &line_size);
	while (bytes_read != READ_EOF && monty.exit_status == EXIT_SUCCESS)
	{
		++line_number;
		get_opcode_oparg(line_buf);
		if (monty.cur_opcode != NULL) /* NULL is a case of an empty line */
		{
			execute_opcode = get_opcode_function(monty.cur_opcode);
			if (execute_opcode == NULL)
			{
				_dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n",
						line_number, monty.cur_opcode);
				monty.exit_status = EXIT_FAILURE;
				break;
			}
			execute_opcode(&top, line_number);
		}
		bytes_read = read_line(fd, &line_buf, &line_size);
	}
	close(fd);
	free(line_buf);
	free_stack(top);
	return (monty.exit_status);
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

	remove_comment(line_ptr);
	monty.cur_opcode = _strtok_r(line_ptr, " ", &line_save);
	monty.cur_oparg = _strtok_r(NULL, " ", &line_save);
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
		{"pop", pop},
		{"swap", swap},
		{"nop", nop},
		{"add", add_opcode},
		{"sub", sub_opcode},
		{"div", div_opcode},
		{"mul", mul_opcode},
		{"mod", mod_opcode},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{"rotr", rotr},
		{"stack", change_to_stack},
		{"queue", change_to_queue},
		{NULL, NULL}
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

