#include "monty.h"

/**
 * nop - handles the nop opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void nop(stack_t **top, unsigned int lnum)
{
	(void)top;
	(void)lnum;
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
	stack_t *node = *top;

	(void)lnum;
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
 * Description: rotl opcode rotates the stack or queue to the left
 */
void rotl(stack_t **top, unsigned int lnum)
{
	stack_t *top_node, *second_top;

	(void)lnum;
	if (*top == NULL) /* In the case of an empty stack or queue */
		return;

	/* Find the top two nodes */
	top_node = *top;
	second_top = top_node->prev;

	/* Bring the top to the bottom */
	if (top_node != monty.bottom) /* Only rotate stack with more than 1 node */
	{
		second_top->next = NULL;
		top_node->prev = NULL;
		top_node->next = monty.bottom;
		monty.bottom->prev = top_node;
	}

	/* Update top and bottom pointers */
	*top = second_top != NULL ? second_top : top_node;
	monty.bottom = top_node;

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
	if (*top == NULL) /* In the case of an empty stack or queue */
		return;

	/* Find the top node and the second last node */
	top_node = *top;
	last_node = monty.bottom;
	second_last = last_node->next;

	/* Bring the bottom to the top */
	if (top_node != monty.bottom) /* Only rotate stack with more than 1 node */
	{
		last_node->prev = top_node;
		last_node->next = NULL;
		top_node->next = last_node;
		second_last->prev = NULL;
	}
	/* Update top and bottom pointers */
	*top = last_node;
	monty.bottom = second_last;

	monty.exit_status = EXIT_SUCCESS;
}
