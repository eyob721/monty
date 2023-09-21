#include "monty.h"

/**
 * push - handles the push opcode
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
 * pall - handles the pall opcode
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
 * pint - handles the pint opcode
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
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * pop - handles the pop opcode
 * @top: double pointer to the op of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void pop(stack_t **top, unsigned int lnum)
{
	stack_t *tmp;

	if (top == NULL)
		return;

	if (*top == NULL) /* Empty stack */
	{
		_dprintf(STDERR_FILENO, "L%d: can't pop an empty stack\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	/* Remove the top node */
	tmp = *top;
	*top = (*top)->prev;
	if (*top != NULL)
		(*top)->next = NULL;
	tmp->prev = tmp->next = NULL;
	free(tmp);
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * swap - handles the swap opcode
 * @top: double pointer to the op of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void swap(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *top_node, *second_node, *third_node;

	if (top == NULL)
		return;
	stack_len = get_stack_len(*top);
	if (stack_len < 2)
	{
		_dprintf(STDERR_FILENO, "L%d: can't swap, stack too short\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	/* Swap the top two nodes, and correct the third node, if there is one */
	top_node = *top;
	second_node = top_node->prev;
	third_node = second_node->prev;

	top_node->prev = third_node;
	top_node->next = second_node;

	second_node->prev = top_node;
	second_node->next = *top;

	if (third_node != NULL)
		third_node->next = second_node;

	*top = second_node;
	monty.exit_status = EXIT_SUCCESS;
}
