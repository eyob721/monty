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
