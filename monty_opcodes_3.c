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
	stack_t *top_node, *second_node, *last_node;

	(void)lnum;
	if (top == NULL || *top == NULL)
		return;

	/* Find the top, second, and the last node */
	top_node = *top;
	second_node = top_node->prev;
	last_node = top_node;
	while (last_node->prev != NULL)
		last_node = last_node->prev;

	/* Bring the top to the bottom and the second to the top */
	if (second_node != NULL)
		second_node->next = NULL;
	top_node->prev = NULL;
	top_node->next = top_node != last_node ? last_node : NULL;
	last_node->prev = top_node != last_node ? top_node : NULL;
	*top = second_node != NULL ? second_node : top_node;

	monty.exit_status = EXIT_SUCCESS;
}
