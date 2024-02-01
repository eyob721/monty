#include "monty.h"

/**
 * _add - handles the add opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void _add(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *second_node;

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
 * _sub - handles the sub opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void _sub(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *second_node;

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
 * _div - handles the div opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void _div(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *second_node;

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
 * _mul - handles the mul opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void _mul(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *second_node;

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

/**
 * _mod - handles the mod opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void _mod(stack_t **top, unsigned int lnum)
{
	int stack_len;
	stack_t *second_node;

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
