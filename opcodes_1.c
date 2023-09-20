#include "lib.h"
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
	/* Check if the opcode argument is an integer */
	if (!is_integer(monty.front->oparg))
	{
		_dprintf(STDERR_FILENO, "L%d: usage: push integer\n",
				line_number);
		free_stack(*top);
		free_monty();
		exit(EXIT_FAILURE);
	}
	/* Allocate memory */
	new_stack = malloc(sizeof(stack_t));
	if (new_stack == NULL)
	{
		_dprintf(STDERR_FILENO, "Error: malloc failed\n");
		free_stack(*top);
		free_monty();
		exit(EXIT_FAILURE);
	}
	/* Add the new stack node to the stack */
	new_stack->n = _atoi(monty.front->oparg);
	new_stack->prev = *top;
	new_stack->next = NULL;
	if (*top != NULL)
		(*top)->next = new_stack;
	*top = new_stack;
}

/**
 * pall - hanldes the pall opcode
 * @top: double pointer to the op of the stack
 * @line_number: current line number in the file
 *
 * Return: void
 */
void pall(stack_t **top, unsigned int line_number)
{
	stack_t *tmp;

	(void)line_number;
	if (top == NULL)
		return;
	for (tmp = *top; tmp != NULL; tmp = tmp->prev)
		_printf("%d\n", tmp->n);
}
