#include "monty.h"

/**
 * nop - handles the nop opcode
 * @top: double pointer to the op of the stack
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
 * add_opcode - handles the add opcode
 * @top: double pointer to the op of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void add_opcode(stack_t **top, unsigned int lnum)
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

/**
 * sub_opcode - handles the sub opcode
 * @top: double pointer to the op of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void sub_opcode(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *second_node;

	if (top == NULL)
		return;
	stack_len = get_stack_len(*top);
	if (stack_len < 2)
	{
		_dprintf(STDERR_FILENO, "L%d: can't sub, stack too short\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	second_node = (*top)->prev;
	second_node->n -= (*top)->n;
	pop(top, lnum);
	monty.exit_status = EXIT_SUCCESS;

}

/**
 * div_opcode - handles the div opcode
 * @top: double pointer to the op of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void div_opcode(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *second_node;

	if (top == NULL)
		return;
	stack_len = get_stack_len(*top);
	if (stack_len < 2)
	{
		_dprintf(STDERR_FILENO, "L%d: can't div, stack too short\n", lnum);
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
	second_node->n /= (*top)->n;
	pop(top, lnum);
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * mul_opcode - handles the mul opcode
 * @top: double pointer to the op of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void mul_opcode(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *second_node;

	if (top == NULL)
		return;
	stack_len = get_stack_len(*top);
	if (stack_len < 2)
	{
		_dprintf(STDERR_FILENO, "L%d: can't mul, stack too short\n", lnum);
		monty.exit_status = EXIT_FAILURE;
		return;
	}
	second_node = (*top)->prev;
	second_node->n *= (*top)->n;
	pop(top, lnum);
	monty.exit_status = EXIT_SUCCESS;

}
