#include "monty.h"

/**
 * add - handles the add opcode
 * @top: double pointer to the op of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void add(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *second_node;

	if (top == NULL)
		return;
	stack_len = get_stack_len(*top);
	if (stack_len < 2)
	{
		_dprintf(STDERR_FILENO, "L%d: can't add, stack too short\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	second_node = (*top)->prev;
	second_node->n += (*top)->n;
	pop(top, lnum);
	monty.exit_status = EXIT_SUCCESS;
}
