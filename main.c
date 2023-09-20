#include "lib.h"
#include "monty.h"
#include <stdlib.h>
#include <unistd.h>

monty_t monty;

/**
 * main - the monty program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, or 1 on error
 */
int main(int ac, char **av)
{
	int bytes_read = READ_EOF, exit_code = EXIT_SUCCESS;
	stack_t *top = NULL;
	void (*execute_opcode)(stack_t **top, unsigned int line_number);

	if (ac != 2)
	{
		_dprintf(STDERR_FILENO, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	monty.fd = open(av[1], O_RDONLY);
	if (monty.fd == OPEN_FILE_ERR)
	{
		_dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		return (EXIT_FAILURE);
	}
	bytes_read = read_file(monty.fd, &monty.file_buf, &monty.buf_size);
	if (bytes_read != READ_EOF && bytes_read != READ_ERR)
	{
		build_queue();
		while (monty.front != NULL)
		{
			execute_opcode = get_opcode_function(monty.front->opcode);
			if (execute_opcode == NULL)
			{
				_dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n",
						monty.front->line, monty.front->opcode);
				exit_code = EXIT_FAILURE;
				break;
			}
			execute_opcode(&top, monty.front->line);
			free(dequeue());
		}
	}
	free_monty();
	return (exit_code);
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
		{"push",  push},
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

