#include "monty.h"

void push(stack_t **top, unsigned int line_number)
{
	stack_t *new_stack = NULL;

	(void)top;
	(void)line_number;
	new_stack = malloc(sizeof(stack_t));
	if (new_stack == NULL)
	{
		_dprintf(STDERR_FILENO, "Error: malloc failed\n");
		free_monty();
		exit(EXIT_FAILURE);
	}
	free(new_stack);
	_printf("Hello from push\n");
}
