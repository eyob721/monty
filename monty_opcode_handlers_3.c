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
