#include "monty.h"

/**
 * push - hanldes the push opcode
 * @top: double pointer to the op of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void push(stack_t **top, unsigned int lnum)
{
	stack_t *new_stack = NULL;

	if (top == NULL)
		return;
	/* Check if the opcode argument is an integer */
	if (!is_integer(monty.node->oparg))
	{
		_dprintf(STDERR_FILENO, "L%d: usage: push integer\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	/* Allocate memory */
	new_stack = malloc(sizeof(stack_t));
	if (new_stack == NULL)
	{
		_dprintf(STDERR_FILENO, "Error: malloc failed\n");
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	/* Add the new stack node to the stack */
	new_stack->n = _atoi(monty.node->oparg);
	new_stack->prev = *top;
	new_stack->next = NULL;
	if (*top != NULL)
		(*top)->next = new_stack;
	*top = new_stack;
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * pall - hanldes the pall opcode
 * @top: double pointer to the op of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void pall(stack_t **top, unsigned int lnum)
{
	stack_t *tmp;

	(void)lnum;
	if (top == NULL)
		return;
	for (tmp = *top; tmp != NULL; tmp = tmp->prev)
		_printf("%d\n", tmp->n);
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * pint - hanldes the pint opcode
 * @top: double pointer to the op of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void pint(stack_t **top, unsigned int lnum)
{
	if (top == NULL)
		return;
	if (*top == NULL) /* Empty stack */
	{
		_dprintf(STDERR_FILENO, "L%d: can't pint, stack empty\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	_printf("%d\n", (*top)->n);
}
