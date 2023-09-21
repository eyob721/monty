#include "monty.h"

monty_t monty = {NULL, EXIT_SUCCESS};

/**
 * main - the monty program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, or 1 on error
 * Description:
 *     - This is how the program uses the stack and queue data structures
 *     - The stack is used to execute opcode instructions.
 *     - The queue is used to arrange the instructions that are found in the
 *       monty byte code file to form, a queue.
 *     - So the program executes each opcodes in the queue on the stack.
 */
int main(int ac, char **av)
{
	int fd, buf_size = 0, bytes_read;
	char *file_buf = NULL;
	stack_t *top = NULL;
	queue_t *front = NULL, *rear = NULL;
	void (*execute_opcode)(stack_t **top, unsigned int line_number);

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
		while (front != NULL && monty.exit_status == EXIT_SUCCESS)
		{
			monty.node = dequeue(&front, &rear);
			execute_opcode = get_opcode_function(monty.node->opcode);
			if (execute_opcode == NULL)
			{
				_dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n",
						monty.node->line, monty.node->opcode);
				monty.exit_status = EXIT_FAILURE;
				free(monty.node); /* Free the executed queue node */
				break;
			}
			execute_opcode(&top, monty.node->line);
			free(monty.node); /* Free the executed queue node */
		}
	}
	close(fd), free_stack(top), free_queue(front), free(file_buf);
	return (monty.exit_status);
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

