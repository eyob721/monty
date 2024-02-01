#include "monty.h"

/**
 * push - handles the push opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void push(stack_t **top, unsigned int lnum)
{
	stack_t *new_node = NULL;

	/* Check if the opcode argument is an integer */
	if (!is_integer(monty.cur_oparg))
	{
		_dprintf(STDERR_FILENO, "L%d: usage: push integer\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	/* Allocate memory */
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		_dprintf(STDERR_FILENO, "Error: malloc failed\n");
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	/* Insert the new node into the stack */
	new_node->n = _atoi(monty.cur_oparg);
	push_to_top(top, new_node);
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * pall - handles the pall opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void pall(stack_t **top, unsigned int lnum)
{
	stack_t *ptr;

	(void)lnum;
	for (ptr = *top; ptr != NULL; ptr = ptr->prev)
		_printf("%d\n", ptr->n);
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * pint - handles the pint opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void pint(stack_t **top, unsigned int lnum)
{
	if (*top == NULL) /* In the case of an empty stack or queue */
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
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void pop(stack_t **top, unsigned int lnum)
{
	stack_t *tmp;

	if (*top == NULL) /* In the case of an empty stack or queue */
	{
		_dprintf(STDERR_FILENO, "L%d: can't pop an empty stack\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}

	/* Remove top node */
	tmp = *top;
	*top = (*top)->prev;
	if (*top != NULL)
		(*top)->next = NULL;

	/* Delete previously top node */
	tmp->prev = tmp->next = NULL;
	free(tmp);

	/* Update bottom pointer */
	if (*top == NULL)
		monty.bottom = NULL;

	monty.exit_status = EXIT_SUCCESS;
}

/**
 * swap - handles the swap opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void swap(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *top_node, *second_node, *third_node;

	stack_len = get_stack_len(*top);
	if (stack_len < 2)
	{
		_dprintf(STDERR_FILENO, "L%d: can't swap, stack too short\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}

	/* Swap the top two nodes and update the third node */
	top_node = *top;
	second_node = top_node->prev;
	third_node = second_node->prev;

	top_node->prev = third_node;
	top_node->next = second_node;

	second_node->prev = top_node;
	second_node->next = *top;

	if (third_node != NULL)
		third_node->next = second_node;

	/* Update the top and bottom pointer */
	*top = second_node;
	if (stack_len == 2)
		monty.bottom = top_node;

	monty.exit_status = EXIT_SUCCESS;
}
