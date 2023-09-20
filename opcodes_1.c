#include "monty.h"

/**
 * push - hanldes the push opcode
 * @top: double pointer to the op of the stack
 * @line_number: current line number in the file
 *
 * Return: void
 */
void push(stack_t **top, unsigned int line_number)
{
	stack_t *new_stack = NULL;

	if (top == NULL)
		return;
	if (is_integer(monty.front->oparg) == 0)
	{
		_dprintf(STDERR_FILENO, "L%d: usage: push integer\n",
				line_number);
		free_stack(*top);
		free_monty();
		exit(EXIT_FAILURE);
	}

	new_stack = malloc(sizeof(stack_t));
	if (new_stack == NULL)
	{
		_dprintf(STDERR_FILENO, "Error: malloc failed\n");
		free_stack(*top);
		free_monty();
		exit(EXIT_FAILURE);
	}
	new_stack->n = _atoi(monty.front->oparg);
	new_stack->prev = *top;
	new_stack->next = NULL;
	if (*top != NULL)
		(*top)->next = new_stack;
	*top = new_stack;
}

