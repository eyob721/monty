#include "monty.h"

/**
 * mod_opcode - handles the mod opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void mod_opcode(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *second_node;

	if (top == NULL)
		return;
	stack_len = get_stack_len(*top);
	if (stack_len < 2)
	{
		_dprintf(STDERR_FILENO, "L%d: can't mod, stack too short\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	if ((*top)->n == 0)
	{
		_dprintf(STDERR_FILENO, "L%d: division by zero\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	second_node = (*top)->prev;
	second_node->n %= (*top)->n;
	pop(top, lnum);
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * pchar - handles the pchar opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void pchar(stack_t **top, unsigned int lnum)
{
	if (top == NULL)
		return;
	if (*top == NULL)
	{
		_dprintf(STDERR_FILENO, "L%d: can't pchar, stack empty\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	if (!IS_VALID_ASCII_VALUE((*top)->n)) /* x >= 0 && x <= 255 */
	{
		_dprintf(STDERR_FILENO, "L%d: can't pchar, value out of range\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	_printf("%c\n", (*top)->n);
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * pstr - handles the pstr opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void pstr(stack_t **top, unsigned int lnum)
{
	stack_t *node = NULL;

	(void)lnum;
	if (top == NULL)
		return;
	node = *top;

	while (node != NULL && node->n != 0 && IS_VALID_ASCII_VALUE(node->n))
	{
		_printf("%c", node->n);
		node = node->prev;
	}
	_printf("\n");
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * rotl - handles the rotl opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void rotl(stack_t **top, unsigned int lnum)
{
	stack_t *top_node, *second_top;

	(void)lnum;
	if (top == NULL || *top == NULL)
		return;

	/* Find the top, second top, and the last node */
	top_node = *top;
	second_top = top_node->prev;

	/* Bring the top to the bottom */
	if (top_node != monty.last_node) /* Only rotate stack with more than 1 node */
	{
		if (second_top != NULL)
			second_top->next = NULL;
		top_node->prev = NULL;
		top_node->next = monty.last_node;
		monty.last_node->prev = top_node;
	}
	/* Update top */
	*top = second_top != NULL ? second_top : top_node;
	monty.last_node = top_node;

	monty.exit_status = EXIT_SUCCESS;
}

/**
 * rotr - handles the rotr opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void rotr(stack_t **top, unsigned int lnum)
{
	stack_t *top_node, *second_last, *last_node;

	(void)lnum;
	if (top == NULL || *top == NULL)
		return;

	/* Find the top, second last, and the last node */
	top_node = *top;
	last_node = top_node;
	while (last_node->prev != NULL)
		last_node = last_node->prev;
	second_last = last_node->next;

	/* Bring the bottom to the top */
	if (top_node != last_node) /* Only rotate stack with more than 1 node */
	{
		last_node->prev = top_node;
		last_node->next = NULL;
		top_node->next = last_node;
		if (second_last != NULL)
			second_last->prev = NULL;
	}
	/* Update top */
	*top = last_node;
	monty.last_node = second_last;

	monty.exit_status = EXIT_SUCCESS;
}

